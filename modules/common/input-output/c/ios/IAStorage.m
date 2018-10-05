#import <Foundation/Foundation.h>
#include "IAStorage+Native.h"

void IAStorage_nativeGetPrivateDataDir(IAString * privateDataDir){
    NSString * identifier = [[[NSBundle mainBundle] infoDictionary] objectForKey:(NSString*)kCFBundleIdentifierKey];
    NSString * filePath = [NSString stringWithFormat:@"%@/Library/Application Support/%@", NSHomeDirectory(), identifier];
    const char * str = [filePath UTF8String];
    IAString_set(privateDataDir, str);
}

