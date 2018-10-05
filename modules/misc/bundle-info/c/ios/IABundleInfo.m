#include "IALibrary.h"
#include "IABundleInfo.h"
#include "IACharArray.h"
#undef in
#import <Foundation/Foundation.h>

#define CLASSNAME "IABundleInfo"

const char * IABundleInfo_getAppVersion(){
    static char * appVersion = NULL;
    if (appVersion == NULL) {
        NSString * nsAppVersionString = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
        const char * appVersionString = [nsAppVersionString UTF8String];
        size_t str_len = strlen(appVersionString);
        appVersion = IA_malloc(str_len + 1);
        memcpy(appVersion, appVersionString, str_len + 1);
    }
    return appVersion;
}

