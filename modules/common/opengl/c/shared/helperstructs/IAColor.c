#include "IALibrary.h"
#include "IAColor.h"
#include <string.h>
#include <math.h>

#define CLASSNAME "IAColor"

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

static int IAColor_getSingleValueinHex(const char hex[2]){
    int value = 0;
    for (int i = 0; i < 2; ++i) {
        value *= 16;
        if (hex[i] >= '0' && hex[i] <= '9'){
            value += hex[i] - '0';
        }else if(hex[i] >= 'a' && hex[i] <= 'f'){
            value += 10 + hex[i] - 'a';
        }else if(hex[i] >= 'A' && hex[i] <= 'F'){
            value += 10 + hex[i] - 'A';
        }else{
            logWarning("Invalid hex detected.");
        }
    }
	return value;
}

IAColor IAColor_makeWithHex(const char * hex){
    assert(hex[0] == '#' && "A hex must start with '#'");
    if (strlen(hex) == 4){
        char hexRed[2] = {hex[1], hex[1]};
        char hexGreen[2] = {hex[2], hex[2]};
        char hexBlue[2] = {hex[3], hex[3]};
        IAColor result = {
                .red = IAColor_getSingleValueinHex(hexRed),
                .green = IAColor_getSingleValueinHex(hexGreen),
                .blue = IAColor_getSingleValueinHex(hexBlue),
                .alpha = 255
        };
        return result;
    }else if (strlen(hex) == 7){
        IAColor result = {
                .red = IAColor_getSingleValueinHex(hex + 1),
                .green = IAColor_getSingleValueinHex(hex + 3),
                .blue = IAColor_getSingleValueinHex(hex + 5),
                .alpha = 255
        };
        return result;
    }else if (strlen(hex) == 9){
        IAColor result = {
                .red = IAColor_getSingleValueinHex(hex + 1),
                .green = IAColor_getSingleValueinHex(hex + 3),
                .blue = IAColor_getSingleValueinHex(hex + 5),
                .alpha = IAColor_getSingleValueinHex(hex + 7)
        };
        return result;
    }else{
        logWarning("Invalid hex length \"%lld\" detected.", strlen(hex));
        IAColor result = {
                .alpha = 255
        };
        return result;
    }
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
