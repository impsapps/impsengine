//
//  IAAchievement+Native.h
//  Hit Verto
//
//  Created by Konstantin Merker on 11.09.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAAchievement_Native_h
#define Hit_Verto_IAAchievement_Native_h

#include "IAAchievement.h"

void IAAchievement_nativeUnlock(IAAchievement * achievement);

void IAAchievement_notifyProgressSubmitted(IAAchievement * achievement, long submittedSteps);

void IAAchievement_notifyAchievementStatus(IAAchievement * achievement, long currentSteps, bool isHidden);

#endif
