// Link.h: interface for the CLink class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINK_H__81E1AA46_8C87_11D3_9F2C_F2073F59A624__INCLUDED_)
#define AFX_LINK_H__81E1AA46_8C87_11D3_9F2C_F2073F59A624__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

enum State
{
  ST_NOT_VISITED,
  ST_VISITED,
  ST_VISIT_FAILED,
  ST_HIGHLIGHTED
};
enum Mode
{
  OPEN,
  EDIT,
  PRINT
};


class CLink  
{
public:
	CLink();
	virtual ~CLink();

	CString m_sActualLink;
	BOOL Open (int how = OPEN );
	BOOL OpenUsingCom (int how = OPEN );
	BOOL OpenUsingShellExecute (int how = OPEN );
	LONG GetRegKey (HKEY key, LPCTSTR subkey, LPTSTR retdata);
	BOOL OpenUsingRegisteredClass (int how = OPEN );

	void SetHyperLink (CString & sActualLink);
    CString GetActualHyperLink () 
    {
      return m_sActualLink;
    };

	void SetActualHyperLink (const CString & sActualLink);
    void CheckActualHyperLink ();

};

#endif // !defined(AFX_LINK_H__81E1AA46_8C87_11D3_9F2C_F2073F59A624__INCLUDED_)
