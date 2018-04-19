//
//  IAUrl.m
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 17.08.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

static NSString * const iOS11AppStoreUrlFormat = @"itms-apps://itunes.apple.com/us/app/id%s?action=write-review";
static NSString * const iOS7AppStoreUrlFormat = @"itms-apps://itunes.apple.com/app/id%s";
static NSString * const iOSAppStoreUrlFormat = @"itms-apps://itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?type=Purple+Software&id=%s";

void IAUrl_openUrlInWebviewWithNSString(NSString * urlString);


void IAUrl_openUrlInWebview(const char * url){
    NSString * urlString = [NSString stringWithUTF8String:url];
    IAUrl_openUrlInWebviewWithNSString(urlString);
}

void IAUrl_openReviewPageInAppstore(const char * iosAppStoreId){
    NSString * appStoreUrlFormat;
    if ([[UIDevice currentDevice].systemVersion floatValue] >= 11.0f){
        appStoreUrlFormat = iOS11AppStoreUrlFormat;
    }else if ([[UIDevice currentDevice].systemVersion floatValue] >= 7.0f) {
        appStoreUrlFormat = iOS7AppStoreUrlFormat;
    }else{
        appStoreUrlFormat = iOSAppStoreUrlFormat;
    }
    NSString * appStoreUrlString = [NSString stringWithFormat:appStoreUrlFormat, iosAppStoreId];
    IAUrl_openUrlInWebviewWithNSString(appStoreUrlString);
}

void IAUrl_openUrlInWebviewWithNSString(NSString * urlString){
    NSURL * url = [NSURL URLWithString:urlString];
    [[UIApplication sharedApplication] openURL: url];
}
