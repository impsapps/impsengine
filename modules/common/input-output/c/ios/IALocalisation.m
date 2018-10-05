#import <Foundation/Foundation.h>

#include "IALibrary.h"
#include "IALocalisation.h"
#include "IAString.h"

#define CLASSNAME "IALocalisation"

static NSString * localeId;

const char * IALocalisation_getLocaleId(){
    if (localeId == NULL) {
         localeId = NSLocalizedString(@"locale_id", nil);
    }
    return [localeId UTF8String];
}

