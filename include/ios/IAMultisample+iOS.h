//
//  IAMultisample+iOS.h
//  Core
//
//  Created by Konstantin Merker on 15/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAMultisample_iOS_h
#define IAMultisample_iOS_h

#import <GLKit/GLKit.h>
#include "IAMultisample.h"

GLKViewDrawableMultisample IAMultisample_convert(IAMultisample multisample);

#endif
