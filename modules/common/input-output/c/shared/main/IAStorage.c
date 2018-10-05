#include "IALibrary.h"
#include "IAStorage+Native.h"

#define CLASSNAME "IAStorage"


static IAString * privateDataDir = NULL;

const char * IAStorage_getPrivateDataDir(){
    if (privateDataDir == NULL){
        privateDataDir = IAString_new("");
        IAStorage_nativeGetPrivateDataDir(privateDataDir);
        if (IAString_lastChar(privateDataDir) != '/') {
            IAString_concat(privateDataDir, "/");
        }
    }
    return IAString_toCharArray(privateDataDir);
}


