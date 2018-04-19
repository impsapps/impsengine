//
//  IAColorRectProgram.h
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 06.04.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineiOS_IAColorRectProgram_h
#define ImpsEngineiOS_IAColorRectProgram_h

#include "IAProgram.h"

typedef struct{
    //@extend
    IAProgram program;
    //@get
    GLuint positionLocation;
    //@get
    GLuint leftTopWidthHeight;
    //@get
    GLuint colorLocation;
    IANotificationDelegate linkingCompleteDelegate;
} IAColorRectProgram;


void IAColorRectProgram_init(IAColorRectProgram *);

void IAColorRectProgram_deinit(IAColorRectProgram *);

#include "IAColorRectProgram+Generated.h"

#endif
