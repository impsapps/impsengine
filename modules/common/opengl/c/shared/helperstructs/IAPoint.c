//
//  Point.c
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 06.04.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAPoint.h"

IAPoint IAPoint_make(float x, float y){
    IAPoint point;
    point.x = x;
    point.y = y;
    return point;
}


