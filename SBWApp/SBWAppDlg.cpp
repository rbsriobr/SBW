/*
		 This file is subject to the terms and conditions defined in
		 file 'LICENSE.txt', which is part of this source code package.
		 Copyright (C) 2013 Ricardo B. Santos.
		 All rights reserved
*/

// SBWAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SBWApp.h"
#include "SBWAppDlg.h"
#include "afxdialogex.h"
#include "afxpropertygridctrl.h"
#include "About.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define BTN_SB4000FLX ((( bool *)( m_pShortener[0] )))
#define BTN_SB3000 (( bool *)( m_pShortener[1] ))
#define COORD (( SBW::_stCoord *)( m_pShortener[2] ))

void CSBWAppDlg::SetDefaults ( )
{
	m_bEnableUpdateOffsetData = false;

	m_clThreshold[XTRA] = 20;
	m_clThreshold[YTRA] = 25;
	m_clThreshold[ZTRA] = 25;
	m_clThreshold[XROT] = 30;
	m_clThreshold[YROT] = 40;
	m_clThreshold[ZROT] = 45;

	m_ctrlNLength.SetRange ( 2, 15 );
	m_ctrlNLength.SetPos ( 5 );

	m_ctrlPeriodOffset.m_dMinValue = 0;
	m_ctrlPeriodOffset.m_dMaxValue = 16;
	m_ctrlPeriodOffset.m_dDefValue = 0;
	m_ctrlPeriodOffset.SetValue ( 0, 0 );
	m_SBW.m_stOffset.lPeriod = 0;

	m_ctrlXTranOffset.m_dMinValue = 0;
	m_ctrlXTranOffset.m_dMaxValue = 16;
	m_ctrlXTranOffset.m_dDefValue = 2;
	m_ctrlXTranOffset.SetValue ( 2, 0 );
	m_SBW.m_stOffset.lXTrans = 2;

	m_ctrlYTranOffset.m_dMinValue = 0;
	m_ctrlYTranOffset.m_dMaxValue = 16;
	m_ctrlYTranOffset.m_dDefValue = 6;
	m_ctrlYTranOffset.SetValue ( 6, 0 );
	m_SBW.m_stOffset.lYTrans = 6;

	m_ctrlZTranOffset.m_dMinValue = 0;
	m_ctrlZTranOffset.m_dMaxValue = 16;
	m_ctrlZTranOffset.m_dDefValue = 4;
	m_ctrlZTranOffset.SetValue ( 4, 0 );
	m_SBW.m_stOffset.lZTrans = 4;

	m_ctrlXRotOffset.m_dMinValue = 0;
	m_ctrlXRotOffset.m_dMaxValue = 16;
	m_ctrlXRotOffset.m_dDefValue = 8;
	m_ctrlXRotOffset.SetValue ( 8, 0 );
	m_SBW.m_stOffset.lXRot = 8;

	m_ctrlYRotOffset.m_dMinValue = 0;
	m_ctrlYRotOffset.m_dMaxValue = 16;
	m_ctrlYRotOffset.m_dDefValue = 12;
	m_ctrlYRotOffset.SetValue ( 12, 0 );
	m_SBW.m_stOffset.lYRot = 12;

	m_ctrlZRotOffset.m_dMinValue = 0;
	m_ctrlZRotOffset.m_dMaxValue = 16;
	m_ctrlZRotOffset.m_dDefValue = 10;
	m_ctrlZRotOffset.SetValue ( 10, 0 );
	m_SBW.m_stOffset.lZRot = 10;

	m_clDefaultState[IDX_MODE] = BST_CHECKED;
	m_clDefaultState[IDX_THRE] = BST_UNCHECKED;
	m_clDefaultState[IDX_TENS] = BST_UNCHECKED;
	m_clDefaultState[IDX_LFTH] = -1;
	m_clDefaultState[IDX_TRAN] = -1;
	m_clDefaultState[IDX_TRAF] = -1;
	m_clDefaultState[IDX_ROTA] = BST_CHECKED;
	m_clDefaultState[IDX_RFOR] = BST_UNCHECKED;
	m_clDefaultState[IDX_RHAN] = BST_UNCHECKED;
	m_clDefaultState[IDX_RPRP] = BST_UNCHECKED;
	m_clDefaultState[IDX_RPPO] = -1;
	m_clDefaultState[IDX_ROTF] = -1;
	m_clDefaultState[IDX_ROTY] = -1;
	m_clDefaultState[IDX_RESS] = BST_CHECKED;
	m_clDefaultState[IDX_RMIN] = BST_CHECKED;
	m_clDefaultState[IDX_RMAX] = -1;
	m_clDefaultState[IDX_REMU] = -1;
	m_clDefaultState[IDX_RENS] = BST_CHECKED;
	m_clDefaultState[IDX_REOT] = BST_CHECKED;
	m_clDefaultState[IDX_SPRT] = BST_UNCHECKED;
	m_clDefaultState[IDX_SPAN] = -1;
	m_clDefaultState[IDX_SPXP] = -1;
	m_clDefaultState[IDX_TRMD] = BST_UNCHECKED;
	m_clDefaultState[IDX_TRSY] = -1;
	m_clDefaultState[IDX_TRCT] = -1;
	m_clDefaultState[IDX_TROU] = -1;
	m_clDefaultState[IDX_TRVE] = BST_UNCHECKED;
	m_clDefaultState[IDX_RODE] = BST_UNCHECKED;
	m_clDefaultState[IDX_RSYS] = -1;
	m_clDefaultState[IDX_RFVE] = -1;
	m_clDefaultState[IDX_ROUT] = -1;
	m_clDefaultState[IDX_RVEC] = BST_UNCHECKED;

	m_clDefaultState[IDX_ABMX] = BST_UNCHECKED;
	m_clDefaultState[IDX_ZERO] = BST_UNCHECKED;
	m_clDefaultState[IDX_BEEP] = BST_UNCHECKED;
	m_clDefaultState[IDX_ORIE] = BST_UNCHECKED;

	m_clDefaultState[IDX_LINS] = BST_UNCHECKED;
	m_clDefaultState[IDX_MODP] = BST_UNCHECKED;

	m_clDefaultValue[IDX_THRE] = COleVariant ( 0x60LL );
	m_clDefaultValue[IDX_TENS] = COleVariant ( 0x400020002000LL );
	m_clDefaultValue[IDX_LFTH] = COleVariant ( ( VARIANT_BOOL ) TRUE );
	m_clDefaultValue[IDX_TRAF] = COleVariant ( m_clString[IDS_SPATIAL] );
	m_clDefaultValue[IDX_ROTF] = COleVariant ( m_clString[IDS_SPATIAL] );
	m_clDefaultValue[IDX_ROTY] = COleVariant ( m_clString[IDS_VECTOR] );
	m_clDefaultValue[IDX_RPPO] = COleVariant ( m_clString[IDS_POST] );
	m_clDefaultValue[IDX_RMIN] = COleVariant ( 0x4040LL | EncodeBits ( 40, 2, 6 ) );
	m_clDefaultValue[IDX_RMAX] = COleVariant ( 0x4040LL | EncodeBits ( 1500, 2, 6 ) );
	m_clDefaultValue[IDX_RENS] = COleVariant ( 0x3FLL );
	m_clDefaultValue[IDX_REOT] = COleVariant ( 0x4CLL );
	m_clDefaultValue[IDX_SPAN] = COleVariant ( 0x4BLL );
	m_clDefaultValue[IDX_SPXP] = COleVariant ( 0x70LL );
	m_clDefaultValue[IDX_TRSY] = COleVariant ( m_clString[IDS_PARENT] );
	m_clDefaultValue[IDX_TRCT] = COleVariant ( m_clString[IDS_PARENT] );
	m_clDefaultValue[IDX_TROU] = COleVariant ( m_clString[IDS_PARENT] );
	m_clDefaultValue[IDX_TRVE] = COleVariant ( 0x400000000000LL );
	m_clDefaultValue[IDX_RSYS] = COleVariant ( m_clString[IDS_PARENT] );
	m_clDefaultValue[IDX_RFVE] = COleVariant ( m_clString[IDS_PARENT] );
	m_clDefaultValue[IDX_ROUT] = COleVariant ( m_clString[IDS_PARENT] );
	m_clDefaultValue[IDX_RVEC] = COleVariant ( 0x400000000000LL );

	m_clDefaultValue[IDX_ZERO] = COleVariant ( m_clString[IDS_VALNOTAPPLIC] );
	m_clDefaultValue[IDX_ABMX] = COleVariant ( 0x000000000000LL );
	m_clDefaultValue[IDX_BEEP] = COleVariant ( m_clString[IDS_NOTIMPLEM] );
	m_clDefaultValue[IDX_ORIE] = COleVariant ( 0x000000000000LL );

	m_clDefaultValue[IDX_LINS] = COleVariant ( m_clString[IDS_NOTIMPLEM] );
	m_clDefaultValue[IDX_MODP] = COleVariant ( m_clString[IDS_BINARY] );

	m_bEnableUpdateOffsetData = true;
}
// CSBWAppDlg dialog

CSBWAppDlg::CSBWAppDlg ( CWnd *pParent /*=NULL*/ )
	: CDialogEx ( CSBWAppDlg::IDD, pParent )
{
	m_hIcon                   = AfxGetApp ( )->LoadIcon ( IDI_APP );
	m_uipTimer                = 0;
	m_iFreq                   = 0.0;
	m_iDoF                    = 0;
	m_iFreedMov               = 2;
	m_dSMAThres               = 0.0;
	m_hTargetWindow           = NULL;
	m_iCommand                = SBE_COMMAND_INT;
	m_hTimerQueue             = NULL;
	m_bEnableUpdateOffsetData = false;
	m_bCanNewWindow           = true;
	m_iSignal                 = -1;

	ZeroMemory ( &m_bNotAllowNewTimer, sizeof ( m_bNotAllowNewTimer ) );
	ZeroMemory ( &m_bCurrent_State_Ball, sizeof ( m_bCurrent_State_Ball ) );
	ZeroMemory ( &m_bFinal_State_Ball, sizeof ( m_bFinal_State_Ball ) );
	ZeroMemory ( &m_bPrevious_Final_State_Ball, sizeof ( m_bPrevious_Final_State_Ball ) );
	ZeroMemory ( &m_pShortener, sizeof ( m_pShortener ) );

	WM_SBEXPLORER       = RegisterWindowMessage ( _T ( "SBExplorer" ) );
	WM_SBEXPLORER_QUERY = RegisterWindowMessage ( _T ( "SBExplorer_query" ) );
}

void CSBWAppDlg::DoDataExchange ( CDataExchange *pDX )
{
	CDialogEx::DoDataExchange ( pDX );
	DDX_Control ( pDX, IDC_CONNECT, m_ctrlConnect );
	DDX_Control ( pDX, IDC_COMMPORT, m_ctrlPortList );
	DDX_Control ( pDX, IDC_ST_BREAK, m_ctrlBREAK );
	DDX_Control ( pDX, IDC_ST_CTS, m_ctrlCTS );
	DDX_Control ( pDX, IDC_ST_DSR, m_ctrlDSR );
	DDX_Control ( pDX, IDC_ST_ERR, m_ctrlERR );
	DDX_Control ( pDX, IDC_ST_RING, m_ctrlRING );
	DDX_Control ( pDX, IDC_ST_RLSD, m_ctrlRLSD );
	DDX_Control ( pDX, IDC_ST_RXCHAR, m_ctrlRXCHAR );
	DDX_Control ( pDX, IDC_ST_RXFLAG, m_ctrlRXFLAG );
	DDX_Control ( pDX, IDC_ST_TXEMPTY, m_ctrlTXEMPTY );
	DDX_Control ( pDX, IDC_ST_FRAME, m_ctrlFRAME );
	DDX_Control ( pDX, IDC_ST_OVERRUN, m_ctrlOVERRUN );
	DDX_Control ( pDX, IDC_ST_RXOVER, m_ctrlRXOVER );
	DDX_Control ( pDX, IDC_ST_RXPARITY, m_ctrlRXPARITY );
	DDX_Control ( pDX, IDC_HEXDATA, m_ctrlHexData );
	DDX_Control ( pDX, IDC_ASCIIDATA, m_ctrlASCIIData );
	DDX_Control ( pDX, IDC_NONPRINT, m_ctrlNonPrint );
	DDX_Control ( pDX, IDC_APPEND, m_ctrlAppendRead );
	DDX_Control ( pDX, IDC_CLEARBREAK, m_ctrlClearBREAK );
	DDX_Control ( pDX, IDC_LOCATION, m_ctrlLocation );
	DDX_Control ( pDX, IDC_WAITEVENT, m_ctrlWaitingEventMsg );
	DDX_Control ( pDX, IDC_SETDEV, m_ctrlSetDev );
	DDX_Control ( pDX, IDC_B1, m_ctrlButton1 );
	DDX_Control ( pDX, IDC_B2, m_ctrlButton2 );
	DDX_Control ( pDX, IDC_B3, m_ctrlButton3 );
	DDX_Control ( pDX, IDC_B4, m_ctrlButton4 );
	DDX_Control ( pDX, IDC_B5, m_ctrlButton5 );
	DDX_Control ( pDX, IDC_B6, m_ctrlButton6 );
	DDX_Control ( pDX, IDC_B7, m_ctrlButton7 );
	DDX_Control ( pDX, IDC_B8, m_ctrlButton8 );
	DDX_Control ( pDX, IDC_B9, m_ctrlButton9 );
	DDX_Control ( pDX, IDC_BA, m_ctrlButtonA );
	DDX_Control ( pDX, IDC_BB, m_ctrlButtonB );
	DDX_Control ( pDX, IDC_BC, m_ctrlButtonC );
	DDX_Control ( pDX, IDC_BUTTONKEYSTROKE, m_ctrlMapButtons );
	DDX_Control ( pDX, IDC_RECVCMDLIST, m_ctrlCmdList );
	DDX_Control ( pDX, IDC_CMDTOSEND, m_ctrlCmd );
	DDX_Control ( pDX, IDC_ADDCR, m_ctrlAddCR );
	DDX_Control ( pDX, IDC_BYTEVALUE, m_ctrlByteValue );
	DDX_Control ( pDX, IDC_ADDBYTE, m_ctrlAddByte );
	DDX_Control ( pDX, IDC_CMDSIZE, m_ctrlSize );
	DDX_Control ( pDX, IDC_SETSIGNAL, m_ctrlSetSignal );
	DDX_Control ( pDX, IDC_XROFFSET, m_ctrlXRotOffset );
	DDX_Control ( pDX, IDC_YROFFSET, m_ctrlYRotOffset );
	DDX_Control ( pDX, IDC_ZROFFSET, m_ctrlZRotOffset );
	DDX_Control ( pDX, IDC_XTOFFSET, m_ctrlXTranOffset );
	DDX_Control ( pDX, IDC_YTOFFSET, m_ctrlYTranOffset );
	DDX_Control ( pDX, IDC_ZTOFFSET, m_ctrlZTranOffset );
	DDX_Control ( pDX, IDC_PEROFFSET, m_ctrlPeriodOffset );
	DDX_Control ( pDX, IDC_COOR_PERIOD, m_ctrlPeriodValue );
	DDX_Control ( pDX, IDC_COOR_AXISX, m_ctrlXTransValue );
	DDX_Control ( pDX, IDC_COOR_AXISY, m_ctrlYTransValue );
	DDX_Control ( pDX, IDC_COOR_AXISZ, m_ctrlZTransValue );
	DDX_Control ( pDX, IDC_COOR_AXISX_ROT, m_ctrlXRotValue );
	DDX_Control ( pDX, IDC_COOR_AXISY_ROT, m_ctrlYRotValue );
	DDX_Control ( pDX, IDC_COOR_AXISZ_ROT, m_ctrlZRotValue );
	DDX_Control ( pDX, IDC_CHECK1, m_ctrlReport );
	DDX_Control ( pDX, IDC_X_LABEL, m_ctrlXLabel );
	DDX_Control ( pDX, IDC_Y_LABEL, m_ctrlYLabel );
	DDX_Control ( pDX, IDC_Z_LABEL, m_ctrlZLabel );
	DDX_Control ( pDX, IDC_XR_LABEL, m_ctrlXRotLabel );
	DDX_Control ( pDX, IDC_YR_LABEL, m_ctrlYRotLabel );
	DDX_Control ( pDX, IDC_ZR_LABEL, m_ctrlZRotLabel );
	DDX_Control ( pDX, IDC_THRES, m_ctrlThres );
	DDX_Control ( pDX, IDC_THRES_SEL, m_ctrlThresSel );
	DDX_Control ( pDX, IDC_MOVAVER, m_ctrlMovAverage );
	DDX_Control ( pDX, IDC_MAPERIOD, m_ctrlTimValue );
	DDX_Control ( pDX, IDC_NELEM, m_ctrlNLength );
	DDX_Control ( pDX, IDC_SMATHRES, m_ctrlSMAThres );
	DDX_Control ( pDX, IDC_PULSE, m_ctrlPulse );
	DDX_Control ( pDX, IDC_FREQ, m_ctrlFreq );
	DDX_Control ( pDX, IDC_BALLKEYSTROKE, m_ctrlBallKeystroke );
	DDX_Control ( pDX, IDC_ABREMAP, m_ctrlRemapAB );
	DDX_Control ( pDX, IDC_BEEP, m_ctrlBeep );
	DDX_Control ( pDX, IDC_TEXTTOFIND, m_ctrlTextToFind );
	DDX_Control ( pDX, IDC_BROADCASTMSG, m_ctrlBroadcast );
	DDX_Control ( pDX, IDC_HANDLE, m_ctrlHandle );
	DDX_Control ( pDX, IDC_NBYTESREAD, m_ctrlNBytesRead );
	DDX_Control ( pDX, IDC_NBYTESWRIT, m_ctrlNBytesWritten );
	DDX_Control ( pDX, IDC_FLASHWIN, m_ctrlFlashWin );
	DDX_Control ( pDX, IDC_STATUSBAR, m_ctrlStatusBar );
}

BEGIN_MESSAGE_MAP ( CSBWAppDlg, CDialogEx )
	ON_BN_CLICKED ( IDC_1DOF, &CSBWAppDlg::OnBnClicked1DoF )
	ON_BN_CLICKED ( IDC_2DOF, &CSBWAppDlg::OnBnClicked2DoF )
	ON_BN_CLICKED ( IDC_4DOF, &CSBWAppDlg::OnBnClicked4DoF )
	ON_BN_CLICKED ( IDC_ABOUT, &CSBWAppDlg::OnAbout )
	ON_BN_CLICKED ( IDC_ABREMAP, &CSBWAppDlg::OnBnClickedAbremap )
	ON_BN_CLICKED ( IDC_ADD, &CSBWAppDlg::OnAddCMDs )
	ON_BN_CLICKED ( IDC_ADDBYTE, &CSBWAppDlg::OnAddByteValue )
	ON_BN_CLICKED ( IDC_APPEND, &CSBWAppDlg::OnBnClickedAppend )
	ON_BN_CLICKED ( IDC_BALLKEYSTROKE, &CSBWAppDlg::OnBnClickedBallkeystroke )
	ON_BN_CLICKED ( IDC_BOTH, &CSBWAppDlg::OnBnClickedBoth )
	ON_BN_CLICKED ( IDC_BROADCASTMSG, &CSBWAppDlg::OnBnClickedBroadcastmsg )
	ON_BN_CLICKED ( IDC_CLEARALL, &CSBWAppDlg::OnClearAll )
	ON_BN_CLICKED ( IDC_CLEARTEXT, &CSBWAppDlg::OnClearText )
	ON_BN_CLICKED ( IDC_CONNECT, &CSBWAppDlg::OnConnect )
	ON_BN_CLICKED ( IDC_FLASHWIN, &CSBWAppDlg::OnFlashWin )
	ON_BN_CLICKED ( IDC_LOAD, &CSBWAppDlg::OnLoadSett )
	ON_BN_CLICKED ( IDC_MOVAVER, &CSBWAppDlg::OnMovAverage )
	ON_BN_CLICKED ( IDC_RESET, &CSBWAppDlg::OnReset )
	ON_BN_CLICKED ( IDC_ROTATION, &CSBWAppDlg::OnBnClickedRotation )
	ON_BN_CLICKED ( IDC_SAVE, &CSBWAppDlg::OnSaveSett )
	ON_BN_CLICKED ( IDC_SETDEV, &CSBWAppDlg::OnSetDevice )
	ON_BN_CLICKED ( IDC_SETSIGNAL, &CSBWAppDlg::OnSetSignal )
	ON_BN_CLICKED ( IDC_TRANSLATION, &CSBWAppDlg::OnBnClickedTranslation )
	ON_CBN_SELCHANGE ( IDC_THRES_SEL, &CSBWAppDlg::OnThresSel )
	ON_EN_SETFOCUS ( IDC_STATUSBAR, &CSBWAppDlg::OnEnSetfocusStatusbar )
	ON_EN_UPDATE ( IDC_BYTEVALUE, &CSBWAppDlg::OnUpdateByteValue )
	ON_EN_UPDATE ( IDC_FREQ, &CSBWAppDlg::OnUpdateFreq )
	ON_EN_UPDATE ( IDC_MAPERIOD, &CSBWAppDlg::OnUpdateMovAverPeriod )
	ON_EN_UPDATE ( IDC_PEROFFSET, &CSBWAppDlg::OnUpdatePeroffset )
	ON_EN_UPDATE ( IDC_SMATHRES, &CSBWAppDlg::OnSMAThresUpdate )
	ON_EN_UPDATE ( IDC_TEXTTOFIND, &CSBWAppDlg::OnEnUpdateTexttofind )
	ON_EN_UPDATE ( IDC_THRES, &CSBWAppDlg::OnUpdateThres )
	ON_EN_UPDATE ( IDC_XROFFSET, &CSBWAppDlg::OnUpdateXroffset )
	ON_EN_UPDATE ( IDC_XTOFFSET, &CSBWAppDlg::OnUpdateXtoffset )
	ON_EN_UPDATE ( IDC_YROFFSET, &CSBWAppDlg::OnUpdateYroffset )
	ON_EN_UPDATE ( IDC_YTOFFSET, &CSBWAppDlg::OnUpdateYtoffset )
	ON_EN_UPDATE ( IDC_ZROFFSET, &CSBWAppDlg::OnUpdateZroffset )
	ON_EN_UPDATE ( IDC_ZTOFFSET, &CSBWAppDlg::OnUpdateZtoffset )
	ON_MESSAGE ( SBE_MESSAGE, &CSBWAppDlg::SBE_Message )
	ON_NOTIFY ( NM_RELEASEDCAPTURE, IDC_NELEM, &CSBWAppDlg::OnNElements )
	ON_REGISTERED_MESSAGE ( WM_SBEXPLORER_QUERY, &CSBWAppDlg::OnSbExplorerQuery )
	ON_WM_PAINT ( )
	ON_WM_QUERYDRAGICON ( )
	ON_WM_SETCURSOR ( )
	ON_WM_TIMER ( )
END_MESSAGE_MAP ( )

void DetectComPorts ( CStringArray &ports, int upperLimit = 128 )
{
	for ( int i = 1; i <= upperLimit; i++ ) {
		CString strPort;
		strPort.Format ( _T ( "COM%d" ), i );
		DWORD dwSize = 0;
		LPCOMMCONFIG lpCC = ( LPCOMMCONFIG ) new BYTE[1];

		if ( GetDefaultCommConfig ( strPort, lpCC, &dwSize ) != TRUE ) {
			delete[] lpCC;
			lpCC = ( LPCOMMCONFIG ) new BYTE[dwSize];
			BOOL ret = GetDefaultCommConfig ( strPort, lpCC, &dwSize );
			delete[] lpCC;

			if ( ret ) {
				ports.Add ( strPort );
			}
		}
	}
}

// CSBWAppDlg message handlers
void CSBWAppDlg::PropCallBack ( CMFCPropertyGridProperty2 *pObj, bool bValue )
{
	UNREFERENCED_PARAMETER ( pObj );
	UNREFERENCED_PARAMETER ( bValue );
}

BOOL CSBWAppDlg::OnInitDialog ( )
{
	CDialogEx::OnInitDialog ( );
	// Set the icon for this dialog.  The framework does this automatically when the application's main window is not a dialog
	SetIcon ( m_hIcon, TRUE );			// Set big icon
	SetIcon ( m_hIcon, FALSE );		    // Set small icon
	CStringArray SerialPorts;
	CString SerialPort;

	int StringIds[] = {
		IDS_ERROR, IDS_WARNING, IDS_QUESTION, IDS_SPATIAL, IDS_VECTOR, IDS_POST, IDS_PARENT, IDS_PLANAR, IDS_LINEAR,
		IDS_LOCAL, IDS_BINARY, IDS_DONOTCHANGE, IDS_NOFREEDOM, IDS_DELTAMATRIX, IDS_ABSOLUTEMATRIX, IDS_MSG1, IDS_INFO,
		IDS_PRINTABLE, IDS_PRE, IDS_DISCONNECT, IDS_CONNECT, IDS_NOTIMPLEM, IDS_VALNOTAPPLIC, IDS_CLEARBREAK, IDS_SETBREAK,
		IDS_CLEARDTR, IDS_SETDTR, IDS_CLEARRTS, IDS_SETRTS, IDS_SETXOFF, IDS_SETXON, IDS_RESETDEV, IDS_ERROR2,
		IDS_INFO2, IDS_WAITNEWEV, IDS_NEWEVENT, IDS_SBALL4000, IDS_NOTREADY, IDS_NEWLINE, IDS_MUSTENABLESMA, IDS_INVWIN,
		IDS_INVFILE, IDS_SETDEVNSUC, IDS_USEMENUSELI, IDS_HEXPREFIX, IDS_FILEEXT, IDS_HEXPREFIX2, IDS_HEXPREFIX3, IDS_HEXPREFIX4, IDS_ZERO,
		IDS_OUTPUT, IDS_FREEDOM, IDS_MODE, IDS_THRESHOLD, IDS_MINIMUM, IDS_MAXIMUM, IDS_ROTATION, IDS_TRANSLATION, IDS_COMMANDS,
		IDS_HANDEDNESS, IDS_RESPONSIVENESS, IDS_MANTISSA, IDS_EXPONENT, IDS_BEEPER, IDS_DATA_TYPE, IDS_ROTATION_FORM, IDS_SPIN_RATE,
		IDS_BALL_SYSTEM, IDS_FREEDOM_VECTOR, IDS_LEFT_HANDED, IDS_ROTATION_MODE, IDS_TRANSLATION_MODE, IDS_RESPONSE_MUL, IDS_PRE_POST_PROC,
		IDS_TRANSLATION_SENS, IDS_SENSITIVITY_MODE, IDS_ORIENTATION_MATRIX, IDS_COMM_MODE_PACKET, IDS_R_OUTPUT_SYSTEM, IDS_A_ROTATION_MATRIX,
		IDS_O_ROTATION_MATRIX, IDS_C_COMM_MODE, IDS_R_BALL_SYSTEM, IDS_T_BALL_SYSTEM, IDS_T_FREE_VECTOR_SYS, IDS_T_OUTPUT_SYS,
		IDS_R_FREE_VECTOR_SYS, IDS_M_TRANS_MODE, IDS_M_ROTATION_MODE, IDS_M_ROT_DATA_TYPE, IDS_M_HANDEDNESS, IDS_P_MAX_PERIOD,
		IDS_P_MIN_PERIOD, IDS_N_NULL_RADIUS, IDS_S_SPIN_R_MANTISSA, IDS_S_SPIN_R_EXPON, IDS_M_PRE_POST_PROC, IDS_FT_FEEL, IDS_FR_FEEL,
		IDS_B_BEEPER, IDS_X_SENSITIVITY, IDS_T_TRANS_FREE_VECTOR, IDS_R_ROT_FREE_VECTOR, IDS_Z, IDS_Y
	};

	for ( int i = 0; i < sizeof ( StringIds ) / sizeof ( int ); i++ ) {
		m_clString[StringIds[i]] = CString ( MAKEINTRESOURCE ( StringIds[i] ) );
	}

	m_pShortener[0] = &m_SBW.m_stButtons.bButton_SB4000FLX;
	m_pShortener[1] = &m_SBW.m_stButtons.bButton_SB3000;
	m_pShortener[2] = &m_SBW.m_stCoord;

	m_clString[0] = _T ( "" );

	DetectComPorts ( SerialPorts );

	for ( int i = 0; i < SerialPorts.GetCount ( ); i++ ) {
		m_ctrlPortList.AddString ( SerialPorts.GetAt ( i ) );
	}

	m_ctrlBroadcast.SetCheck ( BST_CHECKED );

	m_ctrlBeep.EnableWindow ( FALSE );

	m_ctrlNBytesRead.m_dMinValue = 0;
	m_ctrlNBytesRead.m_dMaxValue = (double) 0xFFFFFFFF;
	m_ctrlNBytesRead.m_dDefValue = 0;
	m_ctrlNBytesRead.SetValue ( 0, 0 );

	m_ctrlNBytesWritten.m_dMinValue = 0;
	m_ctrlNBytesWritten.m_dMaxValue = (double) 0xFFFFFFFF;
	m_ctrlNBytesWritten.m_dDefValue = 0;
	m_ctrlNBytesWritten.SetValue ( 0, 0 );

	m_ctrlNLength.EnableWindow ( FALSE );
	m_ctrlSMAThres.EnableWindow ( FALSE );
	m_ctrlSMAThres.m_dMinValue = 0.1;
	m_ctrlSMAThres.m_dMaxValue = 0.99;
	m_ctrlSMAThres.m_dDefValue = 0.75;
	m_ctrlSMAThres.SetValue ( 0.75 );

	m_ctrlTimValue.m_dMinValue = 50;
	m_ctrlTimValue.m_dMaxValue = 2500;
	m_ctrlTimValue.m_dDefValue = 150;
	m_ctrlTimValue.SetValue ( 150, 0 );
	m_ctrlTimValue.EnableWindow ( FALSE );

	m_ctrlThres.m_dMinValue = 0;
	m_ctrlThres.m_dMaxValue = 300;
	m_ctrlThres.m_dDefValue = 25;
	m_ctrlThres.SetValue ( 25, 0 );

	m_ctrlFreq.m_dMinValue = 1;
	m_ctrlFreq.m_dMaxValue = 200;
	m_ctrlFreq.m_dDefValue = 80;
	m_ctrlFreq.SetValue ( 80.0 );

	m_ctrlSetSignal.EnableWindow ( FALSE );
	m_ctrlPortList.SetCurSel ( 0 );

	m_ctrlAppendRead.SetCheck ( BST_UNCHECKED );
	m_SBW.m_bAppendData = false;

	m_ctrlClearBREAK.SetCheck ( BST_CHECKED );
	m_ctrlAddCR.SetCheck ( BST_CHECKED );
	Reset_COM_Group ( );
	m_SBW.m_bAutoClearBREAK = true;

	m_SignalMenu.CreatePopupMenu ( );
	m_SignalMenu.AppendMenu ( MF_STRING, 1, m_clString[IDS_CLEARBREAK] );
	m_SignalMenu.AppendMenu ( MF_STRING, 2, m_clString[IDS_SETBREAK] );
	m_SignalMenu.AppendMenu ( MF_SEPARATOR, 0, _T ( "-" ) );
	m_SignalMenu.AppendMenu ( MF_STRING, 3, m_clString[IDS_CLEARDTR] );
	m_SignalMenu.AppendMenu ( MF_STRING, 4, m_clString[IDS_SETDTR] );
	m_SignalMenu.AppendMenu ( MF_SEPARATOR, 0, _T ( "-" ) );
	m_SignalMenu.AppendMenu ( MF_STRING, 5, m_clString[IDS_CLEARRTS] );
	m_SignalMenu.AppendMenu ( MF_STRING, 6, m_clString[IDS_SETRTS] );
	m_SignalMenu.AppendMenu ( MF_SEPARATOR, 0, _T ( "-" ) );
	m_SignalMenu.AppendMenu ( MF_STRING, 7, m_clString[IDS_SETXOFF] );
	m_SignalMenu.AppendMenu ( MF_STRING, 8, m_clString[IDS_SETXON] );
	m_SignalMenu.AppendMenu ( MF_SEPARATOR, 0, _T ( "-" ) );
	m_SignalMenu.AppendMenu ( MF_STRING, 9, m_clString[IDS_RESETDEV] );
	m_ctrlSetSignal.m_hMenu = m_SignalMenu.GetSafeHmenu ( );
	//m_ctrlSetSignal.SizeToContent ( );
	m_ctrlSetSignal.m_bOSMenu = FALSE;
	m_ctrlSetSignal.m_bDefaultClick = TRUE;

	CRect rectPropList;
	m_ctrlLocation.GetClientRect ( &rectPropList );
	m_ctrlLocation.MapWindowPoints ( this, &rectPropList );
	m_ctrlSettings.Create ( WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectPropList, this, (UINT) - 1 );
	m_ctrlSettings.EnableHeaderCtrl ( );
	m_ctrlSettings.EnableDescriptionArea ( );
	m_ctrlSettings.SetVSDotNetLook ( TRUE );
	m_ctrlSettings.MarkModifiedProperties ( TRUE );
	m_ctrlSettings.SetAlphabeticMode ( FALSE );
	m_ctrlSettings.SetShowDragContext ( FALSE );

	SetDefaults ( );

	//! General and Mode
	std::auto_ptr<CMFCPropertyGridProperty2> apGeneral ( new CMFCPropertyGridProperty2 ( -1, m_clString[IDS_COMMANDS] ) );
	apGeneral.get ( )->OnUpdateAnyItem = (PropCallback) & CSBWAppDlg::PropCallBack;

	CArray<__int64, __int64> Min;
	CArray<__int64, __int64> Max;
	//! Threshold
	CreateProp_Threshold ( Min, Max );
	//! Translation Sensitivities
	CreateProp_TranslationSensitivities ( Min, Max );
	//! Mode
	CreateProp_Mode ( );
	//! Responsiveness
	CreateProp_Responsiveness ( Min, Max );
	//! Response Multiplier
	CreateProp_ResponseMultiplier ( Min, Max );
	//! Spin Rate
	CreateProp_SpinRate ( Min, Max );
	//! Translation Mode
	CreateProp_TranslationMode ( Min, Max );
	//! Rotation Mode
	CreateProp_RotationMode ( Min, Max );
	//! Absolute matrix
	CreateProp_AbsoluteMatrix ( Min, Max );
	//! Orientation matrix
	CreateProp_Orientation ( Min, Max );
	//! Zero
	CreateProp_Zero ( );
	//! Beeper
	CreateProp_Beeper ( Min, Max );
	//! No information available to support implementation
	CreateProp_UnvInfo ( Min, Max );

	int Idx[] = {IDX_ABMX, IDX_BEEP, IDX_LINS, IDX_MODP, IDX_THRE, IDX_TENS, IDX_ORIE,
				 IDX_ZERO, IDX_RESS, IDX_REMU, IDX_SPRT, IDX_TRMD, IDX_RODE, IDX_MODE
				};

	for ( int i = 0; i < sizeof ( Idx ) / sizeof ( int ); i++ ) {
		apGeneral->AddSubItem ( m_clCtrlItem[Idx[i]] );
	}

	apGeneral->Update ( );

	m_ctrlSettings.AddProperty ( apGeneral.release ( ) );

	CButton *pButton1 = ( CButton *) GetDlgItem ( IDC_BOTH );
	pButton1->SetCheck ( BST_CHECKED );
	m_iFreedMov = 2;

	pButton1 = ( CButton *) GetDlgItem ( IDC_1DOF );
	pButton1->SetCheck ( BST_CHECKED );
	m_iDoF = 0;

	m_ctrlThresSel.SetCurSel ( 0 );
	OnThresSel ( );

	pButton1 = ( CButton *) GetDlgItem ( IDC_DIGITAL );
	pButton1->SetCheck ( BST_CHECKED );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below to draw the icon. For
// MFC applications using the document/view model, this is automatically done for you by the framework.

void CSBWAppDlg::OnPaint ( )
{
	if ( IsIconic ( ) ) {
		CPaintDC dc ( this ); // device context for painting
		SendMessage ( WM_ICONERASEBKGND, reinterpret_cast< WPARAM > ( dc.GetSafeHdc ( ) ), 0 );
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics ( SM_CXICON );
		int cyIcon = GetSystemMetrics ( SM_CYICON );
		CRect rect;
		GetClientRect ( &rect );
		int x = ( rect.Width ( ) - cxIcon + 1 ) / 2;
		int y = ( rect.Height ( ) - cyIcon + 1 ) / 2;
		// Draw the icon
		dc.DrawIcon ( x, y, m_hIcon );
	}

	else {
		CDialogEx::OnPaint ( );
	}
}

// The system calls this function to obtain the cursor to display while the m_stUser. drags the minimized window.
HCURSOR CSBWAppDlg::OnQueryDragIcon ( )
{
	return static_cast< HCURSOR > ( m_hIcon );
}

void CSBWAppDlg::Reset ( )
{
	if ( m_uipTimer ) {
		m_uipTimer = 0;
		KillTimer ( ID_TIMER );
	}

	m_clCriSec.Lock ( );

	for ( int iMov = 0; iMov < 6; iMov++ ) {
		m_bMoving_State_Ball2[iMov].clear ( );
	}

	m_clCriSec.Unlock ( );

	ZeroMemory ( &m_bNotAllowNewTimer, sizeof ( m_bNotAllowNewTimer ) );
	ZeroMemory ( &m_bCurrent_State_Ball, sizeof ( m_bCurrent_State_Ball ) );
	ZeroMemory ( &m_bFinal_State_Ball, sizeof ( m_bFinal_State_Ball ) );
	ZeroMemory ( &m_bPrevious_Final_State_Ball, sizeof ( m_bPrevious_Final_State_Ball ) );

	if ( m_hTimerQueue != NULL ) {
		DeleteTimerQueue ( m_hTimerQueue );
		m_hTimerQueue = NULL;
	}
}

void CSBWAppDlg::OnConnect ( )
{
	if ( m_ctrlConnect.GetCheck ( ) & BST_CHECKED ) {
		CString Port;
		m_ctrlPortList.GetLBText ( m_ctrlPortList.GetCurSel ( ), Port );

		if ( m_SBW.Connect ( this->GetSafeHwnd ( ), Port, 1024 ) == 0 ) {
			m_ctrlConnect.SetWindowText ( m_clString[IDS_DISCONNECT] );
			m_ctrlSetSignal.EnableWindow ( TRUE );
			m_ctrlPortList.EnableWindow ( FALSE );
			m_ctrlSetDev.EnableWindow ( TRUE );

			Reset ( );

			m_hTimerQueue = CreateTimerQueue ( );

			if ( m_uipTimer == 0 ) {
				m_uipTimer = SetTimer ( ID_TIMER, ( UINT ) ( ( 1.0 / m_iFreq ) * 1000.0 ), NULL );
			}
		}

		else {
			MessageBox ( m_clString[IDS_NOTREADY], m_clString[IDS_ERROR2], MB_OK );
		}
	}

	else {
		m_SBW.Disconnect ( );
		m_ctrlConnect.SetWindowText ( m_clString[IDS_CONNECT] );
		m_ctrlSetSignal.EnableWindow ( FALSE );
		m_ctrlPortList.EnableWindow ( TRUE );
		m_ctrlSetDev.EnableWindow ( FALSE );
	}
}

void CSBWAppDlg::OnCancel ( )
{
	m_SBW.Disconnect ( );

	if ( !m_SBW.CloseRequest ( ) ) {
		CDialog::OnCancel ( );
	}
}

void CSBWAppDlg::Reset_Cmd_Group ( )
{
	m_ctrlCmdList.SetWindowText ( m_clString[0] );
}

void CSBWAppDlg::Reset_COM_Group ( )
{
	CButton *btns[] = { &m_ctrlBREAK, &m_ctrlCTS, &m_ctrlDSR, &m_ctrlERR,
						&m_ctrlFRAME, &m_ctrlOVERRUN, &m_ctrlRING, &m_ctrlRLSD,
						&m_ctrlRXCHAR, &m_ctrlRXFLAG, &m_ctrlRXOVER, &m_ctrlRXPARITY,
						&m_ctrlTXEMPTY
					  };

	for ( int i = 0; i < sizeof ( btns ) / sizeof ( CButton *); i++ ) {
		btns[i]->SetCheck ( BST_UNCHECKED );
	}
}

void CSBWAppDlg::Print ( )
{
	if ( m_ctrlReport.GetCheck ( ) == BST_UNCHECKED ) {
		return;
	}

	DWORD dwSize = m_SBW.m_clRAWData.size ( );
	INT_PTR rows = ( INT_PTR ) floor ( ( float ) dwSize / 8.0f );
	char val;
	CString Temp, Str, Str1;

	for ( INT_PTR row = 0; row < rows + ( ( dwSize % 8 ) ? 1 : 0 ); row++ ) {
		for ( INT_PTR col = 0; col < ( ( ( ( row * 8 ) + col ) < ( INT_PTR ) dwSize ) ? 8 : ( INT_PTR ) dwSize % 8 ); col++ ) {
			val = m_SBW.m_clRAWData.at ((row * 8) + col);
			Temp.Format ( _T ( " %02X" ), ( unsigned char ) val );
			Str += Temp;

			if ( ( val >= 32 ) && ( val <= 126 ) ) {
				Temp.Format ( _T ( "%c" ), ( unsigned char ) val );
			}

			else {
				Temp.Empty ( );

				if ( m_ctrlNonPrint.GetCheck ( ) & BST_CHECKED ) {
					Temp.Format ( _T ( "\xf0" ) );
				}
			}

			Str1 += Temp;
		}

		Str += m_clString[IDS_NEWLINE];
		Str1 += m_clString[IDS_NEWLINE];
	}

	m_ctrlHexData.SetWindowText ( Str );
	m_ctrlASCIIData.SetWindowText ( Str1 );
}

LRESULT CSBWAppDlg::SBE_Message ( WPARAM wParam, LPARAM lParam )
{
	UNREFERENCED_PARAMETER ( lParam );

	switch ( wParam ) {
		case SBE_CLOSE_COMM: {
				Reset ( );
				EndDialog ( 0 );
			}
			break;

		case SBE_RESET_COMM: {
				m_ctrlNBytesRead.SetValue ( 0, 0 );
				m_ctrlNBytesWritten.SetValue ( 0, 0 );
				Reset_COM_Group ( );
			}
			break;

		case SBE_READ_COMM: {

				INT_PTR iIndex = 0;
				void *Ptr      = NULL;

				__int64 iNRead = m_SBW.m_iBytesRead;
				m_ctrlNBytesRead.SetValue ( iNRead, 0 );

				Print ( );

				while ( m_SBW.GetCommand ( iIndex, &Ptr, m_iCommand ) != -1 ) {
					ProcessCommand ( m_iCommand );
				}
			}
			break;

		case SBE_PRESTATUS_COMM: {
				m_ctrlWaitingEventMsg.SetWindowText ( m_clString[IDS_WAITNEWEV] );
				Reset_COM_Group ( );
			}
			break;

		case SBE_STATUS_COMM: {
				CString Temp, Str;
				CButton *btns[] = { &m_ctrlBREAK, &m_ctrlCTS, &m_ctrlDSR, &m_ctrlERR,
									&m_ctrlRING, &m_ctrlRLSD, &m_ctrlRXCHAR, &m_ctrlRXFLAG,
									&m_ctrlTXEMPTY, &m_ctrlFRAME, &m_ctrlOVERRUN, &m_ctrlRXOVER,
									&m_ctrlRXPARITY
								  };

				int Idx[] = { SBE_SERIAL_BREAK, SBE_SERIAL_CTS, SBE_SERIAL_DSR, SBE_SERIAL_ERR, SBE_SERIAL_RING, SBE_SERIAL_RLSD,
							  SBE_SERIAL_RXCHAR, SBE_SERIAL_RXFLAG, SBE_SERIAL_TXEMPTY, SBE_SERIAL_FRAME, SBE_SERIAL_OVERRUN,
							  SBE_SERIAL_RXOVER, SBE_SERIAL_RXPARITY
							};

				m_ctrlWaitingEventMsg.SetWindowText ( m_clString[IDS_NEWEVENT] );

				for ( int i = 0; i < sizeof ( btns ) / sizeof ( CButton *); i++ ) {
					btns[i]->SetCheck ( m_SBW.m_stStatus.Reg[Idx[i]] ? BST_CHECKED : BST_UNCHECKED );
				}
			}
			break;

		case SBE_WRITE_COMM: {
				__int64 iNWritten = m_SBW.m_iBytesWritten;
				m_ctrlNBytesWritten.SetValue ( iNWritten, 0 );
			}
			break;

		default: {
				return 0;
			}
	}

	return 1;
}

void CSBWAppDlg::OnTimer ( UINT_PTR nIDEvent )
{
	if ( nIDEvent == ID_TIMER ) {

		if ( m_ctrlBallKeystroke.GetCheck ( ) == BST_CHECKED ) {
			SendBallKeystrokes ( );
		}
	}

	else if ( nIDEvent == ID_TIMER_CLEARSTATUSBAR ) {
		m_ctrlStatusBar.SetWindowText ( m_clString[0] );
		KillTimer ( ID_TIMER_CLEARSTATUSBAR );
	}

	CDialogEx::OnTimer ( nIDEvent );
}

void CSBWAppDlg::PutValue ( CEdit *pObj, bool bValue, short sValue )
{
	CString Temp;

	if ( pObj == NULL ) {
		return;
	}

	if ( bValue ) {
		Temp.Format ( _T ( "%d" ), sValue );
	}

	else {
		Temp = _T ( "???" );
	}

	pObj->SetWindowText ( Temp );
}

void CSBWAppDlg::GetAbsoluteValue ( bool bValue, short sCurrValue, short sThres, short &sValue )
{
	if ( bValue ) {
		short sTemp = abs ( sCurrValue ) - sThres;
		sValue = sTemp > 0 ? sTemp : 0;
	}

	else {
		sValue = 0;
	}
}

bool CSBWAppDlg::CheckValue ( short sV0, short sV1, short sV2, short sV3, short sV4, short sV5 )
{
	if ( ( sV0 > sV1 ) && ( sV0 > sV2 ) && ( sV0 > sV3 ) && ( sV0 > sV4 ) && ( sV0 > sV5 ) ) {
		return true;
	}

	return false;
}

bool CSBWAppDlg::CheckValue ( short sV0, short sV1, short sV2 )
{
	if ( ( sV0 > sV1 ) && ( sV0 > sV2 ) ) {
		return true;
	}

	return false;
}

bool CSBWAppDlg::CheckValue ( float fV0, float fV1, float fV2, float fV3, float fV4, float fV5 )
{
	if ( ( fV0 > fV1 ) && ( fV0 > fV2 ) && ( fV0 > fV3 ) && ( fV0 > fV4 ) && ( fV0 > fV5 ) ) {
		return true;
	}

	return false;
}

bool CSBWAppDlg::CheckValue ( float fV0, float fV1, float fV2 )
{
	if ( ( fV0 > fV1 ) && ( fV0 > fV2 ) ) {
		return true;
	}

	return false;
}

bool CSBWAppDlg::CheckValue ( int iV, int iN, float *fV )
{
	bool bValue = true;

	for ( int i = 0; i < iN; i++ ) {
		if ( i != iV ) {
			if ( fV[iV] <= fV[i] ) {
				bValue = false;
			}
		}
	}

	return bValue;
}

void CSBWAppDlg::ProcessCommand ( INT_PTR iCommand )
{
	//Reset_Cmd_Group ( );
	CString Str, Temp;

	if ( m_ctrlReport.GetCheck ( ) == BST_CHECKED ) {
		m_ctrlCmdList.GetWindowText ( Str );
	}

	switch ( iCommand ) {
		case SBE_COMMAND_INT: {
			}
			break;

		case SBE_COMMAND_K: {
				Str += _T ( "K\r\n" );
			}

		//break;

		case SBE_COMMAND_PNT: {
				if ( m_SBW.m_clDeviceInfo.Find ( CT2A (m_clString[IDS_SBALL4000]) ) != -1 ) {
					Str += _T ( "K\r\n.\r\n" );
				}

				RemapButtonsToF13_F24 ( );

				RemapButtonsToConfig ( );

				m_ctrlButton1.SetCheck ( ( BTN_SB4000FLX[SBE_BUTTON_1] | BTN_SB3000[SBE_BUTTON_1] ) ? BST_CHECKED : BST_UNCHECKED );
				m_ctrlButton2.SetCheck ( ( BTN_SB4000FLX[SBE_BUTTON_2] | BTN_SB3000[SBE_BUTTON_2] ) ? BST_CHECKED : BST_UNCHECKED );
				m_ctrlButton3.SetCheck ( ( BTN_SB4000FLX[SBE_BUTTON_3] | BTN_SB3000[SBE_BUTTON_3] ) ? BST_CHECKED : BST_UNCHECKED );
				m_ctrlButton4.SetCheck ( ( BTN_SB4000FLX[SBE_BUTTON_4] | BTN_SB3000[SBE_BUTTON_4] ) ? BST_CHECKED : BST_UNCHECKED );
				m_ctrlButton5.SetCheck ( ( BTN_SB4000FLX[SBE_BUTTON_5] | BTN_SB3000[SBE_BUTTON_5] ) ? BST_CHECKED : BST_UNCHECKED );
				m_ctrlButton6.SetCheck ( ( BTN_SB4000FLX[SBE_BUTTON_6] | BTN_SB3000[SBE_BUTTON_6] ) ? BST_CHECKED : BST_UNCHECKED );
				m_ctrlButton7.SetCheck ( ( BTN_SB4000FLX[SBE_BUTTON_7] | BTN_SB3000[SBE_BUTTON_7] ) ? BST_CHECKED : BST_UNCHECKED );
				m_ctrlButton8.SetCheck ( ( BTN_SB4000FLX[SBE_BUTTON_8] | BTN_SB3000[SBE_BUTTON_8] ) ? BST_CHECKED : BST_UNCHECKED );
				m_ctrlButton9.SetCheck ( BTN_SB4000FLX[SBE_BUTTON_9] ? BST_CHECKED : BST_UNCHECKED );
				m_ctrlButtonA.SetCheck ( BTN_SB4000FLX[SBE_BUTTON_A] ? BST_CHECKED : BST_UNCHECKED );
				m_ctrlButtonB.SetCheck ( BTN_SB4000FLX[SBE_BUTTON_B] ? BST_CHECKED : BST_UNCHECKED );
				m_ctrlButtonC.SetCheck ( BTN_SB4000FLX[SBE_BUTTON_C] ? BST_CHECKED : BST_UNCHECKED );
			}
			break;

		case SBE_COMMAND_RES: {
				Str += _T ( "@\r\n" );
			}
			break;

		case SBE_COMMAND_DBQ: {
				Str += _T ( "\"\r\n" );
			}
			break;

		case SBE_COMMAND_A: {
				Str += _T ( "A\r\n" );
			}
			break;

		case SBE_COMMAND_B: {
				Str += _T ( "B\r\n" );
			}
			break;

		case SBE_COMMAND_C: {
				Str += _T ( "C\r\n" );
			}
			break;

		case SBE_COMMAND_D: {
				Str += _T ( "D\r\n" );
				short XTra = 0, YTra = 0, ZTra = 0;
				short XRot = 0, YRot = 0, ZRot = 0;
				//Note: Set Edit control value
				PutValue ( &m_ctrlPeriodValue, COORD->bPeriod, COORD->sCurrent_Period );
				PutValue ( &m_ctrlXTransValue, COORD->bXTrans, COORD->sCurrent_XTrans );
				PutValue ( &m_ctrlYTransValue, COORD->bYTrans, COORD->sCurrent_YTrans );
				PutValue ( &m_ctrlZTransValue, COORD->bZTrans, COORD->sCurrent_ZTrans );
				PutValue ( &m_ctrlXRotValue, COORD->bXRot, COORD->sCurrent_XRot );
				PutValue ( &m_ctrlYRotValue, COORD->bYRot, COORD->sCurrent_YRot );
				PutValue ( &m_ctrlZRotValue, COORD->bZRot, COORD->sCurrent_ZRot );

				//Note: Get magnitude value
				if ( ( m_iFreedMov == 0 ) || ( m_iFreedMov == 2 ) ) {
					GetAbsoluteValue ( COORD->bXTrans, COORD->sCurrent_XTrans, m_clThreshold[ XTRA ], XTra );
					GetAbsoluteValue ( COORD->bYTrans, COORD->sCurrent_YTrans, m_clThreshold[ YTRA ], YTra );
					GetAbsoluteValue ( COORD->bZTrans, COORD->sCurrent_ZTrans, m_clThreshold[ ZTRA ], ZTra );
				}

				if ( ( m_iFreedMov == 1 ) || ( m_iFreedMov == 2 ) ) {
					GetAbsoluteValue ( COORD->bXRot, COORD->sCurrent_XRot, m_clThreshold[ XROT ], XRot );
					GetAbsoluteValue ( COORD->bYRot, COORD->sCurrent_YRot, m_clThreshold[ YROT ], YRot );
					GetAbsoluteValue ( COORD->bZRot, COORD->sCurrent_ZRot, m_clThreshold[ ZROT ], ZRot );
				}

				CurrentBallState ( XTra, YTra, ZTra, XRot, YRot, ZRot );

				BallState ( );
			}
			break;

		case SBE_COMMAND_E: {
				Str += _T ( "E\r\n" );
			}
			break;

		case SBE_COMMAND_F: {
				Str += _T ( "F\r\n" );
			}
			break;

		case SBE_COMMAND_H: {
				Str += _T ( "H\r\n" );
			}
			break;

		case SBE_COMMAND_M: {
				Str += _T ( "M\r\n" );
			}
			break;

		case SBE_COMMAND_N: {
				Str += _T ( "N\r\n" );
			}
			break;

		case SBE_COMMAND_O: {
				Str += _T ( "O\r\n" );
			}
			break;

		case SBE_COMMAND_P: {
				Str += _T ( "P\r\n" );
			}
			break;

		case SBE_COMMAND_R: {
				Str += _T ( "R\r\n" );
			}
			break;

		case SBE_COMMAND_S: {
				Str += _T ( "S\r\n" );
			}
			break;

		case SBE_COMMAND_T: {
				Str += _T ( "T\r\n" );
			}
			break;

		case SBE_COMMAND_X: {
				Str += _T ( "X\r\n" );
			}
			break;

		case SBE_COMMAND_Z: {
				Str += _T ( "Z\r\n" );
			}
			break;
	}

	if ( m_ctrlReport.GetCheck ( ) == BST_CHECKED ) {
		m_ctrlCmdList.SetWindowText ( Str );
	}
}

bool CSBWAppDlg::RemapButtonsToF13_F24 ( )
{
	if ( m_ctrlMapButtons.GetCheck ( ) == BST_CHECKED ) {
		INPUT keystroke[1] = { 0 };
		keystroke[0].type = INPUT_KEYBOARD;
		keystroke[0].ki.wScan = 0;
		keystroke[0].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
		keystroke[0].ki.time = 0;
		keystroke[0].ki.dwExtraInfo = GetMessageExtraInfo ( );

		for ( int i = 0; i < 8; i++ ) {
			if ( m_SBW.m_stButtons.bButton_PreviousState_SB4000FLX[ i ] | m_SBW.m_stButtons.bButton_PreviousState_SB3000[ i ] ) {
				keystroke[0].ki.wVk = i + VK_F13;

				if ( SendInput ( ( UINT ) 1, keystroke, sizeof ( INPUT ) ) != 1 ) {
					return false;
				}
			}
		}

		for ( int i = 8; i < 12; i++ ) {
			if ( m_SBW.m_stButtons.bButton_PreviousState_SB4000FLX[i] ) {
				keystroke[0].ki.wVk = i + VK_F13;

				if ( SendInput ( ( UINT ) 1, keystroke, sizeof ( INPUT ) ) != 1 ) {
					return false;
				}
			}
		}

		keystroke[0].ki.dwFlags = KEYEVENTF_UNICODE;

		for ( int i = 0; i < 8; i++ ) {
			if ( BTN_SB4000FLX[i] | BTN_SB3000[i] ) {
				keystroke[0].ki.wVk = i + VK_F13;

				if ( SendInput ( ( UINT ) 1, keystroke, sizeof ( INPUT ) ) != 1 ) {
					return false;
				}
			}
		}

		for ( int i = 8; i < 12; i++ ) {
			if ( BTN_SB4000FLX[i] ) {
				keystroke[0].ki.wVk = i + VK_F13;

				if ( SendInput ( ( UINT ) 1, keystroke, sizeof ( INPUT ) ) != 1 ) {
					return false;
				}
			}
		}
	}

	return true;
}

void CSBWAppDlg::PrintStatus ( CString msg, UINT nElapse, int type )
{
	switch ( type ) {
		case 0:
			MessageBeep ( MB_ICONERROR );
			msg = m_clString[IDS_ERROR] + msg;
			break;

		case 1:
			MessageBeep ( MB_ICONWARNING );
			msg = m_clString[IDS_WARNING] + msg;
			break;

		case 2:
			MessageBeep ( MB_ICONQUESTION );
			msg = m_clString[IDS_QUESTION] + msg;
			break;
	}

	m_ctrlStatusBar.SetWindowText ( msg );
	SetTimer ( ID_TIMER_CLEARSTATUSBAR, nElapse, NULL );
}

void CSBWAppDlg::RemapButtonsToConfig ( )
{
	if ( m_ctrlRemapAB.GetCheck ( ) == BST_CHECKED ) {
		if ( BTN_SB4000FLX[6] | BTN_SB3000[6] ) {
			if ( m_ctrlMovAverage.GetCheck ( ) == BST_CHECKED ) {
				if ( m_ctrlPulse.GetCheck ( ) == BST_CHECKED ) {
					m_ctrlPulse.SetCheck ( BST_UNCHECKED );

					if ( m_ctrlBeep.GetCheck ( ) == BST_CHECKED ) {
						Beep ( 700, 70 );
					}
				}

				else {
					m_ctrlPulse.SetCheck ( BST_CHECKED );
				}
			}

			else {
				PrintStatus ( m_clString[IDS_MUSTENABLESMA], 4000, 0 );
			}
		}

		if ( BTN_SB4000FLX[7] | BTN_SB3000[7] ) {
			CButton *pButton1 = ( CButton *) GetDlgItem ( IDC_1DOF );
			CButton *pButton2 = ( CButton *) GetDlgItem ( IDC_2DOF );
			CButton *pButton3 = ( CButton *) GetDlgItem ( IDC_4DOF );

			if ( m_iDoF == 0 ) {
				pButton1->SetCheck ( BST_UNCHECKED );
				pButton2->SetCheck ( BST_CHECKED );
				pButton3->SetCheck ( BST_UNCHECKED );
				m_iDoF = 1;
			}

			else if ( m_iDoF == 1 ) {
				pButton1->SetCheck ( BST_UNCHECKED );
				pButton2->SetCheck ( BST_UNCHECKED );
				pButton3->SetCheck ( BST_CHECKED );
				m_iDoF = 2;
			}

			else {
				pButton1->SetCheck ( BST_CHECKED );
				pButton2->SetCheck ( BST_UNCHECKED );
				pButton3->SetCheck ( BST_UNCHECKED );
				m_iDoF = 0;

				if ( m_ctrlBeep.GetCheck ( ) == BST_CHECKED ) {
					Beep ( 500, 70 );
				}
			}
		}

		if ( BTN_SB4000FLX[8] ) {
			CButton *pButton1 = ( CButton *) GetDlgItem ( IDC_TRANSLATION );
			CButton *pButton2 = ( CButton *) GetDlgItem ( IDC_ROTATION );
			CButton *pButton3 = ( CButton *) GetDlgItem ( IDC_BOTH );

			if ( m_iFreedMov == 0 ) {
				pButton1->SetCheck ( BST_UNCHECKED );
				pButton2->SetCheck ( BST_CHECKED );
				pButton3->SetCheck ( BST_UNCHECKED );
				m_iFreedMov = 1;
			}

			else if ( m_iFreedMov == 1 ) {
				pButton1->SetCheck ( BST_UNCHECKED );
				pButton2->SetCheck ( BST_UNCHECKED );
				pButton3->SetCheck ( BST_CHECKED );
				m_iFreedMov = 2;

				if ( m_ctrlBeep.GetCheck ( ) == BST_CHECKED ) {
					Beep ( 900, 70 );
				}
			}

			else {
				pButton1->SetCheck ( BST_CHECKED );
				pButton2->SetCheck ( BST_UNCHECKED );
				pButton3->SetCheck ( BST_UNCHECKED );
				m_iFreedMov = 0;
			}
		}
	}
}

void CSBWAppDlg::CurrentBallState ( short XTra, short YTra, short ZTra, short XRot, short YRot, short ZRot )
{
	if ( m_iDoF == 0 ) {
		if ( CheckValue ( XTra, YTra, ZTra, XRot, YRot, ZRot ) ) {
			Set ( &m_bCurrent_State_Ball[0], 5, 1, SBE_YTRANS, SBE_ZTRANS, SBE_XROT, SBE_YROT, SBE_ZROT, SBE_XTRANS );
		}

		else if ( CheckValue ( YTra, XTra, ZTra, XRot, YRot, ZRot ) ) {
			Set ( &m_bCurrent_State_Ball[0], 5, 1, SBE_XTRANS, SBE_ZTRANS, SBE_XROT, SBE_YROT, SBE_ZROT, SBE_YTRANS );
		}

		else if ( CheckValue ( ZTra, XTra, YTra, XRot, YRot, ZRot ) ) {
			Set ( &m_bCurrent_State_Ball[0], 5, 1, SBE_XTRANS, SBE_YTRANS, SBE_XROT, SBE_YROT, SBE_ZROT, SBE_ZTRANS );
		}

		else if ( CheckValue ( XRot, XTra, YTra, ZTra, YRot, ZRot ) ) {
			Set ( &m_bCurrent_State_Ball[0], 5, 1, SBE_XTRANS, SBE_YTRANS, SBE_ZTRANS, SBE_YROT, SBE_ZROT, SBE_XROT );
		}

		else if ( CheckValue ( YRot, XTra, YTra, ZTra, XRot, ZRot ) ) {
			Set ( &m_bCurrent_State_Ball[0], 5, 1, SBE_XTRANS, SBE_YTRANS, SBE_ZTRANS, SBE_XROT, SBE_ZROT, SBE_YROT );
		}

		else if ( CheckValue ( ZRot, XTra, YTra, ZTra, XRot, YRot ) ) {
			Set ( &m_bCurrent_State_Ball[0], 5, 1, SBE_XTRANS, SBE_YTRANS, SBE_ZTRANS, SBE_XROT, SBE_YROT, SBE_ZROT );
		}

		else {
			Set ( &m_bCurrent_State_Ball[0], 6, 0, SBE_XTRANS, SBE_YTRANS, SBE_ZTRANS, SBE_XROT, SBE_YROT, SBE_ZROT );
		}
	}

	else if ( m_iDoF == 1 ) {
		if ( CheckValue ( XTra, YTra, ZTra ) ) {
			Set ( &m_bCurrent_State_Ball[0], 2, 1, SBE_YTRANS, SBE_ZTRANS, SBE_XTRANS );
		}

		else if ( CheckValue ( YTra, XTra, ZTra ) ) {
			Set ( &m_bCurrent_State_Ball[0], 2, 1, SBE_XTRANS, SBE_ZTRANS, SBE_YTRANS );
		}

		else if ( CheckValue ( ZTra, XTra, YTra ) ) {
			Set ( &m_bCurrent_State_Ball[0], 2, 1, SBE_XTRANS, SBE_YTRANS, SBE_ZTRANS );
		}

		else {
			Set ( &m_bCurrent_State_Ball[0], 3, 0, SBE_XTRANS, SBE_YTRANS, SBE_ZTRANS );
		}

		if ( CheckValue ( XRot, YRot, ZRot ) ) {
			Set ( &m_bCurrent_State_Ball[0], 2, 1, SBE_YROT, SBE_ZROT, SBE_XROT );
		}

		else if ( CheckValue ( YRot, XRot, ZRot ) ) {
			Set ( &m_bCurrent_State_Ball[0], 2, 1, SBE_XROT, SBE_ZROT, SBE_YROT );
		}

		else if ( CheckValue ( ZRot, XRot, YRot ) ) {
			Set ( &m_bCurrent_State_Ball[0], 2, 1, SBE_XROT, SBE_YROT, SBE_ZROT );
		}

		else {
			Set ( &m_bCurrent_State_Ball[0], 3, 0, SBE_XROT, SBE_YROT, SBE_ZROT );
		}
	}

	else {
		m_bCurrent_State_Ball[SBE_XTRANS] = XTra > 0 ? true : false;
		m_bCurrent_State_Ball[SBE_YTRANS] = YTra > 0 ? true : false;
		m_bCurrent_State_Ball[SBE_ZTRANS] = ZTra > 0 ? true : false;

		if ( CheckValue ( XRot, YRot, ZRot ) ) {
			Set ( &m_bCurrent_State_Ball[0], 2, 1, SBE_YROT, SBE_ZROT, SBE_XROT );
		}

		else if ( CheckValue ( YRot, XRot, ZRot ) ) {
			Set ( &m_bCurrent_State_Ball[0], 2, 1, SBE_XROT, SBE_ZROT, SBE_YROT );
		}

		else if ( CheckValue ( ZRot, XRot, YRot ) ) {
			Set ( &m_bCurrent_State_Ball[0], 2, 1, SBE_XROT, SBE_YROT, SBE_ZROT );
		}

		else {
			Set ( &m_bCurrent_State_Ball[0], 3, 0, SBE_XROT, SBE_YROT, SBE_ZROT );
		}
	}
}

void CSBWAppDlg::SetCtrl ( bool bPulse, bool bPreviousState, bool bState, CButton *pCtrlObj )
{
	if ( ( ! ( bPreviousState && bPulse ) ) && bState ) {
		pCtrlObj->SetCheck ( BST_CHECKED );
	}

	else {
		pCtrlObj->SetCheck ( BST_UNCHECKED );
	}
}

void CSBWAppDlg::BallState ( bool bCheckZeroBallState )
{
	int Idx[] = { SBE_XTRANS, SBE_YTRANS, SBE_ZTRANS, SBE_XROT, SBE_YROT, SBE_ZROT };
	CButton *Ctrls[] = { &m_ctrlXLabel, &m_ctrlYLabel, &m_ctrlZLabel, &m_ctrlXRotLabel, &m_ctrlYRotLabel, &m_ctrlZRotLabel };

	if ( m_ctrlMovAverage.GetCheck ( ) == BST_CHECKED ) {

		bool bPulse = m_ctrlPulse.GetCheck ( ) == BST_CHECKED ? true : false;

		FinalBallState ( bCheckZeroBallState );

		for ( int i = 0; i < sizeof ( Idx ) / sizeof ( int ); i++ ) {
			SetCtrl ( bPulse, m_bPrevious_Final_State_Ball[Idx[i]], m_bFinal_State_Ball[Idx[i]], Ctrls[i] );
		}
	}

	else {
		for ( int i = 0; i < sizeof ( Idx ) / sizeof ( int ); i++ ) {
			SetCtrl ( false, false, m_bCurrent_State_Ball[Idx[i]], Ctrls[i] );
		}
	}
}

void CSBWAppDlg::FillArray ( /*double dValue, */int iMov )
{
	m_clCriSec.Lock ( );

	int iEnd = m_bMoving_State_Ball2[ iMov ].size ( ) - m_ctrlNLength.GetPos ( );
	iEnd = iEnd < 0 ? 0 : iEnd;
	m_bMoving_State_Ball2[iMov].erase ( m_bMoving_State_Ball2[iMov].begin ( ), m_bMoving_State_Ball2[iMov].begin ( ) + iEnd );
	m_bMoving_State_Ball2[iMov].insert ( m_bMoving_State_Ball2[iMov].end ( ), m_bCurrent_State_Ball[iMov] ? 1 : 0 );

	m_clCriSec.Unlock ( );
}

VOID CALLBACK TimerRoutine ( PVOID lpParam, BOOLEAN TimerOrWaitFired )
{
	UNREFERENCED_PARAMETER ( TimerOrWaitFired );

	bool bUpdate = false;
	CSBWAppDlg::_sTimerQueue *pObj = ( CSBWAppDlg::_sTimerQueue *) lpParam;

	if ( pObj == NULL ) {
		return;
	}

	pObj->pThis->m_clCriSec.Lock ( );

	if ( !pObj->pThis->m_bCurrent_State_Ball[pObj->iMov] ) {
		pObj->pThis->m_bMoving_State_Ball2[pObj->iMov].clear ( );
		pObj->pThis->m_bMoving_State_Ball2[pObj->iMov].insert (pObj->pThis->m_bMoving_State_Ball2[pObj->iMov].end ( ), 0 );
		bUpdate = true;
	}

	if ( pObj->hTimer != NULL ) {
		DeleteTimerQueueTimer ( pObj->hTimerQueue, pObj->hTimer, NULL );
	}

	pObj->pThis->m_clCriSec.Unlock ( );

	if ( bUpdate ) {
		pObj->pThis->BallState ( false );
	}

	pObj->pThis->m_bNotAllowNewTimer[pObj->iMov] = false;

	delete pObj;
}

void CSBWAppDlg::CheckZeroBallState ( /*double dValue*/ )
{
	for ( int iMov = 0; iMov < 6; iMov++ ) {

		FillArray (/* dValue,*/ iMov );

		if ( !m_bNotAllowNewTimer[iMov] )
			if ( !m_bCurrent_State_Ball[iMov] ) {

				_sTimerQueue *psTimerQueue = new _sTimerQueue ( );

				psTimerQueue->pThis       = this;
				psTimerQueue->iMov        = iMov;
				psTimerQueue->hTimer      = NULL;
				psTimerQueue->hTimerQueue = m_hTimerQueue;

				if ( m_hTimerQueue != NULL ) {
					if ( CreateTimerQueueTimer ( & ( psTimerQueue->hTimer ),
												 m_hTimerQueue,
												 ( WAITORTIMERCALLBACK ) TimerRoutine,
												 psTimerQueue,
												 (int) m_ctrlTimValue.GetIValue ( ), //m_iPeriod,
												 0, WT_EXECUTEONLYONCE ) != 0 ) {
						m_bNotAllowNewTimer[iMov] = true;
					}
				}
			}
	}
}

int CSBWAppDlg::Sum32 ( vector <BYTE> &v )
{
	int sum_of_elems = 0;

	for ( vector<BYTE>::iterator j = v.begin ( ); j != v.end ( ); ++j ) {
		sum_of_elems += *j;
	}

	return sum_of_elems;
}

void CSBWAppDlg::FinalBallState ( bool bCheckZeroBallState )
{
	float fValues[6];
	double dValue = m_dSMAThres;
	int Idx[] = { SBE_XTRANS, SBE_YTRANS, SBE_ZTRANS, SBE_XROT, SBE_YROT, SBE_ZROT };


	if ( bCheckZeroBallState ) {
		CheckZeroBallState ( /*dValue*/ );
	}

	m_clCriSec.Lock ( );

	for ( int i = 0; i < sizeof ( Idx ) / sizeof ( int ); i++ ) {
		fValues[Idx[i]] = ( (float) Sum32 ( m_bMoving_State_Ball2[Idx[i]] ) ) /
						  ( (float) max ( 1, m_bMoving_State_Ball2[Idx[i]].size ( ) ) );
	}

	m_clCriSec.Unlock ( );

	for ( int i = 0; i < sizeof ( Idx ) / sizeof ( int ); i++ ) {
		m_bPrevious_Final_State_Ball[Idx[i]] = m_bFinal_State_Ball[Idx[i]];
	}

	if ( m_iDoF == 0 ) {
		if ( CheckValue ( SBE_XTRANS, 6, &fValues[0] ) ) {
			m_bFinal_State_Ball[SBE_XTRANS] = fValues[SBE_XTRANS] > dValue ? true : false;
			Set ( &m_bFinal_State_Ball[0], 5, 0, SBE_YTRANS, SBE_ZTRANS, SBE_XROT, SBE_YROT, SBE_ZROT );
		}

		else if ( CheckValue ( SBE_YTRANS, 6, &fValues[0] ) ) {
			m_bFinal_State_Ball[SBE_YTRANS] = fValues[SBE_YTRANS] > dValue ? true : false;
			Set ( &m_bFinal_State_Ball[0], 5, 0, SBE_XTRANS, SBE_ZTRANS, SBE_XROT, SBE_YROT, SBE_ZROT );
		}

		else if ( CheckValue ( SBE_ZTRANS, 6, &fValues[0] ) ) {
			m_bFinal_State_Ball[SBE_ZTRANS] = fValues[SBE_ZTRANS] > dValue ? true : false;
			Set ( &m_bFinal_State_Ball[0], 5, 0, SBE_XTRANS, SBE_YTRANS, SBE_XROT, SBE_YROT, SBE_ZROT );
		}

		else if ( CheckValue ( SBE_XROT, 6, &fValues[0] ) ) {
			m_bFinal_State_Ball[SBE_XROT] = fValues[SBE_XROT] > dValue ? true : false;
			Set ( &m_bFinal_State_Ball[0], 5, 0, SBE_XTRANS, SBE_YTRANS, SBE_ZTRANS, SBE_YROT, SBE_ZROT );
		}

		else if ( CheckValue ( SBE_YROT, 6, &fValues[0] ) ) {
			m_bFinal_State_Ball[SBE_YROT] = fValues[SBE_YROT] > dValue ? true : false;
			Set ( &m_bFinal_State_Ball[0], 5, 0, SBE_XTRANS, SBE_YTRANS, SBE_ZTRANS, SBE_XROT, SBE_ZROT );
		}

		else if ( CheckValue ( SBE_ZROT, 6, &fValues[0] ) ) {
			m_bFinal_State_Ball[SBE_ZROT] = fValues[SBE_ZROT] > dValue ? true : false;
			Set ( &m_bFinal_State_Ball[0], 5, 0, SBE_XTRANS, SBE_YTRANS, SBE_ZTRANS, SBE_XROT, SBE_YROT );
		}

		else {
			Set ( &m_bFinal_State_Ball[0], 6, 0, SBE_XTRANS, SBE_YTRANS, SBE_ZTRANS, SBE_XROT, SBE_YROT, SBE_ZROT );
		}
	}

	else if ( m_iDoF == 1 ) {
		if ( CheckValue ( SBE_XTRANS, 3, &fValues[0] ) ) {
			m_bFinal_State_Ball[SBE_XTRANS] = fValues[SBE_XTRANS] > dValue ? true : false;
			Set ( &m_bFinal_State_Ball[0], 2, 0, SBE_YTRANS, SBE_ZTRANS );
		}

		else if ( CheckValue ( SBE_YTRANS, 3, &fValues[0] ) ) {
			m_bFinal_State_Ball[SBE_YTRANS] = fValues[SBE_YTRANS] > dValue ? true : false;
			Set ( &m_bFinal_State_Ball[0], 2, 0, SBE_XTRANS, SBE_ZTRANS );
		}

		else if ( CheckValue ( SBE_ZTRANS, 3, &fValues[0] ) ) {
			m_bFinal_State_Ball[SBE_ZTRANS] = fValues[SBE_ZTRANS] > dValue ? true : false;
			Set ( &m_bFinal_State_Ball[0], 2, 0, SBE_XTRANS, SBE_YTRANS );
		}

		else {
			Set ( &m_bFinal_State_Ball[0], 3, 0, SBE_XTRANS, SBE_YTRANS, SBE_ZTRANS );
		}

		if ( CheckValue ( SBE_XROT - 3, 3, &fValues[3] ) ) {
			m_bFinal_State_Ball[SBE_XROT] = fValues[SBE_XROT] > dValue ? true : false;
			Set ( &m_bFinal_State_Ball[0], 2, 0, SBE_YROT, SBE_ZROT );
		}

		else if ( CheckValue ( SBE_YROT - 3, 3, &fValues[3] ) ) {
			m_bFinal_State_Ball[SBE_YROT] = fValues[SBE_YROT] > dValue ? true : false;
			Set ( &m_bFinal_State_Ball[0], 2, 0, SBE_XROT, SBE_ZROT );
		}

		else if ( CheckValue ( SBE_ZROT - 3, 3, &fValues[3] ) ) {
			m_bFinal_State_Ball[SBE_ZROT] = fValues[SBE_ZROT] > dValue ? true : false;
			Set ( &m_bFinal_State_Ball[0], 2, 0, SBE_XROT, SBE_YROT );
		}

		else {
			Set ( &m_bFinal_State_Ball[0], 3, 0, SBE_XROT, SBE_YROT, SBE_ZROT );
		}
	}

	else {
		m_bFinal_State_Ball[SBE_XTRANS] = fValues[SBE_XTRANS] > dValue ? true : false;
		m_bFinal_State_Ball[SBE_YTRANS] = fValues[SBE_YTRANS] > dValue ? true : false;
		m_bFinal_State_Ball[SBE_ZTRANS] = fValues[SBE_ZTRANS] > dValue ? true : false;

		if ( CheckValue ( SBE_XROT - 3, 3, &fValues[3] ) ) {
			m_bFinal_State_Ball[SBE_XROT] = fValues[SBE_XROT] > dValue ? true : false;
			Set ( &m_bFinal_State_Ball[0], 2, 0, SBE_YROT, SBE_ZROT );
		}

		else if ( CheckValue ( SBE_YROT - 3, 3, &fValues[3] ) ) {
			m_bFinal_State_Ball[SBE_YROT] = fValues[SBE_YROT] > dValue ? true : false;
			Set ( &m_bFinal_State_Ball[0], 2, 0, SBE_XROT, SBE_ZROT );
		}

		else if ( CheckValue ( SBE_ZROT - 3, 3, &fValues[3] ) ) {
			m_bFinal_State_Ball[SBE_ZROT] = fValues[SBE_ZROT] > dValue ? true : false;
			Set ( &m_bFinal_State_Ball[0], 2, 0, SBE_XROT, SBE_YROT );
		}

		else {
			Set ( &m_bFinal_State_Ball[0], 3, 0, SBE_XROT, SBE_YROT, SBE_ZROT );
		}
	}
}

bool CSBWAppDlg::GetState ( bool bMovAver, bool bPulse, int iMov )
{
	if ( bMovAver ) {
		if ( ( ! ( m_bPrevious_Final_State_Ball[iMov] && bPulse ) ) && m_bFinal_State_Ball[iMov] ) {
			return true;
		}

		return false;
	}

	return m_bCurrent_State_Ball[iMov];
}

LRESULT CSBWAppDlg::SendBallKeystrokes ( WPARAM queryitem )
{
	bool bPulse = m_ctrlPulse.GetCheck ( ) == BST_CHECKED ? true : false;
	bool bMovAver = m_ctrlMovAverage.GetCheck ( ) == BST_CHECKED ? true : false;

	WPARAM wParam = 0;
	WPARAM iTMag  = 0, iRMag = 0, iTDivis = 0, iRDivis = 0;

	if ( queryitem & ( SBE_RIGHT | SBE_LEFT ) ) {
		if ( GetState ( bMovAver, bPulse, SBE_XTRANS ) ) {
			m_bPrevious_Final_State_Ball[SBE_XTRANS] = m_bFinal_State_Ball[SBE_XTRANS];
			iTMag += abs ( COORD->sCurrent_XTrans );
			iTDivis++;

			if ( COORD->sCurrent_XTrans > 0 ) {
				wParam |= SBE_RIGHT;
			}

			else {
				wParam |= SBE_LEFT;
			}
		}
	}

	if ( queryitem & ( SBE_FORWARD | SBE_BACK ) ) {
		if ( GetState ( bMovAver, bPulse, SBE_YTRANS ) ) {
			m_bPrevious_Final_State_Ball[SBE_YTRANS] = m_bFinal_State_Ball[SBE_YTRANS];
			iTMag += abs ( COORD->sCurrent_YTrans );
			iTDivis++;

			if ( COORD->sCurrent_YTrans > 0 ) {
				wParam |= SBE_FORWARD;
			}

			else {
				wParam |= SBE_BACK;
			}
		}
	}

	if ( queryitem & ( SBE_UP | SBE_DOWN ) ) {
		if ( GetState ( bMovAver, bPulse, SBE_ZTRANS ) ) {
			m_bPrevious_Final_State_Ball[SBE_ZTRANS] = m_bFinal_State_Ball[SBE_ZTRANS];
			iTMag += abs ( COORD->sCurrent_ZTrans );
			iTDivis++;

			if ( COORD->sCurrent_ZTrans > 0 ) {
				wParam |= SBE_UP;
			}

			else {
				wParam |= SBE_DOWN;
			}
		}
	}

	if ( queryitem & ( SBE_XROT_1 | SBE_XROT_2 ) ) {
		if ( GetState ( bMovAver, bPulse, SBE_XROT ) ) {
			m_bPrevious_Final_State_Ball[SBE_XROT] = m_bFinal_State_Ball[SBE_XROT];
			iRMag += abs ( COORD->sCurrent_XRot );
			iRDivis++;

			if ( COORD->sCurrent_XRot > 0 ) {
				wParam |= SBE_XROT_1;
			}

			else {
				wParam |= SBE_XROT_2;
			}
		}
	}

	if ( queryitem & ( SBE_YROT_1 | SBE_YROT_2 ) ) {
		if ( GetState ( bMovAver, bPulse, SBE_YROT ) ) {
			m_bPrevious_Final_State_Ball[SBE_YROT] = m_bFinal_State_Ball[SBE_YROT];
			iRMag += abs ( COORD->sCurrent_YRot );
			iRDivis++;

			if ( COORD->sCurrent_YRot > 0 ) {
				wParam |= SBE_YROT_1;
			}

			else {
				wParam |= SBE_YROT_2;
			}
		}
	}

	if ( queryitem & ( SBE_ZROT_1 | SBE_ZROT_2 ) ) {
		if ( GetState ( bMovAver, bPulse, SBE_ZROT ) ) {
			m_bPrevious_Final_State_Ball[SBE_ZROT] = m_bFinal_State_Ball[SBE_ZROT];
			iRMag += abs ( COORD->sCurrent_YRot );
			iRDivis++;

			if ( COORD->sCurrent_ZRot > 0 ) {
				wParam |= SBE_ZROT_1;
			}

			else {
				wParam |= SBE_ZROT_2;
			}
		}
	}

	iTMag = iTMag / max ( 1, iTDivis );
	iTMag = ( iTMag << 6 ) & 0x7FC0;
	iRMag = iRMag / max ( 1, iRDivis );
	iRMag = ( iRMag << 22 ) & 0x7FC00000;
	wParam |= iTMag;
	wParam |= iRMag;

	if ( queryitem == -1 ) {
		if ( wParam != 0 ) {
			LPARAM lParam = ( LPARAM )this->m_hWnd;

			if ( ( IsWindow ( m_hTargetWindow ) == TRUE ) && ( m_ctrlBroadcast.GetCheck ( ) == BST_UNCHECKED ) ) {
				::SendMessage ( m_hTargetWindow, WM_SBEXPLORER, wParam, lParam );
				m_bCanNewWindow = true;
			}

			else if ( m_ctrlBroadcast.GetCheck ( ) == BST_CHECKED ) {
				::SendMessage ( HWND_BROADCAST, WM_SBEXPLORER, wParam, lParam );
				m_bCanNewWindow = true;
			}

			else {
				if ( m_bCanNewWindow ) {
					m_bCanNewWindow = false;
					MessageBox ( m_clString[IDS_INVWIN], m_clString[IDS_ERROR2], MB_OK );
					m_bCanNewWindow = true;
				}
			}
		}
	}

	return (LRESULT) wParam;
}

void CSBWAppDlg::OnClearText ( )
{
	m_SBW.m_clRAWData.clear();
	m_ctrlHexData.SetWindowText ( m_clString[0] );
	m_ctrlASCIIData.SetWindowText ( m_clString[0] );
	m_ctrlCmdList.SetWindowText ( m_clString[0] );
}

void CSBWAppDlg::OnAddCMDs ( )
{
	CString Temp;
	vector <BYTE>  Arr2;
	_stUser stUser = { 0 };
	SBW::_stProperties stProp = { 0 };
	Translate ( true, stProp, stUser );
	m_SBW.EncodeCommands ( stProp, Arr2, m_ctrlAddCR.GetCheck ( ) == BST_CHECKED ? true : false );

	if ( m_ctrlAddByte.GetCheck ( ) == BST_CHECKED ) {
		TCHAR *stopstring;
		m_ctrlByteValue.GetWindowText ( Temp );

		if ( !Temp.IsEmpty ( ) ) {
			long lVal = _tcstol ( Temp.GetBuffer ( ), &stopstring,
								  ( ( Temp.Left ( 2 ).CompareNoCase ( m_clString[IDS_HEXPREFIX4] ) == 0 ) ? 16 : 10 ) );
			lVal = min ( lVal, 255 );
			lVal = max ( lVal, 0 );
			m_SBW.Add ( Arr2, (BYTE *) &lVal, sizeof ( BYTE ) );

			if ( m_ctrlAddCR.GetCheck ( ) == BST_CHECKED ) {
				m_SBW.StringA ( string ( "\r" ), Arr2, true );
			}
		}
	}

	if ( Arr2.size( ) > 0 ) {
		m_SBW.AddCMDs ( Arr2 );
		m_SBW.GetHexCMDs ( Temp );
		m_ctrlCmd.SetWindowText ( Temp );
	}

	Temp.Format ( _T ( "%d" ), m_SBW.iCMDsCounter );
	m_ctrlSize.SetWindowText ( Temp );
}

void CSBWAppDlg::OnClearAll ( )
{
	m_SBW.ClearCMDs();
	m_ctrlSize.SetWindowText ( _T("0") );
	m_ctrlCmd.SetWindowText ( m_clString[0] );
}

void CSBWAppDlg::OnSetDevice ( )
{
	m_SBW.SendCMDs ( );
}

void CSBWAppDlg::Translate ( bool bDirection, SBW::_stProperties &stProp, _stUser &stUser )
{
	__int64 iVal;
	CString Temp;
	COleVariant pVar;

	if ( bDirection ) {
		CButton *pBtn = (CButton *) GetDlgItem ( IDC_1DOF );

		if ( pBtn ) {
			if ( pBtn->GetCheck ( ) == BST_CHECKED ) {
				stUser.Dominance.cMode = 1;
			}
		}

		pBtn = (CButton *) GetDlgItem ( IDC_2DOF );

		if ( pBtn ) {
			if ( pBtn->GetCheck ( ) == BST_CHECKED ) {
				stUser.Dominance.cMode = 2;
			}
		}

		pBtn = (CButton *) GetDlgItem ( IDC_4DOF );

		if ( pBtn ) {
			if ( pBtn->GetCheck ( ) == BST_CHECKED ) {
				stUser.Dominance.cMode = 4;
			}
		}

		pBtn = (CButton *) GetDlgItem ( IDC_TRANSLATION );

		if ( pBtn ) {
			if ( pBtn->GetCheck ( ) == BST_CHECKED ) {
				stUser.Operation.cMode = 1;
			}
		}

		pBtn = (CButton *) GetDlgItem ( IDC_ROTATION );

		if ( pBtn ) {
			if ( pBtn->GetCheck ( ) == BST_CHECKED ) {
				stUser.Operation.cMode = 2;
			}
		}

		pBtn = (CButton *) GetDlgItem ( IDC_BOTH );

		if ( pBtn ) {
			if ( pBtn->GetCheck ( ) == BST_CHECKED ) {
				stUser.Operation.cMode = 3;
			}
		}

		pBtn = (CButton *) GetDlgItem ( IDC_PULSE );

		if ( pBtn ) {
			stUser.Operation.bPulse = pBtn->GetCheck ( ) == BST_CHECKED;
		}

		stUser.MovingAverage.bEnable = m_ctrlMovAverage.GetCheck ( ) == BST_CHECKED;
		stUser.MovingAverage.iLength = m_ctrlNLength.GetPos ( );
		stUser.MovingAverage.iPeriod = (int) m_ctrlTimValue.GetIValue ( );

		stUser.Threshold.sX = m_clThreshold[ XTRA ];
		stUser.Threshold.sY = m_clThreshold[ YTRA ];
		stUser.Threshold.sZ = m_clThreshold[ ZTRA ];
		stUser.Threshold.sRX = m_clThreshold[ XROT ];
		stUser.Threshold.sRY = m_clThreshold[ YROT ];
		stUser.Threshold.sRZ = m_clThreshold[ ZROT ];
		stUser.Operation.dFreq = m_ctrlFreq.GetDValue ( );
		
		//
		stProp.dwSize = sizeof ( SBW::_stProperties );
		//
		stProp.Threshold.bEnable = !m_clCtrlItem[ IDX_THRE ]->Unchecked ( );
		stProp.Threshold.cValue = (BYTE) m_clCtrlItem[ IDX_THRE ]->GetInt ( ) & 0xFFLL;
		//
		stProp.TransSensitivities.bEnable = !m_clCtrlItem[ IDX_TENS ]->Unchecked ( );
		iVal = m_clCtrlItem[ IDX_TENS ]->GetInt ( ) & -1LL;
		stProp.TransSensitivities.sValue[ 2 ] = iVal & 0xFFFF;
		stProp.TransSensitivities.sValue[ 1 ] = ( iVal >> 16 ) & 0xFFFF;
		stProp.TransSensitivities.sValue[ 0 ] = ( iVal >> 32 ) & 0xFFFF;
		// Responsiveness
		stProp.Responsiveness.bEnable = !m_clCtrlItem[ IDX_RESS ]->Unchecked ( );
		stProp.Responsiveness.sMaximum = (unsigned short) m_clCtrlItem[ IDX_RMAX ]->GetInt ( ) & 0xFFFF;
		// Responsiveness - Minimum
		stProp.Responsiveness.Minimum.bEnable = !m_clCtrlItem[ IDX_RMIN ]->Unchecked ( );
		stProp.Responsiveness.Minimum.sValue = (unsigned short) m_clCtrlItem[ IDX_RMIN ]->GetInt ( ) & 0xFFFF;
		// ResponMultiplier
		// ResponMultiplier - Translation
		stProp.ResponMultiplier.Translation.bEnable = !m_clCtrlItem[ IDX_RENS ]->Unchecked ( );
		stProp.ResponMultiplier.Translation.cValue = (BYTE) m_clCtrlItem[ IDX_RENS ]->GetInt ( ) & 0xFF;
		// ResponMultiplier - Rotation
		stProp.ResponMultiplier.Rotation.bEnable = !m_clCtrlItem[ IDX_REOT ]->Unchecked ( );
		stProp.ResponMultiplier.Rotation.cValue = (BYTE) m_clCtrlItem[ IDX_REOT ]->GetInt ( ) & 0xFF;
		// SpinRate
		stProp.SpinRate.bEnable = !m_clCtrlItem[ IDX_SPRT ]->Unchecked ( );
		stProp.SpinRate.cMantissa = (BYTE) m_clCtrlItem[ IDX_SPAN ]->GetInt ( ) & 0xFF;
		stProp.SpinRate.cExponent = (BYTE) m_clCtrlItem[ IDX_SPXP ]->GetInt ( ) & 0xFF;
		// TranslationMode
		stProp.TranslationMode.bEnable = !m_clCtrlItem[ IDX_TRMD ]->Unchecked ( );
		Temp = m_clCtrlItem[ IDX_TRSY ]->GetValue ( );

		if ( Temp.Compare ( m_clString[ IDS_PARENT ] ) == 0 ) {
			stProp.TranslationMode.cBallSystem = 'P';
		}

		else if ( Temp.Compare ( m_clString[ IDS_LOCAL ] ) == 0 ) {
			stProp.TranslationMode.cBallSystem = 'L';
		}

		else {
			stProp.TranslationMode.cBallSystem = 'X';
		}

		Temp = m_clCtrlItem[ IDX_TRCT ]->GetValue ( );

		if ( Temp.Compare ( m_clString[ IDS_PARENT ] ) == 0 ) {
			stProp.TranslationMode.cFreedomVector = 'P';
		}

		else if ( Temp.Compare ( m_clString[ IDS_LOCAL ] ) == 0 ) {
			stProp.TranslationMode.cFreedomVector = 'L';
		}

		else {
			stProp.TranslationMode.cFreedomVector = 'X';
		}

		Temp = m_clCtrlItem[ IDX_TROU ]->GetValue ( );

		if ( Temp.Compare ( m_clString[ IDS_PARENT ] ) == 0 ) {
			stProp.TranslationMode.cOutput = 'P';
		}

		else if ( Temp.Compare ( m_clString[ IDS_LOCAL ] ) == 0 ) {
			stProp.TranslationMode.cOutput = 'L';
		}

		else {
			stProp.TranslationMode.cOutput = 'X';
		}

		stProp.TranslationMode.Vector.bEnable = !m_clCtrlItem[ IDX_TRVE ]->Unchecked ( );
		iVal = m_clCtrlItem[ IDX_TRVE ]->GetInt ( ) & -1LL;
		stProp.TranslationMode.Vector.sValue[ 2 ] = iVal & 0xFFFF;
		stProp.TranslationMode.Vector.sValue[ 1 ] = ( iVal >> 16 ) & 0xFFFF;
		stProp.TranslationMode.Vector.sValue[ 0 ] = ( iVal >> 32 ) & 0xFFFF;
		// RotationMode
		stProp.RotationMode.bEnable = !m_clCtrlItem[ IDX_RODE ]->Unchecked ( );
		Temp = m_clCtrlItem[ IDX_RSYS ]->GetValue ( );

		if ( Temp.Compare ( m_clString[ IDS_PARENT ] ) == 0 ) {
			stProp.RotationMode.cBallSystem = 'P';
		}

		else if ( Temp.Compare ( m_clString[ IDS_LOCAL ] ) == 0 ) {
			stProp.RotationMode.cBallSystem = 'L';
		}

		else {
			stProp.RotationMode.cBallSystem = 'X';
		}

		Temp = m_clCtrlItem[ IDX_RFVE ]->GetValue ( );

		if ( Temp.Compare ( m_clString[ IDS_PARENT ] ) == 0 ) {
			stProp.RotationMode.cFreedomVector = 'P';
		}

		else if ( Temp.Compare ( m_clString[ IDS_LOCAL ] ) == 0 ) {
			stProp.RotationMode.cFreedomVector = 'L';
		}

		else {
			stProp.RotationMode.cFreedomVector = 'X';
		}

		Temp = m_clCtrlItem[ IDX_ROUT ]->GetValue ( );

		if ( Temp.Compare ( m_clString[ IDS_PARENT ] ) == 0 ) {
			stProp.RotationMode.cOutput = 'P';
		}

		else if ( Temp.Compare ( m_clString[ IDS_LOCAL ] ) == 0 ) {
			stProp.RotationMode.cOutput = 'L';
		}

		else {
			stProp.RotationMode.cOutput = 'X';
		}

		stProp.RotationMode.Vector.bEnable = !m_clCtrlItem[ IDX_RVEC ]->Unchecked ( );
		iVal = m_clCtrlItem[ IDX_RVEC ]->GetInt ( ) & -1LL;
		stProp.RotationMode.Vector.sValue[ 2 ] = iVal & 0xFFFF;
		stProp.RotationMode.Vector.sValue[ 1 ] = ( iVal >> 16 ) & 0xFFFF;
		stProp.RotationMode.Vector.sValue[ 0 ] = ( iVal >> 32 ) & 0xFFFF;
		//
		stProp.Mode.bEnable = !m_clCtrlItem[ IDX_MODE ]->Unchecked ( );
		Temp = m_clCtrlItem[ IDX_TRAF ]->GetValue ( );

		if ( ( Temp.Compare ( m_clString[ IDS_DONOTCHANGE ] ) == 0 ) || ( Temp.IsEmpty ( ) ) ) {
			stProp.Mode.cTranslationFreedom = 'X';
		}

		else {
			stProp.Mode.cTranslationFreedom = CT2A ( Temp.GetBuffer ( ) )[ 0 ];
		}

		stProp.Mode.Rotation.bEnable = !m_clCtrlItem[ IDX_ROTA ]->Unchecked ( );
		Temp = m_clCtrlItem[ IDX_ROTF ]->GetValue ( );

		if ( ( Temp.Compare ( m_clString[ IDS_DONOTCHANGE ] ) == 0 ) || ( Temp.IsEmpty ( ) ) ) {
			stProp.Mode.Rotation.cRotationFreedom = 'X';
		}

		else {
			stProp.Mode.Rotation.cRotationFreedom = CT2A ( Temp.GetBuffer ( ) )[ 0 ];
		}

		stProp.Mode.Rotation.DataForm.bEnable = !m_clCtrlItem[ IDX_RFOR ]->Unchecked ( );
		Temp = m_clCtrlItem[ IDX_ROTY ]->GetValue ( );

		if ( ( Temp.Compare ( m_clString[ IDS_DONOTCHANGE ] ) == 0 ) || ( Temp.IsEmpty ( ) ) ) {
			stProp.Mode.Rotation.DataForm.cDataType = 'X';
		}

		else {
			stProp.Mode.Rotation.DataForm.cDataType = CT2A ( Temp.GetBuffer ( ) )[ 0 ];
		}

		stProp.Mode.Rotation.DataForm.Handedness.bEnable = !m_clCtrlItem[ IDX_RHAN ]->Unchecked ( );
		stProp.Mode.Rotation.DataForm.Handedness.bLeftHanded = m_clCtrlItem[ IDX_LFTH ]->GetBool ( );
		stProp.Mode.Rotation.DataForm.Handedness.PrePostProc.bEnable = !m_clCtrlItem[ IDX_RPRP ]->Unchecked ( );
		Temp = m_clCtrlItem[ IDX_RPPO ]->GetValue ( );

		if ( Temp.Compare ( m_clString[ IDS_POST ] ) == 0 ) {
			stProp.Mode.Rotation.DataForm.Handedness.PrePostProc.cValue = 'A';
		}

		else {
			stProp.Mode.Rotation.DataForm.Handedness.PrePostProc.cValue = 'B';
		}

		stProp.Zero.bEnable = !m_clCtrlItem[ IDX_ZERO ]->Unchecked ( );
		stProp.AbsoluteRotMatrix.bEnable = !m_clCtrlItem[ IDX_ABMX ]->Unchecked ( );
		iVal = m_clCtrlItem[ IDX_ABMX ]->GetInt ( ) & -1LL;
		stProp.AbsoluteRotMatrix.sValue[ 2 ] = iVal & 0xFFFF;
		stProp.AbsoluteRotMatrix.sValue[ 1 ] = ( iVal >> 16 ) & 0xFFFF;
		stProp.AbsoluteRotMatrix.sValue[ 0 ] = ( iVal >> 32 ) & 0xFFFF;
		stProp.OrientationMatrix.bEnable = !m_clCtrlItem[ IDX_ORIE ]->Unchecked ( );
		iVal = m_clCtrlItem[ IDX_ORIE ]->GetInt ( ) & -1LL;
		stProp.OrientationMatrix.sValue[ 2 ] = iVal & 0xFFFF;
		stProp.OrientationMatrix.sValue[ 1 ] = ( iVal >> 16 ) & 0xFFFF;
		stProp.OrientationMatrix.sValue[ 0 ] = ( iVal >> 32 ) & 0xFFFF;
		// Communication mode
		stProp.CommunicationMode.bEnable = !m_clCtrlItem[ IDX_MODP ]->Unchecked ( );
		Temp = m_clCtrlItem[ IDX_MODP ]->GetValue ( );

		if ( Temp.Compare ( m_clString[ IDS_BINARY ] ) == 0 ) {
			stProp.CommunicationMode.cValue = 'B';
		}

		else {
			stProp.CommunicationMode.cValue = 'P';
		}

		//
		//IDX_BEEP
		//IDX_LINS
		//
	}

	else {
		CButton *pBtn = (CButton *) GetDlgItem ( IDC_1DOF );

		if ( pBtn ) {
			if ( stUser.Dominance.cMode == 1 ) {
				pBtn->SetCheck ( BST_CHECKED );
			}

			else {
				pBtn->SetCheck ( BST_UNCHECKED );
			}
		}

		pBtn = (CButton *) GetDlgItem ( IDC_2DOF );

		if ( pBtn ) {
			if ( stUser.Dominance.cMode == 2 ) {
				pBtn->SetCheck ( BST_CHECKED );
			}

			else {
				pBtn->SetCheck ( BST_UNCHECKED );
			}
		}

		pBtn = (CButton *) GetDlgItem ( IDC_4DOF );

		if ( pBtn ) {
			if ( stUser.Dominance.cMode == 4 ) {
				pBtn->SetCheck ( BST_CHECKED );
			}

			else {
				pBtn->SetCheck ( BST_UNCHECKED );
			}
		}

		pBtn = (CButton *) GetDlgItem ( IDC_TRANSLATION );

		if ( pBtn ) {
			if ( stUser.Operation.cMode == 1 ) {
				pBtn->SetCheck ( BST_CHECKED );
			}

			else {
				pBtn->SetCheck ( BST_UNCHECKED );
			}
		}

		pBtn = (CButton *) GetDlgItem ( IDC_ROTATION );

		if ( pBtn ) {
			if ( stUser.Operation.cMode == 2 ) {
				pBtn->SetCheck ( BST_CHECKED );
			}

			else {
				pBtn->SetCheck ( BST_UNCHECKED );
			}
		}

		pBtn = (CButton *) GetDlgItem ( IDC_BOTH );

		if ( pBtn ) {
			if ( stUser.Operation.cMode == 3 ) {
				pBtn->SetCheck ( BST_CHECKED );
			}

			else {
				pBtn->SetCheck ( BST_UNCHECKED );
			}
		}

		pBtn = (CButton *) GetDlgItem ( IDC_PULSE );

		if ( pBtn ) {
			pBtn->SetCheck ( (stUser.Operation.bPulse ? BST_CHECKED : BST_UNCHECKED) );
		}

		m_ctrlMovAverage.SetCheck ( ( stUser.MovingAverage.bEnable ? BST_CHECKED : BST_UNCHECKED ) );

		if ( stUser.MovingAverage.bEnable ) {
			m_ctrlSMAThres.EnableWindow ( );
			m_ctrlTimValue.EnableWindow ( );
		}

		else {
			m_ctrlSMAThres.EnableWindow ( FALSE );
			m_ctrlTimValue.EnableWindow ( FALSE );
		}

		m_ctrlNLength.SetPos (stUser.MovingAverage.iLength);
		m_ctrlTimValue.SetValue ( stUser.MovingAverage.iPeriod, 0 );

		m_clThreshold[ XTRA ] = stUser.Threshold.sX;
		m_clThreshold[ YTRA ] = stUser.Threshold.sY;
		m_clThreshold[ ZTRA ] = stUser.Threshold.sZ;
		m_clThreshold[ XROT ] = stUser.Threshold.sRX;
		m_clThreshold[ YROT ] = stUser.Threshold.sRY;
		m_clThreshold[ ZROT ] = stUser.Threshold.sRZ;

		m_ctrlThresSel.SetCurSel ( 0 );
		m_ctrlThres.SetValue ( stUser.Threshold.sX, 0 );

		m_ctrlFreq.SetValue( stUser.Operation.dFreq );
		OnUpdateFreq ( );

		//
		//stProp.dwSize = sizeof ( SBW::_stProperties );
		//
		m_clCtrlItem[ IDX_THRE ]->SetState ( stProp.Threshold.bEnable ? BST_CHECKED : BST_UNCHECKED );
		m_clCtrlItem[ IDX_THRE ]->SetInt ( stProp.Threshold.cValue );

		//
		m_clCtrlItem[ IDX_TENS ]->SetState ( stProp.TransSensitivities.bEnable ? BST_CHECKED : BST_UNCHECKED );
		iVal = stProp.TransSensitivities.sValue[ 2 ] |
			( ( (__int64) stProp.TransSensitivities.sValue[ 1 ] ) << 16 ) |
			( ( (__int64) stProp.TransSensitivities.sValue[ 0 ]) << 32 );
		m_clCtrlItem[ IDX_TENS ]->SetInt ( iVal );
		// Responsiveness
		m_clCtrlItem[ IDX_RESS ]->SetState ( stProp.Responsiveness.bEnable ? BST_CHECKED : BST_UNCHECKED );
		m_clCtrlItem[ IDX_RMAX ]->SetInt ( stProp.Responsiveness.sMaximum );
		// Responsiveness - Minimum
		m_clCtrlItem[ IDX_RMIN ]->SetState ( stProp.Responsiveness.Minimum.bEnable ? BST_CHECKED : BST_UNCHECKED );
		m_clCtrlItem[ IDX_RMIN ]->SetInt ( stProp.Responsiveness.Minimum.sValue );
		// ResponMultiplier
		// ResponMultiplier - Translation
		m_clCtrlItem[ IDX_RENS ]->SetState ( stProp.ResponMultiplier.Translation.bEnable ? BST_CHECKED : BST_UNCHECKED );
		m_clCtrlItem[ IDX_RENS ]->SetInt ( stProp.ResponMultiplier.Translation.cValue );
		// ResponMultiplier - Rotation
		m_clCtrlItem[ IDX_REOT ]->SetState ( stProp.ResponMultiplier.Rotation.bEnable ? BST_CHECKED : BST_UNCHECKED );
		m_clCtrlItem[ IDX_REOT ]->SetInt ( stProp.ResponMultiplier.Rotation.cValue );
		// SpinRate
		m_clCtrlItem[ IDX_SPRT ]->SetState ( stProp.SpinRate.bEnable ? BST_CHECKED : BST_UNCHECKED );
		m_clCtrlItem[ IDX_SPAN ]->SetInt ( stProp.SpinRate.cMantissa );
		m_clCtrlItem[ IDX_SPXP ]->SetInt ( stProp.SpinRate.cExponent );
		// TranslationMode
		m_clCtrlItem[ IDX_TRMD ]->SetState ( stProp.TranslationMode.bEnable ? BST_CHECKED : BST_UNCHECKED );

		if ( stProp.TranslationMode.cBallSystem == 'P' ) {
			m_clCtrlItem[ IDX_TRSY ]->SetValue ( m_clString[ IDS_PARENT ] );
		}

		else if ( stProp.TranslationMode.cBallSystem == 'L' ) {
			m_clCtrlItem[ IDX_TRSY ]->SetValue ( m_clString[ IDS_LOCAL ] );
		}

		else if ( stProp.TranslationMode.cBallSystem == 'X' ) {
			m_clCtrlItem[ IDX_TRSY ]->SetValue ( m_clString[ IDS_DONOTCHANGE ] );
		}

		if ( stProp.TranslationMode.cFreedomVector == 'P' ) {
			m_clCtrlItem[ IDX_TRCT ]->SetValue ( m_clString[ IDS_PARENT ] );
		}

		else if ( stProp.TranslationMode.cFreedomVector == 'L' ) {
			m_clCtrlItem[ IDX_TRCT ]->SetValue ( m_clString[ IDS_LOCAL ] );
		}

		else if ( stProp.TranslationMode.cFreedomVector == 'X' ) {
			m_clCtrlItem[ IDX_TRCT ]->SetValue ( m_clString[ IDS_DONOTCHANGE ] );
		}

		if ( stProp.TranslationMode.cOutput == 'P' ) {
			m_clCtrlItem[ IDX_TROU ]->SetValue ( m_clString[ IDS_PARENT ] );
		}

		else if ( stProp.TranslationMode.cOutput == 'L' ) {
			m_clCtrlItem[ IDX_TROU ]->SetValue ( m_clString[ IDS_LOCAL ] );
		}

		else if ( stProp.TranslationMode.cOutput == 'X' ) {
			m_clCtrlItem[ IDX_TROU ]->SetValue ( m_clString[ IDS_DONOTCHANGE ] );
		}

		m_clCtrlItem[ IDX_TRVE ]->SetState ( stProp.TranslationMode.Vector.bEnable ? BST_CHECKED : BST_UNCHECKED );
		iVal = stProp.TranslationMode.Vector.sValue[ 2 ] |
			( ( (__int64) stProp.TranslationMode.Vector.sValue[ 1 ]) << 16 ) |
			( ( (__int64) stProp.TranslationMode.Vector.sValue[ 0 ]) << 32 );
		m_clCtrlItem[ IDX_TRVE ]->SetInt ( iVal );
		// RotationMode
		m_clCtrlItem[ IDX_RODE ]->SetState ( stProp.RotationMode.bEnable ? BST_CHECKED : BST_UNCHECKED );

		if ( stProp.RotationMode.cBallSystem == 'P' ) {
			m_clCtrlItem[ IDX_RSYS ]->SetValue ( m_clString[ IDS_PARENT ] );
		}

		else if ( stProp.RotationMode.cBallSystem == 'L' ) {
			m_clCtrlItem[ IDX_RSYS ]->SetValue ( m_clString[ IDS_LOCAL ] );
		}

		else if ( stProp.RotationMode.cBallSystem == 'X' ) {
			m_clCtrlItem[ IDX_RSYS ]->SetValue ( m_clString[ IDS_DONOTCHANGE ] );
		}

		if ( stProp.RotationMode.cFreedomVector == 'P' ) {
			m_clCtrlItem[ IDX_RFVE ]->SetValue ( m_clString[ IDS_PARENT ] );
		}

		else if ( stProp.RotationMode.cFreedomVector == 'L' ) {
			m_clCtrlItem[ IDX_RFVE ]->SetValue ( m_clString[ IDS_LOCAL ] );
		}

		else if ( stProp.RotationMode.cFreedomVector == 'X' ) {
			m_clCtrlItem[ IDX_RFVE ]->SetValue ( m_clString[ IDS_DONOTCHANGE ] );
		}

		if ( stProp.RotationMode.cOutput == 'P' ) {
			m_clCtrlItem[ IDX_ROUT ]->SetValue ( m_clString[ IDS_PARENT ] );
		}

		else if ( stProp.RotationMode.cOutput == 'L' ) {
			m_clCtrlItem[ IDX_ROUT ]->SetValue ( m_clString[ IDS_LOCAL ] );
		}

		else if ( stProp.RotationMode.cOutput == 'X' ) {
			m_clCtrlItem[ IDX_ROUT ]->SetValue ( m_clString[ IDS_DONOTCHANGE ] );
		}

		m_clCtrlItem[ IDX_RVEC ]->SetState ( stProp.RotationMode.Vector.bEnable ? BST_CHECKED : BST_UNCHECKED );
		iVal = stProp.RotationMode.Vector.sValue[ 2 ] |
			( ( (__int64) stProp.RotationMode.Vector.sValue[ 1 ] ) << 16 ) |
			( ( (__int64) stProp.RotationMode.Vector.sValue[ 0 ]) << 32 );
		m_clCtrlItem[ IDX_RVEC ]->SetInt ( iVal );
		//
		m_clCtrlItem[ IDX_MODE ]->SetState ( stProp.Mode.bEnable ? BST_CHECKED : BST_UNCHECKED );

		if ( stProp.Mode.cTranslationFreedom == 'X' ) {
			m_clCtrlItem[ IDX_TRAF ]->SetValue ( m_clString[ IDS_DONOTCHANGE ] );
		}

		else if ( stProp.Mode.cTranslationFreedom == 'L' ) {
			m_clCtrlItem[ IDX_TRAF ]->SetValue ( m_clString[ IDS_LINEAR ] );
		}

		else if ( stProp.Mode.cTranslationFreedom == 'S' ) {
			m_clCtrlItem[ IDX_TRAF ]->SetValue ( m_clString[ IDS_SPATIAL ] );
		}

		else if ( stProp.Mode.cTranslationFreedom == 'N' ) {
			m_clCtrlItem[ IDX_TRAF ]->SetValue ( m_clString[ IDS_NOFREEDOM ] );
		}

		m_clCtrlItem[ IDX_ROTA ]->SetState ( stProp.Mode.Rotation.bEnable ? BST_CHECKED : BST_UNCHECKED );

		if ( stProp.Mode.Rotation.cRotationFreedom == 'X' ) {
			m_clCtrlItem[ IDX_ROTF ]->SetValue ( m_clString[ IDS_DONOTCHANGE ] );
		}

		else if ( stProp.Mode.Rotation.cRotationFreedom == 'L' ) {
			m_clCtrlItem[ IDX_ROTF ]->SetValue ( m_clString[ IDS_LINEAR ] );
		}

		else if ( stProp.Mode.Rotation.cRotationFreedom == 'S' ) {
			m_clCtrlItem[ IDX_ROTF ]->SetValue ( m_clString[ IDS_SPATIAL ] );
		}

		else if ( stProp.Mode.Rotation.cRotationFreedom == 'N' ) {
			m_clCtrlItem[ IDX_ROTF ]->SetValue ( m_clString[ IDS_NOFREEDOM ] );
		}

		m_clCtrlItem[ IDX_RFOR ]->SetState ( stProp.Mode.Rotation.DataForm.bEnable ? BST_CHECKED : BST_UNCHECKED );

		if ( stProp.Mode.Rotation.DataForm.cDataType == 'X' ) {
			m_clCtrlItem[ IDX_ROTY ]->SetValue ( m_clString[ IDS_DONOTCHANGE ] );
		}

		else if ( stProp.Mode.Rotation.DataForm.cDataType == 'L' ) {
			m_clCtrlItem[ IDX_ROTY ]->SetValue ( m_clString[ IDS_LINEAR ] );
		}

		else if ( stProp.Mode.Rotation.DataForm.cDataType == 'S' ) {
			m_clCtrlItem[ IDX_ROTY ]->SetValue ( m_clString[ IDS_SPATIAL ] );
		}

		else if ( stProp.Mode.Rotation.DataForm.cDataType == 'N' ) {
			m_clCtrlItem[ IDX_ROTY ]->SetValue ( m_clString[ IDS_NOFREEDOM ] );
		}

		m_clCtrlItem[ IDX_RHAN ]->SetState ( stProp.Mode.Rotation.DataForm.Handedness.bEnable ? BST_CHECKED : BST_UNCHECKED );
		m_clCtrlItem[ IDX_LFTH ]->SetBool( stProp.Mode.Rotation.DataForm.Handedness.bLeftHanded );
		m_clCtrlItem[ IDX_RPRP ]->SetState ( stProp.Mode.Rotation.DataForm.Handedness.PrePostProc.bEnable ? BST_CHECKED : BST_UNCHECKED );

		if ( stProp.Mode.Rotation.DataForm.Handedness.PrePostProc.cValue == 'A' ) {
			m_clCtrlItem[ IDX_RPPO ]->SetValue ( m_clString[ IDS_POST ] );
		}

		else {
			m_clCtrlItem[ IDX_RPPO ]->SetValue ( m_clString[ IDS_PRE ] );
		}

		m_clCtrlItem[ IDX_ZERO ]->SetState ( stProp.Zero.bEnable ? BST_CHECKED : BST_UNCHECKED );
		m_clCtrlItem[ IDX_ABMX ]->SetState ( stProp.AbsoluteRotMatrix.bEnable ? BST_CHECKED : BST_UNCHECKED );
		iVal = stProp.AbsoluteRotMatrix.sValue[ 2 ] |
			( ( (__int64) stProp.AbsoluteRotMatrix.sValue[ 1 ] ) << 16 ) |
			( ( (__int64) stProp.AbsoluteRotMatrix.sValue[ 0 ]) << 32 );
		m_clCtrlItem[ IDX_ABMX ]->SetInt ( iVal );
		m_clCtrlItem[ IDX_ORIE ]->SetState ( stProp.OrientationMatrix.bEnable ? BST_CHECKED : BST_UNCHECKED );
		iVal = stProp.OrientationMatrix.sValue[ 2 ] |
			( ( (__int64) stProp.OrientationMatrix.sValue[ 1 ] ) << 16 ) |
			( ( (__int64) stProp.OrientationMatrix.sValue[ 0 ]) << 32 );
		m_clCtrlItem[ IDX_ORIE ]->SetInt ( iVal );
		// Communication mode
		m_clCtrlItem[ IDX_MODP ]->SetState ( stProp.CommunicationMode.bEnable ? BST_CHECKED : BST_UNCHECKED );

		if ( stProp.CommunicationMode.cValue == 'B' ) {
			m_clCtrlItem[ IDX_MODP ]->SetValue ( m_clString[ IDS_BINARY ] );
		}

		else {
			m_clCtrlItem[ IDX_MODP ]->SetValue ( m_clString[ IDS_PRINTABLE ] );
		}

		//
		//IDX_BEEP
		//IDX_LINS
		//
	}
}

void CSBWAppDlg::OnLoadSett ( )
{
	CString ttt;
	DWORD MaximumComponentLength;
	GetVolumeInformation ( NULL, NULL, 0, NULL, &MaximumComponentLength, NULL, NULL, 0 );
	CString FileName, InitDir;
	CFileDialog dlgFile ( TRUE );
	OPENFILENAME &ofn = dlgFile.GetOFN ( );
	ofn.nMaxFile = max ( MaximumComponentLength, MAX_PATH ) + 1;
	ofn.lpstrFile = FileName.GetBuffer ( ofn.nMaxFile );
	ofn.lpstrInitialDir = InitDir.GetBuffer ( ofn.nMaxFile );
	SHGetSpecialFolderPath ( m_hWnd, ( LPWSTR ) ofn.lpstrInitialDir, CSIDL_DESKTOP, FALSE );
	ofn.lpstrFilter = _T ( "Profile\0*.sbcfg\0\0" );
	ofn.nFilterIndex = 1;

	if ( dlgFile.DoModal ( ) == IDOK ) {
		FileName.ReleaseBuffer ( );

		TCHAR tZero[] = { 0 };
		CString clData;
		CFile clFile;
		clFile.Open ( FileName, CFile::modeRead );
		int iLen = (int) clFile.GetLength ( ) ;
		_stUser stUser = { 0 };
		SBW::_stProperties stProp = { 0 };

		clFile.Read ( &stProp, sizeof ( stProp ) );
		clFile.Read ( &stUser, sizeof ( stUser ) );

		Translate ( false, stProp, stUser );

		iLen = iLen - sizeof ( stProp ) - sizeof ( stUser );

		TCHAR *pRead = clData.GetBuffer ( ( iLen / sizeof ( TCHAR ) ) + 1 );
		clFile.Read ( pRead, iLen );
		pRead[iLen / sizeof ( TCHAR )] = 0;

		m_ctrlSettings.Load ( clData );
	}

	else {
		FileName.ReleaseBuffer ( );
	}

	InitDir.ReleaseBuffer ( );
}

void CSBWAppDlg::OnSaveSett ( )
{
	DWORD MaximumComponentLength;
	GetVolumeInformation ( NULL, NULL, 0, NULL, &MaximumComponentLength, NULL, NULL, 0 );
	CString FileName, InitDir;
	CFileDialog dlgFile ( FALSE );
	OPENFILENAME &ofn = dlgFile.GetOFN ( );
	ofn.nMaxFile = max ( MaximumComponentLength, MAX_PATH ) + 1;
	ofn.lpstrFile = FileName.GetBuffer ( ofn.nMaxFile );
	ofn.lpstrInitialDir = InitDir.GetBuffer ( ofn.nMaxFile );
	SHGetSpecialFolderPath ( m_hWnd, ( LPWSTR ) ofn.lpstrInitialDir, CSIDL_DESKTOP, FALSE );
	ofn.lpstrFilter = _T ( "Profile\0*.sbcfg\0\0" );
	ofn.nFilterIndex = 1;

	if ( dlgFile.DoModal ( ) == IDOK ) {
		FileName.ReleaseBuffer ( );
		FileName += m_clString[IDS_FILEEXT];
		FileName.Replace ( m_clString[IDS_FILEEXT] + m_clString[IDS_FILEEXT], m_clString[IDS_FILEEXT] );

		_stUser stUser = { 0 };
		SBW::_stProperties stProp = { 0 };
		Translate ( true, stProp, stUser );

		CFile clFile;
		clFile.Open ( FileName, CFile::modeReadWrite | CFile::modeCreate );
		clFile.Write ( &stProp, sizeof ( stProp ) );
		clFile.Write ( &stUser, sizeof ( stUser ) );
		clFile.Flush ( );

		m_ctrlSettings.Save ( clFile );
		clFile.Close ( );
	}

	else {
		FileName.ReleaseBuffer ( );
	}

	InitDir.ReleaseBuffer ( );
}

void CSBWAppDlg::CreateProp_RotationMode ( CArray<__int64, __int64> &min, CArray<__int64, __int64> &max )
{
	m_clCtrlItem[IDX_RODE] = new CMFCPropertyGridProperty2 ( m_clDefaultState[IDX_RODE], m_clString[IDS_ROTATION_MODE] );
	m_clCtrlItem[IDX_RSYS] = new CMFCPropertyGridProperty2 ( m_clDefaultState[IDX_RSYS], m_clString[IDS_BALL_SYSTEM],
															 m_clDefaultValue[IDX_RSYS].bstrVal,
															 m_clString[IDS_R_BALL_SYSTEM] );
	m_clCtrlItem[IDX_RSYS]->AddOption ( m_clString[IDS_LOCAL] );
	m_clCtrlItem[IDX_RSYS]->AddOption ( m_clString[IDS_PARENT] );
	m_clCtrlItem[IDX_RSYS]->AddOption ( m_clString[IDS_DONOTCHANGE] );
	m_clCtrlItem[IDX_RSYS]->AllowEdit ( FALSE );;
	m_clCtrlItem[IDX_RFVE] = new CMFCPropertyGridProperty2 ( m_clDefaultState[IDX_RFVE], m_clString[IDS_FREEDOM_VECTOR],
															 m_clDefaultValue[IDX_RFVE].bstrVal,
															 m_clString[IDS_R_FREE_VECTOR_SYS] );
	m_clCtrlItem[IDX_RFVE]->AddOption ( m_clString[IDS_LOCAL] );
	m_clCtrlItem[IDX_RFVE]->AddOption ( m_clString[IDS_PARENT] );
	m_clCtrlItem[IDX_RFVE]->AddOption ( m_clString[IDS_DONOTCHANGE] );
	m_clCtrlItem[IDX_RFVE]->AllowEdit ( FALSE );;
	m_clCtrlItem[IDX_ROUT] = new CMFCPropertyGridProperty2 ( m_clDefaultState[IDX_ROUT], m_clString[IDS_OUTPUT],
															 m_clDefaultValue[IDX_ROUT].bstrVal,
															 m_clString[IDS_R_OUTPUT_SYSTEM] );
	m_clCtrlItem[IDX_ROUT]->AddOption ( m_clString[IDS_LOCAL] );
	m_clCtrlItem[IDX_ROUT]->AddOption ( m_clString[IDS_PARENT] );
	m_clCtrlItem[IDX_ROUT]->AddOption ( m_clString[IDS_DONOTCHANGE] );
	m_clCtrlItem[IDX_ROUT]->AllowEdit ( FALSE );
	min.RemoveAll ( );
	max.RemoveAll ( );
	min.Add ( 0 );
	min.Add ( 0 );
	min.Add ( 0 );
	max.Add ( 0x7FFF );
	max.Add ( 0x7FFF );
	max.Add ( 0x7FFF );
	m_clCtrlItem[IDX_RVEC] = new CHexNumberProp ( m_clDefaultState[IDX_RVEC], m_clString[IDS_VECTOR], m_clDefaultValue[IDX_RVEC].llVal, &min,
												  &max, 4, HEXPFX,
												  m_clString[IDS_R_ROT_FREE_VECTOR] );
	m_clCtrlItem[IDX_RODE]->AddSubItem ( m_clCtrlItem[IDX_RSYS] );
	m_clCtrlItem[IDX_RODE]->AddSubItem ( m_clCtrlItem[IDX_RFVE] );
	m_clCtrlItem[IDX_RODE]->AddSubItem ( m_clCtrlItem[IDX_ROUT] );
	m_clCtrlItem[IDX_RODE]->AddSubItem ( m_clCtrlItem[IDX_RVEC] );
}

void CSBWAppDlg::CreateProp_TranslationMode ( CArray<__int64, __int64> &min, CArray<__int64, __int64> &max )
{
	m_clCtrlItem[IDX_TRMD] = new CMFCPropertyGridProperty2 ( m_clDefaultState[IDX_TRMD], m_clString[IDS_TRANSLATION_MODE] );
	m_clCtrlItem[IDX_TRSY] = new CMFCPropertyGridProperty2 ( m_clDefaultState[IDX_TRSY], m_clString[IDS_BALL_SYSTEM],
															 m_clDefaultValue[IDX_TRSY].bstrVal,
															 m_clString[IDS_T_BALL_SYSTEM] );
	m_clCtrlItem[IDX_TRSY]->AddOption ( m_clString[IDS_LOCAL] );
	m_clCtrlItem[IDX_TRSY]->AddOption ( m_clString[IDS_PARENT] );
	m_clCtrlItem[IDX_TRSY]->AddOption ( m_clString[IDS_DONOTCHANGE] );
	m_clCtrlItem[IDX_TRSY]->AllowEdit ( FALSE );
	m_clCtrlItem[IDX_TRCT] = new CMFCPropertyGridProperty2 ( m_clDefaultState[IDX_TRCT], m_clString[IDS_FREEDOM_VECTOR],
															 m_clDefaultValue[IDX_TRCT].bstrVal,
															 m_clString[IDS_T_FREE_VECTOR_SYS] );
	m_clCtrlItem[IDX_TRCT]->AddOption ( m_clString[IDS_LOCAL] );
	m_clCtrlItem[IDX_TRCT]->AddOption ( m_clString[IDS_PARENT] );
	m_clCtrlItem[IDX_TRCT]->AddOption ( m_clString[IDS_DONOTCHANGE] );
	m_clCtrlItem[IDX_TRCT]->AllowEdit ( FALSE );;
	m_clCtrlItem[IDX_TROU] = new CMFCPropertyGridProperty2 ( m_clDefaultState[IDX_TROU], m_clString[IDS_OUTPUT],
															 m_clDefaultValue[IDX_TROU].bstrVal,
															 m_clString[IDS_T_OUTPUT_SYS] );
	m_clCtrlItem[IDX_TROU]->AddOption ( m_clString[IDS_LOCAL] );
	m_clCtrlItem[IDX_TROU]->AddOption ( m_clString[IDS_PARENT] );
	m_clCtrlItem[IDX_TROU]->AddOption ( m_clString[IDS_DONOTCHANGE] );
	m_clCtrlItem[IDX_TROU]->AllowEdit ( FALSE );
	min.RemoveAll ( );
	max.RemoveAll ( );
	min.Add ( 0 );
	min.Add ( 0 );
	min.Add ( 0 );
	max.Add ( 0x7FFF );
	max.Add ( 0x7FFF );
	max.Add ( 0x7FFF );
	m_clCtrlItem[IDX_TRVE] = new CHexNumberProp ( m_clDefaultState[IDX_TRVE], m_clString[IDS_VECTOR], m_clDefaultValue[IDX_TRVE].llVal, &min,
												  &max, 4, HEXPFX,
												  m_clString[IDS_T_TRANS_FREE_VECTOR] );
	m_clCtrlItem[IDX_TRMD]->AddSubItem ( m_clCtrlItem[IDX_TRSY] );
	m_clCtrlItem[IDX_TRMD]->AddSubItem ( m_clCtrlItem[IDX_TRCT] );
	m_clCtrlItem[IDX_TRMD]->AddSubItem ( m_clCtrlItem[IDX_TROU] );
	m_clCtrlItem[IDX_TRMD]->AddSubItem ( m_clCtrlItem[IDX_TRVE] );
}

void CSBWAppDlg::CreateProp_Mode ( )
{
	m_clCtrlItem[IDX_MODE] = new CMFCPropertyGridProperty2 ( m_clDefaultState[IDX_MODE], m_clString[IDS_MODE] );
	//
	//! Mode - Left-handed
	//
	COleVariant varLeft ( m_clDefaultValue[IDX_LFTH].iVal, VT_BOOL );
	m_clCtrlItem[IDX_LFTH] = new CMFCPropertyGridProperty2 ( m_clDefaultState[IDX_LFTH], m_clString[IDS_LEFT_HANDED], varLeft,
															 m_clString[IDS_M_HANDEDNESS] );
	//
	//! Mode - Translation
	//
	m_clCtrlItem[IDX_TRAN] = new CMFCPropertyGridProperty2 ( m_clDefaultState[IDX_TRAN], m_clString[IDS_TRANSLATION] );
	m_clCtrlItem[IDX_TRAF] = new CMFCPropertyGridProperty2 ( m_clDefaultState[IDX_TRAF], m_clString[IDS_FREEDOM],
															 m_clDefaultValue[IDX_TRAF].bstrVal,
															 m_clString[IDS_M_TRANS_MODE] );
	m_clCtrlItem[IDX_TRAF]->AddOption ( m_clString[IDS_NOFREEDOM] );
	m_clCtrlItem[IDX_TRAF]->AddOption ( m_clString[IDS_LINEAR] );
	m_clCtrlItem[IDX_TRAF]->AddOption ( m_clString[IDS_PLANAR] );
	m_clCtrlItem[IDX_TRAF]->AddOption ( m_clString[IDS_SPATIAL] );
	m_clCtrlItem[IDX_TRAF]->AddOption ( m_clString[IDS_DONOTCHANGE] );
	m_clCtrlItem[IDX_TRAF]->AllowEdit ( FALSE );
	m_clCtrlItem[IDX_TRAN]->AddSubItem ( m_clCtrlItem[IDX_TRAF] );
	//
	//! Mode - Rotation
	//
	m_clCtrlItem[IDX_ROTA] = new CMFCPropertyGridProperty2 ( m_clDefaultState[IDX_ROTA], m_clString[IDS_ROTATION] );
	m_clCtrlItem[IDX_RFOR] = new CMFCPropertyGridProperty2 ( m_clDefaultState[IDX_RFOR], m_clString[IDS_ROTATION_FORM] );
	m_clCtrlItem[IDX_RHAN] = new CMFCPropertyGridProperty2 ( m_clDefaultState[IDX_RHAN], m_clString[IDS_HANDEDNESS] );
	m_clCtrlItem[IDX_RPRP] = new CMFCPropertyGridProperty2 ( m_clDefaultState[IDX_RPRP], m_clString[IDS_PRE_POST_PROC] );
	m_clCtrlItem[IDX_ROTF] = new CMFCPropertyGridProperty2 ( m_clDefaultState[IDX_ROTF], m_clString[IDS_FREEDOM],
															 m_clDefaultValue[IDX_ROTF].bstrVal,
															 m_clString[IDS_M_ROTATION_MODE] );
	m_clCtrlItem[IDX_ROTF]->AddOption ( m_clString[IDS_NOFREEDOM] );
	m_clCtrlItem[IDX_ROTF]->AddOption ( m_clString[IDS_LINEAR] );
	m_clCtrlItem[IDX_ROTF]->AddOption ( m_clString[IDS_PLANAR] );
	m_clCtrlItem[IDX_ROTF]->AddOption ( m_clString[IDS_SPATIAL] );
	m_clCtrlItem[IDX_ROTF]->AddOption ( m_clString[IDS_DONOTCHANGE] );
	m_clCtrlItem[IDX_ROTF]->AllowEdit ( FALSE );
	m_clCtrlItem[IDX_ROTY] = new CMFCPropertyGridProperty2 ( m_clDefaultState[IDX_ROTY], m_clString[IDS_DATA_TYPE],
															 m_clDefaultValue[IDX_ROTY].bstrVal,
															 m_clString[IDS_M_ROT_DATA_TYPE] );
	m_clCtrlItem[IDX_ROTY]->AddOption ( m_clString[IDS_DELTAMATRIX] );
	m_clCtrlItem[IDX_ROTY]->AddOption ( m_clString[IDS_ABSOLUTEMATRIX] );
	m_clCtrlItem[IDX_ROTY]->AddOption ( m_clString[IDS_VECTOR] );
	m_clCtrlItem[IDX_ROTY]->AddOption ( m_clString[IDS_DONOTCHANGE] );
	m_clCtrlItem[IDX_ROTY]->AllowEdit ( FALSE );
	m_clCtrlItem[IDX_RPPO] = new CMFCPropertyGridProperty2 ( m_clDefaultState[IDX_RPPO], m_clString[IDS_MODE],
															 m_clDefaultValue[IDX_RPPO].bstrVal,
															 m_clString[IDS_M_PRE_POST_PROC] );
	m_clCtrlItem[IDX_RPPO]->AddOption ( m_clString[IDS_PRE] );
	m_clCtrlItem[IDX_RPPO]->AddOption ( m_clString[IDS_POST] );
	m_clCtrlItem[IDX_RPPO]->AllowEdit ( FALSE );
	m_clCtrlItem[IDX_RPRP]->AddSubItem ( m_clCtrlItem[IDX_RPPO] );
	m_clCtrlItem[IDX_RHAN]->AddSubItem ( m_clCtrlItem[IDX_LFTH] );
	m_clCtrlItem[IDX_RHAN]->AddSubItem ( m_clCtrlItem[IDX_RPRP] );
	m_clCtrlItem[IDX_RFOR]->AddSubItem ( m_clCtrlItem[IDX_ROTY] );
	m_clCtrlItem[IDX_RFOR]->AddSubItem ( m_clCtrlItem[IDX_RHAN] );
	m_clCtrlItem[IDX_ROTA]->AddSubItem ( m_clCtrlItem[IDX_ROTF] );
	m_clCtrlItem[IDX_ROTA]->AddSubItem ( m_clCtrlItem[IDX_RFOR] );
	m_clCtrlItem[IDX_MODE]->AddSubItem ( m_clCtrlItem[IDX_TRAN] );
	m_clCtrlItem[IDX_MODE]->AddSubItem ( m_clCtrlItem[IDX_ROTA] );
}

void CSBWAppDlg::CreateProp_Threshold ( CArray<__int64, __int64> &min, CArray<__int64, __int64> &max )
{
	min.RemoveAll ( );
	max.RemoveAll ( );
	min.Add ( 0x40 );
	max.Add ( 0x7F );
	m_clCtrlItem[IDX_THRE] = new CHexNumberProp ( m_clDefaultState[IDX_THRE], m_clString[IDS_THRESHOLD], m_clDefaultValue[IDX_THRE].llVal, &min,
												  &max, 2, HEXPFX,
												  m_clString[IDS_N_NULL_RADIUS] );
}

void CSBWAppDlg::CreateProp_TranslationSensitivities ( CArray<__int64, __int64> &min, CArray<__int64, __int64> &max )
{
	min.RemoveAll ( );
	max.RemoveAll ( );
	min.Add ( 0 );
	min.Add ( 0 );
	min.Add ( 0 );
	max.Add ( 0x7FFF );
	max.Add ( 0x7FFF );
	max.Add ( 0x7FFF );
	m_clCtrlItem[IDX_TENS] = new CHexNumberProp ( m_clDefaultState[IDX_TENS], m_clString[IDS_TRANSLATION_SENS],
												  m_clDefaultValue[IDX_TENS].llVal, &min, &max, 4, HEXPFX,
												  m_clString[IDS_X_SENSITIVITY] );
}

void CSBWAppDlg::CreateProp_UnvInfo ( CArray<__int64, __int64> &min, CArray<__int64, __int64> &max )
{
	UNREFERENCED_PARAMETER ( min );
	UNREFERENCED_PARAMETER ( max );

	m_clCtrlItem[IDX_LINS] = new CNullProp ( m_clDefaultState[IDX_LINS], m_clString[IDS_SENSITIVITY_MODE], m_clDefaultValue[IDX_LINS],
											 RGB ( 180, 180, 180 ),
											 m_clString[IDS_Y] );
	m_clCtrlItem[IDX_LINS]->Enable ( FALSE );
	//m_PrObj[IDX_MODP] = new CNullProp ( m_PrState[IDX_MODP], StrMap[IDS_COMM_MODE_PACKET], m_PrDefValue[IDX_MODP], RGB ( 180, 180, 180 ), StrMap[IDS_C_COMM_MODE] );
	//m_PrObj[IDX_MODP]->Enable ( FALSE );
	m_clCtrlItem[IDX_MODP] = new CMFCPropertyGridProperty2 ( m_clDefaultState[IDX_MODP], m_clString[IDS_COMM_MODE_PACKET],
															 m_clDefaultValue[IDX_MODP].bstrVal,
															 m_clString[IDS_C_COMM_MODE] );
	m_clCtrlItem[IDX_MODP]->AddOption ( m_clString[IDS_BINARY] );
	m_clCtrlItem[IDX_MODP]->AddOption ( m_clString[IDS_PRINTABLE] );
}

void CSBWAppDlg::CreateProp_Beeper ( CArray<__int64, __int64> &min, CArray<__int64, __int64> &max )
{
	UNREFERENCED_PARAMETER ( min );
	UNREFERENCED_PARAMETER ( max );

	/* min.RemoveAll ( );
		 max.RemoveAll ( );
		 min.Add ( 0xF0 );
		 max.Add ( 0xFF );*/
	/* m_PrObj[IDX_BEEP] = new CHexNumberProp ( m_PrState[IDX_BEEP], StrMap[IDS_BEEPER], m_PrDefValue[IDX_BEEP].llVal, &min, &max, 2, HEXPFX,
		 StrMap[IDS_B_BEEPER] );*/
	m_clCtrlItem[IDX_BEEP] = new CNullProp ( m_clDefaultState[IDX_BEEP], m_clString[IDS_BEEPER], m_clDefaultValue[IDX_BEEP], RGB ( 180, 180,
											 180 ),
											 m_clString[IDS_B_BEEPER] );
	m_clCtrlItem[IDX_BEEP]->Enable ( FALSE );
}

void CSBWAppDlg::CreateProp_Zero ( )
{
	m_clCtrlItem[IDX_ZERO] = new CNullProp ( m_clDefaultState[IDX_ZERO], m_clString[IDS_ZERO], m_clDefaultValue[IDX_ZERO], RGB ( 180, 180,
											 180 ),
											 m_clString[IDS_Z] );
}

void CSBWAppDlg::CreateProp_Orientation ( CArray<__int64, __int64> &min, CArray<__int64, __int64> &max )
{
	min.RemoveAll ( );
	max.RemoveAll ( );
	min.Add ( 0 );
	min.Add ( 0 );
	min.Add ( 0 );
	max.Add ( 0xFFFF );
	max.Add ( 0xFFFF );
	max.Add ( 0xFFFF );
	m_clCtrlItem[IDX_ORIE] = new CHexNumberProp ( m_clDefaultState[IDX_ORIE], m_clString[IDS_ORIENTATION_MATRIX],
												  m_clDefaultValue[IDX_ORIE].llVal, &min, &max, 4, HEXPFX,
												  m_clString[IDS_O_ROTATION_MATRIX] );
}

void CSBWAppDlg::CreateProp_AbsoluteMatrix ( CArray<__int64, __int64> &min, CArray<__int64, __int64> &max )
{
	min.RemoveAll ( );
	max.RemoveAll ( );
	min.Add ( 0 );
	min.Add ( 0 );
	min.Add ( 0 );
	max.Add ( 0xFFFF );
	max.Add ( 0xFFFF );
	max.Add ( 0xFFFF );
	m_clCtrlItem[IDX_ABMX] = new CHexNumberProp ( m_clDefaultState[IDX_ABMX], m_clString[IDS_ABSOLUTEMATRIX], m_clDefaultValue[IDX_ABMX].llVal,
												  &min, &max, 4, HEXPFX,
												  m_clString[IDS_A_ROTATION_MATRIX] );
}

void CSBWAppDlg::CreateProp_Responsiveness ( CArray<__int64, __int64> &min, CArray<__int64, __int64> &max )
{
	m_clCtrlItem[IDX_RESS] = new CMFCPropertyGridProperty2 ( m_clDefaultState[IDX_RESS], m_clString[IDS_RESPONSIVENESS] );
	min.RemoveAll ( );
	max.RemoveAll ( );
	min.Add ( 0x40 );
	min.Add ( 0x40 );
	max.Add ( 0x7F );
	max.Add ( 0x7F );
	m_clCtrlItem[IDX_RMIN] = new CHexNumberProp ( m_clDefaultState[IDX_RMIN], m_clString[IDS_MINIMUM], m_clDefaultValue[IDX_RMIN].llVal, &min,
												  &max, 2, HEXPFX,
												  m_clString[IDS_P_MIN_PERIOD] );
	m_clCtrlItem[IDX_RMAX] = new CHexNumberProp ( m_clDefaultState[IDX_RMAX], m_clString[IDS_MAXIMUM], m_clDefaultValue[IDX_RMAX].llVal, &min,
												  &max, 2, HEXPFX,
												  m_clString[IDS_P_MAX_PERIOD] );
	m_clCtrlItem[IDX_RESS]->AddSubItem ( m_clCtrlItem[IDX_RMIN] );
	m_clCtrlItem[IDX_RESS]->AddSubItem ( m_clCtrlItem[IDX_RMAX] );
}

void CSBWAppDlg::CreateProp_ResponseMultiplier ( CArray<__int64, __int64> &min, CArray<__int64, __int64> &max )
{
	m_clCtrlItem[IDX_REMU] = new CMFCPropertyGridProperty2 ( m_clDefaultState[IDX_REMU], m_clString[IDS_RESPONSE_MUL] );
	min.RemoveAll ( );
	max.RemoveAll ( );
	min.Add ( 0x00 );
	max.Add ( 0x7F );
	m_clCtrlItem[IDX_RENS] = new CHexNumberProp ( m_clDefaultState[IDX_RENS], m_clString[IDS_TRANSLATION], m_clDefaultValue[IDX_RENS].llVal,
												  &min, &max, 2, HEXPFX,
												  m_clString[IDS_FT_FEEL] );
	m_clCtrlItem[IDX_REOT] = new CHexNumberProp ( m_clDefaultState[IDX_REOT], m_clString[IDS_ROTATION], m_clDefaultValue[IDX_REOT].llVal, &min,
												  &max, 2, HEXPFX,
												  m_clString[IDS_FR_FEEL] );
	m_clCtrlItem[IDX_REMU]->AddSubItem ( m_clCtrlItem[IDX_RENS] );
	m_clCtrlItem[IDX_REMU]->AddSubItem ( m_clCtrlItem[IDX_REOT] );
}

void CSBWAppDlg::CreateProp_SpinRate ( CArray<__int64, __int64> &min, CArray<__int64, __int64> &max )
{
	m_clCtrlItem[IDX_SPRT] = new CMFCPropertyGridProperty2 ( m_clDefaultState[IDX_SPRT], m_clString[IDS_SPIN_RATE] );
	min.RemoveAll ( );
	max.RemoveAll ( );
	min.Add ( 0x40 );
	max.Add ( 0x7F );
	m_clCtrlItem[IDX_SPAN] = new CHexNumberProp ( m_clDefaultState[IDX_SPAN], m_clString[IDS_MANTISSA], m_clDefaultValue[IDX_SPAN].llVal, &min,
												  &max, 2, HEXPFX,
												  m_clString[IDS_S_SPIN_R_MANTISSA] );
	m_clCtrlItem[IDX_SPXP] = new CHexNumberProp ( m_clDefaultState[IDX_SPXP], m_clString[IDS_EXPONENT], m_clDefaultValue[IDX_SPXP].llVal, &min,
												  &max, 2, HEXPFX,
												  m_clString[IDS_S_SPIN_R_EXPON] );
	m_clCtrlItem[IDX_SPRT]->AddSubItem ( m_clCtrlItem[IDX_SPAN] );
	m_clCtrlItem[IDX_SPRT]->AddSubItem ( m_clCtrlItem[IDX_SPXP] );
}

void CSBWAppDlg::OnAbout ( )
{
	CAbout About ( this );
	About.DoModal ( );
}

void CSBWAppDlg::OnAddByteValue ( )
{
	if ( m_ctrlAddByte.GetCheck ( ) == BST_CHECKED ) {
		m_ctrlByteValue.EnableWindow ( );
	}

	else {
		m_ctrlByteValue.EnableWindow ( FALSE );
	}
}

void CSBWAppDlg::OnUpdateByteValue ( )
{
	CString NewStr, Str;
	m_ctrlByteValue.GetWindowText ( Str );
	NewStr = Str;

	if ( NewStr.IsEmpty ( ) )
		return;

	if ( NewStr.Left ( 2 ).CompareNoCase ( m_clString[IDS_HEXPREFIX4] ) == 0 ) {
		if ( NewStr.GetLength ( ) > 4 ) {
			NewStr.Truncate ( 4 );
		}

		NewStr.MakeUpper ( );

		for ( int i = 2; i < NewStr.GetLength ( ); i++ ) {
			if ( ! ( ( ( NewStr.GetAt ( i ) > 47 ) && ( NewStr.GetAt ( i ) < 58 ) ) ||
					 ( ( NewStr.GetAt ( i ) > 64 ) && ( NewStr.GetAt ( i ) < 71 ) ) ) ) {
				NewStr.Delete ( i );
				i = 2;
			}
		}

		NewStr.SetAt ( 1, _T ( 'x' ) );
	}

	else {
		for ( int i = 0; i < NewStr.GetLength ( ); i++ ) {
			if ( ! ( ( NewStr.GetAt ( i ) > 47 ) && ( NewStr.GetAt ( i ) < 58 ) ) ) {
				NewStr.Delete ( i );
				i = 0;
			}
		}

		TCHAR *stopstring;
		long lVal = _tcstol ( NewStr.GetBuffer ( ), &stopstring, 10 );

		/* if ( lVal < 0 ) {
			 NewStr = _T ( "0" );
			 }

			 else*/ if ( lVal > 255 ) {
			NewStr = _T ( "255" );
		}
	}

	if ( NewStr != Str ) {
		m_ctrlByteValue.SetWindowText ( NewStr );
		m_ctrlByteValue.SetSel ( 255, 255, TRUE );
	}
}

void CSBWAppDlg::OnSetSignal ( )
{
	CString strItem;

	switch ( m_ctrlSetSignal.m_nMenuResult ) {
		case 1:
			m_ctrlSetSignal.SetWindowText ( m_clString[IDS_CLEARBREAK] );
			m_iSignal = 1;
			break;

		case 2:
			m_ctrlSetSignal.SetWindowText ( m_clString[IDS_SETBREAK] );
			m_iSignal = 2;
			break;

		case 3:
			m_ctrlSetSignal.SetWindowText ( m_clString[IDS_CLEARDTR] );
			m_iSignal = 3;
			break;

		case 4:
			m_ctrlSetSignal.SetWindowText ( m_clString[IDS_SETDTR] );
			m_iSignal = 4;
			break;

		case 5:
			m_ctrlSetSignal.SetWindowText ( m_clString[IDS_CLEARRTS] );
			m_iSignal = 5;
			break;

		case 6:
			m_ctrlSetSignal.SetWindowText ( m_clString[IDS_SETRTS] );
			m_iSignal = 6;
			break;

		case 7:
			m_ctrlSetSignal.SetWindowText ( m_clString[IDS_SETXOFF] );
			m_iSignal = 7;
			break;

		case 8:
			m_ctrlSetSignal.SetWindowText ( m_clString[IDS_SETXON] );
			m_iSignal = 8;
			break;

		case 9:
			m_ctrlSetSignal.SetWindowText ( m_clString[IDS_RESETDEV] );
			m_iSignal = 9;
			break;

		default:
			if ( m_iSignal != -1 ) {
				DWORD dwSignal;

				switch ( m_iSignal ) {
					case 1:
						dwSignal = CLRBREAK;
						break;

					case 2:
						dwSignal = SETBREAK;
						break;

					case 3:
						dwSignal = CLRDTR;
						break;

					case 4:
						dwSignal = SETDTR;
						break;

					case 5:
						dwSignal = CLRRTS;
						break;

					case 6:
						dwSignal = SETRTS;
						break;

					case 7:
						dwSignal = SETXOFF;
						break;

					case 8:
						dwSignal = SETXON;
						break;

					case 9:
						dwSignal = RESETDEV;
				}

				if ( !m_SBW.Signal ( dwSignal ) ) {
					MessageBox ( m_clString[IDS_SETDEVNSUC], m_clString[IDS_ERROR2], MB_OK );
				}
			}

			else {
				MessageBox ( m_clString[IDS_USEMENUSELI], m_clString[IDS_INFO2], MB_OK );
			}

			break;
	}
}

void CSBWAppDlg::OnReset ( )
{
	m_SBW.SendReset ( );
}

void CSBWAppDlg::OnlyNumber ( CEdit *pObj, long minv, long maxv )
{
	CString NewStr, Str;

	if ( pObj == NULL ) {
		return;
	}

	pObj->GetWindowText ( Str );
	NewStr = Str;

	for ( int i = 0; i < NewStr.GetLength ( ); i++ ) {
		if ( ! ( ( ( NewStr.GetAt ( i ) > 47 ) && ( NewStr.GetAt ( i ) < 58 ) ) || ( ( NewStr.GetAt ( i ) == 45 ) && ( i == 0 ) ) ) ) {
			NewStr.Delete ( i );
			i = 0;
		}
	}

	while ( NewStr.Replace ( _T ( "--" ), _T ( "-" ) ) != 0 ) {
	}

	if ( NewStr != _T ( "-" ) ) {
		TCHAR *stopstring;
		long lVal = _tcstol ( NewStr.GetBuffer ( ), &stopstring, 10 );

		if ( lVal < minv ) {
			NewStr = _T ( "0" );
		}

		else if ( lVal > maxv ) {
			NewStr = _T ( "255" );
		}
	}

	if ( NewStr != Str ) {
		pObj->SetWindowText ( NewStr );
		pObj->SetSel ( 255, 255, TRUE );
	}
}

void CSBWAppDlg::OnThresSel ( )
{
	short sValue = 0;

	switch ( m_ctrlThresSel.GetCurSel ( ) ) {
		case 0:
			sValue = m_clThreshold[XTRA];
			break;

		case 1:
			sValue = m_clThreshold[YTRA];
			break;

		case 2:
			sValue = m_clThreshold[ZTRA];
			break;

		case 3:
			sValue = m_clThreshold[XROT];
			break;

		case 4:
			sValue = m_clThreshold[YROT];
			break;

		case 5:
			sValue = m_clThreshold[ZROT];
			break;
	}

	m_ctrlThres.SetValue ( sValue, 0 );
}

void CSBWAppDlg::OnUpdateThres ( )
{
	short sValue = ( short ) m_ctrlThres.GetIValue ( );

	switch ( m_ctrlThresSel.GetCurSel ( ) ) {
		case 0:
			m_clThreshold[XTRA] = sValue;
			break;

		case 1:
			m_clThreshold[YTRA] = sValue;
			break;

		case 2:
			m_clThreshold[ZTRA] = sValue;
			break;

		case 3:
			m_clThreshold[XROT] = sValue;
			break;

		case 4:
			m_clThreshold[YROT] = sValue;
			break;

		case 5:
			m_clThreshold[ZROT] = sValue;
			break;
	}
}

void CSBWAppDlg::OnMovAverage ( )
{
	if ( m_ctrlMovAverage.GetCheck ( ) == BST_CHECKED ) {
		m_clCriSec.Lock ( );

		for ( int iMov = 0; iMov < 6; iMov++ ) {
			m_bMoving_State_Ball2[iMov].clear ( );
		}

		m_clCriSec.Unlock ( );

		ZeroMemory ( &m_bNotAllowNewTimer, sizeof ( m_bNotAllowNewTimer ) );
		ZeroMemory ( &m_bCurrent_State_Ball, sizeof ( m_bCurrent_State_Ball ) );
		ZeroMemory ( &m_bFinal_State_Ball, sizeof ( m_bFinal_State_Ball ) );
		ZeroMemory ( &m_bPrevious_Final_State_Ball, sizeof ( m_bPrevious_Final_State_Ball ) );

		m_ctrlPulse.EnableWindow ( );
		m_ctrlTimValue.EnableWindow ( );
		m_ctrlNLength.EnableWindow ( );
		m_ctrlSMAThres.EnableWindow ( );
	}

	else {
		ZeroMemory ( &m_bCurrent_State_Ball, sizeof ( m_bCurrent_State_Ball ) );
		m_ctrlPulse.EnableWindow ( FALSE );
		m_ctrlTimValue.EnableWindow ( FALSE );
		m_ctrlNLength.EnableWindow ( FALSE );
		m_ctrlSMAThres.EnableWindow ( FALSE );
	}
}

void CSBWAppDlg::OnUpdateFreq ( )
{
	double iFreq = m_ctrlFreq.GetDValue ( );

	if ( iFreq != m_iFreq ) {
		m_iFreq = iFreq;

		if ( m_uipTimer ) {
			m_uipTimer = 0;
			KillTimer ( ID_TIMER );
		}

		m_uipTimer = SetTimer ( ID_TIMER, ( UINT ) ( ( 1.0 / m_iFreq ) * 1000.0 ), NULL );
	}
}

void CSBWAppDlg::OnUpdateMovAverPeriod ( )
{
	//int iPeriod = ( int ) m_ctrlTimValue.GetIValue ( );

	/*if ( iPeriod != m_iPeriod ) {
		m_iPeriod = iPeriod;
	}*/
}

void CSBWAppDlg::OnNElements ( NMHDR *pNMHDR, LRESULT *pResult )
{
	UNREFERENCED_PARAMETER ( pNMHDR );
	//	m_iLength = m_ctrlNLength.GetPos ( );
	*pResult = 0;
}

void CSBWAppDlg::OnSMAThresUpdate ( )
{
	m_dSMAThres = m_ctrlSMAThres.GetDValue ( );
}

void CSBWAppDlg::Set ( bool *pb, int len1, int len2, ... )
{
	int iItem;
	va_list argptr;
	va_start ( argptr, len2 );

	for ( int i = 0; i < len1; i++ ) {
		iItem = va_arg ( argptr, int );

		if ( ( iItem >= 0 ) && ( iItem < 6 ) ) {
			pb[iItem] = false;
		}
	}

	for ( int i = 0; i < len2; i++ ) {
		iItem = va_arg ( argptr, int );

		if ( ( iItem >= 0 ) && ( iItem < 6 ) ) {
			pb[iItem] = true;
		}
	}

	va_end ( argptr );
}

void CSBWAppDlg::OnUpdatePeroffset ( )
{
	if ( m_bEnableUpdateOffsetData ) {
		if ( MessageBox ( m_clString[IDS_MSG1], m_clString[IDS_INFO],
						  MB_OKCANCEL | MB_DEFBUTTON2 | MB_APPLMODAL | MB_ICONEXCLAMATION ) == IDOK ) {
			m_SBW.m_stOffset.lPeriod = (long) m_ctrlPeriodOffset.GetIValue ( );
		}

		else {
			m_bEnableUpdateOffsetData = false;
			m_ctrlPeriodOffset.SetValue ( m_SBW.m_stOffset.lPeriod, 0 );
			m_bEnableUpdateOffsetData = true;
		}
	}

	else {
		m_SBW.m_stOffset.lPeriod = (long) m_ctrlPeriodOffset.GetIValue ( );
	}
}

void CSBWAppDlg::OnUpdateXtoffset ( )
{
	if ( m_bEnableUpdateOffsetData ) {
		if ( MessageBox ( m_clString[IDS_MSG1], m_clString[IDS_INFO],
						  MB_OKCANCEL | MB_DEFBUTTON2 | MB_APPLMODAL | MB_ICONEXCLAMATION ) == IDOK ) {
			m_SBW.m_stOffset.lXTrans = (long) m_ctrlXTranOffset.GetIValue ( );
		}

		else {
			m_bEnableUpdateOffsetData = false;
			m_ctrlXTranOffset.SetValue ( m_SBW.m_stOffset.lXTrans, 0 );
			m_bEnableUpdateOffsetData = true;
		}
	}

	else {
		m_SBW.m_stOffset.lXTrans = (long) m_ctrlXTranOffset.GetIValue ( );
	}
}

void CSBWAppDlg::OnUpdateYtoffset ( )
{
	if ( m_bEnableUpdateOffsetData ) {
		if ( MessageBox ( m_clString[IDS_MSG1], m_clString[IDS_INFO],
						  MB_OKCANCEL | MB_DEFBUTTON2 | MB_APPLMODAL | MB_ICONEXCLAMATION ) == IDOK ) {
			m_SBW.m_stOffset.lYTrans = (long) m_ctrlYTranOffset.GetIValue ( );
		}

		else {
			m_bEnableUpdateOffsetData = false;
			m_ctrlYTranOffset.SetValue ( m_SBW.m_stOffset.lYTrans, 0 );
			m_bEnableUpdateOffsetData = true;
		}
	}

	else {
		m_SBW.m_stOffset.lYTrans = (long) m_ctrlYTranOffset.GetIValue ( );
	}
}

void CSBWAppDlg::OnUpdateZtoffset ( )
{
	if ( m_bEnableUpdateOffsetData ) {
		if ( MessageBox ( m_clString[IDS_MSG1], m_clString[IDS_INFO],
						  MB_OKCANCEL | MB_DEFBUTTON2 | MB_APPLMODAL | MB_ICONEXCLAMATION ) == IDOK ) {
			m_SBW.m_stOffset.lZTrans = (long) m_ctrlZTranOffset.GetIValue ( );
		}

		else {
			m_bEnableUpdateOffsetData = false;
			m_ctrlZTranOffset.SetValue ( m_SBW.m_stOffset.lZTrans, 0 );
			m_bEnableUpdateOffsetData = true;
		}
	}

	else {
		m_SBW.m_stOffset.lZTrans = (long) m_ctrlZTranOffset.GetIValue ( );
	}
}

void CSBWAppDlg::OnUpdateXroffset ( )
{
	if ( m_bEnableUpdateOffsetData ) {
		if ( MessageBox ( m_clString[IDS_MSG1], m_clString[IDS_INFO],
						  MB_OKCANCEL | MB_DEFBUTTON2 | MB_APPLMODAL | MB_ICONEXCLAMATION ) == IDOK ) {
			m_SBW.m_stOffset.lXRot = (long) m_ctrlXRotOffset.GetIValue ( );
		}

		else {
			m_bEnableUpdateOffsetData = false;
			m_ctrlXRotOffset.SetValue ( m_SBW.m_stOffset.lXRot, 0 );
			m_bEnableUpdateOffsetData = true;
		}
	}

	else {
		m_SBW.m_stOffset.lXRot = (long) m_ctrlXRotOffset.GetIValue ( );
	}
}

void CSBWAppDlg::OnUpdateYroffset ( )
{
	if ( m_bEnableUpdateOffsetData ) {
		if ( MessageBox ( m_clString[IDS_MSG1], m_clString[IDS_INFO],
						  MB_OKCANCEL | MB_DEFBUTTON2 | MB_APPLMODAL | MB_ICONEXCLAMATION ) == IDOK ) {
			m_SBW.m_stOffset.lYRot = (long) m_ctrlYRotOffset.GetIValue ( );
		}

		else {
			m_bEnableUpdateOffsetData = false;
			m_ctrlYRotOffset.SetValue ( m_SBW.m_stOffset.lYRot, 0 );
			m_bEnableUpdateOffsetData = true;
		}
	}

	else {
		m_SBW.m_stOffset.lYRot = (long) m_ctrlYRotOffset.GetIValue ( );
	}
}

void CSBWAppDlg::OnUpdateZroffset ( )
{
	if ( m_bEnableUpdateOffsetData ) {
		if ( MessageBox ( m_clString[IDS_MSG1], m_clString[IDS_INFO],
						  MB_OKCANCEL | MB_DEFBUTTON2 | MB_APPLMODAL | MB_ICONEXCLAMATION ) == IDOK ) {
			m_SBW.m_stOffset.lZRot = (long) m_ctrlZRotOffset.GetIValue ( );
		}

		else {
			m_bEnableUpdateOffsetData = false;
			m_ctrlZRotOffset.SetValue ( m_SBW.m_stOffset.lZRot, 0 );
			m_bEnableUpdateOffsetData = true;
		}
	}

	else {
		m_SBW.m_stOffset.lZRot = (long) m_ctrlZRotOffset.GetIValue ( );
	}
}

void CSBWAppDlg::OnBnClicked1DoF ( )
{
	m_iDoF = 0;
}

void CSBWAppDlg::OnBnClicked2DoF ( )
{
	m_iDoF = 1;
}

void CSBWAppDlg::OnBnClicked4DoF ( )
{
	m_iDoF = 2;
}

void CSBWAppDlg::OnBnClickedTranslation ( )
{
	m_iFreedMov = 0;
}

void CSBWAppDlg::OnBnClickedRotation ( )
{
	m_iFreedMov = 1;
}

void CSBWAppDlg::OnBnClickedBoth ( )
{
	m_iFreedMov = 2;
}

void CSBWAppDlg::OnBnClickedAbremap ( )
{
	if ( m_ctrlRemapAB.GetCheck ( ) == BST_CHECKED ) {
		m_ctrlBeep.EnableWindow ( );
	}

	else {
		m_ctrlBeep.EnableWindow ( FALSE );
	}
}

void CSBWAppDlg::OnBnClickedBroadcastmsg ( )
{
	if ( m_ctrlBroadcast.GetCheck ( ) == BST_UNCHECKED ) {
		m_ctrlTextToFind.EnableWindow ( );
	}

	else {
		m_ctrlTextToFind.EnableWindow ( FALSE );
	}
}

BOOL CALLBACK EnumWindowsProc ( HWND hwnd, LPARAM lParam )
{
	CSBWAppDlg *pObj = reinterpret_cast <CSBWAppDlg *> (lParam);

	if ( pObj ) {
		CString Temp, Str;
		pObj->m_ctrlTextToFind.GetWindowText ( Str );

		if ( !Str.IsEmpty ( ) ) {
			GetWindowText ( hwnd, Temp.GetBuffer ( 256 ), 255 );

			if ( Temp.Find ( Str ) != -1 ) {
				pObj->m_hTargetWindow = hwnd;
				Temp.Format ( _T ( "%p" ), hwnd );
				pObj->m_ctrlHandle.SetWindowText ( Temp );
				return FALSE;
			}
		}
	}

	return TRUE;
}

void CSBWAppDlg::OnEnUpdateTexttofind ( )
{
	m_hTargetWindow = NULL;
	EnumDesktopWindows ( NULL, EnumWindowsProc, ( LPARAM ) this );

	if ( m_hTargetWindow == NULL ) {
		CString Str;
		m_ctrlHandle.SetWindowText ( m_clString[0] );
		m_ctrlTextToFind.GetWindowText ( Str );

		if ( !Str.IsEmpty ( ) ) {
			FindWindowEx ( NULL, NULL, Str, NULL );
		}
	}
}

void CSBWAppDlg::OnBnClickedBallkeystroke ( )
{
	if ( m_ctrlBallKeystroke.GetCheck ( ) == BST_CHECKED ) {
		m_ctrlBroadcast.EnableWindow ( );
		m_ctrlFlashWin.EnableWindow (  );
		OnBnClickedBroadcastmsg ( );
	}

	else {
		m_ctrlTextToFind.EnableWindow ( FALSE );
		m_ctrlBroadcast.EnableWindow ( FALSE );
		m_ctrlFlashWin.EnableWindow ( FALSE );
	}
}


void CSBWAppDlg::OnFlashWin ( )
{
	if ( m_hTargetWindow != NULL ) {
		if ( IsWindow ( m_hTargetWindow ) == TRUE ) {
			m_bCanNewWindow = true;
			FLASHWINFO sFlWin = { 0 };
			sFlWin.cbSize = sizeof ( FLASHWINFO );
			sFlWin.dwFlags = FLASHW_ALL;
			sFlWin.dwTimeout = 250;
			sFlWin.hwnd = m_hTargetWindow;
			sFlWin.uCount = 4;
			::FlashWindowEx ( &sFlWin );
			return;
		}
	}

	if ( m_bCanNewWindow ) {
		m_bCanNewWindow = false;
		MessageBox ( m_clString[IDS_INVWIN], m_clString[IDS_ERROR2], MB_OK );
		m_bCanNewWindow = true;
	}
}

void CSBWAppDlg::OnBnClickedAppend ( )
{
	if ( m_ctrlAppendRead.GetCheck ( ) == BST_UNCHECKED ) {
		m_SBW.m_bAppendData = false;
	}

	else {
		m_SBW.m_bAppendData = true;
	}
}

void CSBWAppDlg::OnEnSetfocusStatusbar ( )
{
	SetFocus ( );
}

BOOL CSBWAppDlg::OnSetCursor ( CWnd *pWnd, UINT nHitTest, UINT message )
{
	if ( m_ctrlStatusBar.m_hWnd == pWnd->m_hWnd ) {
		SetCursor ( AfxGetApp ( )->LoadStandardCursor ( IDC_ARROW ) );
		return true;
	}

	return CDialogEx::OnSetCursor ( pWnd, nHitTest, message );
}

LRESULT CSBWAppDlg::OnSbExplorerQuery ( WPARAM wParam, LPARAM lParam )
{
	UNREFERENCED_PARAMETER ( lParam );
	return SendBallKeystrokes ( wParam );
}

BOOL CSBWAppDlg::PreTranslateMessage ( MSG *pMsg )
{
	if ( pMsg->message == WM_KEYDOWN ) {
		if ( ( pMsg->wParam == VK_RETURN ) || ( pMsg->wParam == VK_ESCAPE ) ) {
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage ( pMsg );
}

__int64 CSBWAppDlg::EncodeBits ( __int64 val, int nbits, int vbits, int nstep ) {
	__int64 newval = 0LL;
	int i = 0, j = 0, k = 0;

	while ( j < 64 ) {
		__int64 temp = val >> j++;

		if ( temp ) {
			newval |= ( ( temp & 1LL ) << i++ );

			if ( i == ( ( k * nbits ) + ( ( k + 1 ) * vbits ) ) ) {
				k++;
				i = i + nbits;
			}
		}

		else {
			break;
		}
	}

	return newval;
}
