//////////////////////////////////////////////////////////////////////////
//
//	HTML.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
// HTML.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHTMLApp:
// �йش����ʵ�֣������ HTML.cpp
//

class CHTMLApp : public CWinApp
{
public:
	CHTMLApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHTMLApp theApp;