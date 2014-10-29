#ifndef __SISW__H__
#define __SISW__H__

#include <windows.h>

/* Get siSw short title */
char* GetSiSwTitle(const char* lpc,char* title);

/* Get si_Sw window procedure */
void HookSiSw(HWND hwnd);

/* Restore si_Sw window procedure */
void UnhookSiSw(HWND hwnd);

#endif
