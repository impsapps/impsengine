//
//  IAAcceleration.c
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 25.06.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAAcceleration.h"

#define CLASSNAME "IAAcceleration"

float IAAcceleration_calculateProgress(uint64_t startTime, uint64_t currentTime, uint64_t duration){
    return ((float) (currentTime - startTime)) / (float) duration;
}

float IAAcceleration_calculateCurrentValue(float startValue, float endValue, float progress, float (*accelerationFunction)(float, float, float)){
    return accelerationFunction(startValue, endValue, progress);
}

IAPoint IAAcceleration_calculateCurrentPoint(IAPoint startPoint, IAPoint endPoint, float progress, float (*accelerationFunction)(float, float, float)){
    float currentX = accelerationFunction(startPoint.x, endPoint.x, progress);
    float currentY = accelerationFunction(startPoint.y, endPoint.y, progress);
    return IAPoint_make(currentX, currentY);
}

IARect IAAcceleration_calculateCurrentRect(IARect startRect, IARect endRect, float progress, float (*accelerationFunction)(float, float, float)){
    float currentX = accelerationFunction(startRect.origin.x, endRect.origin.x, progress);
    float currentY = accelerationFunction(startRect.origin.y, endRect.origin.y, progress);
    float currentWidth = accelerationFunction(startRect.size.width, endRect.size.width, progress);
    float currentHeight = accelerationFunction(startRect.size.height, endRect.size.height, progress);
    return IARect_make(currentX, currentY, currentWidth, currentHeight);
}

float IAAcceleration_linearMovementFunction(float startValue, float endValue, float progress){
    float distance = endValue - startValue;
    return startValue + distance * progress;
}

float IAAcceleration_uniformlyAccelerationFunction(float startValue, float endValue, float progress){
    float totalDistance = endValue - startValue;
    float currentDistance = totalDistance * progress * progress;
    return startValue + currentDistance;
}

float IAAcceleration_uniformlyDecelerationFunction(float startValue, float endValue, float progress){
    progress = 1.0f - progress;
    float acceleration = IAAcceleration_uniformlyAccelerationFunction(endValue, startValue, progress);
    return acceleration;
}

float IAAcceleration_normalAccelerationFunction(float startValue, float endValue, float progress){
    float midValue = startValue + (endValue - startValue) / 2.0f;
    if (progress < 0.5f) {
        return IAAcceleration_uniformlyAccelerationFunction(startValue, midValue, progress * 2.0f);
    }else{
        return IAAcceleration_uniformlyDecelerationFunction(midValue, endValue, (progress - 0.5f) * 2.0f);
    }
}

float IAAcceleration_getWay(float speed, float acceleration) {
	float duration = IAAcceleration_getDuration(speed, acceleration);
	float way = speed * duration / 2.0f;
	return way;
}

float IAAcceleration_getDuration(float speed, float acceleration) {
	return speed / acceleration;
}

