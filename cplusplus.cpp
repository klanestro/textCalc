#include "stdafx.h"
#include "SampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	C++ keywords (MSVC5.0 + POET5.0)
static LPTSTR s_apszCppKeywordList[] =
{

	_T("sin"),
	_T("cos"),
	_T("tan"),
	//_T("cot"),
	_T("asin"),
	_T("acos"),
	_T("atan"),
	_T("sinh"),
	_T("cosh"),
	_T("tanh"),
	_T("ln"),
	_T("log10"),
	_T("log"),
	_T("root"),
	_T("abs"),
	_T("exp"),
	_T("sqr"),
	_T("sqrt"),
	_T("Error"),
	_T("Divide_By_0"),
	//_T("_???_"),
	_T("deg2rad"),
	_T("rad2deg"),
	_T("remainder"),
	_T("div"),
	_T("fact"),
	_T("nCr"),
	_T("nPr"),
	NULL
};

static BOOL IsCppKeyword(LPCTSTR pszChars, int nLength)
{
	for (int L = 0; s_apszCppKeywordList[L] != NULL; L ++)
	{
		if (strncmp(s_apszCppKeywordList[L], pszChars, nLength) == 0
				&& s_apszCppKeywordList[L][nLength] == 0)
			return TRUE;
	}
	return FALSE;
}

static BOOL IsCppNumber(LPCTSTR pszChars, int nLength)
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

#define DEFINE_BLOCK(pos, colorindex)	\
	ASSERT((pos) >= 0 && (pos) <= nLength);\
	if (pBuf != NULL)\
	{\
		if (nActualItems == 0 || pBuf[nActualItems - 1].m_nCharPos <= (pos)){\
		pBuf[nActualItems].m_nCharPos = (pos);\
		pBuf[nActualItems].m_nColorIndex = (colorindex);\
		nActualItems ++;}\
	}

#define COOKIE_COMMENT			0x0001
#define COOKIE_PREPROCESSOR		0x0002
#define COOKIE_EXT_COMMENT		0x0004
#define COOKIE_STRING			0x0008
#define COOKIE_CHAR				0x0010

DWORD CSampleView::ParseLine(DWORD dwCookie, int nLineIndex, TEXTBLOCK *pBuf, int &nActualItems)
{
	int nLength = GetLineLength(nLineIndex);
	if (nLength <= 0)
		return dwCookie & COOKIE_EXT_COMMENT;

	LPCTSTR pszChars    = GetLineChars(nLineIndex);
	BOOL bFirstChar     = (dwCookie & ~COOKIE_EXT_COMMENT) == 0;
	BOOL bRedefineBlock = TRUE;
	BOOL bDecIndex  = FALSE;
	int nIdentBegin = -1;
	for (int I = 0; ; I++)
	{
		if (bRedefineBlock)
		{
			int nPos = I;
			if (bDecIndex)
				nPos--;

			if (dwCookie & (COOKIE_COMMENT | COOKIE_EXT_COMMENT))
			{
				DEFINE_BLOCK(nPos, COLORINDEX_COMMENT);
			}
			else
			if (dwCookie & (COOKIE_STRING))
			{
				DEFINE_BLOCK(nPos, COLORINDEX_STRING);
			}
			else
			{
				DEFINE_BLOCK(nPos, COLORINDEX_NORMALTEXT);
			}
			bRedefineBlock = FALSE;
			bDecIndex      = FALSE;
		}

		if (I == nLength)
			break;

		if (dwCookie & COOKIE_COMMENT)
		{
			DEFINE_BLOCK(I, COLORINDEX_COMMENT);
			dwCookie |= COOKIE_COMMENT;
			break;
		}

		//	String constant "...."
		if (dwCookie & COOKIE_STRING)
		{
			if (pszChars[I] == '"' && (I == 0 || pszChars[I - 1] != '\\'))
			{
				dwCookie &= ~COOKIE_STRING;
				bRedefineBlock = TRUE;
			}
			continue;
		}

		
		
		//	Extended comment /*....*/
		/*
		if (dwCookie & COOKIE_EXT_COMMENT)
		{
			if (I > 0 && pszChars[I] == '/' && pszChars[I - 1] == '*')
			{
				dwCookie &= ~COOKIE_EXT_COMMENT;
				bRedefineBlock = TRUE;
			}
			continue;
		}
		*/
		
		if (dwCookie & COOKIE_EXT_COMMENT)
		{
			if ((I > 1 && pszChars[I] == '/' && pszChars[I - 1] == '*' && pszChars[I-2] !=
			'/')|| (I==1 && pszChars[I] == '/' && pszChars[I - 1] == '*'))
			{
				dwCookie &= ~COOKIE_EXT_COMMENT;
				bRedefineBlock = TRUE;
			}
			continue;
		}

		


		if (I > 0 && pszChars[I] == '/' && pszChars[I - 1] == '/')
		{
			DEFINE_BLOCK(I - 1, COLORINDEX_COMMENT);
			dwCookie |= COOKIE_COMMENT;
			break;
		}

		

		//	Normal text
		if (pszChars[I] == '"')
		{
			DEFINE_BLOCK(I, COLORINDEX_STRING);
			dwCookie |= COOKIE_STRING;
			continue;
		}
		

		if (I > 0 && pszChars[I] == '*' && pszChars[I - 1] == '/')
		{
			DEFINE_BLOCK(I - 1, COLORINDEX_COMMENT);
			dwCookie |= COOKIE_EXT_COMMENT;
			continue;
		}

		

		if (pBuf == NULL)
			continue;	//	We don't need to extract keywords,
						//	for faster parsing skip the rest of loop


		//q: this function is to be used to parse summation and stats
		//but for express.cpp, only the isCppNumber should be used...
		//only in very strict case is the - an identifier, else it is always a separator...

		//logic: most of the time, the - is still treated as a separator
		//only in certain case, where (1) the right is a . or digit will it be considered a indentifier
		//even if (1) is true, we still need to check the left side. If it is not separator..then the - will still be considered a separator
		//therefore, only invery strict case where the left side of the - is a separator and the right side is ok before it can be considered an identifier and become a unary minus
		BOOL minusID=FALSE; //assume  '-' is separator
		if ((pszChars[I] == '-') && (I+1 != nLength)) {

			if (isdigit(pszChars[I+1]) ||  (pszChars[I+1] == '.')) {

				if ((I-1)>=0) {
					//if ((isdigit(pszChars[I-1])) ||  (pszChars[I-1] == '.')) {
					if (isalnum(pszChars[I-1]) || pszChars[I-1] == '_' || pszChars[I-1] == '.' || pszChars[I-1] == '-') //if there is anything on the left side that is not separator, it becomes separator
					{
						minusID=FALSE;  //becomes separtor
					}
					else
						minusID=TRUE;
				}
				else
					minusID=TRUE; //'-' is not separator, but identifier

			}

		}

		
		if (isalnum(pszChars[I]) || pszChars[I] == '_' || pszChars[I] == '.' || minusID)
		{
			if (nIdentBegin == -1)
				nIdentBegin = I;
		}
		else
		{ //here means a separator is encountered, whether it is comma or white space or etc..
		  //nindent =-1 indicates the start of a new word
			if (nIdentBegin >= 0)
			{
				if (IsCppKeyword(pszChars + nIdentBegin, I - nIdentBegin))
				{
					DEFINE_BLOCK(nIdentBegin, COLORINDEX_KEYWORD);
				}
				else {

					if (IsCppNumber(pszChars + nIdentBegin, I - nIdentBegin))
					{
						DEFINE_BLOCK(nIdentBegin, COLORINDEX_NUMBER);
					}
				}
				
				
					bRedefineBlock = TRUE;
					bDecIndex = TRUE;
					nIdentBegin = -1;
				

			}
		}
	}

	
	
	if (nIdentBegin >= 0)
	{
		if (IsCppKeyword(pszChars + nIdentBegin, I - nIdentBegin))
		{
			DEFINE_BLOCK(nIdentBegin, COLORINDEX_KEYWORD);
		}
		else
		if (IsCppNumber(pszChars + nIdentBegin, I - nIdentBegin))
		{
			DEFINE_BLOCK(nIdentBegin, COLORINDEX_NUMBER);
		}
	}

	

	//if (pszChars[nLength - 1] != '\\')
		dwCookie &= COOKIE_EXT_COMMENT;

	return dwCookie;
}


