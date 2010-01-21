// Sample.h : main header file for the SAMPLE application
//

#if !defined(AFX_TCSAMPLE_H__B1B69EC9_9FCE_11D2_8CA4_0080ADB8683C__INCLUDED_)
#define AFX_TCSAMPLE_H__B1B69EC9_9FCE_11D2_8CA4_0080ADB8683C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSampleApp:
// See Sample.cpp for the implementation of this class
//

class CSampleApp : public CWinApp
{
public:
	CString GetProgPath();
	BOOL IsFirstLoad();
	CSampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSampleApp)
	afx_msg void OnAppAbout();
	afx_msg void OnHelpHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCSAMPLE_H__B1B69EC9_9FCE_11D2_8CA4_0080ADB8683C__INCLUDED_)
