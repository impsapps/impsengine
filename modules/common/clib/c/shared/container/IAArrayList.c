#include "IALibrary.h"
#include "IAArrayList.h"
#include "IAArrayListIterator.h"
#include <stdarg.h>
#include <string.h>

#define CLASSNAME "IAArrayList"


void IAArrayList_addObjectsWithVaribleArguments(IAArrayList * this, int numberOfObjects, va_list args);
void * IAArrayList_returnObject(void * object);

void IAArrayList_changeArraySize(IAArrayList * this, size_t newArraySize);


void IAArrayList_init(IAArrayList * this, size_t initialArraySize){
    debugAssert(initialArraySize > 0 && "Initial array size must be greater than 0");
    this->base = IAObject_make(this);
    this->objects = IA_calloc(initialArraySize, sizeof(void *));
    this->offset = 0;
    this->currentSize = 0;
    this->arraySize = initialArraySize;
    IA_incrementInitCount();
}

void IAArrayList_initWithObjects(IAArrayList * this, size_t initialArraySize, int numberOfObjects, ...){
    IAArrayList_init(this, initialArraySize);
    va_list args;
    va_start(args, numberOfObjects);
    IAArrayList_addObjectsWithVaribleArguments(this, numberOfObjects, args);
    va_end(args);
}

IAArrayList * IAArrayList_newWithObjects(size_t initialArraySize, int numberOfObjects, ...){
    IAArrayList * this = IAArrayList_new(initialArraySize);
    va_list args;
    va_start(args, numberOfObjects);
    IAArrayList_addObjectsWithVaribleArguments(this, numberOfObjects, args);
    va_end(args);
    return this;
}

void IAArrayList_addObjectsWithVaribleArguments(IAArrayList * this, int numberOfObjects, va_list args){
    for (int i = 0; i < numberOfObjects; i++) {
        void * object = va_arg(args, void *);
        IAArrayList_add(this, object);
    }
}

void IAArrayList_initShallowCopy(IAArrayList * this, const IAArrayList * arrayListToCopy){
    IAArrayList_initDeepCopy(this, arrayListToCopy, IAArrayList_returnObject);
}

void * IAArrayList_returnObject(void * object){
    return object;
}

void IAArrayList_initDeepCopy(IAArrayList * this, const IAArrayList * arrayListToCopy, void * (*copyObject)(void * object)){
    this->base = IAObject_make(this);
    this->objects = IA_calloc(arrayListToCopy->arraySize, sizeof(void *));
    this->offset = 0;
    this->currentSize = 0;
    this->arraySize = arrayListToCopy->arraySize;
    for (size_t i = 0; i < arrayListToCopy->currentSize; i++) {
        void * object = IAArrayList_get(arrayListToCopy, i);
        object = copyObject(object);
        IAArrayList_add(this, object);
    }
    IA_incrementInitCount();
}

void IAArrayList_add(IAArrayList * this, void * object){
    IA_retain(object);
    if (this->currentSize == this->arraySize){
        IAArrayList_changeArraySize(this, this->currentSize * 2);
    }
    size_t index = (this->offset + this->currentSize) % this->arraySize;
    this->objects[index] = object;
    this->currentSize ++;
}

void IAArrayList_addAllFromArrayList(IAArrayList * this, const IAArrayList * arrayList){
    void * object;
    foreach (object in arrayList(arrayList)){
        IAArrayList_add(this, object);
    }
}

void IAArrayList_insertAtIndex(IAArrayList * this, size_t index, void * object){
    debugAssert(index <= this->currentSize && "IAArrayList_insertAtIndex: index out of bounds");
    IA_retain(object);
    if (this->currentSize == this->arraySize){
        IAArrayList_changeArraySize(this, this->currentSize * 2);
    }
    
    size_t currentIndex;
    
    if (index > this->currentSize / 2) {
        //nach rechts verschieben
        size_t targetIndex = (this->offset + index) % this->arraySize;
        currentIndex = (this->offset + this->currentSize) % this->arraySize;
        
        while (currentIndex != targetIndex) {
            size_t nextIndex = currentIndex - 1;
            if(nextIndex == -1) nextIndex = this->arraySize - 1;
            this->objects[currentIndex] = this->objects[nextIndex];
            currentIndex = nextIndex;
        }
    }else{
        //nach links verschieben
        if (this->offset == 0) {
            this->offset = this->arraySize - 1;
        }else{
            this->offset --;
        }
        
        size_t targetIndex = (this->offset + index) % this->arraySize;
        currentIndex = this->offset % this->arraySize;
        
        if (currentIndex == -1) {
            currentIndex = this->arraySize - 1;
        }
        
        while (currentIndex != targetIndex) {
            size_t nextIndex = currentIndex + 1;
            if(nextIndex == this->arraySize) nextIndex = 0;
            this->objects[currentIndex] = this->objects[nextIndex];
            currentIndex = nextIndex;
        }
        
    }
    this->objects[currentIndex] = object;
    
    this->currentSize++;
}

void IAArrayList_changeArraySize(IAArrayList * this, size_t newArraySize){
    void ** objects = IA_calloc(newArraySize, sizeof(void *));
    void * object;
    size_t i = 0;
    foreach (object in arrayList(this)){
        objects[i] = object;
        i++;
    }
    IA_free(this->objects);
    this->objects = objects;
    this->offset = 0;
    this->arraySize = newArraySize;
}

void * IAArrayList_get(const IAArrayList * this, size_t index){
    if(index >= this->currentSize) {
        return NULL;
    }
    index = (index + this->offset) % this->arraySize;
    return this->objects[index];
}

void * IAArrayList_getFirst(const IAArrayList * this) {
	return IAArrayList_get(this, 0);
}

void * IAArrayList_getLast(const IAArrayList * this){
    size_t currentSize = IAArrayList_getCurrentSize(this);
    if (currentSize == 0) {
        return NULL;
    }else{
        size_t lastIndex = currentSize - 1;
        return IAArrayList_get(this, lastIndex);
    }
}

bool IAArrayList_isEmpty(const IAArrayList * this){
    if (this->currentSize == 0) {
        return true;
    }else{
        return false;
    }
}

void * IAArrayList_removeAtIndex(IAArrayList * this, size_t index){
    if(index >= this->currentSize) {
        return NULL;
    }
    size_t currentIndex = (this->offset + index) % this->arraySize;
    size_t targetIndex;
    
    void * result = this->objects[currentIndex];
    
    if (index > (this->currentSize) / 2) {
        //von rechts holen
        targetIndex = (this->offset + this->currentSize - 1) % this->arraySize;
        
        if (targetIndex == -1) {
            targetIndex = this->arraySize - 1;
        }
        
        while (currentIndex != targetIndex) {
            size_t nextIndex = currentIndex + 1;
            if(nextIndex == this->arraySize) nextIndex = 0;
            this->objects[currentIndex] = this->objects[nextIndex];
            currentIndex = nextIndex;
        }
    }else{
        //von links holen
        targetIndex = (this->offset) % this->arraySize;
        
        while (currentIndex != targetIndex) {
            size_t nextIndex = currentIndex - 1;
            if(nextIndex == -1) nextIndex = this->arraySize - 1;
            this->objects[currentIndex] = this->objects[nextIndex];
            currentIndex = nextIndex;
        }
        this->offset ++;
        if (this->offset >= this->arraySize) {
            this->offset=0;
        }
    }
    
    this->currentSize--;
    IA_autorelease(result);
    return result;
}

void * IAArrayList_removeObject(IAArrayList * this, void * object){
    void * objectInArrayList;
    size_t index = 0;
    foreach (objectInArrayList in arrayList(this)){
        if (objectInArrayList == object) {
            void * removedObject = IAArrayList_removeAtIndex(this, index);
            return removedObject;
        }else{
            index++;
        }
    }
    return NULL;
}

void * IAArrayList_removeFirst(IAArrayList * this) {
	return IAArrayList_removeAtIndex(this, 0);
}

void * IAArrayList_removeLast(IAArrayList * this){
    size_t currentSize = IAArrayList_getCurrentSize(this);
    if (currentSize == 0) {
        return NULL;
    }
    return IAArrayList_removeAtIndex(this, currentSize - 1);
}

void IAArrayList_clear(IAArrayList * this){
    void * object;
    foreach (object in arrayList(this)){
        IA_release(object);
    }
    this->offset = 0;
    this->currentSize = 0;
}

void IAArrayList_callFunctionOnAllObjects(const IAArrayList * this, void(*function)(void * object)){
    size_t index = this->offset;
    for (size_t i = 0; i < this->currentSize; i++) {
        function(this->objects[index]);
        index++;
        if (index == this->arraySize) {
            index = 0;
        }
    }
}

void IAArrayList_deinit(IAArrayList * this){
    void * object;
    foreach (object in arrayList(this)){
        IA_release(object);
    }
    IA_free(this->objects);
    IA_decrementInitCount();
}


