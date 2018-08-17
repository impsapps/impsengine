//
//  IAObject.h
//  CLib
//
//  Created by Konstantin Merker on 14.07.18.
//  Copyright © 2018 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAObject_h
#define IAObject_h

typedef void * IAObject;

static inline IAObject IAObject_make(void * object){
    return object;
}

#endif
