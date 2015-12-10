//////////////////////////////////////////////////////////////////////////
//
//	DlgProxy.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "ThreadTestProxy.h"
#include "EditOnlyNumber.h"

#ifdef _UNICODE
#define stol wcstol
#else
#define stol strtol
#endif

// CDlgProxy �Ի���

class CDlgProxy : public CDialog
{
	DECLARE_DYNAMIC(CDlgProxy)

public:
	CDlgProxy(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgProxy();

// �Ի�������
	enum { IDD = IDD_OLE_PROPPAGE_SMALL_PROXY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
protected:
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnNMClickListProxyList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListProxyList(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnBnClickedAddProxyToList();
	afx_msg void OnBnClickedReviseProxyInList();
	afx_msg void OnBnClickedDeleteProxyInList();
	afx_msg void OnBnClickedDeleteAllProxyInList();
	afx_msg void OnBnClickedButtonUseProxyInList();
	afx_msg void OnBnClickedButtonNoUseProxy();
	afx_msg void OnBnClickedButtonMakeInProxyFileDialog();
	afx_msg void OnBnClickedButtonSaveProxyList();
	afx_msg void OnBnClickedDeleteProxyInImportList();
	afx_msg void OnBnClickedDeleteAllProxyInImportList();
	afx_msg void OnBnClickedButtonRightListToLeft();
	afx_msg void OnBnClickedButtonLeftListToRight();
	afx_msg void OnBnClickedButtonClickAll();
	afx_msg void OnBnClickedButtonClickImportAll();
	afx_msg void OnBnClickedButtonAddTestHtmlPageToList();
	afx_msg void OnBnClickedButtonDeleteTestHtmlPageFromList();
	afx_msg void OnBnClickedButtonStartToTestProxyFromTowList();
	afx_msg void OnBnClickedButtonStopToTestProxyInTowList();
	afx_msg void OnBnClickedButtonDeleteTheBrockProxyInImportList();

	//���һ��ѡ���б���еڼ���
	int m_nLastClickInList;
	//�̳߳���
	CThreadTestProxy m_TTP;
public:
	CEdit m_EdtNowUseProxy;
	CListCtrl m_LclProxyList;
	CEdit m_EdtProxyAddress;
	CEdit m_EdtProxyName;
	CEdit m_EdtProxySpeed;
	CWnd *m_pParent;
	CEdit m_EdtMakeInFilePath;
	CListCtrl m_LclImportProxy;
	CEdit m_EdtSaveProxyListPath;
	CListCtrl m_LclGetProxyWithHtml;
	CListCtrl m_LclToTestProxyThePage;
	CEdit m_EdtTheProxyAnonymousLevel;
	CEdit m_EdtToUseHtmlPageToList;
	CEdit m_EdtToUseHtmlPageTestProxyFlag;
	CStatic m_StcTestProxyStatus;
	CEditOnlyNumber m_EdtTheTestProxyThreadNum;
};
