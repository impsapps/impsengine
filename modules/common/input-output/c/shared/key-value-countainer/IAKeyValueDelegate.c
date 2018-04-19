//
//  IAKeyValueDelegate.c
//  Hit Verto
//
//  Created by Konstantin Merker on 05/01/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAKeyValueDelegate.h"
#include "IAKeyValueDelegateOperations.h"

#define CLASSNAME "IAKeyValueDelegate"


void IAKeyValueDelegate_make(IAKeyValueDelegate * this, const IAKeyValueDelegateAttributes * attributes){
    *this = (IAKeyValueDelegate){
        .value = IAKeyValueDelegateAttributes_getValue(attributes),
        .applyStringToValue = IAKeyValueDelegateAttributes_getApplyStringToValueFunction(attributes),
        .setString = IAKeyValueDelegateAttributes_getSetStringFunction(attributes),
        .shouldSave = IAKeyValueDelegateAttributes_shouldSave(attributes)
    };
}

void IAKeyValueDelegate_makeWithInt(IAKeyValueDelegate * this, int * i){
    IAKeyValueDelegateAttributes attributes;
    IAKeyValueDelegateAttributes_make(&attributes, i, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_applyStringToInt, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_setStringWithInt);
    IAKeyValueDelegate_make(this, &attributes);
}

void IAKeyValueDelegate_makeWithIntAndShouldSaveRef(IAKeyValueDelegate * this, int * i, const bool * shouldSave){
    IAKeyValueDelegateAttributes attributes;
    IAKeyValueDelegateAttributes_make(&attributes, i, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_applyStringToInt, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_setStringWithInt);
    IAKeyValueDelegateAttributes_setShouldSave(&attributes, shouldSave);
    IAKeyValueDelegate_make(this, &attributes);
}

void IAKeyValueDelegate_makeWithUInt64(IAKeyValueDelegate * this, uint64_t * i){
    IAKeyValueDelegateAttributes attributes;
    IAKeyValueDelegateAttributes_make(&attributes, i, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_applyStringToUInt64, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_setStringWithUInt64);
    IAKeyValueDelegate_make(this, &attributes);
}

void IAKeyValueDelegate_makeWithUInt64AndShouldSaveRef(IAKeyValueDelegate * this, uint64_t * i, const bool * shouldSave){
    IAKeyValueDelegateAttributes attributes;
    IAKeyValueDelegateAttributes_make(&attributes, i, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_applyStringToUInt64, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_setStringWithUInt64);
    IAKeyValueDelegateAttributes_setShouldSave(&attributes, shouldSave);
    IAKeyValueDelegate_make(this, &attributes);
}

void IAKeyValueDelegate_makeWithLong(IAKeyValueDelegate * this, long * l){
    IAKeyValueDelegateAttributes attributes;
    IAKeyValueDelegateAttributes_make(&attributes, l, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_applyStringToLong, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_setStringWithLong);
    IAKeyValueDelegate_make(this, &attributes);
}

void IAKeyValueDelegate_makeWithLongAndShouldSaveRef(IAKeyValueDelegate * this, long * l, const bool * shouldSave){
    IAKeyValueDelegateAttributes attributes;
    IAKeyValueDelegateAttributes_make(&attributes, l, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_applyStringToLong, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_setStringWithLong);
    IAKeyValueDelegateAttributes_setShouldSave(&attributes, shouldSave);
    IAKeyValueDelegate_make(this, &attributes);
}


void IAKeyValueDelegate_makeWithFloat(IAKeyValueDelegate * this, float * f){
    IAKeyValueDelegateAttributes attributes;
    IAKeyValueDelegateAttributes_make(&attributes, f, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_applyStringToFloat, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_setStringWithFloat);
    IAKeyValueDelegate_make(this, &attributes);
}

void IAKeyValueDelegate_makeWithFloatAndShouldSaveRef(IAKeyValueDelegate * this, float * f, const bool * shouldSave){
    IAKeyValueDelegateAttributes attributes;
    IAKeyValueDelegateAttributes_make(&attributes, f, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_applyStringToFloat, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_setStringWithFloat);
    IAKeyValueDelegateAttributes_setShouldSave(&attributes, shouldSave);
    IAKeyValueDelegate_make(this, &attributes);
}

void IAKeyValueDelegate_makeWithDouble(IAKeyValueDelegate * this, double * d){
    IAKeyValueDelegateAttributes attributes;
    IAKeyValueDelegateAttributes_make(&attributes, d, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_applyStringToDouble, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_setStringWithDouble);
    IAKeyValueDelegate_make(this, &attributes);
}

void IAKeyValueDelegate_makeWithDoubleAndShouldSaveRef(IAKeyValueDelegate * this, double * d, const bool * shouldSave){
    IAKeyValueDelegateAttributes attributes;
    IAKeyValueDelegateAttributes_make(&attributes, d, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_applyStringToDouble, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_setStringWithDouble);
    IAKeyValueDelegateAttributes_setShouldSave(&attributes, shouldSave);
    IAKeyValueDelegate_make(this, &attributes);
}

void IAKeyValueDelegate_makeWithBool(IAKeyValueDelegate * this, bool * b){
    IAKeyValueDelegateAttributes attributes;
    IAKeyValueDelegateAttributes_make(&attributes, b, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_applyStringToBool, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_setStringWithBool);
    IAKeyValueDelegate_make(this, &attributes);
}

void IAKeyValueDelegate_makeWithBoolAndShouldSaveRef(IAKeyValueDelegate * this, bool * b, const bool * shouldSave){
    IAKeyValueDelegateAttributes attributes;
    IAKeyValueDelegateAttributes_make(&attributes, b, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_applyStringToBool, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_setStringWithBool);
    IAKeyValueDelegateAttributes_setShouldSave(&attributes, shouldSave);
    IAKeyValueDelegate_make(this, &attributes);
}

void IAKeyValueDelegate_makeWithString(IAKeyValueDelegate * this, IAString * str){
    IAKeyValueDelegateAttributes attributes;
    IAKeyValueDelegateAttributes_make(&attributes, str, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_applyStringToString, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_setStringWithString);
    IAKeyValueDelegate_make(this, &attributes);
}

void IAKeyValueDelegate_makeWithStringAndShouldSaveRef(IAKeyValueDelegate * this, IAString * str, const bool * shouldSave){
    IAKeyValueDelegateAttributes attributes;
    IAKeyValueDelegateAttributes_make(&attributes, str, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_applyStringToString, (void (*)(void *, IAString *)) IAKeyValueDelegateOperations_setStringWithString);
    IAKeyValueDelegateAttributes_setShouldSave(&attributes, shouldSave);
    IAKeyValueDelegate_make(this, &attributes);
}

bool IAKeyValueDelegate_shouldSave(IAKeyValueDelegate * this){
    return *this->shouldSave;
}


