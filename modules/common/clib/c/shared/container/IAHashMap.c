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

void IAHashMap_getKeyForObject(const void * object, char keyOut[IA_KEY_SIZE_FOR_OBJECT]){
    char temp[sizeof(void *)];
    memcpy(temp, &object, sizeof(void *));
    int iKeyOut = 0;
    for (int i = 0; i < sizeof(void *); i++) {
        if (temp[i] == 0) {
            keyOut[iKeyOut++] = 127;
            keyOut[iKeyOut++] = 1;
        }else if (temp[i] == 127){
            keyOut[iKeyOut++] = 127;
            keyOut[iKeyOut++] = 127;
        }else{
            keyOut[iKeyOut++] = temp[i];
        }
    }
    keyOut[iKeyOut] = '\0';
    debugAssert(iKeyOut < IA_KEY_SIZE_FOR_OBJECT);
}

void IAHashMap_init(IAHashMap * this, size_t estimatedNumberOfElements){
    size_t fixedSize = IAHashMap_getFixedSizeForEstimatedNumberOfElements(estimatedNumberOfElements);
    IAHashMap_initWithFixedSize(this, fixedSize);
}

void IAHashMap_initWithFixedSize(IAHashMap * this, size_t fixedSize){
    this->base = IAObject_make(this);
    this->size = fixedSize;
    this->list = IA_malloc(sizeof(IAHashMapList*) * fixedSize);
    for (size_t i = 0; i < fixedSize; i++){
        this->list[i] = NULL;
    }
    IA_incrementInitCount();
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
    IA_retain(object);
    size_t index = IAHashMap_moduloHashFunction(this->size, key);
    
    IAHashMapList ** pointerToList = &(this->list[index]);
    IAHashMapList * list = (*pointerToList);
    
    while (list != NULL){
        pointerToList = &(list->next);
        list = list->next;
    }
    
    size_t lengthOfKey = strlen(key);
    IAHashMapList * newListElement = IA_malloc(sizeof(IAHashMapList) + lengthOfKey + 1);
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
    IA_autorelease(object);
    return object;
}

void IAHashMap_clear(IAHashMap * this){
    size_t iArray;
    for(iArray = 0; iArray < this->size; iArray ++){
        IAHashMapList * list = this->list[iArray];
        while(list != NULL){
            IAHashMapList * next = list->next;
            IA_release(list->object);
            IA_free(list);
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
    this->size = hashMapTemp.size;
    this->list = hashMapTemp.list;
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
            IA_release(list->object);
            IA_free(list);
            list = next;
        }
    }
    IA_free(this->list);
    IA_decrementInitCount();
}



