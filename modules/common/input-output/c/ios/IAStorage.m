//
//  IAStorage.m
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 14.08.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#import <Foundation/Foundation.h>
#include "IAStorage+Native.h"

void IAStorage_nativeGetPrivateDataDir(IAString * privateDataDir){
    NSString * filePath = [NSString stringWithFormat:@"%@/Library/Application Support", NSHomeDirectory()];
    const char * str = [filePath UTF8String];
    IAString_set(privateDataDir, str);
}

