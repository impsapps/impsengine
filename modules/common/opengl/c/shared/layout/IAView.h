#ifndef IAView_h
#define IAView_h

#include "IAViewAttributes.h"

typedef struct{
    void * correspondingView;
    void (*setArgs)(void * correspondingView, const void * args);
    void (*onFadeInStart)(void * correspondingView, uint64_t startTime, uint64_t duration);
    void (*drawFadeIn)(void * correspondingView, uint64_t startTime, uint64_t duration, uint64_t currentTime);
    void (*onFadeInFinished)(void * correspondingView, uint64_t startTime, uint64_t duration, uint64_t endTime);
    void (*draw)(void * correspondingView, uint64_t currentTime);
    void (*onFadeOutStart)(void * correspondingView, uint64_t startTime, uint64_t duration);
    void (*drawFadeOut)(void * correspondingView, uint64_t startTime, uint64_t duration, uint64_t currentTime);
    void (*onFadeOutFinished)(void *correspondingView, uint64_t startTime, uint64_t duration, uint64_t endTime);
    //@get
    int zOrder;
    
    /// This variable will be updated before "onFadeInStart" and "onFadeInFinished" on the corresponding view are called.
    //@get
    bool isFadingIn;
    /// This variable will be updated before "onFadeOutStart" and "onFadeOutFinished" on the corresponding view are called.
    //@get
    bool isFadingOut;
    /**
     * This variable is true if view faded in and is now shown. As soon as "onFadeOutStart" is called the variable is set to "false".
     * It will be updated before "onFadeInFinished" and "onFadeOutStart" on the corresponding view are called.
     */
    //@get
    bool isShown;
    
    //@getAsConstRef
    char viewName[21];
} IAView;


void IAView_make(IAView *, const char * viewName, const IAViewAttributes * attributes);

bool IAView_isIdle(const IAView *);

void IAView_setArgs(const IAView *, const void * args);

void IAView_onFadeInStart(IAView *, uint64_t startTime, uint64_t duration);
void IAView_drawFadeIn(IAView *, uint64_t startTime, uint64_t duration, uint64_t currentTime);
void IAView_onFadeInFinished(IAView *, uint64_t startTime, uint64_t duration, uint64_t endTime);
void IAView_draw(IAView *, uint64_t currentTime);
void IAView_onFadeOutStart(IAView *, uint64_t startTime, uint64_t duration);
void IAView_drawFadeOut(IAView *, uint64_t startTime, uint64_t duration, uint64_t currentTime);
void IAView_onFadeOutFinished(IAView *, uint64_t startTime, uint64_t duration, uint64_t endTime);

#include "IAView+Generated.h"

#endif
