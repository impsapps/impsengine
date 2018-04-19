//
//  IAMultisample+iOS.m
//  Core
//
//  Created by Konstantin Merker on 15/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IAMultisample+iOS.h"


GLKViewDrawableMultisample IAMultisample_convert(IAMultisample multisample){
    switch (multisample) {
        case IAMultisample_NONE:
            return GLKViewDrawableMultisampleNone;
        case IAMultisample_4X:
            return GLKViewDrawableMultisample4X;
        default:
            assert(0 && "Unknown multisample format in app delegate!");
    }
}
