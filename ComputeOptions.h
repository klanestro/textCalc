#if !defined(AFX_OMPUTEOPTIONS_H__D2E32C89_873B_11D3_9F2C_9A7B6EAD7F30__INCLUDED_)
#define AFX_OMPUTEOPTIONS_H__D2E32C89_873B_11D3_9F2C_9A7B6EAD7F30__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// omputeOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ComputeOptions dialog

class ComputeOptions : public CDialog
{
// Construction
public:
	void RefreshDialog();
	BOOL m_checkspace;
	BOOL m_checkuser;
	BOOL m_checkseparator;
	CString m_userstr;
	BOOL m_RInextline;
	ComputeOptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ComputeOptions)
	enum { IDD = IDD_DIALOG9 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ComputeOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ComputeOptions)
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OMPUTEOPTIONS_H__D2E32C89_873B_11D3_9F2C_9A7B6EAD7F30__INCLUDED_)
