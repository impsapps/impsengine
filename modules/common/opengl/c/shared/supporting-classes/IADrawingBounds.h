#ifndef IADrawingBounds_h
#define IADrawingBounds_h

#include "IARect.h"

bool IADrawingBounds_isDrawingCompletelyDisabled(void);

void IADrawingBounds_pushBounds(IARect bounds);
void IADrawingBounds_popBounds(void);

#endif
