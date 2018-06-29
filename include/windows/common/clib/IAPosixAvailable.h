//
//  IAPosixAvailable.h
//  CLib
//
//  Created by Konstantin Merker on 31.05.18.
//  Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//


#ifndef IA_POSIX_ONLY

#define IA_POSIX_ONLY(...)

#ifndef _WIN32

#include <unistd.h>

#ifdef _POSIX_VERSION

#define IA_POSIX_AVAILABLE
#undef IA_POSIX_ONLY
#define IA_POSIX_ONLY(...) __VA_ARGS__

#endif

#endif

#endif

