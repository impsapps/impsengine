#include <string.h>
#include "IALibrary.h"
#include "IAPoint.h"

IAPoint IAPoint_make(float x, float y){
    IAPoint point;
    point.x = x;
    point.y = y;
    return point;
}

bool IAPoint_isEqual(IAPoint p1, IAPoint p2){
    if (memcmp(&p1, &p2, sizeof(IAPoint)) == 0) {
        return true;
    }else{
        return false;
    }
}

