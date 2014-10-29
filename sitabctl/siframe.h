#ifndef __SIFRAME__H__
#define __SIFRAME__H__

#include <windows.h>

/* Get Frame window handle */
HWND GetSiFrameHwnd(void);

/* Replace the window message callback */
void HookSiFrame(void);

#endif
