//
//  IAOperatingSystem.h
//  Hit Verto
//
//  Created by Konstantin Merker on 29.08.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAOperatingSystem_h
#define IAOperatingSystem_h

#define IA_OPERATING_SYSTEM_ANDROID 1
#define IA_OPERATING_SYSTEM_IOS 2
#define IA_OPERATING_SYSTEM_WINDOWS 3

#include "IAOperatingSystem+Native.h"

#ifndef IA_CURRENT_OPERATING_SYSTEM
#error IA_CURRENT_OPERATING_SYSTEM is not defined in "IAOperatingSystem+Native.h"
#endif

#if IA_CURRENT_OPERATING_SYSTEM == IA_OPERATING_SYSTEM_ANDROID

#define IA_GET_PLATFORM_SPECIFIC_ID(androidId, iOSId) androidId

#elif IA_CURRENT_OPERATING_SYSTEM == IA_OPERATING_SYSTEM_IOS

#define IA_GET_PLATFORM_SPECIFIC_ID(androidId, iOSId) iOSId

#elif IA_CURRENT_OPERATING_SYSTEM != IA_OPERATING_SYSTEM_WINDOWS

#error IA_CURRENT_OPERATING_SYSTEM has invalid value in "IAOperatingSystem+Native.h"

#endif

#endif
