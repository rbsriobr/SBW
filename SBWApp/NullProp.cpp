/*
This file is subject to the terms and conditions defined in
file 'LICENSE.txt', which is part of this source code package.
Copyright (C) 2014 Ricardo B. Santos.
All rights reserved
*/

#include "stdafx.h"
#include "NullProp.h"

////////////////////////////////////////////////////////////////////////////////
// CNullProp class

CNullProp::CNullProp ( DWORD_PTR dwState, const CString &strName, CString Msg, COLORREF dwClr, LPCTSTR lpszDescr ) :
	CMFCPropertyGridProperty2 ( dwState, strName, _T (""), lpszDescr )
{
	m_clType = _T ( "CNullProp" );
	m_dwClr = dwClr;
	m_Msg = Msg;
	AllowEdit ( FALSE );
}

void CNullProp::OnDrawValue ( CDC *pDC, CRect rect )
{
	COLORREF clrTextOld = pDC->GetTextColor ( );
	pDC->SetTextColor ( m_dwClr );
	pDC->DrawText ( m_Msg, rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER );
	pDC->SetTextColor ( clrTextOld );
}
