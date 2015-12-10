//////////////////////////////////////////////////////////////////////////
//
//	DlgHOOKBaseMessage.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "afxwin.h"
#include "afxcmn.h"

//做HOOK的类
#include "IATHookAPI.h"
#include "ApiHook.h"

//保存参数的链表
#include "MyList.h"


// CDialogHOOKBaseMessage 对话框

class CHTMLDlg;

// 链表内部的参数结构体
struct SMySocketParam
{
	//	这个是存储的时候，对应函数里面的List列表的索引
	int m_index;
	//	缓冲区长度及缓冲区指针
	int m_lenth;
	char * m_buf;

	SMySocketParam()
	{
		m_buf = NULL;
		m_lenth = 0;
	}
	~SMySocketParam()
	{
		if ( NULL != m_buf )
		{
			free( m_buf );
		}
	}
};

class CDlgHOOKBaseMessage : public CDialog
{
	DECLARE_DYNAMIC(CDlgHOOKBaseMessage)

public:
	CDlgHOOKBaseMessage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgHOOKBaseMessage();

// 对话框数据
	enum { IDD = IDD_OLE_PROPPAGE_SMALL_HOOK_BASE_MESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButtonDialogHookButtonStartHook();
	afx_msg void OnBnClickedButtonDialogHookButtonStopHook();
	afx_msg void OnBnClickedButtonDialogHookButtonReinit();
	afx_msg void OnBnClickedButtonHookButtonCleanInfoList();
	afx_msg void OnBnClickedButtonDialogHookButtonStopHookNow();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkListHookListctrlGetMsgInfoIndex(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedRadioHookMakeTheAnsiStringAndAll();
	afx_msg void OnBnClickedRadioHookMakeTheUnicodeStringAndAll();
	afx_msg void OnBnClickedRadioHookMakeTheAnsiStringNoOther();
	afx_msg void OnBnClickedRadioHookMakeTheUnicodeStringNoOther();
public:
	// HOOK初始化函数
	UINT HookInitFun();

	// HOOK send 函数里面要做的事
	UINT SendTODO( IN SOCKET s , char FAR * buf , IN int len , IN int flags );
	// HOOK recv 函数里面要做的事
	UINT RecvTODO( IN SOCKET s , char FAR * buf , IN int len , IN int flags );

	// 清空参数列表
	UINT DeleteAllParam();

	// 把参数数据，解析了放进Edit
	UINT MakeHookInfomation( SMySocketParam *ssp );

	UINT MakeInfomationANSI( unsigned char * buf , int len , CString &strCode );
	UINT MakeInfomationUNICODE( unsigned char * buf , int len , CString &strCode );
	UINT MakeInfomationANSIString( unsigned char * buf , int len , CString &strCode );
	UINT MakeInfomationUNICODEString( unsigned char * buf , int len , CString &strCode );
public:
	CHTMLDlg *m_pParent;
	// HOOK状态提示信息
	CEdit m_EdtHOOKStatusIsHOOKing;
	// 网络信息索引列表，抓到的全部信息索引都在这里
	CListCtrl m_ListCtrlInternetInfoIndex;
	// 做HOOK的类
	enum 
	{
		SEND = 0 ,
		RECV ,
		SENDTO ,
		RECVFROM ,
		WSASEND ,
		WSARECV ,
		WSASENDTO ,
		WSARECVFROM ,
		FUNNUMBER
	};
	HOOK_STRUCT m_HookStruct[FUNNUMBER];
	// CListCtrl 的索引，HOOK向列表中添加信息的时候，就是利用这个索引来添加
	int m_nListIndex ;

	// 数据信息链表，保存了每个数据包的信息
	CMyList<SMySocketParam*> m_listMyListTable;

	CEdit m_EdtHOOKMessageInfomation;

	// 数据包详细信息解析方式  0:ANSI所有	1:UNICODE所有	2:ANSI字符串	3:UNICODE字符串
	int m_infoType;
};
