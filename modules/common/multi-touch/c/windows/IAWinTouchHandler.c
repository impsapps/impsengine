#include "IALibrary.h"
#include "IAWinTouchHandler.h"
#include "IATouchManager.h"

#undef in

#define CLASSNAME "TouchHandler"

static const int mouseTouchId = 1;

static void onTouchBegan(IAPoint point);
static void onTouchMoved(IAPoint point);
static void onTouchEnded(IAPoint point);

static float primaryWidthOfScreen;
static float primaryHeightOfScreen;
static void (*acquireApplicationLock)(void);
static void (*releaseApplicationLock)(void);

#pragma comment( lib, "user32.lib" )

#include <windows.h>
#include <stdio.h>

HHOOK hMouseHook;

static LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
	MOUSEHOOKSTRUCT * pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
	if (pMouseStruct != NULL) {
		IAPoint point = IAPoint_make(pMouseStruct->pt.x, pMouseStruct->pt.y);
		point.x = point.x / primaryWidthOfScreen * 3840.0f;
		point.y = point.y / primaryHeightOfScreen * 2160.0f;
		if (wParam == WM_LBUTTONDOWN) {
			acquireApplicationLock();
			onTouchBegan(point);
			releaseApplicationLock();
		} else if (wParam == WM_LBUTTONUP) {
			acquireApplicationLock();
			onTouchEnded(point);
			releaseApplicationLock();
		} else if (wParam == WM_MOUSEMOVE) {
			acquireApplicationLock();
			onTouchMoved(point);
			releaseApplicationLock();
		}
	}
	return CallNextHookEx(hMouseHook, nCode, wParam, lParam);
}

static DWORD WINAPI MyMouseLogger(LPVOID lpParm) {
	HINSTANCE hInstance = GetModuleHandle(NULL);

	hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, mouseProc, hInstance, 0);

	MSG message;
	while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	UnhookWindowsHookEx(hMouseHook);
	return 0;
}

void IAWinTouchHandler_start(float primaryWidthOfScreenTemp, float primaryHeightOfScreenTemp, void(*acquireApplicationLockTemp)(void), void(*releaseApplicationLockTemp)(void)){
	primaryWidthOfScreen = primaryWidthOfScreenTemp;
	primaryHeightOfScreen = primaryHeightOfScreenTemp;
	acquireApplicationLock = acquireApplicationLockTemp;
	releaseApplicationLock = releaseApplicationLockTemp;

	HANDLE hThread;
	DWORD dwThread;

	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MyMouseLogger, NULL, 0, &dwThread);
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

