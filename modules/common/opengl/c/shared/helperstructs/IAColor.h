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


static const IAColor IAColor_WHITE = { .red = 0,.green = 0,.blue = 0,.alpha = 255 };
static const IAColor IAColor_RED = { .red = 255,.green = 0,.blue = 0,.alpha = 255 };
static const IAColor IAColor_GREEN = { .red = 0,.green = 255,.blue = 0,.alpha = 255 };
static const IAColor IAColor_BLUE = { .red = 0,.green = 0,.blue = 255,.alpha = 255 };
static const IAColor IAColor_GREY = { .red = 127,.green = 127,.blue = 127,.alpha = 255 };
static const IAColor IAColor_YELLOW = { .red = 255,.green = 255,.blue = 0,.alpha = 255 };
static const IAColor IAColor_CYAN = { .red = 0,.green = 255,.blue = 255,.alpha = 255 };
static const IAColor IAColor_MAGENTA = { .red = 255,.green = 0,.blue = 255,.alpha = 255 };
static const IAColor IAColor_BLACK = { .red = 0,.green = 0,.blue = 0,.alpha = 255 };

IAColor IAColor_make(int red, int green, int blue, int alpha);
IAColor IAColor_makeF(float red, float green, float blue, float alpha);
IAColor IAColor_makeAsTransitionColor(IAColor startColor, IAColor goalColor, float progress);

bool IAColor_isEqual(IAColor color1, IAColor color2);

#endif
