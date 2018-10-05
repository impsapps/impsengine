#ifndef IAOpenGLViewControllerHolder_h
#define IAOpenGLViewControllerHolder_h

#import <UIKit/UIKit.h>
#include "IAOpenGLViewController.h"

void IAOpenGLViewControllerHolder_commence(IAOpenGLViewController * viewController);

IAOpenGLViewController * IAOpenGLViewControllerHolder_getViewController();

void IAOpenGLViewControllerHolder_terminate();

#endif
