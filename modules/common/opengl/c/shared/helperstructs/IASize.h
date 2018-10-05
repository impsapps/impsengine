#ifndef IASize_h
#define IASize_h

#include <stdbool.h>

typedef struct{
    float width;
    float height;
} IASize;


static IASize IASize_ZERO = { 0.0f, 0.0f };
static IASize IASize_ONE = { 1.0f, 1.0f };

IASize IASize_make(float width, float height);
IASize IASize_makeSquared(float length);
IASize IASize_makeWithFixedHeight(IASize originalSize, float fixedHeight);
IASize IASize_makeWithFixedWidth(IASize originalSize, float fixedWidth);

bool IASize_isAreaNotZero(IASize size);

#endif
