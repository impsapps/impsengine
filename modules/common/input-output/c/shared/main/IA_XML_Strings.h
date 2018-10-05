#ifndef IA_XML_Strings_h
#define IA_XML_Strings_h

#include "IAAutoExpandingHashMap.h"

typedef struct{
    IAAutoExpandingHashMap * strings;
    IAString * currentElementKey;
    IAString * assetName;
} IA_XML_Strings;


void IA_XML_Strings_init(IA_XML_Strings *, const char * assetName);

void IA_XML_Strings_load(IA_XML_Strings *);

IAString * IA_XML_Strings_get(IA_XML_Strings *, const char * key);
IAAutoExpandingHashMap * IA_XML_Strings_getStrings(IA_XML_Strings *);

void IA_XML_Strings_deinit(IA_XML_Strings *);

#include "IA_XML_Strings+Generated.h"

#endif
