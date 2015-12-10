//////////////////////////////////////////////////////////////////////////
//
//	DlgProxy.cpp
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
// DlgProxy.cpp : 实现文件
//

#include "stdafx.h"
#include "HTML.h"
#include "DlgProxy.h"

#include "HTMLDlg.h"


// CDlgProxy 对话框

IMPLEMENT_DYNAMIC(CDlgProxy, CDialog)

CDlgProxy::CDlgProxy(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProxy::IDD, pParent)
{
	m_nLastClickInList = -1;
}

CDlgProxy::~CDlgProxy()
{
}

void CDlgProxy::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NOW_USE_PROXY, m_EdtNowUseProxy);
	DDX_Control(pDX, IDC_LIST_PROXY_LIST, m_LclProxyList);
	DDX_Control(pDX, IDC_EDIT_PROXY_ADDRESS, m_EdtProxyAddress);
	DDX_Control(pDX, IDC_EDIT_PROXY_NAME, m_EdtProxyName);
	DDX_Control(pDX, IDC_EDIT_PROXY_SPEED, m_EdtProxySpeed);
	DDX_Control(pDX, IDC_EDIT_MAKE_IN_PROXY_FILE_PATH, m_EdtMakeInFilePath);
	DDX_Control(pDX, IDC_LIST_IMPORT_PROXY_MSG, m_LclImportProxy);
	DDX_Control(pDX, IDC_EDIT_SAVE_PROXY_LIST_PATH, m_EdtSaveProxyListPath);
	DDX_Control(pDX, IDC_LIST_GET_PROXY_WITH_THE_HTML_IN_LIST, m_LclGetProxyWithHtml);
	DDX_Control(pDX, IDC_LIST_TO_TEST_PROXY_TO_USE_HTML_PAGE, m_LclToTestProxyThePage);
	DDX_Control(pDX, IDC_EDIT_THE_PROXY_ANONYMOUS_LEVEL, m_EdtTheProxyAnonymousLevel);
	DDX_Control(pDX, IDC_EDIT_TO_USE_HTML_PAGE_TO_LIST, m_EdtToUseHtmlPageToList);
	DDX_Control(pDX, IDC_EDIT_TO_USE_HTML_PAGE_TEST_PROXY_FLAG, m_EdtToUseHtmlPageTestProxyFlag);
	DDX_Control(pDX, IDC_STATIC_TEST_PROXY_STATUS, m_StcTestProxyStatus);
	DDX_Control(pDX, IDC_EDIT_THE_TEST_THE_PROXY_TO_USE_THREAD_NUM, m_EdtTheTestProxyThreadNum);
}


BEGIN_MESSAGE_MAP(CDlgProxy, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PROXY_LIST, &CDlgProxy::OnNMClickListProxyList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PROXY_LIST, &CDlgProxy::OnNMDblclkListProxyList)
	ON_BN_CLICKED(IDC_ADD_PROXY_TO_LIST, &CDlgProxy::OnBnClickedAddProxyToList)
	ON_BN_CLICKED(IDC_REVISE_PROXY_IN_LIST, &CDlgProxy::OnBnClickedReviseProxyInList)
	ON_BN_CLICKED(IDC_DELETE_PROXY_IN_LIST, &CDlgProxy::OnBnClickedDeleteProxyInList)
	ON_BN_CLICKED(IDC_DELETE_ALL_PROXY_IN_LIST, &CDlgProxy::OnBnClickedDeleteAllProxyInList)
	ON_BN_CLICKED(IDC_BUTTON_USE_PROXY_IN_LIST, &CDlgProxy::OnBnClickedButtonUseProxyInList)
	ON_BN_CLICKED(IDC_BUTTON_NO_USE_PROXY, &CDlgProxy::OnBnClickedButtonNoUseProxy)
	ON_BN_CLICKED(IDC_BUTTON_MAKE_IN_PROXY_FILE_DIALOG, &CDlgProxy::OnBnClickedButtonMakeInProxyFileDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_PROXY_LIST, &CDlgProxy::OnBnClickedButtonSaveProxyList)
	ON_BN_CLICKED(IDC_DELETE_PROXY_IN_IMPORT_LIST, &CDlgProxy::OnBnClickedDeleteProxyInImportList)
	ON_BN_CLICKED(IDC_DELETE_ALL_PROXY_IN_IMPORT_LIST, &CDlgProxy::OnBnClickedDeleteAllProxyInImportList)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT_LIST_TO_LEFT, &CDlgProxy::OnBnClickedButtonRightListToLeft)
	ON_BN_CLICKED(IDC_BUTTON_LEFT_LIST_TO_RIGHT, &CDlgProxy::OnBnClickedButtonLeftListToRight)
	ON_BN_CLICKED(IDC_BUTTON_CLICK_ALL, &CDlgProxy::OnBnClickedButtonClickAll)
	ON_BN_CLICKED(IDC_BUTTON_CLICK_IMPORT_ALL, &CDlgProxy::OnBnClickedButtonClickImportAll)
	ON_BN_CLICKED(IDC_BUTTON_ADD_TEST_HTML_PAGE_TO_LIST, &CDlgProxy::OnBnClickedButtonAddTestHtmlPageToList)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_TEST_HTML_PAGE_FROM_LIST, &CDlgProxy::OnBnClickedButtonDeleteTestHtmlPageFromList)
	ON_BN_CLICKED(IDC_BUTTON_START_TO_TEST_PROXY_FROM_TOW_LIST, &CDlgProxy::OnBnClickedButtonStartToTestProxyFromTowList)
	ON_BN_CLICKED(IDC_BUTTON_STOP_TO_TEST_PROXY_IN_TOW_LIST, &CDlgProxy::OnBnClickedButtonStopToTestProxyInTowList)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_THE_BROCK_PROXY_IN_IMPORT_LIST, &CDlgProxy::OnBnClickedButtonDeleteTheBrockProxyInImportList)
END_MESSAGE_MAP()


// CDlgProxy 消息处理程序

void CDlgProxy::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CDlgProxy::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnCancel();
}

BOOL CDlgProxy::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_LclProxyList.InsertColumn( 0 , _T("代理IP地址") , LVCFMT_LEFT , 170 );
	m_LclProxyList.InsertColumn( 1 , _T("名字") , LVCFMT_LEFT , 60 );
	m_LclProxyList.InsertColumn( 2 , _T("速度") , LVCFMT_LEFT , 40 );
	m_LclProxyList.InsertColumn( 3 , _T("匿名度") , LVCFMT_LEFT , 60 );
	m_LclProxyList.SetExtendedStyle( LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT );
	m_LclImportProxy.InsertColumn( 0 , _T("代理IP地址") , LVCFMT_LEFT , 170 );
	m_LclImportProxy.InsertColumn( 1 , _T("名字") , LVCFMT_LEFT , 60 );
	m_LclImportProxy.InsertColumn( 2 , _T("速度") , LVCFMT_LEFT , 40 );
	m_LclImportProxy.InsertColumn( 3 , _T("匿名度") , LVCFMT_LEFT , 60 );
	m_LclImportProxy.SetExtendedStyle( LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT );
	m_LclGetProxyWithHtml.InsertColumn( 0 , _T("目标网址") , LVCFMT_LEFT , 150 );
	m_LclGetProxyWithHtml.InsertColumn( 1 , _T("要搜索的页面") , LVCFMT_LEFT , 150 );
	m_LclGetProxyWithHtml.InsertColumn( 2 , _T("从") , LVCFMT_LEFT , 30 );
	m_LclGetProxyWithHtml.InsertColumn( 3 , _T("到") , LVCFMT_LEFT , 30 );
	m_LclGetProxyWithHtml.SetExtendedStyle( LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT );
	m_LclToTestProxyThePage.InsertColumn( 0 , _T("测试网址") , LVCFMT_LEFT , 180 );
	m_LclToTestProxyThePage.InsertColumn( 1 , _T("连接成功标志") , LVCFMT_LEFT , 180 );
	m_LclToTestProxyThePage.SetExtendedStyle( LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT );

#ifdef _DEBUG
	m_LclProxyList.InsertItem( 0 , _T("10.10.10.1:808") );
	m_LclProxyList.SetItemText( 0 , 1 , _T("宿主机") );
	m_LclProxyList.SetItemText( 0 , 2 , _T("快") );
#endif

	m_EdtProxyName.SetWindowText( _T("0") );
	m_EdtProxySpeed.SetWindowText( _T("0") );
	m_EdtTheProxyAnonymousLevel.SetWindowText( _T("0") );
	m_EdtNowUseProxy.SetWindowText( _T("目前没有用任何代理") );
	m_EdtMakeInFilePath.SetWindowText( _T("等待读取文件") );
	m_EdtSaveProxyListPath.SetWindowText( _T("等待保存文件") );
	m_LclToTestProxyThePage.InsertItem( 0 , _T("http://www.baidu.com/") );
	m_LclToTestProxyThePage.SetCheck( 0 );
	m_EdtTheTestProxyThreadNum.SetWindowText( _T("10") );



	GetDlgItem( IDC_BUTTON_STOP_TO_TEST_PROXY_IN_TOW_LIST )->EnableWindow( FALSE ) ;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgProxy::OnNMClickListProxyList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_nLastClickInList = pNMItemActivate->iItem;

	m_EdtProxyAddress.SetWindowText( _T("") );
	m_EdtProxyName.SetWindowText( _T("0") );
	m_EdtProxySpeed.SetWindowText( _T("0") );
	m_EdtTheProxyAnonymousLevel.SetWindowText( _T("0") );

	*pResult = 0;
}

void CDlgProxy::OnNMDblclkListProxyList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int i  = pNMItemActivate->iItem;
	CString str;
	str = m_LclProxyList.GetItemText( i , 0 );
	m_EdtProxyAddress.SetWindowText( str );
	str = m_LclProxyList.GetItemText( i , 1 );
	m_EdtProxyName.SetWindowText( str );
	str = m_LclProxyList.GetItemText( i , 2 );
	m_EdtProxySpeed.SetWindowText( str );
	str = m_LclProxyList.GetItemText( i , 3 );
	m_EdtTheProxyAnonymousLevel.SetWindowText( str );

	*pResult = 0;
}

void CDlgProxy::OnBnClickedAddProxyToList()
{
	// TODO: 在此添加控件通知处理程序代码


	int i = 0;
	i = m_LclProxyList.GetItemCount();

	CString strIP;
	m_EdtProxyAddress.GetWindowText( strIP );
	m_LclProxyList.InsertItem( i , strIP );

	m_EdtProxyName.GetWindowText( strIP );
	m_LclProxyList.SetItemText( i , 1 , strIP );

	m_EdtProxySpeed.GetWindowText( strIP );
	m_LclProxyList.SetItemText( i , 2 , strIP );

	m_EdtTheProxyAnonymousLevel.GetWindowText( strIP );
	m_LclProxyList.SetItemText( i , 3 , strIP );
	m_nLastClickInList = -1;
}

void CDlgProxy::OnBnClickedReviseProxyInList()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( IDOK != MessageBox( _T("修改操作是不可逆的，改了就变了") , _T("注意") , MB_OKCANCEL ) )
	{
		return;
	}
	if ( -1 == m_nLastClickInList )
	{
		MessageBox( _T("要改哪个，去点一下") , _T("去点一下") );
		return;
	}

	CString strIP;

	m_EdtProxyAddress.GetWindowText( strIP );
	m_LclProxyList.SetItemText( m_nLastClickInList , 0 , strIP );

	m_EdtProxyName.GetWindowText( strIP );
	m_LclProxyList.SetItemText( m_nLastClickInList , 1 , strIP );

	m_EdtProxySpeed.GetWindowText( strIP );
	m_LclProxyList.SetItemText( m_nLastClickInList , 2 , strIP );

	m_EdtTheProxyAnonymousLevel.GetWindowText( strIP );
	m_LclProxyList.SetItemText( m_nLastClickInList , 3 , strIP );
	m_nLastClickInList = -1;
}

void CDlgProxy::OnBnClickedDeleteProxyInList()
{
	// TODO: 在此添加控件通知处理程序代码

	if ( IDOK != MessageBox( _T("删除操作是不可逆的，删了就没了") , _T("注意") , MB_OKCANCEL ) )
	{
		return;
	}

	int h = 0;
	int i = 0;
	int j = m_LclProxyList.GetItemCount();
	for ( i = j - 1 ; i >= 0 ; i-- )
	{
		if ( m_LclProxyList.GetCheck( i ) )
		{
			m_LclProxyList.DeleteItem( i );
			h++;
		}
	}
	if ( 0 == h )
	{
		MessageBox( _T("要删哪个，去点一下") , _T("去点一下") );
		return;
	}
	CString str;
	str.Format( _T("成功删除了%d个代理") , h );
	MessageBox( str , _T("可以了") );
	m_nLastClickInList = -1;
}

void CDlgProxy::OnBnClickedDeleteAllProxyInList()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( IDOK != MessageBox( _T("删除操作是不可逆的，删了就没了") , _T("注意") , MB_OKCANCEL ) )
	{
		return;
	}
	m_LclProxyList.DeleteAllItems();
	m_nLastClickInList = -1;
}

void CDlgProxy::OnBnClickedButtonUseProxyInList()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( -1 == m_nLastClickInList )
	{
		MessageBox( _T("要用哪个代理，去点一下") , _T("去点一下") );
		return;
	}
	CString str;
	str = m_LclProxyList.GetItemText( m_nLastClickInList , 0 );
	((CHTMLDlg*)m_pParent)->SetMyIeProxy( str );

	str.Format( _T("%s(%s)") ,
				str ,
				m_LclProxyList.GetItemText( m_nLastClickInList , 1 ) );
	m_EdtNowUseProxy.SetWindowText( str );
}

void CDlgProxy::OnBnClickedButtonNoUseProxy()
{
	// TODO: 在此添加控件通知处理程序代码
	((CHTMLDlg*)m_pParent)->DelMyIeProxy();
	m_EdtNowUseProxy.SetWindowText( _T("目前没有用任何代理") );
}

void CDlgProxy::OnBnClickedButtonMakeInProxyFileDialog()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fd( TRUE , 0 , _T("") , 4|2 , 
					_T("文本文件(*.txt)|*.txt||") );
	if ( IDOK != fd.DoModal() )
	{
		m_EdtMakeInFilePath.SetWindowText( _T("没有读取文件") );
		return;
	}
	CString str;
	str = fd.GetPathName();
	if ( _T(".txt") != str.Right(4) )
	{
		m_EdtMakeInFilePath.SetWindowText( _T("文件格式出错") );
		return;
	}

	CFile file;
	if(!file.Open( str, CFile::modeRead ))
	{
		m_EdtMakeInFilePath.SetWindowText( _T("文件不存在") );
		return;
	}
	if ( IDOK != MessageBox( _T("是否确认读取") , _T("确认") , MB_OKCANCEL ) )
	{
		m_EdtMakeInFilePath.SetWindowText( _T("没有读取文件") );
		file.Close();
		return;
	}

	m_EdtMakeInFilePath.SetWindowText( str );
	char strfile[1024];
	CStringA strA = "";
	file.SeekToBegin();
	ULONGLONG nlong = file.GetLength();
	for ( ULONGLONG i = 0 ; i < nlong ;  )
	{
		memset( strfile , 0 , 1024 );
		file.Read( strfile , 1023 );
		strA += strfile;
		i += 1023;
	}
	file.Close();
	for ( int i = 0 ; ; )
	{
		i = strA.Find( "\t\t" );
		if ( -1 == i )
		{
			break;
		}
		strA.Delete( i );
	}
	for ( int i = 0 ; ; )
	{
		i = strA.Find( "\t\r\n" );
		if ( -1 == i )
		{
			break;
		}
		strA.Delete( i );
	}
	for ( int i = 0 ; ; )
	{
		i = strA.Find( "\n\t" );
		if ( -1 == i )
		{
			break;
		}
		strA.Delete( i );
	}
	for ( int i = 0 ; ; )
	{
		i = strA.Find( "\r\t" );
		if ( -1 == i )
		{
			break;
		}
		strA.Delete( i );
	}
	str = strA;
	CString strW;
	int j = 0;
	int l = 0;
	int s = 0;
	CString strP;
	CString strQ;
	for ( int i = m_LclImportProxy.GetItemCount() ; ; i++ )
	{
		j = str.Find( _T( '\n' ) ) + 1;
		if ( 0 == str.GetLength() )
		{
			break;
		}
		strW = str.Left( j - 1 );
		str.Delete( 0 , j );
		if ( strW.GetLength() < 9 )
		{
			continue;
		}
		l = strW.GetLength();
		s = strW.Find( _T('\t') );
		if ( -1 != s )
		{
			strP = strW.Left( s );
			strW = strW.Right( l - s - 1 );

			l = strW.GetLength();
			m_LclImportProxy.InsertItem( i , strP );
			if ( s + 1 == j )
			{
				continue;
			}
		}
		else
		{
			s = strW.Find( _T('\n') );
			if ( -1 == s )
			{
				m_LclImportProxy.InsertItem( i , strW );
			}
			continue;
		}
		s = strW.Find( _T('\t') );
		if ( -1 != s )
		{
			strP = strW.Left( s );
			strW = strW.Right( l - s - 1 );

			l = strW.GetLength();
			m_LclImportProxy.SetItemText( i , 1 , strP );
			if ( s + 1 == j )
			{
				continue;
			}
		}
		else
		{
			s = strW.Find( _T('\n') );
			if ( -1 == s )
			{
				m_LclImportProxy.SetItemText( i , 1 , strW );
			}
			continue;
		}
		s = strW.Find( _T('\t') );
		if ( -1 != s )
		{
			strP = strW.Left( s );
			strW = strW.Right( l - s - 1 );

			l = strW.GetLength();
			m_LclImportProxy.SetItemText( i , 2 , strP );
			if ( s + 1 == j )
			{
				continue;
			}
		}
		else
		{
			s = strW.Find( _T('\n') );
			if ( -1 == s )
			{
				m_LclImportProxy.SetItemText( i , 2 , strW );
			}
			continue;
		}
		m_LclImportProxy.SetItemText( i , 3 , strW );
	}
}

void CDlgProxy::OnBnClickedButtonSaveProxyList()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fd( FALSE , _T(".txt") , _T("") , 4|2 , 
		_T("文本文件(*.txt)|*.txt||") );
	if ( IDOK != fd.DoModal() )
	{
		m_EdtSaveProxyListPath.SetWindowText( _T("没有保存文件") );
		return;
	}
	CString str;
	str = fd.GetPathName();
	CFile file;
	if(!file.Open( str, CFile::modeWrite ))
	{
		if ( IDOK != MessageBox( _T("是否创建") , _T("文件不存在") , MB_OKCANCEL ) )
		{
			m_EdtSaveProxyListPath.SetWindowText( _T("没有保存文件") );
			return;
		}
	}
	else
	{
		file.Close();
	}
	if ( !file.Open( str , CFile::modeCreate | CFile::modeWrite ) )
	{
		m_EdtSaveProxyListPath.SetWindowText( _T("覆盖文件失败") );
		file.Close();
		return;
	}
	m_EdtSaveProxyListPath.SetWindowText( str );
	CStringA strA = "";
	str = _T("");
	CString strW = _T("");
	for ( int i = 0 ; i < m_LclImportProxy.GetItemCount() ; i++ )
	{
		str = m_LclImportProxy.GetItemText( i , 0 );
		strW = strW + str ;
		str = m_LclImportProxy.GetItemText( i , 1 );
		if ( !str.IsEmpty() )
		{
			strW = strW + _T('\t') + str ;
		}
		else
		{
			strW = strW + _T("\t0") ;
		}
		str = m_LclImportProxy.GetItemText( i , 2 );
		if ( !str.IsEmpty() )
		{
			strW = strW + _T('\t') + str ;
		}
		else
		{
			strW = strW + _T("\t0") ;
		}
		str = m_LclImportProxy.GetItemText( i , 3 );
		if ( !str.IsEmpty() )
		{
			strW = strW + _T('\t') + str ;
		}
		else
		{
			strW = strW + _T("\t0") ;
		}
		strW = strW + _T("\r\n");
	}
	strA = strW;

	char fnd[3] = { 0x0D , 0x0D , 0x00 };
	for ( int i = 0 ; ; )
	{
		i = strA.Find( fnd );
		if ( -1 == i )
		{
			break;
		}
		strA.Delete( i );
	}

	file.Write( strA.GetBuffer() , strA.GetLength() );
	strA.ReleaseBuffer();

	file.Close();
}

void CDlgProxy::OnBnClickedDeleteProxyInImportList()
{
	// TODO: 在此添加控件通知处理程序代码

	if ( IDOK != MessageBox( _T("删除操作是不可逆的，删了就没了") , _T("注意") , MB_OKCANCEL ) )
	{
		return;
	}

	int h = 0;
	int i = 0;
	int j = m_LclImportProxy.GetItemCount();
	for ( i = j - 1 ; i >= 0 ; i-- )
	{
		if ( m_LclImportProxy.GetCheck( i ) )
		{
			m_LclImportProxy.DeleteItem( i );
			h++;
		}
	}
	if ( 0 == h )
	{
		MessageBox( _T("要删哪个，去点一下") , _T("去点一下") );
		return;
	}
	CString str;
	str.Format( _T("成功删除了%d个代理") , h );
	MessageBox( str , _T("可以了") );
}

void CDlgProxy::OnBnClickedDeleteAllProxyInImportList()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( IDOK != MessageBox( _T("删除操作是不可逆的，删了就没了") , _T("注意") , MB_OKCANCEL ) )
	{
		return;
	}
	m_LclImportProxy.DeleteAllItems();
}

void CDlgProxy::OnBnClickedButtonRightListToLeft()
{
	// TODO: 在此添加控件通知处理程序代码
	int h = 0;
	int i = 0;
	int j = m_LclImportProxy.GetItemCount();
	int k = m_LclProxyList.GetItemCount();
	CString str;
	for ( i = 0 ; i < j ; i++ )
	{
		if ( m_LclImportProxy.GetCheck( i ) )
		{
			str = m_LclImportProxy.GetItemText( i , 0 );
			m_LclProxyList.InsertItem( k , str );
			str = m_LclImportProxy.GetItemText( i , 1 );
			m_LclProxyList.SetItemText( k , 1 , str );
			str = m_LclImportProxy.GetItemText( i , 2 );
			m_LclProxyList.SetItemText( k , 2 , str );
			str = m_LclImportProxy.GetItemText( i , 3 );
			m_LclProxyList.SetItemText( k , 3 , str );
			k++;
			h++;
		}
	}
	j = m_LclImportProxy.GetItemCount();
	for ( i = j - 1 ; i >= 0 ; i-- )
	{
		if ( m_LclImportProxy.GetCheck( i ) )
		{
			m_LclImportProxy.DeleteItem( i );
		}
	}
	if ( 0 == h )
	{
		MessageBox( _T("要移动哪个，去点一下") , _T("去点一下") );
		return;
	}
	str.Format( _T("成功移动了%d个代理") , h );
	MessageBox( str , _T("可以了") );
}

void CDlgProxy::OnBnClickedButtonLeftListToRight()
{
	// TODO: 在此添加控件通知处理程序代码
	int h = 0;
	int i = 0;
	int j = m_LclProxyList.GetItemCount();
	int k = m_LclImportProxy.GetItemCount();
	CString str;
	for ( i = 0 ; i < j ; i++ )
	{
		if ( m_LclProxyList.GetCheck( i ) )
		{
			str = m_LclProxyList.GetItemText( i , 0 );
			m_LclImportProxy.InsertItem( k , str );
			str = m_LclProxyList.GetItemText( i , 1 );
			m_LclImportProxy.SetItemText( k , 1 , str );
			str = m_LclProxyList.GetItemText( i , 2 );
			m_LclImportProxy.SetItemText( k , 2 , str );
			str = m_LclProxyList.GetItemText( i , 3 );
			m_LclImportProxy.SetItemText( k , 3 , str );
			k++;
			h++;
		}
	}
	j = m_LclProxyList.GetItemCount();
	for ( i = j - 1 ; i >= 0 ; i-- )
	{
		if ( m_LclProxyList.GetCheck( i ) )
		{
			m_LclProxyList.DeleteItem( i );
		}
	}
	if ( 0 == h )
	{
		MessageBox( _T("要移动哪个，去点一下") , _T("去点一下") );
		return;
	}
	str.Format( _T("成功移动了%d个代理") , h );
	MessageBox( str , _T("可以了") );
}

void CDlgProxy::OnBnClickedButtonClickAll()
{
	// TODO: 在此添加控件通知处理程序代码
	int j = m_LclProxyList.GetItemCount();
	for ( int i = 0 ; i < j ; i++ )
	{
		m_LclProxyList.SetCheck( i );
	}
}

void CDlgProxy::OnBnClickedButtonClickImportAll()
{
	// TODO: 在此添加控件通知处理程序代码
	int j = m_LclImportProxy.GetItemCount();
	for ( int i = 0 ; i < j ; i++ )
	{
		m_LclImportProxy.SetCheck( i );
	}
}

void CDlgProxy::OnBnClickedButtonAddTestHtmlPageToList()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_EdtToUseHtmlPageToList.GetWindowText( str );
	if ( str.IsEmpty() )
	{
		MessageBox( _T("要添加，咱是不是也该写一个啊") , _T("写") );
		return;
	}
	if ( str.GetLength() <12 )
	{
		MessageBox( _T("重写重写") , _T("重写重写") );
		return;
	}
	if ( _T("http://") != str.Left( 7 ) )
	{
	}
	if ( _T("/") != str.Right(1) )
	{
		MessageBox( _T("删了重写") , _T("格式不对") );
		return;
	}
	int i = m_LclToTestProxyThePage.GetItemCount();
	m_LclToTestProxyThePage.InsertItem( i , str );
	m_EdtToUseHtmlPageTestProxyFlag.GetWindowText( str );
	m_LclToTestProxyThePage.SetItemText( i , 1 , str );
}

void CDlgProxy::OnBnClickedButtonDeleteTestHtmlPageFromList()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( IDOK != MessageBox( _T("删除是多选工作") , _T("想好了要删？") , MB_OKCANCEL ) )
	{
		return;
	}
	int h = 0;
	for ( int i = m_LclToTestProxyThePage.GetItemCount() -1 ; i >= 0 ; i-- )
	{
		if ( m_LclToTestProxyThePage.GetCheck( i ) )
		{
			m_LclToTestProxyThePage.DeleteItem( i );
			h++;
		}
	}
	if ( 0 == h )
	{
		MessageBox( _T("哥们，咱需要选几个，然后再删除") , _T("愁死我了") );
		return;
	}
	CString str;
	str.Format( _T("成功删除：%d个") , h );
	MessageBox( str , _T("很成功") );
}

void CDlgProxy::OnBnClickedButtonStartToTestProxyFromTowList()
{
	// TODO: 在此添加控件通知处理程序代码
	int i = 0;
	for ( i = 0 ; i < m_LclToTestProxyThePage.GetItemCount() ; i++ )
	{
		if ( m_LclToTestProxyThePage.GetCheck(i) )
		{
			break;
		}
	}
	if ( i == m_LclToTestProxyThePage.GetItemCount() )
	{
		MessageBox( _T("咱别这么玩行么") , _T("选一个") );
		return;
	}

	CStringA strH;
	CStringA strA;
	CString strP;
	CString strW;
	strP = m_LclToTestProxyThePage.GetItemText( i , 0 );

	strA = strP;
	strH = "GET " ;
	strA += " HTTP/1.1\r\n";
	strH += strA;
	strH += "Accept: */*\r\n";
	strH += "Accept-Language: zh-cn\r\n";
	strH += "User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET CLR 2.0.50727)\r\n";
	strH += "Host: ";
	strA.Delete( 0 , 7 );
	strA.Delete( strA.GetLength() - 12 , 12 );
	strH += strA;
	strH += "\r\n";
	strH += "Connection: Keep-Alive\r\n\r\n";

	//strH = "GET http://www.baidu.com/ HTTP/1.1\r\n"
	//		"Accept: */*\r\n"
	//		"Accept-Language: zh-cn\r\n"
	//		"User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET CLR 2.0.50727)\r\n"
	//		"Host: www.baidu.com\r\n"
	//		"Connection: Keep-Alive\r\n\r\n";

	strP = m_LclToTestProxyThePage.GetItemText( i , 1 );
	strA = strP;
	m_EdtTheTestProxyThreadNum.GetWindowText( strW );
	i = m_TTP.creat( strH ,
					strA ,
					&m_LclImportProxy ,
					&m_StcTestProxyStatus ,
					stol( strW , 0 , 10) );
	if ( 0 != i )
	{
		m_StcTestProxyStatus.SetWindowText( _T("启动失败") );
		return;
	}
	i = m_TTP.start();
	if ( 0 != i )
	{
		m_StcTestProxyStatus.SetWindowText( _T("启动失败") );
		return;
	}
	GetDlgItem( IDC_BUTTON_START_TO_TEST_PROXY_FROM_TOW_LIST )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_STOP_TO_TEST_PROXY_IN_TOW_LIST )->EnableWindow( TRUE ) ;
}

void CDlgProxy::OnBnClickedButtonStopToTestProxyInTowList()
{
	// TODO: 在此添加控件通知处理程序代码
	m_TTP.stop();
	GetDlgItem( IDC_BUTTON_START_TO_TEST_PROXY_FROM_TOW_LIST )->EnableWindow( TRUE );
	GetDlgItem( IDC_BUTTON_STOP_TO_TEST_PROXY_IN_TOW_LIST )->EnableWindow( FALSE ) ;
}

void CDlgProxy::OnBnClickedButtonDeleteTheBrockProxyInImportList()
{
	// TODO: 在此添加控件通知处理程序代码

	if ( IDOK != MessageBox( _T("删除操作是不可逆的，删了就没了") , _T("注意") , MB_OKCANCEL ) )
	{
		return;
	}

	int i = 0;
	int t = -1;
	CString str;
	for ( i = m_LclImportProxy.GetItemCount() - 1 ; i >= 0  ; i-- )
	{
		str = m_LclImportProxy.GetItemText( i , 2 );

		t = str.Find( _T("连接失败") );
		if ( -1 != t )
		{
			m_LclImportProxy.DeleteItem( i );
			continue;
		}

		t = str.Find( _T("地址无效") );
		if ( -1 != t )
		{
			m_LclImportProxy.DeleteItem( i );
			continue;
		}

		t = str.Find( _T("未知") );
		if ( -1 != t )
		{
			m_LclImportProxy.DeleteItem( i );
			continue;
		}

		t = str.Find( _T("超时") );
		if ( -1 != t )
		{
			m_LclImportProxy.DeleteItem( i );
			continue;
		}
	}
}
