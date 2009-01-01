#ifndef DIALOG_UTIL_H
#define DIALOG_UTIL_H


#define DlgCheckBox_Check(hwndDlg,ID,fCheck) \
	CheckDlgButton(hwndDlg,ID,(fCheck)?BST_CHECKED:BST_UNCHECKED)
#define DlgCheckBox_IsChecked(hwndDlg,ID) \
	(IsDlgButtonChecked(hwndDlg,ID)==BST_CHECKED)

#define DlgRadioButton_IsChecked(hwndDlg,ID) DlgCheckBox_IsChecked(hwndDlg,ID)

#define DlgListBox_GetCount(hwndDlg,ID) \
	SendDlgItemMessage(hwndDlg,ID,LB_GETCOUNT,0,0)
#define DlgListBox_AddString(hwndDlg,ID,pszString) \
	SendDlgItemMessage(hwndDlg,ID,LB_ADDSTRING,0,(LPARAM)(pszString))
#define DlgListBox_InsertString(hwndDlg,ID,Index,pszString) \
	SendDlgItemMessage(hwndDlg,ID,LB_INSERTSTRING,Index,(LPARAM)(pszString))
#define DlgListBox_DeleteString(hwndDlg,ID,Index) \
	SendDlgItemMessage(hwndDlg,ID,LB_DELETESTRING,Index,0)
#define DlgListBox_GetString(hwndDlg,ID,Index,pszString) \
	SendDlgItemMessage(hwndDlg,ID,LB_GETTEXT,Index,(LPARAM)(pszString))
#define DlgListBox_GetItemData(hwndDlg,ID,Index) \
	SendDlgItemMessage(hwndDlg,ID,LB_GETITEMDATA,Index,0)
#define DlgListBox_SetItemData(hwndDlg,ID,Index,Data) \
	SendDlgItemMessage(hwndDlg,ID,LB_SETITEMDATA,Index,Data)
#define DlgListBox_GetCurSel(hwndDlg,ID) \
	SendDlgItemMessage(hwndDlg,ID,LB_GETCURSEL,0,0)
#define DlgListBox_SetCurSel(hwndDlg,ID,Index) \
	SendDlgItemMessage(hwndDlg,ID,LB_SETCURSEL,Index,0)
#define DlgListBox_Clear(hwndDlg,ID) \
	SendDlgItemMessage(hwndDlg,ID,LB_RESETCONTENT,0,0)

#define DlgComboBox_LimitText(hwndDlg,ID,Limit) \
	SendDlgItemMessage(hwndDlg,ID,CB_LIMITTEXT,Limit,0)
#define DlgComboBox_GetCount(hwndDlg,ID) \
	SendDlgItemMessage(hwndDlg,ID,CB_GETCOUNT,0,0)
#define DlgComboBox_AddString(hwndDlg,ID,pszString) \
	SendDlgItemMessage(hwndDlg,ID,CB_ADDSTRING,0,(LPARAM)(pszString))
#define DlgComboBox_InsertString(hwndDlg,ID,Index,pszString) \
	SendDlgItemMessage(hwndDlg,ID,CB_INSERTSTRING,Index,(LPARAM)(pszString))
#define DlgComboBox_DeleteString(hwndDlg,ID,Index) \
	SendDlgItemMessage(hwndDlg,ID,CB_DELETESTRING,Index,0)
#define DlgComboBox_GetItemData(hwndDlg,ID,Index) \
	SendDlgItemMessage(hwndDlg,ID,CB_GETITEMDATA,Index,0)
#define DlgComboBox_SetItemData(hwndDlg,ID,Index,Data) \
	SendDlgItemMessage(hwndDlg,ID,CB_SETITEMDATA,Index,Data)
#define DlgComboBox_GetCurSel(hwndDlg,ID) \
	SendDlgItemMessage(hwndDlg,ID,CB_GETCURSEL,0,0)
#define DlgComboBox_SetCurSel(hwndDlg,ID,Index) \
	SendDlgItemMessage(hwndDlg,ID,CB_SETCURSEL,Index,0)
#define DlgComboBox_GetLBString(hwndDlg,ID,Index,pszString) \
	SendDlgItemMessage(hwndDlg,ID,CB_GETLBTEXT,Index,(LPARAM)(pszString))
#define DlgComboBox_GetLBStringLength(hwndDlg,ID,Index) \
	SendDlgItemMessage(hwndDlg,ID,CB_GETLBTEXTLEN,Index,0)
#define DlgComboBox_Clear(hwndDlg,ID) \
	SendDlgItemMessage(hwndDlg,ID,CB_RESETCONTENT,0,0)
#define DlgComboBox_FindString(hwndDlg,ID,First,pszString) \
	SendDlgItemMessage(hwndDlg,ID,CB_FINDSTRING,First,(LPARAM)(pszString));
#define DlgComboBox_FindStringExact(hwndDlg,ID,First,pszString) \
	SendDlgItemMessage(hwndDlg,ID,CB_FINDSTRINGEXACT,First,(LPARAM)(pszString));

void EnableDlgItem(HWND hDlg,int ID,bool fEnable);
void EnableDlgItems(HWND hDlg,int FirstID,int LastID,bool fEnable);
void InvalidateDlgItem(HWND hDlg,int ID,bool fErase=true);
void ShowDlgItem(HWND hDlg,int ID,bool fShow);
int GetDlgItemTextLength(HWND hDlg,int ID);
int GetCheckedRadioButton(HWND hDlg,int FirstID,int LastID);
bool AdjustDialogPos(HWND hwndOwner,HWND hDlg);
void SyncTrackBarWithEdit(HWND hDlg,int EditID,int TrackbarID);
void SyncEditWithTrackBar(HWND hDlg,int TrackbarID,int EditID);
void SetComboBoxList(HWND hDlg,int ID,LPCTSTR pszList);
bool SetDlgButtonBitmap(HWND hDlg,int ID,HINSTANCE hinst,LPCTSTR pszName);
bool SetListBoxHExtent(HWND hDlg,int ID);
LPTSTR GetDlgItemString(HWND hDlg,int ID);
bool EnableDlgItemSyncCheckBox(HWND hDlg,int ID,int CheckBoxID);
bool EnableDlgItemsSyncCheckBox(HWND hDlg,int FirstID,int LastID,int CheckBoxID);
BOOL SetDlgItemInt64(HWND hDlg,int ID,ULONGLONG Value,BOOL fSigned);
ULONGLONG GetDlgItemInt64(HWND hDlg,int ID,BOOL *pfTranslated,BOOL fSigned);
HMENU CreatePopupMenuFromControls(HWND hDlg,const int *pIDList,int IDListLength);
bool PopupMenuFromControls(HWND hDlg,const int *pIDList,int IDListLength,
						   unsigned int Flags=0,const POINT *ppt=NULL);
#define LBN_EX_RBUTTONDOWN	0x0100
bool ExtendListBox(HWND hwndList,unsigned int Flags=0);


#endif
