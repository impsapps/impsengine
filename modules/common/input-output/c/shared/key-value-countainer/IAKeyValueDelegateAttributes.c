//
//  IAKeyValueDelegateAttributes.c
//  InputOutput
//
//  Created by Konstantin Merker on 12/01/17.
//  Copyright © 2017 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAKeyValueDelegateAttributes.h"

#define CLASSNAME "IAKeyValueDelegateAttributes"

static const bool trueValue = true;

void IAKeyValueDelegateAttributes_make(IAKeyValueDelegateAttributes * this, void * value, void (*applyStringToValue)(void * value, IAString * string), void (*setString)(void * value, IAString * string)){
    *this = (IAKeyValueDelegateAttributes){
        .value = value,
        .applyStringToValue = applyStringToValue,
        .setString = setString,
        .shouldSave = &trueValue
    };
}


