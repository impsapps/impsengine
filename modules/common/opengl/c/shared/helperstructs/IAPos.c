//
//  IAPos.c
//  Hit Verto
//
//  Created by Konstantin Merker on 11.07.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAPos.h"

IAPos IAPos_make(int x, int y){
    IAPos pos;
    pos.x = x;
    pos.y = y;
    return pos;
}

bool IAPos_areEqual(IAPos pos1, IAPos pos2){
    if (pos1.x == pos2.x && pos1.y == pos2.y) {
        return true;
    }else{
        return false;
    }
}

