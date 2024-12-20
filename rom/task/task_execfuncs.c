/*
    Copyright (C) 2015-2023, The AROS Development Team. All rights reserved.
*/

#ifdef DEBUG
#undef DEBUG
#endif
#define DEBUG 0

#include <aros/debug.h>
#include <aros/symbolsets.h>

#include <proto/exec.h>
#include <proto/task.h>

#include "task_intern.h"

#define DTS(x)

AROS_UFH3(void, TaskRes_PreLaunch,
          AROS_UFHA(struct Hook *, h, A0),
          AROS_UFHA(struct Task *, task, A2),
          AROS_UFHA(IPTR, unused, A1))
{
    AROS_USERFUNC_INIT

    struct TaskListEntry *newEntry;
    struct TaskResBase *TaskResBase = (struct TaskResBase *)h->h_Data;

    D(
      bug("[TaskRes] %s(0x%p)\n", __func__, task);
      bug("[TaskRes] %s: TaskResBase @ 0x%p\n", __func__, TaskResBase);
    )
    if ((newEntry = AllocMem(sizeof(struct TaskListEntry), MEMF_CLEAR)) != NULL)
    {
        D(bug("[TaskRes] %s: taskentry @ 0x%p for '%s'\n", __func__, newEntry, task->tc_Node.ln_Name));
        newEntry->tle_Task = task;
        NEWLIST(&newEntry->tle_HookTypes);
        if (IsListEmpty(&TaskResBase->trb_LockedLists))
            AddTail(&TaskResBase->trb_TaskList, &newEntry->tle_Node);
        else
            AddTail(&TaskResBase->trb_NewTasks, &newEntry->tle_Node);
    }

    AROS_USERFUNC_EXIT
}

AROS_LH4(APTR, NewAddTask,
        AROS_LHA(struct Task *,     task,      A1),
        AROS_LHA(APTR,              initialPC, A2),
        AROS_LHA(APTR,              finalPC,   A3),
        AROS_LHA(struct TagItem *,  tagList,   A4),
        struct ExecBase *, SysBase, 176, Task)
{
    AROS_LIBFUNC_INIT

    struct TaskResBase *TaskResBase;
    struct Hook plHook = { NULL };
    struct TagItem nat_Tags[] = {
        { TASKTAG_PRELAUNCHHOOK,        (IPTR)&plHook   },
        { TAG_DONE,                     0               },
        { TAG_DONE,                     0               }
    };
    TaskResBase = (struct TaskResBase *)SysBase->lb_TaskResBase;

    D(bug("[TaskRes] %s(0x%p)\n", __func__, task));

    plHook.h_Entry = (APTR)TaskRes_PreLaunch;
    plHook.h_Data = TaskResBase;
    if (tagList)
    {
        nat_Tags[1].ti_Tag = TAG_MORE;
        nat_Tags[1].ti_Data = (IPTR)tagList;
    }

    D(bug("[TaskRes] %s: Calling original Exec->NewAddTask()\n", __func__));

    return AROS_CALL4(APTR, TaskResBase->trb_NewAddTask,
                AROS_LCA(struct Task *,     task,      A1),
                AROS_LCA(APTR,              initialPC, A2),
                AROS_LCA(APTR,              finalPC,   A3),
                AROS_LCA(struct TagItem *,  nat_Tags,   A4),
                struct ExecBase *, SysBase);

    AROS_LIBFUNC_EXIT
}

AROS_LH1(void, RemTask,
        AROS_LHA(struct Task *, task, A1),
        struct ExecBase *, SysBase, 48, Task)
{
    AROS_LIBFUNC_INIT

    struct Task *findTask = task;
    struct TaskListEntry *taskEntry, *tmpEntry;
    struct TaskResBase *TaskResBase;
    BOOL removed = FALSE;

    TaskResBase = (struct TaskResBase *)SysBase->lb_TaskResBase;

    if (!findTask)
        findTask = FindTask(NULL);

    D(
        bug("[TaskRes] %s(0x%p)\n", __func__, task);
        if (findTask != task)
            bug("[TaskRes] %s: Real task @ 0x%p\n", __func__, findTask);
    )

    ForeachNodeSafe(&TaskResBase->trb_NewTasks, taskEntry, tmpEntry)
    {
        if (taskEntry->tle_Task == findTask)
        {
            D(bug("[TaskRes] %s: destroying new entry @ 0x%p\n", __func__, taskEntry));
            Remove(&taskEntry->tle_Node);
            FreeMem(taskEntry, sizeof(struct TaskListEntry));
            removed = TRUE;
            break;
        }
    }

    if (!removed)
    {
#if !defined(__AROSEXEC_SMP__)
        /* Don't let any other task interfere with us at the moment */
        Forbid();
#else
        EXEC_SPINLOCK_LOCK(&TaskResBase->TaskListSpinLock, NULL, SPINLOCK_MODE_WRITE);
#endif
        ForeachNodeSafe(&TaskResBase->trb_TaskList, taskEntry, tmpEntry)
        {
            if (taskEntry->tle_Task == findTask)
            {
                D(bug("[TaskRes] %s: taskentry @ 0x%p for '%s'\n", __func__, taskEntry, task->tc_Node.ln_Name));
                if (IsListEmpty(&TaskResBase->trb_LockedLists))
                {
                    D(bug("[TaskRes] %s: destroying entry\n", __func__));
                    Remove(&taskEntry->tle_Node);
                    FreeMem(taskEntry, sizeof(struct TaskListEntry));
                }
                else
                {
                    D(bug("[TaskRes] %s: flag entry for removal\n", __func__));
                    taskEntry->tle_Task = NULL;
                }
                break;
            }
        }
#if !defined(__AROSEXEC_SMP__)
        Permit();
#else
        EXEC_SPINLOCK_UNLOCK(&TaskResBase->TaskListSpinLock);
#endif
    }

    struct ETask *et = (struct ETask *)findTask->tc_UnionETask.tc_ETask;
    IPTR *tsstorage = NULL;

    if (et)
        tsstorage = et->et_Reserved[ETASK_RSVD_SLOTID];

    D(bug("[TaskRes] %s: Calling original Exec->RemTask()\n", __func__));

    if (TaskResBase->trb_RemTask)
    {
        AROS_CALL1NR(void, TaskResBase->trb_RemTask,
                    AROS_LCA(struct Task *,     findTask,      A1),
                    struct ExecBase *, SysBase);
    }

    if (tsstorage)
    {
        D(bug("[TaskRes] %s: Freeing Task SlotStorage @ 0x%p, size=%d\n",
              __func__, tsstorage, tsstorage ? (ULONG)tsstorage[__TS_FIRSTSLOT] : 0
        );)
        FreeMem(tsstorage, tsstorage[__TS_FIRSTSLOT] * sizeof(tsstorage[0]));
    }

    return;

    AROS_LIBFUNC_EXIT
}

static inline APTR __inline_Exec_SaveTaskStorage(APTR __SysBase)
{
    AROS_LIBREQ(SysBase, 51)
    return AROS_LC0(APTR, SaveTaskStorage,\
        struct ExecBase *, (__SysBase), 182, Exec    );
}

#define SaveTaskStorage() \
    __inline_Exec_SaveTaskStorage(__EXEC_LIBBASE)

static inline void __inline_Exec_RestoreTaskStorage(APTR __arg1, APTR __SysBase)
{
    AROS_LIBREQ(SysBase, 51)
    AROS_LC1NR(void, RestoreTaskStorage,\
         AROS_LCA(APTR, (__arg1), A0), \
        struct ExecBase *, (__SysBase), 183, Exec    );
}

#define RestoreTaskStorage(arg1) \
    __inline_Exec_RestoreTaskStorage((arg1), __EXEC_LIBBASE)

/* Called from DOS:RunCommand */
AROS_LH3(IPTR, NewStackSwap,
        AROS_LHA(struct StackSwapStruct *, sss, A0),
        AROS_LHA(LONG_FUNC, entry, A1),
        AROS_LHA(struct StackSwapArgs *, args, A2),
        struct ExecBase *, SysBase, 134, Task)
{
    AROS_LIBFUNC_INIT

    struct TaskResBase *TaskResBase;
    TaskResBase = (struct TaskResBase *)SysBase->lb_TaskResBase;

    APTR tsid = SaveTaskStorage();
    DTS(bug("[TaskRes] %s: Pre-StackSwap() <TSID=$%p, TaskStorage @ 0x%p>\n",
          __func__, tsid, FindTask(NULL)->tc_UnionETask.tc_ETask->et_Reserved[ETASK_RSVD_SLOTID]
    ));

    IPTR retval = AROS_CALL3(IPTR, TaskResBase->trb_NewStackSwap,
                AROS_LCA(struct StackSwapStruct *, sss, A0),
                AROS_LCA(LONG_FUNC, entry, A1),
                AROS_LCA(struct StackSwapArgs *, args, A2),
                struct ExecBase *, SysBase);

    DTS(bug("[TaskRes] %s: post-StackSwap() <TSID=$%p, TaskStorage @ 0x%p>\n",
          __func__, tsid, FindTask(NULL)->tc_UnionETask.tc_ETask->et_Reserved[ETASK_RSVD_SLOTID]
    ));

    RestoreTaskStorage(tsid);

    DTS(bug("[TaskRes] %s: Restored TaskStorage <TSID=$%p, TaskStorage @ 0x%p>\n",
          __func__, tsid, FindTask(NULL)->tc_UnionETask.tc_ETask->et_Reserved[ETASK_RSVD_SLOTID]
    ));
    
    return retval;

    AROS_LIBFUNC_EXIT
} /* NewStackSwap() */
