#include "IALibrary.h"
#include "IADrawable.h"

#define CLASSNAME "IADrawable"


void IADrawable_make(IADrawable * this, IADrawable_drawFunction draw){
    this->base = IAObject_make(this);
    this->draw = draw;
    this->isVisible = true;
}

void IADrawable_makeCopy(IADrawable * this, const IADrawable * drawableToCopy){
    this->base = IAObject_make(this);
    this->draw = drawableToCopy->draw;
    this->isVisible = drawableToCopy->isVisible;
}

void IADrawable_draw(const IADrawable * this){
    if (this->isVisible == true) {
        this->draw(this);
    }
}


