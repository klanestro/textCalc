// SampleView.cpp : implementation of the CSampleView class
//

#include "stdafx.h"


#include "Sample.h"
#include "SampleDoc.h"
#include "SampleView.h"
#include <math.h>

#include "ApplyDialog.h"
#include "AddfirstDialog.h"
#include "AddlastDialog.h"
#include "FormatDialog.h"
#include "RemoveFirstDialog.h"
#include "RemoveLastDialog.h"
#include "KeepFirstDialog.h"
#include "KeepLastDialog.h"
#include "ComputeOptions.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSampleView

IMPLEMENT_DYNCREATE(CSampleView, CCrystalEditView)

BEGIN_MESSAGE_MAP(CSampleView, CCrystalEditView)
	//{{AFX_MSG_MAP(CSampleView)
	ON_WM_CONTEXTMENU()
	ON_WM_CREATE()
	ON_COMMAND(Calculate, OnCalculate)
	ON_WM_DESTROY()
	ON_COMMAND(Sumx, OnSum)
	ON_COMMAND(ID_CALCULATE_AVERAGE, OnCalculateAverage)
	ON_COMMAND(ID_CALCULATE_SUMOFSQUARES, OnCalculateSumofsquares)
	ON_COMMAND(ID_CALCULATE_ROOTMEANSQUARE, OnCalculateRootmeansquare)
	ON_COMMAND(ID_CALCULATE_MEANDEVIATIONFROMMEAN, OnCalculateMdmean)
	ON_COMMAND(ID_CALCULATE_COUNTITEMS, OnCalculateCountitems)
	ON_COMMAND(ID_CALCULATE_MEDIAN, OnCalculateMedian)
	ON_COMMAND(ID_CALCULATE_STANDARDDEVIATION, OnCalculateStandarddeviation)
	ON_COMMAND(ID_CALCULATE_VARIANCE, OnCalculateVariance)
	ON_COMMAND(ID_CALCULATE_APPLYNUMBERS, OnCalculateApplynumbers)
	ON_COMMAND(ID_CALCULATE_FINDMINANDMAXVALUES, OnCalculateFindminandmaxvalues)
	ON_COMMAND(ID_TEXT_ADDFIRSTWORD, OnTextAddfirstword)
	ON_COMMAND(ID_TEXT_ADDLASTWORD, OnTextAddlastword)
	ON_COMMAND(ID_CALCULATE_FORMATNUMBERS, OnCalculateFormatnumbers)
	ON_COMMAND(ID_TEXT_REMOVEFIRSTWORD, OnTextRemovefirstword)
	ON_COMMAND(ID_TEXT_REMOVELASTWORD, OnTextRemovelastword)
	ON_COMMAND(ID_TEXT_KEEPFIRSTWORD, OnTextKeepfirstword)
	ON_COMMAND(ID_TEXT_KEEPLASTWORD, OnTextKeeplastword)
	ON_COMMAND(ID_CALCULATE_EXTRACTNUMBERS, OnCalculateExtractnumbers)
	ON_COMMAND(ID_TEXT_MAKEINTOONELINE, OnTextMakeintooneline)
	ON_COMMAND(ID_CALCULATE_COMPUTEOPTIONS, OnCalculateComputeoptions)
	ON_COMMAND(ID_BUTTON32829, OnButton32829)
	ON_COMMAND(Dec, OnDec)
	ON_COMMAND(ID_CONVERSION_DECIMALTOHEX, OnConversionDecimaltohex)
	ON_COMMAND(ID_CONVERSION_DECIMALTOOCT, OnConversionDecimaltooct)
	ON_COMMAND(ID_CONVERSION_HEXTODECIMAL, OnConversionHextodecimal)
	ON_COMMAND(ID_CONVERSION_OCTTODECIMAL, OnConversionOcttodecimal)
	ON_COMMAND(ID_CALCULATE_PI3141592654, OnCalculatePi3141592654)
	ON_COMMAND(ID_CONVERSION_UNITS, OnConversionUnits)
	ON_COMMAND(ID_CONVERSION_TABLES_AREA, OnConversionTablesArea)
	ON_COMMAND(ID_CONVERSION_TABLES_VOLUME, OnConversionTablesVolume)
	ON_COMMAND(ID_CONVERSION_TABLES_WEIGHT, OnConversionTablesWeight)
	ON_COMMAND(ID_CONVERSION_HEXTOOCT, OnConversionHextooct)
	ON_COMMAND(ID_CONVERSION_OCTTOHEX, OnConversionOcttohex)
	ON_COMMAND(ID_HELP_RENDERSOFTPRODUCTS_VRMLEDITOR, OnHelpRendersoftproductsVrmleditor)
	ON_COMMAND(ID_HELP_RENDERSOFTPRODUCTS_ATOMIXBUTTONS, OnHelpRendersoftproductsAtomixbuttons)
	ON_COMMAND(ID_HELP_RENDERSOFTPRODUCTS_ILLUSIONAE, OnHelpRendersoftproductsIllusionae)
	ON_COMMAND(ID_HELP_TEXTCALCWEBSITE, OnHelpTextcalcwebsite)
	ON_COMMAND(ID_TEXT_NUMBERLINE, OnTextNumberline)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CCrystalEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CCrystalEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CCrystalEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleView construction/destruction

static const char *crlfsx[] =
{
	"\x0d\x0a",	//	DOS/Windows style
	"\x0a",		//	UNIX style
	"\x0d"		//	Macintosh style
};


//**************  prototypes here ****************
int compare( const void *arg1, const void *arg2 );
ApplyDialog m_adx;
AddfirstDialog m_addfirst;
AddlastDialog m_addlast;
FormatDialog m_format;
RemoveFirstDialog m_removefirst;
RemoveLastDialog m_removelast;
KeepFirstDialog m_keepfirst;
KeepLastDialog m_keeplast;
ComputeOptions m_computeoptions;


CSampleView::CSampleView()
{
	// TODO: add construction code here
	m_opSelectPartial=1;
	m_dataval=NULL;

	m_applytype=0;
	m_applyfactor=0;
	m_applyvalue=0;
	m_applyexpression="";

	m_insertText="";
	m_lastcount=0;

	m_insertspacebeforeword=TRUE;
	m_insertspaceafterword=TRUE;
	m_addlastword="";
	m_addfirstword="";
	m_resultsinnextline=TRUE;

	m_hexspace=TRUE;
	m_hexuser=FALSE;
	m_hexuserstr=",;(){}<>";
	
}

CSampleView::~CSampleView()
{
}

BOOL CSampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CCrystalEditView::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CSampleView diagnostics

#ifdef _DEBUG
void CSampleView::AssertValid() const
{
	CCrystalEditView::AssertValid();
}

void CSampleView::Dump(CDumpContext& dc) const
{
	CCrystalEditView::Dump(dc);
}

CSampleDoc* CSampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSampleDoc)));
	return (CSampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSampleView message handlers

CCrystalTextBuffer *CSampleView::LocateTextBuffer()
{
	return &GetDocument()->m_xTextBuffer;
}

void CSampleView::OnInitialUpdate() 
{
	CCrystalEditView::OnInitialUpdate();
	CPoint pt(0,0);
	SetCursorPos(pt);
	//SetFont(GetDocument()->m_lf);
}

void CSampleView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	/*
	//AfxMessageBox("Build your own context menu!");
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_MENU1));
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
 
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
	*/

}

void CSampleView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	SetFont(GetDocument()->m_lf);
	
}

int CSampleView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CCrystalEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_VarsMap.InitHashTable(10);
	m_expression.AtachVariables(&m_VarsMap);

	m_ExprStr = _T("");
	m_Result = 0.0;

	
	return 0;
}



CString CSampleView::ValidatePrefix(CString newstr,int& prefixpresent) {

	prefixpresent=0;

	int lenx=0;
	lenx=newstr.GetLength();

	if (lenx>0) {
		if ((newstr[0]=='+') || (newstr[0]=='-')) {

			newstr='0' + newstr;	
			prefixpresent=0;

		}
	}

	return newstr;

}


CString CSampleView::ValidateSuffix(CString newstr, int& suffixpresent) {

	suffixpresent=0;

	int lenx=0;
	lenx=newstr.GetLength();

	if (lenx>0) {
		
		if (newstr[lenx-1]=='=') {

			newstr.SetAt( lenx-1, ' ');	
			suffixpresent=1;

		}
	}

	return newstr;

}


CString CSampleView::RemoveWhiteSpace(CString m_ExprStr) {

	CString newstr="";
	int lenx=m_ExprStr.GetLength();

	for (int i=0;i<lenx;i++) {

		//will not work for multibyte
		if ((m_ExprStr[i]==' ') || (m_ExprStr[i]=='\n') || (m_ExprStr[i]=='\t')) {

		}
		else {
		
			newstr+=m_ExprStr[i];	
				
		}

	}	
	return newstr;

}


CString CSampleView::ChopNewline(CString m_ExprStr) {


	CString newstr="";

	int lenx=m_ExprStr.GetLength();


	for (int i=0;i<lenx;i++) {

		//will not work for multibyte
		if (m_ExprStr[i]=='x0a') {

			if ((i+1)<lenx) {
				if (m_ExprStr[i+1]=='x0d') {

					break;

				}
			}
			

		}
		else {
		
			newstr+=m_ExprStr[i];	
				
		}

	}	


	return newstr;

}



void CSampleView::OnCalculate() 
{
	// TODO: Add your command handler code here
	UpdateData();


	int nCrlfStyle = m_pTextBuffer->GetCRLFMode();
	const char *pszCRLF = crlfsx[nCrlfStyle];
	int nCRLFLength = strlen(pszCRLF);
	CString newline(pszCRLF,nCRLFLength);
	

	CString ExprStr;
	CString resultstr="";
	int vd=0;
	int strtype=0;
	int nLength;
	
	
	//If selection size ==0, use the current line (where cursor resides) as selection! 
	CPoint sStart,sEnd;
	GetSelection(sStart, sEnd);
	if (sStart == sEnd) {

		sStart=GetCursorPos();
		sEnd=GetCursorPos();


		CPoint ptCursorPos=	GetCursorPos();
		nLength = GetLineLength(ptCursorPos.y);
		LPCTSTR pszChars=GetLineChars(ptCursorPos.y);
		CString tempStr(pszChars,nLength); 
		ExprStr=tempStr;
		strtype=0;

	}
	else 
		strtype=1;


	CString newstr="";
	for (int i=sStart.y;i<=sEnd.y;i++) {

		if (strtype==1) {

			nLength = GetLineLength(i);
			LPCTSTR pszChars=GetLineChars(i);
			CString tempStr(pszChars,nLength); 

			if (m_opSelectPartial==1) {
			
				if ((sStart.y==i) && (sStart.x>0))
					ExprStr=tempStr.Right(nLength-sStart.x);
				else		
					ExprStr=tempStr;

				if ((sEnd.y==i) && (sEnd.x<nLength)) {


					if (sStart.y!=sEnd.y)
						ExprStr=ExprStr.Left(sEnd.x);
					else {
						int slength=sEnd.x-sStart.x;
						ExprStr=ExprStr.Left(slength);
					}
				}

			}
			else {

				ExprStr=tempStr;

			}
	
		}
	

		
		if ((i==sEnd.y) && (m_opSelectPartial==0)) {

			int sLength = GetLineLength(i);
			LPCTSTR pszChars=GetLineChars(i);
			CString tempStr(pszChars,sLength); 
			newstr+=tempStr;	

		}
		else {

			//no matter single line or block of lines, set it to ExprStr;
			newstr+=ExprStr;

		}
		
	
	
		ExprStr=RemoveWhiteSpace(ExprStr);
		
		if (ExprStr!="") {

			int result  = m_expression.ChangeExpression(ExprStr);

			
			if (result<0)
			{
				long result = m_expression.Value(m_Result);
				if ((result == ERROR_CODE) || (m_expression.errorstatus==1)) {

					char pszNewText[100];
					sprintf(pszNewText," [Error] ");
					CString result(pszNewText,strlen(pszNewText));
					newstr+=result;
					resultstr="Error";
										
				}
				else if (result == DIVISION_BY_0) {

					char pszNewText[100];
					sprintf(pszNewText," [Divide_By_0] ");
					CString result(pszNewText,strlen(pszNewText));
					newstr+=result;
					resultstr="Divide_By_0";
										
				}
				else if (result == UNKNOWN_ROOT) {

					char pszNewText[100];
					sprintf(pszNewText," [???] ");
					CString result(pszNewText,strlen(pszNewText));
					newstr+=result;
					resultstr="???";
										
				}
				else {
					
					
					char pszNewText[100];
					
					if (fabs(m_Result)<0.0000000000001) m_Result=0;
					sprintf(pszNewText," [%.12g] ",m_Result);
					CString result(pszNewText,strlen(pszNewText));
					newstr+=result;
					resultstr.Format("%.12g",m_Result);
					
				}
			}
			else 
			{
				// evaluation error				
				char pszNewText[100];
				sprintf(pszNewText," [Error] ");
				CString result(pszNewText,strlen(pszNewText));
				newstr+=result;
				resultstr="Error";
								
			}

		}//if (Expr!=null)
		
		if (i!=sEnd.y)
			newstr+=newline;
	
	}


	if (strtype==0) //single line with no selection
	{
	
		if (m_resultsinnextline) {

				//TRACE("\nyea, here!%d",sStart.y);
				resultstr=newline+resultstr;

				
				int xx,yy,linelength;
				linelength=GetLineLength(sStart.y);
				m_pTextBuffer->InsertText(this, sStart.y , linelength, resultstr, yy, xx, CE_ACTION_UNKNOWN);

				//set selection at end of next line (result line)
				xx=GetLineLength(sStart.y+1);
				CPoint newsel(xx,sStart.y+1);
				SetCursorPos(newsel);
				
				SetSelection(newsel,newsel);				

		}
		else
			PasteSelection(newstr,0);


	}
	else 
		PasteSelection(newstr,m_opSelectPartial);

	

	UpdateData(FALSE);
	
}

void CSampleView::OnDestroy() 
{
	CCrystalEditView::OnDestroy();
	
	// TODO: Add your message handler code here
	POSITION pos = m_VarsMap.GetStartPosition();
	while (pos != NULL)
	{
		CString sName;
		CValue *pVal;
		m_VarsMap.GetNextAssoc (pos, sName, pVal);
		delete pVal;
	}
	m_VarsMap.RemoveAll();	

	if (m_dataval!=NULL) free(m_dataval);
}



BOOL CSampleView::WorkSingleLine(int nLineIndex,int xstart, int xend,int function,int wtype)
{

	double diff;
	int x;
	ASSERT(nLineIndex >= -1 && nLineIndex < GetLineCount());

	if (nLineIndex == -1)
	{
		return TRUE;
	}

	int nLength = GetLineLength(nLineIndex);
	if (nLength == 0)
	{
		return TRUE;
	}

	//	Parse the line
	LPCTSTR pszChars = GetLineChars(nLineIndex);
	DWORD dwCookie = GetParseCookie(nLineIndex - 1);
	TEXTBLOCK *pBuf = (TEXTBLOCK *) _alloca(sizeof(TEXTBLOCK) * nLength * 3);
	int nBlocks = 0;
	m_pdwParseCookies[nLineIndex] = ParseLine(dwCookie, nLineIndex, pBuf, nBlocks);
	ASSERT(m_pdwParseCookies[nLineIndex] != (DWORD) -1);

	
	if (nBlocks > 0)
	{

		ASSERT(pBuf[0].m_nCharPos >= 0 && pBuf[0].m_nCharPos <= nLength);
	
		
		if ((nBlocks==1) && (pBuf[0].m_nColorIndex==COLORINDEX_NUMBER)) 
		{

			//this case has not yet occured
			LPCTSTR pszLine = GetLineChars(nLineIndex);
			int xLength = GetLineLength(nLineIndex);
			CString tempStr(pszLine,xLength); 

			ASSERT(TRUE);
			//TRACE("\nSingle : %s\n",LPCTSTR(tempStr));

		}

		for (int I = 1; I < nBlocks+1 ; I ++)
		{
			if (I<nBlocks) {
				ASSERT(pBuf[I].m_nCharPos >= 0 && pBuf[I].m_nCharPos <= nLength);
			}
			
			if (pBuf[I-1].m_nColorIndex==COLORINDEX_NUMBER) {

				int beginn,endn;
				char tempnum[200];
				
				beginn=pBuf[I-1].m_nCharPos;
				
				if (I==nBlocks) 
					endn=nLength;
				else
					endn=pBuf[I].m_nCharPos;

				ASSERT(endn>=beginn);


				//check bounds
				if ((xstart==-1) && (xend==-1)) {
					//ok proceed
				}
				else if ((xstart>beginn) && (xstart<endn)) {

					AfxMessageBox("Ambiguous bounds in start of selection! Cannot select part of a number!");
					//TRACE("AmbBounds : xstart%d, xend%d, beginn%d, endn%d",xstart, xend, beginn, endn);

					return FALSE;
				}
				else if ((xend>beginn) && (xend<endn)) {
					
					AfxMessageBox("Ambiguous bounds in end of selection! Cannot select part of a number!");
					//TRACE("AmbBounds : xstart%d, xend%d, beginn%d, endn%d",xstart, xend, beginn, endn);
					return FALSE;
				}


				//after bounds checking passed, reject the numeric tokens outside the bounds
				//TRACE("\nxstart%d, xend%d, beginn%d, endn%d for token ",xstart, xend, beginn, endn);
				if (beginn<xstart) { //if token beginning is smaller that our selection start
					//reject token
					//TRACE("REJECTION xstart: xstart%d, xend%d, beginn%d, endn%d",xstart, xend, beginn, endn);
					//note is xstart==beginn, we still accept the token
				}
				else if (beginn>=xend) {//not sure

					//reject token
					
					//this should work because xend here is definitely not in the middle of numeric token 
					//TRACE("REJECTION xend: xstart%d, xend%d, beginn%d, endn%d",xstart, xend, beginn, endn);
					

				}
				else {
			
					int i=0;
					while(beginn<endn) {

						tempnum[i]=pszChars[beginn];
						i++;

						beginn++;

					}
					tempnum[i]='\0';
				
					double ftoken=atof(tempnum);
					//TRACE(" %f",ftoken);
					//add toekn handler here
					//WorkToken(function,ftoken);
					if (function==0) {
						m_sum+=ftoken;
						m_counter++;
					}
					else if (function==1) {

						m_sum+=ftoken;
						m_counter++;

					}
					else if (function==2) {

						m_sum+=ftoken*ftoken;
						m_counter++;

					}
					else if (function==3) {
						m_sum+=ftoken*ftoken;
						m_counter++;

					}
					else if (function==4) {
						m_counter++;

					}
					else if (function==5) {
						
						diff=fabs(ftoken-m_mean);
						m_totaldeviation+=diff;
						m_counter++;

					}
					//else if (function==6) {  
						//no such function
					//}
					else if (function==8) { //do nothing, just store
						
						x=int(m_counter);
						m_dataval[x]=ftoken;
						m_counter++;

					}


				}

			}
		}
		
		
	}
	else
	{
		
		//WorkLineHelper(pszChars, 0, nLength, CPoint(0, nLineIndex));
	}


	return TRUE;
}

 


void CSampleView::OnSum() 
{
	// TODO: Add your command handler code here
	int fn=0;
	WorkSelection(fn,ACCUM);
		
}


void CSampleView::InitWorkSingleLine(int function)
{
	if (function==0) {
		m_sum=0;
		m_counter=0;
	}
	else if (function==1) {
		m_sum=0;
		m_counter=0;
	}
	else if (function==2) {
		m_sum=0;
		m_counter=0;
	}
	else if (function==3) {
		m_sum=0;
		m_counter=0;
	}
	else if (function==4) {
		m_sum=0;
		m_counter=0;
	}
	else if (function==5) {
		m_counter=0;
		m_totaldeviation=0;
	}
	//else if (function==6) {
		//no such function
	//}
	else if (function==8) {

		m_counter=0;
		VERIFY(m_dataval!=NULL);

	}


}

CString CSampleView::ResultWorkSingleLine(int function)
{
	CString resultstr="";
	char rstr[500];
	if (function==0) {

		sprintf(rstr," [Sum = %.12g] ",m_sum);
		resultstr=rstr;
	}
	else if (function==1) {

		if (m_counter>0)
			sprintf(rstr," [Average = %.12g] ",m_sum/m_counter);
		else
			sprintf(rstr," [Divide_By_0] ");
		resultstr=rstr;
	}
	else if (function==2) {

		sprintf(rstr," [Sum of Squares = %.12g] ",m_sum);
		resultstr=rstr;
	}
	else if (function==3) {

		if (m_counter>0)
			sprintf(rstr," [Root Mean Squares = %.12g] ",sqrt(m_sum/m_counter));
		else
			sprintf(rstr," [Divide_By_0] ");
		resultstr=rstr;
	}
	else if (function==4) {

		sprintf(rstr," [Count = %.12g] ",m_counter);
		
		resultstr=rstr;
	}
	else if (function==5) {

		if (m_counter>0)
			sprintf(rstr," [Mean = %.12g] [Mean Deviation from Mean = %.12g] ",m_mean,m_totaldeviation/m_counter);
		else
			sprintf(rstr," [Divide_By_0] ");
		resultstr=rstr;
	}
	else if (function==6) { //variance

		if (m_counter>0)
			sprintf(rstr," [Variance = %.12g] ",(m_sumofsqr/m_counter)-m_meansqr);
		else
			sprintf(rstr," [Divide_By_0] ");
		resultstr=rstr;
	}
	else if (function==7) { //standard deviation

		if (m_counter>0)
			sprintf(rstr," [Standard Deviation = %.12g] ",sqrt((m_sumofsqr/m_counter)-m_meansqr));
		else
			sprintf(rstr," [Divide_By_0] ");
		resultstr=rstr;
	}
	else if (function==8) { //standard deviation

		resultstr="";

	}
	return resultstr;


}

//returns TRUE if selection bounds has no problem, else returns FALSE 
BOOL CSampleView::WorkSelection(int fn, int wtype)
{

	UpdateData();

	InitWorkSingleLine(fn);


	int nCrlfStyle = m_pTextBuffer->GetCRLFMode();
	const char *pszCRLF = crlfsx[nCrlfStyle];
	int nCRLFLength = strlen(pszCRLF);
	CString newline(pszCRLF,nCRLFLength);
	

	CString ExprStr;
	int vd=0;
	int strtype=0;
	int nLength;

	BOOL rs;
	int xstart=-1,xend=-1;
	

	
	CPoint sStart,sEnd;
	GetSelection(sStart, sEnd);
	if (sStart == sEnd) {

		sStart=GetCursorPos();
		sEnd=GetCursorPos();

		
		CPoint ptCursorPos=	GetCursorPos();
		nLength = GetLineLength(ptCursorPos.y);
		LPCTSTR pszChars=GetLineChars(ptCursorPos.y);
		CString tempStr(pszChars,nLength); 
		ExprStr=tempStr;
		strtype=0;
		xstart=-1;
		xend=-1;
	
	}
	else 
		strtype=1;


	CString newstr="";
	for (int i=sStart.y;i<=sEnd.y;i++) {

		xstart=0; xend=nLength;
		if (strtype==1) {

			nLength = GetLineLength(i);
			LPCTSTR pszChars=GetLineChars(i);
			CString tempStr(pszChars,nLength); 

			if (m_opSelectPartial==1) {
			
				if ((sStart.y==i) && (sStart.x>0)) {
					ExprStr=tempStr.Right(nLength-sStart.x);
					xstart=sStart.x;
					xend=nLength;

				}
				else {	
					ExprStr=tempStr;
					xstart=0;
					xend=nLength;

				}
			
				if ((sEnd.y==i) && (sEnd.x<nLength)) {


					if (sStart.y!=sEnd.y) {
						
						ExprStr=ExprStr.Left(sEnd.x);
						xend=sEnd.x;

					}
					else {
						int slength=sEnd.x-sStart.x;
						ExprStr=ExprStr.Left(slength);
						xstart=sStart.x;
						xend=sEnd.x;
					}
				}

			}
			else { //not partial select

				ExprStr=tempStr;
				xstart=0; 
				xend=nLength;

			}
	

		}

		
		if ((i==sEnd.y) && (m_opSelectPartial==0)) {

			int sLength = GetLineLength(i);
			LPCTSTR pszChars=GetLineChars(i);
			CString tempStr(pszChars,sLength); 
			newstr+=tempStr;	
			//xstart=-1; xend=-1;

		}
		else {

			//no matter single line or block, set it to ExprStr;
			newstr+=ExprStr;
			//we don't modify xstart, xend here... assume it is already been prepared earlier

		}

		//do work here
		rs=WorkSingleLine(i,xstart,xend,fn,wtype);
		if (!rs) break;

	}


	if (!rs) return FALSE;
	else {

		CString newstr=ResultWorkSingleLine(fn);
		//TRACE("sum=%s",newstr);

		//GetSelection(sStart, sEnd);
		if (wtype==ACCUM) {

			InsertResultText(sStart, sEnd, newstr);

		}
		else if ((wtype==STOREMEAN) && (fn==1)) {

			if (m_counter<=0) 
				InsertResultText(sStart, sEnd, newstr);
			else 
				m_mean=m_sum/m_counter;

		}
		else if ((wtype==STOREMEANSQR) && (fn==1)) {

			if (m_counter<=0) 
				InsertResultText(sStart, sEnd, newstr);
			else 
				m_meansqr=(m_sum/m_counter)*(m_sum/m_counter);

		}
		else if ((wtype==STORESUMOFSQR) && (fn==2)) {
			
			m_sumofsqr=m_sum;

		}
		else if ((wtype==STORECOUNTER) && (fn==4)) {
			
			//store counter
			m_count=m_counter;

			if (m_counter<=0) {
			
				newstr=" [No_Selected_Values] ";	
				InsertResultText(sStart, sEnd, newstr);

			}
			
		}


	}


	UpdateData(FALSE);

	return TRUE;


}

void CSampleView::OnCalculateAverage() 
{
	// TODO: Add your command handler code here
	int fn=1;
	WorkSelection(fn,ACCUM);

	
}

void CSampleView::OnCalculateSumofsquares() 
{
	// TODO: Add your command handler code here
	int fn=2;
	WorkSelection(fn,ACCUM);

	
}

void CSampleView::OnCalculateRootmeansquare() 
{
	// TODO: Add your command handler code here
	int fn=3;
	WorkSelection(fn,ACCUM);

	
}

void CSampleView::OnCalculateMdmean() 
{
	// TODO: Add your command handler code here
	int fn=1;
	m_mean=0;
	BOOL rx=WorkSelection(fn,STOREMEAN);
	if (rx) { //bounds without problem..continue computation

		if (m_counter<=0) return; //problems with the number of items
		WorkSelection(5,ACCUM);

	}

	
}

void CSampleView::OnCalculateCountitems() 
{
	// TODO: Add your command handler code here
	int fn=4;
	WorkSelection(fn,ACCUM);

	
}

void CSampleView::OnCalculateMedian() 
{
	// TODO: Add your command handler code here
	int fn=4;
	m_count=0;
	BOOL rx=WorkSelection(fn,STORECOUNTER);
	if (rx) { //bounds without problem..continue to computation

		if (m_count<=0) return; //problems with the number of items
		
		if (m_dataval!=NULL) free(m_dataval);
		m_dataval=(double *) calloc(int(m_count)+1,sizeof(double));
		if (m_dataval==NULL) return;

		rx=WorkSelection(8,MEMORY);

		//test
		qsort( (void *)m_dataval, (size_t)m_count, sizeof( double  ), compare );

		double median=(m_count-1)/2.0;
		double val=0;
		int mi=0;
		if (median==int(median)) {

			mi=int(median);
			val=m_dataval[mi];

		}
		else {

			mi=int(median);
			val=(m_dataval[mi]+m_dataval[mi+1])/2.0;

		}

		CPoint sStart,sEnd;
		GetSelection(sStart, sEnd);
		if (sStart == sEnd) {
			sStart=GetCursorPos();
			sEnd=GetCursorPos();
		}



		char rstr[500];
		sprintf(rstr," [Median = %.12g] ",val);
		CString newstr=rstr;
		InsertResultText(sStart, sEnd, newstr);
		//SetCursorPos(sEnd);

	}
	
	
}

void CSampleView::OnCalculateStandarddeviation() 
{
	// TODO: Add your command handler code here
		m_meansqr=0;
	BOOL rx=WorkSelection(1,STOREMEANSQR);
	if (!rx) return;

	rx=WorkSelection(2,STORESUMOFSQR);
	if (!rx) return;

	CPoint sStart,sEnd;
	GetSelection(sStart, sEnd);
	if (sStart == sEnd) {
			sStart=GetCursorPos();
			sEnd=GetCursorPos();
	}



	CString newstr=ResultWorkSingleLine(7);
	InsertResultText(sStart, sEnd, newstr);


	
}

void CSampleView::OnCalculateVariance() 
{
	// TODO: Add your command handler code here
	
	m_meansqr=0;
	BOOL rx=WorkSelection(1,STOREMEANSQR);
	if (!rx) return;

	rx=WorkSelection(2,STORESUMOFSQR);
	if (!rx) return;

	CPoint sStart,sEnd;
	GetSelection(sStart, sEnd);
	if (sStart == sEnd) {
			sStart=GetCursorPos();
			sEnd=GetCursorPos();
	}


	CString newstr=ResultWorkSingleLine(6);
	InsertResultText(sStart, sEnd, newstr);
	
	
}

void CSampleView::InsertResultText(CPoint sStart, CPoint sEnd, CString newstr)
{
		int endline, endchar;
		if (sStart==sEnd) {

			//insert at end of line
			int linelength=GetLineLength(sEnd.y);
			m_pTextBuffer->InsertText(this, sEnd.y , linelength, newstr, endline, endchar, CE_ACTION_UNKNOWN);

		}
		else {

			//insert at end of selection
			m_pTextBuffer->InsertText(this, sEnd.y , sEnd.x, newstr, endline, endchar, CE_ACTION_UNKNOWN);

		}
}



int compare( const void *arg1x, const void *arg2x )
{
  double arg1=*((const double*)arg1x);
  double arg2=*((const double*)arg2x);
  if ((arg1)<(arg2)) return -1;
  else if ((arg1)==(arg2)) return 0;
  else return 1;
}


void CSampleView::OnCalculateApplynumbers() 
{
	// TODO: Add your command handler code here
	BOOL rx=ApplySelection(TEST_BOUNDS,APPLY); //Test Bounds
	if (rx) {
		if (m_adx.DoModal()==IDOK) {
			m_applytype=m_adx.m_radioselect;
			m_applyfactor=m_adx.m_factor;
			m_applyvalue=m_adx.m_value;
			m_applyexpression=m_adx.m_expression;
			m_applyresultstatus=m_adx.m_resultstatus;
			
			int res;
			if (m_applyresultstatus==1) {
				res=INSERT_RESULTS;
			}
			else
				res=REPLACE_RESULTS;
			
			ApplySelection(res,APPLY);
		}
	}
		
}

int CSampleView::EvalExpression(int idx, double xvalue,CString ExprStr, double& retResult,CString& retStr)
{


	CExpression expression;
	CMapVariabile VarsMap;

	//warning: the varsmap should never be used
	VarsMap.InitHashTable(3);
	expression.AtachVariables(&VarsMap);
	
	expression.m_identifyx=idx;
	expression.m_xvalue=xvalue;
	ExprStr=RemoveWhiteSpace(ExprStr);
	int result  = expression.ChangeExpression(ExprStr);
	expression.m_identifyx=0;
	expression.m_xvalue=0;

	
	if (result<0)
	{
		long resultx = expression.Value(retResult);
		if ((resultx == ERROR_CODE) || (expression.errorstatus==1)) {

			char pszNewText[100];
			sprintf(pszNewText,"Error");
			retStr=pszNewText;
			result=1; //indicates error
								
		}
		else if (resultx == DIVISION_BY_0) {

			char pszNewText[100];
			sprintf(pszNewText,"Divide_By_0");
			retStr=pszNewText;
			
								
		}
		else if (resultx == UNKNOWN_ROOT) {

			char pszNewText[100];
			sprintf(pszNewText,"???");
			retStr=pszNewText;
					
								
		}
		else {
						
			char pszNewText[100];
			if (fabs(retResult)<0.0000000000001) retResult=0;
			sprintf(pszNewText,"%.12g",retResult);
			retStr=pszNewText;
			
		}
	}
	else 
	{
		// evaluation error
		
		char pszNewText[100];
		sprintf(pszNewText,"Error");
		retStr=pszNewText;
								
	}


	POSITION pos = VarsMap.GetStartPosition();
	while (pos != NULL)
	{
		CString sName;
		CValue *pVal;
		VarsMap.GetNextAssoc (pos, sName, pVal);
		delete pVal;
	}
	VarsMap.RemoveAll();	

	return result;

}


void CSampleView::OnCalculateFindminandmaxvalues() 
{
	// TODO: Add your command handler code here
	int fn=4;
	m_count=0;
	BOOL rx=WorkSelection(fn,STORECOUNTER);
	if (rx) { //bounds without problem

		if (m_count<=0) return; //problems with the number of items
		
		if (m_dataval!=NULL) free(m_dataval);
		m_dataval=(double *) calloc(int(m_count)+1,sizeof(double));
		if (m_dataval==NULL) return;

		rx=WorkSelection(8,MEMORY);

		//test
		qsort( (void *)m_dataval, (size_t)m_count, sizeof( double  ), compare );

		double min=m_dataval[0];
		double max=m_dataval[int(m_count)-1];
		
		CPoint sStart,sEnd;
		GetSelection(sStart, sEnd);
		if (sStart == sEnd) {
			sStart=GetCursorPos();
			sEnd=GetCursorPos();
		}


		char rstr[500];
		sprintf(rstr," [Min. value = %.12g, Max. value = %.12g] ",min,max);
		CString newstr=rstr;
		InsertResultText(sStart, sEnd, newstr);
		//SetCursorPos(sEnd);


	}
	
}



BOOL CSampleView::ApplySingleLine(int nLineIndex,int xstart, int xend,int function,int wtype)
{


	ASSERT(nLineIndex >= -1 && nLineIndex < GetLineCount());

	int initxend=xend;

	m_lineoffset=0;  //always start at zero
	
	if (nLineIndex == -1)
	{
		return TRUE;
	}

	int nLength = GetLineLength(nLineIndex);
	if (wtype!=WTEXT) {
		if (nLength == 0)
		{
			return TRUE;
		}
	}

	//	Parse the line
	LPCTSTR pszChars = GetLineChars(nLineIndex);
	DWORD dwCookie = GetParseCookie(nLineIndex - 1);
	TEXTBLOCK *pBuf = (TEXTBLOCK *) _alloca(sizeof(TEXTBLOCK) * nLength * 3);
	int nBlocks = 0;
	m_pdwParseCookies[nLineIndex] = ParseLine(dwCookie, nLineIndex, pBuf, nBlocks);
	ASSERT(m_pdwParseCookies[nLineIndex] != (DWORD) -1);


	if (wtype==CONVERSION) {

		int cstate=0;
		int wbegin=xstart;
		int wend=xend;
		int lcomp=0;
			
		for (int i=xstart;i<=xend;i++) {

			pszChars = GetLineChars(nLineIndex);
			if (cstate==0) {
				if (CheckSeparator(pszChars[i]))
				{
					continue;
				}
				else {
					cstate=1;
					wbegin=i;
				}
			}
			else if (cstate==1) {
				if (CheckSeparator(pszChars[i])) {
					cstate=0;
					wend=i;
					
					//handle
					//word is at wbegin to wend

					lcomp=handleword(function,wbegin,wend,nLineIndex);
					i+=lcomp;
					xend+=lcomp;
					m_lastcount=xend;

					//TRACE("\ni=%d, xend=%d",i,xend);


				}
				else if (i==xend) {

					cstate=0;
					wend=i;

					lcomp=handleword(function,wbegin,wend,nLineIndex);
					i+=lcomp;
					xend+=lcomp;
					m_lastcount=xend;
					//TRACE("\ni=%d, xend=%d",i,xend);

				}
				else {
					continue;
				}
					
			}

		}//for

		return TRUE;
	  
	} //if Conversion



	if (wtype==WTEXT) {

		
		int x,y;
		if (function==NUMBERLINES) {

			if (m_skiplinesBegin) {
				CString birdstr(pszChars,nLength);
				birdstr.TrimLeft();
				if (birdstr=="") return TRUE;
			}

			
			CString inserttext;
			inserttext.Format("%d",m_curcount);
			if (m_insertspaceafterword) {

				inserttext=inserttext + " ";
						
			}
			
			m_pTextBuffer->InsertText(this, nLineIndex, xstart, inserttext, y, x, CE_ACTION_REPLACE); //	[JRT]
			m_lastcount=GetLineLength(nLineIndex);

			m_curcount++;
		}
		else if (function==ADDFIRSTWORD) {

			if (m_skiplinesBegin) {
				CString birdstr(pszChars,nLength);
				birdstr.TrimLeft();
				if (birdstr=="") return TRUE;
			}

			
			CString inserttext=m_addfirstword;
			if (m_insertspaceafterword) {

				inserttext=inserttext + " ";
						
			}
			
			m_pTextBuffer->InsertText(this, nLineIndex, xstart, inserttext, y, x, CE_ACTION_REPLACE); //	[JRT]
			m_lastcount=GetLineLength(nLineIndex);
		}
		else if (function==ADDLASTWORD) {

			if (m_skiplinesEnd) {
			
				CString birdstr(pszChars,nLength);
				birdstr.TrimLeft();
				if (birdstr=="") return TRUE;

			}
			
			CString inserttext=m_addlastword;
			if (m_insertspacebeforeword) {

				inserttext=" " +inserttext;
						
			}
			
			m_pTextBuffer->InsertText(this, nLineIndex, xend, inserttext, y, x, CE_ACTION_REPLACE); //	[JRT]
			m_lastcount=GetLineLength(nLineIndex);
		}
		else if (function==REMOVEFIRSTWORD) {

			//skip empty lines
			CString birdstr;
			if (xstart>=xend) return TRUE;
			m_pTextBuffer->GetText(nLineIndex, xstart, nLineIndex, xend, birdstr);

			int orglen=birdstr.GetLength();

			birdstr.TrimLeft();
			if (birdstr=="") return TRUE;

			int trimmedlen=birdstr.GetLength();
			int offset=orglen-trimmedlen;

			CString seperatorstr="";
			if (m_rfspace) {
				seperatorstr+=" \t";
			}

			if (m_rfuser) {
				seperatorstr+=m_rfuserstr;
			}

			int valx=birdstr.FindOneOf(seperatorstr);

			if (valx<0) {
				int lenx=orglen;
				if (lenx>0)
					m_pTextBuffer->DeleteText(this, nLineIndex, xstart, nLineIndex, xstart+lenx, CE_ACTION_DELSEL);

			}
			else {

				if (m_rfseparator) {
					valx++;
				}
				
				m_pTextBuffer->DeleteText(this, nLineIndex, xstart, nLineIndex, xstart+offset+valx, CE_ACTION_DELSEL);
	
			}

			m_lastcount=GetLineLength(nLineIndex);

		}
		else if (function==REMOVELASTWORD) {

			//skip empty lines
			CString birdstr;
			if (xstart>=xend) return TRUE;
			m_pTextBuffer->GetText(nLineIndex, xstart, nLineIndex, xend, birdstr);

			int orglen=birdstr.GetLength();

			birdstr.TrimRight();
			if (birdstr=="") return TRUE;

			int trimmedlen=birdstr.GetLength();
			int offset=orglen-trimmedlen;

			CString seperatorstr="";
			if (m_rlspace) {
				seperatorstr+=" \t";
			}

			if (m_rluser) {
				seperatorstr+=m_rluserstr;
			}
		
			int valx=-1;
			valx=ReverseFindOneOf(birdstr,seperatorstr);

			if (valx<0) {


				int lenx=orglen;
				if (lenx>0)
					m_pTextBuffer->DeleteText(this, nLineIndex, xstart, nLineIndex, xstart+lenx, CE_ACTION_DELSEL);


			}
			else {

				if (!m_rlseparator) {
					valx++;
				}
				
				m_pTextBuffer->DeleteText(this, nLineIndex, xstart+valx, nLineIndex, xend, CE_ACTION_DELSEL);
	
			}
			

			m_lastcount=GetLineLength(nLineIndex);

		} 
		else if (function==KEEPFIRSTWORD) {

			//skip empty lines
			CString birdstr;
			if (xstart>=xend) return TRUE;
			m_pTextBuffer->GetText(nLineIndex, xstart, nLineIndex, xend, birdstr);

			int orglen=birdstr.GetLength();

			birdstr.TrimLeft();
			if (birdstr=="") return TRUE;

			int trimmedlen=birdstr.GetLength();
			int offset=orglen-trimmedlen;

			CString seperatorstr="";
			if (m_kfspace) {
				seperatorstr+=" \t";
			}

			if (m_kfuser) {
				seperatorstr+=m_kfuserstr;
			}	
			
			
			int valx=birdstr.FindOneOf(seperatorstr);

			if (valx<0) {
				
				//separator not found, ..do nothing..keep the word
								
			
			}
			else {

				if (!m_kfseparator) {
					valx++;
				}
				
				m_pTextBuffer->DeleteText(this, nLineIndex, xstart+offset+valx, nLineIndex, xend, CE_ACTION_DELSEL);
	
			}

			m_lastcount=GetLineLength(nLineIndex);

		}
		else if (function==KEEPLASTWORD) {

			//skip empty lines
			CString birdstr;
			if (xstart>=xend) return TRUE;
			m_pTextBuffer->GetText(nLineIndex, xstart, nLineIndex, xend, birdstr);

			int orglen=birdstr.GetLength();

			birdstr.TrimRight();
			if (birdstr=="") return TRUE;

			int trimmedlen=birdstr.GetLength();
			int offset=orglen-trimmedlen;

			CString seperatorstr="";
			if (m_klspace) {
				seperatorstr+=" \t";
			}

			if (m_kluser) {
				seperatorstr+=m_kluserstr;
			}
		
			
			int valx=-1;
			valx=ReverseFindOneOf(birdstr,seperatorstr);

			if (valx<0) {
				
				//separator not found, ..do nothing..keep word				

			}
			else {

				if (m_klseparator) {
					valx++;
				}
				
				m_pTextBuffer->DeleteText(this, nLineIndex, xstart, nLineIndex, xstart+valx, CE_ACTION_DELSEL);
	
			}
	

			m_lastcount=GetLineLength(nLineIndex);

		} //continue here


		return TRUE;
	}
	


	
	if (nBlocks > 0)
	{

		ASSERT(pBuf[0].m_nCharPos >= 0 && pBuf[0].m_nCharPos <= nLength);
	
		
		if ((nBlocks==1) && (pBuf[0].m_nColorIndex==COLORINDEX_NUMBER)) 
		{

			//this case has not yet occured
			LPCTSTR pszLine = GetLineChars(nLineIndex);
			int xLength = GetLineLength(nLineIndex);
			CString tempStr(pszLine,xLength); 

			ASSERT(TRUE);
			TRACE("\nSingle : %s\n",LPCTSTR(tempStr));

		}

		int x, y; //temp varaibles
		int lcompensate=0;
		int savebeginn=0;
		for (int I = 1; I < nBlocks+1 ; I ++)
		{
			if (I<nBlocks) {
				ASSERT(pBuf[I].m_nCharPos >= 0 && pBuf[I].m_nCharPos <= nLength);
			}
			
			if (pBuf[I-1].m_nColorIndex==COLORINDEX_NUMBER) {

				int beginn,endn;
				char tempnum[200];
				
				beginn=pBuf[I-1].m_nCharPos;
				
				if (I==nBlocks) 
					endn=nLength;
				else
					endn=pBuf[I].m_nCharPos;

				ASSERT(endn>=beginn);

				
				//Compensation for insertion and deletion
				beginn+=lcompensate;
				endn+=lcompensate;				
			
				//check bounds
				if (function==TEST_BOUNDS) {
					if ((xstart==-1) && (xend==-1)) {
						//ok proceed
					}
					else if ((xstart>beginn) && (xstart<endn)) {

						AfxMessageBox("Ambiguous bounds in start of selection! Cannot select part of a number!");
						//TRACE("AmbBounds : xstart%d, xend%d, beginn%d, endn%d",xstart, xend, beginn, endn);

						return FALSE;
					}
					else if ((xend>beginn) && (xend<endn)) {
						
						AfxMessageBox("Ambiguous bounds in end of selection! Cannot select part of a number!");
						//TRACE("AmbBounds : xstart%d, xend%d, beginn%d, endn%d",xstart, xend, beginn, endn);
						return FALSE;
					}
				}
				 

				//after bounds checking passed, reject the numeric tokens outside 
				//TRACE("\nxstart%d, xend%d, beginn%d, endn%d for token ",xstart, xend, beginn, endn);
				if (beginn<xstart) { //if token beginning is smaller that our selection start
					
					//Reject token					
					
					//note if xstart==beginn, we still accept the token
					//TRACE("REJECTION xstart: xstart%d, xend%d, beginn%d, endn%d",xstart, xend, beginn, endn);

				}
				else if (beginn>=xend) {//not sure :what about xend=-1?

					//Reject token
					
					//this should work because xend here is definitely not in the middle of numeric token 
					//TRACE("REJECTION xend: xstart%d, xend%d, beginn%d, endn%d",xstart, xend, beginn, endn);
					

				}
				else {
					
					//pszChars may not be the same after insertion or deletion
					pszChars = GetLineChars(nLineIndex);
					int i=0;

					savebeginn=beginn;
					while(beginn<endn) {

						tempnum[i]=pszChars[beginn];
						i++;

						beginn++;

					}
					tempnum[i]='\0';
				
					if (function==TEST_BOUNDS) {
						//do nothing
					}
					else if (function==EXTRACT_NUMBERS) { //format numbers

						m_insertText=" ";
						m_insertText=tempnum + m_insertText;
						int inslen=m_insertText.GetLength();
						m_pTextBuffer->InsertText(this, m_linecounter, m_lineoffset, m_insertText, y, x, CE_ACTION_REPLACE); 
						m_lineoffset+=inslen;
						m_lastcount=xend;

					}
					else if (function==FORMAT_NUMBERS) { //format numbers

						m_insertText="";
						double ftoken=atof(tempnum);
						if (m_formatprefix) {
							m_insertText+=m_prefixstr;
						}

						if (m_formatdigits) {
							
							char pszNewText[100];
							//TRACE("\nformatstr=%s",formatstr);
							sprintf(pszNewText,m_formatstr,ftoken);
							m_insertText+=pszNewText; 
						}
						else 
							m_insertText+=tempnum;

						
						if (m_formatsuffix) {
							m_insertText+=m_suffixstr;
						}


						//replace old string with new string
						int dellen=endn-savebeginn;
						int inslen=m_insertText.GetLength();
						lcompensate+=(inslen-dellen);
														
						m_pTextBuffer->DeleteText(this, nLineIndex, savebeginn, nLineIndex, endn, CE_ACTION_DELSEL);
						m_pTextBuffer->InsertText(this, nLineIndex, savebeginn, m_insertText, y, x, CE_ACTION_REPLACE); //	[JRT]
													
						if (xend>=0) xend=initxend+lcompensate;
						m_lastcount=xend;


					}
					else { //apply numbers
					
						double ftoken=atof(tempnum);
						//TRACE("\nftoken %g, savebeginn %d, endn %d, tempnum %s",ftoken,savebeginn,endn,tempnum);
						
						double calcresult;				
						char pszNewText[100];
					
						m_insertText="";
						if (m_applytype==0) {//factor

							calcresult=ftoken*m_applyfactor;
							sprintf(pszNewText,"%.12g",calcresult);
							m_insertText=pszNewText; 
						}
						else if (m_applytype==1) {//value

							calcresult=ftoken+m_applyvalue;
							sprintf(pszNewText,"%.12g",calcresult);
							m_insertText=pszNewText; 

						}
						else if (m_applytype==2) {//expression
							
							
							double resultval=0;
							CString retStr="";
							
														
							int rx=EvalExpression(1, ftoken,m_applyexpression,resultval,retStr);
														
							TRACE("\nftoken %g, resultval %g, m_applyexpression %s",ftoken,resultval,LPCTSTR(m_applyexpression));
							if (rx>=0) {//invalid expression
								m_insertText="Error"; 
							}
							else
								m_insertText=retStr; 							
							
						}
					
						if (function==REPLACE_RESULTS) {
														
							int dellen=endn-savebeginn;
							int inslen=m_insertText.GetLength();
							lcompensate+=(inslen-dellen);
															
							m_pTextBuffer->DeleteText(this, nLineIndex, savebeginn, nLineIndex, endn, CE_ACTION_DELSEL);							//intermediate action here
						
							m_pTextBuffer->InsertText(this, nLineIndex, savebeginn, m_insertText, y, x, CE_ACTION_REPLACE); //	[JRT]
							
						    
							if (xend>=0) xend=initxend+lcompensate;
							m_lastcount=xend;
							//TRACE("\nxend %d, beginn %d",xend,beginn);

						}//if REPLACE
						else if (function==INSERT_RESULTS) {
							
							m_insertText="[" + m_insertText + "]";
					
							int dellen=0;
							int inslen=m_insertText.GetLength();
							lcompensate+=(inslen-dellen);
							
							m_pTextBuffer->InsertText(this, nLineIndex, endn, m_insertText, y, x, CE_ACTION_REPLACE); //	[JRT]
									    
							if (xend>=0) xend=initxend+lcompensate;
							m_lastcount=xend;

						}//if REPLACE
					
					
					}//if else TESTBOUNDS 
					
				}

			}
		}
		
		
	}
	else
	{
		
		//WorkLineHelper(pszChars, 0, nLength, CPoint(0, nLineIndex));
	}


	return TRUE;
}


BOOL CSampleView::InitApplySingleLine(int function,int wtype)
{

	if (function!=TEST_BOUNDS) {
		
		if (! QueryEditable())
			return FALSE;
		if (m_pTextBuffer == NULL)
			return FALSE;

		//can't even reach here if can't edit...==>BeginUndoGroup will not called if workselection cannot edit
		//==>no need to worry about FlushUndoGroup
		m_pTextBuffer->BeginUndoGroup();

		return TRUE;

	}


	return TRUE;

}


CString CSampleView::ResultApplySingleLine(int function,int wtype)
{
	CString resultstr="";
	if (function!=TEST_BOUNDS) {

		m_pTextBuffer->FlushUndoGroup(this);
		
	}
	return resultstr;

}




// Duplication of WorkSingle into ApplySingle
BOOL CSampleView::ApplySelection(int fn, int wtype)
{

	UpdateData();

	BOOL rz=InitApplySingleLine(fn,wtype);
	if (!rz) return FALSE;


	int nCrlfStyle = m_pTextBuffer->GetCRLFMode();
	const char *pszCRLF = crlfsx[nCrlfStyle];
	int nCRLFLength = strlen(pszCRLF);
	CString newline(pszCRLF,nCRLFLength);
	

	CString ExprStr;
	int vd=0;
	int strtype=0;
	int nLength;

	BOOL rs;
	int xstart=-1,xend=-1;
	

	
	CPoint sStart,sEnd;
	GetSelection(sStart, sEnd);
	if (sStart == sEnd) {

		sStart=GetCursorPos();
		sEnd=GetCursorPos();
		
		CPoint ptCursorPos=	GetCursorPos();
		nLength = GetLineLength(ptCursorPos.y);
		LPCTSTR pszChars=GetLineChars(ptCursorPos.y);
		CString tempStr(pszChars,nLength); 
		ExprStr=tempStr;
		strtype=0;
		xstart=-1;
		xend=-1;
	
	}
	else 
		strtype=1;


	CString newstr="";
	
	
	int xz,yz;
	boolean extracttext=TRUE;
	if (fn==EXTRACT_NUMBERS) {


		if (GetLineCount()==sEnd.y+1) {

			int nl=GetLineLength(sEnd.y);
			m_pTextBuffer->InsertText(this, sEnd.y, nl, newline, yz, xz, CE_ACTION_REPLACE); 

		}
		
		m_pTextBuffer->InsertText(this, sEnd.y+1, 0, newline, yz, xz, CE_ACTION_REPLACE); 		
		m_pTextBuffer->InsertText(this, sEnd.y+1, 0, "//Numbers Extraction"+newline, yz, xz, CE_ACTION_REPLACE); 
		m_pTextBuffer->InsertText(this, sEnd.y+1, 0, newline, yz, xz, CE_ACTION_REPLACE); 		
		m_linecounter=sEnd.y+3;

	}
	else
		m_linecounter=0;	
	

	for (int i=sStart.y;i<=sEnd.y;i++) {

		xstart=0; xend=nLength;
		if (strtype==1) {

			nLength = GetLineLength(i);
			LPCTSTR pszChars=GetLineChars(i);
			CString tempStr(pszChars,nLength); 

			if (m_opSelectPartial==1) {
			
				if ((sStart.y==i) && (sStart.x>0)) {
					ExprStr=tempStr.Right(nLength-sStart.x);
					xstart=sStart.x;
					xend=nLength;

				}
				else {	
					ExprStr=tempStr;
					xstart=0;
					xend=nLength;

				}
			
				if ((sEnd.y==i) && (sEnd.x<nLength)) {


					if (sStart.y!=sEnd.y) {
						
						ExprStr=ExprStr.Left(sEnd.x);
						xend=sEnd.x;

					}
					else {
						int slength=sEnd.x-sStart.x;
						ExprStr=ExprStr.Left(slength);
						xstart=sStart.x;
						xend=sEnd.x;
					}
				}

			}
			else {

				ExprStr=tempStr;
				//xstart=-1; xend=-1;
				xstart=0;
				xend=nLength;


			}
	

		}

		
		if ((i==sEnd.y) && (m_opSelectPartial==0)) {

			int sLength = GetLineLength(i);
			LPCTSTR pszChars=GetLineChars(i);
			CString tempStr(pszChars,sLength); 
			newstr+=tempStr;	
			//xstart=-1; xend=-1;

		}
		else {

			//no matter single line or block, set it to ExprStr;
			newstr+=ExprStr;
			//we don't modify xstart, xend here... assume it is already been prepared earlier

		}
	
		
		//do work here
		//this line is needed because applying the text does not reject the word automatically
		if ((sEnd.y==i) && (sEnd.x==0) && (m_opSelectPartial==1) && (wtype==WTEXT) && (sStart.y!=sEnd.y)) { //will only affect text
			
			//do nothing

		}
		else
		{
			rs=ApplySingleLine(i,xstart,xend,fn,wtype);
			if (!rs) break;
		}


		if (fn==EXTRACT_NUMBERS) {
			
			int xl=GetLineLength(m_linecounter);
			if (xl>0){
				m_pTextBuffer->InsertText(this, m_linecounter, xl, newline, yz, xz, CE_ACTION_REPLACE); 
				m_linecounter++;
				
			}
		}



	}


	CString resultstr=ResultApplySingleLine(fn,wtype);
	if (!rs) return FALSE;
	else {

	
	}

	//assertion when trying to select a rejected(empty) line...
	//SELECTION
	//==>does not affect old applynumber code!
	if (fn!=TEST_BOUNDS) {
		if (sStart!=sEnd) {
		
			if (m_opSelectPartial==0) { //no partial selection

				sStart.x=0;
				sEnd.x=GetLineLength(sEnd.y);
				SetSelection(sStart,sEnd);

			}
			//else if (wtype==CONVERSION) { //will only affect text

			//}
			else if (GetLineLength(sEnd.y)>=m_lastcount) { //if partial selection

				if (wtype==WTEXT) { //will only affect text
					
					//do nothing
				
				}
				else {
					sEnd.x=m_lastcount;
					SetSelection(sStart,sEnd);
					SetCursorPos(sEnd);
				}

			}
		}

  	}
	

	UpdateData(FALSE);

	return TRUE;


}

void CSampleView::OnTextAddfirstword() 
{
	// TODO: Add your command handler code here
	if (m_addfirst.DoModal()==IDOK) {

			m_addfirstword=m_addfirst.m_insertstring;
			if (m_addfirst.m_insertspace)
				m_insertspaceafterword=TRUE;
			else
				m_insertspaceafterword=FALSE;

			if (m_addfirst.m_skiplines)
				m_skiplinesBegin=TRUE;
			else
				m_skiplinesBegin=FALSE;
			
			ApplySelection(ADDFIRSTWORD,WTEXT);
	}
	
}




void CSampleView::OnTextAddlastword() 
{
	// TODO: Add your command handler code here
	if (m_addlast.DoModal()==IDOK) {

			m_addlastword=m_addlast.m_insertstring;
			if (m_addlast.m_insertspace)
				m_insertspacebeforeword=TRUE;
			else
				m_insertspacebeforeword=FALSE;

			if (m_addlast.m_skiplines)
				m_skiplinesEnd=TRUE;
			else
				m_skiplinesEnd=FALSE;
			
			ApplySelection(ADDLASTWORD,WTEXT);
	}

	
}

void CSampleView::OnCalculateFormatnumbers() 
{
	// TODO: Add your command handler code here
	BOOL rx=ApplySelection(TEST_BOUNDS,APPLY); //Test Bounds
	if (rx) {
		if (m_format.DoModal()==IDOK) {
			m_formatprefix=m_format.m_formatprefix;
			m_formatsuffix=m_format.m_formatsuffix;
			m_formatdigits=m_format.m_formatdigits;
			m_prefixstr=m_format.prefixstr;
			m_suffixstr=m_format.suffixstr;
			m_numdigits=m_format.m_numdigits;

			if (m_formatdigits)
				sprintf(m_formatstr,"%%.%df",m_numdigits);
								
			ApplySelection(FORMAT_NUMBERS,APPLY);
		}
	}
	
}

void CSampleView::OnTextRemovefirstword() 
{
	// TODO: Add your command handler code here
	if (m_removefirst.DoModal()==IDOK) {

			m_rfspace=m_removefirst.m_checkspace;
			m_rfuser=m_removefirst.m_checkuser;
			m_rfseparator=m_removefirst.m_checkseparator;
			m_rfuserstr=m_removefirst.m_userstr;
			ApplySelection(REMOVEFIRSTWORD,WTEXT);
	}

	
}

void CSampleView::OnTextRemovelastword() 
{
	// TODO: Add your command handler code here
	if (m_removelast.DoModal()==IDOK) {

			m_rlspace=m_removelast.m_checkspace;
			m_rluser=m_removelast.m_checkuser;
			m_rlseparator=m_removelast.m_checkseparator;
			m_rluserstr=m_removelast.m_userstr;
			ApplySelection(REMOVELASTWORD,WTEXT);
	}
	
}

int CSampleView::ReverseFindOneOf(CString orgstr, CString sepstr)
{

	int orglen=orgstr.GetLength();
	int seplen=sepstr.GetLength();
	int i,j;

	if (orglen==0) return -1;
	if (seplen==0) return -1;

	//for (i=orglen-1;i>=0;i--) 
	//	TRACE("\ni=%d, %c",i,orgstr[i]);

	for (i=orglen-1;i>=0;i--) {
		
		for (j=0;j<seplen;j++) {

			if (orgstr[i]==sepstr[j]) 
				return i;


		}

	}

	return -1;


}

void CSampleView::OnTextKeepfirstword() 
{
	// TODO: Add your command handler code here
	if (m_keepfirst.DoModal()==IDOK) {

			m_kfspace=m_keepfirst.m_checkspace;
			m_kfuser=m_keepfirst.m_checkuser;
			m_kfseparator=m_keepfirst.m_checkseparator;
			m_kfuserstr=m_keepfirst.m_userstr;
			ApplySelection(KEEPFIRSTWORD,WTEXT);
	}

	
}

void CSampleView::OnTextKeeplastword() 
{
	// TODO: Add your command handler code here
	if (m_keeplast.DoModal()==IDOK) {

			m_klspace=m_keeplast.m_checkspace;
			m_kluser=m_keeplast.m_checkuser;
			m_klseparator=m_keeplast.m_checkseparator;
			m_kluserstr=m_keeplast.m_userstr;
			ApplySelection(KEEPLASTWORD,WTEXT);
	}
	
}

void CSampleView::OnCalculateExtractnumbers() 
{
	// TODO: Add your command handler code here
	BOOL rx=ApplySelection(TEST_BOUNDS,APPLY); //Test Bounds
	if (rx) {
			ApplySelection(EXTRACT_NUMBERS,APPLY);
	}

	
}

void CSampleView::OnTextMakeintooneline() 
{
	// TODO: Add your command handler code here
	int nCrlfStyle = m_pTextBuffer->GetCRLFMode();
	const char *pszCRLF = crlfsx[nCrlfStyle];
	int nCRLFLength = strlen(pszCRLF);
	CString newline(pszCRLF,nCRLFLength);
	int lnx=lstrlen(newline);


	DWORD dwSearchFlags = 0;

	if (! QueryEditable())
			return;
	if (m_pTextBuffer == NULL)
			return;

	CPoint sStart,sEnd;
	GetSelection(sStart,sEnd);
	if (sStart == sEnd) {
			sStart=GetCursorPos();
			sEnd=GetCursorPos();
	}


	m_pTextBuffer->BeginUndoGroup();

	
	LPCTSTR pszchar;
	int tl=0;
	int linelength=0;
	int x,y;
	
	int i;

	//counting
	int total=0;
	for(i=sStart.y;i<=sEnd.y;i++) {

		linelength=GetLineLength(i);
		total+=linelength;

	}

	if (total>2000) {

		MessageBox("Resulting line is more than 2000 characters!", "Error",MB_ICONEXCLAMATION  | MB_OK);

	}


	for(i=sStart.y;i<=sEnd.y;i++) {

		if (i==sStart.y) continue;
		else {

			linelength=GetLineLength(sStart.y);
			
			pszchar=GetLineChars(i);
			tl=GetLineLength(i);
			if (i==sEnd.y) {
				tl=sEnd.x;
			}
			CString tempstr(pszchar,tl);
			if (tl>0)	
				m_pTextBuffer->InsertText(this, sStart.y , linelength, " " + tempstr , y, x, CE_ACTION_UNKNOWN);

		}

	}

	if (sStart.y+1<=sEnd.y)
		m_pTextBuffer->DeleteText(this, sStart.y+1, 0, sEnd.y, sEnd.x, CE_ACTION_DELSEL);


	m_pTextBuffer->FlushUndoGroup(this);
	
}

void CSampleView::OnCalculateComputeoptions() 
{
	// TODO: Add your command handler code here
	if (m_computeoptions.DoModal()==IDOK) {

			m_resultsinnextline=m_computeoptions.m_RInextline;
			m_hexspace=m_computeoptions.m_checkspace;
			m_hexuser=m_computeoptions.m_checkuser;
			m_hexuserstr=m_computeoptions.m_userstr;

	}

	
}

void CSampleView::OnButton32829() 
{
	// TODO: Add your command handler code here
	ApplyWord(DEC2HEX,CONVERSION);
	
}

BOOL CSampleView::CheckSeparator(char x)
{

	if (m_hexspace) {
		if ((x==' ') || (x=='\t')) return TRUE;
	}


	//TRACE("char x=%c",x);
	if (m_hexuser) {
		int l=m_hexuserstr.GetLength();
		for (int i=0; i<l;i++) {
			//TRACE("\nchar hex=%c",m_hexuserstr[i]);
			if (x==m_hexuserstr[i]) 
				return TRUE;
		}
	}

	return FALSE;

}

int CSampleView::handleword(int function, int wbegin, int wend, int nIndex)
{

	LPCTSTR pszChars=GetLineChars(nIndex);


	char tempnum[200];
	int j=0;
	int savebegin=wbegin;
	while(savebegin<wend) {
		tempnum[j]=pszChars[savebegin];
		j++;
		savebegin++;
	}
	tempnum[j]='\0';
		
	int xx,yy;
	long px=0;

	if (function==DEC2HEX) {
		if (IsDecInteger(tempnum)) {

			
			px= atol(tempnum);
			CString resultstr;
			resultstr.Format("[%X]",px);
			//resultstr.MakeUpper();
			m_pTextBuffer->InsertText(this, nIndex , wend, resultstr, yy, xx, CE_ACTION_UNKNOWN);
			int lcomp=resultstr.GetLength();
			return lcomp;
			//TRACE("\ntoken:%s, hex=%x",tempnum,px);

		}
	}
	if (function==DEC2OCT) {
		if (IsDecInteger(tempnum)) {

			
			px= atol(tempnum);
			CString resultstr;
			resultstr.Format("[%o]",px);
			m_pTextBuffer->InsertText(this, nIndex , wend, resultstr, yy, xx, CE_ACTION_UNKNOWN);
			int lcomp=resultstr.GetLength();
			return lcomp;
			//TRACE("\ntoken:%s, hex=%x",tempnum,px);

		}
	}
	else if (function==HEX2DEC) {

		if (IsHexInteger(tempnum)) {

		
			
			sscanf( tempnum, "%x", &px );
   			CString resultstr;
			resultstr.Format("[%d]",px);
			
			m_pTextBuffer->InsertText(this, nIndex , wend, resultstr, yy, xx, CE_ACTION_UNKNOWN);
			int lcomp=resultstr.GetLength();
			return lcomp;
			//TRACE("\ntoken:%s, hex=%x",tempnum,px);

		}
	}
	else if (function==OCT2DEC) {

		if (IsOctInteger(tempnum)) {
		
			
			sscanf( tempnum, "%o", &px );
   			CString resultstr;
			resultstr.Format("[%d]",px);
			
			m_pTextBuffer->InsertText(this, nIndex , wend, resultstr, yy, xx, CE_ACTION_UNKNOWN);
			int lcomp=resultstr.GetLength();
			return lcomp;
			//TRACE("\ntoken:%s, hex=%x",tempnum,px);

		}
	}
	else if (function==OCT2HEX) {

		if (IsOctInteger(tempnum)) {
		
			//long px= atol(tempnum);
			sscanf( tempnum, "%o", &px );
   			CString resultstr;
			resultstr.Format("[%X]",px);
			
			m_pTextBuffer->InsertText(this, nIndex , wend, resultstr, yy, xx, CE_ACTION_UNKNOWN);
			int lcomp=resultstr.GetLength();
			return lcomp;
			//TRACE("\ntoken:%s, hex=%x",tempnum,px);

		}
	}
	else if (function==HEX2OCT) {

		if (IsHexInteger(tempnum)) {		
			
			sscanf( tempnum, "%x", &px );
   			CString resultstr;
			resultstr.Format("[%o]",px);
			
			m_pTextBuffer->InsertText(this, nIndex , wend, resultstr, yy, xx, CE_ACTION_UNKNOWN);
			int lcomp=resultstr.GetLength();
			return lcomp;
			//TRACE("\ntoken:%s, hex=%x",tempnum,px);

		}
	}
	
	return 0;

}

BOOL CSampleView::IsDecInteger(char * str)
{

	int ix=strlen(str);
	if (ix>12) return FALSE;


	TRACE("\ntoken:%s, strlen=%d",str,ix);
	for (int i=0;i<ix;i++) {
		if (!isdigit(str[i]))
			return FALSE;
	}

	return TRUE;


}


BOOL CSampleView::IsHexInteger(char * str)
{
	int ix=strlen(str);
	if (ix>12) return FALSE;

	TRACE("\ntoken:%s, strlen=%d",str,ix);
	for (int i=0;i<ix;i++) {

		if (isdigit(str[i]))
			continue;
		else if ((str[i]>='a') &&  (str[i]<='f'))
			continue;
		else if ((str[i]>='A') &&  (str[i]<='F'))
			continue;
		else 
			return FALSE;

	}

	return TRUE;

}

void CSampleView::OnDec() 
{
	// TODO: Add your command handler code here
	ApplyWord(HEX2DEC,CONVERSION);
	
}

int CSampleView::ApplyWord(int function, int wtype)
{
	int nCrlfStyle = m_pTextBuffer->GetCRLFMode();
	const char *pszCRLF = crlfsx[nCrlfStyle];
	int nCRLFLength = strlen(pszCRLF);
	CString newline(pszCRLF,nCRLFLength);
	int lnx=lstrlen(newline);


	if (! QueryEditable())
			return 1;
	if (m_pTextBuffer == NULL)
			return 1;

	CPoint sStart,sEnd;
	GetSelection(sStart,sEnd);

	if (sStart == sEnd) {

		sStart=GetCursorPos();
		sEnd=GetCursorPos();	

		sStart.x=0;
		sEnd.x=GetLineLength(sEnd.y);
	}

	if (sStart.x!=0) {

		LPCTSTR pszchar=GetLineChars(sStart.y);
		if (!CheckSeparator(pszchar[sStart.x])) {
			if (!CheckSeparator(pszchar[sStart.x-1])) {
				MessageBox("Error at start of bounds! Please select whole word.","Error",MB_OK | MB_ICONEXCLAMATION);
				return 1;
			}
		}
		
	}


	int lineend=GetLineLength(sEnd.y);
	if ((sEnd.x!=0) && (sEnd.x!=lineend))
	{

		LPCTSTR pszchar=GetLineChars(sEnd.y);
		if (!CheckSeparator(pszchar[sEnd.x])) {
			if (!CheckSeparator(pszchar[sStart.x+1])) {
				MessageBox("Error at end of bounds! Please select whole word.","Error",MB_OK | MB_ICONEXCLAMATION);
				return 1;
			}
		}
	}

	ApplySelection(function,wtype);

	return 0;


}


void CSampleView::OnConversionDecimaltohex() 
{
	// TODO: Add your command handler code here
	ApplyWord(DEC2HEX,CONVERSION);
	
}

void CSampleView::OnConversionDecimaltooct() 
{
	// TODO: Add your command handler code here
	ApplyWord(DEC2OCT,CONVERSION);
	
}

void CSampleView::OnConversionHextodecimal() 
{
	// TODO: Add your command handler code here
	ApplyWord(HEX2DEC,CONVERSION);
	
}

void CSampleView::OnConversionOcttodecimal() 
{
	// TODO: Add your command handler code here
	ApplyWord(OCT2DEC,CONVERSION);
	
}


BOOL CSampleView::IsOctInteger(char * str)
{

	int ix=strlen(str);
	if (ix>12) return FALSE;

	for (int i=0;i<ix;i++) {

		if ((str[i]>='0') &&  (str[i]<='7'))
			continue;
		else 
			return FALSE;

	}

	return TRUE;


}

void CSampleView::OnCalculatePi3141592654() 
{
	// TODO: Add your command handler code here
	insertString("3.141592653589793",0);
	
}

//loc==0 at current cursor, loc==1 at a new line
BOOL CSampleView::insertString(CString str,int loc)
{

	if (! QueryEditable())
			return FALSE;
	if (m_pTextBuffer == NULL)
			return FALSE;

	int nCrlfStyle = m_pTextBuffer->GetCRLFMode();
	const char *pszCRLF = crlfsx[nCrlfStyle];
	int nCRLFLength = strlen(pszCRLF);
	CString newline(pszCRLF,nCRLFLength);
	
	
	CPoint sEnd;
	sEnd=GetCursorPos();
	int xx,yy;

	if (loc<100) {

		m_pTextBuffer->BeginUndoGroup();

		if (loc==0) {
			m_pTextBuffer->InsertText(this, sEnd.y , sEnd.x, str, yy, xx, CE_ACTION_UNKNOWN);
		}
		else if (loc==1) {
			str=newline+str+newline;
			int lx=GetLineLength(sEnd.y);
			m_pTextBuffer->InsertText(this, sEnd.y , lx, str, yy, xx, CE_ACTION_UNKNOWN);
		}

		m_pTextBuffer->FlushUndoGroup(this);

	}
	else if (loc==101) {

		str=str+newline;
		int lx=GetLineLength(sEnd.y);
		if (!m_pTextBuffer->InternalInsertText(this, sEnd.y, lx, str, yy, xx))
			return FALSE;

	}

	return TRUE;

}


//dirspec=0 ,use user defined dir
//dirspec=1 or 2 or greater, use getmodule directory
//dirspec >=2 don't insert new line at beginning...
//dirspec >=100 don't allow undo....

//warning..can only insert file upto 30K in size! (char zbuffer[30001])
BOOL CSampleView::insertFile(CString filex,int dirspec)
{

	
	if (! QueryEditable())
			return FALSE;
	if (m_pTextBuffer == NULL)
			return FALSE;

	int nCrlfStyle = m_pTextBuffer->GetCRLFMode();
	const char *pszCRLF = crlfsx[nCrlfStyle];
	int nCRLFLength = strlen(pszCRLF);
	CString newline(pszCRLF,nCRLFLength);


	if (dirspec>0) {

		//indicates using the files in the program directory
		CString AppDir=GetProgPath();
		filex=AppDir+"\\"+filex;
		TRACE("\nfilename = %s",LPCTSTR(filex));

	}
	


	FILE *fp=fopen(filex,"r");
	if (fp==NULL) {
	
		insertString("[Error Reading File]",1);	
		return FALSE;
	}

		
	char tbuffer[1000];
	char zbuffer[30001];
	
	int numread;
	CString instr;
	
	if (dirspec>=2)
		instr="";
	else	
		instr=newline;


    numread = fread( zbuffer, sizeof( char ), 30000, fp );
	int i=0;
	int j=0;
	while (i<numread) {

		if ((zbuffer[i]!='\n') && (zbuffer[i]!='\0'))
			tbuffer[j]=zbuffer[i];
		else {
			tbuffer[j]='\0';
			instr=instr+tbuffer+newline;
			j=-1;
		}

		j++;
		i++;
	}
      


    	
	if (dirspec>=100) {
		insertString(instr,dirspec);	
	}
	else 
		insertString(instr,1);

	if (fp!=NULL) {
		fclose(fp);
	}
		
	
	return TRUE;
}

void CSampleView::OnConversionUnits() 
{
	// TODO: Add your command handler code here
	insertFile("Length.txt",1);
	
}


CString CSampleView::GetProgPath()
{

	TCHAR    szTemp[300];
	CFile converter;
	CString result;

	// get root
	GetModuleFileName( NULL, szTemp, 300 );

	CString path=(CString)szTemp;
	path=path.Left(path.ReverseFind('\\'));
	return path;
	

}


void CSampleView::OnConversionTablesArea() 
{
	// TODO: Add your command handler code here
	insertFile("Area.txt",1);
	
}

void CSampleView::OnConversionTablesVolume() 
{
	// TODO: Add your command handler code here
	insertFile("Volume.txt",1);
	
}

void CSampleView::OnConversionTablesWeight() 
{
	// TODO: Add your command handler code here
	insertFile("Weight.txt",1);
	
}

void CSampleView::OnConversionHextooct() 
{
	// TODO: Add your command handler code here
	ApplyWord(HEX2OCT,CONVERSION);
	
}

void CSampleView::OnConversionOcttohex() 
{
	// TODO: Add your command handler code here
	ApplyWord(OCT2HEX,CONVERSION);
	
}


BOOL CSampleView::Openlink (CString link)
{

  BOOL bSuccess = FALSE;

  //As a last resort try ShellExecuting the URL, may
  //even work on Navigator!
  if (!bSuccess)
    bSuccess = OpenUsingShellExecute (link);

  if (!bSuccess)
    bSuccess = OpenUsingRegisteredClass (link);
  return bSuccess;
}


BOOL CSampleView::OpenUsingShellExecute (CString link)
{
  LPCTSTR mode;
  mode = _T ("open");

  //HINSTANCE hRun = ShellExecute (GetParent ()->GetSafeHwnd (), mode, m_sActualLink, NULL, NULL, SW_SHOW);
  HINSTANCE hRun = ShellExecute (GetSafeHwnd (), mode, link, NULL, NULL, SW_SHOW);
  if ((int) hRun <= HINSTANCE_ERROR)
    {
      TRACE ("Failed to invoke URL using ShellExecute\n");
      return FALSE;
    }
  return TRUE;
}


BOOL CSampleView::
OpenUsingRegisteredClass (CString link)
{
  TCHAR key[MAX_PATH + MAX_PATH];
  HINSTANCE result;

  if (GetRegKey (HKEY_CLASSES_ROOT, _T (".htm"), key) == ERROR_SUCCESS)
    {
      LPCTSTR mode;
      mode = _T ("\\shell\\open\\command");
      _tcscat (key, mode);
      if (GetRegKey (HKEY_CLASSES_ROOT, key, key) == ERROR_SUCCESS)
        {
          LPTSTR pos;
          pos = _tcsstr (key, _T ("\"%1\""));
          if (pos == NULL)
            {              // No quotes found

              pos = strstr (key, _T ("%1"));   // Check for %1, without quotes

              if (pos == NULL)     // No parameter at all...

                pos = key + _tcslen (key) - 1;
              else
                *pos = _T ('\0');  // Remove the parameter

            }
          else
            *pos = _T ('\0');  // Remove the parameter

          _tcscat (pos, _T (" "));
          _tcscat (pos, link);
          result = (HINSTANCE) WinExec (key, SW_SHOW);
          if ((int) result <= HINSTANCE_ERROR)
            {
              CString str;
              switch ((int) result)
                {
                case 0:
                  str = _T ("The operating system is out\nof memory or resources.");
                  break;
                case SE_ERR_PNF:
                  str = _T ("The specified path was not found.");
                  break;
                case SE_ERR_FNF:
                  str = _T ("The specified file was not found.");
                  break;
                case ERROR_BAD_FORMAT:
                  str = _T ("The .EXE file is invalid\n(non-Win32 .EXE or error in .EXE image).");
                  break;
                case SE_ERR_ACCESSDENIED:
                  str = _T ("The operating system denied\naccess to the specified file.");
                  break;
                case SE_ERR_ASSOCINCOMPLETE:
                  str = _T ("The filename association is\nincomplete or invalid.");
                  break;
                case SE_ERR_DDEBUSY:
                  str = _T ("The DDE transaction could not\nbe completed because other DDE transactions\nwere being processed.");
                  break;
                case SE_ERR_DDEFAIL:
                  str = _T ("The DDE transaction failed.");
                  break;
                case SE_ERR_DDETIMEOUT:
                  str = _T ("The DDE transaction could not\nbe completed because the request timed out.");
                  break;
                case SE_ERR_DLLNOTFOUND:
                  str = _T ("The specified dynamic-link library was not found.");
                  break;
                case SE_ERR_NOASSOC:
                  str = _T ("There is no application associated\nwith the given filename extension.");
                  break;
                case SE_ERR_OOM:
                  str = _T ("There was not enough memory to complete the operation.");
                  break;
                case SE_ERR_SHARE:
                  str = _T ("A sharing violation occurred.");
                  break;
                default:
                  str.Format (_T ("Unknown Error (%d) occurred."), (int) result);
                }
              str = _T ("Unable to open hyperlink:\n\n") + str;
              AfxMessageBox (str, MB_ICONEXCLAMATION | MB_OK);
            }
          else
            return TRUE;
        }
    }
  return FALSE;
}

  

LONG CSampleView::GetRegKey (HKEY key, LPCTSTR subkey, LPTSTR retdata)
{
  HKEY hkey;
  LONG retval = RegOpenKeyEx (key, subkey, 0, KEY_QUERY_VALUE, &hkey);

  if (retval == ERROR_SUCCESS)
    {
      long datasize = MAX_PATH;
      TCHAR data[MAX_PATH];
      RegQueryValue (hkey, NULL, data, &datasize);
      _tcscpy (retdata, data);
      RegCloseKey (hkey);
    }

  return retval;
}

void CSampleView::OnHelpRendersoftproductsVrmleditor() 
{
	// TODO: Add your command handler code here
	Openlink("http://home.pacific.net.sg/~jupboo");
	
}

void CSampleView::OnHelpRendersoftproductsAtomixbuttons() 
{
	// TODO: Add your command handler code here
	Openlink("http://www.atomixbuttons.com");
	
}

void CSampleView::OnHelpRendersoftproductsIllusionae() 
{
	// TODO: Add your command handler code here
	Openlink("http://web.singnet.com.sg/~rendsoft");
}

void CSampleView::OnHelpTextcalcwebsite() 
{
	// TODO: Add your command handler code here
	Openlink("http://www.atomixbuttons.com/textcalc");
	
}


void CSampleView::OnTextNumberline() 
{
	// TODO: Add your command handler code here
	/*
	if (m_addfirst.DoModal()==IDOK) {

			m_addfirstword=m_addfirst.m_insertstring;
			if (m_addfirst.m_insertspace)
				m_insertspaceafterword=TRUE;
			else
				m_insertspaceafterword=FALSE;

			if (m_addfirst.m_skiplines)
				m_skiplinesBegin=TRUE;
			else
				m_skiplinesBegin=FALSE;
			
			ApplySelection(ADDFIRSTWORD,WTEXT);
	}
	*/

	//need to create a dialog for number lines
	//need to adjust applysingleline and handle the options return by the dialog

	m_curcount=0;
	ApplySelection(NUMBERLINES,WTEXT);

	
}
