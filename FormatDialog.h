#if !defined(AFX_FORMATDIALOG_H__6ECAEAA7_7B18_11D3_9F2C_F4D33E810673__INCLUDED_)
#define AFX_FORMATDIALOG_H__6ECAEAA7_7B18_11D3_9F2C_F4D33E810673__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FormatDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FormatDialog dialog

class FormatDialog : public CDialog
{
// Construction
public:
	void RefreshDialog();
	int m_numdigits;
	CString suffixstr;
	CString prefixstr;
	BOOL m_formatdigits;
	BOOL m_formatsuffix;
	BOOL m_formatprefix;
	FormatDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(FormatDialog)
	enum { IDD = IDD_DIALOG4 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FormatDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FormatDialog)
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnSelchangeCombo1();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMATDIALOG_H__6ECAEAA7_7B18_11D3_9F2C_F4D33E810673__INCLUDED_)
