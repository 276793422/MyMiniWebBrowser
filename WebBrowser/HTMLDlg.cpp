//////////////////////////////////////////////////////////////////////////
//
//	HTMLDlg.cpp
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
// HTMLDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HTML.h"
#include "HTMLDlg.h"
#include <Windows.h>
#include <process.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CHTMLDlg 对话框




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


// CHTMLDlg 消息处理程序

BOOL CHTMLDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//设置托盘图标
	m_NotifyMini.Create( _T("穷穷浏览器") , this , IDR_MAINFRAME );
	m_NotifyMini.AddMenu( IDR_MENU_SYSTEM_MENU_ONE );

	
	GetWindowRect( &m_RetItem );
	m_RetItem.top += 22;
	m_RetItem.bottom -= 103;
	m_RetItem.left += 1;
	m_RetItem.right -= 11;

	m_TabCtrlAll.InsertItem( 0 , _T("网页界面") );
	m_TabCtrlAll.InsertItem( 1 , _T("自动控制") );
	m_TabCtrlAll.InsertItem( 2 , _T("代理信息") );
	m_TabCtrlAll.InsertItem( 3 , _T("控制信息") );
	m_TabCtrlAll.InsertItem( 4 , _T("电子邮件") );
	m_TabCtrlAll.InsertItem( 5 , _T("网络抓包") );

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



	//修改网址的URL的TIMER
	//SetTimer( 10001 , 110 , 0 );
	m_EdtURL.SetWindowText( _T("about:blank") );
	m_StrURL = _T("about:blank");
	m_HtmlView->Navigate2( _T("about:blank") );
	GetDlgItem( IDC_BUTTON_STOP_RECORD_VIEW )->EnableWindow( FALSE );

	m_PrcTheHtmlViewOpenProcess.SetRange( 0 , 100 );

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHTMLDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHTMLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CHTMLDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	if ( NULL != m_HtmlView )
	{
		delete m_HtmlView;
	}
}

void CHTMLDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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

//设置浏览器代理
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

//清除浏览器代理
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
	// TODO: 在此添加控件通知处理程序代码

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
	// TODO: 在此添加控件通知处理程序代码

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
	// TODO: 在此添加控件通知处理程序代码
	if ( m_DlgList.m_LBX[0].GetCount() < 1 )
	{
		return;
	}
	m_HtmlView->FillTheList();
}

void CHTMLDlg::OnBnClickedButtonTheHomePage()
{
	// TODO: 在此添加控件通知处理程序代码

	m_StrURL = THEHOMEPAGEDEFINE;
	m_HtmlView->Navigate2( THEHOMEPAGEDEFINE );
}

void CHTMLDlg::OnBnClickedButtonGoForward()
{
	// TODO: 在此添加控件通知处理程序代码
	m_HtmlView->GoForward();
}

void CHTMLDlg::OnBnClickedButtonGoBack()
{
	// TODO: 在此添加控件通知处理程序代码
	m_HtmlView->GoBack();

}

void CHTMLDlg::OnBnClickedButtonStartRecordView()
{
	// TODO: 在此添加控件通知处理程序代码

	m_DlgList.m_EdtRecordTime.GetWindowText( m_StrRecordURL );
	if ( m_StrRecordURL.IsEmpty() )
	{
		MessageBox( _T("需要在功能页面设置刷新时间") , _T("") );
		return;
	}

	int i = stol( m_StrRecordURL.GetBuffer() , 0 , 10 );

	m_DlgList.m_EdtRecordURL.GetWindowText( m_StrRecordURL );
	if ( m_StrRecordURL.IsEmpty() )
	{
		MessageBox( _T("需要在功能页面设置刷新地址") , _T("") );
		return;
	}
	SetTimer( 10002 , i , 0 );
	GetDlgItem( IDC_BUTTON_START_RECORD_VIEW )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_STOP_RECORD_VIEW )->EnableWindow( TRUE );
}

void CHTMLDlg::OnBnClickedButtonStopRecordView()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer( 10002 );
	GetDlgItem( IDC_BUTTON_START_RECORD_VIEW )->EnableWindow( TRUE );
	GetDlgItem( IDC_BUTTON_STOP_RECORD_VIEW )->EnableWindow( FALSE );
}

void CHTMLDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

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
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}


BOOL CHTMLDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
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

//获取Cookies
int CHTMLDlg::GetCookiesOnTheHtml( CString &str )
{
	CString URL;
	m_EdtURL.GetWindowText( URL );
	m_Cookies.GetCookies( URL , str );

	return 0;
}
void CHTMLDlg::OnBnClickedButtonHtmlViewGetCookies()
{
	// TODO: 在此添加控件通知处理程序代码
	CString cookies;
	GetCookiesOnTheHtml( cookies );
	m_EdtHtmlViewCookies.SetWindowText( cookies );
}
