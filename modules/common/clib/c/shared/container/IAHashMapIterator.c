//
//  IAHashMapIterator.c
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 31.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAHashMapIterator.h"

#define CLASSNAME "IAHashMapIterator"


void * IAHashMapIterator_returnValues(IAHashMapList * list);
void * IAHashMapIterator_returnKeys(IAHashMapList * list);


void IAHashMapIterator_makeIteratorOverValues(IAHashMapIterator * this, const IAHashMap * hashMap){
    this->base = IAObject_make(this);
    this->hashMap = hashMap;
    this->listIndex = 0;
    this->currentListElement = hashMap->list[0];
    this->returnResult = IAHashMapIterator_returnValues;
}

void IAHashMapIterator_makeIteratorOverKeys(IAHashMapIterator * this, const IAHashMap * hashMap){
    this->base = IAObject_make(this);
    this->hashMap = hashMap;
    this->listIndex = 0;
    this->currentListElement = hashMap->list[0];
    this->returnResult = IAHashMapIterator_returnKeys;
}

void * IAHashMapIterator_getNextObject(IAHashMapIterator * this){
    while (this->currentListElement == NULL) {
        if (this->listIndex == this->hashMap->size - 1) {
            return NULL;
        }
        this->listIndex++;
        this->currentListElement = this->hashMap->list[this->listIndex];
    }
    void * result = this->returnResult(this->currentListElement);
    this->currentListElement = this->currentListElement->next;
    return result;
}

void * IAHashMapIterator_returnValues(IAHashMapList * list){
    return list->object;
}

void * IAHashMapIterator_returnKeys(IAHashMapList * list){
    return list->key;
}

