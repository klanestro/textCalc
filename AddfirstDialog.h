#if !defined(AFX_ADDFIRSTDIALOG_H__6ECAEAA5_7B18_11D3_9F2C_F4D33E810673__INCLUDED_)
#define AFX_ADDFIRSTDIALOG_H__6ECAEAA5_7B18_11D3_9F2C_F4D33E810673__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AddfirstDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AddfirstDialog dialog

class AddfirstDialog : public CDialog
{
// Construction
public:
	void RefreshDialog();
	CString m_insertstring;
	int m_skiplines;
	int m_insertspace;
	AddfirstDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(AddfirstDialog)
	enum { IDD = IDD_DIALOG2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AddfirstDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AddfirstDialog)
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDFIRSTDIALOG_H__6ECAEAA5_7B18_11D3_9F2C_F4D33E810673__INCLUDED_)
