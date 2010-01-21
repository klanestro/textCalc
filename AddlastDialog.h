#if !defined(AFX_ADDLASTDIALOG_H__6ECAEAA6_7B18_11D3_9F2C_F4D33E810673__INCLUDED_)
#define AFX_ADDLASTDIALOG_H__6ECAEAA6_7B18_11D3_9F2C_F4D33E810673__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AddlastDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AddlastDialog dialog

class AddlastDialog : public CDialog
{
// Construction
public:
	int m_insertspace;
	int m_skiplines;
	CString m_insertstring;
	void RefreshDialog();
	AddlastDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(AddlastDialog)
	enum { IDD = IDD_DIALOG3 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AddlastDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AddlastDialog)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDLASTDIALOG_H__6ECAEAA6_7B18_11D3_9F2C_F4D33E810673__INCLUDED_)
