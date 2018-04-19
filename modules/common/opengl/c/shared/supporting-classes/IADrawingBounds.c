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
#include "IAViewPort.h"

#define CLASSNAME "IADrawingBounds"


void IADrawingBounds_setBounds(IARect bounds){
    if (glIsEnabled(GL_SCISSOR_TEST) == GL_FALSE) {
        glEnable(GL_SCISSOR_TEST);
    }
    IASize size = IAViewPort_getSize();
    glScissor(bounds.origin.x, size.height - bounds.origin.y - bounds.size.height, bounds.size.width, bounds.size.height);
}

void IADrawingBounds_disableBounds(){
    IASize size = IAViewPort_getSize();
    glScissor(0, 0, size.width, size.height);
}

