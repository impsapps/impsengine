#include "IALibrary.h"
#include <string.h>
#include "IAImageContext.h"
#include "expat.h"
#include "IABitmap.h"
#include "IAString+Assets.h"

#define CLASSNAME "IAImageContext"

#ifdef XML_LARGE_SIZE
#if defined(XML_USE_MSC_EXTENSIONS) && _MSC_VER < 1400
#define XML_FMT_INT_MOD "I64"
#else
#define XML_FMT_INT_MOD "ll"
#endif
#else
#define XML_FMT_INT_MOD "l"
#endif


void XMLCALL IAImageContext_startElement(IAImageContext * this, const char * name, const char ** atts);

void IAImageContext_onBitmapUsageBeginFunction(IAImageContext * this, IABitmap * bitmap);
void IAImageContext_onBitmapUsageEndFunction(IAImageContext * this, IABitmap * bitmap);


void IAImageContext_init(IAImageContext * this, IABitmapManager * bitmapManager){
    this->images = IAAutoExpandingHashMap_new();
    this->textures = IAArrayList_new(20);
    IATextureDelegateAttributes attributes;
    IATextureDelegateAttributes_make(&attributes, this);
    IATextureDelegateAttributes_setOnBitmapUsageBeginFunction(&attributes, (void (*)(void *, IABitmap *)) IAImageContext_onBitmapUsageBeginFunction);
    IATextureDelegateAttributes_setOnBitmapUsageEndFunction(&attributes, (void (*)(void *, IABitmap *)) IAImageContext_onBitmapUsageEndFunction);
    IATextureDelegate_make(&this->textureDelegate, &attributes);
    this->sizeOfLastTexture = IASize_make(0.0f, 0.0f);
    this->bitmapManager = bitmapManager;
    IAArrayList_init(&this->bitmaps, 10);
    IAString_init(&this->assetNameTemp, "");
    IA_incrementInitCount();
}

void IAImageContext_addAtlas(IAImageContext * this, const char * assetName){
    IAString_set(&this->assetNameTemp, assetName);
    
    IAString string;
    IAString_initWithAsset(&string, assetName, "xml");
    
    XML_Parser parser = XML_ParserCreate(NULL);
    XML_SetUserData(parser, this);
    XML_SetElementHandler(parser, (XML_StartElementHandler) IAImageContext_startElement, NULL);
    if (XML_Parse(parser, IAString_toCharArray(&string), (int) IAString_getLength(&string), true) == XML_STATUS_ERROR) {
        logError("XMLParser returned error \"%s\" at line %" XML_FMT_INT_MOD "u for xmlResource: %s", XML_ErrorString(XML_GetErrorCode(parser)), XML_GetCurrentLineNumber(parser), assetName);
    }
    XML_ParserFree(parser);

    IAString_deinit(&string);
}

void XMLCALL IAImageContext_startElement(IAImageContext * this, const char * name, const char ** atts){
    if (strcmp(name, "TextureAtlas") == 0) {
        size_t lastPatternMatch;
        IABitmap * bitmap;
        if (IAString_getIndexOfLastPatternMatch(&this->assetNameTemp, "/", &lastPatternMatch)){
            IAString_substring(&this->assetNameTemp, lastPatternMatch + 1);
            IAString_concat(&this->assetNameTemp, atts[1]);
            bitmap = IABitmap_newWithAsset(IAString_toCharArray(&this->assetNameTemp));
        }else{
            bitmap = IABitmap_newWithAsset(atts[1]);
        }
        IABitmapManager_addBitmap(this->bitmapManager, bitmap);
        IAArrayList_add(&this->bitmaps, bitmap);
        
        IATexture * texture = IATexture_new(bitmap);
        IATexture_setTextureDelegate(texture, &this->textureDelegate);
        
        IATexture_use(texture);
        IAArrayList_add(this->textures, texture);
        
        int width = 0;
        int height = 0;
        while (*atts != NULL) {
            if (strcmp(atts[0], "width") == 0) {
                IAString * widthString = IAString_new(atts[1]);
                width = IAString_toInt(widthString);
                IAString_release(widthString);
            }else if (strcmp(atts[0], "height") == 0) {
                IAString * heightString = IAString_new(atts[1]);
                height = IAString_toInt(heightString);
                IAString_release(heightString);
            }
            atts += 2;
        }
        this->sizeOfLastTexture = IASize_make((float) width, (float) height);
        
    }else if(strcmp(name, "sprite") == 0){
        IAHashMap * attributes = IAHashMap_new(8);
        while (*atts != NULL) {
            IAHashMap_add(attributes, atts[0], IAString_new(atts[1]));
            atts += 2;
        }


        IAString * imageName = IAHashMap_get(attributes, "n");
        size_t index;
        debugOnly(bool isFound =) IAString_getIndexOfLastPatternMatch(imageName, ".", &index);
        debugAssert(isFound == true && "Name of bitmap in xml file not valid!");
        IAString_substring(imageName, index);
        if (IAString_getIndexOfLastPatternMatch(imageName, "/", &index)) {
            IAString_substringWithStartingIndexTillEnd(imageName, index + 1);
        }
        
        float x = IAString_toInt(IAHashMap_get(attributes, "x"));
        float y = IAString_toInt(IAHashMap_get(attributes, "y"));
        float spriteWidth = IAString_toInt(IAHashMap_get(attributes, "w"));
        float spriteHeight = IAString_toInt(IAHashMap_get(attributes, "h"));
        bool rotated = false;
        IAString * rotatedString = IAHashMap_get(attributes, "r");
        if (rotatedString != NULL && IAString_isEqualToCharArray(rotatedString, "y")) {
            rotated = true;
        }
        
        IATexture * texture = IAArrayList_getLast(this->textures);
        IATextureSelection selection = IATextureSelection_make(IARect_make(x, y, spriteWidth, spriteHeight), rotated, this->sizeOfLastTexture);
        IAImageAttributes imageAttributes;
        IAImageAttributes_make(&imageAttributes, texture, selection);
        
        IAString * offsetXString = IAHashMap_get(attributes, "oX");
        if (offsetXString != NULL) {
            float offsetX = IAString_toInt(offsetXString);
            float offsetY = IAString_toInt(IAHashMap_get(attributes, "oY"));
            float originalWidth = IAString_toInt(IAHashMap_get(attributes, "oW"));
            float originalHeight = IAString_toInt(IAHashMap_get(attributes, "oH"));
            IARect trimmedRect;
            if (rotated == true) {
                trimmedRect = IARect_make(offsetX, offsetY, spriteHeight, spriteWidth);
            }else{
                trimmedRect = IARect_make(offsetX, offsetY, spriteWidth, spriteHeight);
            }
            
            IASize originalSizeOfImage = IASize_make(originalWidth, originalHeight);
            IAImageAttributes_setTrimmedRect(&imageAttributes, trimmedRect, originalSizeOfImage);
        }
        
        IAImage * image = IAImage_new(&imageAttributes);
		IAAutoExpandingHashMap_add(this->images, IAString_toCharArray(imageName), image);
        IAHashMap_callFunctionOnAllObjects(attributes, (void (*)(void *)) IAString_release);
        IAHashMap_release(attributes);
    }
    
    while (*atts) {
        atts+=2;
    }
}

void IAImageContext_addAtlasAssets(IAImageContext * this, IAAtlasAssets * assets) {
	for (int i = 0; i < IAAtlasAssets_getCount(assets); i++) {
		const char * assetName = IAAtlasAssets_getAssetNameForIndex(assets, i);
		IAImageContext_addAtlas(this, assetName);
	}
}

void IAImageContext_onBitmapUsageBeginFunction(IAImageContext * this, IABitmap * bitmap){
    IABitmapManager_lockBitmapRefFromBeeingDestroyed(this->bitmapManager, bitmap);
}

void IAImageContext_onBitmapUsageEndFunction(IAImageContext * this, IABitmap * bitmap){
    IABitmapManager_unlockBitmapRefFromBeeingDestroyed(this->bitmapManager, bitmap);
}

IAImage * IAImageContext_getImage(IAImageContext * this, const char * imageName){
    IAImage * image = IAAutoExpandingHashMap_get(this->images, imageName);
    if(image == NULL){
        logError("Could not load image %s", imageName);
        abort();
    }
    return image;
}

const IAAutoExpandingHashMap * IAImageContext_getImages(IAImageContext * this){
    return this->images;
}

void IAImageContext_deinit(IAImageContext * this){
	IAAutoExpandingHashMap_callFunctionOnAllObjects(this->images, (void (*)(void *)) IAImage_release);
	IAAutoExpandingHashMap_release(this->images);
    IAArrayList_callFunctionOnAllObjects(this->textures, (void (*)(void *)) IATexture_release);
    IAArrayList_release(this->textures);
    IABitmap * bitmap;
    foreach (bitmap in arrayList(&this->bitmaps)){
        IABitmapManager_removeBitmap(this->bitmapManager, bitmap);
    }
    IAArrayList_callFunctionOnAllObjects(&this->bitmaps, (void (*)(void *)) IABitmap_release);
    IAArrayList_deinit(&this->bitmaps);
    IAString_deinit(&this->assetNameTemp);
    IA_decrementInitCount();
}


