//
//  IATextureDelegateAttributes.c
//  OpenGL
//
//  Created by Konstantin Merker on 01/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IATextureDelegateAttributes.h"

#define CLASSNAME "IATextureDelegateAttributes"


void IATextureDelegateAttributes_make(IATextureDelegateAttributes * this, void * correspondingObject){
    *this = (IATextureDelegateAttributes){
        .correspondingObject = correspondingObject
    };
}


