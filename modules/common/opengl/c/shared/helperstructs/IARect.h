#ifndef IARect_h
#define IARect_h

#include <stdbool.h>

#include "IAPoint.h"
#include "IASize.h"

typedef struct{
    IAPoint origin;
    IASize size;
} IARect;

IARect IARect_make(float x, float y, float width, float height);
IARect IARect_makeWithLeftTopPointAndSize(IAPoint point, IASize size);
IARect IARect_makeWithCenterPointAndSize(IAPoint point, IASize size);
IARect IARect_makeWithLeftTopRightBottom(float left, float top, float right, float bottom);
IARect IARect_makeAsOverlappingRect(IARect rect1, IARect rect2);
IARect IARect_makeMinimalSmallerRect(IARect rect);

IARect IARect_getWithNewCenterPoint(IARect rect, IAPoint centerPoint);
IAPoint IARect_getCenterPoint(IARect rect);

bool IARect_isEqual(IARect rect1, IARect rect2);
bool IARect_areOverlapping(IARect rect1, IARect rect2);
bool IARect_isAreaFullyCovered(IARect rect, IARect area);

bool IARect_isTouchingCircle(IARect rect, IAPoint circleOrigin, float circleRadius);

bool IARect_isPointWithin(IARect rect, IAPoint p);

#endif
