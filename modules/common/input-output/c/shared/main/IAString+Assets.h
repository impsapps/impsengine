#ifndef IAString_Assets_h
#define IAString_Assets_h

#include "IAString.h"

void IAString_initWithAsset(IAString * string, const char * assetName, const char * assetFileExtension);
IAString * IAString_newWithAsset(const char * assetName, const char * assetFileExtension);

#endif
