//
//  IADepthFormat+iOS.h
//  Core
//
//  Created by Konstantin Merker on 15/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IADepthFormat_iOS_h
#define IADepthFormat_iOS_h

#import <GLKit/GLKit.h>
#include "IADepthFormat.h"

GLKViewDrawableDepthFormat IADepthFormat_convert(IADepthFormat depthFormat);

#endif
