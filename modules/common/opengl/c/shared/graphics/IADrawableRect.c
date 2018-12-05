#include "IALibrary.h"
#include "IADrawableRect.h"
#include "IAViewPort.h"

#define CLASSNAME "IADrawableRect"


void IADrawableRect_make(IADrawableRect * this, IADrawable_drawFunction draw, IADrawableRect_setRectFunction setRectNullable){
    IADrawable_make((IADrawable *) this, draw);
    this->setRect = setRectNullable;
    this->rect = IAViewPort_defaultRectForContent;
}

void IADrawableRect_makeCopy(IADrawableRect * this, const IADrawableRect * drawableRectToCopy){			
    IADrawable_makeCopy((IADrawable *) this, (const IADrawable *) drawableRectToCopy);
    this->setRect = drawableRectToCopy->setRect;
    this->rect = drawableRectToCopy->rect;
}

void IADrawableRect_setLeftTopPoint(IADrawableRect * this, IAPoint point){
    IADrawableRect_setRect(this, IARect_makeWithLeftTopPointAndSize(point, this->rect.size));
}

void IADrawableRect_setCenterPoint(IADrawableRect * this, IAPoint point){
    IADrawableRect_setRect(this, IARect_makeWithCenterPointAndSize(point, this->rect.size));
}

void IADrawableRect_setSize(IADrawableRect * this, IASize size){
    IADrawableRect_setRect(this, IARect_makeWithLeftTopPointAndSize(this->rect.origin, size));
}

void IADrawableRect_setRect(IADrawableRect * this, IARect rect){
    this->rect = rect;
    if (this->setRect != NULL){
        this->setRect(this, rect);
    }
}

void IADrawableRect_setLeftTopRightBottom(IADrawableRect * this, float left, float top, float right, float bottom){
    IADrawableRect_setRect(this, IARect_makeWithLeftTopRightBottom(left, top, right, bottom));
}

IAPoint IADrawableRect_getLeftTopPoint(const IADrawableRect * this){
    return this->rect.origin;
}

IAPoint IADrawableRect_getCenterPoint(const IADrawableRect * this){
    return IARect_getCenterPoint(this->rect);
}

float IADrawableRect_getWidth(const IADrawableRect * this){
    return this->rect.size.width;
}

float IADrawableRect_getHeight(const IADrawableRect * this){
    return this->rect.size.height;
}

IASize IADrawableRect_getSize(const IADrawableRect * this){
    return this->rect.size;
}

IARect IADrawableRect_getRect(const IADrawableRect * this){
    return this->rect;
}

