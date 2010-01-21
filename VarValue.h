// VarValue.h: interface for the CNumericValue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCVV_H__AC8E70D6_333D_11D2_89A8_00002145DF63__INCLUDED_)
#define AFX_TCVV_H__AC8E70D6_333D_11D2_89A8_00002145DF63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Value.h"

class CNumericValue : public CValue  
{
public:
	void SetValue(double value);
	virtual double GetValue(void);
	CNumericValue();
	virtual ~CNumericValue();

};

#endif // !defined(AFX_TCVV_H__AC8E70D6_333D_11D2_89A8_00002145DF63__INCLUDED_)
