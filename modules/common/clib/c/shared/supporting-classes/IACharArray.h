#ifndef IACharArray_h
#define IACharArray_h

#include <stdbool.h>
#include <string.h>
#include <stdint.h>


// these macros include null termination

#define IA_MAX_BUFFER_INT 21
#define IA_MAX_BUFFER_LONG 21
#define IA_MAX_BUFFER_UINT64 21


// these functions do not include null termination

size_t IACharArray_lengthOfInt(int i);
size_t IACharArray_lengthOfLong(long l);
size_t IACharArray_lengthOfUInt64(uint64_t i);
size_t IACharArray_lengthOfDouble(double d);
size_t IACharArray_lengthOfBool(bool b);
size_t IACharArray_lengthOfStringWithFormat(const char * format, ...);

void IACharArray_set(char *, const char * str);
void IACharArray_setInt(char *, int i);
void IACharArray_setLong(char *, long l);
void IACharArray_setUInt64(char *, uint64_t i);
void IACharArray_setDouble(char *, double d);
void IACharArray_setBool(char *, bool b);
void IACharArray_setWithFormat(char *, const char * format, ...);

int IACharArray_toInt(const char *);
long IACharArray_toLong(const char *);
uint64_t IACharArray_toUInt64(const char *);
double IACharArray_toDouble(const char *);
bool IACharArray_toBool(const char *);

void IACharArray_firstUpperCase(char *);
void IACharArray_upperCase(char *);
void IACharArray_firstLowerCase(char *);
void IACharArray_lowerCase(char *);

void IACharArray_concat(char *, const char * str);
void IACharArray_concatInt(char *, int i);
void IACharArray_concatLong(char *, long l);
void IACharArray_concatUInt64(char *, uint64_t i);
void IACharArray_concatDouble(char *, double d);
void IACharArray_concatBool(char *, bool b);
void IACharArray_concatWithFormat(char *, const char * format, ...);

bool IACharArray_isNumberFormat(const char *);

bool IACharArray_isEmpty(const char *);
bool IACharArray_areEqual(const char *, const char *);

#endif
