//////////////////////////////////////////////////////////////////////////
//
//	ThreadMassEMail.cpp
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "ThreadMassEMail.h"
#include "DlgEMail.h"

CThreadMassEMail::CThreadMassEMail(void)
{
	m_hStop = NULL;
	//工作者数量
	m_UnWorkerNum = 0;
	m_nIndexString = -1;
	m_hThreadWorkOK = NULL;
}

CThreadMassEMail::~CThreadMassEMail(void)
{
}

UINT CThreadMassEMail::ThreadProcStatus( LPVOID pParam )
{
	CStatic * pStc = (CStatic *)pParam;
	
	CString str;

	while( 1 )
	{
		pStc->GetWindowText( str );
		if ( _T("邮件发送中") != str.Left( 5 ) )
		{
			break;
		}
		str = str + _T(".");

		pStc->SetWindowText( str );
		
		Sleep( 1000 );
	}

	return 0;
}

UINT CThreadMassEMail::ThreadProcTime( LPVOID pParam )
{
	CThreadMassEMail * pThis = (CThreadMassEMail *)pParam;

	int i = 0;
	int index = 0;
	CString str = _T("");

	while( 1 )
	{
		if ( WAIT_OBJECT_0 == WaitForSingleObject( pThis->m_hStop , 1 ) )
		{
			pThis->m_pDlgEMail->m_StcEMailSMTPSendEMailStatus.SetWindowText( str + _T("成功退出") );
			ResetEvent( pThis->m_hStop );
			break;
		}

		pThis->m_pDlgEMail->m_StcEMailSMTPSendEMailStatus.SetWindowText( _T("邮件发送中") );

		AfxBeginThread( ( pThis->ThreadProcStatus ) , ( &(pThis->m_pDlgEMail->m_StcEMailSMTPSendEMailStatus) ) );

		i = pThis->m_pDlgEMail->m_StrMassEMail.Find( _T("\n") );
		str = pThis->m_pDlgEMail->m_StrMassEMail.Left( i );
		pThis->m_pDlgEMail->m_StrMassEMail.Delete( 0 , i + 1 );

		pThis->m_pDlgEMail->m_EMailInforSendInTimer.m_Receiver = str;
		pThis->m_pDlgEMail->m_EdtEMailSMTPRecverAddress.SetWindowText( str );
		pThis->m_pDlgEMail->SendEMail( pThis->m_pDlgEMail->m_EMailInforSendInTimer );

		index ++;

		str.Format( _T("成功发送至%d个邮箱") , index );

		pThis->m_pDlgEMail->m_StcEMailSMTPSendEMailStatus.SetWindowText( str );

		if ( pThis->m_pDlgEMail->m_StrMassEMail.IsEmpty() )
		{
			break; ;
		}

		if ( WAIT_OBJECT_0 == WaitForSingleObject( pThis->m_hStop , 1 ) )
		{
			pThis->m_pDlgEMail->m_StcEMailSMTPSendEMailStatus.SetWindowText( str + _T("成功退出") );
			ResetEvent( pThis->m_hStop );
			break;
		}

		Sleep( pThis->m_pDlgEMail->m_UnTime );
	}

	pThis->m_pDlgEMail->MakeButtonStatus( 1 );

	CloseHandle( pThis->m_hStop );
	pThis->m_hStop = NULL;

	return 0;
}

void CThreadMassEMail::StartTime()
{
	if ( NULL != m_hStop )
	{
		CloseHandle( m_hStop );
		m_hStop = NULL;
	}
	m_hStop = CreateEvent( 0 , 1 , 0 , 0 );
	AfxBeginThread( ThreadProcTime , this );
}

void CThreadMassEMail::StopTime()
{
	if ( NULL == m_hStop )
	{
		return;
	}

	SetEvent( m_hStop );
}

UINT CThreadMassEMail::ThreadProcOnce( LPVOID pParam )
{
	CThreadMassEMail * pThis = (CThreadMassEMail *)pParam;

	pThis->m_pDlgEMail->m_StcEMailSMTPSendEMailStatus.SetWindowText( _T("邮件发送中") );

	AfxBeginThread( ( pThis->ThreadProcStatus ) , ( &(pThis->m_pDlgEMail->m_StcEMailSMTPSendEMailStatus) ) );

	pThis->m_pDlgEMail->SendEMail( pThis->m_pDlgEMail->m_EMailInforSend );

	pThis->m_pDlgEMail->m_StcEMailSMTPSendEMailStatus.SetWindowText( _T("邮件发送成功") );

	return 0;
}

void CThreadMassEMail::StartOnce()
{
	AfxBeginThread( ThreadProcOnce , this );
}

UINT CThreadMassEMail::ThreadProcLoop( LPVOID pParam )
{
	CThreadMassEMail * pThis = (CThreadMassEMail *)pParam;
	UINT i = 0;
	CString str = _T("");

	for ( i = 0 ; i < pThis->m_pDlgEMail->m_UnLoopNum ; i++ )
	{

		if ( WAIT_OBJECT_0 == WaitForSingleObject( pThis->m_hStop , 1 ) )
		{
			pThis->m_pDlgEMail->m_StcEMailSMTPSendEMailStatus.SetWindowText( str + _T("成功退出") );
			ResetEvent( pThis->m_hStop );
			break;
		}

		pThis->m_pDlgEMail->m_StcEMailSMTPSendEMailStatus.SetWindowText( _T("邮件发送中") );

		AfxBeginThread( ( pThis->ThreadProcStatus ) , ( &(pThis->m_pDlgEMail->m_StcEMailSMTPSendEMailStatus) ) );

		pThis->m_pDlgEMail->SendEMail( pThis->m_pDlgEMail->m_EMailInforSend );

		str.Format( _T("成功发送%d次") , ( i + 1 ) );

		pThis->m_pDlgEMail->m_StcEMailSMTPSendEMailStatus.SetWindowText( str );

		if ( WAIT_OBJECT_0 == WaitForSingleObject( pThis->m_hStop , 1 ) )
		{
			pThis->m_pDlgEMail->m_StcEMailSMTPSendEMailStatus.SetWindowText( str + _T("成功退出") );
			ResetEvent( pThis->m_hStop );
			break;
		}

		Sleep( pThis->m_pDlgEMail->m_UnLoopTime );

	}

	CloseHandle( pThis->m_hStop );
	pThis->m_hStop = NULL;

	return 0;
}

void CThreadMassEMail::StartLoop()
{
	if ( m_hStop != NULL )
	{
		CloseHandle( m_hStop );
		m_hStop = NULL;
	}

	m_hStop = CreateEvent( 0 , 1 , 0 , 0 );

	AfxBeginThread( ThreadProcLoop , this );
}

void CThreadMassEMail::StopLoop()
{
	if ( NULL == m_hStop )
	{
		return;
	}

	SetEvent( m_hStop );

}

//管理者线程
UINT CThreadMassEMail::ThreadProcThread( LPVOID pParam )
{
	CThreadMassEMail * pThis = (CThreadMassEMail *)pParam;

	int i = 0;
	i = pThis->m_pDlgEMail->m_LclEMailSMTPCommandList.GetItemCount();
	CString str;
	while( 1 )
	{
		if ( WAIT_OBJECT_0 == WaitForSingleObject( pThis->m_hStop , 1 ) )
		{
			pThis->m_pDlgEMail->m_StcEMailSMTPSendEMailStatus.SetWindowText( _T("强制退出完成") );
			break;
		}
		while ( pThis->m_UnWorkerNum >= pThis->m_pDlgEMail->m_nThreadNum )
		{
			if ( WAIT_OBJECT_0 == WaitForSingleObject( pThis->m_hThreadWorkOK , 0xFF ) )
			{
				ResetEvent( pThis->m_hThreadWorkOK );
				break;
			}
			if ( WAIT_OBJECT_0 == WaitForSingleObject( pThis->m_hStop , 1 ) )
			{
				CloseHandle( pThis->m_hStop );
				pThis->m_hStop = NULL;
				CloseHandle( pThis->m_hThreadWorkOK );
				pThis->m_hThreadWorkOK = NULL;
				pThis->m_pDlgEMail->m_StcEMailSMTPSendEMailStatus.SetWindowText( _T("强制退出完成") );
				return 0;
			}
		}
		if ( pThis->m_nIndexString >= ( i - 1 ) )
		{
			while( 0 != pThis->m_UnWorkerNum )
			{
				Sleep(200);
			}
			pThis->m_pDlgEMail->m_StcEMailSMTPSendEMailStatus.SetWindowText( _T("工作完成") );
			break;
		}

		AfxBeginThread( ThreadProcThreadWork , pParam );

		str.Format( _T("线程数：%d。完成数：%d。") , pThis->m_UnWorkerNum , ( pThis->m_nIndexString - pThis->m_UnWorkerNum ) );
		pThis->m_pDlgEMail->m_StcEMailSMTPSendEMailStatus.SetWindowText( str );

		if ( WAIT_OBJECT_0 == WaitForSingleObject( pThis->m_hStop , 1 ) )
		{
			pThis->m_pDlgEMail->m_StcEMailSMTPSendEMailStatus.SetWindowText( _T("强制退出完成") );
			break;
		}
	}

	CloseHandle( pThis->m_hStop );
	pThis->m_hStop = NULL;
	CloseHandle( pThis->m_hThreadWorkOK );
	pThis->m_hThreadWorkOK = NULL;
	pThis->m_pDlgEMail->MakeButtonStatus( 1 );
	return 0;
}

//工作者线程
UINT CThreadMassEMail::ThreadProcThreadWork( LPVOID pParam )
{
	CThreadMassEMail * pThis = (CThreadMassEMail *)pParam;
	if ( ( pThis->m_nIndexString + 1 ) >= pThis->m_pDlgEMail->m_LclEMailSMTPCommandList.GetItemCount()  )
	{
		return 0;
	}
	CString str;
	pThis->m_CISLock.Lock();
	pThis->m_nIndexString ++;
	pThis->m_UnWorkerNum ++;
	str = pThis->m_pDlgEMail->m_LclEMailSMTPCommandList.GetItemText( pThis->m_nIndexString , 1 );
	pThis->m_CISLock.Unlock();

	Sleep( 500 );

	SEMailInfo EMail;
	pThis->m_pDlgEMail->StringToStruct( EMail , str );
	pThis->m_pDlgEMail->SendEMail( EMail );

	pThis->m_CISLock.Lock();
	pThis->m_UnWorkerNum --;
	SetEvent( pThis->m_hThreadWorkOK );
	pThis->m_CISLock.Unlock();
	return 0;
}

void CThreadMassEMail::StartThread()
{
	if ( m_hStop != NULL )
	{
		CloseHandle( m_hStop );
		m_hStop = NULL;
	}
	if ( m_hThreadWorkOK != NULL )
	{
		CloseHandle( m_hThreadWorkOK );
		m_hThreadWorkOK = NULL;
	}

	m_hStop = CreateEvent( 0 , 1 , 0 , 0 );
	m_hThreadWorkOK = CreateEvent( 0 , 1 , 0 , 0 );

	AfxBeginThread( ThreadProcThread , this );
}

void CThreadMassEMail::StopThread()
{
	if ( NULL == m_hStop )
	{
		return;
	}

	SetEvent( m_hStop );
	m_nIndexString = -1;
}