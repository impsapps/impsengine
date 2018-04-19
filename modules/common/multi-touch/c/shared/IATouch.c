//
//  IATouch.c
//  Hit Verto
//
//  Created by Konstantin Merker on 10/03/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IATouch+Internal.h"
#include "IAAllocationTracker.h"

#define CLASSNAME "IATouch"


void IATouch_make(IATouch * this, IAPoint location){
    this->location = location;
}

void IATouch_makeCopy(IATouch * this, const IATouch * toCopy){
    *this = *toCopy;
}

void IATouch_setLocation(IATouch * this, IAPoint location){
    this->location = location;
}

bool IATouch_isInRect(const IATouch * this, IARect rect){
    IAPoint location = this->location;
    if (rect.origin.x <= location.x
        && rect.origin.y <= location.y
        && rect.origin.x + rect.size.width >= location.x
        && rect.origin.y + rect.size.height >= location.y) {
        return true;
    }else{
        return false;
    }
}


