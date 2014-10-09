/*
This file is subject to the terms and conditions defined in
file 'LICENSE.txt', which is part of this source code package.
Copyright (C) 2013 Ricardo B. Santos.
All rights reserved
*/

#include "stdafx.h"
#include "SBW.h"

const DWORD MS_VC_EXCEPTION = 0x406D1388;

#pragma pack(push,8)
typedef struct tagTHREADNAME_INFO {
	DWORD dwType; // Must be 0x1000.
	LPCSTR szName; // Pointer to name (in user addr space).
	DWORD dwThreadID; // Thread ID (-1=caller thread).
	DWORD dwFlags; // Reserved for future use, must be zero.
} THREADNAME_INFO;
#pragma pack(pop)

void SetThreadName ( DWORD dwThreadID, char *threadName )
{
	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = threadName;
	info.dwThreadID = dwThreadID;
	info.dwFlags = 0;

	__try {
		RaiseException ( MS_VC_EXCEPTION, 0, sizeof ( info ) / sizeof ( ULONG_PTR ), (ULONG_PTR *) &info );
	}

	__except ( EXCEPTION_EXECUTE_HANDLER ) {}
}

SBW::SBW ( )
{
	m_bAbortStatusProc = false;
	m_bAbortWriteProc  = false;
	m_bAbortCloseProc  = false;
	m_bAppendData      = false;
	m_bAutoClearBREAK  = false;
	m_dwBufSize        = 0;
	m_dwCommand        = SBE_NULL_COMM;
	m_dwLastCommand    = 0;
	m_hComm            = NULL;
	m_hProcWriEv       = NULL;
	m_iBytesRead       = 0;
	m_iBytesWritten    = 0;
	m_iInitiated       = 0;
	m_iLastWriteStatus = SBE_WRITE_NUL;
	m_pStThread        = NULL;
	m_pWrThread        = NULL;
	m_ullTimeCounter   = 0;
	m_ullTimeout       = 1500;

	string delim = "\r"; // "\n\r";
	m_clDelimiter.assign ( delim.begin ( ), delim.end ( ) );

	m_hWnd = NULL;
	ZeroMemory ( &m_stStatus, sizeof ( m_stStatus ) );
	//ZeroMemory ( &m_stSettings, sizeof ( m_stSettings ) );
	ZeroMemory ( &m_stButtons, sizeof ( m_stButtons ) );
	ZeroMemory ( &m_stCoord, sizeof ( m_stCoord ) );

	m_clRAWData.clear( );
	m_cl_In.clear( );
	m_clSentence.clear( );
	m_cl_Out.clear( );
	m_clBuffer.clear( );
}

SBW::~SBW ( ) {}

int SBW::Connect ( HWND hWnd, CString sPort, DWORD dwBufSize )
{
	m_clCriSec.Lock ( );

	if ( hWnd == NULL ) {
		return -1;
	}

	if ( IsWindow ( hWnd ) == FALSE ) {
		return -1;
	}

	m_hWnd = hWnd;

	if ( dwBufSize == 0 ) {
		return -1;
	}

	if ( dwBufSize > SBE_MAXBUF_SIZE ) {
		return -1;
	}

	ZeroMemory ( &m_stCoord, sizeof ( m_stCoord ) );
	ZeroMemory ( &m_stButtons, sizeof ( m_stButtons ) );

	m_iBytesRead = 0;
	m_iBytesWritten = 0;

	m_hComm = CreateFile ( sPort,
						   GENERIC_READ | GENERIC_WRITE,
						   0, 0,
						   OPEN_EXISTING,
						   FILE_FLAG_OVERLAPPED,
						   0 );

	if ( m_hComm == INVALID_HANDLE_VALUE ) {
		return -1;
	}

	DCB dcb = { 0 };

	if ( !GetCommState ( m_hComm, &dcb ) ) {
		CloseHandle ( m_hComm );
		m_hComm = NULL;
		return -1;
	}

	// Update DCB rate.
	dcb.BaudRate    = CBR_9600;
	dcb.fParity     = FALSE;
	dcb.Parity      = NOPARITY;
	dcb.fDtrControl = DTR_CONTROL_HANDSHAKE;
	dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;
	dcb.ByteSize    = 8;
	dcb.StopBits    = ONESTOPBIT;

	// Set new state.
	if ( !SetCommState ( m_hComm, &dcb ) ) {
		CloseHandle ( m_hComm );
		m_hComm = NULL;
		return -1;
	}

	if ( !SetCommMask ( m_hComm, EV_BREAK | EV_CTS | EV_DSR | EV_ERR | EV_RING | EV_RLSD | EV_RXCHAR | EV_RXFLAG |
						EV_TXEMPTY ) ) {
		CloseHandle ( m_hComm );
		m_hComm = NULL;
		return -1;
	}

	m_dwBufSize = dwBufSize;

	try {
		m_clBuffer.resize ( dwBufSize );
	}

	catch ( exception &e ) {
		UNREFERENCED_PARAMETER ( e );
		CloseHandle ( m_hComm );
		m_hComm = NULL;
		return -1;
	}

	m_stIO.Internal     = 0;
	m_stIO.InternalHigh = 0;
	m_stIO.Offset       = 0;
	m_stIO.OffsetHigh   = 0;

	m_stIO.hEvent = CreateEvent ( NULL, TRUE, FALSE, NULL );
	ASSERT ( m_stIO.hEvent );

	m_hProcWriEv = NULL;

	m_cl_In.clear ( );

	m_clDeviceInfo.Empty ( );
	m_ullTimeCounter   = 0;
	m_iInitiated       = 0;
	m_bAbortStatusProc = false;
	m_bAbortWriteProc  = false;

	m_pStThread = AfxBeginThread ( StatusThreadProc, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED );
	m_pStThread->m_bAutoDelete = true;
	SetThreadName ( m_pStThread->m_nThreadID, "Status thread" );
	m_pStThread->ResumeThread ( );

	m_pWrThread = AfxBeginThread ( WriteThreadProc, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED );
	m_pWrThread->m_bAutoDelete = true;
	SetThreadName ( m_pWrThread->m_nThreadID, "Write thread" );
	m_pWrThread->ResumeThread ( );

	SetThreadName ( -1, "Main thread" );

	m_clCriSec.Unlock ( );
	return 0;
}

int SBW::Disconnect ( )
{
	if ( m_hComm == NULL ) {
		return -1;
	}

	m_bAbortStatusProc = true;
	m_bAbortWriteProc  = true;

	if ( m_hProcWriEv ) {
		SetEvent ( m_hProcWriEv );
	}

	m_dwBufSize = 0;
	return 0;
}

UINT CloseThreadProc ( LPVOID pParam )
{
	SBW *Obj = reinterpret_cast <SBW *> ( pParam );

	while ( Obj->m_bAbortCloseProc == false ) {
		if ( WaitForSingleObject ( Obj->m_pWrThread->m_hThread, 200 ) != WAIT_TIMEOUT ) {
			if ( WaitForSingleObject ( Obj->m_pStThread->m_hThread, 200 ) != WAIT_TIMEOUT ) {
				Obj->m_pWrThread = NULL;
				Obj->m_pStThread = NULL;
				::SendMessage ( Obj->m_hWnd, SBE_MESSAGE, SBE_CLOSE_COMM, 0 );
				return 1;
			}
		}
	}

	return 0;
}

bool SBW::CloseRequest (  )
{
	if ( ( m_pWrThread == NULL ) || ( m_pStThread == NULL ) ) {
		return false;
	}

	m_bAbortCloseProc = false;
	CWinThread *m_pClThread = AfxBeginThread ( CloseThreadProc, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED );
	m_pClThread->m_bAutoDelete = true;
	SetThreadName ( m_pClThread->m_nThreadID, "Close thread" );
	m_pClThread->ResumeThread ( );
	return true;
}

void SBW::AbortCloseRequest ( )
{
	m_bAbortCloseProc = true;
}

DWORD SBW::Read ( DWORD dwSize, DWORD dwRetries, DWORD dwSleep )
{
	OVERLAPPED stOv   = { 0 };
	DWORD dwBytesRead = 0;
	DWORD dwError     = 0;
	DWORD dwRetry1, dwRetry2;
	BOOL bContinue, bPending;
	dwRetry1 = dwRetry2 = 0;
	bContinue = bPending = TRUE;

	if ( m_hComm == NULL ) {
		return 0;
	}

	stOv.hEvent = CreateEvent ( NULL, TRUE, FALSE, NULL );

	if ( stOv.hEvent == NULL ) {
		return 0;
	}

	//m_cl_In.clear();

	while ( bContinue ) {
		// Default to ending the loop.
		bContinue = FALSE;
		dwBytesRead = 0;

		//try {
		if ( ReadFile ( m_hComm, &m_clBuffer[0], m_dwBufSize > dwSize ? dwSize : m_dwBufSize, &dwBytesRead, &stOv ) == FALSE ) {
			dwError = GetLastError ( );

			switch ( dwError ) {
				case ERROR_HANDLE_EOF: {
						TRACE ( "\nReadFile returned FALSE and EOF condition, async EOF not triggered.\n" );
						break;
					}

				case ERROR_IO_PENDING: {
						bPending = TRUE;

						while ( bPending ) {
							switch ( WaitForSingleObject ( stOv.hEvent, SBE_READ_TIMEOUT ) ) {
								// Read completed.
								case WAIT_OBJECT_0: {
										bPending = FALSE;

										if ( GetOverlappedResult ( m_hComm, &stOv, &dwBytesRead, FALSE ) == FALSE ) {
											switch ( dwError = GetLastError ( ) ) {
												case ERROR_HANDLE_EOF: {
														m_cl_In.insert ( m_cl_In.end ( ), m_clBuffer.begin ( ), m_clBuffer.begin ( ) + dwBytesRead );
														ResetEvent ( stOv.hEvent );
														break;
													}

												case ERROR_IO_INCOMPLETE: {
														m_cl_In.insert ( m_cl_In.end ( ), m_clBuffer.begin ( ), m_clBuffer.begin ( ) + dwBytesRead );
														bPending = TRUE;
														bContinue = TRUE;
														break;
													}

												default: {
														TRACE ( _T ( "GetOverlappedResult failed (%d): %s\n" ), dwError );
													}
											}
										}

										else {
											m_cl_In.insert ( m_cl_In.end ( ), m_clBuffer.begin ( ), m_clBuffer.begin ( ) + dwBytesRead );
											ResetEvent ( stOv.hEvent );
										}

										break;
									}

								case WAIT_TIMEOUT: {
										// This is a good time to do some background work.
										Sleep ( dwSleep );
										dwRetry1++;

										if ( dwRetries <= dwRetry1 ) {
											bPending = FALSE;
										}

										break;
									}

								default:
									// Error in the WaitForSingleObject; abort. This indicates a problem with the
									// OVERLAPPED structure's event handle.
									break;
							}
						}

						break;
					}

				default: {
						TRACE ( "ReadFile GLE unhanded (%d)\n", dwError );
						break;
					}
			}
		}

		else {

			m_cl_In.insert ( m_cl_In.end ( ), m_clBuffer.begin ( ), m_clBuffer.begin ( ) + dwBytesRead );

			ResetEvent ( stOv.hEvent );
		}

		/*}
		catch ( const std::out_of_range &e ) {
		}*/

		m_iBytesRead += dwBytesRead;

		CloseHandle ( stOv.hEvent );
		// The following operation assumes the file is not extremely large, otherwise
		// logic would need to be included to adequately account for very large
		// files and manipulate the OffsetHigh member of the OVERLAPPED structure.
		stOv.Offset += dwBytesRead;
		bContinue = FALSE;

		if ( stOv.Offset < dwSize ) {
			dwRetry1 = 0;
			dwRetry2++;

			if ( dwRetries > dwRetry2 ) {
				stOv.hEvent = CreateEvent ( NULL, TRUE, FALSE, NULL );

				if ( stOv.hEvent != NULL ) {
					bContinue = TRUE;
				}
			}
		}
	}

	return stOv.Offset;
}

bool SBW::Write ( )
{
	return Unlock_Write ( );
}

bool SBW::TranslateStatus ( DWORD dwCommEvent, bool &bClearComm )
{
	bool bDataAvailable = bClearComm = false;
	COMSTAT stComStat   = { 0 };
	DWORD   dwError     = 0;

	ZeroMemory ( &m_stStatus, sizeof ( m_stStatus ) );
	ZeroMemory ( &stComStat, sizeof ( stComStat ) );

	for ( INT_PTR R = 0; R < 18; R++ ) {
		m_stStatus.Reg[R] = ( ( dwCommEvent & 0x00001FFF ) >> R ) & 0x00000001 ? true : false;
	}

	if ( ClearCommError ( m_hComm, &dwError, &stComStat ) == TRUE ) {
		for ( INT_PTR R = 0; R < 5; R++ ) {
			m_stStatus.Reg[R + 13] = ( ( dwError & 0x0000001F ) >> R ) & 0x00000001 ? true : false;
		}

		m_stStatus.dwInQue = stComStat.cbInQue;
		m_stStatus.dwOutQue = stComStat.cbOutQue;
	}

	else {
		m_stStatus.dwInQue = 0;
		m_stStatus.dwOutQue = 0;
		TRACE ( "\nError: %d  ", GetLastError ( ) );
	}

	m_stStatus.dwInQue = stComStat.cbInQue;
	m_stStatus.dwOutQue = stComStat.cbOutQue;

	if ( m_stStatus.Reg[SBE_SERIAL_RXCHAR] && ( m_stStatus.dwInQue > 0 ) /* | m_stStatus.Reg[SERIAL_RXFLAG]*/ ) {
		bDataAvailable = true;
	}

	if ( m_stStatus.Reg[SBE_SERIAL_BREAK] )
		if ( m_bAutoClearBREAK ) {
			bClearComm = true;
		}

	return bDataAvailable;
}

unsigned short LittleEndian2Big ( unsigned short sVal )
{
	return ( ( sVal & 0xFF00 ) >> 8 ) | ( ( sVal & 0xFF ) << 8 );
}

void SBW::Add ( vector <BYTE>  &v, BYTE *ptr, int size)
{
	v.insert ( v.end ( ), ptr, ptr + size );
}

void SBW::EncodeCommands ( _stProperties &Prop, vector <BYTE>  &Arr, bool bAddCr )
{
	unsigned short sVal;
	Arr.clear ( );

	if ( Prop.Threshold.bEnable ) {
		StringA ( string ( "N" ), Arr, true );
		Add ( Arr, (BYTE *) &Prop.Threshold.cValue, sizeof ( Prop.Threshold.cValue ) );

		if ( bAddCr ) {
			StringA ( string ( "\r" ), Arr, true );
		}
	}

	//
	if ( Prop.TransSensitivities.bEnable ) {
		StringA ( string ( "X" ), Arr, true );
		sVal = LittleEndian2Big ( Prop.TransSensitivities.sValue[0] );
		Add ( Arr, (unsigned char *)&sVal, sizeof ( sVal ) );
		sVal = LittleEndian2Big ( Prop.TransSensitivities.sValue[1] );
		Add ( Arr, (BYTE *) &sVal, sizeof ( sVal ) );
		sVal = LittleEndian2Big ( Prop.TransSensitivities.sValue[2] );
		Add ( Arr, (BYTE *) &sVal, sizeof ( sVal ) );

		if ( bAddCr ) {
			StringA ( string ( "\r" ), Arr, true );
		}
	}

	// Responsiveness
	if ( Prop.Responsiveness.bEnable ) {
		StringA ( string ( "P" ), Arr, true );
		sVal = LittleEndian2Big ( Prop.Responsiveness.sMaximum );
		Add ( Arr, (BYTE *) &sVal, sizeof ( sVal ) );

		// Responsiveness - Minimum
		if ( Prop.Responsiveness.Minimum.bEnable ) {
			sVal = LittleEndian2Big ( Prop.Responsiveness.Minimum.sValue );
			Add ( Arr, (BYTE *) &sVal, sizeof ( sVal ) );
		}

		if ( bAddCr ) {
			StringA ( string ( "\r" ), Arr, true );
		}
	}

	// ResponMultiplier
	// ResponMultiplier - Translation
	if ( Prop.ResponMultiplier.Translation.bEnable ) {
		StringA ( string ( "FT" ), Arr, true );
		Add ( Arr, (BYTE *) &Prop.ResponMultiplier.Translation.cValue, sizeof ( Prop.ResponMultiplier.Translation.cValue ) );

		if ( bAddCr ) {
			StringA ( string ( "\r" ), Arr, true );
		}
	}

	// ResponMultiplier - Rotation
	if ( Prop.ResponMultiplier.Rotation.bEnable ) {
		StringA ( string ( "FR" ), Arr, true );
		Add ( Arr, (BYTE *) &Prop.ResponMultiplier.Rotation.cValue, sizeof ( Prop.ResponMultiplier.Rotation.cValue ) );

		if ( bAddCr ) {
			StringA ( string ( "\r" ), Arr, true );
		}
	}

	// SpinRate
	if ( Prop.SpinRate.bEnable ) {
		StringA ( string ( "S" ), Arr, true );
		Add ( Arr, (BYTE *) &Prop.SpinRate.cExponent, sizeof ( Prop.SpinRate.cExponent ) );
		Add ( Arr, (BYTE *) &Prop.SpinRate.cMantissa, sizeof ( Prop.SpinRate.cMantissa ) );

		if ( bAddCr ) {
			StringA ( string ( "\r" ), Arr, true );
		}
	}

	// TranslationMode
	if ( Prop.TranslationMode.bEnable ) {
		StringA ( string ( "T" ), Arr, true );
		Add ( Arr, (BYTE *) &Prop.TranslationMode.cBallSystem, sizeof ( Prop.TranslationMode.cBallSystem ) );
		Add ( Arr, (BYTE *) &Prop.TranslationMode.cFreedomVector, sizeof ( Prop.TranslationMode.cFreedomVector ) );
		Add ( Arr, (BYTE *) &Prop.TranslationMode.cOutput, sizeof ( Prop.TranslationMode.cOutput ) );

		if ( Prop.TranslationMode.Vector.bEnable ) {
			sVal = LittleEndian2Big ( Prop.TranslationMode.Vector.sValue[0] );
			Add ( Arr, (BYTE *) &sVal, sizeof ( sVal ) );
			sVal = LittleEndian2Big ( Prop.TranslationMode.Vector.sValue[1] );
			Add ( Arr, (BYTE *) &sVal, sizeof ( sVal ) );
			sVal = LittleEndian2Big ( Prop.TranslationMode.Vector.sValue[2] );
			Add ( Arr, (BYTE *) &sVal, sizeof ( sVal ) );
		}

		if ( bAddCr ) {
			StringA ( string ( "\r" ), Arr, true );
		}
	}

	// RotationMode
	if ( Prop.RotationMode.bEnable ) {
		StringA ( string ( "R" ), Arr, true );
		Add ( Arr, (BYTE *) &Prop.RotationMode.cBallSystem, sizeof ( Prop.RotationMode.cBallSystem ) );
		Add ( Arr, (BYTE *) &Prop.RotationMode.cFreedomVector, sizeof ( Prop.RotationMode.cFreedomVector ) );
		Add ( Arr, (BYTE *) &Prop.RotationMode.cOutput, sizeof ( Prop.RotationMode.cOutput ) );

		if ( Prop.RotationMode.Vector.bEnable ) {
			sVal = LittleEndian2Big ( Prop.RotationMode.Vector.sValue[0] );
			Add ( Arr, (BYTE *) &sVal, sizeof ( sVal ) );
			sVal = LittleEndian2Big ( Prop.RotationMode.Vector.sValue[1] );
			Add ( Arr, (BYTE *) &sVal, sizeof ( sVal ) );
			sVal = LittleEndian2Big ( Prop.RotationMode.Vector.sValue[2] );
			Add ( Arr, (BYTE *) &sVal, sizeof ( sVal ) );
		}

		if ( bAddCr ) {
			StringA ( string ( "\r" ), Arr, true );
		}
	}

	if ( Prop.Mode.bEnable ) {
		StringA ( string ( "M" ), Arr, true );
		Add ( Arr, (BYTE *) &Prop.Mode.cTranslationFreedom, sizeof ( Prop.Mode.cTranslationFreedom ) );

		if ( Prop.Mode.Rotation.bEnable ) {
			Add ( Arr, (BYTE *) &Prop.Mode.Rotation.cRotationFreedom, sizeof ( Prop.Mode.Rotation.cRotationFreedom ) );

			if ( Prop.Mode.Rotation.DataForm.bEnable ) {
				Add ( Arr, (BYTE *) &Prop.Mode.Rotation.DataForm.cDataType, sizeof ( Prop.Mode.Rotation.DataForm.cDataType ) );

				if ( Prop.Mode.Rotation.DataForm.Handedness.bEnable ) {
					if ( Prop.Mode.Rotation.DataForm.Handedness.bLeftHanded ) {
						StringA ( string ( "L" ), Arr, true );
					}

					else {
						StringA ( string ( "R" ), Arr, true );
					}

					if ( Prop.Mode.Rotation.DataForm.Handedness.PrePostProc.bEnable ) {
						Add ( Arr, (BYTE *) &Prop.Mode.Rotation.DataForm.Handedness.PrePostProc.cValue,
							  sizeof ( Prop.Mode.Rotation.DataForm.Handedness.PrePostProc.cValue ) );
					}
				}
			}
		}

		if ( bAddCr ) {
			StringA ( string ( "\r" ), Arr, true );
		}
	}

	if ( Prop.Zero.bEnable ) {
		StringA ( string ( "Z" ), Arr, true );

		if ( bAddCr ) {
			StringA ( string ( "\r" ), Arr, true );
		}
	}

	if ( Prop.AbsoluteRotMatrix.bEnable ) {
		StringA ( string ( "A" ), Arr, true );
		sVal = LittleEndian2Big ( Prop.AbsoluteRotMatrix.sValue[0] );
		Add ( Arr, (BYTE *) &sVal, sizeof ( sVal ) );
		sVal = LittleEndian2Big ( Prop.AbsoluteRotMatrix.sValue[1] );
		Add ( Arr, (BYTE *) &sVal, sizeof ( sVal ) );
		sVal = LittleEndian2Big ( Prop.AbsoluteRotMatrix.sValue[2] );
		Add ( Arr, (BYTE *) &sVal, sizeof ( sVal ) );

		if ( bAddCr ) {
			StringA ( string ( "\r" ), Arr, true );
		}
	}

	if ( Prop.OrientationMatrix.bEnable ) {
		StringA ( string ( "O" ), Arr, true );
		sVal = LittleEndian2Big ( Prop.OrientationMatrix.sValue[0] );
		Add ( Arr, (BYTE *) &sVal, sizeof ( sVal ) );
		sVal = LittleEndian2Big ( Prop.OrientationMatrix.sValue[1] );
		Add ( Arr, (BYTE *) &sVal, sizeof ( sVal ) );
		sVal = LittleEndian2Big ( Prop.OrientationMatrix.sValue[2] );
		Add ( Arr, (BYTE *) &sVal, sizeof ( sVal ) );

		if ( bAddCr ) {
			StringA ( string ( "\r" ), Arr, true );
		}
	}

	// Communicatiom mode
	if ( Prop.CommunicationMode.bEnable ) {
		StringA ( string ( "C" ), Arr, true );
		Add ( Arr, (BYTE *) &Prop.CommunicationMode.cValue, sizeof ( Prop.CommunicationMode.cValue ) );

		if ( bAddCr ) {
			StringA ( string ( "\r" ), Arr, true );
		}
	}

	//
	//IDX_BEEP
	//IDX_LINS
	//
}

void SBW::Replace ( vector <BYTE>  &vect, vector <BYTE>  &sub, vector <BYTE>  &newsub )
{
	if ( sub != newsub ) {
		vector <BYTE>::iterator result1;
		result1 = search ( vect.begin ( ), vect.end ( ), sub.begin ( ), sub.end ( ) );

		while ( result1 != vect.end ( ) ) {
			int off = result1 - vect.begin ( );
			vect.erase ( result1, result1 + sub.size ( ) );
			vect.insert ( vect.begin() + off, newsub.begin ( ), newsub.end ( ) );
			result1 = search ( vect.begin ( )/*result1 + vect.size()*/, vect.end ( ), sub.begin ( ), sub.end ( ) );
		}
	}
}

void SBW::Escape ( vector <BYTE>  &clData )
{
	vector <BYTE>  sub, newsub;
	StringA ( string ( "^Q" ), sub );
	StringA ( string ( "\x11" ), newsub );
	Replace ( clData, sub, newsub );

	StringA ( string ( "^S" ), sub );
	StringA ( string ( "\x13" ), newsub );
	Replace ( clData, sub, newsub );

	StringA ( string ( "^M" ), sub );
	StringA ( string ( "\r" ), newsub );
	Replace ( clData, sub, newsub );

	StringA ( string ( "^^" ), sub );
	StringA ( string ( "^" ), newsub );
	Replace ( clData, sub, newsub );
}

bool InvalidChar ( BYTE c )
{
	return ( ( ( c < 32 ) || ( c > 126 ) ) && ( c != 13 ) && ( c != 10 ) );
}

void SBW::StringA ( string &Src, vector <BYTE>  &Dest, bool append)
{
	if ( !append ) {
		Dest.clear ( );
	}

	Dest.insert ( Dest.end ( ), Src.begin ( ), Src.end ( ) );
}

void SBW::StringA ( vector <BYTE>  &Src, string &Dest, BYTE NoPrintCharSubst )
{
	vector <BYTE>  NewSrc = Src;
	replace_if ( NewSrc.begin ( ), NewSrc.end ( ), InvalidChar, NoPrintCharSubst );
	Dest.clear ( );
	Dest.insert ( Dest.end ( ), NewSrc.begin ( ), NewSrc.end ( ) );
	Dest.push_back ( '\0' );
}

void SBW::GetTYPEAt ( vector <BYTE>  &Src, INT_PTR nIndex, INT_PTR offset, int &Val )
{
	Val = * ( (int *) ( Src.data ( ) + ( ( nIndex << 2 ) + offset ) ) );
}

void SBW::GetTYPEAt ( vector <BYTE>  &Src, INT_PTR nIndex, INT_PTR offset, short &Val )
{
	Val = * ( (short *) ( Src.data ( ) + ( ( nIndex << 1 ) + offset ) ) );
}

void SBW::GetTYPEAt ( vector <BYTE>  &Src, INT_PTR nIndex, INT_PTR offset, unsigned short &Val )
{
	Val = * ( (unsigned short *) ( Src.data ( ) + ( ( nIndex << 1 ) + offset ) ) );
}

void SBW::SendResetAfterTimeout ( )
{
	if ( m_iInitiated == 0 ) {
		m_iInitiated     = 1;
		m_ullTimeCounter = GetTickCount64 ( );
	}

	if ( m_iInitiated == 1 )
		if ( m_ullTimeCounter + m_ullTimeout < GetTickCount64 ( ) ) {
			m_iInitiated     = 2;
			m_ullTimeCounter = 0;
			string Temp      = "@\r";
			StringA ( Temp, m_cl_Out );
			Write ( );
		}
}

bool SBW::Signal ( DWORD dwSignal )
{
	//DWORD dwError = 0;

	if ( m_hComm != NULL ) {
		if ( EscapeCommFunction ( m_hComm, dwSignal ) == TRUE ) {
			return true;
		}

		//dwError = GetLastError ( );
	}

	return false;
}

bool SBW::AddCMDs ( vector <BYTE> &Arr )
{
	if ( iCMDsCounter + Arr.size ( ) > sizeof ( pbCMDs ) ) {
		return false;
	}

	memmove_s ( pbCMDs + iCMDsCounter, sizeof ( pbCMDs ), Arr.data ( ), Arr.size ( ) );
	iCMDsCounter += Arr.size ( );
	return true;
}

void SBW::ClearCMDs ( )
{
	iCMDsCounter = 0;
	ZeroMemory ( &pbCMDs, sizeof ( pbCMDs ) );
}

void SBW::SendCMDs ( )
{
	m_cl_Out.assign ( pbCMDs, pbCMDs + min ( iCMDsCounter, sizeof ( pbCMDs ) ) );
	Write ( );
}

void SBW::GetHexCMDs ( CString &Str )
{
	CString Temp;
	Str.Empty ( );

	for ( int i = 0; i < ( min ( iCMDsCounter, ( int ) sizeof ( pbCMDs ) ) ); i++ ) {
		Temp.Format ( _T ( "%02X " ), pbCMDs[i] );
		Str += Temp;
	}
}

void SBW::SendReset ( )
{
	CStringA Str;
	Str = "@\r";
	m_cl_Out.assign ( (BYTE *) Str.GetBuffer ( ), (BYTE *) Str.GetBuffer ( ) + Str.GetLength ( ) );
	Write ( );
}

INT_PTR SBW::GetCommand ( INT_PTR &iIndex, void **ppData, INT_PTR &iLastCommand )
{
	string clTemp2;

	INT_PTR iDatLen = m_cl_In.size ( );
	vector <BYTE>::iterator iPos;

	if ( ( iDatLen == 0 ) || ( iIndex >= iDatLen ) ) {
		return -1;
	}

	if ( m_clDelimiter.size ( ) < 0 ) {
		throw;
	}

	else if ( iLastCommand == SBE_COMMAND_INT ) {
		bool bDelInitStr = false;
		BYTE cVal = m_cl_In.at ( iIndex );

		while ( ( cVal == 0 ) || ( cVal == 128 ) || ( cVal == 13 ) ) {
			iIndex++;
			bDelInitStr = true;

			if ( iDatLen <= iIndex ) {
				break;
			}

			cVal = m_cl_In.at ( iIndex );
		}

		if ( bDelInitStr && ( iDatLen > iIndex ) ) {

			m_clRAWData.insert ( m_clRAWData.end ( ), m_cl_In.begin ( ), m_cl_In.begin ( ) + iIndex );
			m_cl_In.erase ( m_cl_In.begin ( ), m_cl_In.begin ( ) + iIndex );

			iLastCommand = SBE_COMMAND_NUL;
			iIndex = 0;
			return 1;
		}

		return -1;
	}

	iPos = search ( m_cl_In.begin ( ) + iIndex, m_cl_In.end ( ), m_clDelimiter.begin ( ), m_clDelimiter.end ( ) );

	if ( iPos == m_cl_In.end ( ) ) {
		return -1;
	}

	m_clSentence.clear ( );
	m_clSentence.insert ( m_clSentence.end ( ), m_cl_In.begin ( ), iPos + m_clDelimiter.size ( ) );
	m_cl_In.erase ( m_cl_In.begin ( ), iPos + m_clDelimiter.size ( ) );

	if ( !m_bAppendData ) {
		m_clRAWData.clear ( );
	}

	m_clRAWData.insert ( m_clRAWData.end ( ), m_clSentence.begin ( ), m_clSentence.end ( ) );

	switch ( m_clSentence.at ( 0 ) ) {
		case '\t': {
				iLastCommand = SBE_COMMAND_NUL;
				return SBE_COMMAND_NUL;	// null
			}

		case '%': {
				iLastCommand = SBE_COMMAND_ECH;
				return  1; // echo
			}

		case '?': {
				iLastCommand = SBE_COMMAND_INV;
				return  1; // invalid
			}

		case '@': {
				Escape ( m_clSentence );

				StringA ( m_clSentence, clTemp2 );
				AddInfo ( clTemp2 );

				string str = "hv\r\"\r";
				m_cl_Out.assign ( str.begin ( ), str.end ( ) );
				m_cl_Out.insert ( m_cl_Out.end ( ), m_clInitializationString.begin ( ), m_clInitializationString.end ( ) );

				Write ( );
				iLastCommand = SBE_COMMAND_RES;
				return  1; // reset
			}

		case '\"': {
				Escape ( m_clSentence );
				StringA ( m_clSentence, clTemp2 );
				AddInfo ( clTemp2 );

				iLastCommand = SBE_COMMAND_DBQ;
				return  1; // "
			}

		case '.': {
				short shVal;
				GetTYPEAt ( m_clSentence, 0, 1, shVal );
				shVal = _rotl16 ( shVal, 8 );

				for ( INT_PTR M = 0; M < 12; M++ ) {
					m_stButtons.bButton_PreviousState_SB4000FLX[M] = m_stButtons.bButton_SB4000FLX[M];
					m_stButtons.bButton_SB4000FLX[M] = ( ( ( shVal & 0x003F ) | ( ( shVal & 0x1F80 ) >> 1 ) ) >> M ) & 0x0001;
				}

				*ppData = m_stButtons.bButton_SB4000FLX;
				iLastCommand = SBE_COMMAND_PNT;
				return  1; // .
			}

		case 'A': {
				iLastCommand = SBE_COMMAND_A;
				return  1;
			}

		case 'B': {
				iLastCommand = SBE_COMMAND_B;
				return  1;

			}

		case 'C': {
				iLastCommand = SBE_COMMAND_C;
				return  1;

			}

		case 'D': {

				unsigned short sTemp;
				Escape ( m_clSentence );

				if ( m_clSentence.size ( ) >= ( vector <int>::size_type )m_stOffset.lPeriod + 1 ) {
					unsigned short usTemp;
					m_stCoord.sPrevious_Period = m_stCoord.sCurrent_Period;
					GetTYPEAt ( m_clSentence, m_stOffset.lPeriod >> ( sizeof ( unsigned short ) - 1 ), 1, usTemp );
					m_stCoord.sCurrent_Period = LittleEndian2Big ( usTemp );
					m_stCoord.bPeriod = true;
				}

				else {
					m_stCoord.bPeriod = false;
				}

				if ( m_clSentence.size ( ) >= ( vector <int>::size_type )m_stOffset.lXTrans + 1 ) {
					m_stCoord.sPrevious_XTrans = m_stCoord.sCurrent_XTrans;
					GetTYPEAt ( m_clSentence, m_stOffset.lXTrans >> ( sizeof ( short ) - 1 ), 1, sTemp );
					m_stCoord.sCurrent_XTrans = LittleEndian2Big ( sTemp );
					m_stCoord.bXTrans = true;
				}

				else {
					m_stCoord.bXTrans = false;
				}

				if ( m_clSentence.size ( ) >= ( vector <int>::size_type )m_stOffset.lYTrans + 1 ) {
					m_stCoord.sPrevious_YTrans = m_stCoord.sCurrent_YTrans;
					GetTYPEAt ( m_clSentence, m_stOffset.lYTrans >> ( sizeof ( short ) - 1 ), 1, sTemp );
					m_stCoord.sCurrent_YTrans = LittleEndian2Big ( sTemp );
					m_stCoord.bYTrans = true;
				}

				else {
					m_stCoord.bYTrans = false;
					m_stCoord.sCurrent_YTrans = 0;
				}

				if ( m_clSentence.size ( ) >= ( vector <int>::size_type )m_stOffset.lZTrans + 1 ) {
					m_stCoord.sPrevious_ZTrans = m_stCoord.sCurrent_ZTrans;
					GetTYPEAt ( m_clSentence, m_stOffset.lZTrans >> ( sizeof ( short ) - 1 ), 1, sTemp );
					m_stCoord.sCurrent_ZTrans = LittleEndian2Big ( sTemp );
					m_stCoord.bZTrans = true;
				}

				else {
					m_stCoord.bZTrans = false;
					m_stCoord.sCurrent_ZTrans = 0;
				}

				if ( m_clSentence.size ( ) >= ( vector <int>::size_type )m_stOffset.lXRot + 1 ) {
					m_stCoord.sPrevious_XRot = m_stCoord.sCurrent_XRot;
					GetTYPEAt ( m_clSentence, m_stOffset.lXRot >> ( sizeof ( short ) - 1 ), 1, sTemp );
					m_stCoord.sCurrent_XRot = LittleEndian2Big ( sTemp );
					m_stCoord.bXRot = true;
				}

				else {
					m_stCoord.bXRot = false;
				}

				if ( m_clSentence.size ( ) >= ( vector <int>::size_type )m_stOffset.lYRot + 1 ) {
					m_stCoord.sPrevious_YRot = m_stCoord.sCurrent_YRot;
					GetTYPEAt ( m_clSentence, m_stOffset.lYRot >> ( sizeof ( short ) - 1 ), 1, sTemp );
					m_stCoord.sCurrent_YRot = LittleEndian2Big ( sTemp );
					m_stCoord.bYRot = true;
				}

				else {
					m_stCoord.bYRot = false;
				}

				if ( m_clSentence.size ( ) >= ( vector <int>::size_type )m_stOffset.lZRot + 1 ) {
					m_stCoord.sPrevious_ZRot = m_stCoord.sCurrent_ZRot;
					GetTYPEAt ( m_clSentence, m_stOffset.lZRot >> ( sizeof ( short ) - 1 ), 1, sTemp );
					m_stCoord.sCurrent_ZRot = LittleEndian2Big ( sTemp );
					m_stCoord.bZRot = true;
				}

				else {
					m_stCoord.bZRot = false;
				}

				iLastCommand = SBE_COMMAND_D;
				return  1;
			}

		case 'E': {
				iLastCommand = SBE_COMMAND_E;
				return  1;
			}

		case 'F': {
				iLastCommand = SBE_COMMAND_F;
				return  1;
			}

		case 'H': {
				Escape ( m_clSentence );
				StringA ( m_clSentence, clTemp2 );
				AddInfo ( clTemp2 );
				iLastCommand = SBE_COMMAND_H;
				return  1;
			}

		case 'K': {
				if ( m_clDeviceInfo.Find ( "Spaceball 4000" ) != -1 ) {
					iLastCommand = SBE_COMMAND_IGN;
					return 1;
				}

				short shVal;
				GetTYPEAt ( m_clSentence, 0, 1, shVal );
				shVal = _rotl16 ( shVal, 8 );

				for ( INT_PTR M = 0; M < 8; M++ ) {
					m_stButtons.bButton_PreviousState_SB3000[M] = m_stButtons.bButton_SB3000[M];
					m_stButtons.bButton_SB3000[M] = ( ( ( shVal & 0x000F ) | ( ( shVal & 0x0F00 ) >> 4 ) ) >> M ) & 0x0001;
				}

				*ppData = m_stButtons.bButton_SB3000;
				iLastCommand = SBE_COMMAND_K;
				return  1;
			}

		case 'M': {
				iLastCommand = SBE_COMMAND_M;
				return  1;
			}

		case 'N': {
				iLastCommand = SBE_COMMAND_N;
				return  1;
			}

		case 'O': {
				iLastCommand = SBE_COMMAND_O;
				return  1;
			}

		case 'P': {
				iLastCommand = SBE_COMMAND_P;
				return  1;
			}

		case 'R': {
				iLastCommand = SBE_COMMAND_R;
				return  1;
			}

		case 'S': {
				iLastCommand = SBE_COMMAND_S;
				return  1;
			}

		case 'T': {
				iLastCommand = SBE_COMMAND_T;
				return  1;
			}

		case 'X': {
				iLastCommand = SBE_COMMAND_X;
				return  1;
			}

		/*  case 'Y':{
			 iLastCommand = SBE_COMMAND_Y;
			 return  1;
	}*/ //	Y scale ???

		case 'Z': {
				iLastCommand = SBE_COMMAND_Z;
				return  1;
			}

		default: {
				Escape ( m_clSentence );
				StringA ( m_clSentence, clTemp2 );
				AddInfo ( clTemp2 );
			}
	}

	return -1;
}

void SBW::AddInfo ( string &clStr )
{
	string info = m_clDeviceInfo;
	info.insert ( info.end ( ), clStr.begin ( ), clStr.end ( ) );
	m_clDeviceInfo = &info[0];
	m_clDeviceInfo.Replace ( "\r", "\n" );
	m_clDeviceInfo.Replace ( "\n\n", "\n" );
}

bool SBW::Unlock_Write ( )
{
	if ( m_hProcWriEv ) {
		SetEvent ( m_hProcWriEv );
		return true;
	}

	return false;
}

bool SBW::Lock_Write ( )
{
	ResetEvent ( m_hProcWriEv );

	if ( WaitForSingleObject ( m_hProcWriEv, INFINITE ) == WAIT_OBJECT_0 ) {
	}
	else {
	}

	//ResetEvent ( m_hProcWriEv );

	if ( m_bAbortWriteProc ) {
		return false;
	}

	return true;
}

bool SBW::SendMessage ( DWORD dwCommand, LPARAM lParam )
{
	if ( ( dwCommand != SBE_PRESTATUS_COMM ) || ( m_dwLastCommand != dwCommand ) ) {
		::SendMessage ( m_hWnd, SBE_MESSAGE, dwCommand, (LPARAM) lParam );
	}

	m_dwLastCommand = dwCommand;

	return !m_bAbortStatusProc;
}

UINT StatusThreadProc ( LPVOID pParam )
{
	SBW *Obj = reinterpret_cast <SBW *> ( pParam );
	BOOL fWaitingOnStat = FALSE;
	DWORD dwCommEvent = 0, dwRes = 0, dwOvRes = 0/*, dwErr = 0*/;
	DWORD dwRead;

	if ( Obj == NULL ) {
		return 0;
	}

	while ( Obj->SendMessage ( SBE_PRESTATUS_COMM, 0 ) ) {
		Obj->SendResetAfterTimeout ( );

		if ( !fWaitingOnStat ) {
			if ( !WaitCommEvent ( Obj->m_hComm, &dwCommEvent, &Obj->m_stIO ) ) {
				if ( GetLastError ( ) == ERROR_IO_PENDING ) {
					fWaitingOnStat = TRUE;
				}

				else {
					// error in WaitCommEvent; abort
					break;
				}
			}

			else {
				bool bClearComm;
				Obj->SendMessage ( (DWORD)SBE_STATUS_COMM, (LPARAM)0 );

				if ( Obj->TranslateStatus ( dwCommEvent, bClearComm ) ) {

					dwRead = Obj->Read ( Obj->m_stStatus.dwInQue );

					if ( dwRead != Obj->m_stStatus.dwInQue ) {
						continue;
					}

					Obj->SendMessage ( SBE_READ_COMM, 0 );

					//Obj->m_stStatus.dwInQue -= dwRead;
				}

				if ( bClearComm )
					if ( ClearCommBreak ( Obj->m_hComm ) == FALSE ) {
						//dwErr = GetLastError ( );
					}
			}
		}

		dwOvRes = 0;

		if ( fWaitingOnStat ) {
			dwRes = WaitForSingleObject ( Obj->m_stIO.hEvent, SBE_STATUS_TIMEOUT );

			switch ( dwRes ) {
				case WAIT_OBJECT_0:
					if ( !GetOverlappedResult ( Obj->m_hComm, &Obj->m_stIO, &dwOvRes, FALSE ) ) {
						// An error occurred in the overlapped operation, call GetLastError to find out what it was and abort if it is fatal.
					}
					else {
						bool bClearComm;
						Obj->SendMessage ( SBE_STATUS_COMM, 0 );

						if ( Obj->TranslateStatus ( dwCommEvent, bClearComm ) ) {

							dwRead = Obj->Read ( Obj->m_stStatus.dwInQue );

							if ( dwRead != Obj->m_stStatus.dwInQue ) {
								continue;
							}

							// Obj->m_stStatus.dwInQue -= dwRead;
						}

						Obj->SendMessage ( SBE_READ_COMM, 0 );

						if ( bClearComm )
							if ( ClearCommBreak ( Obj->m_hComm ) == FALSE ) {
								//dwErr = GetLastError ( );
							}
					}

					// Set fWaitingOnStat flag to indicate that a new WaitCommEvent is to be issued.
					fWaitingOnStat = FALSE;
					break;

				case WAIT_TIMEOUT:
					//DoBackgroundWork();
					break;

				default:
					Obj->Disconnect ( );
					return 0;
			}
		}
	}

	Obj->m_clBuffer.clear ( );

	Obj->SendMessage ( SBE_RESET_COMM, 0 );

	if ( Obj->m_hComm ) {
		CloseHandle ( Obj->m_hComm );
		Obj->m_hComm = NULL;
	}

	return 1;
}

UINT WriteThreadProc ( LPVOID pParam )
{
	SBW *Obj = reinterpret_cast <SBW *> (pParam);

	if ( Obj == NULL ) {
		return -1;
	}

	OVERLAPPED stOv = { 0 };
	DWORD dwWritten;
	stOv.hEvent = CreateEvent ( NULL, TRUE, FALSE, NULL );

	if ( stOv.hEvent == NULL ) {
		return 0;
	}

	Obj->m_hProcWriEv = CreateEvent ( NULL, TRUE, FALSE, NULL );

	if ( Obj->m_hProcWriEv == NULL ) {
		return 0;
	}

	while ( Obj->Lock_Write ( ) ) {
		Obj->m_iLastWriteStatus = SBE_WRITE_NUL;

		if ( Obj->m_hComm == NULL ) {
			break;
		}

		Obj->m_stStatus.dwOutQue = Obj->m_cl_Out.size ( );
		dwWritten = 0;

		if ( !WriteFile ( Obj->m_hComm, Obj->m_cl_Out.data ( ), Obj->m_cl_Out.size ( ), &dwWritten, &stOv ) ) {
			if ( GetLastError ( ) != ERROR_IO_PENDING ) {
				Obj->m_iLastWriteStatus = SBE_WRITE_FAILED;
			}

			else {
				if ( !GetOverlappedResult ( Obj->m_hComm, &stOv, &dwWritten, TRUE ) ) {
					Obj->m_iLastWriteStatus = SBE_WRITE_PEN_ERR;
				}

				else {
					Obj->m_iLastWriteStatus = SBE_WRITE_SUCC;
				}
			}
		}

		else {
			Obj->m_iLastWriteStatus = SBE_WRITE_SUCC_IME;
		}

		if ( dwWritten != 0 ) {
			Obj->SendMessage ( SBE_WRITE_COMM, dwWritten );
		}

		Obj->m_iBytesWritten += dwWritten;

		//FlushFileBuffers ( Obj->m_hComm );
		Obj->m_stStatus.dwOutQue -= dwWritten;
	}

	CloseHandle ( Obj->m_hProcWriEv );
	Obj->m_hProcWriEv = NULL;
	CloseHandle ( stOv.hEvent );
	return 1;
}
