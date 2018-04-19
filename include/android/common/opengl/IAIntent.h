//
//  IAIntent.h
//  OpenGL
//
//  Created by Konstantin Merker on 03/12/17.
//  Copyright © 2017 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAIntent_h
#define IAIntent_h

#include "IAView.h"

typedef struct{
    //@get
    IAView * view;
    //@getAsConst
    void * viewArgs;
    //@get+set
    uint64_t switchDuration;
} IAIntent;


void IAIntent_init(IAIntent * this, IAView * view);

void IAIntent_setViewArgs(IAIntent * this, const void * viewArgs, size_t sizeOfViewArgs);

void IAIntent_deinit(IAIntent * this);

#include "IAIntent+Generated.h"

#endif
