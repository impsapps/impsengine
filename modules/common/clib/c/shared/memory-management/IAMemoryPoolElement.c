#include "IALibrary.h"
#include "IAMemoryPoolElement.h"

#define CLASSNAME "IAMemoryPoolElement"


void IAMemoryPoolElement_make(IAMemoryPoolElement * this, void * object){
    *this = (IAMemoryPoolElement){
        .object = object
    };
}

void IAMemoryPoolElement_run(IAMemoryPoolElement * this){
    IA_release(this->object);
}


