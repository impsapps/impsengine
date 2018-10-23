#ifndef IADrawable_h
#define IADrawable_h

#include <stdbool.h>
#include "IAObject.h"

typedef struct IADrawable IADrawable;

typedef void (*IADrawable_drawFunction)(const IADrawable *);

struct IADrawable{
    //@extend
    IAObject base;
    IADrawable_drawFunction draw;
    //@set+get
    bool isVisible;
};


void IADrawable_make(IADrawable *, IADrawable_drawFunction draw);
void IADrawable_makeCopy(IADrawable *, const IADrawable * drawableToCopy);

void IADrawable_draw(const IADrawable *);

#include "IADrawable+Generated.h"

#endif
