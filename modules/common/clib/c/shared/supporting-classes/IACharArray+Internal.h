#ifndef IACharArray_Internal_h
#define IACharArray_Internal_h

#include <stdint.h>

void IACharArray_setIntWithLength(char *, int i, size_t length);
void IACharArray_setLongWithLength(char *, long i, size_t length);
void IACharArray_setUInt64WithLength(char *, uint64_t i, size_t length);
void IACharArray_setDoubleWithLengthAndNullTermination(char *, double d, size_t length);

#endif
