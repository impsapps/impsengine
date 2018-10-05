#include "IALibrary.h"
#include "IAOpenGLResourceDelegate.h"

#define CLASSNAME "IAOpenGLResourceDelegate"


void IAOpenGLResourceDelegate_make(IAOpenGLResourceDelegate * this, const IAOpenGLResourceDelegateAttributes * attributes){
    *this = (IAOpenGLResourceDelegate){
        .correspondingObject = IAOpenGLResourceDelegateAttributes_getCorrespondingObject(attributes),
        .createResources = IAOpenGLResourceDelegateAttributes_getCreateResourcesFunction(attributes),
        .destroyResources = IAOpenGLResourceDelegateAttributes_getDestroyResourcesFunction(attributes)
    };
}

