#include "IALibrary.h"
#include "IAArrayListIterator.h"

#define CLASSNAME "IAArrayListIterator"


void IAArrayListIterator_make(IAArrayListIterator * this, const IAArrayList * arrayList){
    this->base = IAObject_make(this);
    this->arrayList = arrayList;
    this->numberOfElementsLeft = IAArrayList_getCurrentSize(arrayList);
    this->indexOfCurrentElement = arrayList->offset;
}

void * IAArrayListIterator_getNextObject(IAArrayListIterator * this){
    if (this->numberOfElementsLeft == 0) {
        return NULL;
    }
    void * object = this->arrayList->objects[this->indexOfCurrentElement];
    this->indexOfCurrentElement++;
    if (this->indexOfCurrentElement == this->arrayList->arraySize) {
        this->indexOfCurrentElement = 0;
    }
    this->numberOfElementsLeft--;
    return object;
}

