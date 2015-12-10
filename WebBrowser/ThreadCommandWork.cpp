//////////////////////////////////////////////////////////////////////////
//
//	ThreadCommandWork.cpp
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "ThreadCommandWork.h"
#include "resource.h"

#include "HTMLDlg.h"




CThreadCommandWork::CThreadCommandWork()
{
	m_nStatus = CThreadCommandWork::THREAD_CLEAR;
	m_hPause = NULL;
	m_hStop = NULL;
	nASM = NULL;
	m_pStrStack = NULL;
	m_nStrStack = 0;
	nFlag = 0;
	m_nProxyIndex = 0;
	m_nURLPageIndex = 0;
}

CThreadCommandWork::~CThreadCommandWork()
{
	if ( NULL != nASM )
	{
		free( nASM );
		nASM = NULL;
	}
	if ( NULL != m_pStrStack )
	{
		delete m_pStrStack;
		m_pStrStack = NULL;
		m_nStrStack = 0;
	}
}

UINT __cdecl CThreadCommandWork::pfnThreadProc( LPVOID pParam )
{
	CThreadCommandWork *pThis = (CThreadCommandWork*) pParam;

	pThis->m_pHtmlDlg->m_DlgList.SetWindowTextToCommandEdit( _T("��ʼ����") );

	int all = pThis->m_ListCtrl->GetItemCount();
	pThis->nASM = (short *)malloc( sizeof(short) * all );
	pThis->nEIP = 0;

	for ( int i = 0 ; i < all ; i++ )
	{
		pThis->nASM[i] = pThis->m_pHtmlDlg->m_DlgList.m_InstructTAR.TranslateInstruct( 
												pThis->m_ListCtrl->GetItemText( i , 1 ) );
		if ( 0 == pThis->nASM[i] )
		{
			pThis->nEIP = i;
		}
		if ( 18 == pThis->nASM[i] )
		{
			pThis->m_pHtmlDlg->m_DlgList.m_InstructTAR.Fun18(
									pThis->m_ListCtrl->GetItemText( i , 2 ) ,
									0 );
		}
	}

	pThis->m_pStrStack = new StrStack[pThis->nEIP - 1];
	pThis->m_nStrStack = pThis->nEIP - 1;
	for ( int i = 1 ; i < (pThis->nEIP) ; i++ )
	{
		pThis->m_pHtmlDlg->m_DlgList.m_InstructTAR.Fun10(
								pThis->m_ListCtrl->GetItemText( i , 2 ) ,
								i );
	}

	CString strMessage;
	strMessage.Format( _T("%d����ʼ����") , pThis->nEIP );
	pThis->m_pHtmlDlg->m_DlgList.SetWindowTextToCommandEdit( strMessage );

	pThis->nEIP += 1;
	while (1)
	{
		if ( 1 == (pThis->nASM)[(pThis->nEIP)] )
		{
			break;
		}
		//��ͣ����ʼ��û���źžͿ����⣬һֱ�ȣ�������ͣ�����źž���
		WaitForSingleObject( pThis->m_hPause , 0xFFFFFFFF );
		//ֹͣ���źţ�ֹͣ�����źţ�û���źžͲ�ֹͣ
		if ( WAIT_OBJECT_0 != WaitForSingleObject( pThis->m_hStop , 1 ) )
		{
			break;
		}

		//ȡ��������Ϣ��Ҳ���ǲ�����Ϣ
		strMessage = pThis->m_pHtmlDlg->m_DlgList.m_LclCmd[0].GetItemText( ( pThis->nEIP ) , 2 );
		//	( pThis->nASM )[ ( pThis->nEIP ) ] //ָ������ĵ�ǰ������������װ����ִ��ָ��ĺ���ID
		if( 0 != pThis->m_pHtmlDlg->m_DlgList.m_InstructTAR.RunInstruct( 
								( pThis->nASM )[ ( pThis->nEIP ) ] ,
								strMessage ,
								( pThis->nEIP ) ) )
		{
			break;
		}

		if ( 0 != pThis->m_nSleep )
		{
			pThis->m_pHtmlDlg->m_DlgList.SetWindowTextToCommandEdit( _T("Ĭ���ӳٿ���") );
			Sleep( pThis->m_nSleep );
		}

		pThis->nEIP++;
	}

	strMessage.Format( _T("%d��������������������") , pThis->nEIP );
	pThis->m_pHtmlDlg->m_DlgList.SetWindowTextToCommandEdit( strMessage );

	pThis->DeleteStrStack();
	delete ( pThis->m_pStrStack );
	pThis->m_pStrStack = NULL;
	pThis->m_nStrStack = 0;

	free( pThis->nASM );
	pThis->nASM = NULL;
	pThis->m_pHtmlDlg->m_DlgList.OnBnClickedButtonCommandStopItWork();
	return 0;
}

//�ͷ��ڲ���Դ
void CThreadCommandWork::DeleteStrStack()
{
	int i = 0;
	int j = 0;
	for ( i = 0 ;  ; i++ )
	{
		if ( 0 == nASM[i] )
		{
			j = i - 1;
			break;
		}
	}
	for ( i = 0 ; i < j ; i++ )
	{
		delete (m_pStrStack[i].Str);
	}
}

UINT CThreadCommandWork::Create( CHTMLDlg *Wnd )
{
	//�������̣������ǰ״̬����δ��ʼ��״̬������˵�������ˣ�����
	if ( m_nStatus != CThreadCommandWork::THREAD_CLEAR )
	{
		return 1;
	}
	//ֻ�е�ǰ״̬Ϊδ��ʼ��״̬ʱ�����ܽ���
	m_nStatus = CThreadCommandWork::THREAD_CREATE;

	m_pHtmlDlg = Wnd;

	m_pEdtCmdTxUt = &(Wnd->m_DlgList.m_EdtCommandThreadTextOut);

	m_ListCtrl = &(m_pHtmlDlg->m_DlgList.m_LclCmd[0]);
	if ( NULL != m_hPause )
	{
		ResetEvent( m_hPause );
	}
	m_hPause = CreateEvent( 0 , 1 , 0 , 0 );
	if ( NULL != m_hStop )
	{
		ResetEvent( m_hStop );
	}
	m_hStop = CreateEvent( 0 , 1 , 0 , 0 );

	nFlag = 0;
	m_nURLPageIndex = 0;
	m_nProxyIndex = 0;

	m_pHtmlDlg->m_DlgList.SetWindowTextToCommandEdit( _T("��ʼ�����") );
	return 0;
}

UINT CThreadCommandWork::Start()
{
	if ( m_nStatus != CThreadCommandWork::THREAD_CREATE )
	{
		return 1;
	}
	//ֻ�е�ǰ״̬Ϊδ��ʼ��״̬ʱ�����ܽ���
	m_nStatus = CThreadCommandWork::THREAD_START;

	SetEvent( m_hStop );
	SetEvent( m_hPause );
	m_WinThread = AfxBeginThread( pfnThreadProc , this );

	if ( NULL == m_WinThread )
	{
		return 1;
	}

	return 0;
}

UINT CThreadCommandWork::Pause()
{
	switch ( m_nStatus )
	{
	case CThreadCommandWork::THREAD_START:
		{
			m_nStatus = CThreadCommandWork::THREAD_PAUSE;
			ResetEvent( m_hPause );
			m_pHtmlDlg->m_DlgList.SetWindowTextToCommandEdit( _T("��ͣ") );
			return 0;
		}
	case CThreadCommandWork::THREAD_PAUSE:
		{
			m_nStatus = CThreadCommandWork::THREAD_START;
			SetEvent( m_hPause );
			m_pHtmlDlg->m_DlgList.SetWindowTextToCommandEdit( _T("����") );
			return 0;
		}
	default:
		break;
	}

	return 1;
}

UINT CThreadCommandWork::Stop()
{
	if ( m_nStatus != CThreadCommandWork::THREAD_START &&
		m_nStatus != CThreadCommandWork::THREAD_PAUSE )
	{
		return 1;
	}
	//ֻ�е�ǰ״̬Ϊδ��ʼ��״̬ʱ�����ܽ���
	m_nStatus = CThreadCommandWork::THREAD_STOP;
	SetEvent( m_hPause );
	SetEvent( m_hStop );

	m_pHtmlDlg->m_DlgList.SetWindowTextToCommandEdit( _T("����ֹͣ") );

	return 0;
}

UINT CThreadCommandWork::Clear()
{
	if ( m_nStatus != CThreadCommandWork::THREAD_STOP )
	{
		return 1;
	}
	//ֻ�е�ǰ״̬Ϊδ��ʼ��״̬ʱ�����ܽ���
	m_nStatus = CThreadCommandWork::THREAD_CLEAR;
	ResetEvent( m_hPause );
	ResetEvent( m_hStop );

	m_hPause = NULL;
	m_nProxyIndex = 0;

	m_pHtmlDlg->m_DlgList.SetWindowTextToCommandEdit( _T("�����ͷ�") );

	return 0;
}

