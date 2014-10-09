/*
This file is subject to the terms and conditions defined in
file 'LICENSE.txt', which is part of this source code package.
Copyright (C) 2014 Ricardo B. Santos.
All rights reserved
*/

#pragma once

#include "MFCPropertyGridProperty2.h"
// CMFCPropertyGridCtrl2

class CMFCPropertyGridCtrl2 : public CMFCPropertyGridCtrl {
		DECLARE_DYNAMIC (CMFCPropertyGridCtrl2)

	public:
		CMFCPropertyGridCtrl2();
		virtual ~CMFCPropertyGridCtrl2();

		DWORD Save ( CFile &clFile );
		bool Load ( CString &clData );
	protected:
		void Recurs ( bool bLoad, CString &clData, CMFCPropertyGridProperty2 *pObj, int *iCurPos = NULL );
		bool GetNext ( CString &clData, CString &clRes, int &iCurPos );
		DECLARE_MESSAGE_MAP()
};


