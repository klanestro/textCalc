#if !defined(AFX_APPLYDIALOG_H__8A3F3FCF_750A_11D3_9F2C_D4AB3B404CF1__INCLUDED_)
#define AFX_APPLYDIALOG_H__8A3F3FCF_750A_11D3_9F2C_D4AB3B404CF1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ApplyDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ApplyDialog dialog

class ApplyDialog : public CDialog
{
// Construction
public:
	void SaveStr(int org);
	CString m_str1;
	CString m_str2;
	CString m_str3;
	CString m_expression;
	double m_value;
	double m_factor;
	BOOL IsNumber(LPCTSTR pszchars,int length);
	int m_resultstatus;
	void RefreshDialog();
	int m_radioselect;
	ApplyDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ApplyDialog)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ApplyDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ApplyDialog)
	afx_msg void OnChangeEdit1();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit3();
	afx_msg void OnSelchangeCombo2();
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateEdit2();
	afx_msg void OnUpdateEdit3();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPLYDIALOG_H__8A3F3FCF_750A_11D3_9F2C_D4AB3B404CF1__INCLUDED_)
