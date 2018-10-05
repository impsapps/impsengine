#ifndef IATouch_h
#define IATouch_h

#include "IARect.h"

typedef struct{
    //@get
    long identifier;
    //@get
    IAPoint location;
} IATouch;


IATouch IATouch_make(long identifier, IAPoint location);

bool IATouch_hasSameIdentifier(IATouch t1, IATouch t2);

#include "IATouch+Generated.h"

#endif
