//
//  IAApp.h
//  Core
//
//  Created by Konstantin Merker on 02/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

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
    void (*render)(void * correspondingObject);
    
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
