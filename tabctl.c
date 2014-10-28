/* for mingw */
#ifndef _WIN32_IE
#define _WIN32_IE 0x0500
#endif

#include "const.h"
#include "utils.h"
#include "tabctl.h"

static HMENU hwnd_tab_menu = NULL;
static WNDPROC old_tab_ctl_proc = NULL;
static int row_count = 0;
static COLORREF color_table[10] =
{
	RGB(255,255,255),	/* None */
	RGB(204,182,238),	/* c    */
	RGB(210,227,178),	/* h    */
	RGB(219,236,249),	/* txt  */
	RGB(249,179,180),	/* js   */
	RGB(255,241,134),	/* vb   */
};

#define IDM_TAB_CLOSE_CUR 100
#define IDM_TAB_CLOSE_ALL 101
#define IDM_TAB_CLOSE_OTH 102

extern HWND hwnd_tab_ctl;
extern HWND hwnd_mdi_client;

static LRESULT CALLBACK TabCtlSubClass(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hwnd = NULL;
	LRESULT lr = CallWindowProc(old_tab_ctl_proc, hWnd, uMsg, wParam, lParam);

	switch(uMsg)
	{
	case WM_COMMAND:
		switch(LOWORD(wParam)) {
			case IDM_TAB_CLOSE_CUR:
				hwnd = SiTabCtl_GetMdiHwnd(SiTabCtl_GetCurItem());
				SendMessage(hwnd_mdi_client,WM_MDIDESTROY,(WPARAM)hwnd,0);
				break;
			case IDM_TAB_CLOSE_ALL:
				SiTabCtl_CloseAllMdiHwnd(TRUE);
				break;
			case IDM_TAB_CLOSE_OTH:
				SiTabCtl_CloseAllMdiHwnd(FALSE);
				break;
			default:
				break;
		}
		break;
	case WM_LBUTTONDBLCLK:
		SiTabCtl_OnLButtonDblClk();
		break;
	case WM_RBUTTONUP: /* Get ater WM_NOTIFY-NM_RCLICK */
		SiTabCtl_OnRButtonClk(lParam);
		return TRUE;
	default:
		break;
	}

	return lr;
}

void SiTabCtl_Create(HWND parent)
{
	hwnd_tab_ctl = CreateWindowEx(0,WC_TABCONTROL,"",
		WS_CHILD|WS_VISIBLE|TCS_BOTTOM|TCS_RAGGEDRIGHT|TCS_SCROLLOPPOSITE|TCS_FOCUSNEVER|TCS_OWNERDRAWFIXED,
		0,0,0,SI_TAB_HEIGHT,parent,NULL,NULL,NULL);
								
	HFONT font = CreateFont(16,0,0,0,FW_NORMAL,FALSE,FALSE,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Candara");
	SendMessage(hwnd_tab_ctl,WM_SETFONT,(WPARAM)font,MAKELPARAM(1,0));
							
	row_count = 0;
	old_tab_ctl_proc = (WNDPROC)GetWindowLong(hwnd_tab_ctl,GWL_WNDPROC);
	if(old_tab_ctl_proc == NULL)
	{
		OutputDebugString("old_tab_ctl_proc null!");
	}
	SetWindowLong(hwnd_tab_ctl,GWL_WNDPROC,(DWORD)TabCtlSubClass);

	hwnd_tab_menu = CreatePopupMenu();
	AppendMenu(hwnd_tab_menu, MF_STRING, IDM_TAB_CLOSE_CUR, TEXT("Close"));
	AppendMenu(hwnd_tab_menu, MF_STRING, IDM_TAB_CLOSE_ALL, TEXT("Close All"));
	AppendMenu(hwnd_tab_menu, MF_STRING, IDM_TAB_CLOSE_OTH, TEXT("Close Others"));
}

int SiTabCtl_GetItemCount(void)
{
	return TabCtrl_GetItemCount(hwnd_tab_ctl);
}

int SiTabCtl_GetRowCount(void)
{
	int row = TabCtrl_GetRowCount(hwnd_tab_ctl);
	return row;
}

int SiTabCtl_GetHeight(void)
{
	return (SiTabCtl_GetRowCount()*SI_TAB_HEIGHT);
}

void SiTabCtl_AddItem(char* title,HWND hwnd)
{
	int idx = SiTabCtl_GetItemCount();
	RECT rect;
	TCITEM tci;
	memset(&tci,0,sizeof(TCITEM));
	tci.mask = TCIF_TEXT | TCIF_PARAM;
	tci.pszText = (LPSTR)title;
	tci.lParam = (LPARAM)hwnd;
	TabCtrl_InsertItem(hwnd_tab_ctl,idx,&tci);
	/* Set fixed height */
	SendMessage(hwnd_tab_ctl,TCM_GETITEMRECT,idx,(LPARAM)&rect);
	SendMessage(hwnd_tab_ctl,TCM_SETITEMSIZE,idx,MAKELPARAM(rect.right-rect.left+1,SI_TAB_HEIGHT));
}

int SiTabCtl_FindItem(HWND hwnd)
{
	int rtv = -1;
	int i;
	int count = SiTabCtl_GetItemCount();
	TCITEM tci;
	for(i=0;i<count;i++)
	{
		memset(&tci,0,sizeof(TCITEM));
		tci.mask = TCIF_TEXT | TCIF_PARAM;
		TabCtrl_GetItem(hwnd_tab_ctl,i,&tci);
		if((HWND)tci.lParam == hwnd)
		{
			rtv = i;
			break;
		}
	}

	return rtv;
}

void SiTabCtl_DelItem(HWND hwnd)
{
	int idx = SiTabCtl_FindItem(hwnd);
	if(idx == -1)
		return;
	TabCtrl_DeleteItem(hwnd_tab_ctl,idx);
}

void SiTabCtl_SetItemText(HWND hwnd,char* text)
{
	int idx = SiTabCtl_FindItem(hwnd);
	if(idx == -1)
		return;
	TCITEM tci;
	memset(&tci,0,sizeof(TCITEM));
	tci.mask = TCIF_TEXT | TCIF_PARAM;
	TabCtrl_GetItem(hwnd_tab_ctl,idx,&tci);

	tci.pszText = (LPSTR)text;
	TabCtrl_SetItem(hwnd_tab_ctl,idx,&tci);
}

void SiTabCtl_SetCurItem(HWND hwnd)
{
	int idx = SiTabCtl_FindItem(hwnd);
	if(idx == -1) {
		return;
	}
	TabCtrl_SetCurSel(hwnd_tab_ctl,idx);
}

int SiTabCtl_GetCurItem(void)
{
	return TabCtrl_GetCurSel(hwnd_tab_ctl);
}

HWND SiTabCtl_GetMdiHwnd(int item)
{
	int i;
	TCITEM tci;

	memset(&tci,0,sizeof(TCITEM));
	tci.mask = TCIF_TEXT | TCIF_PARAM;
	TabCtrl_GetItem(hwnd_tab_ctl,item,&tci);
	return (HWND)tci.lParam;
}

void SiTabCtl_CloseAllMdiHwnd(BOOL closeCurrent)
{
	int i;
	HWND activehwnd, hwnd;
	int count = SiTabCtl_GetItemCount();

	activehwnd = SiTabCtl_GetMdiHwnd(SiTabCtl_GetCurItem());

	while (1) {
		hwnd = FindWindowEx(hwnd_mdi_client,activehwnd,SI_CLASSNAME_MDISW,NULL);
		if (hwnd == activehwnd || hwnd == NULL) 
			break;
		SendMessage(hwnd_mdi_client,WM_MDIDESTROY,(WPARAM)hwnd,0);
	}

	activehwnd = SiTabCtl_GetMdiHwnd(SiTabCtl_GetCurItem());
	if (closeCurrent && activehwnd != NULL)
		SendMessage(hwnd_mdi_client,WM_MDIDESTROY,(WPARAM)activehwnd,0);

	return;
}

BOOL SiTabCtl_IsRowChanged(void)
{
	int rtv = FALSE;
	int row = SiTabCtl_GetRowCount();
	if(row_count != row)
	{
		rtv = TRUE;
		row_count = row;
	}

	return rtv;
}

void SiTabCtl_OnPosChanging(WINDOWPOS* pos)
{
	if(!(pos->flags & SWP_NOSIZE))
	{
		int row;
		SetWindowPos(hwnd_tab_ctl,NULL,pos->x,pos->y,pos->cx,SI_TAB_HEIGHT,pos->flags);
		row = SiTabCtl_GetRowCount();
		SetWindowPos(hwnd_tab_ctl,NULL,0,0,pos->cx,SI_TAB_HEIGHT*row,SWP_NOMOVE);
	}
}

void SiTabCtl_OnSelChange(void)
{
	HWND hwnd;
	int idx = SiTabCtl_GetCurItem();
	TCITEM tci;
	memset(&tci,0,sizeof(TCITEM));
	tci.mask = TCIF_TEXT | TCIF_PARAM;
	TabCtrl_GetItem(hwnd_tab_ctl,idx,&tci);
	hwnd = (HWND)tci.lParam;
	SendMessage(GetParent(hwnd),WM_MDIACTIVATE,(WPARAM)hwnd,0);
}

void SiTabCtl_OnLButtonDblClk(void)
{
	HWND hwnd;
	int idx = SiTabCtl_GetCurItem();
	if(idx == -1)
		return;

	TCITEM tci;
	memset(&tci,0,sizeof(TCITEM));
	tci.mask = TCIF_TEXT | TCIF_PARAM;
	TabCtrl_GetItem(hwnd_tab_ctl,idx,&tci);
	hwnd = (HWND)tci.lParam;

	SendMessage(hwnd,WM_SYSCOMMAND,SC_CLOSE,0);
}

void SiTabCtl_OnLButtonClk(void)
{
	int rtv;
	int idx = SiTabCtl_GetCurItem();
	int count = SiTabCtl_GetItemCount();
	if(idx != count)
		return;
	while(count >= 0)
	{
		HWND hwnd;
		TCITEM tci;
		memset(&tci,0,sizeof(TCITEM));
		tci.mask = TCIF_TEXT | TCIF_PARAM;
		TabCtrl_GetItem(hwnd_tab_ctl,count-1,&tci);
		hwnd = (HWND)tci.lParam;

		SendMessage(hwnd,WM_SYSCOMMAND,SC_CLOSE,0);
		count--;
	}
}

void SiTabCtl_OnRButtonClk(LPARAM lParam)
{
	TCHITTESTINFO thti;
	POINT point;

	/* Change tabctl current item */
	thti.pt.x = LOWORD(lParam);
	thti.pt.y = HIWORD(lParam);
	thti.flags = 0;
	int tab = SendMessage(hwnd_tab_ctl, TCM_HITTEST, (WPARAM)0, (LPARAM) & thti);
	if (tab >= 0) {
		TabCtrl_SetCurSel(hwnd_tab_ctl, tab);
		SiTabCtl_OnSelChange();
	}

	GetCursorPos (&point) ;
	/* Show PopUp */
	TrackPopupMenu(hwnd_tab_menu, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON,  
					point.x, point.y, 0, hwnd_tab_ctl, NULL);
}

void SiTabCtl_OnDrawItem(DRAWITEMSTRUCT* item)
{
	HBRUSH hBrush;
	TCITEM tci;
	char text[SI_BUF_SIZE];
	int type;

	memset(&tci,0,sizeof(TCITEM));
	tci.mask = TCIF_TEXT | TCIF_STATE;
	tci.pszText = (LPSTR)text;
	tci.cchTextMax = SI_BUF_SIZE;
	TabCtrl_GetItem(hwnd_tab_ctl,item->itemID,&tci);

	type = GetColorIndex(text);
	/* Create a background brush */
	hBrush = CreateSolidBrush(color_table[type]);
	if(SiTabCtl_GetCurItem() == item->itemID)
	{
		hBrush = CreateSolidBrush(RGB(255,0,0));
	}
    //SetTextColor(lpDrawItem->hDC, RGB(0, 0, 255));
    //FrameRect(item->hDC,&item->rcItem,hBrush);
    FillRect(item->hDC,&item->rcItem,hBrush);
    DeleteObject(hBrush);
    SetBkMode(item->hDC,TRANSPARENT);
    DrawText(item->hDC,text,strlen(text),&item->rcItem,DT_CENTER|DT_LEFT|DT_VCENTER|DT_SINGLELINE);
}
