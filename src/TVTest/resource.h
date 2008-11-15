#define IDI_ICON			10
#define IDI_TRAY			11
#define IDI_TRAY_RECORDING	12
#define IDI_PROGRAMGUIDE	15

#define IDM_MENU					20
#define IDM_RECORD					21
#define IDM_CAPTURE					22
#define IDM_BUFFERING				23
#define IDM_PROGRAMGUIDE			25
#define IDM_CHANNELSCAN				28
#define IDM_TRAY					29
#define IDM_CAPTUREPREVIEW			30
#define IDM_PLUGIN					31

#define IDA_ACCEL	40
#define IDA_ACCEL2	41

#define IDB_LOGO		45
#define IDB_CAPTURE		46
#define IDB_TITLEBAR	47

#define IDD_ABOUT					50
#define IDD_INITIALSETTINGS			51
#define IDD_OPTIONS					52
#define IDD_OPTIONS_GENERAL			53
#define IDD_OPTIONS_VIEW			54
#define IDD_OPTIONS_STATUS			55
#define IDD_OPTIONS_PANEL			56
#define IDD_OPTIONS_COLORSCHEME		57
#define IDD_OPTIONS_OPERATION		58
#define IDD_OPTIONS_RECORD			59
#define IDD_OPTIONS_CAPTURE			60
#define IDD_OPTIONS_CHANNELSCAN		61
#define IDD_OPTIONS_EPG				62
#define IDD_OPTIONS_PROGRAMGUIDE	63
#define IDD_OPTIONS_PLUGIN			64
#define IDD_OPTIONS_NETWORKREMOCON	65
#define IDD_OPTIONS_LOG				66
#define IDD_RECORDOPTION			80
#define IDD_RECORDSTOPTIME			81
#define IDD_CHANNELSCAN				85
#define IDD_PROGRAMGUIDETOOL		86

#define CM_ZOOM_FIRST				100
#define CM_ZOOM_LAST				108
#define CM_ZOOM_20					(CM_ZOOM_FIRST+0)
#define CM_ZOOM_25					(CM_ZOOM_FIRST+1)
#define CM_ZOOM_33					(CM_ZOOM_FIRST+2)
#define CM_ZOOM_50					(CM_ZOOM_FIRST+3)
#define CM_ZOOM_66					(CM_ZOOM_FIRST+4)
#define CM_ZOOM_75					(CM_ZOOM_FIRST+5)
#define CM_ZOOM_100					(CM_ZOOM_FIRST+6)
#define CM_ZOOM_150					(CM_ZOOM_FIRST+7)
#define CM_ZOOM_200					(CM_ZOOM_FIRST+8)
#define CM_ASPECTRATIO				110
#define CM_ASPECTRATIO_FIRST		111
#define CM_ASPECTRATIO_LAST			116
#define CM_ASPECTRATIO_DEFAULT		111
#define CM_ASPECTRATIO_16x9			112
#define CM_ASPECTRATIO_LETTERBOX	113
#define CM_ASPECTRATIO_SUPERFRAME	114
#define CM_ASPECTRATIO_SIDECUT		115
#define CM_ASPECTRATIO_4x3			116
#define CM_FULLSCREEN				118
#define CM_ALWAYSONTOP				119
#define CM_VOLUME_UP				120
#define CM_VOLUME_DOWN				121
#define CM_VOLUME_MUTE				122
#define CM_STEREO_THROUGH			125
#define CM_STEREO_LEFT				126
#define CM_STEREO_RIGHT				127
#define CM_STEREOMODE				128
#define CM_RECORD					130
#define CM_RECORD_START				131
#define CM_RECORD_STOP				132
#define CM_RECORD_PAUSE				133
#define CM_RECORDOPTION				134
#define CM_RECORDSTOPTIME			135
#define CM_OPTIONS_RECORD			136
#define CM_EXITONRECORDINGSTOP		137
#define CM_DISABLEVIEWER			138
#define CM_COPY						140
#define CM_SAVEIMAGE				141
#define CM_CAPTURE					142
#define CM_CAPTUREPREVIEW			143
#define CM_OPENCAPTUREFOLDER		144
#define CM_CAPTURESIZE_ORIGINAL		150
#define CM_CAPTURESIZE_VIEW			151
#define CM_CAPTURESIZE_RAW			152
#define CM_CAPTURESIZE_1920X1080	153
#define CM_CAPTURESIZE_1440X810		154
#define CM_CAPTURESIZE_1280X720		155
#define CM_CAPTURESIZE_1024X576		156
#define CM_CAPTURESIZE_960x540		157
#define CM_CAPTURESIZE_800X450		158
#define CM_CAPTURESIZE_640X360		159
#define CM_CAPTURESIZE_1440X1080	160
#define CM_CAPTURESIZE_1280X960		161
#define CM_CAPTURESIZE_1024X768		162
#define CM_CAPTURESIZE_800X600		163
#define CM_CAPTURESIZE_720X540		164
#define CM_CAPTURESIZE_640X480		165
#define CM_CAPTURESIZE_FIRST		CM_CAPTURESIZE_ORIGINAL
#define CM_CAPTURESIZE_LAST			CM_CAPTURESIZE_640X480
#define CM_RESET					170
#define CM_INFORMATION				180
#define CM_PROGRAMGUIDE				181
#define CM_STATUSBAR				182
#define CM_TITLEBAR					183
#define CM_DECODERPROPERTY			184
#define CM_OPTIONS					185
#define CM_CLOSE					186
#define CM_EXIT						187
#define CM_SHOW						188
#define CM_CHANNEL_UP				190
#define CM_CHANNEL_DOWN				191
#define CM_MENU						192
#define CM_ENABLEBUFFERING			195
#define CM_RESETBUFFER				196

#define CM_CHANNELNO_FIRST	200
#define CM_CHANNELNO_LAST	(CM_CHANNELNO_FIRST+99)
#define CM_CHANNELNO_1		(CM_CHANNELNO_FIRST+0)
#define CM_CHANNELNO_2		(CM_CHANNELNO_FIRST+1)
#define CM_CHANNELNO_3		(CM_CHANNELNO_FIRST+2)
#define CM_CHANNELNO_4		(CM_CHANNELNO_FIRST+3)
#define CM_CHANNELNO_5		(CM_CHANNELNO_FIRST+4)
#define CM_CHANNELNO_6		(CM_CHANNELNO_FIRST+5)
#define CM_CHANNELNO_7		(CM_CHANNELNO_FIRST+6)
#define CM_CHANNELNO_8		(CM_CHANNELNO_FIRST+7)
#define CM_CHANNELNO_9		(CM_CHANNELNO_FIRST+8)
#define CM_CHANNELNO_10		(CM_CHANNELNO_FIRST+9)
#define CM_CHANNELNO_11		(CM_CHANNELNO_FIRST+10)
#define CM_CHANNELNO_12		(CM_CHANNELNO_FIRST+11)

#define CM_CHANNEL_FIRST	300
#define CM_CHANNEL_LAST		399
#define CM_SPACE_ALL		400
#define CM_SPACE_FIRST		401
#define CM_SPACE_LAST		499
#define CM_SERVICE_FIRST	500
#define CM_SERVICE_LAST		599
#define CM_DRIVER_FIRST		600
#define CM_DRIVER_LAST		699

#define CM_VOLUMENORMALIZE_FIRST	700
#define CM_VOLUMENORMALIZE_LAST		(CM_VOLUMENORMALIZE_FIRST+3)
#define CM_VOLUMENORMALIZE_NONE		(CM_VOLUMENORMALIZE_FIRST+0)
#define CM_VOLUMENORMALIZE_125		(CM_VOLUMENORMALIZE_FIRST+1)
#define CM_VOLUMENORMALIZE_150		(CM_VOLUMENORMALIZE_FIRST+2)
#define CM_VOLUMENORMALIZE_200		(CM_VOLUMENORMALIZE_FIRST+3)

#define CM_PROGRAMGUIDE_UPDATE		800
#define CM_PROGRAMGUIDE_ENDUPDATE	801
#define CM_PROGRAMGUIDE_REFRESH		802
#define CM_PROGRAMGUIDE_IEPGASSOCIATE	810

#define CM_PLUGIN_FIRST		2000
#define CM_PLUGIN_LAST		2999

#define SC_ABOUT			0x1000
#define SC_DOCKING			0x1001

#define IDC_VIEW			1000
#define IDC_VIDEOCONTAINER	1001
#define IDC_STATUS			1002
#define IDC_TITLEBAR		1003

#define IDC_ABOUT_LOGO		1000

#define IDC_INITIALSETTINGS_LOGO				1000
#define IDC_INITIALSETTINGS_DRIVER				1001
#define IDC_INITIALSETTINGS_DRIVER_BROWSE		1002
#define IDC_INITIALSETTINGS_MPEG2DECODER		1003
#define IDC_INITIALSETTINGS_VIDEORENDERER		1004
#define IDC_INITIALSETTINGS_CARDREADER			1005
#define IDC_INITIALSETTINGS_HELP				1010

#define IDC_OPTIONS_LIST		1000
#define IDC_OPTIONS_TITLE		1001
#define IDC_OPTIONS_PAGEPLACE	1002
#define IDC_OPTIONS_HELP		1003

#define IDC_OPTIONS_DRIVER						1000
#define IDC_OPTIONS_DRIVER_BROWSE				1001
#define IDC_OPTIONS_DECODER						1002
#define IDC_OPTIONS_RENDERER					1003
#define IDC_OPTIONS_CARDREADER					1004
#define IDC_OPTIONS_USEREMOTECONTROLLER			1005
#define IDC_OPTIONS_REMOTECONTROLLERACTIVEONLY	1006
#define IDC_OPTIONS_NOSCREENSAVER				1007
#define IDC_OPTIONS_NOMONITORLOWPOWER			1008
#define IDC_OPTIONS_NOMONITORLOWPOWERACTIVEONLY	1009
#define IDC_OPTIONS_KEEPSINGLETASK				1010
#define IDC_OPTIONS_RESIDENT					1011
#define IDC_OPTIONS_RESTORECHANNEL				1012
#define IDC_OPTIONS_NEWHDUSDRIVER				1013
#define IDC_OPTIONS_ENABLEBUFFERING				1020
#define IDC_OPTIONS_BUFFERSIZE_LABEL			1021
#define IDC_OPTIONS_BUFFERSIZE					1022
#define IDC_OPTIONS_BUFFERSIZE_UD				1023
#define IDC_OPTIONS_BUFFERPOOLPERCENTAGE_LABEL	1024
#define IDC_OPTIONS_BUFFERPOOLPERCENTAGE		1025
#define IDC_OPTIONS_BUFFERPOOLPERCENTAGE_UD		1026
#define IDC_OPTIONS_BUFFERPOOLPERCENTAGE_UNIT	1027
#define IDC_OPTIONS_BUFFERING_FIRST				IDC_OPTIONS_BUFFERSIZE_LABEL
#define IDC_OPTIONS_BUFFERING_LAST				IDC_OPTIONS_BUFFERPOOLPERCENTAGE_UNIT

#define IDC_OPTIONS_ADJUSTASPECTRESIZING		1000
#define IDC_OPTIONS_SNAPATWINDOWEDGE			1001
#define IDC_OPTIONS_PANSCANNORESIZEWINDOW		1002
#define IDC_OPTIONS_FULLSCREENCUTFRAME			1003
#define IDC_OPTIONS_MAXIMIZECUTFRAME			1004
#define IDC_OPTIONS_CLIENTEDGE					1005
#define IDC_OPTIONS_USEOSD						1010
#define IDC_OPTIONS_PSEUDOOSD					1011
#define IDC_OPTIONS_OSDTEXTCOLOR_LABEL			1012
#define IDC_OPTIONS_OSDTEXTCOLOR				1013
#define IDC_OPTIONS_OSDFADETIME_LABEL			1014
#define IDC_OPTIONS_OSDFADETIME					1015
#define IDC_OPTIONS_OSDFADETIME_UD				1016
#define IDC_OPTIONS_OSDFADETIME_UNIT			1017
#define IDC_OPTIONS_OSD_FIRST					IDC_OPTIONS_PSEUDOOSD
#define IDC_OPTIONS_OSD_LAST					IDC_OPTIONS_OSDFADETIME_UNIT
#define IDC_OPTIONS_DESCRAMBLECURSERVICEONLY	1020

#define IDC_STATUSOPTIONS_ITEMLIST				1000
#define IDC_STATUSOPTIONS_DEFAULT				1001
#define IDC_STATUSOPTIONS_FONTINFO				1010
#define IDC_STATUSOPTIONS_CHOOSEFONT			1011

#define IDC_PANELOPTIONS_SNAPATMAINWINDOW		1000
#define IDC_PANELOPTIONS_ATTACHTOMAINWINDOW		1001

#define IDC_COLORSCHEME_PRESET					1000
#define IDC_COLORSCHEME_SAVE					1001
#define IDC_COLORSCHEME_DELETE					1002
#define IDC_COLORSCHEME_LIST					1003
#define IDC_COLORSCHEME_PALETTEPLACE			1004
#define IDC_COLORSCHEME_PALETTE					1005
#define IDC_COLORSCHEME_PREVIEW					1006

#define IDC_OPTIONS_WHEELMODE					1000
#define IDC_OPTIONS_WHEELSHIFTMODE				1001
#define IDC_OPTIONS_WHEELCHANNELREVERSE			1002
#define IDC_OPTIONS_WHEELCHANNELDELAY			1003
#define IDC_OPTIONS_CHANGECH_FUNCTION			1004
#define IDC_OPTIONS_CHANGECH_DIGIT				1005
#define IDC_OPTIONS_CHANGECH_NUMPAD				1006

#define IDC_RECORDOPTIONS_SAVEFOLDER			1000
#define IDC_RECORDOPTIONS_SAVEFOLDER_BROWSE		1001
#define IDC_RECORDOPTIONS_FILENAME				1002
#define IDC_RECORDOPTIONS_ADDTIME				1003
#define IDC_RECORDOPTIONS_CONFIRMCHANNELCHANGE	1010
#define IDC_RECORDOPTIONS_CONFIRMEXIT			1011
#define IDC_RECORDOPTIONS_DESCRAMBLECURSERVICEONLY	1012

#define IDC_CAPTUREOPTIONS_SAVEFOLDER			1000
#define IDC_CAPTUREOPTIONS_SAVEFOLDER_BROWSE	1001
#define IDC_CAPTUREOPTIONS_FILENAME				1002
#define IDC_CAPTUREOPTIONS_FORMAT				1003
#define IDC_CAPTUREOPTIONS_JPEGQUALITY_TB		1004
#define IDC_CAPTUREOPTIONS_JPEGQUALITY_EDIT		1005
#define IDC_CAPTUREOPTIONS_JPEGQUALITY_UD		1006
#define IDC_CAPTUREOPTIONS_PNGLEVEL_TB			1007
#define IDC_CAPTUREOPTIONS_PNGLEVEL_EDIT		1008
#define IDC_CAPTUREOPTIONS_PNGLEVEL_UD			1009
#define IDC_CAPTUREOPTIONS_ICONSAVEFILE			1010
#define IDC_CAPTUREOPTIONS_SETCOMMENT			1011

#define IDC_CHANNELSCAN_SPACE					1000
#define IDC_CHANNELSCAN_SCANSERVICE				1001
#define IDC_CHANNELSCAN_IGNORESIGNALLEVEL		1002
#define IDC_CHANNELSCAN_CHANNELLIST				1003
#define IDC_CHANNELSCAN_START					1004
#define IDC_CHANNELSCAN_DELETE					1010

#define IDC_CHANNELSCAN_INFO					1000
#define IDC_CHANNELSCAN_PROGRESS				1001

#define IDC_EPGOPTIONS_EPGDATACAPDLLPATH		1000
#define IDC_EPGOPTIONS_EPGDATACAPDLLPATH_BROWSE	1001
#define IDC_EPGOPTIONS_SAVEEPGFILE				1002
#define IDC_EPGOPTIONS_EPGFILENAME_LABEL		1003
#define IDC_EPGOPTIONS_EPGFILENAME				1004
#define IDC_EPGOPTIONS_EPGFILENAME_BROWSE		1005
#define IDC_EPGOPTIONS_UPDATEWHENSTANDBY		1006

#define IDC_PROGRAMGUIDEOPTIONS_VIEWHOURS		1000
#define IDC_PROGRAMGUIDEOPTIONS_VIEWHOURS_UD	1001
#define IDC_PROGRAMGUIDEOPTIONS_CHANNELWIDTH	1002
#define IDC_PROGRAMGUIDEOPTIONS_CHANNELWIDTH_UD	1003
#define IDC_PROGRAMGUIDEOPTIONS_LINESPERHOUR	1004
#define IDC_PROGRAMGUIDEOPTIONS_LINESPERHOUR_UD	1005

#define IDC_PROGRAMGUIDETOOL_NAME				1000
#define IDC_PROGRAMGUIDETOOL_COMMAND			1001
#define IDC_PROGRAMGUIDETOOL_BROWSE				1002

#define IDC_PLUGIN_LIST							1000
#define IDC_PLUGIN_SETTINGS						1001
#define IDC_PLUGIN_UNLOAD						1002

#define IDC_NETWORKREMOCON_USE					1000
#define IDC_NETWORKREMOCON_ADDRESS				1001
#define IDC_NETWORKREMOCON_PORT					1002
#define IDC_NETWORKREMOCON_CHANNELFILE			1003

#define IDC_LOG_LIST							1000
#define IDC_LOG_CLEAR							1001
#define IDC_LOG_SAVE							1002

#define IDC_RECORD_FILENAME_LABEL			1000
#define IDC_RECORD_FILENAME					1001
#define IDC_RECORD_FILENAME_BROWSE			1002
#define IDC_RECORD_FILEEXISTS_LABEL			1003
#define IDC_RECORD_FILEEXISTS				1004
#define IDC_RECORD_STARTTIME				1010
#define IDC_RECORD_START_NOW				1011
#define IDC_RECORD_START_DATETIME			1012
#define IDC_RECORD_START_DELAY				1013
#define IDC_RECORD_STARTTIME_TIME			1014
#define IDC_RECORD_STARTTIME_HOUR			1015
#define IDC_RECORD_STARTTIME_HOUR_UD		1016
#define IDC_RECORD_STARTTIME_HOUR_LABEL		1017
#define IDC_RECORD_STARTTIME_MINUTE			1018
#define IDC_RECORD_STARTTIME_MINUTE_UD		1019
#define IDC_RECORD_STARTTIME_MINUTE_LABEL	1020
#define IDC_RECORD_STARTTIME_SECOND			1021
#define IDC_RECORD_STARTTIME_SECOND_UD		1022
#define IDC_RECORD_STARTTIME_SECOND_LABEL	1023
#define IDC_RECORD_STOPSPECTIME				1030
#define IDC_RECORD_STOPDATETIME				1031
#define IDC_RECORD_STOPREMAINTIME			1032
#define IDC_RECORD_STOPTIME_TIME			1033
#define IDC_RECORD_STOPTIME_HOUR			1034
#define IDC_RECORD_STOPTIME_HOUR_UD			1035
#define IDC_RECORD_STOPTIME_HOUR_LABEL		1036
#define IDC_RECORD_STOPTIME_MINUTE			1037
#define IDC_RECORD_STOPTIME_MINUTE_UD		1038
#define IDC_RECORD_STOPTIME_MINUTE_LABEL	1039
#define IDC_RECORD_STOPTIME_SECOND			1040
#define IDC_RECORD_STOPTIME_SECOND_UD		1041
#define IDC_RECORD_STOPTIME_SECOND_LABEL	1042
#define IDC_RECORD_CANCEL					1050

#define IDC_RECORDSTOPTIME_ENABLE		1000
#define IDC_RECORDSTOPTIME_TIME			1001
