//
//  Point.c
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 06.04.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include <string.h>
#include "IALibrary.h"
#include "IAPoint.h"

IAPoint IAPoint_make(float x, float y){
    IAPoint point;
    point.x = x;
    point.y = y;
    return point;
}

bool IAPoint_isEqual(IAPoint p1, IAPoint p2){
    if (memcmp(&p1, &p2, sizeof(IAPoint)) == 0) {
        return true;
    }else{
        return false;
    }
}

