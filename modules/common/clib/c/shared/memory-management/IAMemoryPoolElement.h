#ifndef IAMemoryPoolElement_h
#define IAMemoryPoolElement_h

typedef struct{
    void * object;
} IAMemoryPoolElement;


void IAMemoryPoolElement_make(IAMemoryPoolElement * this, void * object);

void IAMemoryPoolElement_run(IAMemoryPoolElement * this);

#include "IAMemoryPoolElement+Generated.h"

#endif
