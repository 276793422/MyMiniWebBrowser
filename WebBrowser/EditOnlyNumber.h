//////////////////////////////////////////////////////////////////////////
//
//	EditOnlyNumber.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#pragma once


// CEditOnlyNumber

class CEditOnlyNumber : public CEdit
{
	DECLARE_DYNAMIC(CEditOnlyNumber)

public:
	CEditOnlyNumber();
	virtual ~CEditOnlyNumber();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};


