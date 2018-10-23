#ifndef IADrawableRect_h
#define IADrawableRect_h

#include <stdbool.h>

#include "IADrawable.h"
#include "IAPoint.h"
#include "IASize.h"
#include "IARect.h"

typedef struct IADrawableRect IADrawableRect;

typedef void (*IADrawableRect_setRectFunction)(IADrawableRect *, IARect);
typedef IASize (*IADrawableRect_getMinSizeNeededNullableFunction)(const IADrawableRect *);

struct IADrawableRect{
    //@extend
    IADrawable drawable;
	IADrawableRect_setRectFunction setRect;
	IADrawableRect_getMinSizeNeededNullableFunction getMinSizeNeededNullable;
    IARect rect;
};


void IADrawableRect_make(IADrawableRect *, IADrawable_drawFunction draw, IADrawableRect_setRectFunction setRect, IADrawableRect_getMinSizeNeededNullableFunction getMinSizeNeededNullable);
void IADrawableRect_makeCopy(IADrawableRect *, const IADrawableRect * drawableRectToCopy);

void IADrawableRect_setLeftTopPoint(IADrawableRect *, IAPoint point);
void IADrawableRect_setCenterPoint(IADrawableRect *, IAPoint point);
void IADrawableRect_setSize(IADrawableRect *, IASize size);
void IADrawableRect_setRect(IADrawableRect *, IARect rect);
void IADrawableRect_setLeftTopRightBottom(IADrawableRect *, float left, float top, float right, float bottom);

IAPoint IADrawableRect_getLeftTopPoint(const IADrawableRect *);
IAPoint IADrawableRect_getCenterPoint(const IADrawableRect *);
float IADrawableRect_getWidth(const IADrawableRect *);
float IADrawableRect_getHeight(const IADrawableRect *);
IASize IADrawableRect_getSize(const IADrawableRect *);
IARect IADrawableRect_getRect(const IADrawableRect *);

IASize IADrawableRect_getMinSizeNeeded(const IADrawableRect *);

#include "IADrawableRect+Generated.h"

#endif
