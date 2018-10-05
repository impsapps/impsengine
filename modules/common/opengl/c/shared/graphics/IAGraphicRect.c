#include "IALibrary.h"
#include "IAGraphicRect.h"
#include "IAOpenGLHeaders.h"
#include "IAOpenGLAssert.h"
#include "IAArrayBuffer.h"
#include "IAElementArrayBuffer.h"
#include "IAViewPort.h"

#define CLASSNAME "IAGraphicRect"

void IAGraphicRect_setRectFunction(IAGraphicRect * this, IARect rect);

void IAGraphicRect_drawFunction(const IAGraphicRect * this);
IARect IAGraphicRect_getRectToRender(const IAGraphicRect * this);

static IAElementArrayBuffer * elementArrayBuffer;

void IAGraphicRect_commence(){
    glAssert();
    GLushort indices[] = {0,1,3,2};
    elementArrayBuffer = IAElementArrayBuffer_new(sizeof(GLushort) * 4, indices, GL_STATIC_DRAW);
    glAssert();
}

void IAGraphicRect_make(IAGraphicRect * this, void (*transformRectToRender)(const IAGraphicRect *, IARect *), void (*setupRendering)(const IAGraphicRect *, IARect)){
    IADrawableRect_make((IADrawableRect *) this, (void (*)(const IADrawable *)) IAGraphicRect_drawFunction, (void (*)(IADrawableRect *, IARect)) IAGraphicRect_setRectFunction, NULL);
    this->transformedRectToRender = IARect_make(0.0f, 0.0f, 100.0f, 100.0f);
    this->transformRectToRender = transformRectToRender;
    this->setupRendering = setupRendering;
}

void IAGraphicRect_makeCopy(IAGraphicRect * this, const IAGraphicRect * graphicRectToCopy){
    *this = *graphicRectToCopy;
}

void IAGraphicRect_setRectFunction(IAGraphicRect * this, IARect rect){
    this->transformRectToRender(this, &rect);
    this->transformedRectToRender = rect;
}

void IAGraphicRect_drawFunction(const IAGraphicRect * this){
    glAssert();
    IARect rectToRender = IAGraphicRect_getRectToRender(this);
	if (IARect_areOverlapping(rectToRender, IARect_make(-1.0f, -1.0f, 2.0f, 2.0f)) == false) {
		return;
	}
    this->setupRendering(this, rectToRender);
    glAssert();
	IAElementArrayBuffer_use(elementArrayBuffer);
    glAssert();
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, (void*)(0));
    glAssert();
}

IARect IAGraphicRect_getRectToRender(const IAGraphicRect * this){
    IASize viewSizeHalf = IAViewPort_getSize();
    viewSizeHalf.width /= 2.0f;
    viewSizeHalf.height /= 2.0f;
    
    IARect rectToRender = this->transformedRectToRender;
    rectToRender.origin.x /= viewSizeHalf.width;
    rectToRender.origin.y /= viewSizeHalf.height;
    rectToRender.size.width /= viewSizeHalf.width;
    rectToRender.size.height /= viewSizeHalf.height;
    rectToRender.origin.x -= 1.0f;
    rectToRender.origin.y -= 1.0f;
    return rectToRender;
}

void IAGraphicRect_terminate(){
    IAElementArrayBuffer_release(elementArrayBuffer);
}


