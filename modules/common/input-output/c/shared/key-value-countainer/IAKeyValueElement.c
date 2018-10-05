#include "IALibrary.h"
#include "IAKeyValueElement.h"
#include "IAKeyValueElementOperations.h"

#define CLASSNAME "IAKeyValueElement"


void IAKeyValueElement_make(IAKeyValueElement * this, const IAKeyValueElementAttributes * attributes){
    *this = (IAKeyValueElement){
        .base = IAObject_make(this),
        .value = IAKeyValueElementAttributes_getValue(attributes),
        .applyStringToValue = IAKeyValueElementAttributes_getApplyStringToValueFunction(attributes),
        .setString = IAKeyValueElementAttributes_getSetStringFunction(attributes),
        .shouldSave = IAKeyValueElementAttributes_shouldSave(attributes)
    };
}

void IAKeyValueElement_makeWithInt(IAKeyValueElement * this, int * i){
    IAKeyValueElementAttributes attributes;
    IAKeyValueElementAttributes_make(&attributes, i, (void (*)(void *, IAString *)) IAKeyValueElementOperations_applyStringToInt, (void (*)(void *, IAString *)) IAKeyValueElementOperations_setStringWithInt);
    IAKeyValueElement_make(this, &attributes);
}

void IAKeyValueElement_makeWithIntAndShouldSaveRef(IAKeyValueElement * this, int * i, const bool * shouldSave){
    IAKeyValueElementAttributes attributes;
    IAKeyValueElementAttributes_make(&attributes, i, (void (*)(void *, IAString *)) IAKeyValueElementOperations_applyStringToInt, (void (*)(void *, IAString *)) IAKeyValueElementOperations_setStringWithInt);
    IAKeyValueElementAttributes_setShouldSave(&attributes, shouldSave);
    IAKeyValueElement_make(this, &attributes);
}

void IAKeyValueElement_makeWithUInt64(IAKeyValueElement * this, uint64_t * i){
    IAKeyValueElementAttributes attributes;
    IAKeyValueElementAttributes_make(&attributes, i, (void (*)(void *, IAString *)) IAKeyValueElementOperations_applyStringToUInt64, (void (*)(void *, IAString *)) IAKeyValueElementOperations_setStringWithUInt64);
    IAKeyValueElement_make(this, &attributes);
}

void IAKeyValueElement_makeWithUInt64AndShouldSaveRef(IAKeyValueElement * this, uint64_t * i, const bool * shouldSave){
    IAKeyValueElementAttributes attributes;
    IAKeyValueElementAttributes_make(&attributes, i, (void (*)(void *, IAString *)) IAKeyValueElementOperations_applyStringToUInt64, (void (*)(void *, IAString *)) IAKeyValueElementOperations_setStringWithUInt64);
    IAKeyValueElementAttributes_setShouldSave(&attributes, shouldSave);
    IAKeyValueElement_make(this, &attributes);
}

void IAKeyValueElement_makeWithLong(IAKeyValueElement * this, long * l){
    IAKeyValueElementAttributes attributes;
    IAKeyValueElementAttributes_make(&attributes, l, (void (*)(void *, IAString *)) IAKeyValueElementOperations_applyStringToLong, (void (*)(void *, IAString *)) IAKeyValueElementOperations_setStringWithLong);
    IAKeyValueElement_make(this, &attributes);
}

void IAKeyValueElement_makeWithLongAndShouldSaveRef(IAKeyValueElement * this, long * l, const bool * shouldSave){
    IAKeyValueElementAttributes attributes;
    IAKeyValueElementAttributes_make(&attributes, l, (void (*)(void *, IAString *)) IAKeyValueElementOperations_applyStringToLong, (void (*)(void *, IAString *)) IAKeyValueElementOperations_setStringWithLong);
    IAKeyValueElementAttributes_setShouldSave(&attributes, shouldSave);
    IAKeyValueElement_make(this, &attributes);
}


void IAKeyValueElement_makeWithFloat(IAKeyValueElement * this, float * f){
    IAKeyValueElementAttributes attributes;
    IAKeyValueElementAttributes_make(&attributes, f, (void (*)(void *, IAString *)) IAKeyValueElementOperations_applyStringToFloat, (void (*)(void *, IAString *)) IAKeyValueElementOperations_setStringWithFloat);
    IAKeyValueElement_make(this, &attributes);
}

void IAKeyValueElement_makeWithFloatAndShouldSaveRef(IAKeyValueElement * this, float * f, const bool * shouldSave){
    IAKeyValueElementAttributes attributes;
    IAKeyValueElementAttributes_make(&attributes, f, (void (*)(void *, IAString *)) IAKeyValueElementOperations_applyStringToFloat, (void (*)(void *, IAString *)) IAKeyValueElementOperations_setStringWithFloat);
    IAKeyValueElementAttributes_setShouldSave(&attributes, shouldSave);
    IAKeyValueElement_make(this, &attributes);
}

void IAKeyValueElement_makeWithDouble(IAKeyValueElement * this, double * d){
    IAKeyValueElementAttributes attributes;
    IAKeyValueElementAttributes_make(&attributes, d, (void (*)(void *, IAString *)) IAKeyValueElementOperations_applyStringToDouble, (void (*)(void *, IAString *)) IAKeyValueElementOperations_setStringWithDouble);
    IAKeyValueElement_make(this, &attributes);
}

void IAKeyValueElement_makeWithDoubleAndShouldSaveRef(IAKeyValueElement * this, double * d, const bool * shouldSave){
    IAKeyValueElementAttributes attributes;
    IAKeyValueElementAttributes_make(&attributes, d, (void (*)(void *, IAString *)) IAKeyValueElementOperations_applyStringToDouble, (void (*)(void *, IAString *)) IAKeyValueElementOperations_setStringWithDouble);
    IAKeyValueElementAttributes_setShouldSave(&attributes, shouldSave);
    IAKeyValueElement_make(this, &attributes);
}

void IAKeyValueElement_makeWithBool(IAKeyValueElement * this, bool * b){
    IAKeyValueElementAttributes attributes;
    IAKeyValueElementAttributes_make(&attributes, b, (void (*)(void *, IAString *)) IAKeyValueElementOperations_applyStringToBool, (void (*)(void *, IAString *)) IAKeyValueElementOperations_setStringWithBool);
    IAKeyValueElement_make(this, &attributes);
}

void IAKeyValueElement_makeWithBoolAndShouldSaveRef(IAKeyValueElement * this, bool * b, const bool * shouldSave){
    IAKeyValueElementAttributes attributes;
    IAKeyValueElementAttributes_make(&attributes, b, (void (*)(void *, IAString *)) IAKeyValueElementOperations_applyStringToBool, (void (*)(void *, IAString *)) IAKeyValueElementOperations_setStringWithBool);
    IAKeyValueElementAttributes_setShouldSave(&attributes, shouldSave);
    IAKeyValueElement_make(this, &attributes);
}

void IAKeyValueElement_makeWithString(IAKeyValueElement * this, IAString * str){
    IAKeyValueElementAttributes attributes;
    IAKeyValueElementAttributes_make(&attributes, str, (void (*)(void *, IAString *)) IAKeyValueElementOperations_applyStringToString, (void (*)(void *, IAString *)) IAKeyValueElementOperations_setStringWithString);
    IAKeyValueElement_make(this, &attributes);
}

void IAKeyValueElement_makeWithStringAndShouldSaveRef(IAKeyValueElement * this, IAString * str, const bool * shouldSave){
    IAKeyValueElementAttributes attributes;
    IAKeyValueElementAttributes_make(&attributes, str, (void (*)(void *, IAString *)) IAKeyValueElementOperations_applyStringToString, (void (*)(void *, IAString *)) IAKeyValueElementOperations_setStringWithString);
    IAKeyValueElementAttributes_setShouldSave(&attributes, shouldSave);
    IAKeyValueElement_make(this, &attributes);
}

bool IAKeyValueElement_shouldSave(IAKeyValueElement * this){
    return *this->shouldSave;
}


