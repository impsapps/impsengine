#include "IALibrary.h"
#include "IA_XML_Atlas.h"
#include "expat.h"
#include "IAString+Assets.h"
#include <string.h>

#define CLASSNAME "IA_XML_Atlas"

#ifdef XML_LARGE_SIZE
#if defined(XML_USE_MSC_EXTENSIONS) && _MSC_VER < 1400
#define XML_FMT_INT_MOD "I64"
#else
#define XML_FMT_INT_MOD "ll"
#endif
#else
#define XML_FMT_INT_MOD "l"
#endif


static void XMLCALL IA_XML_Atlas_startElement(IA_XML_Atlas * this, const char * name, const char ** atts){
    if(strcmp(name, "atlas") == 0){
        const char * name = NULL;
        const char * namingTemplate = NULL;
        int count = 1;
        int logoIndex = -1;
        while (*atts != NULL) {
            if (strcmp(atts[0], "name") == 0){
                name = atts[1];
            }else if (strcmp(atts[0], "naming_template") == 0){
                namingTemplate = atts[1];
            }else if (strcmp(atts[0], "count") == 0){
                count = atoi(atts[1]);
            }else if (strcmp(atts[0], "logo_index") == 0){
                logoIndex = atoi(atts[1]);
            }
            atts += 2;
        }
        IAAtlasAssetsAttributes attr = {
            .name = name,
            .namingTemplate = namingTemplate,
            .count = count,
            .logoIndex = logoIndex
        };
        IAAtlasAssets * resource = IAAtlasAssets_new(&attr);
        IAArrayList_add(&this->objects, resource);
    }
}

void IA_XML_Atlas_init(IA_XML_Atlas * this, const char * assetName){
    IAString_init(&this->assetName, assetName);
    IAArrayList_init(&this->objects, 8);
}

void IA_XML_Atlas_load(IA_XML_Atlas * this){
    assert(IAArrayList_isEmpty(&this->objects) && "Resources have already been loaded!");
    IAString * localizedFileData = IAString_newWithAsset(IAString_toCharArray(&this->assetName), "xml");
    XML_Parser parser = XML_ParserCreate(NULL);
    XML_SetUserData(parser, this);
    
    XML_SetElementHandler(parser, (XML_StartElementHandler) IA_XML_Atlas_startElement, NULL);
    
    if (XML_Parse(parser, IAString_toCharArray(localizedFileData), (int) IAString_getLength(localizedFileData), true) == XML_STATUS_ERROR) {
        logError("XMLParser returned error \"%s\" at line %" XML_FMT_INT_MOD "u for xmlResource:\n%s", XML_ErrorString(XML_GetErrorCode(parser)), XML_GetCurrentLineNumber(parser), IAString_toCharArray(localizedFileData));
#ifdef DEBUG
        assert(0 && "Cannot parse xml!");
#endif
    }
    XML_ParserFree(parser);
    
    IAString_release(localizedFileData);
}

IAAtlasAssets * IA_XML_Atlas_get(IA_XML_Atlas * this, const char * name){
    IAAtlasAssets * resource;
    foreach (resource in arrayList(&this->objects)){
        if (strcmp(IAAtlasAssets_getName(resource), name) == 0) {
            return resource;
        }
    }
    return NULL;
}

const IAArrayList * IA_XML_Atlas_getAllAtlasAssets(IA_XML_Atlas * this){
    return &this->objects;
}

void IA_XML_Atlas_deinit(IA_XML_Atlas * this){
    IAString_deinit(&this->assetName);
    IAArrayList_callFunctionOnAllObjects(&this->objects, (void (*)(void *)) IAAtlasAssets_release);
    IAArrayList_deinit(&this->objects);
}

