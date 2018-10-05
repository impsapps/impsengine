#include "IALibrary.h"
#include "IAImageProgramSingleton.h"

#define CLASSNAME "IAImageProgramSingleton"

static IAImageProgram * program = NULL;

void IAImageProgramSingleton_commence(){
    program = IAImageProgram_new();
}

IAImageProgram * IAImageProgramSingleton_getProgram(){
    return program;
}

void IAImageProgramSingleton_terminate(){
    IAImageProgram_release(program);
    program = NULL;
}


