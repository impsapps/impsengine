//
//  IAImageProgramSingleton.h
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 06.06.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineiOS_IAImageProgramSingleton_h
#define ImpsEngineiOS_IAImageProgramSingleton_h

#include "IAImageProgram.h"

void IAImageProgramSingleton_commence();
IAImageProgram * IAImageProgramSingleton_getProgram();
void IAImageProgramSingleton_terminate();

#endif
