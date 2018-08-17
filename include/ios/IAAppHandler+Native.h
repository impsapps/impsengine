//
//  BaseApplication+Native.h
//  ImpsEngine
//
//  Created by Konstantin Merker on 01/04/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngine_IAAppHandler_Native_h
#define ImpsEngine_IAAppHandler_Native_h

#include "IAApp.h"
#include "IASize.h"

void IAAppHandler_onAppStart();

IAApp * IAAppHandler_getAppDelegate();

void IAAppHandler_onSurfaceCreated();
void IAAppHandler_onSurfaceChanged(IASize newSurfaceSize);

void IAAppHandler_render();

void IAAppHandler_switchToPausescreen();

void IAAppHandler_saveGameState();

void IAAppHandler_destroyResources();

#endif
