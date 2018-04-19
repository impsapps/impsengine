//
//  IAInterfaceOrientationMask+iOS.m
//  Core
//
//  Created by Konstantin Merker on 15/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IAInterfaceOrientationMask+iOS.h"


UIInterfaceOrientationMask IAInterfaceOrientationMask_convert(IAInterfaceOrientationMask mask){
    switch (mask) {
        case IAInterfaceOrientationMask_PORTRAIT:
            return UIInterfaceOrientationMaskPortrait;
        case IAInterfaceOrientationMask_LANDSCAPE:
            return UIInterfaceOrientationMaskLandscape;
        case IAInterfaceOrientationMask_ALL_BUT_UPSIDE_DOWN:
            return UIInterfaceOrientationMaskAllButUpsideDown;
        default:
            assert(0 && "IAInterfaceOrientationMask unknown!");
    }
}
