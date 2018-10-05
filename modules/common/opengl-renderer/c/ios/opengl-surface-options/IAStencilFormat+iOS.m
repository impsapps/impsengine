#include "IAStencilFormat+iOS.h"


GLKViewDrawableStencilFormat IAStencilFormat_convert(IAStencilFormat stencilFormat){
    switch (stencilFormat) {
        case IAStencilFormat_NONE:
            return GLKViewDrawableStencilFormatNone;
        case IAStencilFormat_8_BITS:
            return GLKViewDrawableStencilFormat8;
        default:
            assert(0 && "Unknown stencil format in app delegate!");
    }
}
