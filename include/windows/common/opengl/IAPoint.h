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

IAPoint IAPoint_make(float x, float y);

#endif
