#include "IALibrary.h"
#include "IAWinTouchHandler.h"
#include "IATouchManager.h"

#undef in

#pragma comment( lib, "user32.lib" )

#include <windows.h>
#include <stdio.h>

#define CLASSNAME "TouchHandler"

static void onTouchBegan(IAPoint point);
static void onTouchMoved(IAPoint point);
static void onTouchEnded(IAPoint point);

static void (*acquireApplicationLock)(void);
static void (*releaseApplicationLock)(void);

static const int mouseTouchId = 1;


HHOOK hMouseHook;
static float offsetX, offsetY;

static LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
	MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
	if (pMouseStruct != NULL) {
		IAPoint point = IAPoint_make(pMouseStruct->pt.x, pMouseStruct->pt.y);
		point.x -= offsetX;
		point.y -= offsetY;
		if (wParam == WM_LBUTTONDOWN) {
			acquireApplicationLock();
			onTouchBegan(point);
			IAAutoreleasePool_run();
			releaseApplicationLock();
		} else if (wParam == WM_LBUTTONUP) {
			acquireApplicationLock();
			onTouchEnded(point);
			IAAutoreleasePool_run();
			releaseApplicationLock();
		} else if (wParam == WM_MOUSEMOVE) {
			acquireApplicationLock();
			onTouchMoved(point);
			IAAutoreleasePool_run();
			releaseApplicationLock();
		}
	}
	return CallNextHookEx(hMouseHook, nCode, wParam, lParam);
}

static DWORD WINAPI MouseStartRoutine(LPVOID lpParm) {
	acquireApplicationLock();
	IAAutoreleasePool_begin();
	releaseApplicationLock();
	HINSTANCE hInstance = GetModuleHandle(NULL);

	hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, mouseProc, hInstance, 0);

	MSG message;
	while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	UnhookWindowsHookEx(hMouseHook);
	acquireApplicationLock();
	IAAutoreleasePool_end();
	releaseApplicationLock();
	return 0;
}

void IAWinTouchHandler_start(void(*acquireApplicationLockTemp)(void), void(*releaseApplicationLockTemp)(void)){
	acquireApplicationLock = acquireApplicationLockTemp;
	releaseApplicationLock = releaseApplicationLockTemp;

	DWORD dwThread;
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MouseStartRoutine, NULL, 0, &dwThread);
}

void IAWinTouchHandler_setWindowOffset(float offsetXTemp, float offsetYTemp){
	offsetX = offsetXTemp;
	offsetY = offsetYTemp;
}

static void onTouchBegan(IAPoint point) {
	IATouchHandler * touchHandler = IATouchManager_getTouchHandler(mouseTouchId);
	if (touchHandler == NULL) 
	{
		touchHandler = IATouchManager_createNewTouchHandler(mouseTouchId, point);
		IATouchManager_onTouchBegan(1, &touchHandler);
	}
}

static void onTouchMoved(IAPoint point) {
	IATouchHandler * touchHandler = IATouchManager_getTouchHandler(mouseTouchId);
	if (touchHandler != NULL)
	{
		IATouchHandler_setTouchLocation(touchHandler, point);
		IATouchManager_onTouchMoved(1, &touchHandler);
	}
}

static void onTouchEnded(IAPoint point) {
	IATouchHandler * touchHandler = IATouchManager_getTouchHandler(mouseTouchId);
	if (touchHandler != NULL)
	{
		IATouchHandler_setTouchLocation(touchHandler, point);
		IATouchManager_onTouchEnded(1, &touchHandler);
		IATouchManager_destroyTouchHandler(touchHandler);
	}
}

