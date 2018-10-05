#ifndef IAViewPort_h
#define IAViewPort_h

#include "IARect.h"

static const IARect IAViewPort_defaultRectForContent = {
	.origin = {.x = 0.0f, .y = 0.0f},
	.size = {.width = 300.0f, .height = 300.0f}
};

IASize IAViewPort_getSize();
float IAViewPort_getWidth();
float IAViewPort_getHeight();

void IAViewPort_modifySize(IASize newSize);

#endif
