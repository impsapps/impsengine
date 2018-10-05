#include <assert.h>
#include "IAFrameAnimationCalculation.h"


size_t IAFrameAnimationCalculation_calculateFrame(size_t numberOfFrames,
                                                  uint64_t startTime,
                                                  uint64_t currentTime,
                                                  uint64_t duration){
    size_t frame = IAFrameAnimationCalculation_calculateFrameWithOptions(numberOfFrames,
                                                                         startTime,
                                                                         currentTime,
                                                                         duration,
                                                                         false,
                                                                         false,
                                                                         false);
    return frame;
}

size_t IAFrameAnimationCalculation_calculateFrameWithOptions(size_t numberOfFrames,
                                                             uint64_t startTime,
                                                             uint64_t currentTime,
                                                             uint64_t duration,
                                                             bool shouldShowLastFrameForever,
                                                             bool shouldRepeatAnimation,
                                                             bool shouldReverseAnimation){
    assert(numberOfFrames > 0);

    if (currentTime < startTime) {
        if (shouldReverseAnimation) {
            return numberOfFrames - 1;
        }else{
            return 0;
        }
    }
    
    uint64_t timeDifference = currentTime - startTime;
    size_t frame = timeDifference / (((float) duration) / ((float) numberOfFrames));
    
    if (frame >= numberOfFrames) {
        if (shouldShowLastFrameForever) {
            frame = numberOfFrames - 1;
        }else if(shouldRepeatAnimation){
            frame %= numberOfFrames;
        }else{
            frame = 0;
        }
    }
    
    if (shouldReverseAnimation) {
        frame = numberOfFrames - 1 - frame;
    }
    return frame;
}

bool IAFrameAnimationCalculation_isAnimating(uint64_t currentTime, uint64_t finishTime){
    if (currentTime < finishTime) {
        return true;
    }else{
        return false;
    }
}
