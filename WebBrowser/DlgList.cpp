//////////////////////////////////////////////////////////////////////////
//
//	DlgList.cpp
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
// DlgList.cpp : 实现文件
//

#include "stdafx.h"
#include "HTML.h"
#include "DlgList.h"
#include "HTMLDlg.h"


// CDlgList 对话框

IMPLEMENT_DYNAMIC(CDlgList, CDialog)

CDlgList::CDlgList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgList::IDD, pParent)
{
	m_nCommandWorkStatus = 0;
	m_nCommandClick[0] = -1;
	m_nCommandClick[1] = -1;
}

CDlgList::~CDlgList()
{
}

void CDlgList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_KEY_NAME_EDIT_TO_LIST, m_EdtName);
	DDX_Control(pDX, IDC_EDIT_KEY_WORD_EDIT_TO_LIST, m_EdtNum);
	DDX_Control(pDX, IDC_LIST_KEY_NAME_LIST, m_LBX[0]);
	DDX_Control(pDX, IDC_LIST_KEY_WORD_LIST, m_LBX[1]);
	DDX_Control(pDX, IDC_EDIT_RECORD_URL, m_EdtRecordURL);
	DDX_Control(pDX, IDC_EDIT_RECORD_TIME, m_EdtRecordTime);
	DDX_Control(pDX, IDC_LIST_COMMAND_INSTRUCT_LIST, m_LclCmd[0]);
	DDX_Control(pDX, IDC_LIST_COMMADN_INSTRUCT_LIST_FROM, m_LclCmd[1]);
	DDX_Control(pDX, IDC_EDIT_COMMAND_LEFT_LIST_CLICK_TEXT, m_EdtCommandClick[0]);
	DDX_Control(pDX, IDC_EDIT_COMMAND_RIGHT_LIST_CLICK_TEXT, m_EdtCommandClick[1]);
	DDX_Control(pDX, IDC_EDIT_COMMAND_ATTACH_MESSAGE, m_EdtCommandAttachMessage);
	DDX_Control(pDX, IDC_EDIT_COMMAND_THREAD_TEXT_OUT, m_EdtCommandThreadTextOut);
	DDX_Control(pDX, IDC_LIST_OPENED_PAGE_URL_ONLY_OPEN, m_LclOpenedPageUrl);
}


BEGIN_MESSAGE_MAP(CDlgList, CDialog)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_OPENED_PAGE_URL_ONLY_OPEN, &CDlgList::OnNMDblclkListOpenedPageUrlOnlyOpen)
	ON_NOTIFY(NM_CLICK, IDC_LIST_COMMADN_INSTRUCT_LIST_FROM, &CDlgList::OnNMClickListCommadnInstructListFrom)
	ON_NOTIFY(NM_CLICK, IDC_LIST_COMMAND_INSTRUCT_LIST, &CDlgList::OnNMClickListCommandInstructList)
	ON_LBN_SELCHANGE(IDC_LIST_KEY_NAME_LIST, &CDlgList::OnLbnSelchangeList0)
	ON_LBN_SELCHANGE(IDC_LIST_KEY_WORD_LIST, &CDlgList::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_INSERT_TO_TOW_LIST, &CDlgList::OnBnClickedInsertToTowList)
	ON_BN_CLICKED(IDC_DELETE_ONE_IN_TOW_LIST, &CDlgList::OnBnClickedDeleteOneInTowList)
	ON_BN_CLICKED(IDC_DELETE_ALL_IN_THE_TOW_LIST, &CDlgList::OnBnClickedDeleteAllInTheTowList)
	ON_BN_CLICKED(IDC_BUTTON_COMMAND_MAKE_IT_WORK, &CDlgList::OnBnClickedButtonCommandMakeItWork)
	ON_BN_CLICKED(IDC_BUTTON_COMMAND_STOP_IT_WORK, &CDlgList::OnBnClickedButtonCommandStopItWork)
	ON_BN_CLICKED(IDC_BUTTON_COMMAND_PAUSE_IT_WORD, &CDlgList::OnBnClickedButtonCommandPauseItWord)
	ON_BN_CLICKED(IDC_BUTTON_COMMAND_INSERT_FROM_RIGHT_TO_LEFT, &CDlgList::OnBnClickedButtonCommandInsertFromRightToLeft)
	ON_BN_CLICKED(IDC_BUTTON_COMMAND_DELETE_ITEM_IN_LEFT, &CDlgList::OnBnClickedButtonCommandDeleteItemInLeft)
	ON_BN_CLICKED(IDC_BUTTON_COMMAND_CHANGE_ATTACH_MESSAGE, &CDlgList::OnBnClickedButtonCommandChangeAttachMessage)
	ON_BN_CLICKED(IDC_BUTTON_COMMAND_MAKE_LIST_ITEM_UP, &CDlgList::OnBnClickedButtonCommandMakeListItemUp)
	ON_BN_CLICKED(IDC_BUTTON_COMMAND_MAKE_LIST_ITEM_DOWN, &CDlgList::OnBnClickedButtonCommandMakeListItemDown)
	ON_BN_CLICKED(IDC_BUTTON_COMMAND_CLEAR_TEXT_OUT_EDIT, &CDlgList::OnBnClickedButtonCommandClearTextOutEdit)
	ON_BN_CLICKED(IDC_BUTTON_COMMAND_CLEAR_LEFT_LIST, &CDlgList::OnBnClickedButtonCommandClearLeftList)
	ON_BN_CLICKED(IDC_BUTTON_COMMAND_DEFAULT_WITH_LEFT, &CDlgList::OnBnClickedButtonCommandDefaultWithLeft)
END_MESSAGE_MAP()


// CDlgList 消息处理程序

void CDlgList::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnCancel();
}

void CDlgList::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

BOOL CDlgList::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_LclCmd[0].InsertColumn( 0 , _T("序号") , LVCFMT_LEFT , 40 );
	m_LclCmd[0].InsertColumn( 1 , _T("指令解释") , LVCFMT_LEFT , 120 );
	m_LclCmd[0].InsertColumn( 2 , _T("附加信息") , LVCFMT_LEFT , 120 );
	m_LclCmd[0].SetExtendedStyle( LVS_EX_FULLROWSELECT );
	m_LclCmd[1].InsertColumn( 0 , _T("序号") , LVCFMT_LEFT , 40 );
	m_LclCmd[1].InsertColumn( 1 , _T("指令解释") , LVCFMT_LEFT , 160 );
	m_LclCmd[1].SetExtendedStyle( LVS_EX_FULLROWSELECT );
	m_LclOpenedPageUrl.InsertColumn( 0 , _T("ID") , LVCFMT_LEFT , 32 );
	m_LclOpenedPageUrl.InsertColumn( 1 , _T("打开过的网址") , LVCFMT_LEFT , 220 );
	m_LclOpenedPageUrl.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	m_LclOpenedPageUrl.InsertItem( 0 , _T("0") );
	m_LclOpenedPageUrl.SetItemText( 0 , 1 , _T("双击清空该表") );


	GetDlgItem( IDC_BUTTON_COMMAND_STOP_IT_WORK )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_COMMAND_PAUSE_IT_WORD )->EnableWindow( FALSE );

	OnInitCommandList();
	m_InstructTAR.m_pWorkThread = &m_ThreadCommandWork;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgList::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	OnBnClickedButtonCommandStopItWork();
}


//名字ListBox
void CDlgList::OnLbnSelchangeList0()
{
	// TODO: 在此添加控件通知处理程序代码
	m_LBX[1].SetCurSel( m_LBX[0].GetCurSel() );
}

//数据ListBox
void CDlgList::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_LBX[0].SetCurSel( m_LBX[1].GetCurSel() );
}

void CDlgList::OnBnClickedInsertToTowList()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_EdtName.GetWindowText( str );
	if ( str.IsEmpty() )
	{
		MessageBox( _T("键名不可以为空") , _T("") );
		return;
	}
	m_LBX[0].AddString( str );
	m_EdtNum.GetWindowText( str );
	m_LBX[1].AddString( str );
}

void CDlgList::OnBnClickedDeleteOneInTowList()
{
	// TODO: 在此添加控件通知处理程序代码
	int i = m_LBX[0].GetCurSel();
	int j = m_LBX[1].GetCurSel();
	if ( ( i != j ) || ( i == -1 ) || ( j == -1 ) )
	{
		MessageBox( _T("需要你选择一个正确的") , _T("") );
		return ;
	}
	if ( i == j )
	{
		if ( IDOK == MessageBox( _T("是否确定删除") , _T("最后提醒你一次") , MB_OKCANCEL ) )
		{
			m_LBX[0].DeleteString(i);
			m_LBX[1].DeleteString(j);
		}
	}
}

void CDlgList::OnBnClickedButtonCommandClearLeftList()
{
	// TODO: 在此添加控件通知处理程序代码
	m_LclCmd[0].DeleteAllItems();
}

void CDlgList::OnBnClickedDeleteAllInTheTowList()
{
	// TODO: 在此添加控件通知处理程序代码
	m_LBX[0].ResetContent();
	m_LBX[1].ResetContent();
}

//当前界面按钮全部禁用、解禁
void CDlgList::SetDialogEnableWindow( int i )
{
	//主界面按钮全部禁用、解禁
	((CHTMLDlg*)m_pParent)->SetDialogEnableWindow( i );

	GetDlgItem( IDC_BUTTON_COMMAND_MAKE_IT_WORK )->EnableWindow( i );
	GetDlgItem( IDC_BUTTON_COMMAND_STOP_IT_WORK )->EnableWindow( !i );
	GetDlgItem( IDC_BUTTON_COMMAND_PAUSE_IT_WORD )->EnableWindow( !i );

	GetDlgItem( IDC_INSERT_TO_TOW_LIST )->EnableWindow( i );
	GetDlgItem( IDC_DELETE_ONE_IN_TOW_LIST )->EnableWindow( i );
	GetDlgItem( IDC_DELETE_ALL_IN_THE_TOW_LIST )->EnableWindow( i );

	GetDlgItem( IDC_BUTTON_COMMAND_INSERT_FROM_RIGHT_TO_LEFT )->EnableWindow( i );
	GetDlgItem( IDC_BUTTON_COMMAND_DELETE_ITEM_IN_LEFT )->EnableWindow( i );
	GetDlgItem( IDC_BUTTON_COMMAND_CHANGE_ATTACH_MESSAGE )->EnableWindow( i );
	GetDlgItem( IDC_BUTTON_COMMAND_MAKE_LIST_ITEM_UP )->EnableWindow( i );
	GetDlgItem( IDC_BUTTON_COMMAND_MAKE_LIST_ITEM_DOWN )->EnableWindow( i );
	GetDlgItem( IDC_BUTTON_COMMAND_CLEAR_LEFT_LIST )->EnableWindow( i );
	GetDlgItem( IDC_BUTTON_COMMAND_DEFAULT_WITH_LEFT )->EnableWindow( i );
}

//开始
void CDlgList::OnBnClickedButtonCommandMakeItWork()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( 1 == m_nCommandWorkStatus )
	{
		return;
	}
	if ( 0 != TestCommandListItemLegal() )
	{
		return;
	}
	if ( IDOK != MessageBox( _T("一旦开启自动，所有状态将被还原，所有按钮被禁用。") , _T("确定自动？") , MB_OKCANCEL ) )
	{
		return;
	}
	

	m_nCommandWorkStatus = 1;

	((CHTMLDlg*)m_pParent)->KillTimer(10002);
	SetDialogEnableWindow( 0 );

	m_InstructTAR.m_pParent = m_pParent;
	m_ThreadCommandWork.Create( m_pParent );
	m_ThreadCommandWork.Start();
}

//停止
void CDlgList::OnBnClickedButtonCommandStopItWork()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( 0 == m_nCommandWorkStatus )
	{
		return;
	}
	m_nCommandWorkStatus = 0;

	SetDialogEnableWindow( 1 );

	m_ThreadCommandWork.Stop();
	m_ThreadCommandWork.Clear();
	GetDlgItem( IDC_BUTTON_COMMAND_PAUSE_IT_WORD 
		)->SetWindowText( _T("暂停") );
}

//暂停
void CDlgList::OnBnClickedButtonCommandPauseItWord()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ThreadCommandWork.Pause();

	switch( m_ThreadCommandWork.m_nStatus )
	{
	case CThreadCommandWork::THREAD_PAUSE:
		GetDlgItem( IDC_BUTTON_COMMAND_PAUSE_IT_WORD 
					)->SetWindowText( _T("继续") );
		break;
	case CThreadCommandWork::THREAD_START:
		GetDlgItem( IDC_BUTTON_COMMAND_PAUSE_IT_WORD 
			)->SetWindowText( _T("暂停") );
		break;

	}
}

//显示选中的东西
void CDlgList::SetWindowCommandClickText( int list , int nindex )
{
	m_nCommandClick[list] = nindex ;
	if ( -1 == nindex )
	{
		m_EdtCommandClick[list].SetWindowText( _T("") );
		return;
	}
	CString strA = _T("");
	CString strB;
	strA = m_LclCmd[list].GetItemText( nindex , 0 );
	strB = m_LclCmd[list].GetItemText( nindex , 1 );
	strA = strA + _T("|") + strB;
	if ( 0 == list )
	{
		strB = m_LclCmd[list].GetItemText( nindex , 2 );
		strA = strA + _T("|") + strB;
	}
	m_EdtCommandClick[list].SetWindowText( strA );
}

//左侧控制框，鼠标选了一个东西
void CDlgList::OnNMClickListCommandInstructList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	SetWindowCommandClickText( 0 , pNMItemActivate->iItem );
	*pResult = 0;
}

//右侧控制框，鼠标选了一个东西
void CDlgList::OnNMClickListCommadnInstructListFrom(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	SetWindowCommandClickText( 1 , pNMItemActivate->iItem );

	*pResult = 0;
}

void CDlgList::OnBnClickedButtonCommandInsertFromRightToLeft()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( -1 == m_nCommandClick[1] )
	{
		MessageBox( _T("要添加右表哪个") , _T("咱是不是要选一下") );
		return;
	}
	int i = m_LclCmd[0].GetItemCount();
	CString str;
	str.Format( _T("%d") , i );
	SET_MAIN_INFOMATION(		(m_LclCmd[0]) , (i) , (str) );
	str = m_LclCmd[1].GetItemText( m_nCommandClick[1] , 1 );
	SET_INSTRUCTION_INFOMATION(	(m_LclCmd[0]) , (i) , (str) );
	m_EdtCommandAttachMessage.GetWindowText( str );
	SET_ADDITIONAL_INFOMATION(	(m_LclCmd[0]) , (i) , (str) );
	m_EdtCommandAttachMessage.SetWindowText( _T("") );
}

void CDlgList::OnBnClickedButtonCommandDeleteItemInLeft()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( -1 == m_nCommandClick[0] )
	{
		MessageBox( _T("要删除左表哪个") , _T("咱是不是要选一下") );
		return;
	}
	m_LclCmd[0].DeleteItem( m_nCommandClick[0] );
	int all = m_LclCmd[0].GetItemCount();
	int i = 0;
	CString str;
	for ( i = m_nCommandClick[0] ; i < all ; i++ )
	{
		str.Format( _T("%d") , i );
		m_LclCmd[0].SetItemText( i , 0 , str );
	}
	m_nCommandClick[0] = -1;
}

void CDlgList::OnBnClickedButtonCommandMakeListItemUp()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( -1 == m_nCommandClick[0] )
	{
		MessageBox( _T("要移动哪个") , _T("咱是不是要选一下") );
		return;
	}
	if ( m_nCommandClick[0] == 0 )
	{
		return;
	}
	CString str[2];
	CString strT;
	str[0] = m_LclCmd[0].GetItemText( m_nCommandClick[0] , 1 );
	str[1] = m_LclCmd[0].GetItemText( m_nCommandClick[0] , 2 );

	strT = m_LclCmd[0].GetItemText( m_nCommandClick[0] - 1 , 1 );
	m_LclCmd[0].SetItemText( m_nCommandClick[0] , 1 , strT );
	strT = m_LclCmd[0].GetItemText( m_nCommandClick[0] - 1 , 2 );
	m_LclCmd[0].SetItemText( m_nCommandClick[0] , 2 , strT );

	m_LclCmd[0].SetItemText( m_nCommandClick[0] - 1 , 1 , str[0] );
	m_LclCmd[0].SetItemText( m_nCommandClick[0] - 1 , 2 , str[1] );

	m_nCommandClick[0]--;
}

void CDlgList::OnBnClickedButtonCommandMakeListItemDown()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( -1 == m_nCommandClick[0] )
	{
		MessageBox( _T("要移动哪个") , _T("咱是不是要选一下") );
		return;
	}
	if ( ( m_nCommandClick[0] + 1 ) == m_LclCmd[0].GetItemCount() )
	{
		return;
	}
	CString str[2];
	CString strT;
	str[0] = m_LclCmd[0].GetItemText( m_nCommandClick[0] , 1 );
	str[1] = m_LclCmd[0].GetItemText( m_nCommandClick[0] , 2 );

	strT = m_LclCmd[0].GetItemText( m_nCommandClick[0] + 1 , 1 );
	m_LclCmd[0].SetItemText( m_nCommandClick[0] , 1 , strT );
	strT = m_LclCmd[0].GetItemText( m_nCommandClick[0] + 1 , 2 );
	m_LclCmd[0].SetItemText( m_nCommandClick[0] , 2 , strT );

	m_LclCmd[0].SetItemText( m_nCommandClick[0] + 1 , 1 , str[0] );
	m_LclCmd[0].SetItemText( m_nCommandClick[0] + 1 , 2 , str[1] );

	m_nCommandClick[0]++;
}

void CDlgList::OnBnClickedButtonCommandChangeAttachMessage()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( -1 == m_nCommandClick[0] )
	{
		MessageBox( _T("要修改左表哪个") , _T("咱是不是要选一下") );
		return;
	}
	CString str;
	m_EdtCommandAttachMessage.GetWindowText( str );
	m_LclCmd[0].SetItemText( m_nCommandClick[0] , 2 , str );
	SetWindowCommandClickText( 0 , m_nCommandClick[0] );
	m_EdtCommandAttachMessage.SetWindowText( _T("") );
}

//初始化控制列表
void CDlgList::OnInitCommandList()
{
	CString str;

	for ( int i = 0 ; i < m_InstructTAR.GetInstructNum() ; i++ )
	{
		str.Format( _T("%d") , i );
		SET_MAIN_INFOMATION(		(m_LclCmd[1]) , (i) , (str) );
		str.Format( _T("%d") , m_InstructTAR[i].m_nID );
		SET_INSTRUCTION_INFOMATION(	(m_LclCmd[1]) , (i) , (m_InstructTAR[i].m_StrInstruct) );
	}
}

void CDlgList::OnBnClickedButtonCommandClearTextOutEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	m_EdtCommandThreadTextOut.SetWindowText( _T("") );

	//WinExec( "wscript.exe D:\\1.vbs" , SW_SHOWNORMAL );
}

void CDlgList::SetWindowTextToCommandEdit( CString word )
{
	CString str;
	m_EdtCommandThreadTextOut.GetWindowText( str );
	str = str + _T("\r\n") + word;
	m_EdtCommandThreadTextOut.SetWindowText( str );

	int n = m_EdtCommandThreadTextOut.GetLineCount();
	m_EdtCommandThreadTextOut.SetScrollPos(n,n);
	m_EdtCommandThreadTextOut.LineScroll( n - 1 , 0 ); 
}

UINT CDlgList::TestCommandListItemLegal()
{
	if ( 0 != m_InstructTAR.TestInstruct( &(m_LclCmd[0]) ) )
	{
		MessageBox( m_InstructTAR.GetInstructError() , _T("错了") );
		return 1;
	}
	return 0;
}

void CDlgList::OnBnClickedButtonCommandDefaultWithLeft()
{
	// TODO: 在此添加控件通知处理程序代码
	m_LclCmd[0].DeleteAllItems();
	SET_MAIN_INFOMATION(		(m_LclCmd[0]) , (0) , (_T("0")) );
	SET_INSTRUCTION_INFOMATION(	(m_LclCmd[0]) , (0) , (_T("默认延迟：附加信息为默认延迟时间，单位毫秒，需在整个流程最开始处定义")) );
	SET_ADDITIONAL_INFOMATION(	(m_LclCmd[0]) , (0) , (_T("1000")) );

	SET_MAIN_INFOMATION(		(m_LclCmd[0]) , (1) , (_T("1")) );
	SET_INSTRUCTION_INFOMATION(	(m_LclCmd[0]) , (1) , (_T("设置标志：附加信息为标志，在开始工作之前设置，相同标志，整个程序只能拥有一个")) );
	SET_ADDITIONAL_INFOMATION(	(m_LclCmd[0]) , (1) , (_T("默认标志")) );

	SET_MAIN_INFOMATION(		(m_LclCmd[0]) , (2) , (_T("2")) );
	SET_INSTRUCTION_INFOMATION(	(m_LclCmd[0]) , (2) , (_T("开始工作：工作从此处开始，有且只能有一个")) );
	SET_ADDITIONAL_INFOMATION(	(m_LclCmd[0]) , (2) , (_T("")) );

	SET_MAIN_INFOMATION(		(m_LclCmd[0]) , (3) , (_T("3")) );
	SET_INSTRUCTION_INFOMATION(	(m_LclCmd[0]) , (3) , (_T("结束工作：工作从此处结束，有且只能有一个")) );
	SET_ADDITIONAL_INFOMATION(	(m_LclCmd[0]) , (3) , (_T("")) );

}

void CDlgList::OnNMDblclkListOpenedPageUrlOnlyOpen(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int i = pNMItemActivate->iItem;
	if ( -1 == i )
	{
		return ;
	}
	if ( 0 == i )
	{
		m_LclOpenedPageUrl.DeleteAllItems();
		m_LclOpenedPageUrl.InsertItem( 0 , _T("0") );
		m_LclOpenedPageUrl.SetItemText( 0 , 1 , _T("双击清空该表") );
		return ;
	}
	m_pParent->m_HtmlView->Navigate2( m_LclOpenedPageUrl.GetItemText( i , 1 ) );
	*pResult = 0;
}
