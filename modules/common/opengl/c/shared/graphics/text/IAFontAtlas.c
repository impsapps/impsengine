//
//  IAFontAtlas.c
//  Hit Verto
//
//  Created by Konstantin Merker on 30/01/16.
//  Copyright (c) 2016 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IAFontAtlas.h"
#include "IAFontAtlas+IterateOverGlyphList.h"
#include "IAArrayListIterator.h"
#include "IABitmap.h"
#include "IAUTF8Helper.h"
#include "IAFontInformationAttributes.h"
#include "IAString+Assets.h"
#include "IABitmapManagerSingleton.h"
#include "IAKerningAmount.h"


#define CLASSNAME "IAFontAtlas"


void IAFontAtlas_onBitmapUsageBeginFunction(IAFontAtlas * this, IABitmap * bitmap);
void IAFontAtlas_onBitmapUsageEndFunction(IAFontAtlas * this, IABitmap * bitmap);

int IAFontAtlas_parseNextPartToInt(IAArrayListIterator * iterator);
IAString * IAFontAtlas_parseNextPartToString(IAArrayListIterator * iterator);

IAGlyph * IAFontAtlas_getNextGlyphOfText(IAFontAtlas * this, const char ** text);
IAGlyph * IAFontAtlas_getNextPrintableGlyphOfText(IAFontAtlas * this, const char ** text);

float IAFontAtlas_getCurrentScaleForKernings(IAFontAtlas * this);

void IAFontAtlas_iterateOverGlyphesForTextAtTopPoint(IAFontAtlas * this, const char * text, IAPoint topPoint, IATextAlignment alignment, void * data, void (*onGlyph)(void * data, IAGlyph * glyph));
void IAFontAtlas_preDrawGlyph(IAFontAtlas * this, IAGlyph * glyph);

void IAFontAtlas_drawGlyph(void * data, IAGlyph * glyph);

void IAFontAtlas_releaseObject(void * object);


void IAFontAtlas_init(IAFontAtlas * this, IABitmapManager * bitmapManager){
    this->base = IAObject_make(this);
    this->glyphs = NULL;
    this->currentCountOfGlyphs = 0;
    this->kernings = NULL;
    this->currentCountOfKernings = 0;
    
    this->textures = IAArrayList_new(5);
    IATextureDelegateAttributes attributes;
    IATextureDelegateAttributes_make(&attributes, this);
    IATextureDelegateAttributes_setOnBitmapUsageBeginFunction(&attributes, (void (*)(void *, IABitmap *)) IAFontAtlas_onBitmapUsageBeginFunction);
    IATextureDelegateAttributes_setOnBitmapUsageEndFunction(&attributes, (void (*)(void *, IABitmap *)) IAFontAtlas_onBitmapUsageEndFunction);
    IATextureDelegate_make(&this->textureDelegate, &attributes);
    
    this->fontInformation = NULL;
    this->currentSizeOfFont = 0.0f;
    this->correspondingObject = NULL;
    this->preDrawGlyph = NULL;
    this->bitmapManager = bitmapManager;
    IAArrayList_init(&this->bitmaps, 10);
    IA_incrementInitCount();
}

void IAFontAtlas_initWithDefaultBitmapManager(IAFontAtlas * this){
    IABitmapManager * defaultBitmapManager = IABitmapManagerSingleton_getDefaultBitmapManager();
    IAFontAtlas_init(this, defaultBitmapManager);
}

void IAFontAtlas_initWithCustomPreDrawGlyphFunction(IAFontAtlas * this, IABitmapManager * bitmapManager, void * correspondingObject, void (*preDrawGlyph)(void *, IAGlyph *)){
    IAFontAtlas_init(this, bitmapManager);
    this->correspondingObject = correspondingObject;
    this->preDrawGlyph = preDrawGlyph;
}

void IAFontAtlas_onBitmapUsageBeginFunction(IAFontAtlas * this, IABitmap * bitmap){
    IABitmapManager_lockBitmapRefFromBeeingDestroyed(this->bitmapManager, bitmap);
}

void IAFontAtlas_onBitmapUsageEndFunction(IAFontAtlas * this, IABitmap * bitmap){
    IABitmapManager_unlockBitmapRefFromBeeingDestroyed(this->bitmapManager, bitmap);
}

void IAFontAtlas_addGlyphsFromFnt(IAFontAtlas * this, const char * fntResource, bool shouldPreload){
    IATexture * texture = NULL;
    IASize sizeOfTexture = IASize_make(0.0f, 0.0f);
    IAFontInformationAttributes fontInformationAttributes;
    IAFontInformationAttributes_make(&fontInformationAttributes);
    
    IAString * data = IAString_newWithAsset(fntResource, "fnt");
    IAArrayList * lines = IAString_createSplit(data, "\n");
    IAString * line;
    foreach (line in arrayList(lines)) {
        IAString_removeNewLinesAtEnd(line);
        IAArrayList * partsOfLine = IAString_createSplit(line, " ");
        IAArrayListIterator partsIterator;
        IAArrayListIterator_make(&partsIterator, partsOfLine);
        IAString * part = IAArrayListIterator_getNextObject(&partsIterator);
        
        if (IAString_isEqualToCharArray(part, "char")) {
            int id = IAFontAtlas_parseNextPartToInt(&partsIterator);
            int x = IAFontAtlas_parseNextPartToInt(&partsIterator);
            int y = IAFontAtlas_parseNextPartToInt(&partsIterator);
            int width = IAFontAtlas_parseNextPartToInt(&partsIterator);
            int height = IAFontAtlas_parseNextPartToInt(&partsIterator);
            int xOffset = IAFontAtlas_parseNextPartToInt(&partsIterator);
            int yOffset = IAFontAtlas_parseNextPartToInt(&partsIterator);
            int xAdvance = IAFontAtlas_parseNextPartToInt(&partsIterator);
            
            char character[5];
            int characterLength = IAUTF8Helper_idToUTF8(id, character);
            character[characterLength] = '\0';
            
            IAGlyphInformation glyphInformation;
            glyphInformation.originalFontSize = IAFontInformationAttributes_getFontSize(&fontInformationAttributes);
            glyphInformation.xOffset = xOffset;
            glyphInformation.yOffset = yOffset;
            glyphInformation.xAdvance = xAdvance;
            glyphInformation.sizeOfGlyph = IASize_make(width, height);
            for (int i = 0; i < characterLength; i++) {
                glyphInformation.utf8[i] = character[i];
            }
            glyphInformation.utf8Length = characterLength;
            
            IATextureSelection textureSelection = IATextureSelection_make(IARect_make(x, y, width, height), false, sizeOfTexture);
            IAImageAttributes attributes;
            IAImageAttributes_make(&attributes, texture, textureSelection);
            
            IAImage * glyphImage = IAImage_with(&attributes);
            IAGlyph * glyph = IAGlyph_with(glyphImage, glyphInformation);
            
            IAHashMap_add(this->glyphs, character, glyph);
            
        }else if(IAString_isEqualToCharArray(part, "kerning")){
            int first = IAFontAtlas_parseNextPartToInt(&partsIterator);
            int second = IAFontAtlas_parseNextPartToInt(&partsIterator);
            float value = IAFontAtlas_parseNextPartToInt(&partsIterator);
            IAKerningAmount * amount = IAKerningAmount_with(-value);
            char key[9];
            int length = IAUTF8Helper_idToUTF8(first, key);
            length += IAUTF8Helper_idToUTF8(second, key + length);
            key[length] = '\0';
            IAHashMap_add(this->kernings, (char *) key, amount);
            
        }else if(IAString_isEqualToCharArray(part, "info")){
            IAString * str = IAArrayListIterator_getNextObject(&partsIterator); // face
            while (IAString_charAtIndex(str, IAString_getLength(str) - 1) != '"') {
                str = IAArrayListIterator_getNextObject(&partsIterator);
            }
            int fontSize = IAFontAtlas_parseNextPartToInt(&partsIterator);
            IAFontInformationAttributes_setFontSize(&fontInformationAttributes, fontSize);
            
        }else if(IAString_isEqualToCharArray(part, "common")){
            int lineHeight = IAFontAtlas_parseNextPartToInt(&partsIterator);
            int baseLine = IAFontAtlas_parseNextPartToInt(&partsIterator);
            sizeOfTexture.width = IAFontAtlas_parseNextPartToInt(&partsIterator);
            sizeOfTexture.height = IAFontAtlas_parseNextPartToInt(&partsIterator);
            IAFontInformationAttributes_setLineHeight(&fontInformationAttributes, lineHeight);
            IAFontInformationAttributes_setAscent(&fontInformationAttributes, baseLine);
            IAFontInformationAttributes_setDescent(&fontInformationAttributes, lineHeight - baseLine);
            
        }else if(IAString_isEqualToCharArray(part, "page")){
            IAArrayListIterator_getNextObject(&partsIterator); //id part
            IAString * assetName = IAFontAtlas_parseNextPartToString(&partsIterator);
            IABitmap * bitmap = IABitmap_newWithAsset(IAString_toCharArray(assetName));
            IABitmapManager_addBitmap(this->bitmapManager, bitmap);
            IAArrayList_add(&this->bitmaps, bitmap);
            texture = IATexture_with(bitmap);
            IATexture_setTextureDelegate(texture, &this->textureDelegate);
        }else if(IAString_isEqualToCharArray(part, "chars")){
            int countOfGlyphs = IAFontAtlas_parseNextPartToInt(&partsIterator);
            this->currentCountOfGlyphs += countOfGlyphs;
            IAHashMap * newGlyphsHashMap = IAHashMap_new(this->currentCountOfGlyphs);
            if (this->glyphs != NULL) {
                char * key;
                foreach (key in hashMapKeys(this->glyphs)) {
                    IAGlyph * glyph = IAHashMap_get(this->glyphs, key);
                    IAHashMap_add(newGlyphsHashMap, key, glyph);
                }
                IAHashMap_release(this->glyphs);
            }
            this->glyphs = newGlyphsHashMap;
            
        }else if(IAString_isEqualToCharArray(part, "kernings")){
            int countOfKernings = IAFontAtlas_parseNextPartToInt(&partsIterator);
            this->currentCountOfKernings += countOfKernings;
            IAHashMap * newKerningHashMap = IAHashMap_new(this->currentCountOfGlyphs);
            if (this->kernings != NULL) {
                char * key;
                foreach (key in hashMapKeys(this->kernings)) {
                    int * kerningInformation = IAHashMap_get(this->kernings, key);
                    IAHashMap_add(newKerningHashMap, key, kerningInformation);
                }
                IAHashMap_release(this->kernings);
            }
            this->kernings = newKerningHashMap;
        }
        
        IAArrayList_callFunctionOnAllObjects(partsOfLine, (void (*)(void *)) IAString_release);
        IAArrayList_release(partsOfLine);
    }
    
    IAArrayList_callFunctionOnAllObjects(lines, (void (*)(void *)) IAString_release);
    IAArrayList_release(lines);
    IAString_release(data);
    
    if (this->fontInformation != NULL) {
        IAFontInformation_release(this->fontInformation);
    }
    this->fontInformation = IAFontInformation_new(&fontInformationAttributes);
    this->currentSizeOfFont = this->fontInformation->fontSize;
    IAArrayList_add(this->textures, texture);
    
    if (shouldPreload) {
        IATexture_use(texture);
    }
}

int IAFontAtlas_parseNextPartToInt(IAArrayListIterator * iterator){
    IAString * string = IAArrayListIterator_getNextObject(iterator);
    size_t index;
    bool wasIndexFound = IAString_getIndexOfFirstPatternMatch(string, "=", &index);
    debugAssert(wasIndexFound);
    IAString_substringWithStartingIndexTillEnd(string, index + 1);
    return IAString_toInt(string);
}

IAString * IAFontAtlas_parseNextPartToString(IAArrayListIterator * iterator){
    IAString * string = IAArrayListIterator_getNextObject(iterator);
    size_t index;
    bool wasIndexFound = IAString_getIndexOfFirstPatternMatch(string, "=", &index);
    debugAssert(wasIndexFound);
    IAString_substringWithStartingIndexTillEnd(string, index + 2);
    IAString_substring(string, IAString_getLength(string) - 1);
    return string;
}

void IAFontAtlas_setCurrentFontSize(IAFontAtlas * this, float currentFontSize){
    this->currentSizeOfFont = currentFontSize;
}

void IAFontAtlas_setCustomAdditionalAdvanceBetweenGlyphesInPixel(IAFontAtlas * this, float customAdditionalAdvanceBetweenGlyphesInPixel){
    IAGlyph * glyph;
    foreach (glyph in hashMapValues(this->glyphs)){
        IAGlyph_setCustomAdditionalAdvanceBetweenGlyphesInPixel(glyph, customAdditionalAdvanceBetweenGlyphesInPixel);
    }
}

IAGlyph * IAFontAtlas_getNextGlyphOfText(IAFontAtlas * this, const char ** text){
    debugAssert(**text != '\0');
    
    char UTF8Char[5];
    int lengthOfUTF8Char = IAUTF8Helper_getNextChar(*text, UTF8Char);
    *text += lengthOfUTF8Char;
    IAGlyph * glyph = IAHashMap_get(this->glyphs, UTF8Char);
    
    if (lengthOfUTF8Char <= 0) {
        logError("IAFontAtlas_createListWithConvertedGlyphs: critical error: text cannot be converted in glyphs because it is not in a valid UTF8-format!! Canceling.");
        return NULL;
    }
    
    if (glyph == NULL) {
        UTF8Char[0] = 0xFF;
        UTF8Char[1] = 0xFD;
        UTF8Char[2] = '\0';
        glyph = IAHashMap_get(this->glyphs, UTF8Char);
    }
    
    return glyph;
}

IAGlyph * IAFontAtlas_getNextPrintableGlyphOfText(IAFontAtlas * this, const char ** text){
    while (**text != '\0') {
        IAGlyph * glyph = IAFontAtlas_getNextGlyphOfText(this, text);
        if (glyph != NULL) {
            return glyph;
        }
    }
    return NULL;
}

float IAFontAtlas_getLengthForText(IAFontAtlas * this, const char * text){
    float lengthOfText = 0.0f;
    float scaleForKernings = IAFontAtlas_getCurrentScaleForKernings(this);
    IAGlyph * glyph;
    IAGlyph * lastGlyph = NULL;
    while ((glyph = IAFontAtlas_getNextPrintableGlyphOfText(this, &text)) != NULL) {
        IAGlyph_setCurrentFontSize(glyph, this->currentSizeOfFont);
        lengthOfText += IAGlyph_getWidthNeededInPixel(glyph);
        if (lastGlyph != NULL) {
            lengthOfText += IAGlyph_getSpaceBetweenGlyphesInPixel(lastGlyph, glyph, this->kernings, scaleForKernings);
        }
        lastGlyph = glyph;
    }
    return lengthOfText;
}

bool IAFontAtlas_hasAllGlyphesForText(IAFontAtlas * this, const char * text){
    while (*text != '\0') {
        IAGlyph * glyph = IAFontAtlas_getNextGlyphOfText(this, &text);
        if (glyph == NULL) {
            return false;
        }
    }
    return true;
}

float IAFontAtlas_getCurrentScaleForKernings(IAFontAtlas * this){
    return this->currentSizeOfFont / IAFontInformation_getFontSize(this->fontInformation);
}

void IAFontAtlas_iterateOverGlyphesForTextAtTopPoint(IAFontAtlas * this, const char * text, IAPoint topPoint, IATextAlignment alignment, void * data, void (*onGlyph)(void * data, IAGlyph * glyph)){
    if (alignment != IATextAlignment_LEFT) {
        float lengthOfText = IAFontAtlas_getLengthForText(this, text);
        if (alignment == IATextAlignment_CENTER) {
            topPoint.x -= lengthOfText / 2.0f;
        }else if(alignment == IATextAlignment_RIGHT){
            topPoint.x -= lengthOfText;
        }
    }
    
    float scaleForKerningInformation = IAFontAtlas_getCurrentScaleForKernings(this);
    
#ifdef DEBUG
    if (IAFontAtlas_hasAllGlyphesForText(this, text) == false) {
        logInfo("Not all glyphes are in font atlas for text \"%s\"!", text);
    }
#endif
    
    IAGlyph * glyph;
    IAGlyph * lastGlyph = NULL;
    while ((glyph = IAFontAtlas_getNextPrintableGlyphOfText(this, &text)) != NULL) {
        IAGlyph_setCurrentFontSize(glyph, this->currentSizeOfFont);
        if (lastGlyph != NULL) {
            topPoint.x += IAGlyph_getSpaceBetweenGlyphesInPixel(lastGlyph, glyph, this->kernings, scaleForKerningInformation);
        }
        IAGlyph_setLeftTopPoint(glyph, topPoint);
        IAFontAtlas_preDrawGlyph(this, glyph);
        onGlyph(data, glyph);
        topPoint.x += IAGlyph_getWidthNeededInPixel(glyph);
        lastGlyph = glyph;
    }
}

void IAFontAtlas_preDrawGlyph(IAFontAtlas * this, IAGlyph * glyph){
    if (this->preDrawGlyph != NULL) {
        this->preDrawGlyph(this->correspondingObject, glyph);
    }
}

void IAFontAtlas_iterateOverGlyphesForTextAtBaselineLeft(IAFontAtlas * this, const char * text, IAPoint left, void * data, void (*onGlyph)(void * data, IAGlyph * glyph)){
    IAFontAtlas_iterateOverGlyphesForTextAtBaseline(this, text, left, IATextAlignment_LEFT, data, onGlyph);
}

void IAFontAtlas_iterateOverGlyphesForTextAtBaselineCenter(IAFontAtlas * this, const char * text, IAPoint center, void * data, void (*onGlyph)(void * data, IAGlyph * glyph)){
    IAFontAtlas_iterateOverGlyphesForTextAtBaseline(this, text, center, IATextAlignment_CENTER, data, onGlyph);
}

void IAFontAtlas_iterateOverGlyphesForTextAtBaselineRight(IAFontAtlas * this, const char * text, IAPoint right, void * data, void (*onGlyph)(void * data, IAGlyph * glyph)){
    IAFontAtlas_iterateOverGlyphesForTextAtBaseline(this, text, right, IATextAlignment_RIGHT, data, onGlyph);
}

void IAFontAtlas_iterateOverGlyphesForTextAtBaseline(IAFontAtlas * this, const char * text, IAPoint pointAtBaseline, IATextAlignment alignment, void * data, void (*onGlyph)(void * data, IAGlyph * glyph)){
    float ascent = IAFontInformation_getAscent(this->fontInformation);
    ascent = ascent * this->currentSizeOfFont / IAFontInformation_getFontSize(this->fontInformation);
    pointAtBaseline.y -= ascent;
    IAFontAtlas_iterateOverGlyphesForTextAtTopPoint(this, text, pointAtBaseline, alignment, data, onGlyph);
}

void IAFontAtlas_iterateOverGlyphesForTextRelativelyAtMiddlelineLeft(IAFontAtlas * this, const char * text, IAPoint left, void * data, void (*onGlyph)(void * data, IAGlyph * glyph)){
    IAFontAtlas_iterateOverGlyphesForTextRelativelyAtMiddleline(this, text, left, IATextAlignment_LEFT, data, onGlyph);
}

void IAFontAtlas_iterateOverGlyphesForTextRelativelyAtMiddlelineCenter(IAFontAtlas * this, const char * text, IAPoint center, void * data, void (*onGlyph)(void * data, IAGlyph * glyph)){
    IAFontAtlas_iterateOverGlyphesForTextRelativelyAtMiddleline(this, text, center, IATextAlignment_CENTER, data, onGlyph);
}

void IAFontAtlas_iterateOverGlyphesForTextRelativelyAtMiddlelineRight(IAFontAtlas * this, const char * text, IAPoint right, void * data, void (*onGlyph)(void * data, IAGlyph * glyph)){
    IAFontAtlas_iterateOverGlyphesForTextRelativelyAtMiddleline(this, text, right, IATextAlignment_RIGHT, data, onGlyph);
}

void IAFontAtlas_iterateOverGlyphesForTextRelativelyAtMiddleline(IAFontAtlas * this, const char * text, IAPoint pointAtMiddleline, IATextAlignment alignment, void * data, void (*onGlyph)(void * data, IAGlyph * glyph)){
    float ascent = IAFontInformation_getAscent(this->fontInformation);
    float descent = IAFontInformation_getDescent(this->fontInformation);
    float scale = this->currentSizeOfFont / IAFontInformation_getFontSize(this->fontInformation);
    ascent *= scale;
    descent *= scale;
    pointAtMiddleline.y -= (ascent + descent) / 2.0f;
    IAFontAtlas_iterateOverGlyphesForTextAtTopPoint(this, text, pointAtMiddleline, alignment, data, onGlyph);
}

void IAFontAtlas_drawGlyph(void * data, IAGlyph * glyph){
    IAGlyph_draw(glyph);
}

void IAFontAtlas_drawTextAtBaselineLeft(IAFontAtlas * this, const char * text, IAPoint left){
    IAFontAtlas_drawTextAtBaseline(this, text, left, IATextAlignment_LEFT);
}

void IAFontAtlas_drawTextAtBaselineCenter(IAFontAtlas * this, const char * text, IAPoint center){
    IAFontAtlas_drawTextAtBaseline(this, text, center, IATextAlignment_CENTER);
}

void IAFontAtlas_drawTextAtBaselineRight(IAFontAtlas * this, const char * text, IAPoint right){
    IAFontAtlas_drawTextAtBaseline(this, text, right, IATextAlignment_RIGHT);
}

void IAFontAtlas_drawTextAtBaseline(IAFontAtlas * this, const char * text, IAPoint pointAtBaseline, IATextAlignment alignment){
    IAFontAtlas_iterateOverGlyphesForTextAtBaseline(this, text, pointAtBaseline, alignment, NULL, IAFontAtlas_drawGlyph);
}

void IAFontAtlas_drawTextRelativelyAtMiddlelineLeft(IAFontAtlas * this, const char * text, IAPoint left){
    IAFontAtlas_drawTextRelativelyAtMiddleline(this, text, left, IATextAlignment_LEFT);
}

void IAFontAtlas_drawTextRelativelyAtMiddlelineCenter(IAFontAtlas * this, const char * text, IAPoint center){
    IAFontAtlas_drawTextRelativelyAtMiddleline(this, text, center, IATextAlignment_CENTER);
}

void IAFontAtlas_drawTextRelativelyAtMiddlelineRight(IAFontAtlas * this, const char * text, IAPoint right){
    IAFontAtlas_drawTextRelativelyAtMiddleline(this, text, right, IATextAlignment_RIGHT);
}

void IAFontAtlas_drawTextRelativelyAtMiddleline(IAFontAtlas * this, const char * text, IAPoint pointAtMiddleline, IATextAlignment alignment){
    IAFontAtlas_iterateOverGlyphesForTextRelativelyAtMiddleline(this, text, pointAtMiddleline, alignment, NULL, IAFontAtlas_drawGlyph);
}

IAFontInformation * IAFontAtlas_getFontInformation(IAFontAtlas * this){
    return this->fontInformation;
}

void IAFontAtlas_deinit(IAFontAtlas * this){
    if (this->glyphs != NULL) {
        IAHashMap_release(this->glyphs);
    }
    if (this->kernings != NULL) {
        IAHashMap_release(this->kernings);
    }
    IAArrayList_release(this->textures);
    if (this->fontInformation != NULL) {
        IAFontInformation_release(this->fontInformation);
    }
    IABitmap * bitmap;
    foreach (bitmap in arrayList(&this->bitmaps)){
        IABitmapManager_removeBitmap(this->bitmapManager, bitmap);
    }
    IAArrayList_callFunctionOnAllObjects(&this->bitmaps, (void (*)(void *)) IABitmap_release);
    IAArrayList_deinit(&this->bitmaps);
    IA_decrementInitCount();
}


