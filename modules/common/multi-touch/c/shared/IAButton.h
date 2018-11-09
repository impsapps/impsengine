#ifndef IAButton_h
#define IAButton_h

#include <stdbool.h>

#include "IAImage.h"
#include "IATouchDelegate.h"
#include "IAButtonAttributes.h"
#include "IAButtonEvent.h"

typedef struct IAButton IAButton;

struct IAButton{
    //@extend
    IADrawableRect drawableRect;
    IADrawableRect * normal;
    IADrawableRect * touched;
    
    IATouchDelegate touchDelegate;
    IAStructArrayList_IATouch * validTouches;
    
    //@get
    float rectExtensionForTouchBeganLeft;
    //@get
    float rectExtensionForTouchBeganTop;
    //@get
    float rectExtensionForTouchBeganRight;
    //@get
    float rectExtensionForTouchBeganBottom;
    
    //@get
    float rectExtensionForTouchMovedOutsideLeft;
    //@get
    float rectExtensionForTouchMovedOutsideTop;
    //@get
    float rectExtensionForTouchMovedOutsideRight;
    //@get
    float rectExtensionForTouchMovedOutsideBottom;
    
    //@get
    bool isClickable;

    //@register
    IAButtonEvent touchEvents;
    
    //@get
    int tag;
};


void IAButton_init(IAButton *, const IAButtonAttributes * attributes);

void IAButton_setIsClickable(IAButton *, bool isClickable);

bool IAButton_isTouched(const IAButton *);

void IAButton_drawButtonNormal(const IAButton *);
void IAButton_drawButtonTouched(const IAButton *);

void IAButton_deinit(IAButton *);

#include "IAButton+Generated.h"

#endif
