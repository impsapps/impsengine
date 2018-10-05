#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#include "IAShare.h"
#include "IABitmap.h"
#include "IABitmap+Native.h"

void IAShare_shareBitmap(const char * text, IABitmap * bitmap){
    NSMutableArray *sharingItems = [[NSMutableArray alloc] init];
    UIImage * image = (UIImage *) IABitmap_getBitmapRef(bitmap);
    [sharingItems addObject:image];
    UIActivityViewController *activityController = [[UIActivityViewController alloc] initWithActivityItems:sharingItems applicationActivities:nil];
    [sharingItems release];
    UIViewController* viewController = [UIApplication sharedApplication].keyWindow.rootViewController;
    
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        activityController.popoverPresentationController.sourceView = viewController.view;
        activityController.popoverPresentationController.sourceRect = CGRectMake(viewController.view.bounds.size.width/2, viewController.view.bounds.size.height/2, 0, 0);
        activityController.popoverPresentationController.permittedArrowDirections = 0;
    }
    [viewController presentViewController:activityController animated:YES completion:nil];
    [activityController release];
}
