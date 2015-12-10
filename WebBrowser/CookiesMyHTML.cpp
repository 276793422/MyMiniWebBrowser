//////////////////////////////////////////////////////////////////////////
//
//	CookiesMyHTML.cpp
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CookiesMyHTML.h"

CCookiesMyHTML::CCookiesMyHTML()
{
}

CCookiesMyHTML::~CCookiesMyHTML()
{
}


UINT CCookiesMyHTML::GetCookies(LPCTSTR pstrUrl, CString& strCookie)
{
	strCookie = _T("");

	DWORD dwLen;
	if (!InternetGetCookie(pstrUrl, NULL, NULL, &dwLen))
		return FALSE;

	TCHAR *buffer = new TCHAR[dwLen + 1];
	if (NULL == buffer)
		return FALSE;

	BOOL bRetVal = InternetGetCookie(pstrUrl, NULL, buffer, &dwLen);
	if (TRUE == bRetVal)
	{
		buffer[dwLen] = _T('\0');
		strCookie = buffer;
	}
	delete []buffer;

	return 1;
}


UINT CCookiesMyHTML::GetCookiesAValue( LPCTSTR pstrUrl ,
									  LPCTSTR pstrCookieName ,
									  CString& strCookieData)
{
	if (pstrCookieName == NULL || lstrcmp(pstrCookieName, _T("")) == 0)
	{
		return GetCookies(pstrUrl, strCookieData);
	}

	if (false == GetCookies(pstrUrl, strCookieData))
		return FALSE;


	strCookieData.Trim();
	strCookieData.Replace(_T("\t"), _T(""));
	strCookieData.Replace(_T(" "), _T(""));

	if (strCookieData[strCookieData.GetLength()-1] != _T(';'))
		strCookieData += _T(';');

	CString strCookieName(pstrCookieName);

	int k1 = strCookieData.Find(strCookieName);
	int k2;
	if (k1 >= 0)
	{
		k2 = strCookieData.Find(_T(';'), k1);
		if (k2 > k1)
		{
			k1 = strCookieData.Find(_T('='), k1);
			if (k1 >= 0)
			{
				strCookieData = strCookieData.Mid(k1 + 1, k2 - k1 -1);
			}
			else
			{
				strCookieData.Empty();
			}
			return TRUE;
		}
	}

	strCookieData.Empty();
	return false;
}


UINT CCookiesMyHTML::SetCookies( LPCTSTR pstrUrl ,
								   LPCTSTR pstrCookieName ,
								   LPCTSTR pstrCookieData)
{
	CString strCookie(pstrCookieName);
	strCookie += _T(" = ");
	strCookie += pstrCookieData;
	strCookie += _T(';');

	BOOL res = InternetSetCookie(pstrUrl, NULL, strCookie);
	return res != FALSE;
}