//
//  IADrawable.h
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 06.04.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#ifndef ImpsEngineiOS_IADrawable_h
#define ImpsEngineiOS_IADrawable_h

#include <stdbool.h>

typedef struct IADrawable IADrawable;

struct IADrawable{
    void (*drawFunction)(const IADrawable *);
    //@set+get
    bool isVisible;
};


void IADrawable_make(IADrawable *, void (*drawFunction)(const IADrawable*));
void IADrawable_makeCopy(IADrawable *, const IADrawable * drawableToCopy);

void IADrawable_draw(const IADrawable *);

#include "IADrawable+Generated.h"

#endif
