#include "IALibrary.h"
#include "IASize.h"

IASize IASize_make(float width, float height){
    IASize  size;
    size.width = width;
    size.height = height;
    return size;
}

IASize IASize_makeSquared(float length){
    IASize  size;
    size.width = length;
    size.height = length;
    return size;
}

IASize IASize_makeWithFixedHeight(IASize originalSize, float fixedHeight){
    IASize size = IASize_make(originalSize.width / originalSize.height * fixedHeight, fixedHeight);
    return size;
}

IASize IASize_makeWithFixedWidth(IASize originalSize, float fixedWidth){
    IASize size = IASize_make(fixedWidth, originalSize.height / originalSize.width * fixedWidth );
    return size;
}

bool IASize_isAreaNotZero(IASize size){
    if (size.width * size.height == 0.0f) {
        return false;
    }else{
        return true;
    }
}

