//
//  IAFrameAnimation.c
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 21.05.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAFrameAnimation.h"
#include "IAArrayListIterator.h"
#include "IAFrameAnimationCalculation.h"
#include "IACharArray.h"

#define CLASSNAME "IAFrameAnimation"


void IAFrameAnimation_drawFunction(const IAFrameAnimation * this);
void IAFrameAnimation_setRectFunction(IAFrameAnimation * this, IARect rect);


void IAFrameAnimation_iterateOverImages(const IAFrameAnimation * this, void * data, void(*iterateFunction) (IAImage *, void *));


void IAFrameAnimation_init(IAFrameAnimation * this, const IAFrameAnimationAttributes * animationAttributes){
    IADrawableRect_make((IADrawableRect *) this, (void (*)(const IADrawable *)) IAFrameAnimation_drawFunction, (void (*)(IADrawableRect *, IARect)) IAFrameAnimation_setRectFunction);
    this->numberOfFrames = IAFrameAnimationAttributes_getNumberOfFrames(animationAttributes);
    this->duration = IAFrameAnimationAttributes_getDuration(animationAttributes);
    
    this->images = IAArrayList_new(this->numberOfFrames);
    const char * name = (IAFrameAnimationAttributes_getName(animationAttributes));
    int offset = IAFrameAnimationAttributes_getOffset(animationAttributes);
    
    char str[strlen(name) + IA_MAX_BUFFER_INT];
    IAImageContext * context = IAFrameAnimationAttributes_getImageContext(animationAttributes);
    bool shouldMakeCopyOfImages = IAFrameAnimationAttributes_shouldMakeCopyOfImages(animationAttributes);
    for (int i = offset; i < this->numberOfFrames + offset; i++) {
        IACharArray_setWithFormat(str, "%s%d", name, i);
        IAImage * image = IAImageContext_getImage(context, str);
        if (shouldMakeCopyOfImages) {
            image = IAImage_newCopy(image);
        }
        IAArrayList_add(this->images, image);
    }
    
    this->defaultFrame = IAFrameAnimationAttributes_getDefaultFrame(animationAttributes);
    
    this->shouldShowLastFrameForever = IAFrameAnimationAttributes_shouldShowLastFrameForever(animationAttributes);
    this->shouldRepeatAnimation = IAFrameAnimationAttributes_shouldRepeatAnimation(animationAttributes);
    this->shouldReverseAnimation = IAFrameAnimationAttributes_shouldReverseAnimation(animationAttributes);
    
    this->startTime = 0;
    this->currentTime = 0;
    this->isStarted = false;
    
    this->areImagesCopied = shouldMakeCopyOfImages;
    
    IACompositedAnimationDelegateAttributes delegateAttributes;
    IACompositedAnimationDelegateAttributes_make(&delegateAttributes, (IADrawable *) this, (uint64_t (*)(IADrawable *)) IAFrameAnimation_getDuration, (void (*)(IADrawable *)) IAFrameAnimation_release);
    IACompositedAnimationDelegateAttributes_setSetStartTimeFunction(&delegateAttributes, (void (*)(IADrawable *, uint64_t)) IAFrameAnimation_setStartTime);
    IACompositedAnimationDelegateAttributes_setSetCurrentTimeFunction(&delegateAttributes, (void (*)(IADrawable *, uint64_t)) IAFrameAnimation_setCurrentTime);
    IACompositedAnimationDelegate_make(&this->animationDelegate, &delegateAttributes);
    
    IA_incrementInitCount();
}

void IAFrameAnimation_drawFunction(const IAFrameAnimation * this){
    IAImage * currentImage = IAFrameAnimation_getCurrentImage(this);
    IAImage_draw(currentImage);
}

static void IAFrameAnimation_setRectOfImage(IAImage * image, IARect * rect){
    IAImage_setRect(image, *rect);
}

void IAFrameAnimation_setRectFunction(IAFrameAnimation * this, IARect rect){
    IAFrameAnimation_iterateOverImages(this, &rect, (void(*)(IAImage *, void *)) IAFrameAnimation_setRectOfImage);
}

static void IAFrameAnimation_setAlphaOfImage(IAImage * image, int * alpha){
    IAImage_setAlpha(image, *alpha);
}

void IAFrameAnimation_setAlpha(IAFrameAnimation * this, int alpha){
    IAFrameAnimation_iterateOverImages(this, &alpha, (void(*)(IAImage *, void *)) IAFrameAnimation_setAlphaOfImage);
}

static void IAFrameAnimation_setOverlayingColorOfImage(IAImage * image, IAColor * overlayingColor){
    IAImage_setOverlayingColor(image, *overlayingColor);
}

void IAFrameAnimation_setOverlayingColor(IAFrameAnimation * this, IAColor overlayingColor){
    IAFrameAnimation_iterateOverImages(this, &overlayingColor, (void(*)(IAImage *, void *)) IAFrameAnimation_setOverlayingColorOfImage);
}

static void IAFrameAnimation_flipImageHorizontally(IAImage * image, void * null){
    IAImage_flipHorizontally(image);
}

void IAFrameAnimation_flipHorizontally(IAFrameAnimation * this){
    IAFrameAnimation_iterateOverImages(this, NULL, (void(*)(IAImage *, void *)) IAFrameAnimation_flipImageHorizontally);
}

static void IAFrameAnimation_flipImageVertically(IAImage * image, void * null){
    IAImage_flipVertically(image);
}

void IAFrameAnimation_flipVertically(IAFrameAnimation * this){
    IAFrameAnimation_iterateOverImages(this, NULL, (void(*)(IAImage *, void *)) IAFrameAnimation_flipImageVertically);
}

void IAFrameAnimation_setStartTime(IAFrameAnimation * this, uint64_t startTime){
    this->isStarted = true;
    this->startTime = startTime;
}

void IAFrameAnimation_iterateOverImages(const IAFrameAnimation * this, void * data, void(*iterateFunction) (IAImage *, void *)){
    IAImage * image;
    foreach (image in arrayList(this->images)) {
        iterateFunction(image, data);
    }
}

IAImage * IAFrameAnimation_getCurrentImage(const IAFrameAnimation * this){
    size_t currentFrame = IAFrameAnimation_getCurrentFrame(this);
    IAImage * currentImage = IAFrameAnimation_getImage(this, currentFrame);
    return currentImage;
}

size_t IAFrameAnimation_getCurrentFrame(const IAFrameAnimation * this){
    if (this->isStarted == false){
        return this->defaultFrame;
    }
    size_t frame = IAFrameAnimationCalculation_calculateFrameWithOptions(this->numberOfFrames,
                                                                         this->startTime,
                                                                         this->currentTime,
                                                                         this->duration,
                                                                         this->shouldShowLastFrameForever,
                                                                         this->shouldRepeatAnimation,
                                                                         this->shouldReverseAnimation);
    return frame;
}

IAImage * IAFrameAnimation_getImage(const IAFrameAnimation * this, size_t frame){
    IAImage * image = IAArrayList_get(this->images, frame);
    return image;
}

const IAArrayList * IAFrameAnimation_getImages(const IAFrameAnimation * this){
    return this->images;
}

bool IAFrameAnimation_isAnimating(const IAFrameAnimation * this){
    if (this->isStarted && IAFrameAnimationCalculation_isAnimating(this->currentTime, IAFrameAnimation_getFinishTime(this))) {
        return true;
    }else{
        return false;
    }
}

uint64_t IAFrameAnimation_getFinishTime(const IAFrameAnimation * this){
    debugAssert(this->isStarted == true);
    return this->startTime + this->duration;
}

void IAFrameAnimation_stop(IAFrameAnimation * this){
    this->isStarted = false;
}

void IAFrameAnimation_drawFrame(const IAFrameAnimation * this, size_t frame){
    IAImage * image = IAFrameAnimation_getImage(this, frame);
    IAImage_draw(image);
}

void IAFrameAnimation_deinit(IAFrameAnimation * this){
    if (this->areImagesCopied) {
        IAArrayList_callFunctionOnAllObjects(this->images, (void (*)(void *)) IAImage_release);
    }
    IAArrayList_release(this->images);
    IA_decrementInitCount();
}


