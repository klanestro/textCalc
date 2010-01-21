// FormatDialog.cpp : implementation file
//

#include "stdafx.h"
#include "sample.h"
#include "FormatDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FormatDialog dialog


FormatDialog::FormatDialog(CWnd* pParent /*=NULL*/)
	: CDialog(FormatDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(FormatDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_numdigits=2;
	suffixstr="inches";
	prefixstr="$";
	m_formatdigits=FALSE;
	m_formatsuffix=FALSE;
	m_formatprefix=TRUE;
}


void FormatDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FormatDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FormatDialog, CDialog)
	//{{AFX_MSG_MAP(FormatDialog)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FormatDialog message handlers

void FormatDialog::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	m_formatprefix=((CButton *) GetDlgItem(IDC_CHECK1))->GetCheck(); 
	RefreshDialog();
	
}

void FormatDialog::OnCheck2() 
{
	// TODO: Add your control notification handler code here
	m_formatsuffix=((CButton *) GetDlgItem(IDC_CHECK2))->GetCheck(); 
	RefreshDialog();
	
}

void FormatDialog::OnCheck3() 
{
	// TODO: Add your control notification handler code here
	m_formatdigits=((CButton *) GetDlgItem(IDC_CHECK3))->GetCheck(); 
	RefreshDialog();
	
}

void FormatDialog::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	m_numdigits=((CComboBox*) GetDlgItem(IDC_COMBO1))->GetCurSel();
	
}

void FormatDialog::OnOK() 
{
	// TODO: Add extra validation here
	((CEdit *) GetDlgItem(IDC_EDIT1))->GetWindowText(prefixstr);
	((CEdit *) GetDlgItem(IDC_EDIT2))->GetWindowText(suffixstr);
	
	CDialog::OnOK();
}


void FormatDialog::RefreshDialog()
{
		
	if (m_formatprefix) {
		((CButton *) GetDlgItem(IDC_CHECK1))->SetCheck(1); 
		((CEdit *) GetDlgItem(IDC_EDIT1))->EnableWindow(TRUE);
	}
	else {
		((CButton *) GetDlgItem(IDC_CHECK1))->SetCheck(0); 
		((CEdit *) GetDlgItem(IDC_EDIT1))->EnableWindow(FALSE);
	}

	if (m_formatsuffix) {
		((CButton *) GetDlgItem(IDC_CHECK2))->SetCheck(1); 
		((CEdit *) GetDlgItem(IDC_EDIT2))->EnableWindow(TRUE);
	}
	else {
		((CButton *) GetDlgItem(IDC_CHECK2))->SetCheck(0); 
		((CEdit *) GetDlgItem(IDC_EDIT2))->EnableWindow(FALSE);
	}

	if (m_formatdigits) {
		((CButton *) GetDlgItem(IDC_CHECK3))->SetCheck(1); 
		((CComboBox*) GetDlgItem(IDC_COMBO1))->EnableWindow(TRUE);
	}
	else {
		((CButton *) GetDlgItem(IDC_CHECK3))->SetCheck(0); 
		((CComboBox*) GetDlgItem(IDC_COMBO1))->EnableWindow(FALSE);
	}


	((CEdit *) GetDlgItem(IDC_EDIT1))->SetWindowText(prefixstr);
	((CEdit *) GetDlgItem(IDC_EDIT2))->SetWindowText(suffixstr);
	((CComboBox*) GetDlgItem(IDC_COMBO1))->SetCurSel(m_numdigits);
	

}

BOOL FormatDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	RefreshDialog();
	((CEdit *) GetDlgItem(IDC_EDIT1))->SetFocus();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
