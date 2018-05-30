//
//  IADrawingBounds.c
//  OpenGL
//
//  Created by Konstantin Merker on 03/11/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IADrawingBounds.h"
#include "IAOpenGLHeaders.h"
#include "IAViewPort+Internal.h"

#define CLASSNAME "IADrawingBounds"


void IADrawingBounds_setBounds(IARect bounds){
    if (glIsEnabled(GL_SCISSOR_TEST) == GL_FALSE) {
        glEnable(GL_SCISSOR_TEST);
    }
    IASize framebufferSize = IAViewPort_getFrameBufferSize();
	IASize viewSize = IAViewPort_getSize();
	float scaleWidth = framebufferSize.width / viewSize.width;
	float scaleHeight = framebufferSize.height / viewSize.height;
	bounds.origin.x *= scaleWidth;
	bounds.origin.y *= scaleHeight;
	bounds.size.width *= scaleWidth;
	bounds.size.height *= scaleHeight;
    glScissor(bounds.origin.x, framebufferSize.height - bounds.origin.y - bounds.size.height, bounds.size.width, bounds.size.height);
}

void IADrawingBounds_disableBounds(){
    IASize size = IAViewPort_getFrameBufferSize();
    glScissor(0, 0, size.width, size.height);
}

