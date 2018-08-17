//
//  IAStencilFormat+iOS.h
//  Core
//
//  Created by Konstantin Merker on 15/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAStencilFormat_iOS_h
#define IAStencilFormat_iOS_h

#import <GLKit/GLKit.h>
#include "IAStencilFormat.h"

GLKViewDrawableStencilFormat IAStencilFormat_convert(IAStencilFormat stencilFormat);

#endif
