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

//��HOOK����
#include "IATHookAPI.h"
#include "ApiHook.h"

//�������������
#include "MyList.h"


// CDialogHOOKBaseMessage �Ի���

class CHTMLDlg;

// �����ڲ��Ĳ����ṹ��
struct SMySocketParam
{
	//	����Ǵ洢��ʱ�򣬶�Ӧ���������List�б������
	int m_index;
	//	���������ȼ�������ָ��
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
	CDlgHOOKBaseMessage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgHOOKBaseMessage();

// �Ի�������
	enum { IDD = IDD_OLE_PROPPAGE_SMALL_HOOK_BASE_MESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	// HOOK��ʼ������
	UINT HookInitFun();

	// HOOK send ��������Ҫ������
	UINT SendTODO( IN SOCKET s , char FAR * buf , IN int len , IN int flags );
	// HOOK recv ��������Ҫ������
	UINT RecvTODO( IN SOCKET s , char FAR * buf , IN int len , IN int flags );

	// ��ղ����б�
	UINT DeleteAllParam();

	// �Ѳ������ݣ������˷Ž�Edit
	UINT MakeHookInfomation( SMySocketParam *ssp );

	UINT MakeInfomationANSI( unsigned char * buf , int len , CString &strCode );
	UINT MakeInfomationUNICODE( unsigned char * buf , int len , CString &strCode );
	UINT MakeInfomationANSIString( unsigned char * buf , int len , CString &strCode );
	UINT MakeInfomationUNICODEString( unsigned char * buf , int len , CString &strCode );
public:
	CHTMLDlg *m_pParent;
	// HOOK״̬��ʾ��Ϣ
	CEdit m_EdtHOOKStatusIsHOOKing;
	// ������Ϣ�����б�ץ����ȫ����Ϣ������������
	CListCtrl m_ListCtrlInternetInfoIndex;
	// ��HOOK����
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
	// CListCtrl ��������HOOK���б��������Ϣ��ʱ�򣬾�������������������
	int m_nListIndex ;

	// ������Ϣ����������ÿ�����ݰ�����Ϣ
	CMyList<SMySocketParam*> m_listMyListTable;

	CEdit m_EdtHOOKMessageInfomation;

	// ���ݰ���ϸ��Ϣ������ʽ  0:ANSI����	1:UNICODE����	2:ANSI�ַ���	3:UNICODE�ַ���
	int m_infoType;
};
