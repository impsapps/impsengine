#include "IALibrary.h"
#include "IAFontInformation.h"

#define CLASSNAME "IAFontInformation"


void IAFontInformation_make(IAFontInformation * this, const IAFontInformationAttributes * attributes){
    this->base = IAObject_make(this);
    this->fontSize = IAFontInformationAttributes_getFontSize(attributes);
    this->ascent = IAFontInformationAttributes_getAscent(attributes);
    this->descent = IAFontInformationAttributes_getDescent(attributes);
    this->lineHeight = IAFontInformationAttributes_getLineHeight(attributes);
}


