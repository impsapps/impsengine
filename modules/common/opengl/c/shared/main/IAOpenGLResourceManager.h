#ifndef IAOpenGLResourceManager_h
#define IAOpenGLResourceManager_h

#include "IAOpenGLResourceDelegate.h"

void IAOpenGLResourceManager_commence(void);

void IAOpenGLResourceManager_registerOpenGLResourceDelegate(IAOpenGLResourceDelegate * delegate);

void IAOpenGLResourceManager_unregisterOpenGLResourceDelegate(IAOpenGLResourceDelegate * delegate);

void IAOpenGLResourceManager_onSurfaceCreated();
void IAOpenGLResourceManager_onSurfaceDestroyed();

bool IAOpenGLResourceManager_isSurfaceCreated();

void IAOpenGLResourceManager_terminate();

#endif
