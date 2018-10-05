#ifndef IALogger_h
#define IALogger_h

#include <strings.h>
#include <android/log.h>

#define logError(...) __android_log_print(ANDROID_LOG_ERROR, CLASSNAME, __VA_ARGS__)
#define logWarning(...) __android_log_print(ANDROID_LOG_WARNING, CLASSNAME, __VA_ARGS__)
#define logInfo(...) __android_log_print(ANDROID_LOG_INFO, CLASSNAME, __VA_ARGS__)

#endif
