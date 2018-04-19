//
//  IAUTF8Helper.h
//  OpenGL
//
//  Created by Konstantin Merker on 25/10/16.
//  Copyright © 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef IAUTF8Helper_h
#define IAUTF8Helper_h

int IAUTF8Helper_idToUTF8(int id, char utf8[4]);
int IAUTF8Helper_getNextChar(const char * utf8String, char utf8CharOut[5]);

#endif
