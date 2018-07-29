//
//  IAMemoryPoolElement.c
//  CLib
//
//  Created by Konstantin Merker on 15.07.18.
//Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAMemoryPoolElement.h"

#define CLASSNAME "IAMemoryPoolElement"


void IAMemoryPoolElement_make(IAMemoryPoolElement * this, void * object){
    *this = (IAMemoryPoolElement){
        .object = object
    };
}

void IAMemoryPoolElement_run(IAMemoryPoolElement * this){
    IA_release(this->object);
}


