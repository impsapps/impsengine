//
//  Storage.h
//  InputOutput
//
//  Created by Konstantin Merker on 14.08.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef InputOutput_IAStorage_h
#define InputOutput_IAStorage_h


/**
 * Get the name of the dir where the app can store private data. It is guarenteed to end with '/'.
 * \returns the name of the dir
 */

const char * IAStorage_getPrivateDataDir();

#endif
