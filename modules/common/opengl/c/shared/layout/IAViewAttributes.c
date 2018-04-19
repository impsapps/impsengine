//
//  IAViewAttributes.c
//  OpenGL
//
//  Created by Konstantin Merker on 28/09/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAViewAttributes.h"

#define CLASSNAME "IAViewAttributes"


void IAViewAttributes_make(IAViewAttributes * this, void * correspondingView){
    *this = (IAViewAttributes){
        .correspondingView = correspondingView
    };
}

