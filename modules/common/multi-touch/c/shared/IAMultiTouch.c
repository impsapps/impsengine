//
//  IAMultiTouch.c
//  MultiTouch
//
//  Created by Konstantin Merker on 04/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAMultiTouch.h"
#include "IATouchManager.h"

#define CLASSNAME "IAMultiTouch"


void IAMultiTouch_commence(){
    IATouchManager_commence();
}

void IAMultiTouch_terminate(){
    IATouchManager_terminate();
}
