//
//  IAColorFormat.h
//  Core
//
//  Created by Konstantin Merker on 14/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAColorFormat_h
#define IAColorFormat_h

typedef enum{
    IAColorFormat_RGBA_8888,
    IAColorFormat_RGB_565,
    //Android only:
    IAColorFormat_RGBA_4444
} IAColorFormat;

#endif
