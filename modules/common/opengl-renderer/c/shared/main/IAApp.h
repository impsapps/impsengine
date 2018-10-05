#ifndef IAApp_h
#define IAApp_h

#include "IAAppAttributes.h"

typedef struct{
    void * correspondingObject;

    //@exe
    void (*commence)(void * correspondingObject);

    //@exe
    void (*onSurfaceSizeChanged)(void * correspondingObject, IASize surfaceSize);
    
    //@exe
    void (*onRender)(void * correspondingObject);
    
    //@exe+respondsTo
    void (*switchToPauseScreen)(void * correspondingObject);
    //@exe
    void (*saveGameState)(void * correspondingObject);
    //@exe
    void (*terminate)(void * correspondingObject);
    
    //@get
    IAColorFormat colorFormat;
    //@get
    IADepthFormat depthFormat;
    //@get
    IAStencilFormat stencilFormat;
    //@get
    IAMultisample multisample;
    
    //@set+get
    bool shouldLogRenderingPerformance;
} IAApp;


void IAApp_make(IAApp *, IAAppAttributes * attributes);

#include "IAApp+Generated.h"

#endif
