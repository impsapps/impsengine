//
//  IATouchHandler.h
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 28.05.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineiOS_IATouchHandler_h
#define ImpsEngineiOS_IATouchHandler_h

#include <stdbool.h>

#include "IATouchDelegate.h"
#include "IAArrayList.h"
#include "IAPoint.h"
#include "IARect.h"
#include "IATouch.h"

typedef struct{
    //@extend
    IAObject base;
    //@get
    IATouch touch;
    IAArrayList touchDelegates;
} IATouchHandler;


void IATouchHandler_init(IATouchHandler *, long touchId, IAPoint location);
void IATouchHandler_reinit(IATouchHandler *, long touchId, IAPoint location);

void IATouchHandler_setTouchLocation(IATouchHandler *, IAPoint newLocation);

void IATouchHandler_registerTouchDelegate(IATouchHandler *, IATouchDelegate * touchDelegate);
void IATouchHandler_prepareTouchDelegates(IATouchHandler *);
void IATouchHandler_unregisterTouchDelegate(IATouchHandler *, IATouchDelegate * touchDelegate);

void IATouchHandler_deinit(IATouchHandler *);

#include "IATouchHandler+Generated.h"

#endif
