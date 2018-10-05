#ifndef IAFrameAnimationGroupAttributes_h
#define IAFrameAnimationGroupAttributes_h

#include "IAImageContext.h"
#include "IAArray.h"

typedef struct{
    //@get
    IAImageContext * imageContext;
    IAArray names;
    //@get
    int numberOfFrames;
    //@set+get
    int offset;
    //@get
    uint64_t duration;
    
    //@set+get
    bool shouldShowLastFrameForever;
    //@set+get
    bool shouldRepeatAnimation;
    //@set+get
    bool shouldReverseAnimation;
    //@set+get
    bool shouldMakeCopyOfImages;
} IAFrameAnimationGroupAttributes;


void IAFrameAnimationGroupAttributes_init(IAFrameAnimationGroupAttributes *, IAImageContext * imageContext, size_t numberOfAnimations, const char * names[numberOfAnimations], int numberOfFrames, uint64_t duration);
void IAFrameAnimationGroupAttributes_initWithDurationOfSingleFrame(IAFrameAnimationGroupAttributes *, IAImageContext * imageContext, size_t numberOfAnimations, const char * names[numberOfAnimations], int numberOfFrames, uint64_t durationOfSingleFrame);

void IAFrameAnimationGroupAttributes_setNames(IAFrameAnimationGroupAttributes *, size_t numberOfAnimations, const char * names[numberOfAnimations]);

const char * IAFrameAnimationGroupAttributes_getName(const IAFrameAnimationGroupAttributes *, size_t index);
size_t IAFrameAnimationGroupAttributes_getNumberOfAnimations(const IAFrameAnimationGroupAttributes *);

void IAFrameAnimationGroupAttributes_deinit(IAFrameAnimationGroupAttributes *);

#include "IAFrameAnimationGroupAttributes+Generated.h"

#endif
