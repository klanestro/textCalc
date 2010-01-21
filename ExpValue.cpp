// ExpValue.cpp: implementation of the CExpValue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExpValue.h"
#include "express.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExpValue::CExpValue()
{

}

CExpValue::~CExpValue()
{
}

double CExpValue::GetValue()
{
	double value;
	((CExpression *) m_value)->Value(value);
	return value;
}

void CExpValue::UpdateValue()
{
	((CExpression *) m_value)->UpdateArbore();
}
