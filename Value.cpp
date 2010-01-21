// Valoare.cpp: implementation of the CValue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Express.h"
#include "Value.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


IMPLEMENT_SERIAL(CValue, CObject, 0)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CValue::CValue()
{
	m_value = NULL;
}

CValue::~CValue()
{
	delete m_value;
}

void CValue::Serialize(CArchive & ar)
{

}


void CValue::UpdateValue()
{
}

double CValue::GetValue()
{
	return 0;
}

void CValue::SetValue(void* value)
{
	m_value = value;
}
