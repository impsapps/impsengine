#ifndef IAAppAttributes_h
#define IAAppAttributes_h

#include <stdbool.h>
#include "IASize.h"
#include "IAColorFormat.h"
#include "IADepthFormat.h"
#include "IAStencilFormat.h"
#include "IAMultisample.h"


typedef struct{
    //@get
    void * correspondingObject;

    //@set+get
    void (*commence)(void * correspondingObject);

    //@set+get
    void (*onSurfaceSizeChanged)(void * correspondingObject, IASize surfaceSize);
    
    //@set+get
    void (*onRender)(void * correspondingObject);
    
    //@set+get
    void (*switchToPauseScreen)(void * correspondingObject);
    //@set+get
    void (*saveGameState)(void * correspondingObject);
    
    //@set+get
    void (*terminate)(void * correspondingObject);
    
    //@set+get
    IAColorFormat colorFormat;
    //@set+get
    IADepthFormat depthFormat;
    //@set+get
    IAStencilFormat stencilFormat;
    //@set+get
    IAMultisample multisample;
    
    //@set+get
    bool shouldLogRenderingPerformance;
} IAAppAttributes;


void IAAppAttributes_make(IAAppAttributes *, void * correspondingObject);

#include "IAAppAttributes+Generated.h"

#endif
