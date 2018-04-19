//
//  IADepthFormat+iOS.m
//  Core
//
//  Created by Konstantin Merker on 15/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IADepthFormat+iOS.h"


GLKViewDrawableDepthFormat IADepthFormat_convert(IADepthFormat depthFormat){
    switch (depthFormat) {
        case IADepthFormat_NONE:
            return GLKViewDrawableDepthFormatNone;
        case IADepthFormat_16_BITS:
            return GLKViewDrawableDepthFormat16;
        case IADepthFormat_24_BITS:
            return GLKViewDrawableDepthFormat24;
        default:
            assert(0 && "Unknown depth format in app delegate!");
    }
}
