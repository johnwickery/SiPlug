#ifndef __TABCTL__H__
#define __TABCTL__H__

#include <windows.h>
#include <commctrl.h>
#include <wingdi.h>

/* Create tabctl */
void SiTabCtl_Create(HWND parent);
/* Get tabctl count */
int SiTabCtl_GetItemCount(void);
/* Get tabctl row count */
int SiTabCtl_GetRowCount(void);
/* Get tabctl height */
int SiTabCtl_GetHeight(void);
/* Add tabctl item */
void SiTabCtl_AddItem(char* title,HWND hwnd);
/* Find tabctl item */
int SiTabCtl_FindItem(HWND hwnd);
/* Delete tabctl item */
void SiTabCtl_DelItem(HWND hwnd);
/* Set tabctl item text */
void SiTabCtl_SetItemText(HWND hwnd,char* text);
/* Set current tabctl item */
void SiTabCtl_SetCurItem(HWND hwnd);
/* Get current tabctl item */
int SiTabCtl_GetCurItem(void);
/* Get current tabctl item corresponding mdi window */
HWND SiTabCtl_GetMdiHwnd(int item);
/* Close all mdi window */
void SiTabCtl_CloseAllMdiHwnd(BOOL closeCurrent);
/* Judge if row count changed */
BOOL SiTabCtl_IsRowChanged(void);
/* Event tabctl positon change */
void SiTabCtl_OnPosChanging(WINDOWPOS* pos);
/* Event tabctl active item change */
void SiTabCtl_OnSelChange(void);
/* Event double left click tabctl item */
void SiTabCtl_OnLButtonDblClk(void);
/* Event left click tabctl item */
void SiTabCtl_OnLButtonClk(void);
/* Event right click tabctl item */
void SiTabCtl_OnRButtonClk(LPARAM lParam);
/* Redraw tabctl item */
void SiTabCtl_OnDrawItem(DRAWITEMSTRUCT* item);

#endif

