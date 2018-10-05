#include "IALibrary.h"
#include "IALibrary+SendOnMemoryWarningNotification.h"
#include "IAMemoryPool.h"
#include "IAMemoryPoolElement.h"

#define CLASSNAME "IAMemoryPool"

// we do malloc pool element list manually to prevent allocation tracking
static IAStructArrayList_IAMemoryPoolElement * mallocMemoryPoolElementList(size_t count){
    size_t size = sizeof(IAStructArrayList_IAMemoryPoolElement) + sizeof(IAMemoryPoolElement) * count;
    IAStructArrayList_IAMemoryPoolElement * elements = malloc(size);
    while (elements == NULL) {
        IALibrary_onMemoryWarning();
        elements = malloc(size);
    }
    IAStructArrayList_IAMemoryPoolElement_make(elements, count, (IAMemoryPoolElement *) (elements + 1));
    return elements;
}

void IAMemoryPool_init(IAMemoryPool * this){
    *this = (IAMemoryPool){
        .base = IAObject_make(this)
    };
    this->elements = mallocMemoryPoolElementList(10);
    IA_incrementInitCount();
}

void IAMemoryPool_add(IAMemoryPool * this, void * object){
    IAMemoryPoolElement element;
    IAMemoryPoolElement_make(&element, object);
    size_t currentSize = IAStructArrayList_IAMemoryPoolElement_getCurrentSize(this->elements);
    if (currentSize == IAStructArrayList_IAMemoryPoolElement_getBufferSize(this->elements)){
        IAStructArrayList_IAMemoryPoolElement * newElements = mallocMemoryPoolElementList(currentSize * 2);
        IAStructArrayList_IAMemoryPoolElement_addAllFromList(newElements, this->elements);
        free(this->elements);
        this->elements = newElements;
    }
    IAStructArrayList_IAMemoryPoolElement_add(this->elements, element);
}

void IAMemoryPool_run(IAMemoryPool * this){
    while (IAStructArrayList_IAMemoryPoolElement_isEmpty(this->elements) == false) {
        IAMemoryPoolElement element = IAStructArrayList_IAMemoryPoolElement_removeLast(this->elements);
        IAMemoryPoolElement_run(&element);
    }
}

void IAMemoryPool_deinit(IAMemoryPool * this){
    IAMemoryPool_run(this);
    free(this->elements);
    IA_decrementInitCount();
}

