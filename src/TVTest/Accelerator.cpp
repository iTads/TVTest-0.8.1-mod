#include "stdafx.h"
#include "TVTest.h"
#include "AppMain.h"
#include "Accelerator.h"
#include "Menu.h"
#include "DialogUtil.h"
#include "resource.h"


#define MAKE_ACCEL_PARAM(i,mod,key) (((i)<<16)|((mod)<<8)|(key))
#define GET_ACCEL_INDEX(param) ((param)>>16)
#define GET_ACCEL_MOD(param) ((BYTE)(((param)>>8)&0xFF))
#define GET_ACCEL_KEY(param) ((BYTE)((param)&0xFF))


static const struct {
	unsigned int KeyCode;
	LPCTSTR pszText;
} AccelKeyList[] = {
	{VK_BACK,		TEXT("BS")},
	{VK_TAB,		TEXT("Tab")},
	{VK_CLEAR,		TEXT("Clear")},
	{VK_RETURN,		TEXT("Enter")},
	{VK_PAUSE,		TEXT("Pause")},
	{VK_ESCAPE,		TEXT("Esc")},
	{VK_SPACE,		TEXT("Space")},
	{VK_PRIOR,		TEXT("PgUp")},
	{VK_NEXT,		TEXT("PgDown")},
	{VK_END,		TEXT("End")},
	{VK_HOME,		TEXT("Home")},
	{VK_LEFT,		TEXT("��")},
	{VK_UP,			TEXT("��")},
	{VK_RIGHT,		TEXT("��")},
	{VK_DOWN,		TEXT("��")},
	{VK_SELECT,		TEXT("Select")},
	{VK_PRINT,		TEXT("Print")},
	{VK_EXECUTE,	TEXT("Execute")},
	{VK_INSERT,		TEXT("Ins")},
	{VK_DELETE,		TEXT("Del")},
	{VK_HELP,		TEXT("Help")},
	{'0',			TEXT("0")},
	{'1',			TEXT("1")},
	{'2',			TEXT("2")},
	{'3',			TEXT("3")},
	{'4',			TEXT("4")},
	{'5',			TEXT("5")},
	{'6',			TEXT("6")},
	{'7',			TEXT("7")},
	{'8',			TEXT("8")},
	{'9',			TEXT("9")},
	{'A',			TEXT("A")},
	{'B',			TEXT("B")},
	{'C',			TEXT("C")},
	{'D',			TEXT("D")},
	{'E',			TEXT("E")},
	{'F',			TEXT("F")},
	{'G',			TEXT("G")},
	{'H',			TEXT("H")},
	{'I',			TEXT("I")},
	{'J',			TEXT("J")},
	{'K',			TEXT("K")},
	{'L',			TEXT("L")},
	{'M',			TEXT("M")},
	{'N',			TEXT("N")},
	{'O',			TEXT("O")},
	{'P',			TEXT("P")},
	{'Q',			TEXT("Q")},
	{'R',			TEXT("R")},
	{'S',			TEXT("S")},
	{'T',			TEXT("T")},
	{'U',			TEXT("U")},
	{'V',			TEXT("V")},
	{'W',			TEXT("W")},
	{'X',			TEXT("X")},
	{'Y',			TEXT("Y")},
	{'Z',			TEXT("Z")},
	{VK_NUMPAD0,	TEXT("Num0")},
	{VK_NUMPAD1,	TEXT("Num1")},
	{VK_NUMPAD2,	TEXT("Num2")},
	{VK_NUMPAD3,	TEXT("Num3")},
	{VK_NUMPAD4,	TEXT("Num4")},
	{VK_NUMPAD5,	TEXT("Num5")},
	{VK_NUMPAD6,	TEXT("Num6")},
	{VK_NUMPAD7,	TEXT("Num7")},
	{VK_NUMPAD8,	TEXT("Num8")},
	{VK_NUMPAD9,	TEXT("Num9")},
	{VK_MULTIPLY,	TEXT("Num*")},
	{VK_ADD,		TEXT("Num+")},
	{VK_SUBTRACT,	TEXT("Num-")},
	{VK_DECIMAL,	TEXT("Num.")},
	{VK_DIVIDE,		TEXT("Num/")},
	{VK_F1,			TEXT("F1")},
	{VK_F2,			TEXT("F2")},
	{VK_F3,			TEXT("F3")},
	{VK_F4,			TEXT("F4")},
	{VK_F5,			TEXT("F5")},
	{VK_F6,			TEXT("F6")},
	{VK_F7,			TEXT("F7")},
	{VK_F8,			TEXT("F8")},
	{VK_F9,			TEXT("F9")},
	{VK_F10,		TEXT("F10")},
	{VK_F11,		TEXT("F11")},
	{VK_F12,		TEXT("F12")},
};

static struct {
	LPCTSTR pszText;
	WORD Command;
} CommandList[] = {
	{TEXT("Zoom20"),				CM_ZOOM_20},
	{TEXT("Zoom25"),				CM_ZOOM_25},
	{TEXT("Zoom33"),				CM_ZOOM_33},
	{TEXT("Zoom50"),				CM_ZOOM_50},
	{TEXT("Zoom66"),				CM_ZOOM_66},
	{TEXT("Zoom100"),				CM_ZOOM_100},
	{TEXT("Zoom150"),				CM_ZOOM_150},
	{TEXT("Zoom200"),				CM_ZOOM_200},
	{TEXT("AspectRatio"),			CM_ASPECTRATIO},
	{TEXT("AspectDefault"),			CM_ASPECTRATIO_DEFAULT},
	{TEXT("Aspect16x9"),			CM_ASPECTRATIO_16x9},
	{TEXT("LetterBox"),				CM_ASPECTRATIO_LETTERBOX},
	{TEXT("SuperFrame"),			CM_ASPECTRATIO_SUPERFRAME},
	{TEXT("SideCut"),				CM_ASPECTRATIO_SIDECUT},
	{TEXT("Aspect4x3"),				CM_ASPECTRATIO_4x3},
	{TEXT("Fullscreen"),			CM_FULLSCREEN},
	{TEXT("AlwaysOnTop"),			CM_ALWAYSONTOP},
	{TEXT("ChannelUp"),				CM_CHANNEL_UP},
	{TEXT("ChannelDown"),			CM_CHANNEL_DOWN},
	{TEXT("Mute"),					CM_VOLUME_MUTE},
	{TEXT("VolumeUp"),				CM_VOLUME_UP},
	{TEXT("VolumeDown"),			CM_VOLUME_DOWN},
	{TEXT("VolumeNormalizeNone"),	CM_VOLUMENORMALIZE_NONE},
	{TEXT("VolumeNormalize125"),	CM_VOLUMENORMALIZE_125},
	{TEXT("VolumeNormalize150"),	CM_VOLUMENORMALIZE_150},
	{TEXT("VolumeNormalize200"),	CM_VOLUMENORMALIZE_200},
	{TEXT("SwitchAudio"),			CM_SWITCHAUDIO},
	{TEXT("Stereo"),				CM_STEREO_THROUGH},
	{TEXT("StereoLeft"),			CM_STEREO_LEFT},
	{TEXT("StereoRight"),			CM_STEREO_RIGHT},
	{TEXT("Record"),				CM_RECORD},
	{TEXT("RecordPause"),			CM_RECORD_PAUSE},
	{TEXT("RecordOption"),			CM_RECORDOPTION},
	{TEXT("RecordStopTime"),		CM_RECORDSTOPTIME},
	{TEXT("DisableViewer"),			CM_DISABLEVIEWER},
	{TEXT("CopyImage"),				CM_COPY},
	{TEXT("SaveImage"),				CM_SAVEIMAGE},
	{TEXT("CapturePreview"),		CM_CAPTUREPREVIEW},
	{TEXT("Reset"),					CM_RESET},
	{TEXT("Panel"),					CM_INFORMATION},
	{TEXT("ProgramGuide"),			CM_PROGRAMGUIDE},
	{TEXT("StatusBar"),				CM_STATUSBAR},
	{TEXT("TitleBar"),				CM_TITLEBAR},
	{TEXT("VideoDecoderProperty"),	CM_DECODERPROPERTY},
	{TEXT("Options"),				CM_OPTIONS},
	{TEXT("Close"),					CM_CLOSE},
};




const CAccelerator::KeyInfo CAccelerator::m_DefaultAccelList[] = {
	{CM_ZOOM_100,		VK_HOME,		0},
	{CM_ASPECTRATIO,	'A',			0},
	{CM_FULLSCREEN,		VK_RETURN,		MOD_ALT},
	{CM_ALWAYSONTOP,	'T',			0},
	{CM_VOLUME_MUTE,	'M',			0},
	{CM_VOLUME_UP,		VK_UP,			0},
	{CM_VOLUME_DOWN,	VK_DOWN,		0},
	{CM_SWITCHAUDIO,	'S',			0},
	{CM_CHANNEL_DOWN,	VK_LEFT,		0},
	{CM_CHANNEL_UP,		VK_RIGHT,		0},
	{CM_RECORD,			'R',			0},
	{CM_COPY,			'C',			0},
	{CM_SAVEIMAGE,		'V',			0},
	{CM_INFORMATION,	'I',			0},
	{CM_PROGRAMGUIDE,	'E',			0},
};


CAccelerator::CAccelerator()
{
	m_hAccel=NULL;
	for (size_t i=0;i<lengthof(m_DefaultAccelList);i++)
		m_KeyList.push_back(m_DefaultAccelList[i]);
	m_pMainMenu=NULL;
	m_fFunctionKeyChangeChannel=true;
	m_fDigitKeyChangeChannel=true;
	m_fNumPadChangeChannel=true;
}


CAccelerator::~CAccelerator()
{
	if (m_hAccel)
		DestroyAcceleratorTable(m_hAccel);
}


void CAccelerator::FormatAccelText(LPTSTR pszText,int Key,int Modifiers)
{
	pszText[0]='\0';
	if ((Modifiers&MOD_SHIFT)!=0)
		::lstrcat(pszText,TEXT("Shift+"));
	if ((Modifiers&MOD_CONTROL)!=0)
		::lstrcat(pszText,TEXT("Ctrl+"));
	if ((Modifiers&MOD_ALT)!=0)
		::lstrcat(pszText,TEXT("Alt+"));
	for (int i=0;i<lengthof(AccelKeyList);i++) {
		if (Key==AccelKeyList[i].KeyCode) {
			::lstrcat(pszText,AccelKeyList[i].pszText);
			break;
		}
	}
}


void CAccelerator::SetMenuAccelText(HMENU hmenu,int Command)
{
	TCHAR szText[128],*p;
	size_t i;
	const KeyInfo *pKey=NULL;

	GetMenuString(hmenu,Command,szText,lengthof(szText),MF_BYCOMMAND);
	for (i=0;i<m_KeyList.size();i++) {
		if (m_KeyList[i].Command==Command) {
			pKey=&m_KeyList[i];
			break;
		}
	}
	p=szText;
	while (*p!='\t') {
		if (*p=='\0') {
			if (pKey==NULL)
				return;
			break;
		}
		p++;
	}
	if (pKey!=NULL) {
		p[0]='\t';
		FormatAccelText(p+1,pKey->KeyCode,pKey->Modifiers);
	} else
		*p='\0';
	ModifyMenu(hmenu,Command,
		MF_BYCOMMAND | MFT_STRING | GetMenuState(hmenu,Command,MF_BYCOMMAND),
		Command,szText);
}


HACCEL CAccelerator::CreateAccel()
{
	LPACCEL paccl;
	HACCEL hAccel;

	if (m_KeyList.size()==0)
		return NULL;
	paccl=new ACCEL[m_KeyList.size()];
	for (size_t i=0;i<m_KeyList.size();i++) {
		paccl[i].fVirt=FVIRTKEY;
		if ((m_KeyList[i].Modifiers&MOD_SHIFT)!=0)
			paccl[i].fVirt|=FSHIFT;
		if ((m_KeyList[i].Modifiers&MOD_CONTROL)!=0)
			paccl[i].fVirt|=FCONTROL;
		if ((m_KeyList[i].Modifiers&MOD_ALT)!=0)
			paccl[i].fVirt|=FALT;
		paccl[i].key=m_KeyList[i].KeyCode;
		paccl[i].cmd=m_KeyList[i].Command;
	}
	hAccel=::CreateAcceleratorTable(paccl,m_KeyList.size());
	delete [] paccl;
	return hAccel;
}


bool CAccelerator::Read(CSettings *pSettings)
{
	pSettings->Read(TEXT("FuncKeyChangeChannel"),&m_fFunctionKeyChangeChannel);
	pSettings->Read(TEXT("DigitKeyChangeChannel"),&m_fDigitKeyChangeChannel);
	pSettings->Read(TEXT("NumPadChangeChannel"),&m_fNumPadChangeChannel);
	return true;
}


bool CAccelerator::Write(CSettings *pSettings) const
{
	pSettings->Write(TEXT("FuncKeyChangeChannel"),m_fFunctionKeyChangeChannel);
	pSettings->Write(TEXT("DigitKeyChangeChannel"),m_fDigitKeyChangeChannel);
	pSettings->Write(TEXT("NumPadChangeChannel"),m_fNumPadChangeChannel);
	return true;
}


bool CAccelerator::Load(LPCTSTR pszFileName)
{
	CSettings Settings;
	int i,j;

	if (Settings.Open(pszFileName,TEXT("Accelerator"),CSettings::OPEN_READ)) {
		int NumAccel;

		if (Settings.Read(TEXT("AccelCount"),&NumAccel) && NumAccel>=0) {
			m_KeyList.clear();
			for (i=0;i<NumAccel;i++) {
				TCHAR szName[64],szCommand[32];

				::wsprintf(szName,TEXT("Accel%d_Command"),i);
				if (Settings.Read(szName,szCommand,lengthof(szCommand))
						&& szCommand[0]!='\0') {
					for (j=0;j<lengthof(CommandList);j++) {
						if (::lstrcmpi(CommandList[j].pszText,szCommand)==0) {
							unsigned int Key,Modifiers;

							::wsprintf(szName,TEXT("Accel%d_Key"),i);
							if (Settings.Read(szName,&Key)) {
								KeyInfo Info;

								Modifiers=0;
								::wsprintf(szName,TEXT("Accel%d_Mod"),i);
								Settings.Read(szName,&Modifiers);
								Info.Command=CommandList[j].Command;
								Info.KeyCode=Key;
								Info.Modifiers=Modifiers;
								m_KeyList.push_back(Info);
							}
							break;
						}
					}
				}
			}
		}
		Settings.Close();
	}
	return true;
}


bool CAccelerator::Save(LPCTSTR pszFileName) const
{
	CSettings Settings;

	if (Settings.Open(pszFileName,TEXT("Accelerator"),CSettings::OPEN_WRITE)) {
		bool fDefault=false;
		int i,j;

		if (m_KeyList.size()==lengthof(m_DefaultAccelList)) {
			for (i=0;i<lengthof(m_DefaultAccelList);i++) {
				for (j=0;j<lengthof(m_DefaultAccelList);j++) {
					if (m_DefaultAccelList[i]==m_KeyList[j])
						break;
				}
				if (j==lengthof(m_DefaultAccelList))
					break;
			}
			if (i==lengthof(m_DefaultAccelList))
				fDefault=true;
		}
		Settings.Clear();
		if (!fDefault) {
			Settings.Write(TEXT("AccelCount"),(int)m_KeyList.size());
			for (i=0;i<(int)m_KeyList.size();i++) {
				TCHAR szName[64];

				::wsprintf(szName,TEXT("Accel%d_Command"),i);
				for (j=0;CommandList[j].Command!=m_KeyList[i].Command;j++);
				ASSERT(j<lengthof(CommandList));
				Settings.Write(szName,CommandList[j].pszText);
				::wsprintf(szName,TEXT("Accel%d_Key"),i);
				Settings.Write(szName,(int)m_KeyList[i].KeyCode);
				::wsprintf(szName,TEXT("Accel%d_Mod"),i);
				Settings.Write(szName,(int)m_KeyList[i].Modifiers);
			}
		} else
			Settings.Write(TEXT("AccelCount"),-1);
		Settings.Close();
	}
	return true;
}


bool CAccelerator::Initialize(CMainMenu *pMainMenu)
{
	if (m_hAccel==NULL) {
		m_hAccel=CreateAccel();
	}
	m_pMainMenu=pMainMenu;
	m_pMainMenu->SetAccelerator(this);
	return true;
}


bool CAccelerator::TranslateMessage(HWND hwnd,LPMSG pmsg)
{
	if (m_hAccel!=NULL)
		return ::TranslateAccelerator(hwnd,m_hAccel,pmsg)!=FALSE;
	return false;
}


void CAccelerator::SetMenuAccel(HMENU hmenu)
{
	int Count,i;
	unsigned int State;

	Count=::GetMenuItemCount(hmenu);
	for (i=0;i<Count;i++) {
		State=::GetMenuState(hmenu,i,MF_BYPOSITION);
		if ((State&MF_POPUP)!=0) {
			SetMenuAccel(::GetSubMenu(hmenu,i));
		} else if ((State&MF_SEPARATOR)==0) {
			SetMenuAccelText(hmenu,(int)::GetMenuItemID(hmenu,i));
		}
	}
}


int CAccelerator::CheckAccelKey(HWND hwndList,BYTE Mod,BYTE Key)
{
	LV_ITEM lvi;
	int i;

	lvi.mask=LVIF_PARAM;
	lvi.iSubItem=0;
	for (i=0;i<lengthof(CommandList);i++) {
		lvi.iItem=i;
		ListView_GetItem(hwndList,&lvi);
		if (GET_ACCEL_MOD(lvi.lParam)==Mod && GET_ACCEL_KEY(lvi.lParam)==Key)
			return i;
	}
	return -1;
}


void CAccelerator::SetAccelItem(HWND hwndList,int Index,BYTE Mod,BYTE Key)
{
	LV_ITEM lvi;
	TCHAR szText[64];

	lvi.mask=LVIF_PARAM;
	lvi.iItem=Index;
	lvi.iSubItem=0;
	lvi.lParam=MAKE_ACCEL_PARAM(Index,Mod,Key);
	ListView_SetItem(hwndList,&lvi);
	lvi.mask=LVIF_TEXT;
	lvi.iSubItem=1;
	if (Key!=0) {
		FormatAccelText(szText,Key,Mod);
		lvi.pszText=szText;
	} else {
		lvi.pszText=TEXT("");
	}
	ListView_SetItem(hwndList,&lvi);
}


void CAccelerator::SetDlgItemStatus(HWND hDlg)
{
	HWND hwndList=::GetDlgItem(hDlg,IDC_ACCELERATOR_LIST);
	int Sel,Index;
	BYTE Key,Mod;

	Sel=ListView_GetNextItem(hwndList,-1,LVNI_SELECTED);
	if (Sel>=0) {
		LV_ITEM lvi;

		lvi.mask=LVIF_PARAM;
		lvi.iItem=Sel;
		lvi.iSubItem=0;
		ListView_GetItem(hwndList,&lvi);
		Index=GET_ACCEL_INDEX(lvi.lParam);
		Key=GET_ACCEL_KEY(lvi.lParam);
		Mod=GET_ACCEL_MOD(lvi.lParam);
		for (int i=0;i<lengthof(AccelKeyList);i++) {
			if (AccelKeyList[i].KeyCode==(unsigned)Key) {
				::SendDlgItemMessage(hDlg,IDC_ACCELERATOR_KEY,CB_SETCURSEL,i+1,0);
				break;
			}
		}
		DlgCheckBox_Check(hDlg,IDC_ACCELERATOR_SHIFT,(Mod&MOD_SHIFT)!=0);
		DlgCheckBox_Check(hDlg,IDC_ACCELERATOR_CONTROL,(Mod&MOD_CONTROL)!=0);
		DlgCheckBox_Check(hDlg,IDC_ACCELERATOR_ALT,(Mod&MOD_ALT)!=0);
	} else {
		::SendDlgItemMessage(hDlg,IDC_ACCELERATOR_KEY,CB_SETCURSEL,0,0);
		DlgCheckBox_Check(hDlg,IDC_ACCELERATOR_SHIFT,false);
		DlgCheckBox_Check(hDlg,IDC_ACCELERATOR_CONTROL,false);
		DlgCheckBox_Check(hDlg,IDC_ACCELERATOR_ALT,false);
	}
	EnableDlgItems(hDlg,IDC_ACCELERATOR_KEY,IDC_ACCELERATOR_ALT,Sel>=0);
}


CAccelerator *CAccelerator::GetThis(HWND hDlg)
{
	return static_cast<CAccelerator*>(GetOptions(hDlg));
}


BOOL CALLBACK CAccelerator::DlgProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch (uMsg) {
	case WM_INITDIALOG:
		{
			CAccelerator *pThis=static_cast<CAccelerator*>(OnInitDialog(hDlg,lParam));
			HWND hwndList=::GetDlgItem(hDlg,IDC_ACCELERATOR_LIST);
			LV_COLUMN lvc;

			ListView_SetExtendedListViewStyle(hwndList,LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			lvc.mask=LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
			lvc.fmt=LVCFMT_LEFT;
			lvc.cx=120;
			lvc.pszText=TEXT("�R�}���h");
			ListView_InsertColumn(hwndList,0,&lvc);
			lvc.pszText=TEXT("�L�[");
			ListView_InsertColumn(hwndList,1,&lvc);
			for (int i=0;i<lengthof(CommandList);i++) {
				const KeyInfo *pKey=NULL;
				LV_ITEM lvi;
				TCHAR szText[64];

				for (size_t j=0;j<pThis->m_KeyList.size();j++) {
					if (pThis->m_KeyList[j].Command==CommandList[i].Command) {
						pKey=&pThis->m_KeyList[j];
						break;
					}
				}
				lvi.mask=LVIF_TEXT | LVIF_PARAM;
				lvi.iItem=i;
				lvi.iSubItem=0;
				::LoadString(GetAppClass().GetResourceInstance(),
							 CommandList[i].Command,szText,lengthof(szText));
				lvi.pszText=szText;
				if (pKey!=NULL)
					lvi.lParam=MAKE_ACCEL_PARAM(i,pKey->Modifiers,pKey->KeyCode);
				else
					lvi.lParam=MAKE_ACCEL_PARAM(i,0,0);
				lvi.iItem=ListView_InsertItem(hwndList,&lvi);
				if (pKey!=NULL) {
					lvi.mask=LVIF_TEXT;
					lvi.iSubItem=1;
					FormatAccelText(szText,pKey->KeyCode,pKey->Modifiers);
					ListView_SetItem(hwndList,&lvi);
				}
			}
			for (int i=0;i<2;i++)
				ListView_SetColumnWidth(hwndList,i,LVSCW_AUTOSIZE_USEHEADER);
			::SendDlgItemMessage(hDlg,IDC_ACCELERATOR_KEY,CB_ADDSTRING,0,
														(LPARAM)TEXT("�Ȃ�"));
			for (int i=0;i<lengthof(AccelKeyList);i++)
				::SendDlgItemMessage(hDlg,IDC_ACCELERATOR_KEY,CB_ADDSTRING,0,
											(LPARAM)AccelKeyList[i].pszText);
			SetDlgItemStatus(hDlg);

			CheckDlgButton(hDlg,IDC_OPTIONS_CHANGECH_FUNCTION,
				pThis->m_fFunctionKeyChangeChannel?BST_CHECKED:BST_UNCHECKED);
			CheckDlgButton(hDlg,IDC_OPTIONS_CHANGECH_DIGIT,
				pThis->m_fDigitKeyChangeChannel?BST_CHECKED:BST_UNCHECKED);
			CheckDlgButton(hDlg,IDC_OPTIONS_CHANGECH_NUMPAD,
				pThis->m_fNumPadChangeChannel?BST_CHECKED:BST_UNCHECKED);
		}
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_ACCELERATOR_KEY:
			if (HIWORD(wParam)!=CBN_SELCHANGE)
				break;
		case IDC_ACCELERATOR_SHIFT:
		case IDC_ACCELERATOR_CONTROL:
		case IDC_ACCELERATOR_ALT:
			{
				HWND hwndList=::GetDlgItem(hDlg,IDC_ACCELERATOR_LIST);
				LV_ITEM lvi;
				int Key;

				lvi.iItem=ListView_GetNextItem(hwndList,-1,LVNI_SELECTED);
				if (lvi.iItem<0)
					return TRUE;
				lvi.mask=LVIF_PARAM;
				lvi.iSubItem=0;
				ListView_GetItem(hwndList,&lvi);
				Key=SendDlgItemMessage(hDlg,IDC_ACCELERATOR_KEY,CB_GETCURSEL,0,0);
				if (Key>0) {
					BYTE Mod;
					int i;

					Mod=0;
					if (DlgCheckBox_IsChecked(hDlg,IDC_ACCELERATOR_SHIFT))
						Mod|=MOD_SHIFT;
					if (DlgCheckBox_IsChecked(hDlg,IDC_ACCELERATOR_CONTROL))
						Mod|=MOD_CONTROL;
					if (DlgCheckBox_IsChecked(hDlg,IDC_ACCELERATOR_ALT))
						Mod|=MOD_ALT;
					i=CheckAccelKey(hwndList,Mod,AccelKeyList[Key-1].KeyCode);
					if (i>=0) {
						if (i!=GET_ACCEL_INDEX(lvi.lParam)) {
							TCHAR szCommand[64],szText[128],szMessage[128];

							::LoadString(GetAppClass().GetResourceInstance(),
										 CommandList[i].Command,
										 szCommand,lengthof(szCommand));
							wsprintf(szText,TEXT("���� [%s] �Ɋ��蓖�Ă��Ă��܂��B\r\n���蓖�Ē����܂���?"),szCommand);
							if (::MessageBox(hDlg,szText,NULL,
											MB_YESNO | MB_ICONQUESTION)!=IDYES)
								return TRUE;
							SetAccelItem(hwndList,i,0,0);
						}
					}
					lvi.lParam=MAKE_ACCEL_PARAM(GET_ACCEL_INDEX(lvi.lParam),
											Mod,AccelKeyList[Key-1].KeyCode);
				} else {
					lvi.lParam=
							MAKE_ACCEL_PARAM(GET_ACCEL_INDEX(lvi.lParam),0,0);
				}
				ListView_SetItem(hwndList,&lvi);
				TCHAR szText[64];
				lvi.mask=LVIF_TEXT;
				lvi.iSubItem=1;
				if (Key>0) {
					FormatAccelText(szText,GET_ACCEL_KEY(lvi.lParam),GET_ACCEL_MOD(lvi.lParam));
					lvi.pszText=szText;
				} else {
					lvi.pszText=TEXT("");
				}
				ListView_SetItem(hwndList,&lvi);
			}
			return TRUE;

		case IDC_ACCELERATOR_DEFAULT:
			{
				LV_ITEM lvi;
				HWND hwndList=::GetDlgItem(hDlg,IDC_ACCELERATOR_LIST);
				int i,j;

				lvi.mask=LVIF_PARAM;
				lvi.iSubItem=0;
				for (i=0;i<lengthof(CommandList);i++) {
					BYTE Key=0,Mod=0;

					lvi.iItem=i;
					ListView_GetItem(hwndList,&lvi);
					int Index=GET_ACCEL_INDEX(lvi.lParam);
					for (j=0;j<lengthof(m_DefaultAccelList);j++) {
						if (m_DefaultAccelList[j].Command==CommandList[Index].Command) {
							Key=m_DefaultAccelList[j].KeyCode;
							Mod=m_DefaultAccelList[j].Modifiers;
							break;
						}
					}
					if (GET_ACCEL_KEY(lvi.lParam)!=Key
							|| GET_ACCEL_MOD(lvi.lParam)!=Mod)
						SetAccelItem(hwndList,Index,Mod,Key);
				}
				SetDlgItemStatus(hDlg);
			}
			return TRUE;
		}
		return TRUE;

	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->code) {
		case LVN_ITEMCHANGED:
			SetDlgItemStatus(hDlg);
			break;

		case LVN_KEYDOWN:
			{
				LPNMLVKEYDOWN pnmlvk=reinterpret_cast<LPNMLVKEYDOWN>(lParam);

				if (pnmlvk->wVKey==VK_BACK || pnmlvk->wVKey==VK_DELETE) {
					HWND hwndList=::GetDlgItem(hDlg,IDC_ACCELERATOR_LIST);
					int Sel=ListView_GetNextItem(hwndList,-1,LVNI_SELECTED);

					if (Sel>=0)
						SetAccelItem(hwndList,Sel,0,0);
				}
			}
			break;

		case PSN_APPLY:
			{
				CAccelerator *pThis=GetThis(hDlg);
				HWND hwndList=::GetDlgItem(hDlg,IDC_ACCELERATOR_LIST);
				LV_ITEM lvi;

				pThis->m_KeyList.clear();
				lvi.mask=LVIF_PARAM;
				lvi.iSubItem=0;
				for (int i=0;i<lengthof(CommandList);i++) {
					lvi.iItem=i;
					ListView_GetItem(hwndList,&lvi);
					if (GET_ACCEL_KEY(lvi.lParam)!=0) {
						KeyInfo Info;

						Info.Command=CommandList[i].Command;
						Info.KeyCode=GET_ACCEL_KEY(lvi.lParam);
						Info.Modifiers=GET_ACCEL_MOD(lvi.lParam);
						pThis->m_KeyList.push_back(Info);
					}
				}
				HACCEL hAccel=pThis->CreateAccel();
				if (pThis->m_hAccel!=NULL)
					::DestroyAcceleratorTable(pThis->m_hAccel);
				pThis->m_hAccel=hAccel;
				pThis->m_pMainMenu->SetAccelerator(pThis);

				pThis->m_fFunctionKeyChangeChannel=IsDlgButtonChecked(hDlg,
								IDC_OPTIONS_CHANGECH_FUNCTION)==BST_CHECKED;
				pThis->m_fDigitKeyChangeChannel=IsDlgButtonChecked(hDlg,
									IDC_OPTIONS_CHANGECH_DIGIT)==BST_CHECKED;
				pThis->m_fNumPadChangeChannel=IsDlgButtonChecked(hDlg,
									IDC_OPTIONS_CHANGECH_NUMPAD)==BST_CHECKED;
			}
			break;
		}
		break;
	}
	return FALSE;
}
