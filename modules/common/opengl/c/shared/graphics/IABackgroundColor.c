//
//  IABackgroundColor.c
//  Hit Verto
//
//  Created by Konstantin Merker on 30.08.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IABackgroundColor.h"
#include "IAOpenGLHeaders.h"

#define CLASSNAME "IABackgroundColor"

void IABackgroundColor_draw(IAColor color){
    debugAssert(color.alpha == 255 && "background color must have alpha == 255");
    glClearColor(color.red / 255.0f, color.green / 255.0f, color.blue / 255.0f, 1.0f);
}


