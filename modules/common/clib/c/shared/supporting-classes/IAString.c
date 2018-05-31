//
//  IAString.c
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 25.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#include "IALibrary.h"
#include "IAString.h"
#include "IAArrayList.h"
#include "IACharArray.h"
#include "IACharArray+Internal.h"
#include <stdlib.h>
#include <stdarg.h>

#define CLASSNAME "IAString"


void IAString_applyMinArraySizeThrowingAssertIfNeeded(IAString * this, size_t minArraySize);
void IAString_initCharArrayWithMinArraySize(IAString * this, size_t minArraySize);
void IAString_applyMinArraySize(IAString * this, size_t minArraySize);

void IAString_writeIntIntoString(IAString * this, int i, size_t length);
void IAString_writeLongIntoString(IAString * this, long l, size_t length);
void IAString_writeUInt64IntoString(IAString * this, uint64_t i, size_t length);
void IAString_writeDoubleIntoString(IAString * this, double d, size_t length);
void IAString_writeBoolIntoString(IAString * this, bool b, size_t length);
void IAString_writeCharArrayIntoString(IAString * this, const char * c, size_t length);

bool IAString_matchesPattern(const char * string, const char * pattern);


void IAString_applyMinArraySizeThrowingAssertIfNeeded(IAString * this, size_t minArraySize){
    if (minArraySize > this->arraySize){
        assert(0 && "Cannot enlarge buffer size of string. Did you initialize this string with your own buffer?");
    }
}

void IAString_init(IAString * this, const char * c){
    if (c == NULL) {
        c = "";
    }
    size_t length = strlen(c);
    IAString_initCharArrayWithMinArraySize(this, length);
    IAString_writeCharArrayIntoString(this, (char *) c, length);
}

void IAString_initWithLength(IAString * this, const char * c, size_t length){
    IAString_initCharArrayWithMinArraySize(this, length);
    IAString_writeCharArrayIntoString(this, c, length);
}

void IAString_initWithInt(IAString * this, int i){
    size_t length = IACharArray_lengthOfInt(i);
    IAString_initCharArrayWithMinArraySize(this, length);
    IAString_writeIntIntoString(this, i, length);
}

void IAString_initWithLong(IAString * this, long l){
    size_t length = IACharArray_lengthOfLong(l);
    IAString_initCharArrayWithMinArraySize(this, length);
    IAString_writeLongIntoString(this, l, length);
}

void IAString_initWithUInt64(IAString * this, uint64_t i){
    size_t length = IACharArray_lengthOfUInt64(i);
    IAString_initCharArrayWithMinArraySize(this, length);
    IAString_writeUInt64IntoString(this, i, length);
}

void IAString_initWithDouble(IAString * this, double d){
    IAString_initWithFormat(this, "%f", d);
}

void IAString_initWithBool(IAString * this, bool b){
    size_t length = IACharArray_lengthOfBool(b);
    IAString_initCharArrayWithMinArraySize(this, length);
    IAString_writeBoolIntoString(this, b, length);
}

void IAString_initWithFormat(IAString * this, const char * format, ...){
    va_list args;
    va_start(args, format);
    size_t length = vsnprintf(NULL, 0, format, args);
    IAString_initCharArrayWithMinArraySize(this, length);
    va_end (args);
    va_start(args, format);
    vsnprintf(this->c, length + 1, format, args);
    va_end (args);
    this->length = length;
}

IAString * IAString_newWithFormat(const char * format, ...){
    IAString * this = IA_malloc(sizeof(IAString));
    va_list args;
    va_start(args, format);
    size_t length = vsnprintf(NULL, 0, format, args);
    IAString_initCharArrayWithMinArraySize(this, length);
    va_end (args);
    va_start(args, format);
    vsnprintf(this->c, length + 1, format, args);
    va_end (args);
    this->length = length;
    return this;
}

void IAString_initCopy(IAString * this, const IAString * stringToCopy){
    IAString_initWithLength(this, stringToCopy->c, stringToCopy->length);
}

void IAString_initCharArrayWithMinArraySize(IAString * this, size_t minArraySize){
    this->c = IA_malloc(sizeof(char) * (minArraySize * 2 + 1));
    this->arraySize = minArraySize * 2;
}

void IAString_applyMinArraySize(IAString * this, size_t minArraySize){
    if (minArraySize > this->arraySize){
        this->c = IA_realloc(this->c, sizeof(char) * (minArraySize * 2 + 1));
        this->arraySize = minArraySize * 2;
    }
}

void IAString_writeIntIntoString(IAString * this, int i, size_t length){
    IACharArray_setIntWithLength(this->c, i, length);
    this->c[length] = '\0';
    this->length = length;
}

void IAString_writeLongIntoString(IAString * this, long l, size_t length){
    IACharArray_setLongWithLength(this->c, l, length);
    this->c[length] = '\0';
    this->length = length;
}

void IAString_writeUInt64IntoString(IAString * this, uint64_t i, size_t length){
    IACharArray_setUInt64WithLength(this->c, i, length);
    this->c[length] = '\0';
    this->length = length;
}

void IAString_writeDoubleIntoString(IAString * this, double d, size_t length){
    IACharArray_setDoubleWithLengthAndNullTermination(this->c, d, length + 1);
    this->length = length;
}

void IAString_writeBoolIntoString(IAString * this, bool b, size_t length){
    IACharArray_setBool(this->c, b);
    this->length = length;
}

void IAString_writeCharArrayIntoString(IAString * this, const char * c, size_t length){
    memcpy(this->c, c, length);
    this->c[length] = '\0';
    this->length = length;
}

void IAString_set(IAString * this, const char * c){
    size_t newLength = strlen(c);
    IAString_applyMinArraySize(this, newLength);
    IAString_writeCharArrayIntoString(this, c, newLength);
}

void IAString_setWithLength(IAString * this, const char * c, size_t length){
    IAString_applyMinArraySize(this, length);
    IAString_writeCharArrayIntoString(this, c, length);
}

void IAString_setInt(IAString * this, int i){
    size_t newLength = IACharArray_lengthOfInt(i);
    IAString_applyMinArraySize(this, newLength);
    IAString_writeIntIntoString(this, i, newLength);
}

void IAString_setLong(IAString * this, long l){
    size_t newLength = IACharArray_lengthOfLong(l);
    IAString_applyMinArraySize(this, newLength);
    IAString_writeLongIntoString(this, l, newLength);
}

void IAString_setUInt64(IAString * this, uint64_t i){
    size_t newLength = IACharArray_lengthOfUInt64(i);
    IAString_applyMinArraySize(this, newLength);
    IAString_writeUInt64IntoString(this, i, newLength);
}

void IAString_setDouble(IAString * this, double d){
    IAString_setWithFormat(this, "%f", d);
}

void IAString_setBool(IAString * this, bool b){
    size_t newLength = IACharArray_lengthOfBool(b);
    IAString_applyMinArraySize(this, newLength);
    IAString_writeBoolIntoString(this, b, newLength);
}

void IAString_setString(IAString * this, const IAString * str){
    IAString_set(this, IAString_toCharArray(str));
}

void IAString_setWithFormat(IAString * this, const char * format, ...){
    va_list args;
    va_start(args, format);
    size_t length = vsnprintf(NULL, 0, format, args);
    IAString_applyMinArraySize(this, length);
    va_end (args);
    va_start(args, format);
    vsnprintf(this->c, length + 1, format, args);
    va_end (args);
    this->length = length;
}

void IAString_setCharAtIndex(IAString * this, char c, size_t index){
    this->c[index] = c;
}

const char * IAString_toCharArray(const IAString * this){
    return this->c;
}

int IAString_toInt(const IAString * this){
    return IACharArray_toInt(this->c);
}

long IAString_toLong(const IAString * this){
    return IACharArray_toLong(this->c);
}

uint64_t IAString_toUInt64(const IAString * this){
    return IACharArray_toUInt64(this->c);
}

double IAString_toDouble(const IAString * this){
    return IACharArray_toDouble(this->c);
}

bool IAString_toBool(const IAString * this){
    return IACharArray_toBool(this->c);
}

char IAString_charAtIndex(const IAString * this, size_t index){
    return this->c[index];
}

char IAString_lastChar(const IAString * this){
    if(this->length == 0){
        return '\0';
    }else{
        return this->c[this->length - 1];
    }
}

void IAString_firstUpperCase(IAString * this){
    IACharArray_firstUpperCase(this->c);
}

void IAString_upperCase(IAString * this){
    IACharArray_upperCase(this->c);
}

void IAString_firstLowerCase(IAString * this){
    IACharArray_firstLowerCase(this->c);
}

void IAString_lowerCase(IAString * this){
    IACharArray_lowerCase(this->c);
}

void IAString_concat(IAString * this, const char * c){
    IAString_concatWithLength(this, c, strlen(c));
}

void IAString_concatWithLength(IAString * this, const char * c, size_t length){
    debugAssert(this->c != c && "Concatenation must be different");
    if (this->length + length <= this->arraySize){
        memcpy(this->c + this->length, c, length);
        this->c[length + this->length] = '\0';
        this->length += length;
    }
    else{
        char backup[this->length];
        memcpy(backup, this->c, sizeof(char) * this->length);
        size_t newLength = this->length + length;
        IAString_applyMinArraySize(this, newLength);
        memcpy(this->c, backup, sizeof(char) * this->length);
        memcpy(this->c + this->length, c, sizeof(char) * length);
        this->c[newLength] = '\0';
        this->length = newLength;
    }
}

void IAString_concatInt(IAString * this, int i){
    size_t length = IACharArray_lengthOfInt(i);
    char temp[length];
    IACharArray_setIntWithLength(temp, i, length);
    IAString_concatWithLength(this, temp, length);
}

void IAString_concatLong(IAString * this, long l){
    size_t length = IACharArray_lengthOfLong(l);
    char temp[length];
    IACharArray_setLongWithLength(temp, l, length);
    IAString_concatWithLength(this, temp, length);
}

void IAString_concatUInt64(IAString * this, uint64_t i){
    size_t length = IACharArray_lengthOfUInt64(i);
    char temp[length];
    IACharArray_setUInt64WithLength(temp, i, length);
    IAString_concatWithLength(this, temp, length);
}

void IAString_concatDouble(IAString * this, double d){
    size_t length = IACharArray_lengthOfDouble(d);
    char temp[length + 1];
    IACharArray_setDoubleWithLengthAndNullTermination(temp, d, length + 1);
    IAString_concatWithLength(this, temp, length);
}

void IAString_concatBool(IAString * this, bool b){
    size_t length = IACharArray_lengthOfBool(b);
    char temp[length + 1];
    IACharArray_setBool(temp, b);
    IAString_concatWithLength(this, temp, length);
}

void IAString_concatString(IAString * this, const IAString * stringExtension){
    if (this == stringExtension) {
        char concatenation[stringExtension->length];
        memcpy(concatenation, stringExtension->c, stringExtension->length);
        IAString_concatWithLength(this, concatenation, stringExtension->length);
    }else{
        IAString_concatWithLength(this, stringExtension->c, stringExtension->length);
    }
}

void IAString_concatWithFormat(IAString * this, const char * format, ...){
    va_list args;
    va_start(args, format);
    size_t length = vsnprintf(NULL, 0, format, args);
    va_end (args);
    char temp[length+1];
    va_start(args, format);
    vsnprintf(temp, length + 1, format, args);
    va_end (args);
    IAString_concatWithLength(this, temp, length);
}

void IAString_substring(IAString * this, size_t newLength){
    if (newLength > IAString_getLength(this)) {
        logError("substring: newLength is greater than current length");
    }
    this->length = newLength;
    this->c[newLength] = '\0';
}

void IAString_substringWithStartingIndex(IAString * this, size_t startingIndex, size_t newLength){
    char * c = this->c;
    for (size_t i = 0; i < newLength; i++) {
        c[i] = c[i+startingIndex];
    }
    c[newLength] = '\0';
    this->length = newLength;
}

void IAString_substringWithStartingIndexTillEnd(IAString * this, size_t startingIndex){
    IAString_substringWithStartingIndex(this, startingIndex, this->length - startingIndex);
}

void IAString_remove(IAString * this, size_t startingIndex, size_t length){
    debugAssert(this->length >= startingIndex + length);
    char * c = this->c;
    size_t newLength = this->length - length;
    for (size_t i = startingIndex; i < newLength; i++) {
        c[i] = c[i+length];
    }
    c[newLength] = '\0';
    this->length = newLength;
}

void IAString_removeLast(IAString * this){
    debugAssert(this->length > 0);
    this->length--;
    this->c[this->length] = '\0';
}

void IAString_removeNewLinesAtEnd(IAString * this){
    while(IAString_getLength(this) > 0){
        char lastChar = IAString_lastChar(this);
        if (lastChar == '\n' || lastChar == '\r'){
            IAString_removeLast(this);
        }else{
            break;
        }
    }
}

IAString * IAString_createSubstring(const IAString * this, size_t startIndex, size_t length){
    if (startIndex + length > IAString_getLength(this)) {
        length = IAString_getLength(this) - startIndex;
    }
    return IAString_newWithLength(this->c+startIndex, length);
}

IAArrayList * IAString_createSplit(const IAString * this, const char * pattern){
    size_t lengthOfPattern = strlen(pattern);
    
    IAArrayList * list = IAArrayList_new(8);
    
    const char * current = IAString_toCharArray(this);
    const char * last = current;
    size_t length = 0;
    
    while (*current != '\0') {
        if (IAString_matchesPattern(current, pattern)) {
            IAString * newString = IAString_newWithLength(last, length);
            IAArrayList_add(list, newString);
            length = 0;
            current+=lengthOfPattern;
            last = current;
        }else{
            length++;
            current++;
        }
    }
    
    IAString * newString = IAString_newWithLength(last, length);
    IAArrayList_add(list, newString);
    
    return list;
}

bool IAString_getIndexOfFirstPatternMatch(const IAString * this, const char * pattern, size_t * indexOut){
    const char * current = IAString_toCharArray(this);
    size_t index = 0;
    while (*current != '\0') {
        if (IAString_matchesPattern(current, pattern)) {
            *indexOut = index;
            return true;
        }else{
            index++;
            current++;
        }
    }
    return false;
}

bool IAString_getIndexOfSecondPatternMatch(const IAString * this, const char * pattern, size_t * indexOut){
    size_t skip = 1;
    const char * current = IAString_toCharArray(this);
    size_t index = 0;
    while (*current != '\0') {
        if (IAString_matchesPattern(current, pattern)) {
            if (skip == 0) {
                *indexOut = index;
                return true;
            }else{
                skip--;
            }
        }
        index++;
        current++;
    }
    return false;
}

bool IAString_getIndexOfLastPatternMatch(const IAString * this, const char * pattern, size_t * indexOut){
    const char * current = IAString_toCharArray(this);
    
    for (size_t index = this->length; index > 0;) {
        index--;
        if (IAString_matchesPattern(current + index, pattern)) {
            *indexOut = index;
            return true;
        }
    }
    return false;
}

bool IAString_contains(const IAString * this, const char * pattern){
    size_t index;
    bool wasIndexFound = IAString_getIndexOfFirstPatternMatch(this, pattern, &index);
    return wasIndexFound;
}

bool IAString_matchesPattern(const char * this, const char * pattern){
    size_t position = 0;
    while (pattern[position] != '\0' && pattern[position] == this[position]) {
        position ++;
    }
    if (pattern[position] == '\0') {
        return true;
    }else{
        return false;
    }
    
}


int IAString_compare(const IAString * this, const IAString * str){
    for (int i = 0; i < this->length && i < str->length; i++) {
        if (this->c[i] > str->c[i]) {
            return 1;
        }else if(this->c[i] < str->c[i]){
            return -1;
        }
    }
    if (this->length == str->length) {
        return 0;
    }else if(this->length < str->length){
        return -1;
    }else{
        return 1;
    }
}

int IAString_compareToChar(const IAString * this, const char * c){
    int result = strcmp(this->c, c);
    if (result > 0) {
        return 1;
    }else if (result < 0){
        return -1;
    }else{
        return 0;
    }
}

bool IAString_isNumberFormat(const IAString * this){
    return IACharArray_isNumberFormat(this->c);
}

bool IAString_isEmpty(const IAString * this){
    return IACharArray_isEmpty(this->c);
}

bool IAString_isEqual(const IAString * this, const IAString * str){
    if (IAString_compare(this, str) == 0) {
        return true;
    }else{
        return false;
    }
}

bool IAString_isEqualToCharArray(const IAString * this, const char * c){
    return IACharArray_areEqual(this->c, c);
}

void IAString_deinit(IAString * this){
    IA_free(this->c);
}
