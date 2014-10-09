/*
This file is subject to the terms and conditions defined in
file 'LICENSE.txt', which is part of this source code package.
Copyright (C) 2013 Ricardo B. Santos.
All rights reserved
*/

#pragma once
#include "afxwin.h"
#include "afxpropertygridctrl.h"
#include "MFCPropertyGridProperty2.h"

#define HEXPFX _T ( "0x" )

class CHexNumberProp : public CMFCPropertyGridProperty2 {
	public:
		CHexNumberProp ( DWORD_PTR dwState, const CString &strName, __int64 nValue, CArray<__int64, __int64> *MinSeq,
							  CArray<__int64, __int64> *MaxSeq, int nWidth, LPCTSTR Prefix, LPCTSTR lpszDescr = NULL );

		virtual BOOL OnUpdateValue ( );
		virtual __int64 GetInt ( );
		virtual void SetInt ( __int64 iValue );
	private:
		CArray<__int64, __int64> m_MinSeq;
		CArray<__int64, __int64> m_MaxSeq;
		int m_nWidth;
		CString m_Prefix;
};
