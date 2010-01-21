// AddlastDialog.cpp : implementation file
//

#include "stdafx.h"
#include "sample.h"
#include "AddlastDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AddlastDialog dialog


AddlastDialog::AddlastDialog(CWnd* pParent /*=NULL*/)
	: CDialog(AddlastDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(AddlastDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_insertstring="String";
	m_skiplines=1;
	m_insertspace=1;
}


void AddlastDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AddlastDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AddlastDialog, CDialog)
	//{{AFX_MSG_MAP(AddlastDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AddlastDialog message handlers

void AddlastDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void AddlastDialog::OnOK() 
{
	// TODO: Add extra validation here
	((CEdit *) GetDlgItem(IDC_EDIT1))->GetWindowText(m_insertstring);


	if (((CButton *) GetDlgItem(IDC_CHECK1))->GetCheck()) 
	{
		m_insertspace=1;		
	} 
	else m_insertspace=0;

	
	if (((CButton *) GetDlgItem(IDC_CHECK2))->GetCheck()){
		m_skiplines=1;		
	} 
	else m_skiplines=0;
	

	CDialog::OnOK();
}

BOOL AddlastDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	RefreshDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void AddlastDialog::RefreshDialog()
{
	if (m_insertspace==1)
		((CButton *) GetDlgItem(IDC_CHECK1))->SetCheck(1); 
	else
		((CButton *) GetDlgItem(IDC_CHECK1))->SetCheck(0); 

	if (m_skiplines==1)
		((CButton *) GetDlgItem(IDC_CHECK2))->SetCheck(1); 
	else
		((CButton *) GetDlgItem(IDC_CHECK2))->SetCheck(0); 

	((CEdit *) GetDlgItem(IDC_EDIT1))->SetWindowText(m_insertstring);

}


