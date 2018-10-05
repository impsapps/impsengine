#ifndef IAFrameAnimationAttributes_h
#define IAFrameAnimationAttributes_h

#include "IAImageContext.h"

typedef struct{
    //@get
    IAImageContext * imageContext;
    //@setAsCharArray+getAsCharArray
    IAString name;
    //@get
    int numberOfFrames;
    //@set+get
    int offset;
    //@get
    uint64_t duration;
    
    //@get
    int defaultFrame;
    
    //@set+get
    bool shouldShowLastFrameForever;
    //@set+get
    bool shouldRepeatAnimation;
    //@set+get
    bool shouldReverseAnimation;
    
    //@set+get
    bool shouldMakeCopyOfImages;
} IAFrameAnimationAttributes;


void IAFrameAnimationAttributes_init(IAFrameAnimationAttributes *, IAImageContext * imageContext, const char * name, int numberOfFrames, uint64_t duration);
void IAFrameAnimationAttributes_initWithDurationOfSingleFrame(IAFrameAnimationAttributes *, IAImageContext * imageContext, const char * name, int numberOfFrames, uint64_t durationOfSingleFrame);

void IAFrameAnimationAttributes_setDefaultFrame(IAFrameAnimationAttributes * this, int defaultFrame);
void IAFrameAnimationAttributes_setLastAsDefaultFrame(IAFrameAnimationAttributes * this);

void IAFrameAnimationAttributes_deinit(IAFrameAnimationAttributes *);

#include "IAFrameAnimationAttributes+Generated.h"

#endif
