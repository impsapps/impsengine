#include "IALibrary.h"
#include "IADrawingBounds.h"
#include "IAOpenGLHeaders.h"
#include "IAViewPort+Internal.h"
#include "IAStructArrayList.h"

#define CLASSNAME "IADrawingBounds"

#ifndef IAStructArrayList_IARect_h
#define IAStructArrayList_IARect_h
IA_STRUCT_ARRAY_LIST(IARect);
#endif

static IAStructArrayList_IARect * boundsStack = NULL;

static void updateBounds(){
	if (IAStructArrayList_IARect_isEmpty(boundsStack)){
		if (glIsEnabled(GL_SCISSOR_TEST)) {
			glDisable(GL_SCISSOR_TEST);
		}
	}else{
		IASize orgSize = IAViewPort_getFrameBufferSize();
		IARect bounds = IARect_makeWithLeftTopPointAndSize(IAPoint_zero, orgSize);
		for (size_t i = 0; i < IAStructArrayList_IARect_getCurrentSize(boundsStack); i++) {
			IARect newBounds = IAStructArrayList_IARect_get(boundsStack, i);
			bounds = IARect_makeAsOverlappingRect(bounds, newBounds);
		}
		if (bounds.size.width >= 1.0f && bounds.size.height >= 1.0f){
			if (glIsEnabled(GL_SCISSOR_TEST) == GL_FALSE) {
				glEnable(GL_SCISSOR_TEST);
			}
			glScissor(bounds.origin.x, orgSize.height - bounds.origin.y - bounds.size.height, bounds.size.width, bounds.size.height);
		}else{
			if (glIsEnabled(GL_SCISSOR_TEST)) {
				glDisable(GL_SCISSOR_TEST);
			}
		}
	}
}

void IADrawingBounds_pushBounds(IARect bounds){
    IASize framebufferSize = IAViewPort_getFrameBufferSize();
	IASize viewSize = IAViewPort_getSize();
	float scaleWidth = framebufferSize.width / viewSize.width;
	float scaleHeight = framebufferSize.height / viewSize.height;
	bounds.origin.x *= scaleWidth;
	bounds.origin.y *= scaleHeight;
	bounds.size.width *= scaleWidth;
	bounds.size.height *= scaleHeight;
	if (boundsStack == NULL){
		IA_STRUCT_ARRAY_LIST_MALLOC_MAKE(boundsStack, IARect, 10);
	}else{
		IA_STRUCT_ARRAY_LIST_REALLOC_MAKE_IF_NEEDED(boundsStack, IARect);
	}
	IAStructArrayList_IARect_add(boundsStack, bounds);
}

void IADrawingBounds_popBounds(){
	debugAssert(boundsStack != NULL);
	debugAssert(IAStructArrayList_IARect_isEmpty(boundsStack) == false);
	IAStructArrayList_IARect_removeLast(boundsStack);
	updateBounds();
}

