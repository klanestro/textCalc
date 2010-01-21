// ComputeOptions.cpp : implementation file
//

#include "stdafx.h"
#include "sample.h"
#include "ComputeOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ComputeOptions dialog


ComputeOptions::ComputeOptions(CWnd* pParent /*=NULL*/)
	: CDialog(ComputeOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(ComputeOptions)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_checkspace=TRUE;
	m_checkuser=FALSE;
	m_userstr=",;(){}<>";
	m_RInextline=TRUE;
}


void ComputeOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ComputeOptions)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ComputeOptions, CDialog)
	//{{AFX_MSG_MAP(ComputeOptions)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ComputeOptions message handlers

void ComputeOptions::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	m_checkspace=((CButton *) GetDlgItem(IDC_CHECK1))->GetCheck(); 
	
}

void ComputeOptions::OnCheck2() 
{
	// TODO: Add your control notification handler code here
	m_checkuser=((CButton *) GetDlgItem(IDC_CHECK2))->GetCheck(); 
	RefreshDialog();

	
}

void ComputeOptions::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	
	((CButton *) GetDlgItem(IDC_RADIO2))->SetCheck(0); 
	m_RInextline=TRUE;
	
}

void ComputeOptions::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	((CButton *) GetDlgItem(IDC_RADIO1))->SetCheck(0); 
	m_RInextline=FALSE;
	
	
}

void ComputeOptions::OnOK() 
{
	// TODO: Add extra validation here
	((CEdit *) GetDlgItem(IDC_EDIT1))->GetWindowText(m_userstr);
	
	CDialog::OnOK();
}

BOOL ComputeOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	RefreshDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void ComputeOptions::RefreshDialog()
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


	if (m_RInextline) {
		((CButton *) GetDlgItem(IDC_RADIO1))->SetCheck(1); 
		((CButton *) GetDlgItem(IDC_RADIO2))->SetCheck(0); 
	}
	else {
		((CButton *) GetDlgItem(IDC_RADIO1))->SetCheck(0); 
		((CButton *) GetDlgItem(IDC_RADIO2))->SetCheck(1); 
	}


	((CEdit *) GetDlgItem(IDC_EDIT1))->SetWindowText(m_userstr);


}
