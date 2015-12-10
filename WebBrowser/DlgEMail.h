//////////////////////////////////////////////////////////////////////////
//
//	DlgEMail.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "resource.h"
#include "afxwin.h"
#include "Smtp.h"
#include "afxcmn.h"
#include "EditOnlyNumber.h"
#include "ThreadMassEMail.h"
#include "POP3.h"
#include "ThreadRecvEMail.h"

class CHTMLDlg;

class CHtmlViewMail : public CHtmlView
{

};

//字符串转化数字函数，只能这么重定义
#ifdef _UNICODE
#define stol wcstol
#else
#define stol strtol
#endif


typedef struct _SEMailInfo
{
	CString m_ServerAddress;		//服务器地址
	CString m_ServerPort;			//服务器端口
	CString m_LoginTest;			//服务器验证方式

	CString m_UID;					//发送信件的用户名
	CString m_PWD;					//发送信件的密码
	CString m_Name;					//发件人全名
	CString m_Address;				//发件人信箱地址
	CString m_LocalIP;				//发送信件者的本地IP
	CString m_LocalPort;			//发送信件的本地端口

	CString m_Receiver;				//收件人信箱
	CString m_CC;					//抄送地址
	CString m_BCC;					//暗送地址

	CString m_Title;				//信件主题
	CString m_Attachment;			//附件列表
	CString m_Text;					//正文
}SEMailInfo;


#define WRONG_MSG_RTN( AAA , BBB ) if ( (AAA) ) {	MessageBox( (BBB) , _T("犯了个低级错误") );	return 1;	}

// CDlgEMail 对话框

class CDlgEMail : public CDialog
{
	DECLARE_DYNAMIC(CDlgEMail)

public:
	CDlgEMail(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgEMail();

// 对话框数据
	enum { IDD = IDD_OLE_PROPPAGE_SMALL_E_MAIL_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

protected:
	virtual void OnOK();
	virtual void OnCancel();

	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
public:
	afx_msg void OnNMDblclkListEMailReceiverPop3EMailList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonEMailSmtpSendEMailAnnexListAdd();
	afx_msg void OnBnClickedButtonEMailSmtpSendEMail();
	afx_msg void OnBnClickedButtonEMailSmtpCommandSaveToFile();
	afx_msg void OnBnClickedButtonEMailSmtpCommandLoadFromFile();
	afx_msg void OnBnClickedButtonEMailSmtpCommandMoveLeft();
	afx_msg void OnBnClickedButtonEMailSmtpCommandAdd();
	afx_msg void OnBnClickedButtonEMailSmtpCommandDelete();
	afx_msg void OnBnClickedButtonEMailSmtpCommandThreadStart();
	afx_msg void OnBnClickedButtonEMailSmtpCommandThreadStop();
	afx_msg void OnBnClickedButtonEMailSmtpMassEMailSend();
	afx_msg void OnBnClickedButtonEMailSmtpMassEMailSendStop();
	afx_msg void OnBnClickedButtonEMailSmtpMassEMailSaveToFile();
	afx_msg void OnBnClickedButtonEMailSmtpMassEMailReadFromFile();
	afx_msg void OnBnClickedButtonEMailSmtpSendEMailLoopStart();
	afx_msg void OnBnClickedButtonEMailSmtpSendEMailLoopStop();
	afx_msg void OnBnClickedButtonEMailReceiverPop3Connect();
	afx_msg void OnBnClickedButtonEMailReceiverPop3Open();
	afx_msg void OnBnClickedButtonEMailReceiverPop3Record();
	afx_msg void OnBnClickedButtonEMailReceiverPop3Delete();
	afx_msg void OnBnClickedButtonEMailReceiverPop3Quit();

public://邮件发送部分
	CSMTPConnection::LoginMethod m_Authenticate;
	DWORD m_Authenticate_1;
	BOOL m_BMime;
	BOOL m_BHTML;
	CString m_StrEncodingFriendly;
	CString m_StrEncodingCharset;

	CSMTPMessage* CreateMessage( SEMailInfo & EMailInfoSend );
	void SendEMail( SEMailInfo & EMailInfoSend );
	//邮件信息结构体
	SEMailInfo m_EMailInforSend;

	//Edit输入格式测试
	UINT TestEdit( SEMailInfo & EMailInfoSend );

public://总父窗口指针
	CHTMLDlg *m_pParent;

public://主界面部分发送邮件全部控件
	CComboBox m_CbBEMailSMTPServerTestMode;
	CEdit m_EdtEMailSMTPServerAddress;
	CEdit m_EdtEMailSMTPServerPort;
	CEdit m_EdtEMailSMTPSenderUserName;
	CEdit m_EdtEMailSMTPSenderPassWord;
	CEdit m_EdtEMailSMTPSenderAllName;
	CEdit m_EdtEMailSMTPSenderAddress;
	CEdit m_EdtEMailSMTPSenderLocalAddress;
	CEdit m_EdtEMailSMTPSenderLocalPort;
	CEdit m_EdtEMailSMTPRecverAddress;
	CEdit m_EdtEMailSMTPRecverAddressCC;
	CEdit m_EdtEMailSMTPRecverAddressBCC;
	CEdit m_EdtEMailSMTPSendEMailTitle;
	CEdit m_EdtEMailSMTPSendEMailAnnexList;
	CEdit m_EdtEMailSMTPSendEMailText;

	//内部控制台部分
	CEdit m_EdtEMailSMTPCommandSaveToFile;
	CEdit m_EdtEMailSMTPCommandLoadFromFile;
	CListCtrl m_LclEMailSMTPCommandList;
	CEditOnlyNumber m_EdtEMailSMTPCommandThreadNum;
	SEMailInfo m_EMailInforSendInThread;
	UINT m_nThreadNum;

	//邮件群发
	CEdit m_EdtEMailSMTPMassEMailAddress;
	CEditOnlyNumber m_EdtEMailSMTPMassEMailTime;
	CString m_StrMassEMail;
	UINT m_UnTime;
	SEMailInfo m_EMailInforSendInTimer;
	CThreadMassEMail m_ThreadMassEMail;

	//邮箱轰炸
	CStatic m_StcEMailSMTPSendEMailStatus;
	CEditOnlyNumber m_EdtEMailSMTPSendEMailLoopTime;
	CEditOnlyNumber m_EdtEMailSMTPSendEMailLoopNum;
	UINT m_UnLoopTime;
	UINT m_UnLoopNum;

public:
	//按钮的状态改变
	//0为邮件群发部分按下开始
	//2为邮件轰炸部分按下开始
	//4为发件信息多线程群发部分按下开始
	void MakeButtonStatus( int nStatus );

	UINT SetText( SEMailInfo & EMailInfoSend );

	void StringToStruct(  SEMailInfo & EMail , CString &str );
	CEdit m_EdtEMailPOP3EMailCachePath;
	CStatic m_StcEMailPOP3ReciverEMailStatus;


public://接收邮件
	CEdit m_EdtEMailPOP3Server;
	CEditOnlyNumber m_EdtEMailPOP3Port;
	CEdit m_EdtEMailPOP3UserName;
	CEdit m_EdtEMailPOP3PassWord;
	CListCtrl m_LclEMailPOP3EMailList;
	CHtmlViewMail *m_pHtmlView;
	CPOP3 m_Pop3;
	CThreadRecvEMail m_pThreadRecvEMail;
	int m_nListCtrlDrop;

	void MakeButtonStatusR( int nStatus );
	afx_msg void OnNMClickListEMailReceiverPop3EMailList(NMHDR *pNMHDR, LRESULT *pResult);
};
