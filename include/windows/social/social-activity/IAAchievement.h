//
//  IAAchievement.h
//  Hit Verto
//
//  Created by Konstantin Merker on 10.09.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAAchievement_h
#define Hit_Verto_IAAchievement_h

#include "IAString.h"
#include "IARecursiveLock.h"
#include "IAAchievementAttributes.h"

typedef struct{
    //@getAsCharArray
    IAString * achievementId;
    long submittedSteps;
    long currentSteps;
    long maxSteps;
    bool isHiddenOnClient;
    bool isHiddenOnServer;
    IARecursiveLock lock;
} IAAchievement;


void IAAchievement_setShouldSendAchievementUnlocksImmediately(bool shouldSendAchievementUnlocksImmediately);

void IAAchievement_init(IAAchievement *, IAAchievementAttributes * attributes);

long IAAchievement_getCurrentSteps(IAAchievement *);
long IAAchievement_getMaxSteps(IAAchievement *);
double IAAchievement_getProgress(IAAchievement *);
bool IAAchievement_isHidden(IAAchievement *);
bool IAAchievement_isIncremental(IAAchievement *);
bool IAAchievement_isUnlocked(IAAchievement *);

void IAAchievement_reveal(IAAchievement *);
void IAAchievement_setMinSteps(IAAchievement *, long minSteps);
void IAAchievement_unlock(IAAchievement *);

bool IAAchievement_needToSubmitProgress(IAAchievement *);

void IAAchievement_deinit(IAAchievement *);

#include "IAAchievement+Generated.h"

#endif
