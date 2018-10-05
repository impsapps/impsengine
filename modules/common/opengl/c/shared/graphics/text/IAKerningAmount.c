#include "IALibrary.h"
#include "IAKerningAmount.h"

#define CLASSNAME "IAKerningAmount"


void IAKerningAmount_make(IAKerningAmount * this, float amount){
    debugAssert(amount >= 0 && "kerning amounts must be positive");
    *this = (IAKerningAmount){
        .base = IAObject_make(this),
        .amount = amount
    };
}


