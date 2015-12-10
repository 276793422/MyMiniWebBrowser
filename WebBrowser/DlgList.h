//////////////////////////////////////////////////////////////////////////
//
//	DlgList.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "ThreadCommandWork.h"
#include "EditOnlyNumber.h"
#include "InstructTranslationAndRun.h"

//�Զ����б��ר��
//���ר��
//��ȡ������Ϣ
#define GET_ADDITIONAL_INFOMATION( AA , BB )		(AA).GetItemText( (BB) , 2 );
//��������Ϣ
#define SET_ADDITIONAL_INFOMATION( AA , BB , CC )	(AA).SetItemText( (BB) , 2 , (CC) );

//����ͨ��
//��ȡָ����Ϣ
#define GET_INSTRUCTION_INFOMATION( AA , BB )		(AA).GetItemText( (BB) , 1 );
//��ָ����Ϣ
#define SET_INSTRUCTION_INFOMATION( AA , BB , CC )	(AA).SetItemText( (BB) , 1 , (CC) );
//������
#define SET_MAIN_INFOMATION( AA , BB , CC )			(AA).InsertItem( (BB) , (CC) );

//�ַ���ת�����ֺ�����ֻ����ô�ض���
#ifdef _UNICODE
#define stol wcstol
#else
#define stol strtol
#endif

class CHTMLDlg;

// CDlgList �Ի���

class CDlgList : public CDialog
{
	DECLARE_DYNAMIC(CDlgList)

public:
	CDlgList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgList();

// �Ի�������
	enum { IDD = IDD_OLE_PROPPAGE_SMALL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
public:
	afx_msg void OnNMDblclkListOpenedPageUrlOnlyOpen(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListCommadnInstructListFrom(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListCommandInstructList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLbnSelchangeList0();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedButtonCommandDefaultWithLeft();
	afx_msg void OnBnClickedInsertToTowList();
	afx_msg void OnBnClickedDeleteOneInTowList();
	afx_msg void OnBnClickedDeleteAllInTheTowList();
	afx_msg void OnBnClickedButtonCommandMakeItWork();
	afx_msg void OnBnClickedButtonCommandStopItWork();
	afx_msg void OnBnClickedButtonCommandPauseItWord();
	afx_msg void OnBnClickedButtonCommandInsertFromRightToLeft();
	afx_msg void OnBnClickedButtonCommandDeleteItemInLeft();
	afx_msg void OnBnClickedButtonCommandChangeAttachMessage();
	afx_msg void OnBnClickedButtonCommandMakeListItemUp();
	afx_msg void OnBnClickedButtonCommandMakeListItemDown();
	afx_msg void OnBnClickedButtonCommandClearTextOutEdit();
	afx_msg void OnBnClickedButtonCommandClearLeftList();
	void OnInitCommandList();
	void SetDialogEnableWindow( int i );
	void SetWindowCommandClickText( int list , int nindex );
	UINT TestCommandListItemLegal();
	void SetWindowTextToCommandEdit( CString word );

	CHTMLDlg * m_pParent;
	CThreadCommandWork m_ThreadCommandWork;
	int m_nCommandWorkStatus;
	CInstructTranslationAndRun m_InstructTAR;

	CEdit m_EdtName;
	CEdit m_EdtNum;
	CListBox m_LBX[2]; 
	CEdit m_EdtRecordURL;
	CEditOnlyNumber m_EdtRecordTime;
	//�����Զ���ListCtrl��0Ϊִ�еģ�1Ϊѡ���
	CListCtrl m_LclCmd[2];
	CEdit m_EdtCommandClick[2];
	int m_nCommandClick[2];
	CEdit m_EdtCommandAttachMessage;
	CEdit m_EdtCommandThreadTextOut;
	CListCtrl m_LclOpenedPageUrl;
};
