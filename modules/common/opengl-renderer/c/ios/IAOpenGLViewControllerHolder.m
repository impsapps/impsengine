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


