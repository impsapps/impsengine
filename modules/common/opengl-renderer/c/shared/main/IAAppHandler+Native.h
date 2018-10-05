#ifndef IAAppHandler_Native_h
#define IAAppHandler_Native_h

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
