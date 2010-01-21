// Link.cpp: implementation of the CLink class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sample.h"
#include "Link.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLink::CLink()
{

}

CLink::~CLink()
{

}




/*
BOOL CLink::OpenUsingCom (int how )
{
  //Get the URL Com interface
  IUniformResourceLocator *pURL;
  HRESULT hres = CoCreateInstance (CLSID_InternetShortcut, NULL, CLSCTX_INPROC_SERVER, IID_IUniformResourceLocator, (void **) &pURL);
  if (!SUCCEEDED (hres))
    {
      TRACE ("Failed to get the IUniformResourceLocator interface\n");
      return FALSE;
    }

  hres = pURL->SetURL (m_sActualLink, IURL_SETURL_FL_GUESS_PROTOCOL);
  if (!SUCCEEDED (hres))
    {
      TRACE ("Failed in call to SetURL\n");
      pURL->Release ();
      return FALSE;
    }

  //Open the URL by calling InvokeCommand
  URLINVOKECOMMANDINFO ivci;
  ivci.dwcbSize = sizeof (URLINVOKECOMMANDINFO);
  ivci.dwFlags = IURL_INVOKECOMMAND_FL_ALLOW_UI;
  ivci.hwndParent = GetParent ()->GetSafeHwnd ();
  switch (how)
    {
    case OPEN:
      ivci.pcszVerb = _T ("open");
      break;
    case EDIT:
      ivci.pcszVerb = _T ("edit");
      break;
    case PRINT:
      ivci.pcszVerb = _T ("print");
      break;
    default:
      ASSERT (FALSE);
    }
  hres = pURL->InvokeCommand (&ivci);
  if (!SUCCEEDED (hres))
    {
      TRACE ("Failed to invoke URL using InvokeCommand\n");
      pURL->Release ();
      return FALSE;
    }

  // Release the pointer to IUniformResourceLocator.
  pURL->Release ();

  return TRUE;
}
*/

BOOL CLink::Open (int how /*= OPEN*/ )
{

  //First try to open using IUniformResourceLocator
  //BOOL bSuccess = OpenUsingCom (how);
  BOOL bSuccess = FALSE;

  //As a last resort try ShellExecuting the URL, may
  //even work on Navigator!
  if (!bSuccess)
    bSuccess = OpenUsingShellExecute (how);

  if (!bSuccess)
    bSuccess = OpenUsingRegisteredClass (how);
  return bSuccess;
}


BOOL CLink::OpenUsingShellExecute (int how /*= OPEN*/ )
{
  LPCTSTR mode;
  switch (how)
    {
    case OPEN:
      mode = _T ("open");
      break;
    case EDIT:
      mode = _T ("edit");
      break;
    case PRINT:
      mode = _T ("print");
      break;
    default:
      ASSERT (FALSE);
      mode = _T ("open");
    }
  HINSTANCE hRun = ShellExecute (GetParent ()->GetSafeHwnd (), mode, m_sActualLink, NULL, NULL, SW_SHOW);
  if ((int) hRun <= HINSTANCE_ERROR)
    {
      TRACE ("Failed to invoke URL using ShellExecute\n");
      return FALSE;
    }
  return TRUE;
}

LONG
GetRegKey (HKEY key, LPCTSTR subkey, LPTSTR retdata)
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

BOOL CLink::
OpenUsingRegisteredClass (int how /*= OPEN*/ )
{
  TCHAR key[MAX_PATH + MAX_PATH];
  HINSTANCE result;

  if (GetRegKey (HKEY_CLASSES_ROOT, _T (".htm"), key) == ERROR_SUCCESS)
    {
      LPCTSTR mode;
      switch (how)
        {
        case OPEN:
          mode = _T ("\\shell\\open\\command");
          break;
        case EDIT:
          mode = _T ("\\shell\\edit\\command");
          break;
        case PRINT:
          mode = _T ("\\shell\\print\\command");
          break;
        default:
          mode = _T ("\\shell\\open\\command");
          ASSERT (FALSE);
        }
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
          _tcscat (pos, m_sActualLink);
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


void CLink::
SetHyperLink (const CString & sActualLink)
{
  SetActualHyperLink (sActualLink);
}


void CLink::SetActualHyperLink (const CString & sActualLink)
{
  m_sActualLink = sActualLink;
  CheckActualHyperLink ();
  
}

void CLink::
CheckActualHyperLink ()
{
  int pos = m_sActualLink.Find (_T ('\n'));
  if (pos != -1)
    {
 
      int pos1 = m_sActualLink.Mid (pos + 1).Find (_T ('\n'));
      if (pos1 != -1)
        {
 
          m_sActualLink = m_sActualLink.Mid (pos + 1, pos1);
        }
      else
        {
          m_sActualLink = m_sActualLink.Mid (pos + 1);
 
        }
    }
}