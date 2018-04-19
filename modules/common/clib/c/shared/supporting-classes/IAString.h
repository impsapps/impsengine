//
//  IAString.h
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 25.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineCLibrary_IAString_h
#define ImpsEngineCLibrary_IAString_h


#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "IAArrayList.h"

/** 
 * A class to support string handling.
 *
 */


typedef struct IAString IAString;

struct IAString{
    char * c;
    //@get
    size_t length;
    size_t arraySize;
};


void IAString_init(IAString *, const char * c);
void IAString_initWithLength(IAString *, const char * c, size_t length);
void IAString_initWithInt(IAString *, int i);
void IAString_initWithLong(IAString *, long l);
void IAString_initWithUInt64(IAString *, uint64_t i);
void IAString_initWithDouble(IAString *, double d);
void IAString_initWithBool(IAString *, bool b);
void IAString_initWithFormat(IAString *, const char * format, ...);
IAString * IAString_newWithFormat(const char * format, ...);

void IAString_initCopy(IAString *, const IAString * stringToCopy);

void IAString_set(IAString *, const char * c);
void IAString_setWithLength(IAString *, const char * c, size_t length);
void IAString_setInt(IAString *, int i);
void IAString_setLong(IAString *, long l);
void IAString_setUInt64(IAString *, uint64_t i);
void IAString_setDouble(IAString *, double d);
void IAString_setBool(IAString *, bool b);
void IAString_setString(IAString *, const IAString * str);
void IAString_setWithFormat(IAString *, const char * format, ...);

void IAString_setCharAtIndex(IAString *, char c, size_t index);

const char * IAString_toCharArray(const IAString *);
int IAString_toInt(const IAString *);
long IAString_toLong(const IAString *);
uint64_t IAString_toUInt64(const IAString *);
double IAString_toDouble(const IAString *);
bool IAString_toBool(const IAString *);
char IAString_charAtIndex(const IAString *, size_t index);
char IAString_lastChar(const IAString *);

void IAString_firstUpperCase(IAString *);
void IAString_upperCase(IAString *);
void IAString_firstLowerCase(IAString *);
void IAString_lowerCase(IAString *);

void IAString_concat(IAString *, const char * c);
void IAString_concatWithLength(IAString * this, const char * c, size_t length);
void IAString_concatInt(IAString *, int i);
void IAString_concatLong(IAString *, long l);
void IAString_concatUInt64(IAString *, uint64_t i);
void IAString_concatDouble(IAString *, double d);

/**
 * \param b The boolean will be converted to '1' for true or '0' for false.
 */
void IAString_concatBool(IAString *, bool b);
void IAString_concatString(IAString *, IAString * stringExtension);
void IAString_concatWithFormat(IAString *, const char * format, ...);

void IAString_substring(IAString *, size_t newLength);
void IAString_substringWithStartingIndex(IAString *, size_t startingIndex, size_t newLength);
void IAString_substringWithStartingIndexTillEnd(IAString *, size_t startingIndex);
void IAString_remove(IAString *, size_t startingIndex, size_t length);
void IAString_removeLast(IAString *);
void IAString_removeNewLinesAtEnd(IAString *);

IAString * IAString_createSubstring(const IAString *, size_t startIndex, size_t length);
IAArrayList * IAString_createSplit(const IAString *, const char * pattern);

bool IAString_getIndexOfFirstPatternMatch(const IAString *, const char * pattern, size_t * indexOut);
bool IAString_getIndexOfSecondPatternMatch(const IAString *, const char * pattern, size_t * indexOut);
bool IAString_getIndexOfLastPatternMatch(const IAString *, const char * pattern, size_t * indexOut);

bool IAString_contains(const IAString *, const char * pattern);

//compare: 1 -> ascending, 0 -> equal, -1 -> descending
int IAString_compare(const IAString *, const IAString * str);

int IAString_compareToChar(const IAString *, const char * c);

bool IAString_isNumberFormat(const IAString *);

bool IAString_isEmpty(const IAString *);

bool IAString_isEqual(const IAString *, const IAString * str);
bool IAString_isEqualToCharArray(const IAString *, const char * c);

void IAString_deinit(IAString *);

#include "IAString+Generated.h"

#endif
