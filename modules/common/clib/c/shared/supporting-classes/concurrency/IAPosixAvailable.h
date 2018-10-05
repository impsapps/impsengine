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

