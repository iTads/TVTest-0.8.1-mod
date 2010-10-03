#ifndef APP_MAIN_H
#define APP_MAIN_H


#include "CoreEngine.h"
#include "UICore.h"
#include "ChannelManager.h"
#include "Record.h"


class CCommandList;
class CDriverManager;
class CLogoManager;
class CControllerManager;

class CAppMain
{
	CUICore m_UICore;
	bool m_fSilent;
	TCHAR m_szIniFileName[MAX_PATH];
	TCHAR m_szDefaultChannelFileName[MAX_PATH];
	TCHAR m_szChannelSettingFileName[MAX_PATH];
	bool m_fFirstExecute;

	bool SetService(int Service);
	bool GenerateRecordFileName(LPTSTR pszFileName,int MaxFileName) const;

public:
	CAppMain();
	bool Initialize();
	bool Finalize();
	HINSTANCE GetInstance() const;
	HINSTANCE GetResourceInstance() const;
	bool GetAppDirectory(LPTSTR pszDirectory) const;
	bool GetDriverDirectory(LPTSTR pszDirectory) const;
	LPCTSTR GetIniFileName() const { return m_szIniFileName; }
	void AddLog(LPCTSTR pszText, ...);
	void OnError(const CBonErrorHandler *pErrorHandler,LPCTSTR pszTitle=NULL);
	void SetSilent(bool fSilent) { m_fSilent=fSilent; }
	bool IsSilent() const { return m_fSilent; }
	bool LoadSettings();
	bool SaveSettings();
	bool SaveCurrentChannel();
	bool IsFirstExecute() const;

	bool SaveChannelSettings();
	bool InitializeChannel();
	bool RestoreChannel();
	bool UpdateChannelList(const CTuningSpaceList *pList);
	const CChannelInfo *GetCurrentChannelInfo() const;
	bool SetChannel(int Space,int Channel,int ServiceID=-1);
	bool FollowChannelChange(WORD TransportStreamID,WORD ServiceID);
	bool SetServiceByIndex(int Service);
	bool SetServiceByID(WORD ServiceID,int *pServiceIndex=NULL);
	bool SetDriver(LPCTSTR pszFileName);
	bool SetDriverAndChannel(LPCTSTR pszDriverFileName,const CChannelInfo *pChannelInfo);
	bool OpenTuner();
	bool CloseTuner();
	bool OpenBcasCard(bool fRetry=false);

	bool StartRecord(LPCTSTR pszFileName=NULL,
					 const CRecordManager::TimeSpecInfo *pStartTime=NULL,
					 const CRecordManager::TimeSpecInfo *pStopTime=NULL,
					 CRecordManager::RecordClient Client=CRecordManager::CLIENT_USER,
					 bool fTimeShift=false);
	bool ModifyRecord(LPCTSTR pszFileName=NULL,
					  const CRecordManager::TimeSpecInfo *pStartTime=NULL,
					  const CRecordManager::TimeSpecInfo *pStopTime=NULL,
					  CRecordManager::RecordClient Client=CRecordManager::CLIENT_USER);
	bool StartReservedRecord();
	bool CancelReservedRecord();
	bool StopRecord();
	bool RelayRecord(LPCTSTR pszFileName);
	LPCTSTR GetDefaultRecordFolder() const;

	bool ShowHelpContent(int ID);
	void BeginChannelScan(int Space);
	bool IsChannelScanning() const;
	bool IsDriverNoSignalLevel(LPCTSTR pszFileName) const;
	void SetProgress(int Pos,int Max);
	void EndProgress();
	COLORREF GetColor(LPCTSTR pszText) const;

	CCoreEngine *GetCoreEngine();
	const CCoreEngine *GetCoreEngine() const;
	CUICore *GetUICore();
	const CCommandList *GetCommandList() const;
	const CChannelManager *GetChannelManager() const;
	const CRecordManager *GetRecordManager() const;
	const CDriverManager *GetDriverManager() const;
	CLogoManager *GetLogoManager() const;
	CControllerManager *GetControllerManager() const;
};


CAppMain &GetAppClass();


#endif
