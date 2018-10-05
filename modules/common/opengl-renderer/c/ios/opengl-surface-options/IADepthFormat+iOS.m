#include "IADepthFormat+iOS.h"


GLKViewDrawableDepthFormat IADepthFormat_convert(IADepthFormat depthFormat){
    switch (depthFormat) {
        case IADepthFormat_NONE:
            return GLKViewDrawableDepthFormatNone;
        case IADepthFormat_16_BITS:
            return GLKViewDrawableDepthFormat16;
        case IADepthFormat_24_BITS:
            return GLKViewDrawableDepthFormat24;
        default:
            assert(0 && "Unknown depth format in app delegate!");
    }
}
