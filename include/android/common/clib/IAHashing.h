//
//  IAHashing.h
//  Hit Verto
//
//  Created by Konstantin Merker on 24/10/15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef Hit_Verto_IAHashing_h
#define Hit_Verto_IAHashing_h

/// Simple hash. Don't use it for security purposes. The hash is subject to change, so don't safe the hash code on persistend storage.
long IAHashing_getHashCode(const char * c);

#endif
