/*
     AHI - Hardware independent audio subsystem
     Copyright (C) 2017 The AROS Dev Team
     Copyright (C) 1996-2005 Martin Blom <martin@blom.org>
     
     This library is free software; you can redistribute it and/or
     modify it under the terms of the GNU Library General Public
     License as published by the Free Software Foundation; either
     version 2 of the License, or (at your option) any later version.
     
     This library is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     Library General Public License for more details.
     
     You should have received a copy of the GNU Library General Public
     License along with this library; if not, write to the
     Free Software Foundation, Inc., 59 Temple Place - Suite 330, Cambridge,
     MA 02139, USA.
*/

#ifndef ahi_modeinfo_h
#define ahi_modeinfo_h

#include <exec/types.h>
#include <utility/tagitem.h>

ULONG
_AHI_GetAudioAttrsA( ULONG                    id,
		     struct AHIPrivAudioCtrl* actrl,
		     struct TagItem*          tags,
		     struct AHIBase*          AHIBase );

ULONG
_AHI_BestAudioIDA( struct TagItem* tags,
		   struct AHIBase* AHIBase );

BOOL
TestAudioID( ULONG id,
             struct TagItem *tags );

#endif /* ahi_modeinfo_h */
