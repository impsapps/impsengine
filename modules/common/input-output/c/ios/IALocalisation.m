//
//  IALocalisation.m
//  Hit Verto
//
//  Created by Konstantin Merker on 02.09.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

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

