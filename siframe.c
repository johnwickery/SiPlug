#include <string.h>
#include <stdio.h>
#include "siframe.h"
#include "tabctl.h"
#include "const.h"

extern HWND hwnd_si_frame;
extern HWND hwnd_tab_ctl;
static WNDPROC old_si_frame_proc = NULL;

static BOOL CALLBACK EnumWindowsProc(HWND hwnd,LPARAM lparam)
{
	DWORD processid = *((DWORD*)lparam);
	DWORD threadprocessid = 0;

	GetWindowThreadProcessId(hwnd,&threadprocessid);
	if(threadprocessid == processid && GetParent(hwnd) == NULL)
	{
		*((HWND*)lparam) = hwnd;
		return FALSE;
	}

	return TRUE;
}

HWND GetSiFrameHwnd(void)
{
	DWORD processid = GetCurrentProcessId();
	if(!EnumWindows(EnumWindowsProc,(LPARAM)&processid))
	{
		return (HWND)processid;
	}

	return NULL;
}

static LRESULT CALLBACK SiFrameSubClass(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_NOTIFY:
		{
			LPNMHDR hdr = (LPNMHDR)lParam;
			if(hdr->hwndFrom != hwnd_tab_ctl)
			{
				break;
			}
			
			if(hdr->code == TCN_SELCHANGE)
			{
				SiTabCtl_OnSelChange();
			}
			else if(hdr->code == NM_CLICK)
			{
				SiTabCtl_OnLButtonClk();
			}
			else if(hdr->code == NM_RCLICK)
			{
				/* TRUE must be returned, or si's owner popupmenu will come out */
				return TRUE;
			}
		}
		break;
	case WM_DRAWITEM:
		{
			DRAWITEMSTRUCT* item = (DRAWITEMSTRUCT*)lParam;
            if (item->hwndItem != hwnd_tab_ctl)
                break;
            SiTabCtl_OnDrawItem(item);
		}
		break;
	default:
		break;
	}


	LRESULT lr = CallWindowProc(old_si_frame_proc, hWnd, uMsg, wParam, lParam);
	return lr;
}

void HookSiFrame(void)
{
	old_si_frame_proc = (WNDPROC)GetWindowLong(hwnd_si_frame,GWL_WNDPROC);
	SetWindowLong(hwnd_si_frame,GWL_WNDPROC,(DWORD)SiFrameSubClass);
	
	SiTabCtl_Create(hwnd_si_frame);	
}
