#include "IALibrary.h"
#include "IAScrollViewAttributes.h"
#include "IAViewPort.h"

#define CLASSNAME "IAScrollViewAttributes"


static float IAScrollViewAttributes_getScrollPosChangeHorizontal(IAPoint current, IAPoint last) {
	return last.x - current.x;
}
static float IAScrollViewAttributes_getScrollPosChangeVertical(IAPoint current, IAPoint last) {
	return last.y - current.y;
}

static void IAScrollViewAttributes_makeWithGetScrollPosChangeFunc(IAScrollViewAttributes * this, void * correspondingObject, uint64_t(*getTime)(), float(*getScrollPosChange)(IAPoint current, IAPoint last)) {
	*this = (IAScrollViewAttributes) {
		.correspondingObject = correspondingObject,
		.viewPosition = IAViewPort_defaultRectForContent,
		.getScrollPosChange = getScrollPosChange,
		.getTime = getTime
	};
}

void IAScrollViewAttributes_makeHorizontal(IAScrollViewAttributes * this, void * correspondingObject, uint64_t(*getTime)()) {
	IAScrollViewAttributes_makeWithGetScrollPosChangeFunc(this, correspondingObject, getTime, IAScrollViewAttributes_getScrollPosChangeHorizontal);
}

void IAScrollViewAttributes_makeVertical(IAScrollViewAttributes * this, void * correspondingObject, uint64_t(*getTime)()){
	IAScrollViewAttributes_makeWithGetScrollPosChangeFunc(this, correspondingObject, getTime, IAScrollViewAttributes_getScrollPosChangeVertical);
}


