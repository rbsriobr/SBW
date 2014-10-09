#include "stdafx.h"
#include "MFCPropertyGridProperty2.h"

////////////////////////////////////////////////////////////////////////////////
// CMFCPropertyGridProperty2 object


CMFCPropertyGridProperty2::CMFCPropertyGridProperty2 ( DWORD_PTR dwState, const CString &strGroupName, BOOL bIsValueList ) :
	CMFCPropertyGridProperty ( strGroupName, 0, bIsValueList )
{
	m_clType = _T ( "CMFCPropertyGridProperty2" );
	m_dwState = dwState;

	if ( ( m_dwState != BST_CHECKED ) && ( m_dwState != BST_UNCHECKED ) ) {
		m_dwState = -1;
	}

	m_iRef          = 0;
	OnUpdateAnyItem = NULL;
	m_rectCheckBox.SetRectEmpty ( );
}

CMFCPropertyGridProperty2::CMFCPropertyGridProperty2 ( DWORD_PTR dwState, const CString &strName, const COleVariant &varValue,
													   LPCTSTR lpszDescr, LPCTSTR lpszEditMask, LPCTSTR lpszEditTemplate, LPCTSTR lpszValidChars ) :
	CMFCPropertyGridProperty ( strName, varValue, lpszDescr, 0, lpszEditMask, lpszEditTemplate, lpszValidChars )
{
	m_clType = _T ( "CMFCPropertyGridProperty2" );
	m_dwState = dwState;

	if ( ( m_dwState != BST_CHECKED ) && ( m_dwState != BST_UNCHECKED ) ) {
		m_dwState = -1;
	}

	m_iRef          = 0;
	OnUpdateAnyItem = NULL;
	m_rectCheckBox.SetRectEmpty ( );
}

void CMFCPropertyGridProperty2::Root ( CMFCPropertyGridProperty2 **pObj )
{
	CMFCPropertyGridProperty2 *pPar = dynamic_cast<CMFCPropertyGridProperty2 *> ( ( *pObj )->GetParent ( ) );

	if ( pPar ) {
		pObj = &pPar;
		Root ( pObj );
	}
}

void CMFCPropertyGridProperty2::PropagateAll ( CMFCPropertyGridProperty2 *pObj )
{
	for ( int i = 0; i < pObj->GetSubItemsCount ( ); i++ ) {
		CMFCPropertyGridProperty2 *pSubObj = dynamic_cast<CMFCPropertyGridProperty2 *> ( pObj->GetSubItem ( i ) );

		if ( pSubObj ) {
			pSubObj->OnUpdateAnyItem = OnUpdateAnyItem;
			PropagateAll ( pSubObj );
		}
	}
}

void CMFCPropertyGridProperty2::Update ( )
{
	Root ( & (( CMFCPropertyGridProperty2 *)this) );
	PropagateAll ( ( this ) );
}

void CMFCPropertyGridProperty2::SetState ( DWORD_PTR dwState )
{
	m_dwState = dwState;
	m_pWndList->InvalidateRect ( m_rectCheckBox );
}

bool CMFCPropertyGridProperty2::Unchecked ( )
{
	if ( m_dwState == -1 )
		throw;
	return  m_dwState == BST_UNCHECKED ? true : false;
}

bool CMFCPropertyGridProperty2::Checked ( )
{
	if ( m_dwState == -1 )
		throw;
	return  m_dwState == BST_CHECKED ? true : false;
}

bool CMFCPropertyGridProperty2::Indeterminate ( )
{
	if ( m_dwState == -1 )
		throw;
	return  m_dwState == BST_INDETERMINATE ? true : false;
}

bool CMFCPropertyGridProperty2::GetBool ( ) {
	COleVariant pVar;
	pVar = GetValue ( );
	pVar.ChangeType ( VT_BOOL );
	if ( pVar.boolVal == 0 )
		return false;
	return true;
}

void CMFCPropertyGridProperty2::SetBool ( bool bValue ) {
	COleVariant varValue;
	varValue.ChangeType ( VT_BOOL );
	if ( bValue )
		varValue.boolVal = -1;
	else
		varValue.boolVal = 0;
	SetValue ( varValue );
}

__int64 CMFCPropertyGridProperty2::GetInt ( )
{
	COleVariant pVar;
	TCHAR *stopstring;
	pVar = GetValue ( );
	pVar.ChangeType ( VT_BSTR );
	return ( _tcstoi64 ( CString ( pVar.bstrVal ), &stopstring, 10 ) );
}

void CMFCPropertyGridProperty2::SetInt ( __int64 iValue )
{
	COleVariant varValue = iValue;
	varValue.ChangeType ( VT_BSTR );
	//m_varValue = varValue;
	SetValue ( varValue );
}

void CMFCPropertyGridProperty2::OnClickName ( CPoint point )
{
	if ( ( m_dwState & 0x80000000 ) == 0 ) {
		if ( m_bEnabled && m_rectCheckBox.PtInRect ( point ) ) {
			m_dwState = ( ( ( m_dwState == BST_UNCHECKED ) ||
							( m_dwState == BST_INDETERMINATE ) ) ? BST_CHECKED : ( m_iRef > 0 ? BST_INDETERMINATE : BST_UNCHECKED ) );
		}

		bool bHasUnchecked = false;
		bool bHasChecked = false;

		CMFCPropertyGridProperty2 *pObj = (CMFCPropertyGridProperty2 *) GetParent ( );

		if ( pObj ) {
			pObj->PropagateToRoot ( m_dwState, m_iRef );
		}


		m_pWndList->InvalidateRect ( m_rectCheckBox );

		if ( OnUpdateAnyItem ) {
			( this->*OnUpdateAnyItem ) ( this, false );
		}
	}
}

void CMFCPropertyGridProperty2::PropagateToRoot ( DWORD_PTR dwState, int iRef )
{
	if ( dwState == BST_CHECKED ) {
		iRef++;
	}

	m_iRef = iRef;

	if ( ( m_dwState & 0x80000000 ) == 0 ) {
		if ( m_dwState != BST_CHECKED ) {
			if ( m_iRef > 0 ) {
				m_dwState = BST_INDETERMINATE;
			}

			else {
				m_dwState = BST_UNCHECKED;
			}

			if ( m_pWndList ) {
				m_pWndList->InvalidateRect ( m_Rect );
			}
		}
	}

	CMFCPropertyGridProperty2 *pObj = (CMFCPropertyGridProperty2 *) GetParent ( );

	if ( pObj ) {
		pObj->PropagateToRoot ( m_dwState, m_iRef );
	}
}

BOOL CMFCPropertyGridProperty2::AddSubItem ( CMFCPropertyGridProperty2 *pProp )
{
	ASSERT_VALID ( this );

	if ( pProp ) {
		if ( pProp->OnUpdateAnyItem == NULL ) {
			if ( OnUpdateAnyItem ) {
				pProp->OnUpdateAnyItem = OnUpdateAnyItem;
			}
		}

		PropagateToRoot ( pProp->m_dwState, m_iRef );
	}

	return CMFCPropertyGridProperty::AddSubItem ( pProp );
}

BOOL CMFCPropertyGridProperty2::OnUpdateValue ( )
{
	if ( OnUpdateAnyItem ) {
		( this->*OnUpdateAnyItem ) ( this, true );
	}

	return CMFCPropertyGridProperty::OnUpdateValue ( );
}

void CMFCPropertyGridProperty2::OnDrawName ( CDC *pDC, CRect rect )
{
	if ( ( m_dwState & 0x80000000 ) == 0 ) {
		m_rectCheckBox = rect;
		m_rectCheckBox.DeflateRect ( 2, 2 );
		m_rectCheckBox.right = m_rectCheckBox.left + m_rectCheckBox.Height ( );
		rect.left = m_rectCheckBox.right + 1;
	}

	CMFCPropertyGridProperty::OnDrawName ( pDC, rect );

	if ( ( m_dwState & 0x80000000 ) == 0 ) {
		OnDrawCheckBox ( pDC, m_rectCheckBox, m_dwState );
	}
}

BOOL CMFCPropertyGridProperty2::OnDblClk ( CPoint point )
{
	if ( ( m_dwState & 0x80000000 ) == 0 ) {
		if ( m_bEnabled && m_rectCheckBox.PtInRect ( point ) ) {
			return TRUE;
		}

		m_dwState = ( m_dwState == 0 ? BST_CHECKED : BST_UNCHECKED );
		m_pWndList->InvalidateRect ( m_rectCheckBox );
	}

	return TRUE;
}

void CMFCPropertyGridProperty2::OnDrawCheckBox ( CDC *pDC, CRect rect, DWORD_PTR dwState )
{
	COLORREF clrTextOld = pDC->GetTextColor ( );
	CMFCVisualManager::GetInstance ( )->OnDrawCheckBoxEx ( pDC, rect, m_dwState, FALSE, FALSE, m_bEnabled );
	pDC->SetTextColor ( clrTextOld );
}
