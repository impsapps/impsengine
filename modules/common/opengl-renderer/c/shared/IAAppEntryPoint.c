//
//  IAAppEntryPoint.c
//  ImpsEngine
//
//  Created by Konstantin Merker on 06/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAAppEntryPoint+Core.h"

#define CLASSNAME "IAAppEntryPoint"

static IAInterfaceOrientationMask interfaceOrientationMask = IAInterfaceOrientationMask_PORTRAIT;
static void (*onAppStart)(IAAppAttributes * attributes);


void IAAppEntryPoint_setInterfaceOrientationMask(IAInterfaceOrientationMask interfaceOrientationMask_){
    interfaceOrientationMask = interfaceOrientationMask_;
}

IAInterfaceOrientationMask IAAppEntryPoint_getInterfaceOrientationMask(){
    return interfaceOrientationMask;
}

void IAAppEntryPoint_setOnAppStart(void (*onAppStart_)(IAAppAttributes * attributesOut)){
    onAppStart = onAppStart_;
}

void IAAppEntryPoint_onAppStart(IAAppAttributes * attributesOut){
    if (onAppStart != NULL) {
        onAppStart(attributesOut);
    }else{
        logInfo("Function \"onAppStart\" is not defined. Call \"IAAppEntryPoint_setOnAppStart\" to specify an entry point!");
    }
}
