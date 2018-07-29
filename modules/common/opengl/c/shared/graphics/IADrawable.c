//
//  IADrawable.c
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 06.04.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IADrawable.h"

#define CLASSNAME "IADrawable"


void IADrawable_make(IADrawable * this, void (*drawFunction)(const IADrawable*)){
    this->base = IAObject_make(this);
    this->drawFunction = drawFunction;
    this->isVisible = true;
}

void IADrawable_makeCopy(IADrawable * this, const IADrawable * drawableToCopy){
    this->base = IAObject_make(this);
    this->drawFunction = drawableToCopy->drawFunction;
    this->isVisible = drawableToCopy->isVisible;
}

void IADrawable_draw(const IADrawable * this){
    if (this->isVisible == true) {
        this->drawFunction(this);
    }
}


