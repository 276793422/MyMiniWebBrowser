//////////////////////////////////////////////////////////////////////////
//
//	DlgCommandListInfomation.cpp
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
// DlgCommandListInfomation.cpp : 实现文件
//

#include "stdafx.h"
#include "HTML.h"
#include "DlgCommandListInfomation.h"
#include "HTMLDlg.h"


// CDlgCommandListInfomation 对话框

IMPLEMENT_DYNAMIC(CDlgCommandListInfomation, CDialog)

CDlgCommandListInfomation::CDlgCommandListInfomation(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCommandListInfomation::IDD, pParent)
{

}

CDlgCommandListInfomation::~CDlgCommandListInfomation()
{
}

void CDlgCommandListInfomation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CLI_COMMAND_OPEN_PAGE_LIST, m_LclCLICommandOpenURLList);
	DDX_Control(pDX, IDC_EDIT_CLI_ADD_TO_OPEN_LIST, m_EdtCLIAddToOpenList);
	DDX_Control(pDX, IDC_EDIT_CLI_ADD_TO_OPEN_LIST_FROM, m_EdtONCLIAddToOpenFrom);
	DDX_Control(pDX, IDC_EDIT_CLI_ADD_TO_OPEN_LIST_TO, m_EdtONCLIAddToOpenTo);
	DDX_Control(pDX, IDC_EDIT_CLI_GET_THE_URL_ON_PAGE_WITH_HAND_SYMBOL, m_EdtCLIGetTheURLOnPageWithHandSymbol);
	DDX_Control(pDX, IDC_EDIT_CLI_GET_THE_URL_ON_PAGE_WITH_LAST_SYMBOL, m_EdtCLIGetTheURLOnPageWithLastSymbol);
	DDX_Control(pDX, IDC_EDIT_CLI_GET_THE_URL_ON_PAGE_WITH_HAND_AND_LAST_NUM, m_EdtCLIGetTheURLOnPageWithHandAndLastNum);
	DDX_Control(pDX, IDC_LIST_CLI_TO_GET_THE_ELEMENT_FROM_PAGE, m_LclCLIToGetTheElementFromPage);
	DDX_Control(pDX, IDC_EDIT_CLI_SAVE_GET_MESSAGE_TO_THIS_FILE, m_EdtCLISaveGetMessageToThisFile);
	DDX_Control(pDX, IDC_EDIT_CLI_COMMAND_OPEN_PAGE_LIST_LOAD_FROM_FILE, m_EdtCLICommandOpenURLLoadFromFile);
	DDX_Control(pDX, IDC_EDIT_CLI_COMMAND_OPEN_PAGE_LIST_SAVE_TO_FILE, m_EdtCLICommandOpenURLSaveToFile);
	DDX_Control(pDX, IDC_EDIT_CLI_THE_ELEMENT_FROM_PAGE_ADD_FIRST, m_EdtCLITheElementFromPageAddFirst);
	DDX_Control(pDX, IDC_EDIT_CLI_TO_GET_THE_ELEMENT_LOAD_FROM_FILE, m_EdtCLIToGetTheElenentLoadFromFile);
	DDX_Control(pDX, IDC_EDIT_CLI_TO_GET_THE_ELEMENT_SAVE_TO_FILE, m_EdtCLIToGetTheElenentSaveToFile);
	DDX_Control(pDX, IDC_STATIC_CLI_ELEMENT_LIST_COUNT, m_StcCLIElementListCount);
}


BEGIN_MESSAGE_MAP(CDlgCommandListInfomation, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CLI_ADD_TO_OPEN_LIST, &CDlgCommandListInfomation::OnBnClickedButtonCliAddToOpenList)
	ON_BN_CLICKED(IDC_BUTTON_CLI_DELETE_URL_FROM_OPEN_LIST, &CDlgCommandListInfomation::OnBnClickedButtonCliDeleteUrlFromOpenList)
	ON_BN_CLICKED(IDC_BUTTON_CLI_DELETE_ALL_URL_FROM_OPEN_LIST, &CDlgCommandListInfomation::OnBnClickedButtonCliDeleteAllUrlFromOpenList)
	ON_BN_CLICKED(IDC_BUTTON_CLI_SAVE_GET_MESSAGE_TO_THIS_FILE, &CDlgCommandListInfomation::OnBnClickedButtonCliSaveGetMessageToThisFile)
	ON_BN_CLICKED(IDC_BUTTON_CLI_COMMAND_OPEN_PAGE_LIST_SIVE_TO_FILE, &CDlgCommandListInfomation::OnBnClickedButtonCliCommandOpenPageListSiveToFile)
	ON_BN_CLICKED(IDC_BUTTON_CLI_COMMAND_OPEN_PAGE_LIST_LOAD_FROM_FILE, &CDlgCommandListInfomation::OnBnClickedButtonCliCommandOpenPageListLoadFromFile)
	ON_BN_CLICKED(IDC_BUTTON_CLI_THE_ELEMENT_FROM_PAGE_ADD_FIRST, &CDlgCommandListInfomation::OnBnClickedButtonCliTheElementFromPageAddFirst)
	ON_BN_CLICKED(IDC_BUTTON_CLI_TO_GET_THE_ELEMENT_LOAD_FROM_FILE, &CDlgCommandListInfomation::OnBnClickedButtonCliToGetTheElementLoadFromFile)
	ON_BN_CLICKED(IDC_BUTTON_CLI_TO_GET_THE_ELEMENT_SAVE_TO_FILE, &CDlgCommandListInfomation::OnBnClickedButtonCliToGetTheElementSaveToFile)
	ON_BN_CLICKED(IDC_BUTTON_CLI_THE_ELEMENT_FROM_PAGE_DELETE_ALL, &CDlgCommandListInfomation::OnBnClickedButtonCliTheElementFromPageDeleteAll)
	ON_BN_CLICKED(IDC_BUTTON_CLI_THE_ELEMENT_FROM_PAGE_DELETE_THE_SAME, &CDlgCommandListInfomation::OnBnClickedButtonCliTheElementFromPageDeleteTheSame)
END_MESSAGE_MAP()


// CDlgCommandListInfomation 消息处理程序

BOOL CDlgCommandListInfomation::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_LclCLICommandOpenURLList.InsertColumn( 0 , _T("要打开的URL") , LVCFMT_LEFT , 255 );
	m_LclCLICommandOpenURLList.SetExtendedStyle( LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT );
	m_LclCLIToGetTheElementFromPage.InsertColumn( 0 , _T("提取出来的地址") , LVCFMT_LEFT , 255 );
	m_LclCLIToGetTheElementFromPage.SetExtendedStyle( LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT );

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgCommandListInfomation::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CDlgCommandListInfomation::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnCancel();
}

void CDlgCommandListInfomation::OnBnClickedButtonCliAddToOpenList()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_EdtCLIAddToOpenList.GetWindowText( str );
	if ( str.IsEmpty() )
	{
		MessageBox( _T("要加入什么，是不是得写一下") , _T("犯了个低级错误") );
		return;
	}
	CString strNum;
	int i = m_LclCLICommandOpenURLList.GetItemCount();
	strNum.Format( _T("%d") , i );
	int n = str.Find( _T("(*)") );
	if ( -1 == n )
	{
		m_LclCLICommandOpenURLList.InsertItem( 0 , str );
		return;
	}
	CString strFrom;
	m_EdtONCLIAddToOpenFrom.GetWindowText( strFrom );
	CString strTo;
	m_EdtONCLIAddToOpenTo.GetWindowText( strTo );
	if ( strFrom > strTo )
	{
		MessageBox( _T("写得乱七八糟") , _T("不能逆序") );
		return;
	}
	int nFrom = stol( strFrom , 0 , 10 );
	int nTo = stol( strTo , 0 , 10 );
	strFrom = str.Left( n );
	strTo = str.Right( str.GetLength() - n - 3 );
	for ( ; ; i++ )
	{
		str.Format( _T("%s%d%s") , strFrom , nFrom , strTo );
		m_LclCLICommandOpenURLList.InsertItem( 0 , str );
		if ( nFrom == nTo )
		{
			break;
		}
		nFrom++;
	}
}

void CDlgCommandListInfomation::OnBnClickedButtonCliDeleteUrlFromOpenList()
{
	// TODO: 在此添加控件通知处理程序代码
	int h = 0;
	int all = m_LclCLICommandOpenURLList.GetItemCount();
	if ( 0 == all )
	{
		MessageBox( _T("一个都没有，你删啥") , _T("犯了个低级错误") );
		return;
	}
	for ( int i = ( all - 1 ) ; i >= 0 ; i-- )
	{
		if ( m_LclCLICommandOpenURLList.GetCheck(i) )
		{
			m_LclCLICommandOpenURLList.DeleteItem(i);
			h++;
		}
	}
	if ( 0 == h )
	{
		MessageBox( _T("一个都没选，你删啥") , _T("犯了个低级错误") );
	}
}

void CDlgCommandListInfomation::OnBnClickedButtonCliDeleteAllUrlFromOpenList()
{
	// TODO: 在此添加控件通知处理程序代码
	m_LclCLICommandOpenURLList.DeleteAllItems();
}

void CDlgCommandListInfomation::OnBnClickedButtonCliSaveGetMessageToThisFile()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog f( FALSE , 0 , _T("") , 4|2 , _T("文本文件(*.txt)|*.txt||") );
	if ( IDOK != f.DoModal() )
	{
		return ;
	}
	CString str = f.GetPathName();
	m_EdtCLISaveGetMessageToThisFile.SetWindowText( str );
}

void CDlgCommandListInfomation::OnBnClickedButtonCliTheElementFromPageAddFirst()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_EdtCLITheElementFromPageAddFirst.GetWindowText( str );
	CString strT;
	for ( int i = 0 ; i < m_LclCLIToGetTheElementFromPage.GetItemCount() ; i++ )
	{
		strT = m_LclCLIToGetTheElementFromPage.GetItemText( i , 0 );
		if ( _T("..") == strT.Left(2) )
		{
			strT.Delete( 0 , 2 );
			m_LclCLIToGetTheElementFromPage.SetItemText( i , 0 , str + strT );
		}
	}
}

void CDlgCommandListInfomation::OnBnClickedButtonCliCommandOpenPageListSiveToFile()
{
	// TODO: 在此添加控件通知处理程序代码
	SaveFileWithList( 1 );
}

void CDlgCommandListInfomation::OnBnClickedButtonCliCommandOpenPageListLoadFromFile()
{
	// TODO: 在此添加控件通知处理程序代码
	LoadFileWithList( 1 );
}

void CDlgCommandListInfomation::OnBnClickedButtonCliToGetTheElementSaveToFile()
{
	// TODO: 在此添加控件通知处理程序代码
	SaveFileWithList( 2 );
}

void CDlgCommandListInfomation::OnBnClickedButtonCliToGetTheElementLoadFromFile()
{
	// TODO: 在此添加控件通知处理程序代码
	LoadFileWithList( 2 );
}

void CDlgCommandListInfomation::SaveFileWithList( int mod )
{
	CFileDialog f( FALSE , 0 , _T("") , 4|2 , _T("文本文件(*.txt)|*.txt||") );
	if ( IDOK != f.DoModal() )
	{
		return ;
	}
	if ( IDOK != MessageBox( _T("是否确定保存，若原有文件存在，则直接覆盖") , _T("要慎重") , MB_OKCANCEL ) )
	{
		return;
	}
	CString str = f.GetPathName();
	if ( 1 == mod )
	{
		m_EdtCLICommandOpenURLSaveToFile.SetWindowText( str );
	}
	if ( 2 == mod )
	{
		m_EdtCLIToGetTheElenentSaveToFile.SetWindowText( str );
	}

	CFile file( str , CFile::modeCreate | CFile::modeWrite );
	CStringA strA ;
	CStringA strAA = "";
	int j = 0;
	if ( 1 == mod )
	{
		j = m_LclCLICommandOpenURLList.GetItemCount();
	}
	if ( 2 == mod )
	{
		j = m_LclCLIToGetTheElementFromPage.GetItemCount();
	}
	for ( int i = 0 ; i < j ; i++ )
	{
		if ( 1 == mod )
		{
			str = m_LclCLICommandOpenURLList.GetItemText( i, 0 );
		}
		if ( 2 == mod )
		{
			str = m_LclCLIToGetTheElementFromPage.GetItemText( i, 0 );
		}
		strA = str;
		strAA = strAA + strA + "\r\n";
	}
	j = 0;
	while ( 1 )
	{
		j = strAA.Find( "\r\n\r\n" );
		if ( -1 == j )
		{
			break;;
		}
		strAA.Delete( j , 2 );
	}
	file.Write( strAA.GetBuffer() , strAA.GetLength() );
	file.Close();
	strAA.ReleaseBuffer();

}

void CDlgCommandListInfomation::LoadFileWithList( int mod )
{
	CFileDialog f( TRUE , 0 , _T("") , 4|2 , _T("文本文件(*.txt)|*.txt||") );
	if ( IDOK != f.DoModal() )
	{
		return ;
	}
	if ( IDOK != MessageBox( _T("是否确定读取，原有列表将被清空") , _T("要慎重") , MB_OKCANCEL ) )
	{
		return;
	}
	CString str = f.GetPathName();
	if ( 1 == mod )
	{
		m_EdtCLICommandOpenURLLoadFromFile.SetWindowText( str );
	}
	if ( 2 == mod )
	{
		m_EdtCLIToGetTheElenentLoadFromFile.SetWindowText( str );
	}

	CFile file( str , CFile::modeRead );
	if ( file == NULL )
	{
		MessageBox( _T("文件不存在") , _T("...") );
		return ;
	}
	int lenth = (int)file.GetLength();
	if ( 0 == lenth )
	{
		MessageBox( _T("文件不存在或无法读取文件内容") , _T("") );
		return;
	}
	char * nstr = (char*) malloc( lenth + 1);
	file.Read( nstr , lenth );
	nstr[lenth] = '\0';
	str = nstr;
	while ( 1 )
	{
		lenth = str.Find( _T("\r\n\r\n") );
		if ( -1 == lenth )
		{
			break;;
		}
		str.Delete( lenth , 2 );
	}

	while ( 1 )
	{
		lenth = str.Find( _T("\r\n") );
		if ( str.GetLength() <= 2 )
		{
			break ;
		}
		if ( 1 == mod )
		{
			m_LclCLICommandOpenURLList.InsertItem( 0 , str.Left( lenth ) );
		}
		if ( 2 == mod )
		{
			m_LclCLIToGetTheElementFromPage.InsertItem( 0 , str.Left( lenth ) );
		}
		str.Delete( 0 , lenth + 2 );
	}

	if ( 2 == mod )
	{
		str.Format( _T("%d") , m_LclCLIToGetTheElementFromPage.GetItemCount() );
		m_StcCLIElementListCount.SetWindowText( str );
	}

	file.Close();
	free ( nstr );

}

void CDlgCommandListInfomation::OnBnClickedButtonCliTheElementFromPageDeleteAll()
{
	// TODO: 在此添加控件通知处理程序代码
	m_LclCLIToGetTheElementFromPage.DeleteAllItems();
}

void CDlgCommandListInfomation::OnBnClickedButtonCliTheElementFromPageDeleteTheSame()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( m_LclCLIToGetTheElementFromPage.GetItemCount() > 500 )
	{
		if ( IDOK == MessageBox( _T("数量太多，最好别这么干") , _T("电脑容易卡住") , MB_OKCANCEL ) )
		{
			return;
		}
	}
}
