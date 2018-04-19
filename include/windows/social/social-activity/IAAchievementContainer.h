//
//  IAAchievementContainer.h
//  Hit Verto
//
//  Created by Konstantin Merker on 10.09.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAAchievementContainer_h
#define Hit_Verto_IAAchievementContainer_h

#include "IAAchievement.h"
#include "IAAchievementContainerAttributes.h"
#include "IAHashMap.h"

typedef struct{
    //@getAsConstRef
    IAHashMap achievements;
    void * correspondingObject;
    void(*onLoadingFinished)(void * correspondingObject);
} IAAchievementContainer;


void IAAchievementContainer_show();

void IAAchievementContainer_init(IAAchievementContainer *, const IAAchievementContainerAttributes * attributes);

void IAAchievementContainer_startLoading(IAAchievementContainer *);

IAAchievement * IAAchievementContainer_getAchievement(const IAAchievementContainer *, const char * achievementId);

void IAAchievementContainer_submitProgress(IAAchievementContainer *);

void IAAchievementContainer_releaseRegisteredAchievements(IAAchievementContainer *);
void IAAchievementContainer_deinit(IAAchievementContainer *);

#include "IAAchievementContainer+Generated.h"

#endif
