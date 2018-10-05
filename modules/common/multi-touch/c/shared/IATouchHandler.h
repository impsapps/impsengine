#ifndef IATouchHandler_h
#define IATouchHandler_h

#include <stdbool.h>

#include "IATouchDelegate.h"
#include "IAArrayList.h"
#include "IAPoint.h"
#include "IARect.h"
#include "IATouch.h"

typedef struct{
    //@extend
    IAObject base;
    //@get
    IATouch touch;
    IAArrayList touchDelegates;
} IATouchHandler;


void IATouchHandler_init(IATouchHandler *, long touchId, IAPoint location);
void IATouchHandler_reinit(IATouchHandler *, long touchId, IAPoint location);

void IATouchHandler_setTouchLocation(IATouchHandler *, IAPoint newLocation);

void IATouchHandler_registerTouchDelegate(IATouchHandler *, IATouchDelegate * touchDelegate);
void IATouchHandler_prepareTouchDelegates(IATouchHandler *);
void IATouchHandler_unregisterTouchDelegate(IATouchHandler *, IATouchDelegate * touchDelegate);

void IATouchHandler_deinit(IATouchHandler *);

#include "IATouchHandler+Generated.h"

#endif
