//
//  IAKeyValueDelegateOperations.h
//  Hit Verto
//
//  Created by Konstantin Merker on 05/01/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAKeyValueDelegateOperations_h
#define Hit_Verto_IAKeyValueDelegateOperations_h

#include "IAString.h"

void IAKeyValueDelegateOperations_applyStringToInt(int * i, IAString * string);
void IAKeyValueDelegateOperations_setStringWithInt(int * i, IAString * string);

void IAKeyValueDelegateOperations_applyStringToUInt64(uint64_t * i, IAString * string);
void IAKeyValueDelegateOperations_setStringWithUInt64(uint64_t * i, IAString * string);

void IAKeyValueDelegateOperations_applyStringToLong(long * l, IAString * string);
void IAKeyValueDelegateOperations_setStringWithLong(long * l, IAString * string);

void IAKeyValueDelegateOperations_applyStringToFloat(float * f, IAString * string);
void IAKeyValueDelegateOperations_setStringWithFloat(float * f, IAString * string);

void IAKeyValueDelegateOperations_applyStringToDouble(double * d, IAString * string);
void IAKeyValueDelegateOperations_setStringWithDouble(double * d, IAString * string);

void IAKeyValueDelegateOperations_applyStringToBool(bool * b, IAString * string);
void IAKeyValueDelegateOperations_setStringWithBool(bool * b, IAString * string);

void IAKeyValueDelegateOperations_applyStringToString(IAString * str, IAString * string);
void IAKeyValueDelegateOperations_setStringWithString(IAString * str, IAString * string);

#endif
