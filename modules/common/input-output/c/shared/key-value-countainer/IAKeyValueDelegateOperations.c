//
//  IAKeyValueDelegateOperations.c
//  Hit Verto
//
//  Created by Konstantin Merker on 05/01/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAKeyValueDelegateOperations.h"

#define CLASSNAME "IAKeyValueDelegateOperations"

void IAKeyValueDelegateOperations_applyStringToInt(int * i, IAString * string){
    *i = IAString_toInt(string);
}

void IAKeyValueDelegateOperations_setStringWithInt(int * i, IAString * string){
    IAString_setInt(string, *i);
}

void IAKeyValueDelegateOperations_applyStringToUInt64(uint64_t * i, IAString * string){
    *i = IAString_toUInt64(string);
}

void IAKeyValueDelegateOperations_setStringWithUInt64(uint64_t * i, IAString * string){
    IAString_setUInt64(string, *i);
}

void IAKeyValueDelegateOperations_applyStringToLong(long * l, IAString * string){
    *l = IAString_toLong(string);
}

void IAKeyValueDelegateOperations_setStringWithLong(long * l, IAString * string){
    IAString_setLong(string, *l);
}

void IAKeyValueDelegateOperations_applyStringToFloat(float * f, IAString * string){
    *f = (float) IAString_toDouble(string);
}

void IAKeyValueDelegateOperations_setStringWithFloat(float * f, IAString * string){
    IAString_setDouble(string, *f);
}

void IAKeyValueDelegateOperations_applyStringToDouble(double * d, IAString * string){
    *d = IAString_toDouble(string);
}

void IAKeyValueDelegateOperations_setStringWithDouble(double * d, IAString * string){
    IAString_setDouble(string, *d);
}

void IAKeyValueDelegateOperations_applyStringToBool(bool * b, IAString * string){
    *b = IAString_toBool(string);
}

void IAKeyValueDelegateOperations_setStringWithBool(bool * b, IAString * string){
    IAString_setBool(string, *b);
}

void IAKeyValueDelegateOperations_applyStringToString(IAString * str, IAString * string){
    IAString_setString(str, string);
}

void IAKeyValueDelegateOperations_setStringWithString(IAString * str, IAString * string){
    IAString_setString(string, str);
}

