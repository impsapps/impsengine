#ifndef IAMatrix44_h
#define IAMatrix44_h

#include "IAOpenGLHeaders.h"
#include "IARect.h"
#include "IAObject.h"

typedef struct{
    //@extend
    IAObject base;
    GLfloat values[16];
}IAMatrix44;


void IAMatrix44_make(IAMatrix44 *);
void IAMatrix44_makeCopy(IAMatrix44 *, const IAMatrix44 * toCopy);
void IAMatrix44_makeOrthographicProjection(IAMatrix44 *, GLfloat near, GLfloat far, GLfloat left, GLfloat right, GLfloat top, GLfloat bottom);

void IAMatrix44_makeWithMultiplikationResult(IAMatrix44 *, IAMatrix44 * firstFactor, IAMatrix44 * secondFactor);

void IAMatrix44_makeTranslationMatrix(IAMatrix44 *, GLfloat x, GLfloat y, GLfloat z);

void IAMatrix44_makeScaleMatrix(IAMatrix44 *, GLfloat stretchX, GLfloat stretchY, GLfloat stretchZ);

void IAMatrix44_makeRotationXMatrix(IAMatrix44 *, GLfloat radians);
void IAMatrix44_makeRotationXMatrixWithDegrees(IAMatrix44 *, GLfloat degrees);
void IAMatrix44_makeRotationYMatrix(IAMatrix44 *, GLfloat radians);
void IAMatrix44_makeRotationYMatrixWithDegrees(IAMatrix44 *, GLfloat degrees);
void IAMatrix44_makeRotationZMatrix(IAMatrix44 *, GLfloat radians);
void IAMatrix44_makeRotationZMatrixWithDegrees(IAMatrix44 *, GLfloat degrees);

void IAMatrix44_makeTrimmedRect(IAMatrix44 *, IARect trimmedRect, IASize originalSize);
void IAMatrix44_makeTransformation(IAMatrix44 *, IARect oldRect, IARect newRect);

void IAMatrix44_makeAsIdentityMatrix(IAMatrix44 *);


void IAMatrix44_multiplyModelMatrix(IAMatrix44 *, IAMatrix44 * modelMatrix);

void IAMatrix44_changeTranslationMatrix(IAMatrix44 *, GLfloat x, GLfloat y, GLfloat z);
void IAMatrix44_setXForTranslationMatrix(IAMatrix44 *, GLfloat x);
GLfloat IAMatrix44_getXForTranslationMatrix(IAMatrix44 *);
void IAMatrix44_setYForTranslationMatrix(IAMatrix44 *, GLfloat y);
GLfloat IAMatrix44_getYForTranslationMatrix(IAMatrix44 *);
void IAMatrix44_setZForTranslationMatrix(IAMatrix44 *, GLfloat z);
GLfloat IAMatrix44_getZForTranslationMatrix(IAMatrix44 *);

void IAMatrix44_changeScaleMatrix(IAMatrix44 *, GLfloat stretchX, GLfloat stretchY, GLfloat stretchZ);
void IAMatrix44_setStretchXForScaleMatrix(IAMatrix44 *, GLfloat stretchX);
GLfloat IAMatrix44_getStretchXForScaleMatrix(IAMatrix44 *);
void IAMatrix44_setStretchYForScaleMatrix(IAMatrix44 *, GLfloat stretchY);
GLfloat IAMatrix44_getStretchYForScaleMatrix(IAMatrix44 *);
void IAMatrix44_setStretchZForScaleMatrix(IAMatrix44 *, GLfloat stretchZ);
GLfloat IAMatrix44_getStretchZForScaleMatrix(IAMatrix44 *);

void IAMatrix44_setRotationZ(IAMatrix44 *, GLfloat radians);

void IAMatrix44_setTrimmedRect(IAMatrix44 *, IARect trimmedRect, IASize originalSize);
void IAMatrix44_setTransformation(IAMatrix44 *, IARect oldRect, IARect newRect);

void IAMatrix44_setIdentityMatrix(IAMatrix44 *);

GLfloat * IAMatrix44_getValues(IAMatrix44 *);

void IAMatrix44_setValuesFromMatrix(IAMatrix44 *, IAMatrix44 * matrixWithValuesToCopy);

void IAMatrix44_copySafely(IAMatrix44 *, IAMatrix44 ** destination);

void IAMatrix44_releaseMatrixIfNotNull(IAMatrix44 *);

#include "IAMatrix44+Generated.h"

#endif
