// ExpValue.h: interface for the CExpValue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCEALE_H__AC1A20C4_129D_20C1_1568_00002375CE22__INCLUDED_)
#define AFX_TCEALE_H__AC1A20C4_129D_20C1_1568_00002375CE22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Value.h"

class CExpValue : public CValue  
{
public:
	virtual void UpdateValue(void);
	virtual double GetValue(void);
	CExpValue();
	virtual ~CExpValue();

};

#endif // !defined(AFX_TCEALE_H__AC1A20C4_129D_20C1_1568_00002375CE22__INCLUDED_)
