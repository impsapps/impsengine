//
//  IAOpenGLViewController.h
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 26.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#import <GameKit/GameKit.h>

@interface IAOpenGLViewController : GLKViewController <GKGameCenterControllerDelegate>{
    bool wasOnSurfaceCreateCalled;
}

@end
