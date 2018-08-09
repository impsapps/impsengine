//
//  IAApp.c
//  Core
//
//  Created by Konstantin Merker on 02/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAApp.h"

#define CLASSNAME "IAApp"


void IAApp_make(IAApp * this, IAAppAttributes * attributes){
    *this = (IAApp){
        .correspondingObject = IAAppAttributes_getCorrespondingObject(attributes),
        .commence = IAAppAttributes_getCommenceFunction(attributes),
        .onSurfaceSizeChanged = IAAppAttributes_getOnSurfaceSizeChangedFunction(attributes),
        .onRender = IAAppAttributes_getOnRenderFunction(attributes),
        .switchToPauseScreen = IAAppAttributes_getSwitchToPauseScreenFunction(attributes),
        .saveGameState = IAAppAttributes_getSaveGameStateFunction(attributes),
        .terminate = IAAppAttributes_getTerminateFunction(attributes),
        .colorFormat = IAAppAttributes_getColorFormat(attributes),
        .depthFormat = IAAppAttributes_getDepthFormat(attributes),
        .stencilFormat = IAAppAttributes_getStencilFormat(attributes),
        .multisample = IAAppAttributes_getMultisample(attributes),
        .shouldLogRenderingPerformance = IAAppAttributes_shouldLogRenderingPerformance(attributes)
    };
}


