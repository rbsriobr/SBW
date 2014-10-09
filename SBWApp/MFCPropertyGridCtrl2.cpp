/*
This file is subject to the terms and conditions defined in
file 'LICENSE.txt', which is part of this source code package.
Copyright (C) 2013 Ricardo B. Santos.
All rights reserved
*/

#include "stdafx.h"
#include "MFCPropertyGridCtrl2.h"

// CMFCPropertyGridCtrl2

IMPLEMENT_DYNAMIC (CMFCPropertyGridCtrl2, CMFCPropertyGridCtrl)

CMFCPropertyGridCtrl2::CMFCPropertyGridCtrl2()
{

}

CMFCPropertyGridCtrl2::~CMFCPropertyGridCtrl2()
{
}

BEGIN_MESSAGE_MAP (CMFCPropertyGridCtrl2, CMFCPropertyGridCtrl)
END_MESSAGE_MAP()


void CMFCPropertyGridCtrl2::Recurs ( bool bLoad, CString &clData, CMFCPropertyGridProperty2 *pObj, int *iCurPos )
{
	for ( int i = 0; i < pObj->GetSubItemsCount ( ); i++ ) {
		CMFCPropertyGridProperty2 *pSubObj = dynamic_cast<CMFCPropertyGridProperty2 *> ( pObj->GetSubItem ( i ) );

		if ( pSubObj ) {
			if ( bLoad ) {
				CString clValue;

				if ( GetNext ( clData, clValue, *iCurPos ) ) {
					pSubObj->m_dwState = _ttoi ( clValue );

					if ( GetNext ( clData, clValue, *iCurPos ) ) {
						pSubObj->m_iRef = _ttoi ( clValue );

						if ( GetNext ( clData, clValue, *iCurPos ) ) {
							if ( pSubObj->m_clType == clValue ) {
								if ( GetNext ( clData, clValue, *iCurPos ) ) {
									if ( CString ( pSubObj->GetName ( ) ) == clValue ) {
										if ( GetNext ( clData, clValue, *iCurPos ) ) {
											COleVariant pVar = pSubObj->GetValue ( );
											VARTYPE vt = pVar.vt;
											pVar = clValue;
											pVar.ChangeType ( vt );
											pSubObj->SetValue ( pVar );
										}
									}
								}
							}
						}
					}
				}
			}

			else {
				CString State, Ref;
				State.Format ( _T ( "%d" ), pSubObj->m_dwState );
				Ref.Format ( _T ( "%d" ), pSubObj->m_iRef );
				CString Type = pSubObj->m_clType;
				CString Name = CString (pSubObj->GetName ( ));
				COleVariant pVar = pSubObj->GetValue ( );
				pVar.ChangeType ( VT_BSTR );
				CString Value = CString ( pVar.bstrVal );

				Name.Replace ( _T ( "\r" ), _T ( "\n" ) );
				Type.Replace ( _T ( "\r" ), _T ( "\n" ) );
				Value.Replace ( _T ( "\r" ), _T ( "\n" ) );

				clData += State + _T ( "\r" );
				clData += Ref + _T ( "\r" );
				clData += Type + _T ("\r");
				clData += Name + _T ( "\r" );
				clData += CString ( pVar.bstrVal ) + _T ("\r");
			}

			Recurs ( bLoad, clData, pSubObj, iCurPos );
		}
	}
}

DWORD CMFCPropertyGridCtrl2::Save ( CFile &clFile)
{
	CMFCPropertyGridProperty2 *pProp;
	CString clData;
	DWORD dwLen = 0;

	for ( int i = 0; i < GetPropertyCount ( ); i++ ) {
		pProp = ( CMFCPropertyGridProperty2 *) GetProperty ( i );

		if ( pProp ) {
			CString State, Ref;
			State.Format ( _T ( "%d" ), pProp->m_dwState );
			Ref.Format ( _T ( "%d" ), pProp->m_iRef );
			CString Type = pProp->m_clType;
			CString Name = CString ( pProp->GetName ( ) );
			COleVariant pVar = pProp->GetValue ( );
			pVar.ChangeType ( VT_BSTR );
			CString Value = CString ( pVar.bstrVal );

			Name.Replace ( _T ( "\r" ), _T ( "\n" ) );
			Type.Replace ( _T ( "\r" ), _T ( "\n" ) );
			Value.Replace ( _T ( "\r" ), _T ( "\n" ) );

			clData += State + _T ( "\r" );
			clData += Ref + _T ( "\r" );
			clData += Type + _T ( "\r" );
			clData += Name + _T ( "\r" );
			clData += CString ( pVar.bstrVal ) + _T ( "\r" );
			Recurs ( false, clData, pProp );
		}

		if ( !clData.IsEmpty ( ) ) {
			dwLen = clData.GetLength ( ) * sizeof ( TCHAR );
			clFile.Write ( clData.GetBuffer ( ), dwLen );
			clFile.Flush ( );
		}
	}

	return dwLen;
}

bool CMFCPropertyGridCtrl2::GetNext ( CString &clData, CString &clRes, int &iCurPos )
{
	BOOL res = AfxExtractSubString ( clRes, clData, iCurPos, '\r' );
	iCurPos++;
	return ( res == TRUE ? true : false);
}

bool CMFCPropertyGridCtrl2::Load ( CString &clData )
{
	CMFCPropertyGridProperty2 *pProp;
	DWORD dwLen = 0;
	int iCurPos = 0;
	CString clValue;

	for ( int i = 0; i < GetPropertyCount ( ); i++ ) {
		pProp = (CMFCPropertyGridProperty2 *) GetProperty ( i );

		if ( pProp ) {
			if ( GetNext ( clData, clValue, iCurPos ) ) {
				pProp->m_dwState = _ttoi ( clValue );

				if ( GetNext ( clData, clValue, iCurPos ) ) {
					pProp->m_iRef = _ttoi ( clValue );

					if ( GetNext ( clData, clValue, iCurPos ) ) {
						if ( pProp->m_clType == clValue ) {
							if ( GetNext ( clData, clValue, iCurPos ) ) {
								if ( CString ( pProp->GetName ( ) ) == clValue ) {
									if ( GetNext ( clData, clValue, iCurPos ) ) {
										pProp->SetValue ( clValue );
									}
								}
							}
						}
					}
				}

			}

			Recurs ( true, clData, pProp, &iCurPos );
		}
	}

	return true;
}




