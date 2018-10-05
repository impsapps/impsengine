#include "IALibrary.h"
#include "IAMeassure.h"
#include "IATime.h"

#define CLASSNAME "IAMeassure"


IAMeassure IAMeassure_make(){
    IAMeassure meassure;
    meassure.timeInNanoSeconds = IATime_getTimeInNanoSeconds();
    meassure.pausedTimeInNanoSeconds = 0;
    return meassure;
}

void IAMeassure_pause(IAMeassure * this){
    if (this->pausedTimeInNanoSeconds == 0) {
        this->pausedTimeInNanoSeconds = IATime_getTimeInNanoSeconds();
    }
}

void IAMeassure_unpause(IAMeassure * this){
    if (this->pausedTimeInNanoSeconds != 0) {
        uint64_t difference = IATime_getTimeInNanoSeconds() - this->pausedTimeInNanoSeconds;
        this->timeInNanoSeconds += difference;
        this->pausedTimeInNanoSeconds = 0;
    }
}

void IAMeassure_logInfo(IAMeassure this, const char * string){
    if (this.pausedTimeInNanoSeconds == 0) {
        uint64_t current = IATime_getTimeInNanoSeconds();
        logInfo("%s: %f", string, (current - this.timeInNanoSeconds) / 1000000000.0);
    }else{
        logInfo("%s: %f", string, (this.pausedTimeInNanoSeconds - this.timeInNanoSeconds) / 1000000000.0);
    }
}

void IAMeassure_logError(IAMeassure this, const char * string){
    if (this.pausedTimeInNanoSeconds == 0) {
        uint64_t current = IATime_getTimeInNanoSeconds();
        logError("%s: %f", string, (current - this.timeInNanoSeconds) / 1000000000.0);
    }else{
        logError("%s: %f", string, (this.pausedTimeInNanoSeconds - this.timeInNanoSeconds) / 1000000000.0);
    }
}


