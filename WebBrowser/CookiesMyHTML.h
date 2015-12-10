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

	//获取当前Html上URL的Cookies
	UINT GetCookies( LPCTSTR pstrUrl ,
					CString& strCookie);

	//获取Cookies的一个键值
	UINT GetCookiesAValue( LPCTSTR pstrUrl ,
							LPCTSTR pstrCookieName ,
							CString& strCookieData);

	//设置Cookies的一个键值
	UINT SetCookies( LPCTSTR pstrUrl ,
						LPCTSTR pstrCookieName ,
						LPCTSTR pstrCookieData);


};
