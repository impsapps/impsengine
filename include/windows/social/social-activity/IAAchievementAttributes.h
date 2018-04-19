//
//  IAAchievementAttributes.h
//  GameCenter
//
//  Created by Konstantin Merker on 30/12/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAAchievementAttributes_h
#define IAAchievementAttributes_h

typedef struct{
    //@set+get
    const char * achievementId;
    //@set+get
    long maxSteps;
    //@set+get
    bool isInitiallyHidden;
} IAAchievementAttributes;


void IAAchievementAttributes_make(IAAchievementAttributes *, const char * achievementId);

#include "IAAchievementAttributes+Generated.h"

#endif
