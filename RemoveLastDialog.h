#if !defined(AFX_REMOVELASTDIALOG_H__8475DDCF_7DA1_11D3_9F2C_A4ABDB6BDD24__INCLUDED_)
#define AFX_REMOVELASTDIALOG_H__8475DDCF_7DA1_11D3_9F2C_A4ABDB6BDD24__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RemoveLastDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RemoveLastDialog dialog

class RemoveLastDialog : public CDialog
{
// Construction
public:
	void RefreshDialog();
	BOOL m_checkspace;
	BOOL m_checkuser;
	BOOL m_checkseparator;
	CString m_userstr;
	RemoveLastDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(RemoveLastDialog)
	enum { IDD = IDD_DIALOG6 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RemoveLastDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RemoveLastDialog)
	afx_msg void OnCheck1();
	afx_msg void OnCheck3();
	afx_msg void OnCheck2();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REMOVELASTDIALOG_H__8475DDCF_7DA1_11D3_9F2C_A4ABDB6BDD24__INCLUDED_)
