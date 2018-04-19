//
//  IAAssert.h
//  CLib
//
//  Created by Konstantin Merker on 19/08/17.
//  Copyright © 2017 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAAssert_h
#define IAAssert_h

#include <assert.h>

#if DEBUG_ASSERTS == true
#define debugAssert(e) assert(e)
#else
#define debugAssert(e)
#endif

#endif
