//
//  IAArrayList.h
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 25.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineCLibrary_IAArrayList_h
#define ImpsEngineCLibrary_IAArrayList_h

#include <stddef.h>
#include <stdbool.h>

typedef struct IAArrayList IAArrayList;

struct IAArrayList{
    void ** objects;
    size_t offset;
    //@get
    size_t currentSize;
    //@get
    size_t arraySize;
    void (*changeArraySize)(IAArrayList * arrayList, size_t newArraySize);
};


void IAArrayList_makeWithMaxSizeAndBuffer(IAArrayList *, size_t maxArraySize, void * buffer[maxArraySize]);

void IAArrayList_init(IAArrayList *, size_t initialArraySize);
void IAArrayList_initWithObjects(IAArrayList *, size_t initialArraySize, int numberOfObjects, ...);
IAArrayList * IAArrayList_newWithObjects(size_t initialArraySize, int numberOfObjects, ...);

void IAArrayList_initShallowCopy(IAArrayList *, const IAArrayList * arrayListToCopy);
void IAArrayList_initDeepCopy(IAArrayList *, const IAArrayList * arrayListToCopy, void * (*copyObject)(void * object));

void IAArrayList_add(IAArrayList *, void * object);
void IAArrayList_addAllFromArrayList(IAArrayList *, const IAArrayList * arrayList);
void IAArrayList_insertAtIndex(IAArrayList *, size_t index, void * object);

void IAArrayList_changeArraySize(IAArrayList *, size_t newArraySize);

void * IAArrayList_get(const IAArrayList *, size_t index);
void * IAArrayList_getFirst(const IAArrayList *);
void * IAArrayList_getLast(const IAArrayList *);

bool IAArrayList_isEmpty(const IAArrayList *);

void * IAArrayList_removeAtIndex(IAArrayList *, size_t index);
void * IAArrayList_removeObject(IAArrayList *, void * object);
void * IAArrayList_removeFirst(IAArrayList *);
void * IAArrayList_removeLast(IAArrayList *);

void IAArrayList_clear(IAArrayList *);

void IAArrayList_callFunctionOnAllObjects(const IAArrayList *, void(*function)(void * object));

void IAArrayList_deinit(IAArrayList *);

#include "IAArrayListIterator.h"
#include "IAArrayList+Generated.h"

#endif


