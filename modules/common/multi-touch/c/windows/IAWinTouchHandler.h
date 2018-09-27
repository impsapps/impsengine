#pragma once

void IAWinTouchHandler_start(void(*acquireApplicationLock)(void), void(*releaseApplicationLock)(void));

void IAWinTouchHandler_setWindowOffset(float offsetX, float offsetY);
