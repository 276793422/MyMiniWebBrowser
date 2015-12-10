//////////////////////////////////////////////////////////////////////////
//
//	EditOnlyNumber.cpp
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
// EditOnlyNumber.cpp : 实现文件
//

#include "stdafx.h"
#include "HTML.h"
#include "EditOnlyNumber.h"


// CEditOnlyNumber

IMPLEMENT_DYNAMIC(CEditOnlyNumber, CEdit)

CEditOnlyNumber::CEditOnlyNumber()
{

}

CEditOnlyNumber::~CEditOnlyNumber()
{
}


BEGIN_MESSAGE_MAP(CEditOnlyNumber, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()



// CEditOnlyNumber 消息处理程序



void CEditOnlyNumber::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if ( ( nChar > '9' || nChar < '0' ) && 8 != nChar )
	{
		return;
	}

	CEdit::OnChar(nChar, nRepCnt, nFlags);
}
