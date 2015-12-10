//////////////////////////////////////////////////////////////////////////
//
//	DlgCommandListInfomation.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////


#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "EditOnlyNumber.h"

//�ַ���ת�����ֺ�����ֻ����ô�ض���
#ifdef _UNICODE
#define stol wcstol
#else
#define stol strtol
#endif

class CHTMLDlg;

// CDlgCommandListInfomation �Ի���

class CDlgCommandListInfomation : public CDialog
{
	DECLARE_DYNAMIC(CDlgCommandListInfomation)

public:
	CDlgCommandListInfomation(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCommandListInfomation();

// �Ի�������
	enum { IDD = IDD_OLE_PROPPAGE_SMALL_COMMAND_LIST_INFOMATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
protected:
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();

public:
	afx_msg void OnBnClickedButtonCliAddToOpenList();
	afx_msg void OnBnClickedButtonCliDeleteUrlFromOpenList();
	afx_msg void OnBnClickedButtonCliDeleteAllUrlFromOpenList();
	afx_msg void OnBnClickedButtonCliSaveGetMessageToThisFile();
	afx_msg void OnBnClickedButtonCliCommandOpenPageListSiveToFile();
	afx_msg void OnBnClickedButtonCliCommandOpenPageListLoadFromFile();
	afx_msg void OnBnClickedButtonCliTheElementFromPageAddFirst();
	afx_msg void OnBnClickedButtonCliToGetTheElementLoadFromFile();
	afx_msg void OnBnClickedButtonCliToGetTheElementSaveToFile();
public:
	//ͨ�ô�ȡ���������ListCtrlΪ1���ұ�Ϊ2
	void LoadFileWithList( int mod = 0 );
	void SaveFileWithList( int mod = 0 );

	CHTMLDlg *m_pParent;

	CListCtrl m_LclCLICommandOpenURLList;
	CEdit m_EdtCLIAddToOpenList;
	CEditOnlyNumber m_EdtONCLIAddToOpenFrom;
	CEditOnlyNumber m_EdtONCLIAddToOpenTo;
	CEdit m_EdtCLIGetTheURLOnPageWithHandSymbol;
	CEdit m_EdtCLIGetTheURLOnPageWithLastSymbol;
	CEditOnlyNumber m_EdtCLIGetTheURLOnPageWithHandAndLastNum;
	CListCtrl m_LclCLIToGetTheElementFromPage;
	CEdit m_EdtCLISaveGetMessageToThisFile;
	CEdit m_EdtCLICommandOpenURLLoadFromFile;
	CEdit m_EdtCLICommandOpenURLSaveToFile;
	CEdit m_EdtCLITheElementFromPageAddFirst;
	CEdit m_EdtCLIToGetTheElenentLoadFromFile;
	CEdit m_EdtCLIToGetTheElenentSaveToFile;
	CStatic m_StcCLIElementListCount;
	afx_msg void OnBnClickedButtonCliTheElementFromPageDeleteAll();
	afx_msg void OnBnClickedButtonCliTheElementFromPageDeleteTheSame();
};
