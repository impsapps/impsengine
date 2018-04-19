//
//  IAKeyValueContainer.c
//  Hit Verto
//
//  Created by Konstantin Merker on 05/01/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAKeyValueContainer.h"
#include "IAKeyValueDelegateOperations.h"
#include "IAArrayListIterator.h"
#include "IAHashing.h"

#define CLASSNAME "IAKeyValueContainer"


typedef struct{
    const IAHashMap * keyValueDelegates;
    const char * dataPosition;
    IAString * temp;
} IAKeyValueContainer_onKeyValueParsedState;

void IAKeyValueContainer_onKeyValueParsed(IAKeyValueContainer_onKeyValueParsedState * state, long keyLength, long valueLength);


static long IAKeyValueContainer_toNumber(size_t lengthOfData, const char * data, size_t * charsReadOut){
    size_t charsRead = 0;
    char c;
    long number = 0;
    while (lengthOfData > 0) {
        c = *data;
        if (c >= '0' && c <= '9') {
            number *= 10;
            number += c - '0';
        }else{
            *charsReadOut = charsRead;
            return number;
        }
        charsRead++;
        data++;
        lengthOfData--;
    }
    *charsReadOut = charsRead;
    return number;
}

static bool IAKeyValueContainer_isValidFormat(size_t lengthOfData, const char data[lengthOfData], void * object, void (*onKeyValueParsed)(void * object, long keyLength, long valueLength)){
    size_t lengthNeeded = 0;
    while (lengthOfData > 0 && *data != '#') {
        size_t temp;
        long keyLength = IAKeyValueContainer_toNumber(lengthOfData, data, &temp);
        if (temp == 0){
            return false;
        }
        debugAssert(temp <= lengthOfData);
        data += temp;
        lengthOfData -= temp;
        lengthNeeded += keyLength;
        if(lengthOfData == 0 || *data != '-'){
            return false;
        }
        data++;
        lengthOfData--;
        
        size_t valueLength = IAKeyValueContainer_toNumber(lengthOfData, data, &temp);
        if (temp == 0){
            return false;
        }
        debugAssert(temp <= lengthOfData);
        data += temp;
        lengthOfData -= temp;
        lengthNeeded += valueLength;
        if(lengthOfData != 0 && *data == ','){
            data++;
            lengthOfData--;
        }
        if(onKeyValueParsed != NULL){
            onKeyValueParsed(object, keyLength, valueLength);
        }
    }
    if (lengthOfData == 0 || *data != '#'){
        return false;
    }
    data++;
    lengthOfData--;
    
    if(lengthOfData >= lengthNeeded){
        return true;
    }else{
        return false;
    }
}

bool IAKeyValueContainer_load(const IAHashMap * keyValueDelegates, const IAString * data){
    //format: "[lengthOfFirstKey]-[lengthOfFirstValue],[lengthOfSecondKey]-[lengthOfSecondValue],...,[lengthOfLastKey]-[lengthOfLastValue]#[allValues]"
    size_t lengthOfData = IAString_getLength(data);
    const char * dataStr = IAString_toCharArray(data);
    long maxKeyLength;
    if(IAKeyValueContainer_isValidFormat(lengthOfData, dataStr, &maxKeyLength, NULL) == false){
        return false;
    }else{
        size_t hashTagPosition;
        bool wasHashTagPositionFound = IAString_getIndexOfFirstPatternMatch(data, "#", &hashTagPosition);
        debugAssert(wasHashTagPositionFound);
        const char * dataPosition = IAString_toCharArray(data);
        dataPosition += hashTagPosition + 1;
        IAString temp;
        IAString_init(&temp, "");
        IAKeyValueContainer_onKeyValueParsedState state = {.keyValueDelegates = keyValueDelegates, .dataPosition = dataPosition, .temp = &temp};
        IAKeyValueContainer_isValidFormat(lengthOfData, dataStr, &state, (void (*)(void *, long, long)) IAKeyValueContainer_onKeyValueParsed);
        IAString_deinit(&temp);
        return true;
    }
}

void IAKeyValueContainer_onKeyValueParsed(IAKeyValueContainer_onKeyValueParsedState * state, long keyLength, long valueLength){
    char key[keyLength + 1];
    memcpy(key, state->dataPosition, keyLength);
    key[keyLength] = '\0';
    state->dataPosition += keyLength;
    IAString_setWithLength(state->temp, state->dataPosition, valueLength);
    state->dataPosition += valueLength;
    IAKeyValueDelegate * delegate = IAHashMap_get(state->keyValueDelegates, key);
    if (delegate != NULL) {
        IAKeyValueDelegate_applyStringToValue(delegate, state->temp);
    }
}

void IAKeyValueContainer_save(const IAHashMap * keyValueDelegates, IAString * data){
    IAString_set(data, "");
    
    IAString keysAndValues;
    IAString_init(&keysAndValues, "");
    
    IAHashMapIterator iterator;
    IAHashMapIterator_makeIteratorOverKeys(&iterator, keyValueDelegates);
    char * key;
    IAString temp;
    IAString_init(&temp, "");
    while ((key = IAHashMapIterator_getNextObject(&iterator)) != NULL) {
        IAKeyValueDelegate * delegate = IAHashMap_get(keyValueDelegates, key);
        if (IAKeyValueDelegate_shouldSave(delegate) == true) {
            //key
            IAString_concatLong(data, strlen(key));
            IAString_concat(data, "-");
            IAString_concat(&keysAndValues, key);
            
            //value
            IAString_set(&temp, "");
            IAKeyValueDelegate_setString(delegate, &temp);
            IAString_concatLong(data, IAString_getLength(&temp));
            IAString_concat(data, ",");
            IAString_concatString(&keysAndValues, &temp);
        }
    }
    IAString_removeLast(data);
    IAString_concat(data, "#");
    IAString_concatString(data, &keysAndValues);
    IAString_deinit(&temp);
    IAString_deinit(&keysAndValues);
}


