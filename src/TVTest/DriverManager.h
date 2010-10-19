#ifndef DRIVER_MANAGER_H
#define DRIVER_MANAGER_H


#include "ChannelList.h"
#include "PointerArray.h"


class CDriverInfo
{
	LPTSTR m_pszFileName;
	LPTSTR m_pszTunerName;
	bool m_fChannelFileLoaded;
	CTuningSpaceList m_TuningSpaceList;
	bool m_fDriverSpaceLoaded;
	CTuningSpaceList m_DriverSpaceList;

public:
	CDriverInfo(LPCTSTR pszFileName);
	CDriverInfo(const CDriverInfo &Info);
	~CDriverInfo();
	CDriverInfo &operator=(const CDriverInfo &Src);
	LPCTSTR GetFileName() const { return m_pszFileName; }
	LPCTSTR GetTunerName() const { return m_pszTunerName; }
	enum LoadTuningSpaceListMode {
		LOADTUNINGSPACE_DEFAULT,
		LOADTUNINGSPACE_NOLOADDRIVER,
		LOADTUNINGSPACE_USEDRIVER,
		LOADTUNINGSPACE_USEDRIVER_NOOPEN,
	};
	bool LoadTuningSpaceList(LoadTuningSpaceListMode Mode=LOADTUNINGSPACE_DEFAULT);
	bool IsChannelFileLoaded() const { return m_fChannelFileLoaded; }
	bool IsDriverChannelLoaded() const { return m_fDriverSpaceLoaded; }
	bool IsTuningSpaceListLoaded() const {
		return m_fChannelFileLoaded || m_fDriverSpaceLoaded;
	}
	const CTuningSpaceList *GetTuningSpaceList() const { return &m_TuningSpaceList; }
	const CTuningSpaceList *GetDriverSpaceList() const { return &m_DriverSpaceList; }
	const CTuningSpaceList *GetAvailableTuningSpaceList() const;
	const CChannelList *GetChannelList(int Space) const;
	int NumDriverSpaces() const { return m_DriverSpaceList.NumSpaces(); }
};

class CDriverManager
{
	CPointerVector<CDriverInfo> m_DriverList;
	LPTSTR m_pszBaseDirectory;
	static int CompareDriverFileName(const CDriverInfo *pDriver1,const CDriverInfo *pDriver2,void *pParam);

public:
	CDriverManager();
	~CDriverManager();
	void Clear();
	int NumDrivers() const { return m_DriverList.Length(); }
	bool Find(LPCTSTR pszDirectory);
	CDriverInfo *GetDriverInfo(int Index);
	const CDriverInfo *GetDriverInfo(int Index) const;
	LPCTSTR GetBaseDirectory() const { return m_pszBaseDirectory; }
};


#endif
