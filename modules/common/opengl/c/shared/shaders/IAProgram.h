#ifndef IAProgram_h
#define IAProgram_h

#include <stdbool.h>

#include "IAStructArrayList.h"
#include "IAShader.h"
#include "IAOpenGLHeaders.h"
#include "IAOpenGLResourceDelegate.h"
#include "IANotificationEvent.h"
#include "IAObject.h"

typedef struct{
    GLint attributeLocation;
} IAProgramAttribute;

IA_STRUCT_ARRAY_LIST(IAProgramAttribute);

typedef struct{
    //@extend
    IAObject base;
    GLuint programId;
    IAShader * vertexShader;
    IAShader * fragmentShader;
    IAStructArrayList_IAProgramAttribute * attributes;
    void (*glBindAttributeLocations)(GLuint programId);
    IAOpenGLResourceDelegate delegate;
    //@register
    IANotificationEvent linkingComplete;
} IAProgram;


void IAProgram_onNewOpenGLContext();

void IAProgram_init(IAProgram *, const char * vertexShaderCode, const char * fragmentShaderCode, void (*glBindAttributeLocations)(GLuint programId));

//register all dynamic attributes before you call program_use
void IAProgram_registerDynamicAttribute(IAProgram *, GLint attributeLocation);

GLint IAProgram_getAttributeLocation(IAProgram *, const GLchar * name);
GLint IAProgram_getUniformLocation(IAProgram *, const GLchar * name);

bool IAProgram_isEqual(IAProgram *, IAProgram * program2);

void IAProgram_use(IAProgram *);

void IAProgram_deinit(IAProgram *);

#include "IAProgram+Generated.h"

#endif
