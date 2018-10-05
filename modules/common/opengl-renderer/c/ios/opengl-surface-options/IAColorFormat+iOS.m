#include "IAColorFormat+iOS.h"


GLKViewDrawableColorFormat IAColorFormat_convert(IAColorFormat colorFormat){
    switch (colorFormat) {
        case IAColorFormat_RGBA_8888:
            return GLKViewDrawableColorFormatRGBA8888;
        case IAColorFormat_RGB_565:
            return GLKViewDrawableColorFormatRGB565;
        case IAColorFormat_RGBA_4444:
            assert(0 && "IAColorFormat_RGBA_4444 is only supported on Android");
        default:
            assert(0 && "Unknown color format in app delegate!");
    }
}
