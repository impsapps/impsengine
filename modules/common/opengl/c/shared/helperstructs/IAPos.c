#include "IALibrary.h"
#include "IAPos.h"

IAPos IAPos_make(int x, int y){
    IAPos pos;
    pos.x = x;
    pos.y = y;
    return pos;
}

bool IAPos_areEqual(IAPos pos1, IAPos pos2){
    if (pos1.x == pos2.x && pos1.y == pos2.y) {
        return true;
    }else{
        return false;
    }
}

