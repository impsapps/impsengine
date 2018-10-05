#include "IALibrary.h"
#include "IAOpenGLResourceDelegateAttributes.h"

#define CLASSNAME "IAOpenGLResourceDelegateAttributes"


void IAOpenGLResourceDelegateAttributes_make(IAOpenGLResourceDelegateAttributes * this, void * correspondingObject){
    *this = (IAOpenGLResourceDelegateAttributes){
        .correspondingObject = correspondingObject
    };
}


