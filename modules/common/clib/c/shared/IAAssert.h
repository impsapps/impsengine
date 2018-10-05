#ifndef IAAssert_h
#define IAAssert_h

#include <assert.h>

#ifdef DEBUG
#define debugAssert(e) assert(e)
#else
#define debugAssert(e)
#endif

#endif
