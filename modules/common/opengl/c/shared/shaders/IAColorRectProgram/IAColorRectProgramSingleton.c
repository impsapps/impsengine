//
//  IAColorRectProgramSingleton.c
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 06.06.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

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


