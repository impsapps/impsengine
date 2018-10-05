#include "IALibrary.h"
#include "IAColorRectProgramSingleton.h"

#define CLASSNAME "IAColorRectProgramSingleton"

static IAColorRectProgram * colorRectProgram = NULL;

void IAColorRectProgramSingleton_commence(){
    colorRectProgram = IAColorRectProgram_new();
}

IAColorRectProgram * IAColorRectProgramSingleton_getColorRectProgram(){
    return colorRectProgram;
}

void IAColorRectProgramSingleton_terminate(){
    IAColorRectProgram_release(colorRectProgram);
    colorRectProgram = NULL;
}


