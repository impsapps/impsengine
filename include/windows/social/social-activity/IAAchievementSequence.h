//
//  IAAchievementSequence.h
//  Hit Verto
//
//  Created by Konstantin Merker on 18.09.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAAchievementSequence_h
#define Hit_Verto_IAAchievementSequence_h

#include "IAAchievement.h"

/**
 * \file IAAchievement.h
 * Sets the min steps of multiple incremental achievements which are based on the same integer. For Example you have 3 achievements, the first is unlocked with 10 hits, the second with 20 and the last with 30. You can call this function like "IAAchievementSequence_setMinStepsOfAchievements(minSteps, 3, a1, a2, a3)" which will allow you to set the steps of all achievements at once.
 * If the achievements are hidden, they will be revealed only, if all previous achievements in the sequence are unlocked.
 * The achievements should be ordered from low to high.
 */

void IAAchievementSequence_setMinStepsOfTripleAchievements(long minSteps, IAAchievement * achievements[3]);
void IAAchievementSequence_setMinStepsOfAchievements(long minSteps, size_t numberOfAchievements, ...);

long IAAchievementSequence_getMaxCurrentStepsOfTripleAchievements(IAAchievement * achievements[3]);
long IAAchievementSequence_getMaxCurrentStepsOfAchievements(size_t numberOfAchievements, ...);

#endif
