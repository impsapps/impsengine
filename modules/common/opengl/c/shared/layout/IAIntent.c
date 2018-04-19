//
//  IAIntent.c
//  OpenGL
//
//  Created by Konstantin Merker on 03/12/17.
//  Copyright © 2017 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAIntent.h"
#include <string.h>

#define CLASSNAME "IAIntent"


void IAIntent_init(IAIntent * this, IAView * view){
    *this = (IAIntent){
        .view = view
    };
    IA_increaseAllocationCount();
}

void IAIntent_setViewArgs(IAIntent * this, const void * viewArgs, size_t sizeOfViewArgs){
    if (this->viewArgs == NULL) {
        this->viewArgs = IA_malloc(sizeOfViewArgs);
    }else{
        this->viewArgs = IA_realloc(this->viewArgs, sizeOfViewArgs);
    }
    memcpy(this->viewArgs, viewArgs, sizeOfViewArgs);
}

void IAIntent_deinit(IAIntent * this){
    if (this->viewArgs != NULL) {
        IA_free(this->viewArgs);
    }
    IA_decreaseAllocationCount();
}

