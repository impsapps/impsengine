//
//  IAPos.h
//  Hit Verto
//
//  Created by Konstantin Merker on 11.07.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAPos_h
#define Hit_Verto_IAPos_h

#include <stdbool.h>

typedef struct{
    int x;
    int y;
} IAPos;

IAPos IAPos_make(int x, int y);

bool IAPos_areEqual(IAPos pos1, IAPos pos2);

#endif
