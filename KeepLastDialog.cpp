// KeepLastDialog.cpp : implementation file
//

#include "stdafx.h"
#include "sample.h"
#include "KeepLastDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// KeepLastDialog dialog


KeepLastDialog::KeepLastDialog(CWnd* pParent /*=NULL*/)
	: CDialog(KeepLastDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(KeepLastDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_checkspace=TRUE;
	m_checkuser=FALSE;
	m_checkseparator=TRUE;
	m_userstr=",;=";
}


void KeepLastDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(KeepLastDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(KeepLastDialog, CDialog)
	//{{AFX_MSG_MAP(KeepLastDialog)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// KeepLastDialog message handlers

void KeepLastDialog::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	m_checkspace=((CButton *) GetDlgItem(IDC_CHECK1))->GetCheck(); 
	
}

void KeepLastDialog::OnCheck2() 
{
	// TODO: Add your control notification handler code here
	m_checkuser=((CButton *) GetDlgItem(IDC_CHECK2))->GetCheck(); 
	RefreshDialog();
	
	
}

void KeepLastDialog::OnCheck3() 
{
	// TODO: Add your control notification handler code here
	m_checkseparator=((CButton *) GetDlgItem(IDC_CHECK3))->GetCheck(); 
	
}

void KeepLastDialog::OnOK() 
{
	// TODO: Add extra validation here
	((CEdit *) GetDlgItem(IDC_EDIT1))->GetWindowText(m_userstr);
	
	CDialog::OnOK();
}

BOOL KeepLastDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	RefreshDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void KeepLastDialog::RefreshDialog()
{

	if (m_checkspace) {
		((CButton *) GetDlgItem(IDC_CHECK1))->SetCheck(1); 
	}
	else {
		((CButton *) GetDlgItem(IDC_CHECK1))->SetCheck(0); 
	}

	if (m_checkuser) {
		((CButton *) GetDlgItem(IDC_CHECK2))->SetCheck(1); 
		((CEdit *) GetDlgItem(IDC_EDIT1))->EnableWindow(TRUE);
	}
	else {
		((CButton *) GetDlgItem(IDC_CHECK2))->SetCheck(0); 
		((CEdit *) GetDlgItem(IDC_EDIT1))->EnableWindow(FALSE);
	}

	if (m_checkseparator) {
		((CButton *) GetDlgItem(IDC_CHECK3))->SetCheck(1); 
	}
	else {
		((CButton *) GetDlgItem(IDC_CHECK3))->SetCheck(0); 
	}


	((CEdit *) GetDlgItem(IDC_EDIT1))->SetWindowText(m_userstr);



}

