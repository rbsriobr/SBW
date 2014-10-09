/*
This file is subject to the terms and conditions defined in
file 'LICENSE.txt', which is part of this source code package.
Copyright (C) 2013 Ricardo B. Santos.
All rights reserved
*/

#pragma once
#include "afxwin.h"
#include "afxpropertygridctrl.h"

class CMFCPropertyGridProperty2;

typedef void ( CMFCPropertyGridProperty2::*PropCallback ) ( CMFCPropertyGridProperty2 *pObj, bool bValue );

class CMFCPropertyGridProperty2 : public CMFCPropertyGridProperty {

	public:
		CMFCPropertyGridProperty2 ( DWORD_PTR dwState, const CString &strGroupName, BOOL bIsValueList = FALSE );
		CMFCPropertyGridProperty2 ( DWORD_PTR dwState, const CString &strName, const COleVariant &varValue, LPCTSTR lpszDescr = NULL,
									LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL );
		virtual BOOL OnUpdateValue ( );
		BOOL AddSubItem ( CMFCPropertyGridProperty2 *pProp );
		PropCallback OnUpdateAnyItem;
		int m_iRef;
		DWORD_PTR m_dwState;
		void Update ( );
		CString m_clType;
		void SetState ( DWORD_PTR dwState );
		bool Checked ( );
		bool Unchecked ( );
		bool Indeterminate ( );
		virtual __int64 GetInt ( );
		virtual void SetInt ( __int64 iValue );
		bool GetBool ( );
		void SetBool ( bool bValue );
	protected:
		void PropagateToRoot ( DWORD_PTR wState, int iRef );
		virtual void OnDrawCheckBox ( CDC *pDC, CRect rectCheck, DWORD_PTR dwState );
		virtual void OnDrawName ( CDC *pDC, CRect rect );
		virtual BOOL OnDblClk ( CPoint point );
		virtual void OnClickName ( CPoint point );
		void Root ( CMFCPropertyGridProperty2 **pObj );
		void PropagateAll ( CMFCPropertyGridProperty2 *pObj );
	protected:
		CRect m_rectCheckBox;
};