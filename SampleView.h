// SampleView.h : interface of the CSampleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCSAMPLEVIEW_H__B1B69ED3_9FCE_11D2_8CA4_0080ADB8683C__INCLUDED_)
#define AFX_TCSAMPLEVIEW_H__B1B69ED3_9FCE_11D2_8CA4_0080ADB8683C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CCrystalEditView.h"
#include "Express.h"	

#define GENERIC -1
#define ACCUM 0
#define APPLY 1
#define STOREMEAN 2
#define STOREMEANSQR 3
#define STORESUMOFSQR 4
#define STORECOUNTER 5

#define CONVERSION 19
#define WTEXT 20
#define ADDFIRSTWORD 21
#define ADDLASTWORD 22
#define REMOVEFIRSTWORD 23
#define REMOVELASTWORD 24
#define KEEPFIRSTWORD 25
#define KEEPLASTWORD 26
#define DEC2HEX 27
#define HEX2DEC 28
#define DEC2OCT 29
#define OCT2DEC 30
#define OCT2HEX 31
#define HEX2OCT 32
#define NUMBERLINES 33
#define FORMAT_NUMBERS 50
#define EXTRACT_NUMBERS 51
#define MEMORY 100


#define REPLACE_RESULTS 0
#define INSERT_RESULTS 1
#define OUTPUT_RESULTS 2
#define TEST_BOUNDS 2


enum State
{
  ST_NOT_VISITED,
  ST_VISITED,
  ST_VISIT_FAILED,
  ST_HIGHLIGHTED
};

class CSampleDoc;

class CSampleView : public CCrystalEditView
{
protected: // create from serialization only
	CSampleView();
	DECLARE_DYNCREATE(CSampleView)

// Attributes
public:
	CSampleDoc* GetDocument();

	virtual CCrystalTextBuffer *LocateTextBuffer();
	static CString RemoveWhiteSpace(CString m_ExprStr);
	CString ChopNewline(CString m_ExprStr);
	CString ValidatePrefix(CString newstr,int&);
	CString ValidateSuffix(CString newstr,int&);


	//Calc values	
	CMapVariabile m_VarsMap;
	CExpression m_expression;
	CString	m_ExprStr;
	double	m_Result;



protected:
	virtual DWORD ParseLine(DWORD dwCookie, int nLineIndex, TEXTBLOCK *pBuf, int &nActualItems);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSampleView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:

	BOOL Openlink (CString);
	BOOL OpenUsingShellExecute (CString);
	LONG GetRegKey (HKEY key, LPCTSTR subkey, LPTSTR retdata);
	BOOL OpenUsingRegisteredClass (CString);

	CString GetProgPath();
	BOOL insertFile(CString filex,int dirspec=0);
	BOOL insertString(CString str,int loc=0);
	BOOL IsOctInteger(char *str);
	int ApplyWord(int function, int wtype);
	BOOL IsHexInteger(char *str);
	BOOL IsDecInteger(char *str);
	int handleword(int function, int wbegin, int wend, int nIndex);
	BOOL CheckSeparator(char x);
	BOOL m_hexspace;
	BOOL m_hexuser;
	CString m_hexuserstr;
	BOOL m_resultsinnextline;
	int m_lineoffset;
	int m_linecounter;
	BOOL m_klspace;
	BOOL m_kluser;
	BOOL m_klseparator;
	CString m_kluserstr;
	BOOL m_kfspace;
	BOOL m_kfuser;
	BOOL m_kfseparator;
	CString m_kfuserstr;
	int ReverseFindOneOf(CString orgstr,CString sepstr);
	BOOL m_rfspace;
	BOOL m_rfuser;
	BOOL m_rfseparator;
	CString m_rfuserstr;
	BOOL m_rlspace;
	BOOL m_rluser;
	BOOL m_rlseparator;
	CString m_rluserstr;
	char m_formatstr[30];
	BOOL m_formatprefix;
	BOOL m_formatsuffix;
	BOOL m_formatdigits;
	CString m_prefixstr;
	CString m_suffixstr;
	int m_numdigits;
	BOOL m_skiplinesBegin;
	BOOL m_skiplinesEnd;
	BOOL m_insertspacebeforeword;
	BOOL m_insertspaceafterword;
	CString m_addlastword;
	CString m_addfirstword;
	int m_curcount;
	int m_lastcount;
	int m_applyresultstatus;
	CString m_insertText;
	CString m_applyexpression;
	double m_applyvalue;
	double m_applyfactor;
	int m_applytype;
	BOOL ApplySelection(int fn,int wtype);
	CString ResultApplySingleLine(int function,int wtype);
	BOOL InitApplySingleLine(int function,int wtype);
	BOOL ApplySingleLine(int nLineIndex,int xstart=-1, int xend=-1,int function=0,int wtype=0);
	static int EvalExpression(int idx, double xvalue,CString ExprStr, double& retResult,CString& retStr);
	double m_percentile2;
	double m_percentile1;
	double m_percentile;
	double m_count;
	double * m_dataval;
	double m_sumofsqr;
	double m_meansqr;
	double m_totaldeviation;
	void InsertResultText(CPoint sStart, CPoint sEnd, CString newstr);
	double m_mean;
	double m_counter;
	BOOL WorkSelection(int fn,int wtype);
	double m_sum;
	CString ResultWorkSingleLine(int function);
	void InitWorkSingleLine(int function);
	BOOL WorkSingleLine(int nLineIndex,int xstart=-1, int xend=-1,int function=0,int wtype=0);
	//BOOL IsInternetConnected (void);
	int m_opSelectPartial;
	virtual ~CSampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSampleView)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCalculate();
	afx_msg void OnDestroy();
	afx_msg void OnSum();
	afx_msg void OnCalculateAverage();
	afx_msg void OnCalculateSumofsquares();
	afx_msg void OnCalculateRootmeansquare();
	afx_msg void OnCalculateMdmean();
	afx_msg void OnCalculateCountitems();
	afx_msg void OnCalculateMedian();
	afx_msg void OnCalculateStandarddeviation();
	afx_msg void OnCalculateVariance();
	afx_msg void OnCalculateApplynumbers();
	afx_msg void OnCalculateFindminandmaxvalues();
	afx_msg void OnTextAddfirstword();
	afx_msg void OnTextAddlastword();
	afx_msg void OnCalculateFormatnumbers();
	afx_msg void OnTextRemovefirstword();
	afx_msg void OnTextRemovelastword();
	afx_msg void OnTextKeepfirstword();
	afx_msg void OnTextKeeplastword();
	afx_msg void OnCalculateExtractnumbers();
	afx_msg void OnTextMakeintooneline();
	afx_msg void OnCalculateComputeoptions();
	afx_msg void OnButton32829();
	afx_msg void OnDec();
	afx_msg void OnConversionDecimaltohex();
	afx_msg void OnConversionDecimaltooct();
	afx_msg void OnConversionHextodecimal();
	afx_msg void OnConversionOcttodecimal();
	afx_msg void OnCalculatePi3141592654();
	afx_msg void OnConversionUnits();
	afx_msg void OnConversionTablesArea();
	afx_msg void OnConversionTablesVolume();
	afx_msg void OnConversionTablesWeight();
	afx_msg void OnConversionHextooct();
	afx_msg void OnConversionOcttohex();
	afx_msg void OnHelpRendersoftproductsVrmleditor();
	afx_msg void OnHelpRendersoftproductsAtomixbuttons();
	afx_msg void OnHelpRendersoftproductsIllusionae();
	afx_msg void OnHelpTextcalcwebsite();
	afx_msg void OnTextNumberline();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SampleView.cpp
inline CSampleDoc* CSampleView::GetDocument()
   { return (CSampleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCSAMPLEVIEW_H__B1B69ED3_9FCE_11D2_8CA4_0080ADB8683C__INCLUDED_)
