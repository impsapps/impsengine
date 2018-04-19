//
//  IAOpenGLViewControllerHolder.h
//  Hit Verto
//
//  Created by Konstantin Merker on 10.09.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAOpenGLViewControllerHolder_h
#define Hit_Verto_IAOpenGLViewControllerHolder_h

#import <UIKit/UIKit.h>
#include "IAOpenGLViewController.h"

void IAOpenGLViewControllerHolder_commence(IAOpenGLViewController * viewController);

IAOpenGLViewController * IAOpenGLViewControllerHolder_getViewController();

void IAOpenGLViewControllerHolder_terminate();

#endif
