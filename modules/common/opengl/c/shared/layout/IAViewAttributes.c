#include "IALibrary.h"
#include "IAViewAttributes.h"

#define CLASSNAME "IAViewAttributes"


void IAViewAttributes_make(IAViewAttributes * this, void * correspondingView){
    *this = (IAViewAttributes){
        .correspondingView = correspondingView
    };
}

