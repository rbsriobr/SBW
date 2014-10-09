/*
This file is subject to the terms and conditions defined in
file 'LICENSE.txt', which is part of this source code package.
Copyright (C) 2014 Ricardo B. Santos.
All rights reserved
*/

#pragma once
#include "afxwin.h"
#include "afxpropertygridctrl.h"
#include "MFCPropertyGridProperty2.h"

class CNullProp : public CMFCPropertyGridProperty2 {
	public:
		CNullProp ( DWORD_PTR dwState, const CString &strName, CString Msg, COLORREF dwClr, LPCTSTR lpszDescr = NULL );
		CString m_Msg;
		COLORREF m_dwClr;
	private:
		virtual void OnDrawValue ( CDC *pDC, CRect rect );
};
