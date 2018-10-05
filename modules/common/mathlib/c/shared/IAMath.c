#include "IAMath.h"
#include <math.h>
#include <stdlib.h>


long IAMath_min(long value1, long value2){
    if (value1 < value2) {
        return value1;
    }else{
        return value2;
    }
}

long IAMath_max(long value1, long value2){
    if (value1 > value2) {
        return value1;
    }else{
        return value2;
    }
}

long IAMath_abs(long value){
	return value > 0 ? value : -value;
}

bool IAMath_isPow2(long value){
    if (value <= 0) return false;
    if ((value & (value - 1)) == 0) {
        return true;
    }else{
        return false;
    }
}

double IAMath_log(double base, double result){
    return log(result) / log(base);
}

#define IA_ROUNDING_TOLERANCE 0.00000000001

bool IAMath_isInt(double d){
    int i = round(d);
    if (i + IA_ROUNDING_TOLERANCE > d && i - IA_ROUNDING_TOLERANCE < d) {
        return true;
    }else{
        return false;
    }
}

long IAMath_roundUp(float value){
    if (value == (float) ((long) value)) {
        return (long) value;
    }else{
        return ((long) value) + 1;
    }
}
