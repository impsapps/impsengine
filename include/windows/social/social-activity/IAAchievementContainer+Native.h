//
//  IAAchievementContainer+Native.h
//  Hit Verto
//
//  Created by Konstantin Merker on 11.09.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAAchievementContainer_Native_h
#define Hit_Verto_IAAchievementContainer_Native_h

#include "IAAchievementContainer.h"

void IAAchievementContainer_nativeShow();

void IAAchievementContainer_nativeStartLoading(IAAchievementContainer * container);

void IAAchievementContainer_notifyLoadingFinished(IAAchievementContainer *);

void IAAchievementContainer_nativeSubmitProgress(IAHashMap * achievements, bool (*shouldSubmitAchievement)(IAAchievement * achievement));

#endif
