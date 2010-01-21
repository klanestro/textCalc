// VarValue.cpp: implementation of the CNumericValue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VarValue.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNumericValue::CNumericValue()
{

}

CNumericValue::~CNumericValue()
{

}

double CNumericValue::GetValue()
{
	return *((double*)m_value);
}

void CNumericValue::SetValue(double value)
{
	double *val =  new double;
	*val = value;
	CValue::SetValue(val);
}
