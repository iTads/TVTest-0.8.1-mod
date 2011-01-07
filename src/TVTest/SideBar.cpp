#include "stdafx.h"
#include "TVTest.h"
#include "SideBar.h"
#include "DrawUtil.h"
#include "resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#define SIDE_BAR_CLASS APP_NAME TEXT(" Side Bar")
#define ICON_WIDTH			16
#define ICON_HEIGHT			16
#define PADDING_WIDTH		1
#define BUTTON_MARGIN		3
#define SEPARATOR_WIDTH		8




HINSTANCE CSideBar::m_hinst=NULL;


bool CSideBar::Initialize(HINSTANCE hinst)
{
	if (m_hinst==NULL) {
		WNDCLASS wc;

		wc.style=CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc=WndProc;
		wc.cbClsExtra=0;
		wc.cbWndExtra=0;
		wc.hInstance=hinst;
		wc.hIcon=NULL;
		wc.hCursor=LoadCursor(NULL,IDC_ARROW);
		wc.hbrBackground=NULL;
		wc.lpszMenuName=NULL;
		wc.lpszClassName=SIDE_BAR_CLASS;
		if (RegisterClass(&wc)==0)
			return false;
		m_hinst=hinst;
	}
	return true;
}


CSideBar::CSideBar(const CCommandList *pCommandList)
	: m_fShowTooltips(true)
	, m_hbmIcons(NULL)
	, m_fVertical(true)
	, m_HotItem(-1)
	, m_ClickItem(-1)
	, m_fTrackMouseEvent(false)
	, m_pEventHandler(NULL)
	, m_pCommandList(pCommandList)
{
	m_Theme.ItemStyle.Gradient.Type=Theme::GRADIENT_NORMAL;
	m_Theme.ItemStyle.Gradient.Direction=Theme::DIRECTION_HORZ;
	m_Theme.ItemStyle.Gradient.Color1=RGB(192,192,192);
	m_Theme.ItemStyle.Gradient.Color2=RGB(192,192,192);
	m_Theme.ItemStyle.Border.Type=Theme::BORDER_NONE;
	m_Theme.ItemStyle.TextColor=RGB(0,0,0);
	m_Theme.HighlightItemStyle.Gradient.Type=Theme::GRADIENT_NORMAL;
	m_Theme.HighlightItemStyle.Gradient.Direction=Theme::DIRECTION_HORZ;
	m_Theme.HighlightItemStyle.Gradient.Color1=RGB(128,128,128);
	m_Theme.HighlightItemStyle.Gradient.Color2=RGB(128,128,128);
	m_Theme.HighlightItemStyle.Border.Type=Theme::BORDER_NONE;
	m_Theme.HighlightItemStyle.TextColor=RGB(255,255,255);
	m_Theme.CheckItemStyle=m_Theme.ItemStyle;
	m_Theme.CheckItemStyle.Border.Type=Theme::BORDER_SUNKEN;
	m_Theme.CheckItemStyle.Border.Color=RGB(192,192,192);
	m_Theme.Border.Type=Theme::BORDER_RAISED;
	m_Theme.Border.Color=RGB(192,192,192);
}


CSideBar::~CSideBar()
{
	Destroy();
	if (m_pEventHandler!=NULL)
		m_pEventHandler->m_pSideBar=NULL;
	if (m_hbmIcons!=NULL)
		::DeleteObject(m_hbmIcons);
}


bool CSideBar::Create(HWND hwndParent,DWORD Style,DWORD ExStyle,int ID)
{
	return CreateBasicWindow(hwndParent,Style,ExStyle,ID,
							 SIDE_BAR_CLASS,NULL,m_hinst);
}


int CSideBar::GetBarWidth() const
{
	return (m_fVertical?ICON_WIDTH:ICON_HEIGHT)+BUTTON_MARGIN*2+PADDING_WIDTH*2;
}


bool CSideBar::SetIconImage(HBITMAP hbm,COLORREF crTransparent)
{
	if (hbm==NULL)
		return false;
	if (m_hbmIcons!=NULL)
		::DeleteObject(m_hbmIcons);
	m_hbmIcons=hbm;
	m_IconTransparentColor=crTransparent;
	if (m_hwnd!=NULL)
		Invalidate();
	return true;
}


void CSideBar::DeleteAllItems()
{
	m_ItemList.clear();
	m_Tooltip.DeleteAllTools();
}


bool CSideBar::AddItem(const SideBarItem *pItem)
{
	return AddItems(pItem,1);
}


bool CSideBar::AddItems(const SideBarItem *pItemList,int NumItems)
{
	if (pItemList==NULL || NumItems<=0)
		return false;

	size_t OldSize=m_ItemList.size();
	m_ItemList.resize(OldSize+NumItems);
	::CopyMemory(&m_ItemList[OldSize],pItemList,NumItems*sizeof(SideBarItem));

	if (m_Tooltip.IsCreated()) {
		for (int i=0;i<NumItems;i++) {
			if (pItemList[i].Command!=ITEM_SEPARATOR) {
				RECT rc;

				GetItemRect((int)OldSize+i,&rc);
				m_Tooltip.AddTool((UINT)OldSize+i,rc);
			}
		}
	}
	return true;
}


int CSideBar::CommandToIndex(int Command) const
{
	for (size_t i=0;i<m_ItemList.size();i++) {
		if (m_ItemList[i].Command==Command)
			return (int)i;
	}
	return -1;
}


bool CSideBar::EnableItem(int Command,bool fEnable)
{
	int Index=CommandToIndex(Command);

	if (Index<0)
		return false;
	if (((m_ItemList[Index].Flags&ITEM_FLAG_DISABLED)==0)!=fEnable) {
		m_ItemList[Index].Flags^=ITEM_FLAG_DISABLED;
		if (!fEnable && m_HotItem==Index)
			m_HotItem=-1;
		UpdateItem(Index);
	}
	return true;
}


bool CSideBar::IsItemEnabled(int Command) const
{
	int Index=CommandToIndex(Command);

	if (Index<0)
		return false;
	return (m_ItemList[Index].Flags&ITEM_FLAG_DISABLED)==0;
}


bool CSideBar::CheckItem(int Command,bool fCheck)
{
	int Index=CommandToIndex(Command);

	if (Index<0)
		return false;
	if (((m_ItemList[Index].Flags&ITEM_FLAG_CHECKED)!=0)!=fCheck) {
		m_ItemList[Index].Flags^=ITEM_FLAG_CHECKED;
		UpdateItem(Index);
	}
	return true;
}


bool CSideBar::CheckRadioItem(int First,int Last,int Check)
{
	if (First>Last)
		return false;
	for (int i=First;i<=Last;i++)
		CheckItem(i,i==Check);
	return true;
}


bool CSideBar::IsItemChecked(int Command) const
{
	int Index=CommandToIndex(Command);

	if (Index<0)
		return false;
	return (m_ItemList[Index].Flags&ITEM_FLAG_CHECKED)!=0;
}


bool CSideBar::SetTheme(const ThemeInfo *pTheme)
{
	if (pTheme==NULL)
		return false;
	m_Theme=*pTheme;
	if (m_hwnd!=NULL)
		Invalidate();
	return true;
}


bool CSideBar::GetTheme(ThemeInfo *pTheme) const
{
	if (pTheme==NULL)
		return false;
	*pTheme=m_Theme;
	return true;
}


void CSideBar::ShowToolTips(bool fShow)
{
	if (m_fShowTooltips!=fShow) {
		m_fShowTooltips=fShow;
		m_Tooltip.Enable(fShow);
	}
}


void CSideBar::SetVertical(bool fVertical)
{
	if (m_fVertical!=fVertical) {
		m_fVertical=fVertical;
		if (m_hwnd!=NULL) {
			Invalidate();
			UpdateTooltipsRect();
		}
	}
}


void CSideBar::SetEventHandler(CEventHandler *pHandler)
{
	if (m_pEventHandler!=NULL)
		m_pEventHandler->m_pSideBar=NULL;
	if (pHandler!=NULL)
		pHandler->m_pSideBar=this;
	m_pEventHandler=pHandler;
}


LRESULT CSideBar::OnMessage(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		{
			LPCREATESTRUCT pcs=reinterpret_cast<LPCREATESTRUCT>(lParam);

			m_Tooltip.Create(hwnd);
			m_Tooltip.Enable(m_fShowTooltips);
			for (int i=0;i<(int)m_ItemList.size();i++) {
				if (m_ItemList[i].Command!=ITEM_SEPARATOR) {
					RECT rc;
					GetItemRect(i,&rc);
					m_Tooltip.AddTool(i,rc);
				}
			}

			m_HotItem=-1;
			m_fTrackMouseEvent=false;
		}
		return 0;

	case WM_SIZE:
		if (m_HotItem>=0) {
			UpdateItem(m_HotItem);
			m_HotItem=-1;
		}
		UpdateTooltipsRect();
		return 0;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;

			::BeginPaint(hwnd,&ps);
			Draw(ps.hdc,ps.rcPaint);
			::EndPaint(hwnd,&ps);
		}
		return 0;

	case WM_MOUSEMOVE:
		{
			int x=GET_X_LPARAM(lParam),y=GET_Y_LPARAM(lParam);
			int HotItem=HitTest(x,y);

			if (HotItem>=0
					&& (m_ItemList[HotItem].Command==ITEM_SEPARATOR
						|| (m_ItemList[HotItem].Flags&ITEM_FLAG_DISABLED)!=0))
				HotItem=-1;
			if (GetCapture()==hwnd) {
				if (HotItem!=m_ClickItem)
					HotItem=-1;
				if (HotItem!=m_HotItem) {
					int OldHotItem;

					OldHotItem=m_HotItem;
					m_HotItem=HotItem;
					if (OldHotItem>=0)
						UpdateItem(OldHotItem);
					if (m_HotItem>=0)
						UpdateItem(m_HotItem);
				}
			} else {
				if (HotItem!=m_HotItem) {
					int OldHotItem;

					OldHotItem=m_HotItem;
					m_HotItem=HotItem;
					if (OldHotItem>=0)
						UpdateItem(OldHotItem);
					if (m_HotItem>=0)
						UpdateItem(m_HotItem);
				}
				// WM_MOUSELEAVE が送られなくても無効にされる事があるようだ
				/*if (!m_fTrackMouseEvent)*/ {
					TRACKMOUSEEVENT tme;

					tme.cbSize=sizeof(TRACKMOUSEEVENT);
					tme.dwFlags=TME_LEAVE;
					tme.hwndTrack=hwnd;
					if (::TrackMouseEvent(&tme))
						m_fTrackMouseEvent=true;
				}
			}
		}
		return 0;

	case WM_MOUSELEAVE:
		if (m_HotItem>=0) {
			UpdateItem(m_HotItem);
			m_HotItem=-1;
		}
		m_fTrackMouseEvent=false;
		if (m_pEventHandler)
			m_pEventHandler->OnMouseLeave();
		return 0;

	case WM_LBUTTONDOWN:
		if (m_HotItem>=0) {
			m_ClickItem=m_HotItem;
			::SetCapture(hwnd);
		}
		return 0;

	case WM_LBUTTONUP:
		if (::GetCapture()==hwnd) {
			::ReleaseCapture();
			if (m_HotItem>=0) {
				if (m_pEventHandler!=NULL)
					m_pEventHandler->OnCommand(m_ItemList[m_HotItem].Command);
			}
		}
		return 0;

	case WM_RBUTTONDOWN:
		if (m_pEventHandler!=NULL)
			m_pEventHandler->OnRButtonDown(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
		return 0;

	case WM_SETCURSOR:
		if (LOWORD(lParam)==HTCLIENT) {
			if (m_HotItem>=0) {
				::SetCursor(::LoadCursor(NULL,IDC_HAND));
				return TRUE;
			}
		}
		break;

	case WM_NOTIFY:
		switch (reinterpret_cast<NMHDR*>(lParam)->code) {
		case TTN_NEEDTEXT:
			{
				LPNMTTDISPINFO pnmttdi=reinterpret_cast<LPNMTTDISPINFO>(lParam);

				m_pCommandList->GetCommandName(
					m_pCommandList->IDToIndex(m_ItemList[pnmttdi->hdr.idFrom].Command),
					pnmttdi->szText,lengthof(pnmttdi->szText));
				pnmttdi->lpszText=pnmttdi->szText;
				pnmttdi->hinst=NULL;
			}
			return 0;

		case TTN_SHOW:
			if (m_fVertical) {
				LPNMHDR pnmh=reinterpret_cast<LPNMHDR>(lParam);
				RECT rcBar,rcTip;
				int x,y;

				::GetWindowRect(hwnd,&rcBar);
				::GetWindowRect(pnmh->hwndFrom,&rcTip);
				x=rcBar.right-PADDING_WIDTH;
				y=rcTip.top;
				HMONITOR hMonitor=::MonitorFromRect(&rcTip,MONITOR_DEFAULTTONULL);
				if (hMonitor!=NULL) {
					MONITORINFO mi;

					mi.cbSize=sizeof(mi);
					if (::GetMonitorInfo(hMonitor,&mi)) {
						if (x>=mi.rcMonitor.right-16)
							x=(rcBar.left+PADDING_WIDTH)-(rcTip.right-rcTip.left);
					}
				}
				::SetWindowPos(pnmh->hwndFrom,HWND_TOPMOST,
							   x,y,rcTip.right-rcTip.left,rcTip.bottom-rcTip.top,
							   SWP_NOACTIVATE);
				return TRUE;
			}
			break;
		}
		break;

	case WM_DESTROY:
		m_Tooltip.Destroy();
		return 0;
	}
	return ::DefWindowProc(hwnd,uMsg,wParam,lParam);
}


void CSideBar::GetItemRect(int Item,RECT *pRect) const
{
	int Offset=PADDING_WIDTH;

	for (int i=0;i<Item;i++) {
		if (m_ItemList[i].Command==ITEM_SEPARATOR) {
			Offset+=SEPARATOR_WIDTH;
		} else {
			if (m_fVertical)
				Offset+=ICON_HEIGHT+BUTTON_MARGIN*2;
			else
				Offset+=ICON_WIDTH+BUTTON_MARGIN*2;
		}
	}
	if (m_fVertical) {
		pRect->left=PADDING_WIDTH;
		pRect->right=PADDING_WIDTH+ICON_WIDTH+BUTTON_MARGIN*2;
		pRect->top=Offset;
		pRect->bottom=Offset+(m_ItemList[Item].Command==ITEM_SEPARATOR?SEPARATOR_WIDTH:ICON_HEIGHT+BUTTON_MARGIN*2);
	} else {
		pRect->top=PADDING_WIDTH;
		pRect->bottom=PADDING_WIDTH+ICON_HEIGHT+BUTTON_MARGIN*2;
		pRect->left=Offset;
		pRect->right=Offset+(m_ItemList[Item].Command==ITEM_SEPARATOR?SEPARATOR_WIDTH:ICON_WIDTH+BUTTON_MARGIN*2);
	}
}


void CSideBar::UpdateItem(int Item)
{
	if (m_hwnd!=NULL) {
		RECT rc;

		GetItemRect(Item,&rc);
		Invalidate(&rc);
	}
}


int CSideBar::HitTest(int x,int y) const
{
	POINT pt;

	pt.x=x;
	pt.y=y;
	for (int i=0;i<(int)m_ItemList.size();i++) {
		RECT rc;
		GetItemRect(i,&rc);
		if (::PtInRect(&rc,pt))
			return i;
	}
	return -1;
}


void CSideBar::UpdateTooltipsRect()
{
	for (int i=0;i<(int)m_ItemList.size();i++) {
		RECT rc;

		GetItemRect(i,&rc);
		m_Tooltip.SetToolRect(i,rc);
	}
}


static Theme::GradientDirection GetGradientDirection(bool fVertical,Theme::GradientDirection Direction)
{
	if (fVertical)
		return Direction;
	switch (Direction) {
	case Theme::DIRECTION_HORZ:			Direction=Theme::DIRECTION_VERT;		break;
	case Theme::DIRECTION_VERT:			Direction=Theme::DIRECTION_HORZ;		break;
	case Theme::DIRECTION_HORZMIRROR:	Direction=Theme::DIRECTION_VERTMIRROR;	break;
	case Theme::DIRECTION_VERTMIRROR:	Direction=Theme::DIRECTION_HORZMIRROR;	break;
	}
	return Direction;
}

void CSideBar::Draw(HDC hdc,const RECT &PaintRect)
{
	RECT rcClient,rc;
	HDC hdcMemory;
	HBITMAP hbmOld;

	GetClientRect(&rcClient);
	rc=rcClient;
	if (m_fVertical) {
		rc.top=PaintRect.top;
		rc.bottom=PaintRect.bottom;
	} else {
		rc.left=PaintRect.left;
		rc.right=PaintRect.right;
	}
	Theme::GradientInfo Gradient;
	Gradient=m_Theme.ItemStyle.Gradient;
	Gradient.Direction=GetGradientDirection(m_fVertical,Gradient.Direction);
	Theme::FillGradient(hdc,&rc,&Gradient);
	hdcMemory=::CreateCompatibleDC(hdc);
	hbmOld=static_cast<HBITMAP>(::SelectObject(hdcMemory,m_hbmIcons));
	for (int i=0;i<(int)m_ItemList.size();i++) {
		GetItemRect(i,&rc);
		if (m_ItemList[i].Command!=ITEM_SEPARATOR
				&& rc.left<PaintRect.right && rc.right>PaintRect.left
				&& rc.top<PaintRect.bottom && rc.bottom>PaintRect.top) {
			COLORREF ForeColor;

			if (m_HotItem==i) {
				Theme::Style Style=m_Theme.HighlightItemStyle;
				Style.Gradient.Direction=
					GetGradientDirection(m_fVertical,Style.Gradient.Direction);
				if ((m_ItemList[i].Flags&ITEM_FLAG_CHECKED)!=0)
					Style.Border=m_Theme.CheckItemStyle.Border;
				Theme::DrawStyleBackground(hdc,&rc,&Style);
				ForeColor=m_Theme.HighlightItemStyle.TextColor;
			} else {
				if ((m_ItemList[i].Flags&ITEM_FLAG_CHECKED)!=0) {
					Theme::Style Style=m_Theme.CheckItemStyle;
					Style.Gradient.Direction=
						GetGradientDirection(m_fVertical,Style.Gradient.Direction);
					Theme::DrawStyleBackground(hdc,&rc,&Style);
					ForeColor=m_Theme.CheckItemStyle.TextColor;
				} else {
					ForeColor=m_Theme.ItemStyle.TextColor;
				}
				if ((m_ItemList[i].Flags&ITEM_FLAG_DISABLED)!=0)
					ForeColor=MixColor(ForeColor,
									   MixColor(m_Theme.ItemStyle.Gradient.Color1,
												m_Theme.ItemStyle.Gradient.Color2));
			}
			DrawUtil::DrawMonoColorDIB(hdc,
									   rc.left+BUTTON_MARGIN,rc.top+BUTTON_MARGIN,
									   hdcMemory,
									   m_ItemList[i].Icon*ICON_WIDTH,0,
									   ICON_WIDTH,ICON_HEIGHT,ForeColor);
		}
	}
	/*
	if ((m_fVertical && PaintRect.bottom>rc.bottom)
			|| (!m_fVertical && PaintRect.right>rc.right)) {
		Theme::GradientInfo Gradient;

		if (m_fVertical) {
			rc.top=rc.bottom;
			rc.bottom=PaintRect.bottom;
		} else {
			rc.left=rc.right;
			rc.right=PaintRect.right;
		}
		Gradient=m_Theme.ItemStyle.Gradient;
		Gradient.Direction=FillDir;
		Theme::FillGradient(hdc,&rc,&Gradient);
	}
	*/
	::SelectObject(hdcMemory,hbmOld);
	::DeleteDC(hdcMemory);
	Theme::DrawBorder(hdc,rcClient,&m_Theme.Border);
}




CSideBar::CEventHandler::CEventHandler()
	: m_pSideBar(NULL)
{
}


CSideBar::CEventHandler::~CEventHandler()
{
	if (m_pSideBar!=NULL)
		m_pSideBar->SetEventHandler(NULL);
}
