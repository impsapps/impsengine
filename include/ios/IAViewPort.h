//
//  IAViewPort.h
//  OpenGL
//
//  Created by Konstantin Merker on 03/11/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAViewPort_h
#define IAViewPort_h

#include "IARect.h"

static const IARect IAViewPort_defaultRectForContent = {
	.origin = {.x = 0.0f, .y = 0.0f},
	.size = {.width = 300.0f, .height = 300.0f}
};

IASize IAViewPort_getSize();

#endif
