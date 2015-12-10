//////////////////////////////////////////////////////////////////////////
//
//	DlgEMail.cpp
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
// DlgEMail.cpp : 实现文件
//

#include "stdafx.h"
#include "HTML.h"
#include "DlgEMail.h"


// CDlgEMail 对话框

IMPLEMENT_DYNAMIC(CDlgEMail, CDialog)

CDlgEMail::CDlgEMail(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEMail::IDD, pParent)
{
	m_BMime = FALSE;
	m_BHTML = FALSE;
	m_StrEncodingFriendly = _T("Chinese Simplified (GB2312)");
	m_StrEncodingCharset = _T("gb2312");
	m_Authenticate_1 = CSMTPConnection::NoLoginMethod;
	m_pHtmlView = NULL;
	m_nListCtrlDrop = -1;
}

CDlgEMail::~CDlgEMail()
{
}

void CDlgEMail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_SMTP_SERVER_ADDRESS, m_EdtEMailSMTPServerAddress);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_SMTP_SERVER_PORT, m_EdtEMailSMTPServerPort);
	DDX_Control(pDX, IDC_COMBO_E_MAIL_SMTP_SERVER_TO_TEST_MODE, m_CbBEMailSMTPServerTestMode);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_SMTP_SENDER_USER_NAME, m_EdtEMailSMTPSenderUserName);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_SMIP_SENDER_USER_PASS_WORD, m_EdtEMailSMTPSenderPassWord);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_SMTP_SENDER_ALL_NAME, m_EdtEMailSMTPSenderAllName);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_SMTP_SENDER_ADDRESS, m_EdtEMailSMTPSenderAddress);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_SMTP_SENDER_LOCAL_ADDRESS, m_EdtEMailSMTPSenderLocalAddress);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_SMTP_SENDER_LOCAL_PORT, m_EdtEMailSMTPSenderLocalPort);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_SMTP_RECVER_ADDRESS, m_EdtEMailSMTPRecverAddress);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_SMTP_RECVER_ADDRESS_CC, m_EdtEMailSMTPRecverAddressCC);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_SMTP_RECVER_ADDRESS_BCC, m_EdtEMailSMTPRecverAddressBCC);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_SMTP_SEND_E_MAIL_TITLE, m_EdtEMailSMTPSendEMailTitle);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_SMTP_SEND_E_MAIL_ANNEX_LIST, m_EdtEMailSMTPSendEMailAnnexList);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_SMTP_SEND_E_MAIL_TEXT, m_EdtEMailSMTPSendEMailText);
	DDX_Control(pDX, IDC_LIST_E_MAIL_SMTP_COMMAND_LIST, m_LclEMailSMTPCommandList);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_SMTP_COMMAND_SAVE_TO_FILE, m_EdtEMailSMTPCommandSaveToFile);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_SMTP_COMMAND_LOAD_FROM_FILE, m_EdtEMailSMTPCommandLoadFromFile);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_SMTP_MASS_E_MAIL_ADDRESS, m_EdtEMailSMTPMassEMailAddress);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_SMTP_MASS_E_MAIL_TIME, m_EdtEMailSMTPMassEMailTime);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_SMTP_COMMAND_THREAD_NUM, m_EdtEMailSMTPCommandThreadNum);
	DDX_Control(pDX, IDC_STATIC_E_MAIL_SMTP_SEND_E_MAIL_STATUS, m_StcEMailSMTPSendEMailStatus);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_SMTP_SEND_E_MAIL_LOOP_TIME, m_EdtEMailSMTPSendEMailLoopTime);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_SMTP_SEND_E_MAIL_LOOP_NUM, m_EdtEMailSMTPSendEMailLoopNum);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_RECEIVER_POP3_SERVER, m_EdtEMailPOP3Server);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_RECEIVER_POP3_PORT, m_EdtEMailPOP3Port);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_RECEIVER_POP3_USER_NAME, m_EdtEMailPOP3UserName);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_RECEIVER_POP3_PASS_WORD, m_EdtEMailPOP3PassWord);
	DDX_Control(pDX, IDC_LIST_E_MAIL_RECEIVER_POP3_E_MAIL_LIST, m_LclEMailPOP3EMailList);
	DDX_Control(pDX, IDC_EDIT_E_MAIL_RECEIVER_POP3_E_MAIL_CACHE, m_EdtEMailPOP3EMailCachePath);
	DDX_Control(pDX, IDC_STATIC_E_MAIL_POP3_RECIVER_E_MAIL_STATUS, m_StcEMailPOP3ReciverEMailStatus);
}


BEGIN_MESSAGE_MAP(CDlgEMail, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_E_MAIL_SMTP_SEND_E_MAIL_ANNEX_LIST_ADD, &CDlgEMail::OnBnClickedButtonEMailSmtpSendEMailAnnexListAdd)
	ON_BN_CLICKED(IDC_BUTTON_E_MAIL_SMTP_SEND_E_MAIL, &CDlgEMail::OnBnClickedButtonEMailSmtpSendEMail)
	ON_BN_CLICKED(IDC_BUTTON_E_MAIL_SMTP_COMMAND_SAVE_TO_FILE, &CDlgEMail::OnBnClickedButtonEMailSmtpCommandSaveToFile)
	ON_BN_CLICKED(IDC_BUTTON_E_MAIL_SMTP_COMMAND_LOAD_FROM_FILE, &CDlgEMail::OnBnClickedButtonEMailSmtpCommandLoadFromFile)
	ON_BN_CLICKED(IDC_BUTTON_E_MAIL_SMTP_COMMAND_MOVE_LEFT, &CDlgEMail::OnBnClickedButtonEMailSmtpCommandMoveLeft)
	ON_BN_CLICKED(IDC_BUTTON_E_MAIL_SMTP_COMMAND_ADD, &CDlgEMail::OnBnClickedButtonEMailSmtpCommandAdd)
	ON_BN_CLICKED(IDC_BUTTON_E_MAIL_SMTP_COMMAND_DELETE, &CDlgEMail::OnBnClickedButtonEMailSmtpCommandDelete)
	ON_BN_CLICKED(IDC_BUTTON_E_MAIL_SMTP_MASS_E_MAIL_SEND, &CDlgEMail::OnBnClickedButtonEMailSmtpMassEMailSend)
	ON_BN_CLICKED(IDC_BUTTON_E_MAIL_SMTP_MASS_E_MAIL_SAVE_TO_FILE, &CDlgEMail::OnBnClickedButtonEMailSmtpMassEMailSaveToFile)
	ON_BN_CLICKED(IDC_BUTTON_E_MAIL_SMTP_MASS_E_MAIL_READ_FROM_FILE, &CDlgEMail::OnBnClickedButtonEMailSmtpMassEMailReadFromFile)
	ON_BN_CLICKED(IDC_BUTTON_E_MAIL_SMTP_COMMAND_THREAD_START, &CDlgEMail::OnBnClickedButtonEMailSmtpCommandThreadStart)
	ON_BN_CLICKED(IDC_BUTTON_E_MAIL_SMTP_COMMAND_THREAD_STOP, &CDlgEMail::OnBnClickedButtonEMailSmtpCommandThreadStop)
	ON_BN_CLICKED(IDC_BUTTON_E_MAIL_SMTP_MASS_E_MAIL_SEND_STOP, &CDlgEMail::OnBnClickedButtonEMailSmtpMassEMailSendStop)
	ON_BN_CLICKED(IDC_BUTTON_E_MAIL_SMTP_SEND_E_MAIL_LOOP_START, &CDlgEMail::OnBnClickedButtonEMailSmtpSendEMailLoopStart)
	ON_BN_CLICKED(IDC_BUTTON_E_MAIL_SMTP_SEND_E_MAIL_LOOP_STOP, &CDlgEMail::OnBnClickedButtonEMailSmtpSendEMailLoopStop)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_E_MAIL_RECEIVER_POP3_E_MAIL_LIST, &CDlgEMail::OnNMDblclkListEMailReceiverPop3EMailList)
	ON_BN_CLICKED(IDC_BUTTON_E_MAIL_RECEIVER_POP3_CONNECT, &CDlgEMail::OnBnClickedButtonEMailReceiverPop3Connect)
	ON_BN_CLICKED(IDC_BUTTON_E_MAIL_RECEIVER_POP3_OPEN, &CDlgEMail::OnBnClickedButtonEMailReceiverPop3Open)
	ON_BN_CLICKED(IDC_BUTTON_E_MAIL_RECEIVER_POP3_RECORD, &CDlgEMail::OnBnClickedButtonEMailReceiverPop3Record)
	ON_BN_CLICKED(IDC_BUTTON_E_MAIL_RECEIVER_POP3_DELETE, &CDlgEMail::OnBnClickedButtonEMailReceiverPop3Delete)
	ON_BN_CLICKED(IDC_BUTTON_E_MAIL_RECEIVER_POP3_QUIT, &CDlgEMail::OnBnClickedButtonEMailReceiverPop3Quit)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(NM_CLICK, IDC_LIST_E_MAIL_RECEIVER_POP3_E_MAIL_LIST, &CDlgEMail::OnNMClickListEMailReceiverPop3EMailList)
END_MESSAGE_MAP()


// CDlgEMail 消息处理程序

void CDlgEMail::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CDlgEMail::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnCancel();
}

BOOL CDlgEMail::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_LclEMailSMTPCommandList.InsertColumn( 0 , _T("ID") , LVCFMT_LEFT , 55 );
	m_LclEMailSMTPCommandList.InsertColumn( 1 , _T("信息") , LVCFMT_LEFT , 98 );
	m_LclEMailSMTPCommandList.SetExtendedStyle( LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT );
	m_LclEMailPOP3EMailList.InsertColumn( 0 , _T("ID") , LVCFMT_LEFT , 55 );
	m_LclEMailPOP3EMailList.InsertColumn( 1 , _T("标题") , LVCFMT_LEFT , 150 );
	m_LclEMailPOP3EMailList.InsertColumn( 2 , _T("大小") , LVCFMT_LEFT , 53 );
	m_LclEMailPOP3EMailList.SetExtendedStyle( LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT );


	m_CbBEMailSMTPServerTestMode.AddString( _T("无验证") );
	m_CbBEMailSMTPServerTestMode.AddString( _T("AUTH LOGIN") );
	m_CbBEMailSMTPServerTestMode.AddString( _T("LOGIN PLAIN") );
	m_CbBEMailSMTPServerTestMode.SelectString( 1 , _T("AUTH LOGIN") );

	m_EdtEMailSMTPServerPort.SetWindowText( _T("25") );

	m_EdtEMailSMTPSenderLocalAddress.SetWindowText( _T("ANY_IP_ADDRESS") );
	m_EdtEMailSMTPSenderLocalPort.SetWindowText( _T("0") );

	m_EdtEMailSMTPCommandThreadNum.SetWindowText( _T("1") );
	m_EdtEMailSMTPMassEMailTime.SetWindowText( _T("3000") );

	m_ThreadMassEMail.m_pDlgEMail = this;
	GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_COMMAND_THREAD_STOP )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_SEND_E_MAIL_LOOP_STOP )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_MASS_E_MAIL_SEND_STOP )->EnableWindow( FALSE );

	m_EdtEMailSMTPSendEMailLoopTime.SetWindowText( _T("3000") );
	m_EdtEMailSMTPSendEMailLoopNum.SetWindowText( _T("1") );
	m_EdtEMailPOP3Port.SetWindowText( _T("110") );
	MakeButtonStatusR( 0 );


#ifndef _DEBUG	//Release版本隐藏
	//GetDlgItem( IDC_BUTTON_E_MAIL_RECEIVER_POP3_CONNECT )->EnableWindow( 0 );
#endif

#ifdef _DEBUG
	m_EdtEMailSMTPServerAddress.SetWindowText( _T("smtp.qq.com") );
	m_EdtEMailSMTPSenderUserName.SetWindowText( _T("304415988") );
	m_EdtEMailSMTPSenderPassWord.SetWindowText( _T("sunjiawang") );
	m_EdtEMailSMTPSenderAllName.SetWindowText( _T("304415988@qq.com") );
	m_EdtEMailSMTPSenderAddress.SetWindowText( _T("304415988@qq.com") );
	m_EdtEMailSMTPRecverAddress.SetWindowText( _T("276793422@qq.com") );
	m_EdtEMailSMTPSendEMailTitle.SetWindowText( _T("半夜了，终于差不多了") );
	m_EdtEMailSMTPSendEMailText.SetWindowText( _T("半夜了，终于差不多了，环境差不多配完了") );
	m_EdtEMailPOP3Server.SetWindowText( _T("pop.qq.com") );
	m_EdtEMailPOP3UserName.SetWindowText( _T("304415988") );
	m_EdtEMailPOP3PassWord.SetWindowText( _T("sunjiawang") );
	m_EdtEMailPOP3EMailCachePath.SetWindowText( _T("E:\\123.html") );
#endif

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgEMail::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	//OnBnClickedButtonEMailReceiverPop3Quit();

	if ( NULL != m_pHtmlView )
	{
		delete m_pHtmlView;
	}
}

void CDlgEMail::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	if ( NULL != m_pHtmlView )
	{
		if ( 0 == bShow )
		{
			m_pHtmlView->ShowWindow( SW_HIDE );
		}
		if ( 1 == bShow )
		{
			RECT prect;
			prect.top		= 280 ;
			prect.bottom	= 545 ;
			prect.left		= 714 ;
			prect.right		= 993 ;
			m_pHtmlView->MoveWindow( &prect );
			m_pHtmlView->ShowWindow( SW_SHOW );
		}
		return;
	}
	if ( 1 == bShow )
	{
		if ( NULL == m_pHtmlView )
		{
			m_pHtmlView = new CHtmlViewMail;
			CRect rect;
			rect.top		= 280 ;
			rect.bottom		= 545 ;
			rect.left		= 714 ;
			rect.right		= 993 ;
			m_pHtmlView->Create( 0 , 0 ,
									WS_VISIBLE | WS_CHILD , 
									rect , 
									this , 
									AFX_IDW_PANE_FIRST );
			m_pHtmlView->MoveWindow( &rect );
			m_pHtmlView->ShowWindow( SW_SHOW );
		}
	}
}

//获取各种信息以及报错提示
UINT CDlgEMail::TestEdit( SEMailInfo & EMailInfoSend )
{
	//////////////////////////////////////////////////////////////////////////
	//	服务器信息设置
	m_EdtEMailSMTPServerAddress.GetWindowText( EMailInfoSend.m_ServerAddress );
	WRONG_MSG_RTN( ( EMailInfoSend.m_ServerAddress.IsEmpty() ) , _T("咱是不是要把服务器地址写上") );

	m_EdtEMailSMTPServerPort.GetWindowText( EMailInfoSend.m_ServerPort );
	WRONG_MSG_RTN( ( EMailInfoSend.m_ServerPort.IsEmpty() ) , _T("咱是不是要把服务端口写上") );

	m_CbBEMailSMTPServerTestMode.GetWindowText( EMailInfoSend.m_LoginTest );

	//////////////////////////////////////////////////////////////////////////
	//	发件人信息配置
	m_EdtEMailSMTPSenderUserName.GetWindowText( EMailInfoSend.m_UID );
	WRONG_MSG_RTN( ( EMailInfoSend.m_UID.IsEmpty() ) , _T("咱是不是要把用户名写上") );

	m_EdtEMailSMTPSenderPassWord.GetWindowText( EMailInfoSend.m_PWD );
	WRONG_MSG_RTN( ( EMailInfoSend.m_PWD.IsEmpty() ) , _T("咱是不是要把密码写上") );

	m_EdtEMailSMTPSenderAllName.GetWindowText( EMailInfoSend.m_Name );
	WRONG_MSG_RTN( ( EMailInfoSend.m_Name.IsEmpty() ) , _T("发件人全名要写一下") );

	m_EdtEMailSMTPSenderAddress.GetWindowText( EMailInfoSend.m_Address );
	WRONG_MSG_RTN( ( EMailInfoSend.m_Address != EMailInfoSend.m_Name ) , _T("发件人地址和全名要完全一样") );

	m_EdtEMailSMTPSenderLocalAddress.GetWindowText( EMailInfoSend.m_LocalIP );
	EMailInfoSend.m_LocalIP=_T("");

	m_EdtEMailSMTPSenderLocalPort.GetWindowText( EMailInfoSend.m_LocalPort );

	//////////////////////////////////////////////////////////////////////////
	//	收件人信息配置
	m_EdtEMailSMTPRecverAddress.GetWindowText( EMailInfoSend.m_Receiver );
	WRONG_MSG_RTN( ( EMailInfoSend.m_Receiver.IsEmpty() ) , _T("收件人都不写？") );

	m_EdtEMailSMTPRecverAddressCC.GetWindowText( EMailInfoSend.m_CC );

	m_EdtEMailSMTPRecverAddressBCC.GetWindowText( EMailInfoSend.m_BCC );

	//////////////////////////////////////////////////////////////////////////
	//	邮件信息
	m_EdtEMailSMTPSendEMailTitle.GetWindowText( EMailInfoSend.m_Title );

	m_EdtEMailSMTPSendEMailAnnexList.GetWindowText( EMailInfoSend.m_Attachment );

	m_EdtEMailSMTPSendEMailText.GetWindowText( EMailInfoSend.m_Text );

	return 0;
}

UINT CDlgEMail::SetText( SEMailInfo & EMailInfoSend )
{
	//////////////////////////////////////////////////////////////////////////
	//	服务器信息设置
	m_EdtEMailSMTPServerAddress.SetWindowText( EMailInfoSend.m_ServerAddress );

	m_EdtEMailSMTPServerPort.SetWindowText( EMailInfoSend.m_ServerPort );

	m_CbBEMailSMTPServerTestMode.SelectString( 0 , EMailInfoSend.m_LoginTest );

	//////////////////////////////////////////////////////////////////////////
	//	发件人信息配置
	m_EdtEMailSMTPSenderUserName.SetWindowText( EMailInfoSend.m_UID );

	m_EdtEMailSMTPSenderPassWord.SetWindowText( EMailInfoSend.m_PWD );

	m_EdtEMailSMTPSenderAllName.SetWindowText( EMailInfoSend.m_Name );

	m_EdtEMailSMTPSenderAddress.SetWindowText( EMailInfoSend.m_Address );

	m_EdtEMailSMTPSenderLocalAddress.SetWindowText( _T("ANY_IP_ADDRESS")/*EMailInfoSend.m_LocalIP*/ );

	m_EdtEMailSMTPSenderLocalPort.SetWindowText( EMailInfoSend.m_LocalPort );

	//////////////////////////////////////////////////////////////////////////
	//	收件人信息配置
	m_EdtEMailSMTPRecverAddress.SetWindowText( EMailInfoSend.m_Receiver );

	m_EdtEMailSMTPRecverAddressCC.SetWindowText( EMailInfoSend.m_CC );

	m_EdtEMailSMTPRecverAddressBCC.SetWindowText( EMailInfoSend.m_BCC );

	//////////////////////////////////////////////////////////////////////////
	//	邮件信息
	m_EdtEMailSMTPSendEMailTitle.SetWindowText( EMailInfoSend.m_Title );

	m_EdtEMailSMTPSendEMailAnnexList.SetWindowText( EMailInfoSend.m_Attachment );

	m_EdtEMailSMTPSendEMailText.SetWindowText( EMailInfoSend.m_Text );

	return 0;
}

void CDlgEMail::StringToStruct( SEMailInfo & EMail , CString &str )
{
	str.TrimLeft(_T("|"));
	int i = 0;
	CString *strMsg = (CString *)&EMail;
	i = 0;
	int j = 0;
	while ( 1 )
	{
		i = str.Find( _T("|") );
		if ( -1 == i )
		{
			break;
		}
		strMsg[j] = str.Left( i );
		j++;
		str.Delete( 0 , i + 1 );
	}
	strMsg[j] = str;
}

//开始发信
void CDlgEMail::SendEMail( SEMailInfo & EMailInfoSend )
{

	CWaitCursor wc;
	if ( _T("AUTH LOGIN") == EMailInfoSend.m_LoginTest )
	{
		m_Authenticate = (CSMTPConnection::LoginMethod)2;
	}
	if ( _T("LOGIN PLAIN") == EMailInfoSend.m_LoginTest )
	{
		m_Authenticate = (CSMTPConnection::LoginMethod)3;
	}
	if ( _T("无验证") == EMailInfoSend.m_LoginTest )
	{
		m_Authenticate = (CSMTPConnection::LoginMethod)0;
	}

	//创建SMTP信息体，通过类来实现
	CSMTPMessage* pMessage = CreateMessage( EMailInfoSend );
	//连接到服务器
	CSMTPConnection connection;

	if ( _T("AUTH LOGIN") == EMailInfoSend.m_LoginTest )
	{
		m_Authenticate = (CSMTPConnection::LoginMethod)2;
	}
	if ( _T("LOGIN PLAIN") == EMailInfoSend.m_LoginTest )
	{
		m_Authenticate = (CSMTPConnection::LoginMethod)3;
	}
	if ( _T("无验证") == EMailInfoSend.m_LoginTest )
	{
		m_Authenticate = (CSMTPConnection::LoginMethod)0;
	}

	BOOL bConnect = connection.Connect( EMailInfoSend.m_ServerAddress ,
										m_Authenticate ,
										EMailInfoSend.m_UID ,
										EMailInfoSend.m_PWD ,
										stol( EMailInfoSend.m_ServerPort , 0 , 10 ) ,
										m_EMailInforSend.m_LocalIP );
	//判断连接是否成功
	if (!bConnect) 
	{
		AfxMessageBox( _T("不能连接到服务器!") );
	}
	else 
	{
		//发送具体信息
		if (!connection.SendMessage(*pMessage)) 
		{
			AfxMessageBox( _T("发送信息失败!") );
		}
	}
	//删除消息体
	delete pMessage;

}

//创建信息主体
CSMTPMessage* CDlgEMail::CreateMessage( SEMailInfo & EMailInfoSend )
{
	//创建信息体
	CSMTPMessage* pMessage = new CSMTPMessage;
	CSMTPBodyPart attachment;

	//设定mine标志mime
	pMessage->SetMime( m_BMime );

	//设定信息和附件的编码方式
	pMessage->SetCharset(m_StrEncodingCharset);
	attachment.SetCharset(m_StrEncodingCharset);

	//获得各种基本信息
	pMessage->AddMultipleRecipients( EMailInfoSend.m_Receiver , CSMTPMessage::TO);
	if ( !EMailInfoSend.m_CC.IsEmpty() )
	{
		pMessage->AddMultipleRecipients( EMailInfoSend.m_CC , CSMTPMessage::CC );
	}
	if ( !EMailInfoSend.m_BCC.IsEmpty() )
	{
		pMessage->AddMultipleRecipients( EMailInfoSend.m_BCC , CSMTPMessage::BCC );
	}
	if ( !EMailInfoSend.m_Title.IsEmpty() )
	{
		pMessage->m_sSubject = EMailInfoSend.m_Title;
	}

	if ( !EMailInfoSend.m_Text.IsEmpty() )
	{
		//表示是否以HTML的格式发送邮件
		if (m_BHTML)
		{
			pMessage->AddHTMLBody( EMailInfoSend.m_Text , _T("") );
		}
		else
		{
			pMessage->AddTextBody( EMailInfoSend.m_Text );
		}
	}

	//增加附件，如果要发送附件
	if ( !EMailInfoSend.m_Attachment.IsEmpty() )
	{
		pMessage->AddMultipleAttachments( EMailInfoSend.m_Attachment );
	}

	//设定发送者地址
	if ( EMailInfoSend.m_Name.IsEmpty() ) 
	{
		pMessage->m_From = EMailInfoSend.m_Address;
		pMessage->m_ReplyTo = EMailInfoSend.m_Address;
	}
	else 
	{
		CSMTPAddress address( EMailInfoSend.m_Name , EMailInfoSend.m_Address );
		pMessage->m_From = address;
		pMessage->m_ReplyTo = address;
	}

	m_Authenticate=(CSMTPConnection::LoginMethod) m_Authenticate_1;

	//增加一个自定义头，测试用
//#ifdef _DEBUG
//	pMessage->AddCustomHeader(_T("X-Program: CSTMPMessageTester"));
//#endif

	return pMessage;
}

//0为邮件群发部分按下开始
//2为邮件轰炸部分按下开始
//4为发件信息多线程群发部分按下开始
void CDlgEMail::MakeButtonStatus( int nStatus )
{
	if ( 0 == nStatus )
	{
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_MASS_E_MAIL_SEND )->EnableWindow( 0 );
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_MASS_E_MAIL_SEND_STOP )->EnableWindow( 1 );
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_COMMAND_THREAD_START )->EnableWindow( 0 );
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_COMMAND_THREAD_STOP )->EnableWindow( 0 );
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_SEND_E_MAIL_LOOP_START )->EnableWindow( 0 );
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_SEND_E_MAIL_LOOP_STOP )->EnableWindow( 0 );
	}
	if ( 2 == nStatus )
	{
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_MASS_E_MAIL_SEND )->EnableWindow( 0 );
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_MASS_E_MAIL_SEND_STOP )->EnableWindow( 0 );
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_SEND_E_MAIL_LOOP_START )->EnableWindow( 0 );
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_SEND_E_MAIL_LOOP_STOP )->EnableWindow( 1 );
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_COMMAND_THREAD_START )->EnableWindow( 0 );
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_COMMAND_THREAD_STOP )->EnableWindow( 0 );
	}
	if ( 4 == nStatus )
	{
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_MASS_E_MAIL_SEND )->EnableWindow( 0 );
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_MASS_E_MAIL_SEND_STOP )->EnableWindow( 0 );
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_SEND_E_MAIL_LOOP_START )->EnableWindow( 0 );
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_SEND_E_MAIL_LOOP_STOP )->EnableWindow( 0 );
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_COMMAND_THREAD_START )->EnableWindow( 0 );
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_COMMAND_THREAD_STOP )->EnableWindow( 1 );
	}
	if ( 1 == ( nStatus&1 ) )
	{
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_MASS_E_MAIL_SEND )->EnableWindow( 1 );
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_MASS_E_MAIL_SEND_STOP )->EnableWindow( 0 );
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_COMMAND_THREAD_START )->EnableWindow( 1 );
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_COMMAND_THREAD_STOP )->EnableWindow( 0 );
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_SEND_E_MAIL_LOOP_START )->EnableWindow( 1 );
		GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_SEND_E_MAIL_LOOP_STOP )->EnableWindow( 0 );
	}


	GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_SEND_E_MAIL_ANNEX_LIST_ADD )->EnableWindow( nStatus&1 );
	GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_SEND_E_MAIL )->EnableWindow( nStatus&1 );
	GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_COMMAND_SAVE_TO_FILE )->EnableWindow( nStatus&1 );
	GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_COMMAND_LOAD_FROM_FILE )->EnableWindow( nStatus&1 );
	GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_COMMAND_MOVE_LEFT )->EnableWindow( nStatus&1 );
	GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_COMMAND_ADD )->EnableWindow( nStatus&1 );
	GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_COMMAND_DELETE )->EnableWindow( nStatus&1 );
	GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_MASS_E_MAIL_SAVE_TO_FILE )->EnableWindow( nStatus&1 );
	GetDlgItem( IDC_BUTTON_E_MAIL_SMTP_MASS_E_MAIL_READ_FROM_FILE )->EnableWindow( nStatus&1 );

}

void CDlgEMail::OnBnClickedButtonEMailSmtpSendEMailAnnexListAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog f ( TRUE , NULL , 
		_T("打开文件") , 512 , 
		_T("所有文件(*.*)|*.*||") );
	if( f.DoModal() != IDOK )
	{
		return ;
	}

	int type1 = 0;
	CString str = _T("");
	POSITION pos = f.GetStartPosition();
	int i=0;
	while(pos)
	{
		//读取文件到曲目路径列表
		str = str + f.GetNextPathName( pos ) + _T(", ");
	}
	str.Delete( str.GetLength() - 2 , 2 );

	m_EdtEMailSMTPSendEMailAnnexList.SetWindowText( str );
}

void CDlgEMail::OnBnClickedButtonEMailSmtpSendEMail()
{
	// TODO: 在此添加控件通知处理程序代码
	//////////////////////////////////////////////////////////////////////////
	//	获取全部信息
	if ( TestEdit( m_EMailInforSend ) )
	{
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	//	发送邮件
	m_ThreadMassEMail.StartOnce();
}

void CDlgEMail::OnBnClickedButtonEMailSmtpCommandMoveLeft()
{
	// TODO: 在此添加控件通知处理程序代码
	int i = 0;
	for ( i = 0 ; i < m_LclEMailSMTPCommandList.GetItemCount() ; i++ )
	{
		if ( m_LclEMailSMTPCommandList.GetCheck( i ) )
		{
			break;
		}
	}
	if ( i == m_LclEMailSMTPCommandList.GetItemCount() )
	{
		MessageBox( _T("至少要选一个") , _T("重新来") );
		return ;
	}

	SEMailInfo EMail;
	StringToStruct( EMail , m_LclEMailSMTPCommandList.GetItemText( i , 1 ) );

	SetText( EMail );
}

void CDlgEMail::OnBnClickedButtonEMailSmtpCommandAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	SEMailInfo EMail;
	if ( TestEdit( EMail ) )
	{
		return ;
	}
	CString str ;
	int i = 0;
	int j = 0;
	i = m_LclEMailSMTPCommandList.GetItemCount();
	str.Format( _T("%d") , i );
	m_LclEMailSMTPCommandList.InsertItem( i , str );
	j = i;

	CString *strMsg;
	strMsg = (CString *)&EMail;
	str = _T("");
	for ( i = 0 ; i < 15 ; i++ )
	{
		str = str + _T("|") + strMsg[i];
	}
	i = m_LclEMailSMTPCommandList.GetItemCount();
	m_LclEMailSMTPCommandList.SetItemText( j , 1 , str );
}

void CDlgEMail::OnBnClickedButtonEMailSmtpCommandDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	int i = 0;
	for ( i = m_LclEMailSMTPCommandList.GetItemCount() - 1 ; i >= 0 ; i-- )
	{
		if ( m_LclEMailSMTPCommandList.GetCheck( i ) )
		{
			m_LclEMailSMTPCommandList.DeleteItem( i );
		}
	}
	CString str;
	for ( i = 0 ; i < m_LclEMailSMTPCommandList.GetItemCount() ; i++ )
	{
		str.Format( _T("%d") , i );
		m_LclEMailSMTPCommandList.SetItemText( i , 0 , str );
	}
}

void CDlgEMail::OnBnClickedButtonEMailSmtpCommandSaveToFile()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDlgEMail::OnBnClickedButtonEMailSmtpCommandLoadFromFile()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDlgEMail::OnBnClickedButtonEMailSmtpCommandThreadStart()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( IDCANCEL == MessageBox( _T("按照上表多线程群发\r\n这里只能实现最基础的多线程群发\r\n如果想要更多功能，去控制台\r\n默认发信延迟0.5秒") , _T("注意") , MB_OKCANCEL ) )
	{
		return ;
	}
	CString str;
	m_EdtEMailSMTPCommandThreadNum.GetWindowText( str );
	m_nThreadNum = stol( str , 0 , 10 );
	MakeButtonStatus( 4 );
	m_ThreadMassEMail.StartThread();
}

void CDlgEMail::OnBnClickedButtonEMailSmtpCommandThreadStop()
{
	// TODO: 在此添加控件通知处理程序代码
	MakeButtonStatus( 1 );
	m_ThreadMassEMail.StopThread();
}

void CDlgEMail::OnBnClickedButtonEMailSmtpMassEMailSend()
{
	// TODO: 在此添加控件通知处理程序代码

	if ( IDCANCEL == MessageBox( _T("邮件群发会按照左侧的配置及信息\r\n发送至框内的地址") , _T("注意") , MB_OKCANCEL ) )
	{
		return ;
	}
	if ( TestEdit( m_EMailInforSendInTimer ) )
	{
		return ;
	}
	CString str;
	m_EdtEMailSMTPMassEMailTime.GetWindowText( str );
	m_UnTime = stol( str , 0 , 10 );
	m_EdtEMailSMTPMassEMailAddress.GetWindowText( m_StrMassEMail );
	int i = -1;
	while( 1 )
	{
		i = m_StrMassEMail.Find( _T('\r') );
		if ( -1 == i )
		{
			break;
		}
		m_StrMassEMail.Delete( i );
	}
	m_StrMassEMail.TrimRight( _T('\n') );
	if ( m_StrMassEMail.Right( 1 ) != _T("\n") )
	{
		m_StrMassEMail = m_StrMassEMail + _T("\n");
	}
	MakeButtonStatus( 0 );
	m_ThreadMassEMail.StartTime();
}

void CDlgEMail::OnBnClickedButtonEMailSmtpMassEMailSendStop()
{
	// TODO: 在此添加控件通知处理程序代码

	m_ThreadMassEMail.StopTime();
	MakeButtonStatus( 1 );
}

void CDlgEMail::OnBnClickedButtonEMailSmtpMassEMailSaveToFile()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDlgEMail::OnBnClickedButtonEMailSmtpMassEMailReadFromFile()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDlgEMail::OnBnClickedButtonEMailSmtpSendEMailLoopStart()
{
	// TODO: 在此添加控件通知处理程序代码

	if ( IDCANCEL == MessageBox( _T("邮箱轰炸会按照当前配置轰炸单个邮箱\r\n邮箱群轰炸需至控制台中使用") , _T("注意") , MB_OKCANCEL ) )
	{
		return ;
	}
	if ( TestEdit( m_EMailInforSend ) )
	{
		return;
	}
	CString str;
	m_EdtEMailSMTPSendEMailLoopTime.GetWindowText( str );
	m_UnLoopTime = stol( str , 0 , 10 );
	m_EdtEMailSMTPSendEMailLoopNum.GetWindowText( str );
	m_UnLoopNum = stol( str , 0 , 10 );

	MakeButtonStatus( 2 );

	m_ThreadMassEMail.StartLoop();
}

void CDlgEMail::OnBnClickedButtonEMailSmtpSendEMailLoopStop()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ThreadMassEMail.StopLoop();
	MakeButtonStatus( 1 );
}

void CDlgEMail::OnNMDblclkListEMailReceiverPop3EMailList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int i = pNMItemActivate->iItem + 1;
	if ( 0 == i )
	{
		return ;
	}

	m_pThreadRecvEMail.OpenEMail( i );

	*pResult = 0;
}

void CDlgEMail::OnNMClickListEMailReceiverPop3EMailList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nListCtrlDrop = pNMItemActivate->iItem;

	*pResult = 0;
}

void CDlgEMail::OnBnClickedButtonEMailReceiverPop3Connect()
{
	// TODO: 在此添加控件通知处理程序代码

	if ( IDNO == MessageBox( _T("是否确定使用接收邮件功能") , _T("功能并不完善") , MB_YESNO ) )
	{
		return;
	}

	int Ret = 0;
	CString str;
	CStringA strA;
	m_EdtEMailPOP3Server.GetWindowText( str );
	strA = str;
	Ret = m_Pop3.StartWork( POP_SET_SERVER , &strA );
	if ( Ret )	{	return ;	}
	m_EdtEMailPOP3Port.GetWindowText( str );
	strA = str;
	Ret = m_Pop3.StartWork( POP_SET_PORT , &strA );
	if ( Ret )	{	return ;	}
	m_EdtEMailPOP3UserName.GetWindowText( str );
	strA = str;
	Ret = m_Pop3.StartWork( POP_SET_USER_NAME , &strA );
	if ( Ret )	{	return ;	}
	m_EdtEMailPOP3PassWord.GetWindowText( str );
	strA = str;
	Ret = m_Pop3.StartWork( POP_SET_PASS_WORD , &strA );
	if ( Ret )	{	return ;	}

	m_pThreadRecvEMail.Create( this );

	m_pThreadRecvEMail.StartNOOP();

}

void CDlgEMail::OnBnClickedButtonEMailReceiverPop3Open()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( -1 == m_nListCtrlDrop )
	{
		return ;
	}

	m_pThreadRecvEMail.OpenEMail( ( m_nListCtrlDrop + 1 ) );
}

void CDlgEMail::OnBnClickedButtonEMailReceiverPop3Record()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pThreadRecvEMail.RecvEMail();
}

void CDlgEMail::OnBnClickedButtonEMailReceiverPop3Delete()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDlgEMail::OnBnClickedButtonEMailReceiverPop3Quit()
{
	// TODO: 在此添加控件通知处理程序代码
	m_LclEMailPOP3EMailList.DeleteAllItems();
	m_pHtmlView->Navigate2( _T("about:blank") );

	m_pThreadRecvEMail.Stop();
}

void CDlgEMail::MakeButtonStatusR( int nStatus )
{
	GetDlgItem( IDC_BUTTON_E_MAIL_RECEIVER_POP3_CONNECT )->EnableWindow( !nStatus );
	GetDlgItem( IDC_BUTTON_E_MAIL_RECEIVER_POP3_DELETE )->EnableWindow( nStatus );
	GetDlgItem( IDC_BUTTON_E_MAIL_RECEIVER_POP3_OPEN )->EnableWindow( nStatus );
	GetDlgItem( IDC_BUTTON_E_MAIL_RECEIVER_POP3_QUIT )->EnableWindow( nStatus );
	GetDlgItem( IDC_BUTTON_E_MAIL_RECEIVER_POP3_RECORD )->EnableWindow( nStatus );
}