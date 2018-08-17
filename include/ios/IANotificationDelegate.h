//
//  IANotificationDelegate.h
//  ImpsEngine
//
//  Created by Konstantin Merker on 09/08/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngine_IANotificationDelegate_h
#define ImpsEngine_IANotificationDelegate_h

//@event
typedef struct{
    void * correspondingObject;
    //@exe
    void (*notify)(void * correspondingObject);
} IANotificationDelegate;

#include "IANotificationDelegate+Generated.h"

#endif
