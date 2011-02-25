/*
 * Copyright (c) 2010-2011 Kevin M. Bowling, <kevin.bowling@kev009.com>, USA
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CRAFTD_LIST_H
#define CRAFTD_LIST_H

#include "klist.h"

#define __cdList_free(x)

KLIST_INIT(cdList, void*, __cdList_free);

typedef struct _CDList {
    klist_t(cdList)* list;

    pthread_rwlock_t lock;
} CDList;

typedef kliter_t(cdList)* CDListIterator;

CDList* CD_CreateList (void);

CDList* CD_CloneList (CDList* self);

void** CD_DestroyList (CDList* self);

CDListIterator CD_ListBegin (CDList* self);

CDListIterator CD_ListEnd (CDList* self);

CDListIterator CD_ListNext (CDListIterator self);

size_t CD_ListLength (CDList* self);

void* CD_ListIteratorValue (CDListIterator iterator);

CDList* CD_ListPush (CDList* self, void* data);

void* CD_ListShift (CDList* self);

void* CD_ListDelete (CDList* self, void* data);

void* CD_ListDeleteAll (CDList* self, void* data);

void* CD_ListFirst (CDList* self);

void* CD_ListLast (CDList* self);

void** CD_ListClear (CDList* self);

#define CD_LIST_FOREACH(list, it) \
    for (CDListIterator it = CD_ListBegin(list), end = CD_ListEnd(list); it != end; it = CD_ListNext(it))

#endif