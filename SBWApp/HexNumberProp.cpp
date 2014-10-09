/*
This file is subject to the terms and conditions defined in
file 'LICENSE.txt', which is part of this source code package.
Copyright (C) 2013 Ricardo B. Santos.
All rights reserved
*/

#include "stdafx.h"
#include "HexNumberProp.h"
////////////////////////////////////////////////////////////////////////////////
// CHexNumberProp class

CHexNumberProp::CHexNumberProp ( DWORD_PTR dwState, const CString &strName, __int64 nValue, CArray<__int64, __int64> *MinSeq,
								 CArray<__int64, __int64> *MaxSeq, int nWidth, LPCTSTR Prefix, LPCTSTR lpszDescr ) :
	CMFCPropertyGridProperty2 ( dwState, strName, _T ( "" ), lpszDescr )
{
	m_clType = _T ( "CHexNumberProp" );

	m_nWidth = nWidth;
	m_Prefix = Prefix;

	if ( MinSeq ) {
		m_MinSeq.Copy ( *MinSeq );
	}

	if ( MaxSeq ) {
		m_MaxSeq.Copy ( *MaxSeq );
	}

	ASSERT ( m_MaxSeq.GetCount ( ) == m_MinSeq.GetCount ( ) );
	CString Str;
	Str.Format ( _T ( "%s%0*I64X" ), m_Prefix, ( m_MaxSeq.GetCount ( ) > 0 ) ? ( m_MaxSeq.GetCount ( ) * m_nWidth ) : m_nWidth, nValue );
	m_varValue = /*SetValue (*/ Str /*)*/;
}

BOOL CHexNumberProp::OnUpdateValue ( )
{
	ASSERT_VALID ( this );
	ASSERT_VALID ( m_pWndInPlace );
	ASSERT_VALID ( m_pWndList );
	ASSERT ( ::IsWindow ( m_pWndInPlace->GetSafeHwnd ( ) ) );
	TCHAR *stopstring;
	BOOL bRet = TRUE;

	CString Str;
	m_pWndInPlace->GetWindowText ( Str );
	Str.Replace ( HEXPFX, _T ( "" ) );
	__int64 nItem = _tcstoi64 ( Str.GetBuffer ( ), &stopstring, 16 );
	Str.Format ( _T ( "%s%0*I64X" ), m_Prefix, ( m_MaxSeq.GetCount ( ) > 0 ) ? ( m_MaxSeq.GetCount ( ) * m_nWidth ) : m_nWidth, nItem );

	if ( FormatProperty ( ) != Str ) {
		//m_pWndInPlace->SetWindowText ( Str );
		if ( m_MinSeq.GetCount ( ) ) {
			__int64 nNewVal = 0, Seq[] = { 0xF, 0xFF, 0xFFF, 0xFFFF, 0xFFFFF, 0xFFFFFF, 0xFFFFFFF, 0xFFFFFFFF };

			for ( INT_PTR i = 0; i < m_MinSeq.GetCount ( ); i++ ) { // 0, 4, 8, 12, 16, 20, 24, 28
				INT_PTR nRot = ( ( i * m_nWidth ) << 2 );
				__int64 nTempVal = ( nItem >> nRot ) & Seq[m_nWidth - 1];

				if ( nTempVal  < m_MinSeq.GetAt ( i ) ) {
					nNewVal |= ( m_MinSeq.GetAt ( i ) << nRot );
				}

				else if ( nTempVal  > m_MaxSeq.GetAt ( i ) ) {
					nNewVal |= ( m_MaxSeq.GetAt ( i ) << nRot );
				}

				else {
					nNewVal |= ( nTempVal << nRot );
				}
			}

			Str.Format ( _T ( "%s%0*I64X" ), m_Prefix, m_nWidth * m_MinSeq.GetCount ( ), nNewVal );
			m_pWndInPlace->SetWindowText ( Str );
			m_varValue = /*SetValue (*/ Str /*)*/;
			bRet = CMFCPropertyGridProperty2::OnUpdateValue ( );
			return bRet;
		}

		if ( m_pParent != NULL ) {
			m_pWndList->OnPropertyChanged ( m_pParent );
		}
	}

	bRet = CMFCPropertyGridProperty2::OnUpdateValue ( );
	return bRet;
}

__int64 CHexNumberProp::GetInt ( ) {
	COleVariant pVar;
	TCHAR *stopstring;
	pVar = GetValue ( );
	return ( _tcstoi64 ( CString ( pVar.bstrVal ), &stopstring, 16 ) );
}

void CHexNumberProp::SetInt ( __int64 iValue ) {
	CString Str;
	Str.Format ( _T ( "%s%0*I64X" ), m_Prefix, ( m_MaxSeq.GetCount ( ) > 0 ) ? ( m_MaxSeq.GetCount ( ) * m_nWidth ) : m_nWidth, iValue );
	//m_varValue = /*SetValue (*/ Str /*)*/;
	SetValue ( Str );
}