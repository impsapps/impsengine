//
//  IADate.m
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 26.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#import <Foundation/Foundation.h>
#include "IADate+Native.h"
#include "IALibrary.h"

#define CLASSNAME "IADate"


void IADate_nativeMakeDateWithNSString(IADate * this, NSString * date);

void IADate_nativeMakeWithCurrentDate(IADate * this){
    NSDate* date = [NSDate date];
    NSDateFormatter* dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"yyyy-MM-dd-HH-mm-SS"];//@"yyyy-MM-dd'T'HH:mm:SS.SSS'Z'"
    NSString* dateTime = [dateFormatter stringFromDate:date];
    IADate_nativeMakeDateWithNSString(this, dateTime);
}

void IADate_nativeMakeWithCurrentUTCDate(IADate * this){
    NSDate* date = [NSDate date];
    NSDateFormatter* dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setTimeZone:[NSTimeZone timeZoneWithAbbreviation:@"UTC"]];
    [dateFormatter setDateFormat:@"yyyy-MM-dd-HH-mm-SS"];
    NSString* dateTime = [dateFormatter stringFromDate:date];
    IADate_nativeMakeDateWithNSString(this, dateTime);
}

void IADate_nativeMakeDateWithNSString(IADate * this, NSString * date){
    NSArray * array = [date componentsSeparatedByString:@"-"];
    this->base = IAObject_make(this);
    
    this->day = [[array objectAtIndex:2] intValue];
    this->month = [[array objectAtIndex:1] intValue];
    this->year = [[array objectAtIndex:0] intValue];
    
    this->hour = [[array objectAtIndex:3] intValue];
    this->minute = [[array objectAtIndex:4] intValue];
    this->second = [[array objectAtIndex:5] intValue];
}
