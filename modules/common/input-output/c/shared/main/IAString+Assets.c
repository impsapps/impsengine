//
//  IAString+Assets.c
//  InputOutput
//
//  Created by Konstantin Merker on 18/09/16.
//
//

#include "IALibrary.h"
#include "IAString.h"
#include "IAString+Assets.h"
#include "IAString+Assets+Native.h"

#define CLASSNAME "IAString"


void IAString_initWithAsset(IAString * string, const char * assetName, const char * assetFileExtension){
    IAString_nativeInitWithAsset(string, assetName, assetFileExtension);
}

IAString * IAString_newWithAsset(const char * assetName, const char * assetFileExtension){
    IAString * string = IA_new(sizeof(IAString), (void (*)(void *)) IAString_deinit);
    IAString_initWithAsset(string, assetName, assetFileExtension);
    return string;
}



