#include "IALibrary.h"
#include "IAFrameAnimationGroup.h"

#define CLASSNAME "IAFrameAnimationGroup"


static void IAFrameAnimationGroup_drawFunction(const IAFrameAnimationGroup * this){
    IAFrameAnimation * animation;
    foreach (animation in array(&this->frameAnimations)){
        IAFrameAnimation_draw(animation);
    }
}

static void IAFrameAnimationGroup_setRectFunction(IAFrameAnimationGroup * this, IARect rect){
    IAFrameAnimation * animation;
    foreach (animation in array(&this->frameAnimations)){
        IAFrameAnimation_setRect(animation, rect);
    }
}

void IAFrameAnimationGroup_init(IAFrameAnimationGroup * this, const IAFrameAnimationGroupAttributes * attr){
    IADrawableRect_make((IADrawableRect *) this, (void (*)(const IADrawable *)) IAFrameAnimationGroup_drawFunction, (void (*)(IADrawableRect *, IARect)) IAFrameAnimationGroup_setRectFunction, NULL);
    size_t numberOfAnimations = IAFrameAnimationGroupAttributes_getNumberOfAnimations(attr);
    IAArray_init(&this->frameAnimations, numberOfAnimations);
    
    IAFrameAnimationAttributes frameAnimationAttr;
    IAFrameAnimationAttributes_init(&frameAnimationAttr,
                                    IAFrameAnimationGroupAttributes_getImageContext(attr),
                                    NULL,
                                    IAFrameAnimationGroupAttributes_getNumberOfFrames(attr),
                                    IAFrameAnimationGroupAttributes_getDuration(attr));
    IAFrameAnimationAttributes_setOffset(&frameAnimationAttr,
                                         IAFrameAnimationGroupAttributes_getOffset(attr));
    
    IAFrameAnimationAttributes_setShouldShowLastFrameForever(&frameAnimationAttr,
                                                             IAFrameAnimationGroupAttributes_shouldShowLastFrameForever(attr));
    IAFrameAnimationAttributes_setShouldRepeatAnimation(&frameAnimationAttr,
                                                        IAFrameAnimationGroupAttributes_shouldRepeatAnimation(attr));
    IAFrameAnimationAttributes_setShouldReverseAnimation(&frameAnimationAttr,
                                                         IAFrameAnimationGroupAttributes_shouldReverseAnimation(attr));
    IAFrameAnimationAttributes_setShouldMakeCopyOfImages(&frameAnimationAttr,
                                                         IAFrameAnimationGroupAttributes_shouldMakeCopyOfImages(attr));
    
    for (size_t i = 0; i < numberOfAnimations; i++) {
        const char * nameOfAnimation = IAFrameAnimationGroupAttributes_getName(attr, i);
        IAFrameAnimationAttributes_setName(&frameAnimationAttr, nameOfAnimation);
        IAFrameAnimation * animation = IAFrameAnimation_new(&frameAnimationAttr);
        IAArray_set(&this->frameAnimations, i, animation);
    }
    IAFrameAnimationAttributes_deinit(&frameAnimationAttr);
}


void IAFrameAnimationGroup_setStartTime(IAFrameAnimationGroup * this, uint64_t startTime){
    IAFrameAnimation * animation;
    foreach (animation in array(&this->frameAnimations)){
        IAFrameAnimation_setStartTime(animation, startTime);
    }
}

void IAFrameAnimationGroup_setCurrentTime(IAFrameAnimationGroup * this, uint64_t currentTime){
    IAFrameAnimation * animation;
    foreach (animation in array(&this->frameAnimations)){
        IAFrameAnimation_setCurrentTime(animation, currentTime);
    }
}

void IAFrameAnimationGroup_stop(IAFrameAnimationGroup * this){
    IAFrameAnimation * animation;
    foreach (animation in array(&this->frameAnimations)){
        IAFrameAnimation_stop(animation);
    }
}

void IAFrameAnimationGroup_drawFrame(const IAFrameAnimationGroup * this, size_t frame){
    IAFrameAnimation * animation;
    foreach (animation in array(&this->frameAnimations)){
        IAFrameAnimation_drawFrame(animation, frame);
    }
}

IAFrameAnimation * IAFrameAnimationGroup_getFrameAnimation(IAFrameAnimationGroup * this, size_t index){
    return IAArray_get(&this->frameAnimations, index);
}

void IAFrameAnimationGroup_deinit(IAFrameAnimationGroup * this){
    IAArray_callFunctionOnAllObjects(&this->frameAnimations, (void (*)(void *)) IAFrameAnimation_release);
    IAArray_deinit(&this->frameAnimations);
}

