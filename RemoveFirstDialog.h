#if !defined(AFX_REMOVEFIRSTDIALOG_H__03F38169_7CF8_11D3_9F2C_C77F612E6270__INCLUDED_)
#define AFX_REMOVEFIRSTDIALOG_H__03F38169_7CF8_11D3_9F2C_C77F612E6270__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RemoveFirstDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RemoveFirstDialog dialog

class RemoveFirstDialog : public CDialog
{
// Construction
public:
	void RefreshDialog();
	BOOL m_checkspace;
	BOOL m_checkuser;
	BOOL m_checkseparator;
	CString m_userstr;
	RemoveFirstDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(RemoveFirstDialog)
	enum { IDD = IDD_DIALOG5 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RemoveFirstDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RemoveFirstDialog)
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

#endif // !defined(AFX_REMOVEFIRSTDIALOG_H__03F38169_7CF8_11D3_9F2C_C77F612E6270__INCLUDED_)
