//
//  IACharArray.c
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 04.04.18.
//  Copyright (c) 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#include "IALibrary.h"
#include "IACharArray.h"
#include "IACharArray+Internal.h"
#include <stdlib.h>
#include <stdarg.h>

#define CLASSNAME "IACharArray"


size_t IACharArray_lengthOfInt(int i){
    size_t length = 1;
    if (i < 0) {
        length ++;
        i *= -1;
    }
    while (i > 9){
        length++;
        i /= 10;
    }
    return length;
}

size_t IACharArray_lengthOfLong(long l){
    size_t length = 1;
    if (l < 0) {
        length ++;
        l *= -1;
    }
    while (l > 9){
        length++;
        l /= 10;
    }
    return length;
}

size_t IACharArray_lengthOfUInt64(uint64_t i){
    size_t length = 1;
    while (i > 9){
        length++;
        i /= 10;
    }
    return length;
}

size_t IACharArray_lengthOfDouble(double d){
    size_t length = snprintf(NULL, 0, "%f", d);
    return length;
}

size_t IACharArray_lengthOfBool(bool b){
    return 1;
}

size_t IACharArray_lengthOfStringWithFormat(const char * format, ...){
    va_list args;
    va_start(args, format);
    size_t length = vsnprintf(NULL, 0, format, args);
    va_end (args);
    return length;
}

void IACharArray_set(char * c, const char * str){
    strcpy(c, str);
}

void IACharArray_setInt(char * c, int i){
    size_t length = IACharArray_lengthOfInt(i);
    IACharArray_setIntWithLength(c, i, length);
    c[length] = '\0';
}

void IACharArray_setIntWithLength(char * c, int i, size_t length){
    size_t stop = 0;
    if (i < 0) {
        stop = 1;
        i *= -1;
        c[0] = '-';
    }
    size_t index;
    for (index = length; index > stop;){
        c[--index] = (i % 10) + '0';
        i /= 10;
    }
}

void IACharArray_setLong(char * c, long l){
    size_t length = IACharArray_lengthOfLong(l);
    IACharArray_setLongWithLength(c, l, length);
    c[length] = '\0';
}

void IACharArray_setLongWithLength(char * c, long l, size_t length){
    size_t stop = 0;
    if (l < 0) {
        stop = 1;
        l *= -1;
        c[0] = '-';
    }
    for (size_t i = length; i > stop;){
        c[--i] = (l % 10) + '0';
        l /= 10;
    }
}

void IACharArray_setUInt64(char * c, uint64_t i){
    size_t length = IACharArray_lengthOfUInt64(i);
    IACharArray_setUInt64WithLength(c, i, length);
    c[length] = '\0';
}

void IACharArray_setUInt64WithLength(char * c, uint64_t i, size_t length){
    for (size_t index = length; index > 0;){
        c[--index] = (i % 10) + '0';
        i /= 10;
    }
}

void IACharArray_setDouble(char * c, double d){
    size_t length = IACharArray_lengthOfDouble(d);
    IACharArray_setDoubleWithLengthAndNullTermination(c, d, length + 1);
}

void IACharArray_setDoubleWithLengthAndNullTermination(char * c, double d, size_t length){
    snprintf(c, length, "%f", d);
}

void IACharArray_setBool(char * c, bool b){
    if (b) {
        c[0] = '1';
    }else{
        c[0] = '0';
    }
    c[1] = '\0';
}

void IACharArray_setWithFormat(char * c, const char * format, ...){
    va_list args;
    va_start(args, format);
    vsprintf(c, format, args);
    va_end (args);
}

int IACharArray_toInt(const char * c){
    return atoi(c);
}

long IACharArray_toLong(const char * c){
    return atol(c);
}

uint64_t IACharArray_toUInt64(const char * c){
    uint64_t result = 0;
    while (*c >= '0' && *c <= '9') {
        result *= 10;
        result += (*c - '0');
        c++;
    }
    return result;
}

double IACharArray_toDouble(const char * c){
    return atof(c);
}

bool IACharArray_toBool(const char * c){
    if (IACharArray_isEmpty(c) || strcmp(c, "0") == 0) {
        return false;
    }else{
        return true;
    }
}

void IACharArray_firstUpperCase(char * c){
    if (c[0] >= 'a' && c[0] <='z') {
        c[0] -= 32;
    }
}

void IACharArray_upperCase(char * c){
    size_t i = 0;
    while (c[i] != '\0') {
        if (c[i] >= 'a' && c[i] <='z') {
            c[i] -= 32;
        }
        i++;
    }
}

void IACharArray_firstLowerCase(char * c){
    if (c[0] >= 'A' && c[0] <='Z') {
        c[0] += 32;
    }
}

void IACharArray_lowerCase(char * c){
    size_t i = 0;
    while (c[i] != '\0') {
        if (c[i] >= 'A' && c[i] <='Z') {
            c[i] += 32;
        }
        i++;
    }
}

void IACharArray_concat(char * c, const char * str){
    c += strlen(c);
    IACharArray_set(c, str);
}

void IACharArray_concatInt(char * c, int i){
    c += strlen(c);
    IACharArray_setInt(c, i);
}

void IACharArray_concatLong(char * c, long l){
    c += strlen(c);
    IACharArray_setLong(c, l);
}

void IACharArray_concatUInt64(char * c, uint64_t i){
    c += strlen(c);
    IACharArray_setUInt64(c, i);
}

void IACharArray_concatDouble(char * c, double d){
    c += strlen(c);
    IACharArray_setDouble(c, d);
}

void IACharArray_concatBool(char * c, bool b){
    c += strlen(c);
    IACharArray_setBool(c, b);
}

void IACharArray_concatWithFormat(char * c, const char * format, ...){
    c += strlen(c);
    va_list args;
    va_start(args, format);
    vsprintf(c, format, args);
    va_end (args);
}

bool IACharArray_isNumberFormat(const char * c){
    while (*c != '\0'){
        if (*c < '0' || *c > '9'){
            return false;
        }
        c++;
    }
    return true;
}

bool IACharArray_isEmpty(const char * c){
    if (*c == '\0') {
        return true;
    }else{
        return false;
    }
}

bool IACharArray_areEqual(const char * c1, const char * c2){
    if (strcmp(c1, c2) == 0) {
        return true;
    }else{
        return false;
    }
}

