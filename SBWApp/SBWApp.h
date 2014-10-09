/*
	   This file is subject to the terms and conditions defined in
	   file 'LICENSE.txt', which is part of this source code package.
	   Copyright (C) 2014 Ricardo B. Santos.
	   All rights reserved
*/


// SBWApp.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSBWAppApp:
// See SBWApp.cpp for the implementation of this class
//

class CSBWAppApp : public CWinApp
{
	public:
		CSBWAppApp();

		// Overrides
	public:
		virtual BOOL InitInstance();

		// Implementation

		DECLARE_MESSAGE_MAP()
};

extern CSBWAppApp theApp;