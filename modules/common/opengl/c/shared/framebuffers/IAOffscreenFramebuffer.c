//
//  IAOffscreenFramebuffer.c
//  OpenGL
//
//  Created by Konstantin Merker on 13.12.17.
//Copyright © 2017 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAOffscreenFramebuffer.h"
#include "IAOpenGLAssert.h"
#include "IAOpenGL.h"
#include "IAViewPort+Internal.h"
#include "IABackgroundColor.h"
#include "IACurrentFramebuffer.h"

#define CLASSNAME "IAOffscreenFramebuffer"

void IAOffscreenFramebuffer_initWithRGB565AndBind(IAOffscreenFramebuffer * this, int width, int height, IAColor backgroundColor){
    glAssert();
    glGenFramebuffers(1, &this->framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);
    glAssert();
    glGenRenderbuffers(1, &this->colorRenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, this->colorRenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB565, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, this->colorRenderbuffer);
    glAssert();
    glGenRenderbuffers(1, &this->depthRenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, this->depthRenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->depthRenderbuffer);
    
    IAViewPort_updateFrameBufferSize(IASize_make(width, height));
    IACurrentFramebuffer_set(this->framebuffer);
    
    IABackgroundColor_draw(backgroundColor);
    
#ifdef DEBUG
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER) ;
    if(status != GL_FRAMEBUFFER_COMPLETE) {
        logError("failed to make complete framebuffer object %x", status);
    }
#endif
    glAssert();
    IA_incrementInitCount();
}

void IAOffscreenFramebuffer_deinit(IAOffscreenFramebuffer * this){
    glDeleteFramebuffers(1, &this->framebuffer);
    glDeleteRenderbuffers(1, &this->colorRenderbuffer);
    glDeleteRenderbuffers(1, &this->depthRenderbuffer);
    IA_decrementInitCount();
}

