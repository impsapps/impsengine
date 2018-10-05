#ifndef IAOpenGLLogger_h
#define IAOpenGLLogger_h

#include "IALogger.h"
#include "IAOpenGLHeaders.h"
#include <assert.h>

#if defined(DEBUG) && ! defined(IA_OPENGL_ASSERT)

#define IA_OPENGL_ASSERT

#endif

#ifdef IA_OPENGL_ASSERT

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
