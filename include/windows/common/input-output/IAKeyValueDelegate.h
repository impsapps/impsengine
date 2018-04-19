//
//  IAKeyValueDelegate.h
//  Hit Verto
//
//  Created by Konstantin Merker on 05/01/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAKeyValueDelegate_h
#define Hit_Verto_IAKeyValueDelegate_h

#include "IAString.h"
#include "IAKeyValueDelegateAttributes.h"

typedef struct{
    void * value;
    //@exe
    void (*applyStringToValue)(void * value, IAString * string);
    //@exe
    void (*setString)(void * value, IAString * string);
    const bool * shouldSave;
} IAKeyValueDelegate;


void IAKeyValueDelegate_make(IAKeyValueDelegate *, const IAKeyValueDelegateAttributes * attributes);
void IAKeyValueDelegate_makeWithInt(IAKeyValueDelegate *, int * i);
void IAKeyValueDelegate_makeWithIntAndShouldSaveRef(IAKeyValueDelegate *, int * i, const bool * shouldSave);
void IAKeyValueDelegate_makeWithUInt64(IAKeyValueDelegate *, uint64_t * i);
void IAKeyValueDelegate_makeWithUInt64AndShouldSaveRef(IAKeyValueDelegate *, uint64_t * i, const bool * shouldSave);
void IAKeyValueDelegate_makeWithLong(IAKeyValueDelegate *, long * l);
void IAKeyValueDelegate_makeWithLongAndShouldSaveRef(IAKeyValueDelegate *, long * l, const bool * shouldSave);
void IAKeyValueDelegate_makeWithFloat(IAKeyValueDelegate *, float * f);
void IAKeyValueDelegate_makeWithFloatAndShouldSaveRef(IAKeyValueDelegate *, float * f, const bool * shouldSave);
void IAKeyValueDelegate_makeWithDouble(IAKeyValueDelegate *, double * d);
void IAKeyValueDelegate_makeWithDoubleAndShouldSaveRef(IAKeyValueDelegate *, double * d, const bool * shouldSave);
void IAKeyValueDelegate_makeWithBool(IAKeyValueDelegate *, bool * b);
void IAKeyValueDelegate_makeWithBoolAndShouldSaveRef(IAKeyValueDelegate *, bool * b, const bool * shouldSave);
void IAKeyValueDelegate_makeWithString(IAKeyValueDelegate *, IAString * str);
void IAKeyValueDelegate_makeWithStringAndShouldSaveRef(IAKeyValueDelegate *, IAString * str, const bool * shouldSave);

bool IAKeyValueDelegate_shouldSave(IAKeyValueDelegate *);

#include "IAKeyValueDelegate+Generated.h"

#endif
