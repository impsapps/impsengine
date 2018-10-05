#include <string.h>
#include "IALibrary.h"
#include "IAAllocationTrackingElement.h"

#define CLASSNAME "IAAllocationTrackingElement"

#ifdef DEBUG

void IAAllocationTrackingElement_init(IAAllocationTrackingElement * this, size_t size, const char * className, bool isObject){
    this->base = IAObject_make(this);
    this->size = size;
    size_t strLength = strlen(className);
    this->className = IA_malloc(strLength + 1);
    this->isObject = isObject;
    memcpy(this->className, className, strLength + 1);
    IA_incrementInitCount();
}

void IAAllocationTrackingElement_deinit(IAAllocationTrackingElement * this){
    IA_free(this->className);
    IA_decrementInitCount();
}

#endif

