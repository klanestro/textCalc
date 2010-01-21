// Valoare.h: interface for the CValue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCVALUE_H__5231D2C4_B344_11D1_866F_00002145DF63__INCLUDED_)
#define AFX_TCVALUE_H__5231D2C4_B344_11D1_866F_00002145DF63__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000




class CValue : public CObject  
{
public:
	DECLARE_SERIAL(CValue);
	virtual void SetValue(void* value);
	virtual double GetValue(void);
	virtual void UpdateValue(void);
	virtual void Serialize(CArchive &ar);
	CValue();
	virtual ~CValue();

protected:
	void *m_value;
};

#endif // !defined(AFX_TCVALUE_H__5231D2C4_B344_11D1_866F_00002145DF63__INCLUDED_)
