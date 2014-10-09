/*
This file is subject to the terms and conditions defined in
file 'LICENSE.txt', which is part of this source code package.
Copyright (C) 2014 Ricardo B. Santos.
All rights reserved
*/

#include "stdafx.h"
#include "SBWApp.h"
#include "About.h"
#include "afxdialogex.h"

// CAbout dialog

IMPLEMENT_DYNAMIC (CAbout, CDialogEx)

CAbout::CAbout (CWnd *pParent /*=NULL*/)
	: CDialogEx (CAbout::IDD, pParent)
{

}

CAbout::~CAbout()
{
}

void CAbout::DoDataExchange (CDataExchange *pDX)
{
	CDialogEx::DoDataExchange ( pDX );
}


BEGIN_MESSAGE_MAP (CAbout, CDialogEx)
	ON_WM_CTLCOLOR ( )
END_MESSAGE_MAP ( )

// CAbout message handlers

HBRUSH CAbout::OnCtlColor ( CDC *pDC, CWnd *pWnd, UINT nCtlColor )
{
	//HBRUSH hbr = CDialogEx::OnCtlColor ( pDC, pWnd, nCtlColor );
	return m_clBrush;
}

BOOL CAbout::OnInitDialog ( )
{
	CDialogEx::OnInitDialog ( );

	m_clBrush.CreateSolidBrush ( RGB ( 255, 255, 255 ) );

	return TRUE;
}