//////////////////////////////////////////////////////////////////////////
//
//	EditOnlyNumber.cpp
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
// EditOnlyNumber.cpp : ʵ���ļ�
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



// CEditOnlyNumber ��Ϣ�������



void CEditOnlyNumber::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if ( ( nChar > '9' || nChar < '0' ) && 8 != nChar )
	{
		return;
	}

	CEdit::OnChar(nChar, nRepCnt, nFlags);
}
