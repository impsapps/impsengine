#ifndef IAIntent_h
#define IAIntent_h

#include "IAView.h"

typedef struct{
    //@get
    IAView * view;
    //@getAsConst
    void * viewArgs;
    //@set+get
    uint64_t switchDuration;
} IAIntent;


void IAIntent_init(IAIntent * this, IAView * view);

void IAIntent_setViewArgs(IAIntent * this, const void * viewArgs, size_t sizeOfViewArgs);

void IAIntent_deinit(IAIntent * this);

#include "IAIntent+Generated.h"

#endif
