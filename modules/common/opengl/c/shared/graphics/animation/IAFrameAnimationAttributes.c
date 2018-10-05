#include "IALibrary.h"
#include "IAFrameAnimationAttributes.h"
#include "IAAllocationTracking.h"

#define CLASSNAME "IAFrameAnimationAttributes"


void IAFrameAnimationAttributes_init(IAFrameAnimationAttributes * this, IAImageContext * imageContext, const char * name, int numberOfFrames, uint64_t duration){
    *this = (IAFrameAnimationAttributes){
        .imageContext = imageContext,
        .numberOfFrames = numberOfFrames,
        .duration = duration
    };
    IAString_init(&this->name, name);
    IA_incrementInitCount();
}

void IAFrameAnimationAttributes_initWithDurationOfSingleFrame(IAFrameAnimationAttributes * this, IAImageContext * imageContext, const char * name, int numberOfFrames, uint64_t durationOfSingleFrame){
    IAFrameAnimationAttributes_init(this, imageContext, name, numberOfFrames, durationOfSingleFrame * numberOfFrames);
}

void IAFrameAnimationAttributes_setDefaultFrame(IAFrameAnimationAttributes * this, int defaultFrame){
    assert(defaultFrame >= 0 && defaultFrame < this->numberOfFrames && "Invalid default frame. Must be in range of numberOfFrames");
    this->defaultFrame = defaultFrame;
}

void IAFrameAnimationAttributes_setLastAsDefaultFrame(IAFrameAnimationAttributes * this){
    IAFrameAnimationAttributes_setDefaultFrame(this, this->numberOfFrames - 1);
}

void IAFrameAnimationAttributes_deinit(IAFrameAnimationAttributes * this){
    IAString_deinit(&this->name);
    IA_decrementInitCount();
}
