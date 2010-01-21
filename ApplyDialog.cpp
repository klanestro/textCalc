// ApplyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "sample.h"
#include "ApplyDialog.h"
#include "SampleView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ApplyDialog dialog


ApplyDialog::ApplyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(ApplyDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(ApplyDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_radioselect=0;
	m_resultstatus=0;
	m_str1="1.0";
	m_str2="0.0";
	m_str3="2*x";

}


void ApplyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ApplyDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ApplyDialog, CDialog)
	//{{AFX_MSG_MAP(ApplyDialog)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	ON_WM_CREATE()
	ON_EN_UPDATE(IDC_EDIT2, OnUpdateEdit2)
	ON_EN_UPDATE(IDC_EDIT3, OnUpdateEdit3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ApplyDialog message handlers

void ApplyDialog::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}

void ApplyDialog::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	SaveStr(m_radioselect);
	m_radioselect=0;
	RefreshDialog();
}

void ApplyDialog::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	SaveStr(m_radioselect);
	m_radioselect=1;
	RefreshDialog();
	
}

void ApplyDialog::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	SaveStr(m_radioselect);
	m_radioselect=2;
	RefreshDialog();
	
}

void ApplyDialog::OnChangeEdit2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
		
}

void ApplyDialog::OnChangeEdit3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}

void ApplyDialog::OnSelchangeCombo2() 
{
	// TODO: Add your control notification handler code here
	m_resultstatus=((CComboBox*) GetDlgItem(IDC_COMBO2))->GetCurSel();


	
}

BOOL ApplyDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

		
	// TODO: Add extra initialization here
	RefreshDialog();
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int ApplyDialog::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here


	return 0;
}

void ApplyDialog::RefreshDialog()
{
	switch (m_radioselect) {

		case 0:{
				((CButton *) GetDlgItem(IDC_RADIO1))->SetCheck(1); 
				((CEdit *) GetDlgItem(IDC_EDIT2))->EnableWindow(TRUE);
				((CEdit *) GetDlgItem(IDC_EDIT3))->EnableWindow(FALSE); 
				((CEdit *) GetDlgItem(IDC_EDIT1))->EnableWindow(FALSE);

				((CEdit *) GetDlgItem(IDC_EDIT2))->SetFocus();
				break;
			   }
		case 1:{
				((CButton *) GetDlgItem(IDC_RADIO2))->SetCheck(1); 
				((CEdit *) GetDlgItem(IDC_EDIT2))->EnableWindow(FALSE);
				((CEdit *) GetDlgItem(IDC_EDIT3))->EnableWindow(TRUE); 
				((CEdit *) GetDlgItem(IDC_EDIT1))->EnableWindow(FALSE);

				((CEdit *) GetDlgItem(IDC_EDIT3))->SetFocus();
				break;
			   }
		case 2:{
				((CButton *) GetDlgItem(IDC_RADIO3))->SetCheck(1); 
				((CEdit *) GetDlgItem(IDC_EDIT2))->EnableWindow(FALSE);
				((CEdit *) GetDlgItem(IDC_EDIT3))->EnableWindow(FALSE); 
				((CEdit *) GetDlgItem(IDC_EDIT1))->EnableWindow(TRUE);

				((CEdit *) GetDlgItem(IDC_EDIT1))->SetFocus();
				break;
			   }
	
	}

	((CComboBox*) GetDlgItem(IDC_COMBO2))->SetCurSel(m_resultstatus);;

	((CEdit *) GetDlgItem(IDC_EDIT2))->SetWindowText(m_str1);
	((CEdit *) GetDlgItem(IDC_EDIT3))->SetWindowText(m_str2);
	((CEdit *) GetDlgItem(IDC_EDIT1))->SetWindowText(m_str3);

}


BOOL ApplyDialog::IsNumber(LPCTSTR pszChars, int nLength)
{

	if (nLength==1)  {
		if ((pszChars[0]=='.') || (pszChars[0]=='-'))
			return FALSE;

	}
	else if (nLength==2)  {
		if ((pszChars[0]=='-') && (pszChars[1]=='.'))
			return FALSE;

	}
	
	//The first char cannot be a 'e', must only be digit or '.'
	int state=0;
	if (!isdigit(pszChars[0])) {

		if (pszChars[0]=='.') {

			state=1;
		}
		else if (pszChars[0]=='-') {

			state=0;
		}
		else
			return FALSE;

	}
	//else state=0;

	//[whitespace] [sign] [digits] [.digits] [ {d | D | e | E }[sign]digits]
	//the first must be a digit or dec point
	//what about using atof itself to test?

	int I=1;
	while ((state==0) && (I<nLength)) {

		if (pszChars[I]=='.') {
			state=1;
			I++;
			break;
		}
		
		if (!isdigit(pszChars[I])) return FALSE;
		I++;
	}
		
	
	//dec point detected
	while ((state==1) && (I<nLength)) {

	
		if (!isdigit(pszChars[I])) return FALSE;
		I++;
	}
	return TRUE;


}


void ApplyDialog::OnUpdateEdit2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	/*
	CEdit *tmpEdit=((CEdit *) GetDlgItem(IDC_EDIT2));
	if (tmpEdit->IsWindowEnabled()) {
		
		tmpEdit->GetWindowText(m_oldstr2);

	}
	*/
	
	
}

void ApplyDialog::OnUpdateEdit3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
	
}



void ApplyDialog::OnOK() 
{
	// TODO: Add extra validation here
	
	

	if (m_radioselect==0) {

		CString rStr;
		((CEdit *) GetDlgItem(IDC_EDIT2))->GetWindowText(rStr);
		int len=rStr.GetLength();
		BOOL rx=IsNumber(rStr, len);
		if (!rx) {//restore original text

			MessageBox("Invalid factor. Please enter a number.","Note",MB_ICONEXCLAMATION  | MB_OK);
			return;

		}

		((CEdit *) GetDlgItem(IDC_EDIT2))->GetWindowText(m_str1);
		m_factor=atof(rStr);

	}
	else if (m_radioselect==1) {

		CString rStr;
		((CEdit *) GetDlgItem(IDC_EDIT3))->GetWindowText(rStr);
		int len=rStr.GetLength();
		BOOL rx=IsNumber(rStr, len);
		if (!rx) {//restore original text

			MessageBox("Invalid value. Please enter a number.","Note",MB_ICONEXCLAMATION  | MB_OK);
			return;

		}

		((CEdit *) GetDlgItem(IDC_EDIT3))->GetWindowText(m_str2);
		m_value=atof(rStr);

	}
	else if (m_radioselect==2) {

		double resultval;
		CString rStr;
		((CEdit *) GetDlgItem(IDC_EDIT1))->GetWindowText(rStr);
		int len=rStr.GetLength();
		CString retStr="";
		int rx=CSampleView::EvalExpression(1, 0,rStr,resultval,retStr);
		if (rx>=0) {//invalid expression
		
			MessageBox("Invalid expression. Please reenter expression.","Note",MB_ICONEXCLAMATION  | MB_OK);
			return;

		}

		((CEdit *) GetDlgItem(IDC_EDIT1))->GetWindowText(m_str3);
		m_expression=CSampleView::RemoveWhiteSpace(rStr);

	}
	
	CDialog::OnOK();

	
}

void ApplyDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void ApplyDialog::SaveStr(int org)
{
	if (org==0) {
		CString rStr;
		((CEdit *) GetDlgItem(IDC_EDIT2))->GetWindowText(rStr);
		int len=rStr.GetLength();
		BOOL rx=IsNumber(rStr, len);
		if (!rx) {//restore original text
			
			//do nothing, don't save result
		}
		else //save result
		{
			
			m_str1=rStr;
		}
	}
	else if (org==1) {
		CString rStr;
		((CEdit *) GetDlgItem(IDC_EDIT3))->GetWindowText(rStr);
		int len=rStr.GetLength();
		BOOL rx=IsNumber(rStr, len);
		if (!rx) {//restore original text
			
			//do nothing, don't save result
		}
		else //save result
		{
			
			m_str2=rStr;
		}
	}
	else if (org==2) {
		double resultval;
		CString rStr;
		((CEdit *) GetDlgItem(IDC_EDIT1))->GetWindowText(rStr);
		int len=rStr.GetLength();
		CString retStr="";
		int rx=CSampleView::EvalExpression(1, 0,rStr,resultval,retStr);
		if (rx>=0) {//invalid expression
		
			//do nothing, don't save result
		}
		else //save result
		{
			m_str3=CSampleView::RemoveWhiteSpace(rStr);
		}
	}


}

		
