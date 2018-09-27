//
//  IATouch.c
//  Hit Verto
//
//  Created by Konstantin Merker on 10/03/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IATouch.h"

#define CLASSNAME "IATouch"


IATouch IATouch_make(long identifier, IAPoint location){
    return (IATouch){
            .identifier = identifier,
            .location = location
    };
}

bool IATouch_hasSameIdentifier(IATouch t1, IATouch t2){
    if (t1.identifier == t2.identifier){
        return true;
    }else{
        return false;
    }
}
