//
//  IAHashing.c
//  Hit Verto
//
//  Created by Konstantin Merker on 24/10/15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAHashing.h"

#define CLASSNAME "IAHashing"


long IAHashing_getHashCode(const char * c){
    long hashCode = 189021;
    int i = 2;
    while (*c != '\0') {
        hashCode += ((*c) * i);
        i++;
        if (i > 11) {
            i = 1;
        }
        c++;
    }
    return hashCode;
}

