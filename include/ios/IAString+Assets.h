//
//  IAString+Assets.h
//  InputOutput
//
//  Created by Konstantin Merker on 18/09/16.
//
//

#ifndef InputOutput_IAString_Assets_h
#define InputOutput_IAString_Assets_h

#include "IAString.h"

void IAString_initWithAsset(IAString * string, const char * assetName, const char * assetFileExtension);
IAString * IAString_newWithAsset(const char * assetName, const char * assetFileExtension);

#endif
