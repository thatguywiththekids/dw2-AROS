/*
    Copyright (C) 1995-2025, The AROS Development Team. All rights reserved.

    C99 function putwc().
*/

/*****************************************************************************

    NAME
#include <wchar.h>
#include <stdio.h>

        wint_t putwc(

    SYNOPSIS
        wchar_t wc,
        FILE * fp)

    FUNCTION
        Writes the wide character wc to the stream and advances the position indicator.

    INPUTS
        wc - The wide character to write.
        fp - Pointer to a FILE object that identifies an output stream.
        
    RESULT
        On success, the character written is returned.

    NOTES

    EXAMPLE

    BUGS

    SEE ALSO

    INTERNALS
        putwc() is an alias to fputwc()
******************************************************************************/
