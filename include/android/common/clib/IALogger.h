//
//  IALogger.h
//  ImpsEngineCLibrary
//
//  Created by Konstantin Merker on 25.03.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineCLibrary_IALogger_h
#define ImpsEngineCLibrary_IALogger_h

#include <strings.h>
#include <android/log.h>

#define logError(...) __android_log_print(ANDROID_LOG_ERROR, CLASSNAME, __VA_ARGS__)
#define logWarning(...) __android_log_print(ANDROID_LOG_WARNING, CLASSNAME, __VA_ARGS__)
#define logInfo(...) __android_log_print(ANDROID_LOG_INFO, CLASSNAME, __VA_ARGS__)

#endif
