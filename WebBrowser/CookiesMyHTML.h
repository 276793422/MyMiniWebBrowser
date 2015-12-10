//////////////////////////////////////////////////////////////////////////
//
//	CookiesMyHTML.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////

#pragma once


#include <afxinet.h>

class CCookiesMyHTML
{
public:
	CCookiesMyHTML();
	~CCookiesMyHTML();

	//��ȡ��ǰHtml��URL��Cookies
	UINT GetCookies( LPCTSTR pstrUrl ,
					CString& strCookie);

	//��ȡCookies��һ����ֵ
	UINT GetCookiesAValue( LPCTSTR pstrUrl ,
							LPCTSTR pstrCookieName ,
							CString& strCookieData);

	//����Cookies��һ����ֵ
	UINT SetCookies( LPCTSTR pstrUrl ,
						LPCTSTR pstrCookieName ,
						LPCTSTR pstrCookieData);


};
