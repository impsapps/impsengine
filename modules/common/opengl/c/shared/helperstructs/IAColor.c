//
//  Color.c
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 06.04.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAColor.h"
#include <string.h>
#include <math.h>

int IAColor_getTransitionValue(int startValue, int goalValue, float progress);

IAColor IAColor_make(int red, int green, int blue, int alpha){
    IAColor color = {
        .red = red,
        .green = green,
        .blue = blue,
        .alpha = alpha
    };
    return color;
}

IAColor IAColor_makeF(float red, float green, float blue, float alpha){
    IAColor color;
    color.red = (int) lroundf(red * 255);
    color.green = (int) lroundf(green * 255);
    color.blue = (int) lroundf(blue * 255);
    color.alpha = (int) lroundf(alpha * 255);
    return color;
}

IAColor IAColor_makeAsTransitionColor(IAColor startColor, IAColor goalColor, float progress){
    IAColor transitionColor;
    transitionColor.red = IAColor_getTransitionValue(startColor.red, goalColor.red, progress);
    transitionColor.green = IAColor_getTransitionValue(startColor.green, goalColor.green, progress);
    transitionColor.blue = IAColor_getTransitionValue(startColor.blue, goalColor.blue, progress);
    transitionColor.alpha = IAColor_getTransitionValue(startColor.alpha, goalColor.alpha, progress);
    return transitionColor;
}

int IAColor_getTransitionValue(int startValue, int goalValue, float progress){
    return startValue + (int) lroundf((goalValue - startValue) * progress);
}

bool IAColor_isEqual(IAColor color1, IAColor color2){
    if (memcmp(&color1, &color2, sizeof(IAColor)) == 0) {
        return true;
    }else{
        return false;
    }
}
