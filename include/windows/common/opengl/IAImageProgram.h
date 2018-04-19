//
//  IAImageProgram.h
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 14.04.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineiOS_IAImageProgram_h
#define ImpsEngineiOS_IAImageProgram_h

#include "IAProgram.h"

typedef struct{
    //@extend
    IAProgram program;
    //@get
    GLint positionLocation;
    //@get
    GLint texturePositionLocation;
    //@get
    GLint leftTopWidthHeight;
    //@get
    GLint multiplicatorLocation;
    //@get
    GLint textureSampler2DLocation;
    IANotificationDelegate linkingCompleteDelegate;
} IAImageProgram;


void IAImageProgram_init(IAImageProgram *);

void IAImageProgram_deinit(IAImageProgram *);

#include "IAImageProgram+Generated.h"

#endif
