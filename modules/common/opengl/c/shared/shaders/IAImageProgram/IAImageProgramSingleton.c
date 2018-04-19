//
//  IAImageProgramSingleton.c
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 06.06.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

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


