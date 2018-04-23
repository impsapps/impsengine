//
//  IATouchManager.h
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 28.05.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineiOS_IATouchManager_h
#define ImpsEngineiOS_IATouchManager_h

#include "IATouchHandler.h"
#include "IATouchDelegate.h"

void IATouchManager_commence();

void IATouchManager_registerTouchDelegate(IATouchDelegate * touchDelegate);
void IATouchManager_unregisterTouchDelegate(IATouchDelegate * touchDelegate);

IATouchHandler *  IATouchManager_createNewTouchHandler(long touchId, IAPoint location);
IATouchHandler * IATouchManager_getTouchHandler(long touchId);
void IATouchManager_destroyTouchHandler(IATouchHandler * touchHandler);

void IATouchManager_onTouchBegan(size_t lengthOfTouchHandlers, IATouchHandler * touchHandlers[lengthOfTouchHandlers]);
void IATouchManager_onTouchMoved(size_t lengthOfTouchHandlers, IATouchHandler * touchHandlers[lengthOfTouchHandlers]);
void IATouchManager_onTouchEnded(size_t lengthOfTouchHandlers, IATouchHandler * touchHandlers[lengthOfTouchHandlers]);

void IATouchManager_terminate();

#endif
