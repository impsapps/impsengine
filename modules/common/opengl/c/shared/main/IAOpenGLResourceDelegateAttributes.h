#ifndef IAOpenGLResourceDelegateAttributes_h
#define IAOpenGLResourceDelegateAttributes_h

typedef struct{
    //@get
    void * correspondingObject;
    //@set+get
    void (*createResources)(void * correspondingObject);
    //@set+get
    void (*destroyResources)(void * correspondingObject);
} IAOpenGLResourceDelegateAttributes;


void IAOpenGLResourceDelegateAttributes_make(IAOpenGLResourceDelegateAttributes *, void * correspondingObject);

#include "IAOpenGLResourceDelegateAttributes+Generated.h"

#endif
