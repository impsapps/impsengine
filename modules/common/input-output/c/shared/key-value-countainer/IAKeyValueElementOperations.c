#include "IALibrary.h"
#include "IAKeyValueElementOperations.h"

#define CLASSNAME "IAKeyValueElementOperations"

void IAKeyValueElementOperations_applyStringToInt(int * i, IAString * string){
    *i = IAString_toInt(string);
}

void IAKeyValueElementOperations_setStringWithInt(int * i, IAString * string){
    IAString_setInt(string, *i);
}

void IAKeyValueElementOperations_applyStringToUInt64(uint64_t * i, IAString * string){
    *i = IAString_toUInt64(string);
}

void IAKeyValueElementOperations_setStringWithUInt64(uint64_t * i, IAString * string){
    IAString_setUInt64(string, *i);
}

void IAKeyValueElementOperations_applyStringToLong(long * l, IAString * string){
    *l = IAString_toLong(string);
}

void IAKeyValueElementOperations_setStringWithLong(long * l, IAString * string){
    IAString_setLong(string, *l);
}

void IAKeyValueElementOperations_applyStringToFloat(float * f, IAString * string){
    *f = (float) IAString_toDouble(string);
}

void IAKeyValueElementOperations_setStringWithFloat(float * f, IAString * string){
    IAString_setDouble(string, *f);
}

void IAKeyValueElementOperations_applyStringToDouble(double * d, IAString * string){
    *d = IAString_toDouble(string);
}

void IAKeyValueElementOperations_setStringWithDouble(double * d, IAString * string){
    IAString_setDouble(string, *d);
}

void IAKeyValueElementOperations_applyStringToBool(bool * b, IAString * string){
    *b = IAString_toBool(string);
}

void IAKeyValueElementOperations_setStringWithBool(bool * b, IAString * string){
    IAString_setBool(string, *b);
}

void IAKeyValueElementOperations_applyStringToString(IAString * str, IAString * string){
    IAString_setString(str, string);
}

void IAKeyValueElementOperations_setStringWithString(IAString * str, IAString * string){
    IAString_setString(string, str);
}

