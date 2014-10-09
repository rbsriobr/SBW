/*
This file is subject to the terms and conditions defined in
file 'LICENSE.txt', which is part of this source code package.
Copyright (C) 2014 Ricardo B. Santos.
All rights reserved
*/

#include "stdafx.h"
#include "SBWApp.h"
#include "NumEdit.h"
#include <locale.h>

// CNumEdit

IMPLEMENT_DYNAMIC ( CNumEdit, CEdit )

CNumEdit::CNumEdit()
{
	m_sDec       = _T ( "" );
	m_sNeg       = _T ( "" );
	m_dDefValue  = 0.0;
	m_dMinValue  = 0.0;
	m_dMaxValue  = 0.0;
	m_dIncDec    = 1.0;
	m_iDefDig    = 0;
	m_bInteger   = true;
	m_iPrecision = 2;
}

CNumEdit::~CNumEdit()
{
}

BEGIN_MESSAGE_MAP ( CNumEdit, CEdit )
	// "ON_NOTIFY_REFLECT_EX() in your message map, your message handler may or may not allow the parent window to handle the message. If the handler returns FALSE,
	// the message will be handled by the parent as well."
	ON_CONTROL_REFLECT_EX ( EN_UPDATE, &CNumEdit::OnEnUpdate )
	ON_CONTROL_REFLECT_EX ( EN_KILLFOCUS, &CNumEdit::OnEnKillfocus )
	ON_WM_KEYDOWN ( )
END_MESSAGE_MAP ( )

// CNumEdit message handlers

void CNumEdit::Symbols ( CString &Dec, CString &Neg )
{
	int iRet = GetLocaleInfo ( LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, Dec.GetBufferSetLength ( 2 ), 2 );
	Dec.ReleaseBuffer ( );

	if ( iRet == 0 ) {
		Dec = _T ( "." );
	}

	iRet = GetLocaleInfo ( LOCALE_USER_DEFAULT, LOCALE_SNEGATIVESIGN, Neg.GetBufferSetLength ( 2 ), 2 );
	Neg.ReleaseBuffer ( );

	if ( iRet == 0 ) {
		Neg = _T ( "-" );
	}
}

BOOL CNumEdit::OnEnUpdate ( )
{
	CString Temp, Neg, DNeg, Dec;
	GetWindowText ( Temp );
	bool bSetSel = false;
	double dVal;
	Symbols ( Dec, Neg );
	DNeg = Neg;
	DNeg += DNeg;

	if ( m_iPrecision > MAXPRECISION ) {
		m_iPrecision = MAXPRECISION;
	}

	while ( Temp.Replace ( DNeg, Neg ) != 0 ) {
	}

	if ( m_bInteger ) {
		if ( Temp.Left ( 2 ) != _T ( "0x" ) ) {
			for ( int i = 0; i < Temp.GetLength ( ); i++ ) {
				if ( ! ( ( ( Temp.GetAt ( i ) > 47 ) && ( Temp.GetAt ( i ) < 58 ) ) || ( ( Temp.GetAt ( i ) == Neg.GetAt ( 0 ) ) && ( i == 0 ) ) ) ) {
					Temp.Delete ( i );
					i = 0;
					bSetSel = true;
				}
			}
		}

		else {
			Temp.MakeUpper ( );

			for ( int i = 2; i < Temp.GetLength ( ); i++ ) {
				if ( ! ( ( ( Temp.GetAt ( i ) > 47 ) && ( Temp.GetAt ( i ) < 58 ) ) ||
							( ( Temp.GetAt ( i ) > 64 ) && ( Temp.GetAt ( i ) < 71 ) ) ||
							( ( Temp.GetAt ( i ) == Neg.GetAt ( 0 ) ) && ( i == 0 ) ) ) ) {
					Temp.Delete ( i );
					i = 0;
					bSetSel = true;
				}
			}

			Temp.Replace ( _T ( "0X" ), _T ( "0x" ) );
		}
	}

	else {
		for ( int i = 0; i < Temp.GetLength ( ); i++ ) {
			if ( ! ( ( ( Temp.GetAt ( i ) > 47 ) && ( Temp.GetAt ( i ) < 58 ) ) ||
						( ( Temp.GetAt ( i ) == Neg.GetAt ( 0 ) ) && ( i == 0 ) ) ||
						( ( Temp.GetAt ( i ) == Dec.GetAt ( 0 ) ) && ( i != 0 ) ) ) ) {
				Temp.Delete ( i );
				i = 0;
				bSetSel = true;
			}
		}

		int pos = Temp.Find ( Dec, 0 );

		if ( pos != -1 ) {
			dVal = GetDValue ( );

			if ( ( Temp.GetLength ( ) - ( pos + 1 ) ) > m_iPrecision ) {
				Temp.Format ( _T ( "%.*f" ), m_iPrecision, dVal );
				Temp.Replace ( _T ( "." ), Dec );
				bSetSel = true;
			}
		}
	}

	if ( ( Temp != Neg ) && ( Temp.Right ( 1 ) != Dec ) && ( Temp != _T ( "0x" ) ) && ( !Temp.IsEmpty() ) ) {
		if ( m_bInteger ) {
			__int64 iVal = GetIValue ( );

			if ( iVal < ( __int64 ) m_dMinValue ) {
				Temp.Format ( _T ( "%0*I64d" ), m_iDefDig, ( __int64 ) m_dMinValue );
				bSetSel = true;
			}

			else  if ( iVal > ( __int64 ) m_dMaxValue ) {
				Temp.Format ( _T ( "%0*I64d" ), m_iDefDig, ( __int64 ) m_dMaxValue );
				bSetSel = true;
			}
		}

		else {
			dVal = GetDValue ( );

			if ( dVal < m_dMinValue ) {
				Temp.Format ( _T ( "%.*f" ), m_iPrecision, m_dMinValue );
				Temp.Replace ( _T ( "." ), Dec );
				bSetSel = true;
			}

			else  if ( dVal > m_dMaxValue ) {
				Temp.Format ( _T ( "%.*f" ), m_iPrecision, m_dMaxValue );
				Temp.Replace ( _T ( "." ), Dec );
				bSetSel = true;
			}
		}
	}

	if ( bSetSel ) {
		SetWindowText ( Temp );
		SetSel ( 255, 255, TRUE );
	}

	return FALSE;
}

BOOL CNumEdit::OnEnKillfocus ( )
{
	CString Temp, Dec, Neg;
	Symbols ( Dec, Neg );
	GetWindowText ( Temp );

	if ( m_iPrecision > MAXPRECISION ) {
		m_iPrecision = MAXPRECISION;
	}

	if ( ( Temp == _T ( "-" ) ) || ( Temp == _T ( "" ) ) ) {
		if ( m_bInteger ) {
			SetValue ( ( __int64 ) m_dDefValue, m_iDefDig );
			GetWindowText ( Temp );
		}

		else {
			SetValue ( m_dDefValue );
			GetWindowText ( Temp );
		}
	}

	if ( !m_bInteger ) {
		if ( m_iPrecision > 0 ) {
			int pos = Temp.Find ( Dec, 0 );

			if (  pos == -1  ) {
				Temp += Dec;
			}

			pos = Temp.Find ( Dec, 0 );

			while ( ( ( pos + 1 ) + m_iPrecision ) - Temp.GetLength ( ) > 0 ) {
				Temp += _T ( "0" );
			}

			SetWindowText ( Temp );
		}
	}

	return FALSE;
}

__int64 CNumEdit::GetIValue ( )
{
	CString Temp;
	TCHAR *stopstring;
	GetWindowText ( Temp );

	if ( Temp.IsEmpty ( ) ) {
		if ( m_bInteger ) {
			SetValue ( ( __int64 ) m_dDefValue, m_iDefDig );
		}

		else {
			SetValue ( m_dDefValue );
		}
	}

	return _tcstoi64 ( Temp.GetBuffer ( ), &stopstring, 10 );
}

double CNumEdit::GetDValue ( )
{
	CString Temp, Dec, Neg;
	GetWindowText ( Temp );

	if ( Temp.IsEmpty ( ) ) {
		if ( m_bInteger ) {
			SetValue ( ( __int64 ) m_dDefValue, m_iDefDig );
		}

		else {
			SetValue ( m_dDefValue );
		}
	}

	Symbols ( Dec, Neg );
	Temp.Replace ( Dec, _T ( "." ) );
	double dValue = _tstof ( Temp.GetBuffer ( ) );
	return dValue;
}

void CNumEdit::SetValue ( __int64 iValue, int iDig )
{
	CString Temp;
	Temp.Format ( _T ( "%0*I64d" ), iDig, iValue );
	m_bInteger = true;
	SetWindowText ( Temp );
}

void CNumEdit::SetValue ( double dValue )
{
	CString Temp, Dec, Neg;

	if ( m_iPrecision > MAXPRECISION ) {
		m_iPrecision = MAXPRECISION;
	}

	Temp.Format ( _T ( "%.*f" ), m_iPrecision, dValue );
	Symbols ( Dec, Neg );
	Temp.Replace ( _T ( "." ), Dec );
	m_bInteger = false;
	SetWindowText ( Temp );
}


void CNumEdit::OnKeyDown ( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	if ( nChar == VK_UP ) {
		if ( m_bInteger ) {
			__int64 iValue = GetIValue ( );
			SetValue ( iValue + ( __int64 ) m_dIncDec, m_iDefDig );
		}

		else {
			double dValue = GetDValue ( );
			SetValue ( dValue + m_dIncDec );
		}

		SetSel ( 255, 255, TRUE );
	}

	else if ( nChar == VK_DOWN ) {
		if ( m_bInteger ) {
			__int64 iValue = GetIValue ( );
			SetValue ( iValue - ( __int64 ) m_dIncDec, m_iDefDig );
		}

		else {
			double dValue = GetDValue ( );
			SetValue ( dValue - m_dIncDec );
		}

		SetSel ( 255, 255, TRUE );
	}

	else {
		CEdit::OnKeyDown ( nChar, nRepCnt, nFlags );
	}
}
