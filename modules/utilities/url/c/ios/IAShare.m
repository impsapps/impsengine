//
//  IAShare.m
//  Url
//
//  Created by Konstantin Merker on 13.12.17.
//  Copyright © 2017 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#include "IAShare.h"
#include "IABitmap.h"
#include "IABitmap+Native.h"

void IAShare_shareBitmap(const char * text, IABitmap * bitmap){
    NSMutableArray *sharingItems = [[NSMutableArray alloc] init];
    UIImage * image = (UIImage *) IABitmap_getBitmapRef(bitmap);
    [sharingItems addObject:image];
    /*NSString * str = [NSString stringWithUTF8String:text];
    [sharingItems addObject:str];*/
    UIActivityViewController *activityController = [[UIActivityViewController alloc] initWithActivityItems:sharingItems applicationActivities:nil];
    [sharingItems release];
    UIViewController* viewController = [UIApplication sharedApplication].keyWindow.rootViewController;
    
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        activityController.popoverPresentationController.sourceView = viewController.view;
        activityController.popoverPresentationController.sourceRect = CGRectMake(viewController.view.bounds.size.width/2, viewController.view.bounds.size.height/2, 0, 0);
        activityController.popoverPresentationController.permittedArrowDirections = 0;
    }
    [viewController presentViewController:activityController animated:YES completion:nil];
}
