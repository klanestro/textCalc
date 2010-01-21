#if !defined(AFX_KEEPFIRSTDIALOG_H__A21E3C85_7DCB_11D3_9F2C_A921FEA1E874__INCLUDED_)
#define AFX_KEEPFIRSTDIALOG_H__A21E3C85_7DCB_11D3_9F2C_A921FEA1E874__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// KeepFirstDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// KeepFirstDialog dialog

class KeepFirstDialog : public CDialog
{
// Construction
public:
	void RefreshDialog();
	BOOL m_checkspace;
	BOOL m_checkuser;
	BOOL m_checkseparator;
	CString m_userstr;
	KeepFirstDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(KeepFirstDialog)
	enum { IDD = IDD_DIALOG7 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(KeepFirstDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(KeepFirstDialog)
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEEPFIRSTDIALOG_H__A21E3C85_7DCB_11D3_9F2C_A921FEA1E874__INCLUDED_)
