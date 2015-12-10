//////////////////////////////////////////////////////////////////////////
//
//	HtmlViewMy.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#pragma once

#ifdef _WIN32_WCE
#error "Windows CE ��֧�� CHtmlView��"
#endif 

#include "HTMLDlg.h"
class CHTMLDlg;

#define ERROR_MESSAGE( hr , ERR_MSG , rtn )		\
	if( ( hr ) != S_OK )						\
	{											\
		MessageBox( (ERR_MSG) , _T("") );		\
		return (rtn) ;							\
	}



// CHtmlViewMy Html ��ͼ

class CHtmlViewMy : public CHtmlView
{
	DECLARE_DYNCREATE(CHtmlViewMy)

protected:
public:
	CHtmlViewMy();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CHtmlViewMy();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();


public:
	UINT FillTheList();

	UINT ClickButton( CString strBtnName );

	CHTMLDlg * m_pParent;

	CString SrandString();

	virtual void OnStatusTextChange(LPCTSTR lpszText);
	virtual void OnProgressChange(long nProgress, long nProgressMax);
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
};

