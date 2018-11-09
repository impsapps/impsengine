#ifndef IAOpenGLResourceDelegate_h
#define IAOpenGLResourceDelegate_h

#include "IAOpenGLResourceDelegateAttributes.h"

//@event
typedef struct{
    void * correspondingObject;
    //@exe
    void (*createResources)(void * correspondingObject);
    //@exe
    void (*destroyResources)(void * correspondingObject);
} IAOpenGLResourceDelegate;


void IAOpenGLResourceDelegate_make(IAOpenGLResourceDelegate *, const IAOpenGLResourceDelegateAttributes * attributes);

#include "IAOpenGLResourceDelegate+Generated.h"

#endif
