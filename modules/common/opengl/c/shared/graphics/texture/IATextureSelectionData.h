#ifndef IATextureSelectionData_h
#define IATextureSelectionData_h

#include "IAOpenGLHeaders.h"
#include "IATextureSelection.h"

typedef struct{
    //@getAsConstRef
    GLfloat values[8];
    bool isRotated;
} IATextureSelectionData;


void IATextureSelectionData_make(IATextureSelectionData *, IATextureSelection textureSelection);
void IATextureSelectionData_makeCopy(IATextureSelectionData *, const IATextureSelectionData * textureSelectionDataToCopy);

GLfloat IATextureSelectionData_getSelectionLeft(IATextureSelectionData *);
GLfloat IATextureSelectionData_getSelectionTop(IATextureSelectionData *);
GLfloat IATextureSelectionData_getSelectionRight(IATextureSelectionData *);
GLfloat IATextureSelectionData_getSelectionBottom(IATextureSelectionData *);

IASize IATextureSelectionData_getSizeOfSelection(IATextureSelectionData *, IASize textureSize);

#include "IATextureSelectionData+Generated.h"

#endif
