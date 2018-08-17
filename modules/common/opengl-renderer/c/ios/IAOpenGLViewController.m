//
//  IAOpenGLViewController.m
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 26.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//



#import "IAOpenGLViewController.h"

#include "IALibrary.h"
#include "IALibrary+SendOnMemoryWarningNotification.h"
#include "IAAllocationTracking.h"
#include "IAAppEntryPoint+Core.h"

#include "IAOpenGLViewControllerHolder.h"
#include "IAAppHandler+Native.h"

#include "IAInterfaceOrientationMask+iOS.h"
#include "IAColorFormat+iOS.h"
#include "IADepthFormat+iOS.h"
#include "IAStencilFormat+iOS.h"
#include "IAMultisample+iOS.h"

#include "IATouchManager.h"

#include "IAOpenGLAssert.h"
#include "IACurrentFrame.h"

#undef in

#define CLASSNAME "IAOpenGLViewController"


#define pointsToPixels(POINTS) (POINTS) * [UIScreen mainScreen].scale


@interface IAOpenGLViewController () {
    int width;
    int height;
}

@property (strong, nonatomic) EAGLContext *context;

@end

@implementation IAOpenGLViewController


-(id) initWithCoder:(NSCoder *)aDecoder{
    self = [super initWithCoder:aDecoder];
    if (self) {
        IAOpenGLViewControllerHolder_commence(self);
    }
    return self;
}

- (UIInterfaceOrientationMask)supportedInterfaceOrientations{
    IAInterfaceOrientationMask mask = IAAppEntryPoint_getInterfaceOrientationMask();
    return IAInterfaceOrientationMask_convert(mask);
}

- (void)viewDidLoad{
    [super viewDidLoad];
    
#ifdef DEBUG
    logInfo("MainScreen scale: %f", [UIScreen mainScreen].scale);
#endif
    glAssert();
    
    IAApp * appDelegate = IAAppHandler_getAppDelegate();
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    CGRect frame = [UIScreen mainScreen].applicationFrame;
    width = frame.size.width;
    height = frame.size.height;
    
    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    
    IAColorFormat colorFormat = IAApp_getColorFormat(appDelegate);
    view.drawableColorFormat = IAColorFormat_convert(colorFormat);
    
    IADepthFormat depthFormat = IAApp_getDepthFormat(appDelegate);
    view.drawableDepthFormat = IADepthFormat_convert(depthFormat);
    
    IAStencilFormat stencilFormat = IAApp_getStencilFormat(appDelegate);
    view.drawableStencilFormat = IAStencilFormat_convert(stencilFormat);
    
    IAMultisample multisample = IAApp_getMultisample(appDelegate);
    view.drawableMultisample = IAMultisample_convert(multisample);
    
    [EAGLContext setCurrentContext:self.context];
    glAssert();
    
    NSNotificationCenter* defaultCenter = [NSNotificationCenter defaultCenter];
    [defaultCenter addObserver:self selector:@selector(onPause) name:UIApplicationWillResignActiveNotification object:nil];
    [defaultCenter addObserver:self selector:@selector(onStop) name:UIApplicationDidEnterBackgroundNotification object:nil];
    [defaultCenter addObserver:self selector:@selector(onResume) name:UIApplicationDidBecomeActiveNotification object:nil];
    [defaultCenter addObserver:self selector:@selector(onStart) name:UIApplicationWillEnterForegroundNotification object:nil];
    glAssert();
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    //This code fixes delayed touches began on left and right side of screen on iPad.
    UIGestureRecognizer* gr0 = self.view.window.gestureRecognizers[0];
    UIGestureRecognizer* gr1 = self.view.window.gestureRecognizers[1];
    gr0.delaysTouchesBegan = false;
    gr1.delaysTouchesBegan = false;
}

-(void) onStart{
    
}

-(void) onResume{
    
}

-(void) onPause{
    
}

-(void) onStop{
    bool shouldRenderPauseScreen;
    IAAppHandler_switchToPausescreen(&shouldRenderPauseScreen);
    IAAppHandler_saveGameState();
}



- (BOOL)prefersStatusBarHidden{
    return YES;
}

- (void)didReceiveMemoryWarning{
    IALibrary_onMemoryWarning();
    [super didReceiveMemoryWarning];
}

- (void)update{
    
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect{
    IASize surfaceSize = IASize_make(pointsToPixels(rect.size.width), pointsToPixels(rect.size.height));
    
    if (wasOnSurfaceCreateCalled == false) {
        wasOnSurfaceCreateCalled = true;
        IAAppHandler_onSurfaceCreated();
        IAAppHandler_onSurfaceChanged(surfaceSize);
        
        width = rect.size.width;
        height = rect.size.height;
    }
    
    if (width != rect.size.width || height != rect.size.height) {
        width = rect.size.width;
        height = rect.size.height;
        IAAppHandler_onSurfaceChanged(surfaceSize);
    }
    IAAppHandler_render();
    glAssert();
}

-(void) addCorrespondingTouchHandlersToArray: (NSSet *) touches :(IATouchHandler *[]) touchHandlers{
    size_t i = 0;
    for (UITouch * uiTouch in touches) {
        IATouchHandler * touchHandler = IATouchManager_getTouchHandler((long) uiTouch);
        CGPoint location = [uiTouch locationInView: self.view];
        IATouchHandler_setTouchLocation(touchHandler, IAPoint_make(pointsToPixels(location.x), pointsToPixels(location.y)));
        touchHandlers[i++] = touchHandler;
    }
}

-(void) destroyTouchHandlersInArray: (size_t) lengthOfTouchHandlers :(IATouchHandler *[]) touchHandlers{
    for (size_t i = 0; i < lengthOfTouchHandlers; i++) {
        IATouchManager_destroyTouchHandler(touchHandlers[i]);
    }
}

-(void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event{
    size_t lengthOfTouchHandlers = touches.count;
    IATouchHandler * touchHandlers[lengthOfTouchHandlers];
    
    size_t i = 0;
    for (UITouch * touch in touches) {
        CGPoint location = [touch locationInView: self.view];
        IATouchHandler * touchHandler = IATouchManager_createNewTouchHandler((long) touch, IAPoint_make(pointsToPixels(location.x), pointsToPixels(location.y)));
        touchHandlers[i++] = touchHandler;
    }
    IATouchManager_onTouchBegan(lengthOfTouchHandlers, touchHandlers);
}

-(void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event{
    size_t lengthOfTouchHandlers = touches.count;
    IATouchHandler * touchHandlers[lengthOfTouchHandlers];
    [self addCorrespondingTouchHandlersToArray: touches :touchHandlers];
    
    IATouchManager_onTouchMoved(lengthOfTouchHandlers, touchHandlers);
}

-(void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event{
    size_t lengthOfTouchHandlers = touches.count;
    IATouchHandler * touchHandlers[lengthOfTouchHandlers];
    [self addCorrespondingTouchHandlersToArray: touches :touchHandlers];
    
    IATouchManager_onTouchEnded(lengthOfTouchHandlers, touchHandlers);
    
    [self destroyTouchHandlersInArray:lengthOfTouchHandlers :touchHandlers];
}

- (void)gameCenterViewControllerDidFinish:(GKGameCenterViewController *) gameCenterViewController{
    [self dismissViewControllerAnimated:YES completion:nil];
    
}

- (void)dealloc{
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
    [self.context release];
    [super dealloc];
}

@end
