//
//  IA_XML_Strings.c
//  Hit Verto
//
//  Created by Konstantin Merker on 02.09.15.
//  Copyright (c) 2015 Konstantin Merker, Paul Wallrabe und Martin Krautschick GbR (Imps Apps). All rights reserved.
//

#include "IALibrary.h"
#include "IA_XML_Strings.h"
#include "IALocalisation.h"
#include "expat.h"
#include "IALogger.h"
#include "IAString+Assets.h"

#include <string.h>


#define CLASSNAME "IA_XML_Strings"

#ifdef XML_LARGE_SIZE
#if defined(XML_USE_MSC_EXTENSIONS) && _MSC_VER < 1400
#define XML_FMT_INT_MOD "I64"
#else
#define XML_FMT_INT_MOD "ll"
#endif
#else
#define XML_FMT_INT_MOD "l"
#endif


void XMLCALL IA_XML_Strings_startElement(IA_XML_Strings * this, const char * name, const char ** atts);
void XMLCALL IA_XML_Strings_handleElementData(IA_XML_Strings * this, const char * elementData, int elementDataLength);
void XMLCALL IA_XML_Strings_endElement(IA_XML_Strings * this, const char * name);


void IA_XML_Strings_init(IA_XML_Strings * this, const char * assetName){
    this->strings = IAAutoExpandingHashMap_new();
    this->currentElementKey = NULL;
    this->assetName = IAString_new(assetName);
}

void IA_XML_Strings_load(IA_XML_Strings * this){
    IAString * assetName = IAString_new(IAString_toCharArray(this->assetName));
    IAString_concat(assetName, "-");
    IAString_concat(assetName, IALocalisation_getLocaleId());
    IAString * localizedFileData = IAString_newWithAsset(IAString_toCharArray(assetName), "xml");
    XML_Parser parser = XML_ParserCreate(NULL);
    XML_SetUserData(parser, this);

    XML_SetElementHandler(parser, (XML_StartElementHandler) IA_XML_Strings_startElement, (XML_EndElementHandler) IA_XML_Strings_endElement);
    XML_SetCharacterDataHandler(parser, (XML_CharacterDataHandler) IA_XML_Strings_handleElementData);

    if (XML_Parse(parser, IAString_toCharArray(localizedFileData), (int) IAString_getLength(localizedFileData), true) == XML_STATUS_ERROR) {
        logError("XMLParser returned error \"%s\" at line %" XML_FMT_INT_MOD "u for xmlResource:\n%s", XML_ErrorString(XML_GetErrorCode(parser)), XML_GetCurrentLineNumber(parser), IAString_toCharArray(localizedFileData));
#ifdef DEBUG
        assert(0 && "Cannot parse xml!");
#endif
    }
    XML_ParserFree(parser);
    
    IAString_release(localizedFileData);
    IAString_release(assetName);
}

void XMLCALL IA_XML_Strings_startElement(IA_XML_Strings * this, const char * name, const char ** atts){
    if (strcmp(name, "resources") == 0) {
        
    }else if(strcmp(name, "string") == 0){
        while (*atts != NULL) {
            if (strcmp(atts[0], "name") == 0){
                IAString * key = IAString_new(atts[1]);
                this->currentElementKey = key;
            }
            atts += 2;
        }
    }
}

void XMLCALL IA_XML_Strings_handleElementData(IA_XML_Strings * this, const char * elementData, int elementDataLength){
    if (this->currentElementKey != NULL) {
        IAString * data = IAString_newWithLength(elementData, elementDataLength);
        IAAutoExpandingHashMap_add(this->strings, IAString_toCharArray(this->currentElementKey), data);
        IAString_release(this->currentElementKey);
        this->currentElementKey = NULL;
    }
}

void XMLCALL IA_XML_Strings_endElement(IA_XML_Strings * this, const char * name){
    assert(this->currentElementKey == NULL && "xml file invalid!");
}

IAString * IA_XML_Strings_get(IA_XML_Strings * this, const char * key){
#ifdef DEBUG
    IAString * string = IAAutoExpandingHashMap_get(this->strings, key);
    assert(string != NULL && "Cannot get string!");
    return string;
#else
    return IAAutoExpandingHashMap_get(this->strings, key);
#endif
}

IAAutoExpandingHashMap * IA_XML_Strings_getStrings(IA_XML_Strings * this){
    return this->strings;
}

void IA_XML_Strings_deinit(IA_XML_Strings * this){
    IAAutoExpandingHashMap_callFunctionOnAllObjects(this->strings, (void (*)(void *)) IAString_release);
    IAAutoExpandingHashMap_release(this->strings);
    IAString_release(this->assetName);
}


