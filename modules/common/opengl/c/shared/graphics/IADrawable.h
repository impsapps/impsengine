#ifndef IADrawable_h
#define IADrawable_h

#include <stdbool.h>
#include "IAObject.h"

typedef struct IADrawable IADrawable;

struct IADrawable{
    //@extend
    IAObject base;
    void (*drawFunction)(const IADrawable *);
    //@set+get
    bool isVisible;
};


void IADrawable_make(IADrawable *, void (*drawFunction)(const IADrawable*));
void IADrawable_makeCopy(IADrawable *, const IADrawable * drawableToCopy);

void IADrawable_draw(const IADrawable *);

#include "IADrawable+Generated.h"

#endif
