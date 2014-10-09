/*
This file is subject to the terms and conditions defined in
file 'LICENSE.txt', which is part of this source code package.
Copyright (C) 2014 Ricardo B. Santos.
All rights reserved
*/

#pragma once
#include "stdafx.h"
#include "afxwin.h"

// CAbout dialog

class CAbout : public CDialogEx {
		DECLARE_DYNAMIC ( CAbout )

	public:
		CAbout ( CWnd *pParent = NULL ); // standard constructor
		virtual ~CAbout();

		// Dialog Data
		enum {
			IDD = IDD_ABOUT
		};

	protected:
		CBrush m_clBrush;
		virtual void DoDataExchange ( CDataExchange *pDX ); // DDX/DDV support
		DECLARE_MESSAGE_MAP()
	public:
		afx_msg HBRUSH OnCtlColor ( CDC *pDC, CWnd *pWnd, UINT nCtlColor );
		virtual BOOL OnInitDialog ( );
};
