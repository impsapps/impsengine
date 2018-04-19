//
//  IAColorRectProgramSingleton.h
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 06.06.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineiOS_IAColorRectProgramSingleton_h
#define ImpsEngineiOS_IAColorRectProgramSingleton_h

#include "IAColorRectProgram.h"

void IAColorRectProgramSingleton_commence();

IAColorRectProgram * IAColorRectProgramSingleton_getColorRectProgram();

void IAColorRectProgramSingleton_terminate();

#endif
