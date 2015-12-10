//////////////////////////////////////////////////////////////////////////
//
//	ThreadRecvEMail.cpp
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "ThreadRecvEMail.h"
#include "DlgEMail.h"




CThreadRecvEMail::CThreadRecvEMail( )
{
	m_HClose = NULL;
	m_pParent = NULL;
	m_Status = 0;
}

CThreadRecvEMail::~CThreadRecvEMail( )
{
	if ( m_HClose != NULL )
	{
		ResetEvent( m_HClose );
		CloseHandle( m_HClose );
		m_HClose = NULL;
	}
}

//等待状态线程
UINT CThreadRecvEMail::ThreadProcWait( LPVOID pParam )
{
	CThreadRecvEMail * pThis = ( CThreadRecvEMail * )pParam;

	CString str;

	pThis->m_pParent->m_StcEMailPOP3ReciverEMailStatus.GetWindowText( str );

	if ( _T("登陆中") == str )
	{
		while ( 1 )
		{
			str = str + _T(".");
			pThis->m_pParent->m_StcEMailPOP3ReciverEMailStatus.SetWindowText( str );
			Sleep( 1000 );
			pThis->m_pParent->m_StcEMailPOP3ReciverEMailStatus.GetWindowText( str );
			if ( _T("登陆中") != str.Left(3) )
			{
				return 0;
			}
			if ( 42 == str.GetLength() )
			{
				str = _T("登陆中");
			}
		}
	}
	if ( _T("收信中") == str )
	{
		while ( 1 )
		{
			str = str + _T(".");
			pThis->m_pParent->m_StcEMailPOP3ReciverEMailStatus.SetWindowText( str );
			Sleep( 1000 );
			pThis->m_pParent->m_StcEMailPOP3ReciverEMailStatus.GetWindowText( str );
			if ( _T("收信中") != str.Left(3) )
			{
				return 0;
			}
			if ( 42 == str.GetLength() )
			{
				str = _T("收信中");
			}
		}
	}
	if ( _T("打开中") == str )
	{
		while ( 1 )
		{
			str = str + _T(".");
			pThis->m_pParent->m_StcEMailPOP3ReciverEMailStatus.SetWindowText( str );
			Sleep( 1000 );
			pThis->m_pParent->m_StcEMailPOP3ReciverEMailStatus.GetWindowText( str );
			if ( _T("打开中") != str.Left(3) )
			{
				return 0;
			}
			if ( 42 == str.GetLength() )
			{
				str = _T("打开中");
			}
		}
	}
	if ( _T("正在获取邮件列表") == str )
	{
		while ( 1 )
		{
			str = str + _T(".");
			pThis->m_pParent->m_StcEMailPOP3ReciverEMailStatus.SetWindowText( str );
			Sleep( 1000 );
			pThis->m_pParent->m_StcEMailPOP3ReciverEMailStatus.GetWindowText( str );
			if ( _T("正在获取邮件列表") != str.Left(8) )
			{
				return 0;
			}
			if ( 37 == str.GetLength() )
			{
				str = _T("正在获取邮件列表");
			}
		}
	}

	return 0;
}

UINT CThreadRecvEMail::ThreadProcNOOP( LPVOID pParam )
{
	CThreadRecvEMail * pThis = ( CThreadRecvEMail * )pParam;
	CString str;

	pThis->m_pParent->MakeButtonStatusR( 1 );

	pThis->m_pParent->m_StcEMailPOP3ReciverEMailStatus.SetWindowText( _T("登陆中") );
	AfxBeginThread( ThreadProcWait , pParam );
	if ( POP_CONNECT_SERVER == pThis->m_pParent->m_Pop3.StartWork( POP_CONNECT_SERVER ) )
	{
		pThis->m_pParent->m_StcEMailPOP3ReciverEMailStatus.SetWindowText( _T("连接服务器失败.") );
		pThis->m_pParent->MakeButtonStatusR( 0 );
		return 0;
	}
	pThis->m_pParent->m_Pop3.StartWork( POP_STAT );
	pThis->m_pParent->m_Pop3.StartWork( POP_TOP );
	pThis->m_pParent->m_StcEMailPOP3ReciverEMailStatus.SetWindowText( _T("登陆完成，等待操作") );
	pThis->m_pParent->m_LclEMailPOP3EMailList.DeleteAllItems();
	for ( UINT i = 1 ; i <= pThis->m_pParent->m_Pop3.GetNumOfEMail() ; i++ )
	{
		str = (CString)( pThis->m_pParent->m_Pop3[ i - 1 ]->strEMailIndex );
		pThis->m_pParent->m_LclEMailPOP3EMailList.InsertItem( i - 1 , str );
		str = (CString)( pThis->m_pParent->m_Pop3[ i - 1 ]->strEMailTop );
		pThis->m_pParent->m_LclEMailPOP3EMailList.SetItemText( i - 1 , 1 , str );
		str = (CString)( pThis->m_pParent->m_Pop3[ i - 1 ]->strEMailLenth );
		pThis->m_pParent->m_LclEMailPOP3EMailList.SetItemText( i - 1 , 2 , str );
	}

	for (  ; pThis->m_Status > 0 ; pThis->m_Status-- )
	{
		Sleep( 5500 );

		if ( WAIT_OBJECT_0 == WaitForSingleObject( pThis->m_HClose , 1 ) )
		{
			break;
		}

		if ( pThis->m_pParent->m_Pop3.StartWork( POP_NOOP ) )
		{
			break;
		}

		if ( WAIT_OBJECT_0 == WaitForSingleObject( pThis->m_HClose , 1 ) )
		{
			break;
		}
	}

	pThis->m_pParent->m_Pop3.StartWork( POP_DISCONNECT_SERVER );
	if ( NULL != pThis->m_HClose )
	{
		ResetEvent( pThis->m_HClose );
		CloseHandle( pThis->m_HClose );
		pThis->m_HClose = NULL;
	}
	pThis->m_pParent->m_LclEMailPOP3EMailList.DeleteAllItems();
	pThis->m_pParent->m_pHtmlView->Navigate2( _T("about:blank") );
	pThis->m_pParent->m_StcEMailPOP3ReciverEMailStatus.SetWindowText( _T("邮件客户端已正常退出，等待操作") );
	if ( 0 == pThis->m_Status )
	{
		pThis->m_pParent->m_StcEMailPOP3ReciverEMailStatus.SetWindowText( _T("七分钟未作操作。邮件客户端已正常退出，等待操作") );
	}

	pThis->m_Status = 0;
	pThis->m_pParent->MakeButtonStatusR( 0 );

	return 0;
}

UINT CThreadRecvEMail::Create( CDlgEMail *parent )
{
	if ( 0 < m_Status )
	{
		return 1;
	}
	if ( NULL != m_HClose )
	{
		ResetEvent( m_HClose );
		CloseHandle( m_HClose );
		m_HClose = NULL;
	}

	m_pParent = parent;
	m_HClose = CreateEvent( 0 , 1 , 0 , 0 );
	return 0;
}

UINT CThreadRecvEMail::StartNOOP()
{
	if ( 0 < m_Status )
	{
		return 1;
	}
	if ( NULL == m_HClose )
	{
		return 2;
	}
	m_Status = 120;
	AfxBeginThread( ThreadProcNOOP , this );
	return 0;
}

UINT CThreadRecvEMail::Stop(  )
{
	if ( 0 == m_Status )
	{
		return 1;
	}
	if ( NULL == m_HClose )
	{
		return 2;
	}
	SetEvent( m_HClose );

	return 0;
}

//打开信线程，还没有写
UINT CThreadRecvEMail::ThreadProcOpen( LPVOID pParam )
{
	CThreadRecvEMail * pThis = ( CThreadRecvEMail * )pParam;


	pThis->m_pParent->m_StcEMailPOP3ReciverEMailStatus.SetWindowText( _T("打开中") );
	AfxBeginThread( ThreadProcWait , pParam );

	CStringA strA;
	CString str;
	pThis->m_pParent->m_EdtEMailPOP3EMailCachePath.GetWindowText( str );

	pThis->m_pParent->m_Pop3.StartWork( POP_RETR , (LPVOID)pThis->m_nOpenIndex );
	strA = pThis->m_pParent->m_Pop3.GetReturn();
	CFile file;
	file.Open( str , CFile::modeCreate | CFile::modeWrite );
	file.Write( strA.GetBuffer() , strA.GetLength() );
	strA.ReleaseBuffer();
	file.Close();
	pThis->m_pParent->m_pHtmlView->Navigate2( str );

	pThis->m_pParent->m_StcEMailPOP3ReciverEMailStatus.SetWindowText( _T("信件已打开") );

	return 0;
}

UINT CThreadRecvEMail::OpenEMail( int i )
{
	m_nOpenIndex = i;
	if ( m_nOpenIndex < 1 )
	{
		return 1;
	}
	AfxBeginThread( ThreadProcOpen , this );
	return 0;
}

//获取邮件列表
UINT CThreadRecvEMail::ThreadProcRecv( LPVOID pParam )
{
	CThreadRecvEMail * pThis = ( CThreadRecvEMail * )pParam;

	CString str;
	pThis->m_pParent->m_StcEMailPOP3ReciverEMailStatus.SetWindowText( _T("正在获取邮件列表") );
	pThis->m_pParent->m_LclEMailPOP3EMailList.DeleteAllItems();
	AfxBeginThread( ThreadProcWait , pParam );

	pThis->m_pParent->m_Pop3.MakeEmpty();
	pThis->m_pParent->m_Pop3.StartWork( POP_TOP );
	pThis->m_pParent->m_LclEMailPOP3EMailList.DeleteAllItems();
	for ( UINT i = 1 ; i <= pThis->m_pParent->m_Pop3.GetNumOfEMail() ; i++ )
	{
		str = (CString)( pThis->m_pParent->m_Pop3[ i - 1 ]->strEMailIndex );
		pThis->m_pParent->m_LclEMailPOP3EMailList.InsertItem( i - 1 , str );
		str = (CString)( pThis->m_pParent->m_Pop3[ i - 1 ]->strEMailTop );
		pThis->m_pParent->m_LclEMailPOP3EMailList.SetItemText( i - 1 , 1 , str );
		str = (CString)( pThis->m_pParent->m_Pop3[ i - 1 ]->strEMailLenth );
		pThis->m_pParent->m_LclEMailPOP3EMailList.SetItemText( i - 1 , 2 , str );
	}

	pThis->m_pParent->m_StcEMailPOP3ReciverEMailStatus.SetWindowText( _T("邮件列表获取完成") );
	return 0;
}

UINT CThreadRecvEMail::RecvEMail()
{
	AfxBeginThread( ThreadProcRecv , this );

	return 0;
}