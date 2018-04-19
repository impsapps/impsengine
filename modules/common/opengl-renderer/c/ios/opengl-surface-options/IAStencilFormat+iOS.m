//
//  IAStencilFormat+iOS.m
//  Core
//
//  Created by Konstantin Merker on 15/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IAStencilFormat+iOS.h"


GLKViewDrawableStencilFormat IAStencilFormat_convert(IAStencilFormat stencilFormat){
    switch (stencilFormat) {
        case IAStencilFormat_NONE:
            return GLKViewDrawableStencilFormatNone;
        case IAStencilFormat_8_BITS:
            return GLKViewDrawableStencilFormat8;
        default:
            assert(0 && "Unknown stencil format in app delegate!");
    }
}
