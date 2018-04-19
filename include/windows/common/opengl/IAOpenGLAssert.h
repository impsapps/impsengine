//
//  IAOpenGLAssert.h
//  ImpsEngineiOS
//
//  Created by Konstantin Merker on 07.04.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#ifndef ImpsEngineiOS_IAOpenGLLogger_h
#define ImpsEngineiOS_IAOpenGLLogger_h

#include "IALogger.h"
#include "IAOpenGLHeaders.h"
#include <assert.h>

#ifdef DEBUG

#define glAssert()  { \
            GLenum glError = glGetError(); \
            if (glError != GL_NO_ERROR){ \
                logError("OpenGLError: %d", glError); \
                assert(glError == GL_NO_ERROR); \
            } \
        }
#else
#define glAssert()
#endif

#endif
