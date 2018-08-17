//
//  IACharArray+Internal.h
//  CLib
//
//  Created by Konstantin Merker on 04.04.18.
//  Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IACharArray_Internal_h
#define IACharArray_Internal_h

#include <stdint.h>

void IACharArray_setIntWithLength(char *, int i, size_t length);
void IACharArray_setLongWithLength(char *, long i, size_t length);
void IACharArray_setUInt64WithLength(char *, uint64_t i, size_t length);
void IACharArray_setDoubleWithLengthAndNullTermination(char *, double d, size_t length);

#endif
