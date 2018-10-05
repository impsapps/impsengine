#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#import <GameKit/GameKit.h>

@interface IAOpenGLViewController : GLKViewController <GKGameCenterControllerDelegate>{
    bool wasOnSurfaceCreateCalled;
}

@end
