//
//  IAAchievementContainerAttributes.h
//  GameCenter
//
//  Created by Konstantin Merker on 02/01/17.
//  Copyright © 2017 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAAchievementContainerAttributes_h
#define IAAchievementContainerAttributes_h

#include "IAAchievement.h"

typedef struct{
    //@set+get
    void * correspondingObject;
    //@set+get
    void(*onLoadingFinished)(void * correspondingObject);
    //@getAsConstRef
    IAArrayList achievements;
} IAAchievementContainerAttributes;


void IAAchievementContainerAttributes_init(IAAchievementContainerAttributes *);

void IAAchievementContainerAttributes_addAchievement(IAAchievementContainerAttributes *, IAAchievement * achievement);

void IAAchievementContainerAttributes_deinit(IAAchievementContainerAttributes *);

#include "IAAchievementContainerAttributes+Generated.h"

#endif
