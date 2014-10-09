/*
This file is subject to the terms and conditions defined in
file 'LICENSE.txt', which is part of this source code package.
Copyright (C) 2013 Ricardo B. Santos.
All rights reserved
*/

#pragma once
// CNumEdit

#define MAXPRECISION 5

class CNumEdit : public CEdit {
		DECLARE_DYNAMIC ( CNumEdit )

	public:
		CNumEdit();
		virtual ~CNumEdit();

	protected:
		DECLARE_MESSAGE_MAP()
	public:
		afx_msg BOOL OnEnUpdate ( );
		afx_msg BOOL OnEnKillfocus ( );
		CString  m_sDec;
		CString  m_sNeg;
		double m_dIncDec;
		double m_dMinValue;
		double m_dMaxValue;
		double m_dDefValue;
		__int64 GetIValue ( );
		double GetDValue ( );
		void SetValue ( __int64 iValue, int iDig = 0 );
		void SetValue ( double dValue );
		int m_iDefDig;
		bool m_bInteger;
	protected:
		void Symbols ( CString &Dec, CString &Neg );
	public:
		int m_iPrecision;
		afx_msg void OnKeyDown ( UINT nChar, UINT nRepCnt, UINT nFlags );
};


