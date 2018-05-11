//
//  Point.h
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 06.04.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineiOS_IAPoint_h
#define ImpsEngineiOS_IAPoint_h

typedef struct{
    float x;
    float y;
} IAPoint;

static const IAPoint IAPoint_ZERO = {.x = 0.0f, .y = 0.0f};
static const IAPoint IAPoint_ONE = {.x = 1.0f,.y = 1.0f};

IAPoint IAPoint_make(float x, float y);

#endif
