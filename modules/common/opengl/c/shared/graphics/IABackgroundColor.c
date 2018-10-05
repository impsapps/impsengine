#include "IALibrary.h"
#include "IABackgroundColor.h"
#include "IAOpenGLHeaders.h"

#define CLASSNAME "IABackgroundColor"

void IABackgroundColor_draw(IAColor color){
    debugAssert(color.alpha == 255 && "background color must have alpha == 255");
    glClearColor(color.red / 255.0f, color.green / 255.0f, color.blue / 255.0f, 1.0f);
}


