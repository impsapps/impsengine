//
//  IAInterfaceOrientationMask.h
//  Core
//
//  Created by Konstantin Merker on 14/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAInterfaceOrientationMask_h
#define IAInterfaceOrientationMask_h

typedef enum{
    IAInterfaceOrientationMask_PORTRAIT = 1,
    IAInterfaceOrientationMask_LANDSCAPE = (1 << 1),
    IAInterfaceOrientationMask_ALL_BUT_UPSIDE_DOWN = (IAInterfaceOrientationMask_PORTRAIT | IAInterfaceOrientationMask_LANDSCAPE)
} IAInterfaceOrientationMask;

#endif
