#include "IALibrary.h"
#include "IAAppAttributes.h"

#define CLASSNAME "IAAppAttributes"


void IAAppAttributes_make(IAAppAttributes * this, void * correspondingObject){
    *this = (IAAppAttributes){
        .correspondingObject = correspondingObject,
        .colorFormat = IAColorFormat_RGBA_8888,
        .depthFormat = IADepthFormat_24_BITS,
        .stencilFormat = IAStencilFormat_NONE,
        .multisample = IAMultisample_4X,
    };
}
