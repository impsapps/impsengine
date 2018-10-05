#ifndef IAViewAttributes_h
#define IAViewAttributes_h

#include <stdint.h>


typedef void (*IAViewAttributes_setArgs)(void * correspondingView, const void * args);
typedef void (*IAViewAttributes_onFadeInStart)(void * correspondingView, uint64_t startTime, uint64_t duration);
typedef void (*IAViewAttributes_drawFadeIn)(void * correspondingView, uint64_t startTime, uint64_t duration, uint64_t currentTime);
typedef void (*IAViewAttributes_onFadeInFinished)(void * correspondingView, uint64_t startTime, uint64_t duration, uint64_t endTime);
typedef void (*IAViewAttributes_drawFunction)(void * correspondingView, uint64_t currentTime);
typedef void (*IAViewAttributes_onFadeOutStart)(void * correspondingView, uint64_t startTime, uint64_t duration);
typedef void (*IAViewAttributes_drawFadeOut)(void * correspondingView, uint64_t startTime, uint64_t duration, uint64_t currentTime);
typedef void (*IAViewAttributes_onFadeOutFinished)(void *correspondingView, uint64_t startTime, uint64_t duration, uint64_t endTime);

typedef struct{
    //@get
    void * correspondingView;
    //@set+get
    IAViewAttributes_setArgs setArgsFunction;
    //@set+get
    IAViewAttributes_onFadeInStart onFadeInStartFunction;
    //@set+get
    IAViewAttributes_drawFadeIn drawFadeInFunction;
    //@set+get
    IAViewAttributes_onFadeInFinished onFadeInFinishedFunction;
    //@set+get
    IAViewAttributes_drawFunction drawFunction;
    //@set+get
    IAViewAttributes_onFadeOutStart onFadeOutStartFunction;
    //@set+get
    IAViewAttributes_drawFadeOut drawFadeOutFunction;
    //@set+get
    IAViewAttributes_onFadeOutFinished onFadeOutFinishedFunction;
    //@set+get
    int zOrder;
} IAViewAttributes;


void IAViewAttributes_make(IAViewAttributes *, void * correspondingView);

#include "IAViewAttributes+Generated.h"

#endif
