#ifndef IAButtonAttributes_h
#define IAButtonAttributes_h

#include "IAImage.h"

typedef struct IAButton IAButton;

typedef struct{
    //@set+get
    IADrawableRect * normal;
    //@set+get
    IADrawableRect * touched;
    
    //@set+get
    float rectExtensionForTouchBeganLeft;
    //@set+get
    float rectExtensionForTouchBeganTop;
    //@set+get
    float rectExtensionForTouchBeganRight;
    //@set+get
    float rectExtensionForTouchBeganBottom;
    
    //@set+get
    float rectExtensionForTouchMovedOutsideLeft;
    //@set+get
    float rectExtensionForTouchMovedOutsideTop;
    //@set+get
    float rectExtensionForTouchMovedOutsideRight;
    //@set+get
    float rectExtensionForTouchMovedOutsideBottom;

    //@set+get
    int zOrder;
    
    //@set+get
    int tag;
} IAButtonAttributes;


void IAButtonAttributes_make(IAButtonAttributes *);

void IAButtonAttributes_setRectExtensionForTouchBegan(IAButtonAttributes *, float extension);
void IAButtonAttributes_setRectExtensionForTouchMovedOutside(IAButtonAttributes *, float extension);

#include "IAButtonAttributes+Generated.h"

#endif
