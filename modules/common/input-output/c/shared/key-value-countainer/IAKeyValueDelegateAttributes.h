//
//  IAKeyValueDelegateAttributes.h
//  InputOutput
//
//  Created by Konstantin Merker on 12/01/17.
//  Copyright © 2017 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAKeyValueDelegateAttributes_h
#define IAKeyValueDelegateAttributes_h

#include "IAString.h"

typedef struct{
    //@set+get
    void * value;
    //@set+get
    void (*applyStringToValue)(void * value, IAString * string);
    //@set+get
    void (*setString)(void * value, IAString * string);
    //@set+get
    const bool * shouldSave;
} IAKeyValueDelegateAttributes;


void IAKeyValueDelegateAttributes_make(IAKeyValueDelegateAttributes *, void * value, void (*applyStringToValue)(void * value, IAString * string), void (*setString)(void * value, IAString * string));

#include "IAKeyValueDelegateAttributes+Generated.h"

#endif
