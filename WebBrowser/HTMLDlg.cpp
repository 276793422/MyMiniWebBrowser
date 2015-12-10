//////////////////////////////////////////////////////////////////////////
//
//	HTMLDlg.cpp
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
// HTMLDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HTML.h"
#include "HTMLDlg.h"
#include <Windows.h>
#include <process.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CHTMLDlg �Ի���




CHTMLDlg::CHTMLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHTMLDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_HtmlView = new CHtmlViewMy;
	m_SW_SHOW_HIDE = 1;
}

void CHTMLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrlAll);
	DDX_Control(pDX, IDC_EDIT_URL_ON_PARENT, m_EdtURL);
	DDX_Control(pDX, IDC_EDIT_HTML_VIEW_STATUS_TEXT_CHANGE, m_EdtHtmlViewStatusTextOut);
	DDX_Control(pDX, IDC_PROGRESS_THE_HTML_VIEW_PROCESS, m_PrcTheHtmlViewOpenProcess);
	DDX_Control(pDX, IDC_EDIT_HTML_VIEW_COOKIES_TEXT, m_EdtHtmlViewCookies);
}

BEGIN_MESSAGE_MAP(CHTMLDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CHTMLDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_THE_URL, &CHTMLDlg::OnBnClickedButtonOpenTheUrl)
	ON_BN_CLICKED(IDC_BUTTON_FILL_THE_FORM, &CHTMLDlg::OnBnClickedButtonFillTheForm)
	ON_BN_CLICKED(IDC_BUTTON_THE_HOME_PAGE, &CHTMLDlg::OnBnClickedButtonTheHomePage)
	ON_BN_CLICKED(IDC_BUTTON_GO_FORWARD, &CHTMLDlg::OnBnClickedButtonGoForward)
	ON_BN_CLICKED(IDC_BUTTON_GO_BACK, &CHTMLDlg::OnBnClickedButtonGoBack)
	ON_BN_CLICKED(IDC_BUTTON_START_RECORD_VIEW, &CHTMLDlg::OnBnClickedButtonStartRecordView)
	ON_BN_CLICKED(IDC_BUTTON_STOP_RECORD_VIEW, &CHTMLDlg::OnBnClickedButtonStopRecordView)
	ON_BN_CLICKED(IDC_BUTTON_HTML_VIEW_GET_COOKIES, &CHTMLDlg::OnBnClickedButtonHtmlViewGetCookies)
END_MESSAGE_MAP()


// CHTMLDlg ��Ϣ�������

BOOL CHTMLDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//��������ͼ��
	m_NotifyMini.Create( _T("���������") , this , IDR_MAINFRAME );
	m_NotifyMini.AddMenu( IDR_MENU_SYSTEM_MENU_ONE );

	
	GetWindowRect( &m_RetItem );
	m_RetItem.top += 22;
	m_RetItem.bottom -= 103;
	m_RetItem.left += 1;
	m_RetItem.right -= 11;

	m_TabCtrlAll.InsertItem( 0 , _T("��ҳ����") );
	m_TabCtrlAll.InsertItem( 1 , _T("�Զ�����") );
	m_TabCtrlAll.InsertItem( 2 , _T("������Ϣ") );
	m_TabCtrlAll.InsertItem( 3 , _T("������Ϣ") );
	m_TabCtrlAll.InsertItem( 4 , _T("�����ʼ�") );
	m_TabCtrlAll.InsertItem( 5 , _T("����ץ��") );

	m_HtmlView->Create( 0 , 0 , 
						WS_VISIBLE | WS_CHILD , 
						m_RetItem , 
						&m_TabCtrlAll /*this*/ , 
						AFX_IDW_PANE_FIRST );
	m_HtmlView->m_pParent = this;

	m_DlgList.Create( IDD_OLE_PROPPAGE_SMALL , &m_TabCtrlAll /*this*/ );
	m_DlgList.m_pParent = this;

	m_DlgProxy.Create( IDD_OLE_PROPPAGE_SMALL_PROXY , &m_TabCtrlAll );
	m_DlgProxy.m_pParent = this;

	m_DlgCLI.Create( IDD_OLE_PROPPAGE_SMALL_COMMAND_LIST_INFOMATION , &m_TabCtrlAll );
	m_DlgCLI.m_pParent = this;

	m_DlgEmail.Create( IDD_OLE_PROPPAGE_SMALL_E_MAIL_PAGE , &m_TabCtrlAll );
	m_DlgEmail.m_pParent = this;

	m_DlgHookBaseMessage.Create( IDD_OLE_PROPPAGE_SMALL_HOOK_BASE_MESSAGE , &m_TabCtrlAll );
	m_DlgHookBaseMessage.m_pParent = this;



	//�޸���ַ��URL��TIMER
	//SetTimer( 10001 , 110 , 0 );
	m_EdtURL.SetWindowText( _T("about:blank") );
	m_StrURL = _T("about:blank");
	m_HtmlView->Navigate2( _T("about:blank") );
	GetDlgItem( IDC_BUTTON_STOP_RECORD_VIEW )->EnableWindow( FALSE );

	m_PrcTheHtmlViewOpenProcess.SetRange( 0 , 100 );

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CHTMLDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHTMLDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHTMLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CHTMLDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	if ( NULL != m_HtmlView )
	{
		delete m_HtmlView;
	}
}

void CHTMLDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch( nIDEvent )
	{
	//case 10001:
	//	//if ( m_StrURL == _T("about:blank") )
	//	//{
	//	//	break;
	//	//}
	//	if ( m_StrURL != m_HtmlView->GetLocationURL() )
	//	{
	//		m_StrURL = m_HtmlView->GetLocationURL();

	//		m_EdtURL.SetWindowText( m_StrURL );
	//	}
	//	break;
	case 10002:
		m_HtmlView->Navigate2( m_StrRecordURL );
		break;
	}

	CDialog::OnTimer(nIDEvent);
}

//�������������
int CHTMLDlg::SetMyIeProxy( CString str )
{
	m_StrProxy = str;
	m_StrProxyByPass = "<local>";

	ipi.dwAccessType = INTERNET_OPEN_TYPE_PROXY ;
	ipi.lpszProxy = m_StrProxy;
	ipi.lpszProxyBypass = m_StrProxyByPass;
	return InternetSetOptionA( NULL ,
								INTERNET_OPTION_PROXY ,
								&ipi ,
								sizeof(ipi) );
}

//������������
int CHTMLDlg::DelMyIeProxy()
{
	ipi.dwAccessType = INTERNET_OPEN_TYPE_DIRECT ;

	return InternetSetOptionA( NULL ,
								INTERNET_OPTION_PROXY ,
								&ipi ,
								sizeof(ipi) );
}

void CHTMLDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int i = m_TabCtrlAll.GetCurSel();
	if ( m_DlgList.m_nCommandWorkStatus )
	{
		if ( i > 1 )
		{
			return;
		}
		if ( i < 0 )
		{
			return;
		}
	}
	*pResult = 0;

	m_HtmlView->ShowWindow( SW_HIDE );
	m_DlgList.ShowWindow( SW_HIDE );
	m_DlgProxy.ShowWindow( SW_HIDE );
	m_DlgCLI.ShowWindow( SW_HIDE );
	m_DlgEmail.ShowWindow( SW_HIDE );
	m_DlgHookBaseMessage.ShowWindow( SW_HIDE );

	switch( i )
	{
	case -1:
		return ;
	case 0:
		m_HtmlView->MoveWindow( &m_RetItem );
		m_HtmlView->ShowWindow( SW_SHOW );
		break;
	case 1:
		m_DlgList.MoveWindow( &m_RetItem );
		m_DlgList.ShowWindow( SW_SHOW );
		break;
	case 2:
		m_DlgProxy.MoveWindow( &m_RetItem );
		m_DlgProxy.ShowWindow( SW_SHOW );
		break;
	case 3:
		m_DlgCLI.MoveWindow( &m_RetItem );
		m_DlgCLI.ShowWindow( SW_SHOW );
		break;
	case 4:
		m_DlgEmail.MoveWindow( &m_RetItem );
		m_DlgEmail.ShowWindow( SW_SHOW );
		break;
	case 5:
		m_DlgHookBaseMessage.MoveWindow( &m_RetItem );
		m_DlgHookBaseMessage.ShowWindow( SW_SHOW );
		break;
	}
}


void CHTMLDlg::OnBnClickedButtonOpenTheUrl()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString str;

	m_EdtURL.GetWindowText( str );

	m_HtmlView->Navigate2( str );
	if ( _T("http://") != str.Left(7) )
	{
		str = _T("http://") + str;
	}
	if ( _T("/") != str.Right(1) )
	{
		str += _T("/");
	}
	m_EdtURL.SetWindowText( str );
	int i = m_DlgList.m_LclOpenedPageUrl.GetItemCount();
	CString str2;
	str2.Format( _T("%d") , i );
	m_DlgList.m_LclOpenedPageUrl.InsertItem( i , str2 );
	m_DlgList.m_LclOpenedPageUrl.SetItemText( i , 1 , str );
}

void CHTMLDlg::OnBnClickedButtonFillTheForm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if ( m_DlgList.m_LBX[0].GetCount() < 1 )
	{
		return;
	}
	m_HtmlView->FillTheList();
}

void CHTMLDlg::OnBnClickedButtonTheHomePage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_StrURL = THEHOMEPAGEDEFINE;
	m_HtmlView->Navigate2( THEHOMEPAGEDEFINE );
}

void CHTMLDlg::OnBnClickedButtonGoForward()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_HtmlView->GoForward();
}

void CHTMLDlg::OnBnClickedButtonGoBack()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_HtmlView->GoBack();

}

void CHTMLDlg::OnBnClickedButtonStartRecordView()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_DlgList.m_EdtRecordTime.GetWindowText( m_StrRecordURL );
	if ( m_StrRecordURL.IsEmpty() )
	{
		MessageBox( _T("��Ҫ�ڹ���ҳ������ˢ��ʱ��") , _T("") );
		return;
	}

	int i = stol( m_StrRecordURL.GetBuffer() , 0 , 10 );

	m_DlgList.m_EdtRecordURL.GetWindowText( m_StrRecordURL );
	if ( m_StrRecordURL.IsEmpty() )
	{
		MessageBox( _T("��Ҫ�ڹ���ҳ������ˢ�µ�ַ") , _T("") );
		return;
	}
	SetTimer( 10002 , i , 0 );
	GetDlgItem( IDC_BUTTON_START_RECORD_VIEW )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_STOP_RECORD_VIEW )->EnableWindow( TRUE );
}

void CHTMLDlg::OnBnClickedButtonStopRecordView()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer( 10002 );
	GetDlgItem( IDC_BUTTON_START_RECORD_VIEW )->EnableWindow( TRUE );
	GetDlgItem( IDC_BUTTON_STOP_RECORD_VIEW )->EnableWindow( FALSE );
}

void CHTMLDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	if ( m_SW_SHOW_HIDE )
	{
		ShowWindow( SW_HIDE );
		m_SW_SHOW_HIDE = 0;
	}
	else
	{
		ShowWindow( SW_SHOW );
		m_SW_SHOW_HIDE = 1;
	}

	//CDialog::OnCancel();
}

void CHTMLDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnOK();
}


BOOL CHTMLDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(!wParam)
	{
		if(lParam == WM_RBUTTONDOWN)
		{
			m_NotifyMini.MakeOutMenu(this);
		}
		if(lParam == WM_LBUTTONDBLCLK)
		{
			OnCancel();
		}
	}

	return CDialog::OnCommand(wParam, lParam);
}

void CHTMLDlg::SetDialogEnableWindow( int i )
{
	GetDlgItem( IDC_BUTTON_FILL_THE_FORM )->EnableWindow( i );
	GetDlgItem( IDC_BUTTON_OPEN_THE_URL )->EnableWindow( i );
	GetDlgItem( IDC_BUTTON_THE_HOME_PAGE )->EnableWindow( i );
	GetDlgItem( IDC_BUTTON_GO_FORWARD )->EnableWindow( i );
	GetDlgItem( IDC_BUTTON_GO_BACK )->EnableWindow( i );

	GetDlgItem( IDC_BUTTON_START_RECORD_VIEW )->EnableWindow( i );
	GetDlgItem( IDC_BUTTON_HTML_VIEW_GET_COOKIES )->EnableWindow( i );

	if ( 0 == i )
	{
		GetDlgItem( IDC_BUTTON_STOP_RECORD_VIEW )->EnableWindow( i );
	}
}

//��ȡCookies
int CHTMLDlg::GetCookiesOnTheHtml( CString &str )
{
	CString URL;
	m_EdtURL.GetWindowText( URL );
	m_Cookies.GetCookies( URL , str );

	return 0;
}
void CHTMLDlg::OnBnClickedButtonHtmlViewGetCookies()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString cookies;
	GetCookiesOnTheHtml( cookies );
	m_EdtHtmlViewCookies.SetWindowText( cookies );
}
