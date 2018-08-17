//
//  IAKeyValueElement.h
//  Hit Verto
//
//  Created by Konstantin Merker on 05/01/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAKeyValueElement_h
#define Hit_Verto_IAKeyValueElement_h

#include "IAString.h"
#include "IAKeyValueElementAttributes.h"

typedef struct{
    //@extend
    IAObject base;
    void * value;
    //@exe
    void (*applyStringToValue)(void * value, IAString * string);
    //@exe
    void (*setString)(void * value, IAString * string);
    const bool * shouldSave;
} IAKeyValueElement;


void IAKeyValueElement_make(IAKeyValueElement *, const IAKeyValueElementAttributes * attributes);
void IAKeyValueElement_makeWithInt(IAKeyValueElement *, int * i);
void IAKeyValueElement_makeWithIntAndShouldSaveRef(IAKeyValueElement *, int * i, const bool * shouldSave);
void IAKeyValueElement_makeWithUInt64(IAKeyValueElement *, uint64_t * i);
void IAKeyValueElement_makeWithUInt64AndShouldSaveRef(IAKeyValueElement *, uint64_t * i, const bool * shouldSave);
void IAKeyValueElement_makeWithLong(IAKeyValueElement *, long * l);
void IAKeyValueElement_makeWithLongAndShouldSaveRef(IAKeyValueElement *, long * l, const bool * shouldSave);
void IAKeyValueElement_makeWithFloat(IAKeyValueElement *, float * f);
void IAKeyValueElement_makeWithFloatAndShouldSaveRef(IAKeyValueElement *, float * f, const bool * shouldSave);
void IAKeyValueElement_makeWithDouble(IAKeyValueElement *, double * d);
void IAKeyValueElement_makeWithDoubleAndShouldSaveRef(IAKeyValueElement *, double * d, const bool * shouldSave);
void IAKeyValueElement_makeWithBool(IAKeyValueElement *, bool * b);
void IAKeyValueElement_makeWithBoolAndShouldSaveRef(IAKeyValueElement *, bool * b, const bool * shouldSave);
void IAKeyValueElement_makeWithString(IAKeyValueElement *, IAString * str);
void IAKeyValueElement_makeWithStringAndShouldSaveRef(IAKeyValueElement *, IAString * str, const bool * shouldSave);

bool IAKeyValueElement_shouldSave(IAKeyValueElement *);

#include "IAKeyValueElement+Generated.h"

#endif
