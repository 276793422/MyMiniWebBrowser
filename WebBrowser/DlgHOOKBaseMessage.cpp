//////////////////////////////////////////////////////////////////////////
//
//	DlgHOOKBaseMessage.cpp
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
// DialogHOOKBaseMessage.cpp : 实现文件
//

#include "stdafx.h"
#include "HTML.h"
#include "DlgHOOKBaseMessage.h"

#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")


int WSAAPI HOOK_send( IN SOCKET s , char FAR * buf , IN int len , IN int flags );
int WSAAPI HOOK_recv( IN SOCKET s , char FAR * buf , IN int len , IN int flags );
int WSAAPI HOOK_WSASend( SOCKET s , LPWSABUF lpBuffers , DWORD dwBufferCount , LPDWORD lpNumberOfBytesSent ,
						DWORD dwFlags , LPWSAOVERLAPPED lpOverlapped , LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine );
int WSAAPI HOOK_WSARecv( SOCKET s , LPWSABUF lpBuffers ,	DWORD dwBufferCount , LPDWORD lpNumberOfBytesRecvd,
						LPDWORD lpFlags , LPWSAOVERLAPPED lpOverlapped ,LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine );

static CDlgHOOKBaseMessage *g_this;

// CDialogHOOKBaseMessage 对话框

IMPLEMENT_DYNAMIC(CDlgHOOKBaseMessage, CDialog)

CDlgHOOKBaseMessage::CDlgHOOKBaseMessage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHOOKBaseMessage::IDD, pParent)
{
	m_infoType = 0;
}

CDlgHOOKBaseMessage::~CDlgHOOKBaseMessage()
{
	DeleteAllParam();
}

void CDlgHOOKBaseMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DIALOG_HOOK_STATUS_ISHOOKING_MSG, m_EdtHOOKStatusIsHOOKing);
	DDX_Control(pDX, IDC_LIST_HOOK_LISTCTRL_GET_MSG_INFO_INDEX, m_ListCtrlInternetInfoIndex);
	DDX_Control(pDX, IDC_EDIT_HOOK_HOOK_MESSAGE_INFOMATION, m_EdtHOOKMessageInfomation);
}


BEGIN_MESSAGE_MAP(CDlgHOOKBaseMessage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DIALOG_HOOK_BUTTON_START_HOOK, &CDlgHOOKBaseMessage::OnBnClickedButtonDialogHookButtonStartHook)
	ON_BN_CLICKED(IDC_BUTTON_DIALOG_HOOK_BUTTON_STOP_HOOK, &CDlgHOOKBaseMessage::OnBnClickedButtonDialogHookButtonStopHook)
	ON_BN_CLICKED(IDC_BUTTON_DIALOG_HOOK_BUTTON_REINIT, &CDlgHOOKBaseMessage::OnBnClickedButtonDialogHookButtonReinit)
	ON_BN_CLICKED(IDC_BUTTON_HOOK_BUTTON_CLEAN_INFO_LIST, &CDlgHOOKBaseMessage::OnBnClickedButtonHookButtonCleanInfoList)
	ON_BN_CLICKED(IDC_BUTTON_DIALOG_HOOK_BUTTON_STOP_HOOK_NOW, &CDlgHOOKBaseMessage::OnBnClickedButtonDialogHookButtonStopHookNow)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_HOOK_LISTCTRL_GET_MSG_INFO_INDEX, &CDlgHOOKBaseMessage::OnNMDblclkListHookListctrlGetMsgInfoIndex)
	ON_BN_CLICKED(IDC_RADIO_HOOK_MAKE_THE_ANSI_STRING_AND_ALL, &CDlgHOOKBaseMessage::OnBnClickedRadioHookMakeTheAnsiStringAndAll)
	ON_BN_CLICKED(IDC_RADIO_HOOK_MAKE_THE_UNICODE_STRING_AND_ALL, &CDlgHOOKBaseMessage::OnBnClickedRadioHookMakeTheUnicodeStringAndAll)
	ON_BN_CLICKED(IDC_RADIO_HOOK_MAKE_THE_ANSI_STRING_NO_OTHER, &CDlgHOOKBaseMessage::OnBnClickedRadioHookMakeTheAnsiStringNoOther)
	ON_BN_CLICKED(IDC_RADIO_HOOK_MAKE_THE_UNICODE_STRING_NO_OTHER, &CDlgHOOKBaseMessage::OnBnClickedRadioHookMakeTheUnicodeStringNoOther)
END_MESSAGE_MAP()

BOOL CDlgHOOKBaseMessage::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	g_this = this;

	int i = m_ListCtrlInternetInfoIndex.GetExtendedStyle();
	m_ListCtrlInternetInfoIndex.SetExtendedStyle( LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | i );

	m_ListCtrlInternetInfoIndex.InsertColumn( 0 , _T("ID") , 0 , 40 );
	m_ListCtrlInternetInfoIndex.InsertColumn( 1 , _T("源地址") , 0 , 140 );
	m_ListCtrlInternetInfoIndex.InsertColumn( 2 , _T("目的地址") , 0 , 140 );
	m_ListCtrlInternetInfoIndex.InsertColumn( 3 , _T("包长") , 0 , 55 );
	m_ListCtrlInternetInfoIndex.InsertColumn( 4 , _T("发收") , 0 , 40 );
	m_ListCtrlInternetInfoIndex.InsertColumn( 5 , _T("时间") , 0 , 150 );
	m_ListCtrlInternetInfoIndex.InsertColumn( 6 , _T("SocketID") , 0 , 70 );

//#ifdef DEBUG
//	for ( int i = 0 ; i < 60 ; i++ )
//	{
//		m_ListCtrlInternetInfoIndex.InsertItem( i , _T("1000") );
//		m_ListCtrlInternetInfoIndex.SetItemText( i , 1 , _T("255.255.255.255:65535") );
//		m_ListCtrlInternetInfoIndex.SetItemText( i , 2 , _T("255.255.255.255:65535") );
//		m_ListCtrlInternetInfoIndex.SetItemText( i , 3 , _T("65535") );
//		m_ListCtrlInternetInfoIndex.SetItemText( i , 4 , _T("  收") );
//		m_ListCtrlInternetInfoIndex.SetItemText( i , 5 , _T("2011-12-31 15:36:40.999") );
//	}
//#endif

	if ( HookInitFun() )
	{
		GetDlgItem( IDC_BUTTON_DIALOG_HOOK_BUTTON_STOP_HOOK )->EnableWindow( FALSE );
		GetDlgItem( IDC_BUTTON_DIALOG_HOOK_BUTTON_START_HOOK )->EnableWindow( FALSE );
		GetDlgItem( IDC_BUTTON_DIALOG_HOOK_BUTTON_STOP_HOOK_NOW )->EnableWindow( FALSE );
		return 1;
	}

	CheckRadioButton( IDC_RADIO_HOOK_MAKE_THE_UNICODE_STRING_AND_ALL , IDC_RADIO_HOOK_MAKE_THE_ANSI_STRING_NO_OTHER , IDC_RADIO_HOOK_MAKE_THE_ANSI_STRING_AND_ALL );

	GetDlgItem( IDC_BUTTON_DIALOG_HOOK_BUTTON_REINIT )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_DIALOG_HOOK_BUTTON_STOP_HOOK )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_DIALOG_HOOK_BUTTON_STOP_HOOK_NOW )->EnableWindow( FALSE );

	HookInitFun();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// CDialogHOOKBaseMessage 消息处理程序

//	ANSI 输出所有信息
void CDlgHOOKBaseMessage::OnBnClickedRadioHookMakeTheAnsiStringAndAll()
{
	// TODO: 在此添加控件通知处理程序代码
	m_infoType = 0;
}

//	UNICODE 输出所有信息
void CDlgHOOKBaseMessage::OnBnClickedRadioHookMakeTheUnicodeStringAndAll()
{
	// TODO: 在此添加控件通知处理程序代码
	m_infoType = 1;
}

//	ANSI 输出字符串信息
void CDlgHOOKBaseMessage::OnBnClickedRadioHookMakeTheAnsiStringNoOther()
{
	// TODO: 在此添加控件通知处理程序代码
	m_infoType = 2;
}

//	UNICODE 输出字符串信息
void CDlgHOOKBaseMessage::OnBnClickedRadioHookMakeTheUnicodeStringNoOther()
{
	// TODO: 在此添加控件通知处理程序代码
	m_infoType = 3;
}

void CDlgHOOKBaseMessage::OnBnClickedButtonDialogHookButtonStartHook()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = 0;
	m_HookStruct[SEND].srcFunction = GetProcAddress( LoadLibraryA("WS2_32.dll") , "send" );
	m_HookStruct[SEND].destFunction = HOOK_send;
	ret = HookWin32ApiS( &(m_HookStruct[SEND]) );
	if ( ret )
	{
		m_EdtHOOKStatusIsHOOKing.SetWindowText( _T("启动抓包失败") );
		return ;
	}
	m_HookStruct[RECV].srcFunction = GetProcAddress( LoadLibraryA("WS2_32.dll") , "recv" );
	m_HookStruct[RECV].destFunction = HOOK_recv;
	ret = HookWin32ApiS( &(m_HookStruct[RECV]) );
	if ( ret )
	{
		m_EdtHOOKStatusIsHOOKing.SetWindowText( _T("启动抓包失败") );
		return ;
	}
	m_HookStruct[WSASEND].srcFunction = GetProcAddress( LoadLibraryA("WS2_32.dll") , "WSASend" );
	m_HookStruct[WSASEND].destFunction = HOOK_WSASend;
	ret = HookWin32ApiS( &(m_HookStruct[WSASEND]) );
	if ( ret )
	{
		m_EdtHOOKStatusIsHOOKing.SetWindowText( _T("启动抓包失败") );
		return ;
	}
	m_HookStruct[WSARECV].srcFunction = GetProcAddress( LoadLibraryA("WS2_32.dll") , "WSARecv" );
	m_HookStruct[WSARECV].destFunction = HOOK_WSARecv;
	ret = HookWin32ApiS( &(m_HookStruct[WSARECV]) );
	if ( ret )
	{
		m_EdtHOOKStatusIsHOOKing.SetWindowText( _T("启动抓包失败") );
		return ;
	}

	GetDlgItem( IDC_BUTTON_DIALOG_HOOK_BUTTON_STOP_HOOK )->EnableWindow( TRUE );
	GetDlgItem( IDC_BUTTON_DIALOG_HOOK_BUTTON_STOP_HOOK_NOW )->EnableWindow( TRUE );
	GetDlgItem( IDC_BUTTON_DIALOG_HOOK_BUTTON_START_HOOK )->EnableWindow( FALSE );
	m_EdtHOOKStatusIsHOOKing.SetWindowText( _T("启动抓包成功") );
	m_nListIndex = m_ListCtrlInternetInfoIndex.GetItemCount();
}

void CDlgHOOKBaseMessage::OnBnClickedButtonDialogHookButtonStopHook()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret = 0;
	ret = UnHookWin32ApiS( &(m_HookStruct[SEND]) );
	if ( ret )
	{
		m_EdtHOOKStatusIsHOOKing.SetWindowText( _T("停止抓包失败") );
		return ;
	}
	ret = UnHookWin32ApiS( &(m_HookStruct[RECV]) );
	if ( ret )
	{
		m_EdtHOOKStatusIsHOOKing.SetWindowText( _T("停止抓包失败") );
		return ;
	}
	ret = UnHookWin32ApiS( &(m_HookStruct[WSASEND]) );
	if ( ret )
	{
		m_EdtHOOKStatusIsHOOKing.SetWindowText( _T("停止抓包失败") );
		return ;
	}
	ret = UnHookWin32ApiS( &(m_HookStruct[WSARECV]) );
	if ( ret )
	{
		m_EdtHOOKStatusIsHOOKing.SetWindowText( _T("停止抓包失败") );
		return ;
	}

	GetDlgItem( IDC_BUTTON_DIALOG_HOOK_BUTTON_STOP_HOOK )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_DIALOG_HOOK_BUTTON_STOP_HOOK_NOW )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_DIALOG_HOOK_BUTTON_START_HOOK )->EnableWindow( TRUE );
	m_EdtHOOKStatusIsHOOKing.SetWindowText( _T("抓包功能停止") );
}

void CDlgHOOKBaseMessage::OnBnClickedButtonDialogHookButtonReinit()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( HookInitFun() )
	{
		//return ;
	}

	GetDlgItem( IDC_BUTTON_DIALOG_HOOK_BUTTON_STOP_HOOK )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_DIALOG_HOOK_BUTTON_STOP_HOOK_NOW )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_DIALOG_HOOK_BUTTON_START_HOOK )->EnableWindow( TRUE );
}

void CDlgHOOKBaseMessage::OnBnClickedButtonDialogHookButtonStopHookNow()
{
	// TODO: 在此添加控件通知处理程序代码

	GetDlgItem( IDC_BUTTON_DIALOG_HOOK_BUTTON_STOP_HOOK )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_DIALOG_HOOK_BUTTON_STOP_HOOK_NOW )->EnableWindow( FALSE );
	GetDlgItem( IDC_BUTTON_DIALOG_HOOK_BUTTON_START_HOOK )->EnableWindow( TRUE );
}

void CDlgHOOKBaseMessage::OnBnClickedButtonHookButtonCleanInfoList()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ListCtrlInternetInfoIndex.DeleteAllItems();
	DeleteAllParam();
	m_nListIndex = 0;
}

UINT CDlgHOOKBaseMessage::SendTODO( IN SOCKET s , char FAR * buf , IN int len , IN int flags )
{
	SYSTEMTIME systime;
	CString str;
	CString strT;
	int i ;
	sockaddr_in sk;
	int t ;
	SMySocketParam *param;

	i = m_nListIndex ;//m_ListCtrlInternetInfoIndex.GetItemCount();
	m_nListIndex++;

	param = (SMySocketParam *)malloc( sizeof(SMySocketParam) );
	param->m_index = i;
	param->m_lenth = len;
	param->m_buf = (char *)malloc( len + 1 );
	memcpy_s( param->m_buf , len , buf , len );
	param->m_buf[len] = '\0';
	m_listMyListTable.AddItem( param );

	// 设置当前包ID
	str.Format( _T("%d") , i );
	m_ListCtrlInternetInfoIndex.InsertItem( i , str );

	// 发送到的位置
	t = sizeof(sk);
	getpeername( s , (sockaddr*)&sk , &t );
	strT = inet_ntoa( sk.sin_addr );
	str.Format( _T("%s:%d") , strT , ntohs( sk.sin_port ) );
	m_ListCtrlInternetInfoIndex.SetItemText( i , 2 , str );

	// 写出包长
	str.Format( _T("%d") , len );
	m_ListCtrlInternetInfoIndex.SetItemText( i , 3 , str );

	// 收/发
	m_ListCtrlInternetInfoIndex.SetItemText( i , 4 , _T("发  ") );

	// 设置时间
	GetSystemTime( &systime );
	str.Format( _T("%d-%d-%d %d:%d:%d.%d") , systime.wYear , systime.wMonth , systime.wDay ,
								systime.wHour , systime.wMinute , systime.wSecond , systime.wMilliseconds );
	m_ListCtrlInternetInfoIndex.SetItemText( i , 5 , str );

	// 设置SocketID
	str.Format( _T("%08x") , s );
	m_ListCtrlInternetInfoIndex.SetItemText( i , 6 , str );

	m_ListCtrlInternetInfoIndex.SendMessage( WM_VSCROLL , SB_BOTTOM , 0 );
	{
		char ch = buf[len - 1];
		buf[len-1] = '\0';
		char * def = strstr( buf , "Accept-Encoding:" );
		if ( 0 == def )
		{
			return 0;
		}
		char * def2 = strstr( def , "\r\n" );
		buf[len-1] = ch;
		memmove_s( def , len , def2+2 , len - ( def2 - buf + 2 ) );
	}
	return 0;
}

UINT CDlgHOOKBaseMessage::RecvTODO( IN SOCKET s , char FAR * buf , IN int len , IN int flags )
{
	SYSTEMTIME systime;
	CString str;
	CString strT;
	int i ;
	sockaddr_in sk;
	int t ;
	SMySocketParam *param;

	i = m_nListIndex ;//m_ListCtrlInternetInfoIndex.GetItemCount();
	m_nListIndex++;

	param = (SMySocketParam *)malloc( sizeof(SMySocketParam) );
	param->m_index = i;
	param->m_lenth = len;
	param->m_buf = (char *)malloc( len + 1 );
	memcpy_s( param->m_buf , len , buf , len );
	param->m_buf[len] = '\0';
	m_listMyListTable.AddItem( param );

	// 设置当前包ID
	str.Format( _T("%d") , i );
	m_ListCtrlInternetInfoIndex.InsertItem( i , str );

	// 从哪里来的
	t = sizeof(sk);
	getpeername( s , (sockaddr*)&sk , &t );
	strT = inet_ntoa( sk.sin_addr );
	str.Format( _T("%s:%d") , strT , ntohs( sk.sin_port ) );
	m_ListCtrlInternetInfoIndex.SetItemText( i , 1 , str );


	// 写出包长
	str.Format( _T("%d") , len );
	m_ListCtrlInternetInfoIndex.SetItemText( i , 3 , str );

	// 收/发
	m_ListCtrlInternetInfoIndex.SetItemText( i , 4 , _T("  收") );

	// 设置时间
	GetSystemTime( &systime );
	str.Format( _T("%d-%d-%d %d:%d:%d.%d") , systime.wYear , systime.wMonth , systime.wDay ,
								systime.wHour , systime.wMinute , systime.wSecond , systime.wMilliseconds );
	m_ListCtrlInternetInfoIndex.SetItemText( i , 5 , str );

	// 设置SocketID
	str.Format( _T("%08x") , s );
	m_ListCtrlInternetInfoIndex.SetItemText( i , 6 , str );

	m_ListCtrlInternetInfoIndex.SendMessage( WM_VSCROLL , SB_BOTTOM , 0 );
	return 0;
}

int WSAAPI HOOK_send( IN SOCKET s , char FAR * buf , IN int len , IN int flags )
{
	int ret = 0;
	typedef int (WSAAPI * Fun)( IN SOCKET , char FAR * , IN int , IN int );
	g_this->SendTODO( s , buf , len , flags );

	return ((Fun)(g_this->m_HookStruct[g_this->SEND].newFunction))( s , buf , len , flags );
}

int WSAAPI HOOK_recv( IN SOCKET s , char FAR * buf , IN int len , IN int flags )
{
	int ret = 0;
	typedef int (WSAAPI * Fun)( IN SOCKET , char FAR * , IN int , IN int );
	ret = ((Fun)(g_this->m_HookStruct[g_this->RECV].newFunction))( s , buf , len , flags );

	g_this->RecvTODO( s , buf , len , flags );
	return ret;
}

int WSAAPI HOOK_WSASend( SOCKET s , LPWSABUF lpBuffers , DWORD dwBufferCount , LPDWORD lpNumberOfBytesSent ,
		DWORD dwFlags , LPWSAOVERLAPPED lpOverlapped , LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine )
{
	int ret = 0;
	typedef int (WSAAPI * Fun)( SOCKET , LPWSABUF , DWORD , LPDWORD , DWORD , LPWSAOVERLAPPED , LPWSAOVERLAPPED_COMPLETION_ROUTINE );
	g_this->SendTODO( s , lpBuffers->buf , lpBuffers->len , dwFlags );

	ret = ((Fun)(g_this->m_HookStruct[g_this->WSASEND].newFunction))( s , lpBuffers , dwBufferCount , lpNumberOfBytesSent , dwFlags , lpOverlapped , lpCompletionRoutine );
	return ret;
}

int WSAAPI HOOK_WSARecv( SOCKET s , LPWSABUF lpBuffers ,	DWORD dwBufferCount , LPDWORD lpNumberOfBytesRecvd,
			LPDWORD lpFlags , LPWSAOVERLAPPED lpOverlapped ,LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine )
{
	int ret = 0;
	typedef int (WSAAPI * Fun)( SOCKET , LPWSABUF , DWORD , LPDWORD , LPDWORD , LPWSAOVERLAPPED , LPWSAOVERLAPPED_COMPLETION_ROUTINE );
	ret = ((Fun)(g_this->m_HookStruct[g_this->WSARECV].newFunction))( s , lpBuffers , dwBufferCount , lpNumberOfBytesRecvd , lpFlags , lpOverlapped , lpCompletionRoutine );

	if ( WSA_WAIT_FAILED == ret )
	{
		return ret;
	}
	if ( 0 == *lpNumberOfBytesRecvd )
	{
		return ret;
	}
	g_this->RecvTODO( s , lpBuffers->buf , *lpNumberOfBytesRecvd , *lpFlags );
	return ret;
}

UINT CDlgHOOKBaseMessage::HookInitFun()
{
	m_EdtHOOKStatusIsHOOKing.SetWindowText( _T("初始化抓包成功") );
	return 0;
}

// 清空参数列表
UINT CDlgHOOKBaseMessage::DeleteAllParam()
{
	m_listMyListTable.MakeEmpty( 1 );
	return 0;
}
void CDlgHOOKBaseMessage::OnNMDblclkListHookListctrlGetMsgInfoIndex(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	SMySocketParam * param;
	int ncur = pNMItemActivate->iItem;
	int l = m_listMyListTable.GetCount();
	for ( int i = 0 ; i < l ; i++ )
	{
		param = m_listMyListTable[i];
		if ( param->m_index == ncur )
		{
			break;
		}
	}
	if ( param->m_index != ncur )
	{
		return;
	}

	MakeHookInfomation( param );

	*pResult = 0;
}

UINT CDlgHOOKBaseMessage::MakeHookInfomation( SMySocketParam *ssp )
{
	//m_EdtHOOKMessageInfomation.SetWindowText( L"00000001      00 11 22 33 44 55 66 77 88 99 AA BB CC DD EE FF      123456789ABCDEF\r\n00000001      00 11 22 33 44 55 66 77 88 99 AA BB CC DD EE FF      123456789ABCDEF" );
	CString strCode;
	switch( m_infoType )
	{
	case 0:		// ANSI
		MakeInfomationANSI( ( unsigned char * ) ssp->m_buf , ssp->m_lenth , strCode );
		break;
	case 1:		// UNICODE
		MakeInfomationUNICODE( ( unsigned char * ) ssp->m_buf , ssp->m_lenth , strCode );
		break;
	case 2:		// ANSI String
		MakeInfomationANSIString( ( unsigned char * ) ssp->m_buf , ssp->m_lenth , strCode );
		break;
	case 3:		// UNICODE String
		MakeInfomationUNICODEString( ( unsigned char * ) ssp->m_buf , ssp->m_lenth , strCode );
		break;
	default:
		break;
	}
	m_EdtHOOKMessageInfomation.SetWindowText( strCode );
	return 0;
}

UINT CDlgHOOKBaseMessage::MakeInfomationANSI( unsigned char * buf , int len , CString &strCode )
{
	unsigned char * strt ;
	int lent = len;
	int i = 0;
	int j = 0;
	int k = 0;
	int t = 0;
	int s = 0;
	int e = 0;
	CString str;
	CString strCharType;
	CString strct;
	strCharType = L"`1234567890-=\\~!@#$%^&*()_+|[];',./{}:\"<>?qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM ";
	j = len / 16;
	k = len % 16;
	for ( i = 0 ; i < j ; i++ )
	{
		strt = buf + i*16;
		str.Format( L"%08x      %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x      ",//%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c" , 
					 i*16 , strt[0] , strt[1] , strt[2] , strt[3] , strt[4] , strt[5] , strt[6] , strt[7] ,
							strt[8] , strt[9] , strt[10], strt[11], strt[12], strt[13], strt[14], strt[15]/*,
							strt[0] , strt[1] , strt[2] , strt[3] , strt[4] , strt[5] , strt[6] , strt[7] ,
							strt[8] , strt[9] , strt[10], strt[11], strt[12], strt[13], strt[14], strt[15] */);
		for ( s = 0 ; s < 16 ; s++ )
		{
			if ( '\0' == strt[s] )
			{
				strct = L".";
			}
			else
			{
				strct.Format( L"%c" , strt[s] );
			}
			str += strct;
		}
		for ( s = 0 , e = str.GetLength(); s < e ; s++  )
		{
			if ( -1 == strCharType.Find( str[s] ) )
			{
				str.SetAt( s , '.' );
			}
		}
		str += L"\r\n";
		strCode += str;
	}
	if ( 0 != k )
	{
		strct = L"";
		char strsp[54];
		memset( strsp , ' ' , 54 );
		strsp[53] = '\0';
		strt = buf + i*16;
		str.Format( L"%08x      " , i*16 );
		strct += str;
		for ( i = 0 ; i < k ; i++ )
		{
			str.Format( L"%02x " , strt[i] );
			strct += str;
		}
		strsp[ (3*(16-k))+5 ] = '\0';
		strct += strsp;
		for ( i = 0 ; i < k ; i++ )
		{
			if ( '\0' == strt[i] )
			{
				str = L".";
			}
			else
			{
				str.Format( L"%c" , strt[i] );
			}
			strct += str;
		}
		for ( int s = 0 , e = strct.GetLength(); s < e ; s++  )
		{
			if ( -1 == strCharType.Find( strct[s] ) )
			{
				strct.SetAt( s , '.' );
			}
		}
		//str += L" \r\n";
		strCode += strct;
	}

	return 0;
}

UINT CDlgHOOKBaseMessage::MakeInfomationUNICODE( unsigned char * buf , int len , CString &strCode )
{
	return 0;
}

UINT CDlgHOOKBaseMessage::MakeInfomationANSIString( unsigned char * buf , int len , CString &strCode )
{
	CString str;
	int i = 0;
	for ( i = 0 ; i < len ; i++ )
	{
		if ( '\0' == buf[i] )
		{
			str = L".";
		}
		else
		{
			str.Format( L"%c" , buf[i] );
		}
		strCode += str;
	}
	return 0;
}

UINT CDlgHOOKBaseMessage::MakeInfomationUNICODEString( unsigned char * buf , int len , CString &strCode )
{
	return 0;
}