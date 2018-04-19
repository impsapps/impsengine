//
//  IALogger.h
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 25.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineCLibrary_IALogger_h
#define ImpsEngineCLibrary_IALogger_h

#include <stdio.h>


#define logError(...) printf("!!!ERROR!!! %s: ", CLASSNAME); printf (__VA_ARGS__); printf("\n")
#define logWarning(...) printf("Warning %s: ", CLASSNAME); printf (__VA_ARGS__); printf("\n")
#define logInfo(...) printf("Info %s: ", CLASSNAME); printf (__VA_ARGS__); printf("\n")

#endif
