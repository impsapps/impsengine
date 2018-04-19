//
//  IATextureSelectionData.c
//  Hit Verto
//
//  Created by Konstantin Merker on 03/02/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IATextureSelectionData.h"

#define CLASSNAME "IATextureSelectionData"


void IATextureSelectionData_setDataWithLeftTopRightBottomAndCurrentIsRotated(IATextureSelectionData * this, GLfloat left, GLfloat top, GLfloat right, GLfloat bottom);


void IATextureSelectionData_make(IATextureSelectionData * this, IATextureSelection textureSelection){
    this->isRotated = textureSelection.isRotated;
    GLfloat left = textureSelection.selectionRect.origin.x / textureSelection.baseSizeOfTexture.width;
    GLfloat top = textureSelection.selectionRect.origin.y / textureSelection.baseSizeOfTexture.height;
    GLfloat right = (textureSelection.selectionRect.origin.x + textureSelection.selectionRect.size.width) / textureSelection.baseSizeOfTexture.width;
    GLfloat bottom = (textureSelection.selectionRect.origin.y + textureSelection.selectionRect.size.height) / textureSelection.baseSizeOfTexture.height;
    IATextureSelectionData_setDataWithLeftTopRightBottomAndCurrentIsRotated(this, left, top, right, bottom);
}

void IATextureSelectionData_makeCopy(IATextureSelectionData * this, const IATextureSelectionData * textureSelectionDataToCopy){
    *this = *textureSelectionDataToCopy;
}

void IATextureSelectionData_setDataWithLeftTopRightBottomAndCurrentIsRotated(IATextureSelectionData * this, GLfloat left, GLfloat top, GLfloat right, GLfloat bottom){
    if (this->isRotated == false){
        this->values[0] = left;
        this->values[1] = top;
        this->values[2] = left;
        this->values[3] = bottom;
        this->values[4] = right;
        this->values[5] = bottom;
        this->values[6] = right;
        this->values[7] = top;
    }else{
        this->values[0] = right;
        this->values[1] = top;
        this->values[2] = left;
        this->values[3] = top;
        this->values[4] = left;
        this->values[5] = bottom;
        this->values[6] = right;
        this->values[7] = bottom;
    }
}

GLfloat IATextureSelectionData_getSelectionLeft(IATextureSelectionData * this){
    return this->values[2];
}

GLfloat IATextureSelectionData_getSelectionTop(IATextureSelectionData * this){
    return this->values[1];
}

GLfloat IATextureSelectionData_getSelectionRight(IATextureSelectionData * this){
    return this->values[6];
}

GLfloat IATextureSelectionData_getSelectionBottom(IATextureSelectionData * this){
    return this->values[5];
}

IASize IATextureSelectionData_getSizeOfSelection(IATextureSelectionData * this, IASize textureSize){
    float scaleWidth = IATextureSelectionData_getSelectionRight(this) - IATextureSelectionData_getSelectionLeft(this);
    float scaleHeight = IATextureSelectionData_getSelectionBottom(this) - IATextureSelectionData_getSelectionTop(this);
    IASize sizeOfSelection = IASize_make(scaleWidth * textureSize.width, scaleHeight * textureSize.height);
    if (this->isRotated) {
        float temp = sizeOfSelection.width;
        sizeOfSelection.width = sizeOfSelection.height;
        sizeOfSelection.height = temp;
    }
    return sizeOfSelection;
}


