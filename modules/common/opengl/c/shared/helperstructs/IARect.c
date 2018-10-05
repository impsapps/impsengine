#include "IALibrary.h"
#include "IARect.h"
#include <string.h>
#include <math.h>


bool IARect_isTouchingCircleLeft(IARect rect, IAPoint circleOrigin, float circleRadius);
bool IARect_isTouchingCircleTop(IARect rect, IAPoint circleOrigin, float circleRadius);
bool IARect_isTouchingCircleRight(IARect rect, IAPoint circleOrigin, float circleRadius);
bool IARect_isTouchingCircleBottom(IARect rect, IAPoint circleOrigin, float circleRadius);

bool IARect_isTouchingCircleTopLeft(IARect rect, IAPoint circleOrigin, float circleRadius);
bool IARect_isTouchingCircleTopRight(IARect rect, IAPoint circleOrigin, float circleRadius);
bool IARect_isTouchingCircleBottomLeft(IARect rect, IAPoint circleOrigin, float circleRadius);
bool IARect_isTouchingCircleBottomRight(IARect rect, IAPoint circleOrigin, float circleRadius);

bool IARect_isPointInRadius(IAPoint point, IAPoint origin, float radius);


IARect IARect_make(float x, float y, float width, float height){
    IARect rect;
    rect.origin.x = x;
    rect.origin.y = y;
    rect.size.width = width;
    rect.size.height = height;
    return rect;
}

IARect IARect_makeWithLeftTopPointAndSize(IAPoint point, IASize size){
    IARect rect;
    rect.origin = point;
    rect.size = size;
    return rect;
}

IARect IARect_makeWithCenterPointAndSize(IAPoint point, IASize size){
    IARect rect;
    rect.origin = point;
    rect.origin.x -= size.width / 2.0f;
    rect.origin.y -= size.height / 2.0f;
    rect.size = size;
    return rect;
}

IARect IARect_makeWithLeftTopRightBottom(float left, float top, float right, float bottom){
    IARect rect;
    rect.origin.x = left;
    rect.origin.y = top;
    rect.size.width = right - left;
    rect.size.height = bottom - top;
    return rect;
}

IARect IARect_makeAsOverlappingRect(IARect rect1, IARect rect2){
    float left = rect1.origin.x > rect2.origin.x ? rect1.origin.x : rect2.origin.x;
    float top = rect1.origin.y > rect2.origin.y ? rect1.origin.y : rect2.origin.y;
    float rect1Right = rect1.origin.x + rect1.size.width;
    float rect2Right = rect2.origin.x + rect2.size.width;
    float right = rect1Right < rect2Right ? rect1Right : rect2Right;
    float rect1Bottom = rect1.origin.y + rect1.size.height;
    float rect2Bottom = rect2.origin.y + rect2.size.height;
    float bottom = rect1Bottom < rect2Bottom ? rect1Bottom : rect2Bottom;
    if (right < left) {
        right = left;
    }
    if (bottom < top) {
        bottom = top;
    }
    return IARect_makeWithLeftTopRightBottom(left, top, right, bottom);
}

IARect IARect_makeMinimalSmallerRect(IARect rect){
    float changeBy = 0.00001f;
    rect.origin.x += changeBy;
    rect.origin.y += changeBy;
    rect.size.width -= changeBy * 2.0f;
    rect.size.height -= changeBy * 2.0f;
    return rect;
}

IARect IARect_getWithNewCenterPoint(IARect rect, IAPoint centerPoint){
    rect.origin = centerPoint;
    rect.origin.x -= rect.size.width / 2.0f;
    rect.origin.y -= rect.size.height / 2.0f;
    return rect;
}

IAPoint IARect_getCenterPoint(IARect rect){
    IAPoint point = rect.origin;
    point.x += rect.size.width / 2.0f;
    point.y += rect.size.height / 2.0f;
    return point;
}

float IARect_getLeft(IARect rect){
    return rect.origin.x;
}

float IARect_getTop(IARect rect){
    return rect.origin.y;
}

float IARect_getRight(IARect rect){
    return rect.origin.x + rect.size.width;
}

float IARect_getBottom(IARect rect){
    return rect.origin.y + rect.size.height;
}

bool IARect_isEqual(IARect rect1, IARect rect2){
    if (memcmp(&rect1, &rect2, sizeof(IARect)) == 0) {
        return true;
    }else{
        return false;
    }
}

bool IARect_areOverlapping(IARect rect1, IARect rect2){
    if (rect1.origin.x + rect1.size.width < rect2.origin.x) {
        return false;
    }
    if (rect2.origin.x + rect2.size.width < rect1.origin.x) {
        return false;
    }
    if (rect1.origin.y + rect1.size.height < rect2.origin.y) {
        return false;
    }
    if (rect2.origin.y + rect2.size.height < rect1.origin.y) {
        return false;
    }
    return true;
}

bool IARect_isTouchingCircle(IARect rect, IAPoint circleOrigin, float circleRadius){
    float left = circleOrigin.x - circleRadius;
    float top = circleOrigin.y - circleRadius;
    float right = circleOrigin.x + circleRadius;
    float bottom = circleOrigin.y + circleRadius;
    IARect circleRect = IARect_makeWithLeftTopRightBottom(left, top, right, bottom);
    if (IARect_areOverlapping(rect, circleRect) == false) {
        return false;
    }else{
        int positionX;
        if (circleOrigin.x < rect.origin.x) {
            //left
            positionX = 0;
        }else if(circleOrigin.x > rect.origin.x + rect.size.width){
            //right
            positionX = 2;
        }else{
            //center
            positionX = 1;
        }
        
        int positionY;
        if (circleOrigin.y < rect.origin.y) {
            //top
            positionY = 0;
        }else if(circleOrigin.y > rect.origin.y + rect.size.height){
            //bottom
            positionY = 2;
        }else{
            //center
            positionY = 1;
        }
        
        switch (positionX) {
            case 0:
                switch (positionY) {
                    case 0:
                        return IARect_isTouchingCircleTopLeft(rect, circleOrigin, circleRadius);
                    case 1:
                        return IARect_isTouchingCircleLeft(rect, circleOrigin, circleRadius);
                    case 2:
                        return IARect_isTouchingCircleBottomLeft(rect, circleOrigin, circleRadius);
                    default:
                        break;
                }
                break;
            case 1:
                switch (positionY) {
                    case 0:
                        return IARect_isTouchingCircleTop(rect, circleOrigin, circleRadius);
                    case 1:
                        return true;
                    case 2:
                        return IARect_isTouchingCircleBottom(rect, circleOrigin, circleRadius);
                    default:
                        break;
                }
                break;
            case 2:
                switch (positionY) {
                    case 0:
                        return IARect_isTouchingCircleTopRight(rect, circleOrigin, circleRadius);
                    case 1:
                        return IARect_isTouchingCircleRight(rect, circleOrigin, circleRadius);
                    case 2:
                        return IARect_isTouchingCircleBottomRight(rect, circleOrigin, circleRadius);
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
    return false;
}

bool IARect_isTouchingCircleLeft(IARect rect, IAPoint circleOrigin, float circleRadius){
    float circleRight = circleOrigin.x + circleRadius;
    if (circleRight >= rect.origin.x) {
        return true;
    }else{
        return false;
    }
}

bool IARect_isTouchingCircleTop(IARect rect, IAPoint circleOrigin, float circleRadius){
    float circleBottom = circleOrigin.y + circleRadius;
    if (circleBottom >= rect.origin.y) {
        return true;
    }else{
        return false;
    }
}

bool IARect_isTouchingCircleRight(IARect rect, IAPoint circleOrigin, float circleRadius){
    float circleLeft = circleOrigin.x - circleRadius;
    if (circleLeft <= rect.origin.x + rect.size.width) {
        return true;
    }else{
        return false;
    }
}

bool IARect_isTouchingCircleBottom(IARect rect, IAPoint circleOrigin, float circleRadius){
    float circleTop = circleOrigin.y - circleRadius;
    if (circleTop <= rect.origin.y + rect.size.height) {
        return true;
    }else{
        return false;
    }
}

bool IARect_isTouchingCircleTopLeft(IARect rect, IAPoint circleOrigin, float circleRadius){
    IAPoint point = rect.origin;
    return IARect_isPointInRadius(point, circleOrigin, circleRadius);
}

bool IARect_isTouchingCircleTopRight(IARect rect, IAPoint circleOrigin, float circleRadius){
    IAPoint point = IAPoint_make(rect.origin.x + rect.size.width, rect.origin.y);
    return IARect_isPointInRadius(point, circleOrigin, circleRadius);
}

bool IARect_isTouchingCircleBottomLeft(IARect rect, IAPoint circleOrigin, float circleRadius){
    IAPoint point = IAPoint_make(rect.origin.x, rect.origin.y + rect.size.height);
    return IARect_isPointInRadius(point, circleOrigin, circleRadius);
}

bool IARect_isTouchingCircleBottomRight(IARect rect, IAPoint circleOrigin, float circleRadius){
    IAPoint point = IAPoint_make(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height);
    return IARect_isPointInRadius(point, circleOrigin, circleRadius);
}

bool IARect_isPointInRadius(IAPoint point, IAPoint origin, float radius){
    float x = (point.x - origin.x);
    float y = (point.y - origin.y);
    x = x * x;
    y = y * y;
    double distance = sqrt(x+y);
    if (distance <= radius) {
        return true;
    }else{
        return false;
    }
}

bool IARect_isPointWithin(IARect rect, IAPoint p){
    if (rect.origin.x <= p.x
        && rect.origin.y <= p.y
        && rect.origin.x + rect.size.width >= p.x
        && rect.origin.y + rect.size.height >= p.y) {
        return true;
    }else{
        return false;
    }
}

