//
//  IAOpenGLViewControllerHolder.c
//  Hit Verto
//
//  Created by Konstantin Merker on 10.09.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#include "IAOpenGLViewControllerHolder.h"
#include "IALibrary.h"

#define CLASSNAME "IAOpenGLViewControllerHolder"


static IAOpenGLViewController * viewController = NULL;

void IAOpenGLViewControllerHolder_commence(IAOpenGLViewController * viewController_){
    [UIView setAnimationsEnabled:NO];
    viewController = viewController_;
}

IAOpenGLViewController * IAOpenGLViewControllerHolder_getViewController(){
    return viewController;
}

void IAOpenGLViewControllerHolder_terminate(){
    viewController = NULL;
}


