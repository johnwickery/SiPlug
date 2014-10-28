#ifndef __MDICLIENT__H__
#define __MDICLIENT__H__

#include <windows.h>

/* Get MdiClient handle  */
HWND GetMdiClientHwnd(HWND parent);

/* Resize MdiClient */
void ResizeMdiClient(void);

/* Replace the MdiClient message callback */
void HookMdiClient(void);

#endif
