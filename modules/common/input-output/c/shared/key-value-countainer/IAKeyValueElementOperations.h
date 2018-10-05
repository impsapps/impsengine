#ifndef IAKeyValueElementOperations_h
#define IAKeyValueElementOperations_h

#include "IAString.h"

void IAKeyValueElementOperations_applyStringToInt(int * i, IAString * string);
void IAKeyValueElementOperations_setStringWithInt(int * i, IAString * string);

void IAKeyValueElementOperations_applyStringToUInt64(uint64_t * i, IAString * string);
void IAKeyValueElementOperations_setStringWithUInt64(uint64_t * i, IAString * string);

void IAKeyValueElementOperations_applyStringToLong(long * l, IAString * string);
void IAKeyValueElementOperations_setStringWithLong(long * l, IAString * string);

void IAKeyValueElementOperations_applyStringToFloat(float * f, IAString * string);
void IAKeyValueElementOperations_setStringWithFloat(float * f, IAString * string);

void IAKeyValueElementOperations_applyStringToDouble(double * d, IAString * string);
void IAKeyValueElementOperations_setStringWithDouble(double * d, IAString * string);

void IAKeyValueElementOperations_applyStringToBool(bool * b, IAString * string);
void IAKeyValueElementOperations_setStringWithBool(bool * b, IAString * string);

void IAKeyValueElementOperations_applyStringToString(IAString * str, IAString * string);
void IAKeyValueElementOperations_setStringWithString(IAString * str, IAString * string);

#endif
