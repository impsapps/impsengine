#ifndef IAMemoryPool_h
#define IAMemoryPool_h

#include "IAObject.h"
#include "IAStructArrayList.h"
#include "IAMemoryPoolElement.h"

IA_STRUCT_ARRAY_LIST(IAMemoryPoolElement)

typedef struct{
    //@extend
    IAObject base;
    IAStructArrayList_IAMemoryPoolElement * elements;
} IAMemoryPool;


void IAMemoryPool_init(IAMemoryPool * this);

void IAMemoryPool_add(IAMemoryPool * this, void * object);
void IAMemoryPool_run(IAMemoryPool * this);

void IAMemoryPool_deinit(IAMemoryPool * this);

#include "IAMemoryPool+Generated.h"

#endif
