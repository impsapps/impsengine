#include "IALibrary.h"
#include "IAKeyValueHashMap.h"
#include "IAKeyValueElementOperations.h"
#include "IAArrayListIterator.h"
#include "IAHashing.h"

#define CLASSNAME "IAKeyValueHashMap"


typedef struct{
    const IAHashMap * elements;
    const char * dataPosition;
    IAString * temp;
} IAKeyValueHashMap_onKeyValueParsedState;

void IAKeyValueHashMap_onKeyValueParsed(IAKeyValueHashMap_onKeyValueParsedState * state, long keyLength, long valueLength);


static long IAKeyValueHashMap_toNumber(size_t lengthOfData, const char * data, size_t * charsReadOut){
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

static bool IAKeyValueHashMap_isValidFormat(size_t lengthOfData, const char data[lengthOfData], void * object, void (*onKeyValueParsed)(void * object, long keyLength, long valueLength)){
    size_t lengthNeeded = 0;
    while (lengthOfData > 0 && *data != '#') {
        size_t temp;
        long keyLength = IAKeyValueHashMap_toNumber(lengthOfData, data, &temp);
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
        
        size_t valueLength = IAKeyValueHashMap_toNumber(lengthOfData, data, &temp);
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

bool IAKeyValueHashMap_load(const IAHashMap * elements, const IAString * data){
    //format: "[lengthOfFirstKey]-[lengthOfFirstValue],[lengthOfSecondKey]-[lengthOfSecondValue],...,[lengthOfLastKey]-[lengthOfLastValue]#[allValues]"
    size_t lengthOfData = IAString_getLength(data);
    const char * dataStr = IAString_toCharArray(data);
    long maxKeyLength;
    if(IAKeyValueHashMap_isValidFormat(lengthOfData, dataStr, &maxKeyLength, NULL) == false){
        return false;
    }else{
        size_t hashTagPosition;
        debugOnly(bool wasHashTagPositionFound =) IAString_getIndexOfFirstPatternMatch(data, "#", &hashTagPosition);
        debugAssert(wasHashTagPositionFound);
        const char * dataPosition = IAString_toCharArray(data);
        dataPosition += hashTagPosition + 1;
        IAString temp;
        IAString_init(&temp, "");
        IAKeyValueHashMap_onKeyValueParsedState state = {.elements = elements, .dataPosition = dataPosition, .temp = &temp};
        IAKeyValueHashMap_isValidFormat(lengthOfData, dataStr, &state, (void (*)(void *, long, long)) IAKeyValueHashMap_onKeyValueParsed);
        IAString_deinit(&temp);
        return true;
    }
}

void IAKeyValueHashMap_onKeyValueParsed(IAKeyValueHashMap_onKeyValueParsedState * state, long keyLength, long valueLength){
    char key[keyLength + 1];
    memcpy(key, state->dataPosition, keyLength);
    key[keyLength] = '\0';
    state->dataPosition += keyLength;
    IAString_setWithLength(state->temp, state->dataPosition, valueLength);
    state->dataPosition += valueLength;
    IAKeyValueElement * delegate = IAHashMap_get(state->elements, key);
    if (delegate != NULL) {
        IAKeyValueElement_applyStringToValue(delegate, state->temp);
    }
}

void IAKeyValueHashMap_save(const IAHashMap * elements, IAString * data){
    IAString_set(data, "");
    
    IAString keysAndValues;
    IAString_init(&keysAndValues, "");
    
    IAHashMapIterator iterator;
    IAHashMapIterator_makeIteratorOverKeys(&iterator, elements);
    char * key;
    IAString temp;
    IAString_init(&temp, "");
    while ((key = IAHashMapIterator_getNextObject(&iterator)) != NULL) {
        IAKeyValueElement * delegate = IAHashMap_get(elements, key);
        if (IAKeyValueElement_shouldSave(delegate) == true) {
            //key
            IAString_concatLong(data, strlen(key));
            IAString_concat(data, "-");
            IAString_concat(&keysAndValues, key);
            
            //value
            IAString_set(&temp, "");
            IAKeyValueElement_setString(delegate, &temp);
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


