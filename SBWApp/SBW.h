/*
	 This file is subject to the terms and conditions defined in
	 file 'LICENSE.txt', which is part of this source code package.
	 Copyright (C) 2014 Ricardo B. Santos.
	 All rights reserved
*/

#pragma once

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <intrin.h>

using namespace std;

//using namespace std;
/*
						3			     1	            0
						1			     5              0
						----------------------------------
	 vector 1			XXXXXXXXXXXXXXXX RMMMMMMMMMOOOOOO
										 RMag.	   Orie.
	 Forward								       000001
	 Back										   000010
	 Right								           000100
	 Left										   001000
	 Up										       010000
	 Down										   100000
						---------------------------------
						RMMMMMMMMMRRRRRR XXXXXXXXXXXXXXXX
						RMag      Rot.
	 XRot	  	          		  000001
								  000010
	 YRot			          	  000100
								  001000
	 ZRot		          		  010000
								  100000
*/

#define SBE_TRANS_MASK			0x3F
#define SBE_FORWARD				1
#define SBE_BACK				2
#define SBE_RIGHT 				4
#define SBE_LEFT 				8
#define SBE_UP   				16
#define SBE_DOWN 				32

#define SBE_ROT_MASK			0x3F0000
#define SBE_XROT_1				0x10000
#define SBE_XROT_2				0x20000
#define SBE_YROT_1 				0x40000
#define SBE_YROT_2				0x80000
#define SBE_ZROT_1				0x100000
#define SBE_ZROT_2				0x200000

#define SBE_MESSAGE				(WM_APP+1)

#define SBE_MAXBUF_SIZE			8192
#define SBE_READ_TIMEOUT		500
#define SBE_MUTEX_TIMEOUT		INFINITE
#define SBE_STATUS_TIMEOUT	    500

#define SBE_XTRANS				0
#define SBE_YTRANS              1
#define SBE_ZTRANS              2
#define SBE_XROT                3
#define SBE_YROT                4
#define SBE_ZROT                5

#define SBE_BUTTON_1		0
#define SBE_BUTTON_2		1
#define SBE_BUTTON_3		2
#define SBE_BUTTON_4		3
#define SBE_BUTTON_5		4
#define SBE_BUTTON_6		5
#define SBE_BUTTON_7		6
#define SBE_BUTTON_8		7
#define SBE_BUTTON_9		8
#define SBE_BUTTON_A		9
#define SBE_BUTTON_B		10
#define SBE_BUTTON_C		11

#define SBE_PRESTATUS_COMM		(1<<16)
#define SBE_STATUS_COMM         (2<<16)
#define SBE_RESET_COMM          (3<<16)
#define SBE_CLOSE_COMM          (4<<16)
#define SBE_READ_COMM           (5<<16)
#define SBE_WRITE_COMM          (6<<16)
#define SBE_COMMAND_COMM        (7<<16)
#define SBE_UNKNOWN_COMM        (8<<16)
#define SBE_NULL_COMM           (9<<16)

#define SBE_WRITE_NUL	  	0
#define SBE_WRITE_SUCC_IME	1
#define SBE_WRITE_SUCC		2
#define SBE_WRITE_PEN_ERR	-2
#define SBE_WRITE_FAILED	-1

#define SBE_COMMAND_NUL	    0	// null
#define SBE_COMMAND_ECH	    1	// echo
#define SBE_COMMAND_INV	    2	// invalid
#define SBE_COMMAND_IGN	    3	// ignore
#define SBE_COMMAND_RES	    4	// @ reset
#define SBE_COMMAND_DBQ   	5	// "
#define SBE_COMMAND_INT	    6	// initial invalid sequence
#define SBE_COMMAND_PNT	    7	// .
#define SBE_COMMAND_A		8
#define SBE_COMMAND_B		9
#define SBE_COMMAND_C		10
#define SBE_COMMAND_D		11
#define SBE_COMMAND_E		12
#define SBE_COMMAND_F		13
#define SBE_COMMAND_H		14
#define SBE_COMMAND_K		15
#define SBE_COMMAND_M		16
#define SBE_COMMAND_N		17
#define SBE_COMMAND_O		18
#define SBE_COMMAND_P		19
#define SBE_COMMAND_R		20
#define SBE_COMMAND_S		21
#define SBE_COMMAND_T		22
#define SBE_COMMAND_X		23
//#define SBE_COMMAND_Y	24
#define SBE_COMMAND_Z		25

#define SBE_SERIAL_RXCHAR		0  // Any Character received
#define SBE_SERIAL_RXFLAG		1  // Received certain character
#define SBE_SERIAL_TXEMPTY	    2  // Transmit Queue Empty
#define SBE_SERIAL_CTS			3  // CTS changed state
#define SBE_SERIAL_DSR			4  // DSR changed state
#define SBE_SERIAL_RLSD			5  // RLSD changed state
#define SBE_SERIAL_BREAK		6  // BREAK received
#define SBE_SERIAL_ERR			7  // Line status error occurred
#define SBE_SERIAL_RING			8  // Ring signal detected
#define SBE_SERIAL_PERR			9  // Printer error occurred
#define SBE_SERIAL_RX80FULL     10 // Receive buffer is 80 percent full
#define SBE_SERIAL_EVENT1		11 // Provider specific event 1
#define SBE_SERIAL_EVENT2		12 // Provider specific event 2

#define SBE_SERIAL_RXOVER		13  // Receive Queue overflow
#define SBE_SERIAL_OVERRUN	    14  // Receive Overrun Error
#define SBE_SERIAL_RXPARITY     15  // Receive Parity Error
#define SBE_SERIAL_FRAME		16  // Receive Framing error
#define SBE_SERIAL_BREAK2		17  // Break Detected

unsigned short LittleEndian2Big ( unsigned short sVal );

UINT StatusThreadProc ( LPVOID pParam );
UINT WriteThreadProc ( LPVOID pParam );
UINT CloseThreadProc ( LPVOID pParam );

class SBW {
	private:
		CCriticalSection      m_clCriSec;
		DWORD                 m_dwBufSize;
		INT_PTR               m_iInitiated;
		ULONGLONG	          m_ullTimeCounter;
		ULONGLONG		      m_ullTimeout;
	public:
		SBW();
		~SBW();

		struct STATUS
		{
			bool Reg[ 18 ];
			DWORD dwInQue;
			DWORD dwOutQue;
		};

		#pragma pack(1)
		struct _stProperties {
			size_t dwSize;
			struct absolut_rot_matrix {
				bool bEnable;
				unsigned short sValue[ 3 ];
			} AbsoluteRotMatrix;
			struct beeper {
				bool bEnable;
				BYTE cValue[ 30 ];
			} Beeper;
			struct threshold {
				bool bEnable;
				BYTE cValue;
			} Threshold;
			struct trans_sensitivities {
				bool bEnable;
				unsigned short sValue[ 3 ];
			} TransSensitivities;
			struct responsiveness {
				bool bEnable;
				unsigned short sMaximum;
				struct minimum {
					bool bEnable;
					unsigned short sValue;
				} Minimum;
			} Responsiveness;
			struct resp_multip {
				struct translation {
					bool bEnable;
					BYTE cValue;
				} Translation;
				struct rotation {
					bool bEnable;
					BYTE cValue;
				} Rotation;
			} ResponMultiplier;
			struct spin_rate {
				bool bEnable;
				BYTE cMantissa;
				BYTE cExponent;
			}	SpinRate;
			struct trans_mode {
				bool bEnable;
				BYTE cBallSystem;
				BYTE cFreedomVector;
				BYTE cOutput;
				struct vector {
					bool bEnable;
					unsigned short sValue[ 3 ];
				} Vector;
			} TranslationMode;
			struct rot_mode {
				bool bEnable;
				BYTE cBallSystem;
				BYTE cFreedomVector;
				BYTE cOutput;
				struct vector {
					bool bEnable;
					unsigned short sValue[ 3 ];
				} Vector;
			} RotationMode;
			struct mode {
				bool bEnable;
				BYTE  cTranslationFreedom;
				struct rot {
					bool bEnable;
					BYTE cRotationFreedom;
					struct dat_form {
						bool bEnable;
						BYTE cDataType;
						struct handedness {
							bool bEnable;
							bool bLeftHanded;
							struct prepost_proc {
								bool bEnable;
								BYTE cValue;
							} PrePostProc;
						} Handedness;
					} DataForm;
				} Rotation;
			} Mode;
			struct orient_matrix {
				bool bEnable;
				unsigned short sValue[ 3 ];
			} OrientationMatrix;
			struct zero {
				bool bEnable;
			} Zero;
			struct comm_mode {
				bool bEnable;
				BYTE cValue;
			} CommunicationMode;
		};
		#pragma pack()

		void GetTYPEAt (vector <BYTE>  &Src, INT_PTR nIndex, INT_PTR offset, int &Val);
		void GetTYPEAt (vector <BYTE>  &Src, INT_PTR nIndex, INT_PTR offset, short &Val);
		void GetTYPEAt (vector <BYTE>  &Src, INT_PTR nIndex, INT_PTR offset, unsigned short &Val);

		bool AddCMDs ( vector <BYTE>  &Arr );
		bool CloseRequest ( );
		bool Lock_Write ( );
		bool SendMessage ( DWORD dwCommand, LPARAM lParam );
		bool Signal ( DWORD dwSignal );
		bool TranslateStatus ( DWORD dwCommEvent, bool &bClearComm );
		bool Unlock_Write ( );
		bool Write ( );
		DWORD Read ( DWORD dwSize, DWORD dwRetries = 3, DWORD dwSleep = 500 );
		int Connect ( HWND hWnd, CString sPort, DWORD dwBufSize );
		int Disconnect ( );
		INT_PTR GetCommand ( INT_PTR &iIndex, void **ppData, INT_PTR &iLastCommand );
		void AbortCloseRequest ( );
		void Add ( vector <BYTE>  &v, BYTE *ptr, int size );
		void AddInfo ( string &clStr );
		void ClearCMDs ( );
		void Escape (vector <BYTE>  &clData);
		void GetHexCMDs ( CString &Str );
		void Replace (vector <BYTE>  &vect, vector <BYTE>  &sub, vector <BYTE>  &newsub);
		void SendCMDs ( );
		void SendReset ( );
		void SendResetAfterTimeout ( );
		void StringA ( string &Src, vector <BYTE>  &Dest, bool append = false );
		void StringA (vector <BYTE>  &Src, string &Dest, BYTE NoPrintCharSubst = 63);
		void EncodeCommands ( _stProperties &Prop, vector <BYTE> &Arr, bool bAddCr );

		__int64       m_iBytesRead;
		__int64       m_iBytesWritten;
		bool          m_bAbortCloseProc;
		bool          m_bAbortStatusProc;
		bool          m_bAbortWriteProc;
		bool          m_bAppendData;
		bool          m_bAutoClearBREAK;
		CStringA      m_clDeviceInfo;
		CWinThread	 *m_pStThread;
		CWinThread	 *m_pWrThread;
		DWORD         m_dwCommand;
		DWORD         m_dwLastCommand;
		HANDLE        m_hComm;
		HANDLE        m_hProcWriEv;
		HWND          m_hWnd;
		INT_PTR	      m_iLastWriteStatus;
		OVERLAPPED    m_stIO;
		STATUS        m_stStatus;
		string	      m_clInitializationString;
		vector <BYTE> m_clDelimiter;
		vector <BYTE> m_clRAWData;
		vector <BYTE> m_cl_In;
		vector <BYTE> m_clSentence;
		vector <BYTE> m_cl_Out;
		vector <BYTE> m_clBuffer;

		struct _stButtons {
			bool bButton_SB3000[8];
			bool bButton_SB4000FLX[12];
			bool bButton_PreviousState_SB3000[8];
			bool bButton_PreviousState_SB4000FLX[12];
		} m_stButtons;

		struct _stCoord {
			bool	bPeriod;
			bool	bXTrans;
			bool	bYTrans;
			bool	bZTrans;
			bool	bXRot;
			bool	bYRot;
			bool	bZRot;

			unsigned short	sCurrent_Period;
			short	sCurrent_XTrans;
			short	sCurrent_YTrans;
			short	sCurrent_ZTrans;
			short	sCurrent_XRot;
			short	sCurrent_YRot;
			short	sCurrent_ZRot;

			unsigned short	sPrevious_Period;
			short	sPrevious_XTrans;
			short	sPrevious_YTrans;
			short	sPrevious_ZTrans;
			short	sPrevious_XRot;
			short	sPrevious_YRot;
			short	sPrevious_ZRot;
		} m_stCoord;

		struct _stOffset {
			long lPeriod;
			long lXTrans;
			long lYTrans;
			long lZTrans;
			long lXRot;
			long lYRot;
			long lZRot;
		} m_stOffset;

		int iCMDsCounter;
		BYTE pbCMDs[1024];
};
