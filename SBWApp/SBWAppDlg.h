/*
	   This file is subject to the terms and conditions defined in
	   file 'LICENSE.txt', which is part of this source code package.
	   Copyright (C) 2013 Ricardo B. Santos.
	   All rights reserved
*/

// SBWAppDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "SBW.h"
#include "afxpropertygridctrl.h"
#include "MFCPropertyGridCtrl2.h"
#include "MFCPropertyGridProperty2.h"
#include "HexNumberProp.h"
//#include "NumberProp.h"
#include "NullProp.h"
#include <memory>
#include "afxmenubutton.h"
#include "afxcmn.h"
#include "NumEdit.h"

#define RSHIFT_KEY	    0
#define RCTRL_KEY		1
//#define LMENU_KEY		2
#define LEFT_KEY		3
#define UP_KEY			4
#define PRIOR_KEY		5

#define XTRA			0
#define YTRA            1
#define ZTRA            2
#define XROT            3
#define YROT            4
#define ZROT            5

#define IDX_GENE           0
#define IDX_MODE  IDX_GENE+1
#define IDX_THRE  IDX_GENE+2
#define IDX_TENS  IDX_GENE+3
#define IDX_LFTH  IDX_GENE+4
#define IDX_TRAN  IDX_GENE+5
#define IDX_TRAF  IDX_GENE+6
#define IDX_ROTA  IDX_GENE+7
#define IDX_RFOR  IDX_GENE+8
#define IDX_ROTF  IDX_GENE+9
#define IDX_ROTY  IDX_GENE+10
#define IDX_RHAN  IDX_GENE+11
#define IDX_RPRP  IDX_GENE+12
#define IDX_RPPO  IDX_GENE+13
#define IDX_RESS  IDX_GENE+14
#define IDX_RMIN  IDX_GENE+15
#define IDX_RMAX  IDX_GENE+16
#define IDX_REMU  IDX_GENE+17
#define IDX_RENS  IDX_GENE+18
#define IDX_REOT  IDX_GENE+19
#define IDX_SPRT  IDX_GENE+20
#define IDX_SPAN  IDX_GENE+21
#define IDX_SPXP  IDX_GENE+22
#define IDX_TRMD  IDX_GENE+23
#define IDX_TRSY  IDX_GENE+24
#define IDX_TRCT  IDX_GENE+25
#define IDX_TROU  IDX_GENE+26
#define IDX_TRVE  IDX_GENE+27
#define IDX_RODE  IDX_GENE+28
#define IDX_RSYS  IDX_GENE+29
#define IDX_RFVE  IDX_GENE+30
#define IDX_ROUT  IDX_GENE+31
#define IDX_RVEC	IDX_GENE+32
#define IDX_ABMX	IDX_GENE+33
#define IDX_ZERO	IDX_GENE+34
#define IDX_BEEP	IDX_GENE+35
#define IDX_ORIE	IDX_GENE+36
#define IDX_LINS	IDX_GENE+37
#define IDX_MODP	IDX_GENE+38

//
#define ID_COMM_PORT 5000

static UINT NEAR WM_SBEXPLORER_QUERY = 0;

class CSBWAppDlg;

// CSBWAppDlg dialog
class CSBWAppDlg : public CDialogEx {
		// Construction
	public:
		CSBWAppDlg ( CWnd *pParent = NULL );	// standard constructor

		// Dialog Data
		enum { IDD = IDD_SBWAPP_DIALOG };

	protected:
		virtual void DoDataExchange ( CDataExchange *pDX );	// DDX/DDV support

		void OnlyNumber ( CEdit *pObj, long minv, long maxv );

		// Implementation
	protected:

		bool             m_bCanNewWindow;
		double           m_dSMAThres;
		double           m_iFreq;
		HANDLE           m_hTimerQueue;
		HICON            m_hIcon;
		int              m_iCommand;
		int              m_iDoF;
		int              m_iFreedMov;
		int              m_iSignal;
		UINT             WM_SBEXPLORER;
		UINT_PTR         m_uipTimer;

		// Generated message map functions
		virtual BOOL OnInitDialog ( );
		afx_msg void OnPaint ( );
		afx_msg HCURSOR OnQueryDragIcon ( );
		DECLARE_MESSAGE_MAP ( )
	public:

		SBW m_SBW;

		struct _sTimerQueue {
			CSBWAppDlg *pThis;
			int iMov;
			HANDLE hTimer;
			HANDLE hTimerQueue;
		};

#pragma pack(1)
		struct _stUser {
			struct dominance {
				char cMode;
			} Dominance;
			struct operation {
				char cMode;
				bool bPulse;
				double dFreq;
			} Operation;
			struct threshold {
				short sX;
				short sY;
				short sZ;
				short sRX;
				short sRY;
				short sRZ;
			} Threshold;
			struct mov_aver {
				bool bEnable;
				int iLength;
				int iPeriod;
			} MovingAverage;
		};
#pragma pack()

		CMap<int, int, short, short> m_clThreshold;

		CMFCPropertyGridCtrl2 m_ctrlSettings;
		CComboBox             m_ctrlPortList;
		CComboBox             m_ctrlThresSel;
		CMFCMenuButton        m_ctrlSetSignal;
		CSliderCtrl           m_ctrlNLength;

		CStatic m_ctrlLocation;
		CStatic m_ctrlWaitingEventMsg;

		CButton m_ctrlAddByte;
		CButton m_ctrlAddCR;
		CButton m_ctrlAppendRead;
		CButton m_ctrlBallKeystroke;
		CButton m_ctrlBeep;
		CButton m_ctrlBREAK;
		CButton m_ctrlBroadcast;
		CButton m_ctrlButton1;
		CButton m_ctrlButton2;
		CButton m_ctrlButton3;
		CButton m_ctrlButton4;
		CButton m_ctrlButton5;
		CButton m_ctrlButton6;
		CButton m_ctrlButton7;
		CButton m_ctrlButton8;
		CButton m_ctrlButton9;
		CButton m_ctrlButtonA;
		CButton m_ctrlButtonB;
		CButton m_ctrlButtonC;
		CButton m_ctrlClearBREAK;
		CButton m_ctrlConnect;
		CButton m_ctrlCTS;
		CButton m_ctrlDSR;
		CButton m_ctrlERR;
		CButton m_ctrlFlashWin;
		CButton m_ctrlFRAME;
		CButton m_ctrlMapButtons;
		CButton m_ctrlMovAverage;
		CButton m_ctrlNonPrint;
		CButton m_ctrlOVERRUN;
		CButton m_ctrlPulse;
		CButton m_ctrlRemapAB;
		CButton m_ctrlReport;
		CButton m_ctrlRING;
		CButton m_ctrlRLSD;
		CButton m_ctrlRXCHAR;
		CButton m_ctrlRXFLAG;
		CButton m_ctrlRXOVER;
		CButton m_ctrlRXPARITY;
		CButton m_ctrlSetDev;
		CButton m_ctrlTXEMPTY;
		CButton m_ctrlXLabel;
		CButton m_ctrlXRotLabel;
		CButton m_ctrlYLabel;
		CButton m_ctrlYRotLabel;
		CButton m_ctrlZLabel;
		CButton m_ctrlZRotLabel;

		CEdit m_ctrlASCIIData;
		CEdit m_ctrlByteValue;
		CEdit m_ctrlCmd;
		CEdit m_ctrlCmdList;
		CEdit m_ctrlHandle;
		CEdit m_ctrlHexData;
		CEdit m_ctrlPeriodValue;
		CEdit m_ctrlSize;
		CEdit m_ctrlStatusBar;
		CEdit m_ctrlTextToFind;
		CEdit m_ctrlXRotValue;
		CEdit m_ctrlXTransValue;
		CEdit m_ctrlYRotValue;
		CEdit m_ctrlYTransValue;
		CEdit m_ctrlZRotValue;
		CEdit m_ctrlZTransValue;

		CNumEdit m_ctrlFreq;
		CNumEdit m_ctrlNBytesRead;
		CNumEdit m_ctrlNBytesWritten;
		CNumEdit m_ctrlPeriodOffset;
		CNumEdit m_ctrlSMAThres;
		CNumEdit m_ctrlThres;
		CNumEdit m_ctrlTimValue;
		CNumEdit m_ctrlXRotOffset;
		CNumEdit m_ctrlXTranOffset;
		CNumEdit m_ctrlYRotOffset;
		CNumEdit m_ctrlYTranOffset;
		CNumEdit m_ctrlZRotOffset;
		CNumEdit m_ctrlZTranOffset;

		CMenu m_SignalMenu;

		CMap < int, int, CMFCPropertyGridProperty2 *, CMFCPropertyGridProperty2 *> m_clCtrlItem;
		CMap < int, int, COleVariant, COleVariant>                                 m_clDefaultValue;
		CMap < int, int, CString, LPCTSTR>                                         m_clString;
		CMap < int, int, DWORD_PTR, DWORD_PTR>                                     m_clDefaultState;

		void CreateProp_AbsoluteMatrix ( CArray<__int64, __int64> &min, CArray<__int64, __int64> &max );
		void CreateProp_Beeper ( CArray<__int64, __int64> &min, CArray<__int64, __int64> &max );
		void CreateProp_Mode ( );
		void CreateProp_Orientation ( CArray<__int64, __int64> &min, CArray<__int64, __int64> &max );
		void CreateProp_ResponseMultiplier ( CArray<__int64, __int64> &min, CArray<__int64, __int64> &max );
		void CreateProp_Responsiveness ( CArray<__int64, __int64> &min, CArray<__int64, __int64> &max );
		void CreateProp_RotationMode ( CArray<__int64, __int64> &min, CArray<__int64, __int64> &max );
		void CreateProp_SpinRate ( CArray<__int64, __int64> &min, CArray<__int64, __int64> &max );
		void CreateProp_Threshold ( CArray<__int64, __int64> &min, CArray<__int64, __int64> &max );
		void CreateProp_TranslationMode ( CArray<__int64, __int64> &min, CArray<__int64, __int64> &max );
		void CreateProp_TranslationSensitivities ( CArray<__int64, __int64> &min, CArray<__int64, __int64> &max );
		void CreateProp_UnvInfo ( CArray<__int64, __int64> &min, CArray<__int64, __int64> &max );
		void CreateProp_Zero ( );

		afx_msg BOOL OnSetCursor ( CWnd *pWnd, UINT nHitTest, UINT message );
		afx_msg LRESULT OnSbExplorerQuery ( WPARAM wParam, LPARAM lParam );
		afx_msg LRESULT SBE_Closed ( WPARAM, LPARAM );
		afx_msg LRESULT SBE_Message ( WPARAM, LPARAM );
		afx_msg void OnAbout ( );
		afx_msg void OnAddByteValue ( );
		afx_msg void OnAddCMDs ( );
		afx_msg void OnBnClicked1DoF ( );
		afx_msg void OnBnClicked2DoF ( );
		afx_msg void OnBnClicked4DoF ( );
		afx_msg void OnBnClickedAbremap ( );
		afx_msg void OnBnClickedAppend ( );
		afx_msg void OnBnClickedBallkeystroke ( );
		afx_msg void OnBnClickedBoth ( );
		afx_msg void OnBnClickedBroadcastmsg ( );
		afx_msg void OnBnClickedRotation ( );
		afx_msg void OnBnClickedTranslation ( );
		afx_msg void OnClearAll ( );
		afx_msg void OnClearText ( );
		afx_msg void OnConnect ( );
		afx_msg void OnEnSetfocusStatusbar ( );
		afx_msg void OnEnUpdateTexttofind ( );
		afx_msg void OnFlashWin ( );
		afx_msg void OnLoadSett ( );
		afx_msg void OnMovAverage ( );
		afx_msg void OnNElements ( NMHDR *pNMHDR, LRESULT *pResult );
		afx_msg void OnReset ( );
		afx_msg void OnSaveSett ( );
		afx_msg void OnSetDevice ( );
		afx_msg void OnSetSignal ( );
		afx_msg void OnSMAThresUpdate ( );
		afx_msg void OnThresSel ( );
		afx_msg void OnTimer ( UINT_PTR nIDEvent );
		afx_msg void OnUpdateByteValue ( );
		afx_msg void OnUpdateFreq ( );
		afx_msg void OnUpdateMovAverPeriod ( );
		afx_msg void OnUpdatePeroffset ( );
		afx_msg void OnUpdateThres ( );
		afx_msg void OnUpdateXroffset ( );
		afx_msg void OnUpdateXtoffset ( );
		afx_msg void OnUpdateYroffset ( );
		afx_msg void OnUpdateYtoffset ( );
		afx_msg void OnUpdateZroffset ( );
		afx_msg void OnUpdateZtoffset ( );
		virtual BOOL PreTranslateMessage (MSG *pMsg	);
		virtual void OnCancel ( );

		CCriticalSection  m_clCriSec;

		bool CheckValue ( float fV0, float fV1, float fV2 );
		bool CheckValue ( float fV0, float fV1, float fV2, float fV3, float fV4, float fV5 );
		bool CheckValue ( int iV, int iN, float *fV );
		bool CheckValue ( short sV0, short sV1, short sV2 );
		bool CheckValue ( short sV0, short sV1, short sV2, short sV3, short sV4, short sV5 );
		bool GetState ( bool bMovAver, bool bPulse, int iMov );

		bool m_bCurrent_State_Ball[ 6 ];
		bool m_bEnableUpdateOffsetData;
		bool m_bFinal_State_Ball[ 6 ];
		bool m_bNotAllowNewTimer[ 6 ];
		bool m_bPrevious_Final_State_Ball[ 6 ];
		vector <BYTE> m_bMoving_State_Ball2[ 6 ];
		void *m_pShortener[ 3 ];

		bool RemapButtonsToF13_F24 ( );
		int Sum32 ( vector <BYTE> &v );
		LRESULT SendBallKeystrokes ( WPARAM queryitem = -1 );
		void BallState ( bool bCheckZeroBallState = true );
		void CheckZeroBallState ( /*double dValue*/ );
		void CurrentBallState ( short XTra, short YTra, short ZTra, short XRot, short YRot, short ZRot );
		void FillArray ( /*double dValue,*/ int iElem );
		void FinalBallState ( bool bCheckZeroBallState = true );
		void GetAbsoluteValue ( bool bValue, short sCurrValue, short sThres, short &sValue );
		void Print ( );
		void PrintStatus ( CString msg, UINT nElapse, int type );
		void ProcessCommand ( INT_PTR iCommand );
		void PropCallBack ( CMFCPropertyGridProperty2 *pObj, bool bValue );
		void PutValue ( CEdit *pObj, bool bValue, short sValue );
		void RemapButtonsToConfig ( );
		void Reset ( );
		void Reset_Cmd_Group ( );
		void Reset_COM_Group ( );
		void Set ( bool *pb, int len1, int len2, ... );
		void SetCtrl ( bool bPulse, bool bPreviousState, bool bState, CButton *pCtrlObj );
		void SetDefaults ( );
		void Translate ( bool bDirection, SBW::_stProperties &stProp, _stUser &stUser );
		__int64 EncodeBits ( __int64 val, int nbits, int vbits, int nstep = 0 );

		HWND m_hTargetWindow;
};

