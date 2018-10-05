#import <Foundation/Foundation.h>
#include "IAString.h"
#include "IAString+Assets+Native.h"

void IAString_nativeInitWithAsset(IAString * this, const char * assetName, const char * filenameExtension){
    NSString * filePath = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:assetName] ofType:[NSString stringWithUTF8String:filenameExtension]];
    NSString * data = [NSString stringWithContentsOfFile:filePath encoding:NSUTF8StringEncoding error:nil];
    IAString_initWithLength(this, [data UTF8String], (int) [data lengthOfBytesUsingEncoding:NSUTF8StringEncoding]);
}
