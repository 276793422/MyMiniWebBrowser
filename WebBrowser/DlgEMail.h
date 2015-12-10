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

//�ַ���ת�����ֺ�����ֻ����ô�ض���
#ifdef _UNICODE
#define stol wcstol
#else
#define stol strtol
#endif


typedef struct _SEMailInfo
{
	CString m_ServerAddress;		//��������ַ
	CString m_ServerPort;			//�������˿�
	CString m_LoginTest;			//��������֤��ʽ

	CString m_UID;					//�����ż����û���
	CString m_PWD;					//�����ż�������
	CString m_Name;					//������ȫ��
	CString m_Address;				//�����������ַ
	CString m_LocalIP;				//�����ż��ߵı���IP
	CString m_LocalPort;			//�����ż��ı��ض˿�

	CString m_Receiver;				//�ռ�������
	CString m_CC;					//���͵�ַ
	CString m_BCC;					//���͵�ַ

	CString m_Title;				//�ż�����
	CString m_Attachment;			//�����б�
	CString m_Text;					//����
}SEMailInfo;


#define WRONG_MSG_RTN( AAA , BBB ) if ( (AAA) ) {	MessageBox( (BBB) , _T("���˸��ͼ�����") );	return 1;	}

// CDlgEMail �Ի���

class CDlgEMail : public CDialog
{
	DECLARE_DYNAMIC(CDlgEMail)

public:
	CDlgEMail(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgEMail();

// �Ի�������
	enum { IDD = IDD_OLE_PROPPAGE_SMALL_E_MAIL_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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

public://�ʼ����Ͳ���
	CSMTPConnection::LoginMethod m_Authenticate;
	DWORD m_Authenticate_1;
	BOOL m_BMime;
	BOOL m_BHTML;
	CString m_StrEncodingFriendly;
	CString m_StrEncodingCharset;

	CSMTPMessage* CreateMessage( SEMailInfo & EMailInfoSend );
	void SendEMail( SEMailInfo & EMailInfoSend );
	//�ʼ���Ϣ�ṹ��
	SEMailInfo m_EMailInforSend;

	//Edit�����ʽ����
	UINT TestEdit( SEMailInfo & EMailInfoSend );

public://�ܸ�����ָ��
	CHTMLDlg *m_pParent;

public://�����沿�ַ����ʼ�ȫ���ؼ�
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

	//�ڲ�����̨����
	CEdit m_EdtEMailSMTPCommandSaveToFile;
	CEdit m_EdtEMailSMTPCommandLoadFromFile;
	CListCtrl m_LclEMailSMTPCommandList;
	CEditOnlyNumber m_EdtEMailSMTPCommandThreadNum;
	SEMailInfo m_EMailInforSendInThread;
	UINT m_nThreadNum;

	//�ʼ�Ⱥ��
	CEdit m_EdtEMailSMTPMassEMailAddress;
	CEditOnlyNumber m_EdtEMailSMTPMassEMailTime;
	CString m_StrMassEMail;
	UINT m_UnTime;
	SEMailInfo m_EMailInforSendInTimer;
	CThreadMassEMail m_ThreadMassEMail;

	//�����ը
	CStatic m_StcEMailSMTPSendEMailStatus;
	CEditOnlyNumber m_EdtEMailSMTPSendEMailLoopTime;
	CEditOnlyNumber m_EdtEMailSMTPSendEMailLoopNum;
	UINT m_UnLoopTime;
	UINT m_UnLoopNum;

public:
	//��ť��״̬�ı�
	//0Ϊ�ʼ�Ⱥ�����ְ��¿�ʼ
	//2Ϊ�ʼ���ը���ְ��¿�ʼ
	//4Ϊ������Ϣ���߳�Ⱥ�����ְ��¿�ʼ
	void MakeButtonStatus( int nStatus );

	UINT SetText( SEMailInfo & EMailInfoSend );

	void StringToStruct(  SEMailInfo & EMail , CString &str );
	CEdit m_EdtEMailPOP3EMailCachePath;
	CStatic m_StcEMailPOP3ReciverEMailStatus;


public://�����ʼ�
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
