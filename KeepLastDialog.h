#if !defined(AFX_KEEPLASTDIALOG_H__3173FA05_7E3F_11D3_9F2C_F9E3C248627D__INCLUDED_)
#define AFX_KEEPLASTDIALOG_H__3173FA05_7E3F_11D3_9F2C_F9E3C248627D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// KeepLastDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// KeepLastDialog dialog

class KeepLastDialog : public CDialog
{
// Construction
public:
	void RefreshDialog();
	BOOL m_checkspace;
	BOOL m_checkuser;
	BOOL m_checkseparator;
	CString m_userstr;
	KeepLastDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(KeepLastDialog)
	enum { IDD = IDD_DIALOG8 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(KeepLastDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(KeepLastDialog)
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

#endif // !defined(AFX_KEEPLASTDIALOG_H__3173FA05_7E3F_11D3_9F2C_F9E3C248627D__INCLUDED_)
