//
//  IAViewPort.c
//  OpenGL
//
//  Created by Konstantin Merker on 03/11/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAViewPort+Internal.h"
#include "IADrawingBounds.h"
#include "IAOpenGLHeaders.h"

#define CLASSNAME "IAViewPort"


static IASize frameBufferSize;
static IASize size;

void IAViewPort_updateFrameBufferSize(IASize frameBufferSizeTemp){
    frameBufferSize = frameBufferSizeTemp;
	size = frameBufferSizeTemp;
    glViewport(0, 0, frameBufferSize.width, frameBufferSize.height);
}

IASize IAViewPort_getFrameBufferSize() {
	return frameBufferSize;
}

IASize IAViewPort_getSize(){
    return size;
}

float IAViewPort_getWidth() {
	return size.width;
}

float IAViewPort_getHeight() {
	return size.height;
}

void IAViewPort_modifySize(IASize newSize) {
	size = newSize;
}
