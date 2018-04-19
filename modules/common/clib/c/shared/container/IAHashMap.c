//
//  IAHashMap.c
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 25.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAHashMap.h"
#include <string.h>

#define CLASSNAME "IAHashMap"


size_t IAHashMap_getFixedSizeForEstimatedNumberOfElements(size_t estimatedNumberOfElements);
size_t IAHashMap_moduloHashFunction(size_t size, const char * key);


size_t IAHashMap_getFixedSizeForEstimatedNumberOfElements(size_t estimatedNumberOfElements){
    debugAssert(estimatedNumberOfElements > 0);
    return estimatedNumberOfElements * 4 / 3;
}

void IAHashMap_init(IAHashMap * this, size_t estimatedNumberOfElements){
    size_t fixedSize = IAHashMap_getFixedSizeForEstimatedNumberOfElements(estimatedNumberOfElements);
    IAHashMap_initWithFixedSize(this, fixedSize);
}

void IAHashMap_initWithFixedSize(IAHashMap * this, size_t fixedSize){
    this->size = fixedSize;
    this->list = IA_malloc(sizeof(IAHashMapList*) * fixedSize);
    for (size_t i = 0; i < fixedSize; i++){
        this->list[i] = NULL;
    }
}

size_t IAHashMap_moduloHashFunction(size_t size, const char * key){
    size_t sum = 0;
    size_t i = 0;
    while (key[i]) {
        sum += (unsigned char) key[i++];
    }
#ifdef DEBUG
    assert(sum >= 0);
#endif
    return sum % size;
}


void IAHashMap_add(IAHashMap * this, const char * key, void * object){
    size_t index = IAHashMap_moduloHashFunction(this->size, key);
    
    IAHashMapList ** pointerToList = &(this->list[index]);
    IAHashMapList * list = (*pointerToList);
    
    while (list != NULL){
        pointerToList = &(list->next);
        list = list->next;
    }
    
    size_t lengthOfKey = strlen(key);
    IAHashMapList * newListElement = IA_malloc(sizeof(IAHashMapList) + lengthOfKey + 1);
    IA_decreaseAllocationCount();
    newListElement->next = NULL;
    newListElement->object = object;
    
    memcpy(newListElement->key, key, lengthOfKey + 1);
    
    (*pointerToList) = newListElement;
}

bool IAHashMap_containsKey(const IAHashMap * this, const char * key){
    size_t index = IAHashMap_moduloHashFunction(this->size, key);
    
    IAHashMapList * list = this->list[index];
    while (list != NULL && strcmp(list->key, key) != 0){
        list = list->next;
    }
    if (list == NULL) return false;
    else return true;
}

void * IAHashMap_get(const IAHashMap * this, const char * key){
    size_t index = IAHashMap_moduloHashFunction(this->size, key);
    
    IAHashMapList * list = this->list[index];
    while (list != NULL && strcmp(list->key, key) != 0){
        list = list->next;
    }
    if (list == NULL) return NULL;
    else return list->object;
    
}

void * IAHashMap_remove(IAHashMap * this, const char *  key){
    size_t index = IAHashMap_moduloHashFunction(this->size, key);
    
    IAHashMapList ** pointerToList = &(this->list[index]);
    IAHashMapList * list = (*pointerToList);
    
    while (list != NULL && strcmp(list->key, key) != 0){
        pointerToList = &(list->next);
        list = list->next;
    }
    
    if (list == NULL){
        return NULL;
    }
    
    *pointerToList = list->next;
    
    void * object = list->object;
    IA_free(list);
    IA_increaseAllocationCount();
    return object;
}

void IAHashMap_clear(IAHashMap * this){
    size_t iArray;
    for(iArray = 0; iArray < this->size; iArray ++){
        IAHashMapList * list = this->list[iArray];
        while(list != NULL){
            IAHashMapList * next = list->next;
            IA_free(list);
            IA_increaseAllocationCount();
            list = next;
        }
        this->list[iArray] = NULL;
    }
}

void IAHashMap_changeSize(IAHashMap * this, size_t estimatedNumberOfElements){
    size_t fixedSize = IAHashMap_getFixedSizeForEstimatedNumberOfElements(estimatedNumberOfElements);
    IAHashMap_changeSizeWithFixedSize(this, fixedSize);
}

void IAHashMap_changeSizeWithFixedSize(IAHashMap * this, size_t fixedSize){
    if (IAHashMap_getSize(this) == fixedSize) {
        return;
    }
    IAHashMap hashMapTemp;
    IAHashMap_initWithFixedSize(&hashMapTemp, fixedSize);
    char * key;
    void * object;
    foreach (key in hashMapKeys(this)) {
        object = IAHashMap_get(this, key);
        IAHashMap_add(&hashMapTemp, key, object);
    }
    IAHashMap_deinit(this);
    *this = hashMapTemp;
}

void IAHashMap_callFunctionOnAllObjects(const IAHashMap * this, void(*function)(void * object)){
    size_t iArray;
    for(iArray = 0; iArray < this->size; iArray ++){
        IAHashMapList * list = this->list[iArray];
        while(list != NULL){
            function(list->object);
            list = list->next;
        }
    }
}

void IAHashMap_deinit(IAHashMap * this){
    size_t iArray;
    for(iArray = 0; iArray < this->size; iArray ++){
        IAHashMapList * list = this->list[iArray];
        while(list != NULL){
            IAHashMapList * next = list->next;
            IA_free(list);
            IA_increaseAllocationCount();
            list = next;
        }
    }
    IA_free(this->list);
}



