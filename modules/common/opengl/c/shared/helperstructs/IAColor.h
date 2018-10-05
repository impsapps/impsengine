#ifndef IAColor_h
#define IAColor_h

#include <stdbool.h>

typedef struct{
    int red;
    int green;
    int blue;
    int alpha;
} IAColor;


static const IAColor IAColor_white = { .red = 0,.green = 0,.blue = 0,.alpha = 255 };
static const IAColor IAColor_red = { .red = 255,.green = 0,.blue = 0,.alpha = 255 };
static const IAColor IAColor_green = { .red = 0,.green = 255,.blue = 0,.alpha = 255 };
static const IAColor IAColor_blue = { .red = 0,.green = 0,.blue = 255,.alpha = 255 };
static const IAColor IAColor_grey = { .red = 127,.green = 127,.blue = 127,.alpha = 255 };
static const IAColor IAColor_yellow = { .red = 255,.green = 255,.blue = 0,.alpha = 255 };
static const IAColor IAColor_cyan = { .red = 0,.green = 255,.blue = 255,.alpha = 255 };
static const IAColor IAColor_magenta = { .red = 255,.green = 0,.blue = 255,.alpha = 255 };
static const IAColor IAColor_black = { .red = 0,.green = 0,.blue = 0,.alpha = 255 };

IAColor IAColor_make(int red, int green, int blue, int alpha);
IAColor IAColor_makeF(float red, float green, float blue, float alpha);
IAColor IAColor_makeAsTransitionColor(IAColor startColor, IAColor goalColor, float progress);

bool IAColor_isEqual(IAColor color1, IAColor color2);

#endif
