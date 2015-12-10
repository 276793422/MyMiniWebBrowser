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

//自动化列表框专用
//左框专用
//获取附加信息
#define GET_ADDITIONAL_INFOMATION( AA , BB )		(AA).GetItemText( (BB) , 2 );
//赋附加信息
#define SET_ADDITIONAL_INFOMATION( AA , BB , CC )	(AA).SetItemText( (BB) , 2 , (CC) );

//两框通用
//获取指令信息
#define GET_INSTRUCTION_INFOMATION( AA , BB )		(AA).GetItemText( (BB) , 1 );
//赋指令信息
#define SET_INSTRUCTION_INFOMATION( AA , BB , CC )	(AA).SetItemText( (BB) , 1 , (CC) );
//赋主项
#define SET_MAIN_INFOMATION( AA , BB , CC )			(AA).InsertItem( (BB) , (CC) );

//字符串转化数字函数，只能这么重定义
#ifdef _UNICODE
#define stol wcstol
#else
#define stol strtol
#endif

class CHTMLDlg;

// CDlgList 对话框

class CDlgList : public CDialog
{
	DECLARE_DYNAMIC(CDlgList)

public:
	CDlgList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgList();

// 对话框数据
	enum { IDD = IDD_OLE_PROPPAGE_SMALL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	//两个自动的ListCtrl，0为执行的，1为选择的
	CListCtrl m_LclCmd[2];
	CEdit m_EdtCommandClick[2];
	int m_nCommandClick[2];
	CEdit m_EdtCommandAttachMessage;
	CEdit m_EdtCommandThreadTextOut;
	CListCtrl m_LclOpenedPageUrl;
};
