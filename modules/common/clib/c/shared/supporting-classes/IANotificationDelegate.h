#ifndef IANotificationDelegate_h
#define IANotificationDelegate_h

//@event
typedef struct{
    void * correspondingObject;
    //@exe
    void (*notify)(void * correspondingObject);
} IANotificationDelegate;

#include "IANotificationDelegate+Generated.h"

#endif
