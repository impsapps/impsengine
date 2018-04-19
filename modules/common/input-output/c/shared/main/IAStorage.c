//
//  Storage.c
//  InputOutput
//
//  Created by Konstantin Merker on 14.08.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAStorage+Native.h"

#define CLASSNAME "IAStorage"


static IAString * privateDataDir = NULL;

const char * IAStorage_getPrivateDataDir(){
    if (privateDataDir == NULL){
        IA_disableAllocationTracking();
        privateDataDir = IAString_new("");
        IAStorage_nativeGetPrivateDataDir(privateDataDir);
        if (IAString_lastChar(privateDataDir) != '/') {
            IAString_concat(privateDataDir, "/");
        }
        IA_enableAllocationTracking();
    }
    return IAString_toCharArray(privateDataDir);
}


