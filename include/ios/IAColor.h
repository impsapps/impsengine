//
//  Color.h
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 06.04.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineiOS_IAColor_h
#define ImpsEngineiOS_IAColor_h

#include <stdbool.h>

typedef struct{
    int red;
    int green;
    int blue;
    int alpha;
} IAColor;


IAColor IAColor_make(int red, int green, int blue, int alpha);
IAColor IAColor_makeF(float red, float green, float blue, float alpha);
IAColor IAColor_makeAsTransitionColor(IAColor startColor, IAColor goalColor, float progress);

bool IAColor_isEqual(IAColor color1, IAColor color2);

#endif
