#ifndef IAFrameAnimation_h
#define IAFrameAnimation_h

#include "IADrawableRect.h"
#include "IAImageContext.h"
#include "IAFrameAnimationAttributes.h"
#include "IACompositedAnimationDelegate.h"

typedef struct{
    //@extend
    IADrawableRect drawableRect;
    IAArrayList * images;
    //@get
    int numberOfFrames;
    //@get
    uint64_t duration;
    
    int defaultFrame;
    
    bool shouldShowLastFrameForever;
    bool shouldRepeatAnimation;
    bool shouldReverseAnimation;
    
    //@get
    uint64_t startTime;
    //@set
    uint64_t currentTime;
    //@get
    bool isStarted;
    
    bool areImagesCopied;
    
    //@getAsRef
    IACompositedAnimationDelegate animationDelegate;
} IAFrameAnimation;


void IAFrameAnimation_init(IAFrameAnimation *, const IAFrameAnimationAttributes * animationAttributes);

void IAFrameAnimation_setAlpha(IAFrameAnimation *, int alpha);
void IAFrameAnimation_setOverlayingColor(IAFrameAnimation *, IAColor overlayingColor);

void IAFrameAnimation_flipHorizontally(IAFrameAnimation *);
void IAFrameAnimation_flipVertically(IAFrameAnimation *);

void IAFrameAnimation_setStartTime(IAFrameAnimation *, uint64_t startTime);

IAImage * IAFrameAnimation_getCurrentImage(const IAFrameAnimation *);
size_t IAFrameAnimation_getCurrentFrame(const IAFrameAnimation *);

IAImage * IAFrameAnimation_getImage(const IAFrameAnimation *, size_t frame);
const IAArrayList * IAFrameAnimation_getImages(const IAFrameAnimation *);

bool IAFrameAnimation_isAnimating(const IAFrameAnimation *);
uint64_t IAFrameAnimation_getFinishTime(const IAFrameAnimation *);

void IAFrameAnimation_stop(IAFrameAnimation *);

void IAFrameAnimation_drawFrame(const IAFrameAnimation *, size_t frame);

void IAFrameAnimation_deinit(IAFrameAnimation *);

#include "IAFrameAnimation+Generated.h"

#endif
