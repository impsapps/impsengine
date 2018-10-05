#include "IAMultisample+iOS.h"


GLKViewDrawableMultisample IAMultisample_convert(IAMultisample multisample){
    switch (multisample) {
        case IAMultisample_NONE:
            return GLKViewDrawableMultisampleNone;
        case IAMultisample_4X:
            return GLKViewDrawableMultisample4X;
        default:
            assert(0 && "Unknown multisample format in app delegate!");
    }
}
