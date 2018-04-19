//
//  IAFrameAnimationCalculation.h
//  OpenGL
//
//  Created by Konstantin Merker on 18/11/17.
//  Copyright © 2017 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAFrameAnimationCalculation_h
#define IAFrameAnimationCalculation_h

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>


size_t IAFrameAnimationCalculation_calculateFrame(size_t numberOfFrames,
                                                  uint64_t startTime,
                                                  uint64_t currentTime,
                                                  uint64_t duration);

size_t IAFrameAnimationCalculation_calculateFrameWithOptions(size_t numberOfFrames,
                                                             uint64_t startTime,
                                                             uint64_t currentTime,
                                                             uint64_t duration,
                                                             bool shouldShowLastFrameForever,
                                                             bool shouldRepeatAnimation,
                                                             bool shouldReverseAnimation);

bool IAFrameAnimationCalculation_isAnimating(uint64_t currentTime, uint64_t finishTime);

#endif
