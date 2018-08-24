#pragma once

void IAWinTouchHandler_start(float primaryWidthOfScreen, float primaryHeightOfScreen, void(*acquireApplicationLock)(void), void(*releaseApplicationLock)(void));
