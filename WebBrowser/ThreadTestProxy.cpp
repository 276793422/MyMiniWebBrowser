//////////////////////////////////////////////////////////////////////////
//
//	ThreadTestProxy.cpp
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "ThreadTestProxy.h"

CThreadTestProxy::CThreadTestProxy()
{
	m_nCreateStatus = 0;
	m_nThreadWorkingNum = 0;
	m_nNeedThreadWorkNum = 10;
	m_nProxyInListCtrlMax = -1;
	m_nProxyInListCtrl = 0;
	m_nProxyInListCtrlCopy = 0;
	m_StrHtml = "";
	m_StrPass = "";
	m_LclImportProxyList = NULL;
	m_StcStatus = NULL;
	m_nNeedThreadWorkNum = 0;
	m_HQuitNowMust = NULL;
	m_HQuitNowMustCopy = NULL;
	m_HThreadOK = NULL;
}

CThreadTestProxy::~CThreadTestProxy()
{
	if ( NULL != m_HQuitNowMust )
	{
		CloseHandle( m_HQuitNowMust );
	}
	if ( NULL != m_HQuitNowMustCopy )
	{
		CloseHandle( m_HQuitNowMustCopy );
	}
	if ( NULL != m_HThreadOK )
	{
		CloseHandle( m_HThreadOK );
	}
}

UINT CThreadTestProxy::creat( CStringA &strHtml ,	//�����õ���ҳ����
							 CStringA &strPass ,		//����ͨ���ַ�
							 CListCtrl *Lcl ,		//��������Դ����ListCtrl
							 CStatic *Stc ,			//���״̬��Static
							 int nWorkNum )			//���蹤�����߳�����
{
	if ( 1 == m_nCreateStatus )
	{
		m_StrError = _T("�Ѿ���ʼ��");
		return 1;
	}

	m_StrHtml = strHtml;				//�����õ���ҳ����
	m_StrPass = strPass;				//����ͨ���ַ�
	m_LclImportProxyList = Lcl;			//��������Դ����ListCtrl
	m_StcStatus = Stc;					//���״̬��Static
	m_nNeedThreadWorkNum = nWorkNum;	//���蹤�����߳�����

	m_nProxyInListALL = Lcl->GetItemCount();
	for ( int i = 0 ; i < m_nProxyInListALL ; i++ )
	{
		if ( Lcl->GetCheck(i) )
		{
			m_nProxyInListCtrl++;
		}
	}
	if ( 0 == m_nProxyInListCtrl )
	{
		m_StcStatus->SetWindowText( _T("û��Ҫ��֤�İ�") );
		m_StrHtml = _T("");
		m_StrPass = _T("");
		m_LclImportProxyList = NULL;
		m_StcStatus = NULL;
		m_nNeedThreadWorkNum = 0;
		m_nCreateStatus = 0;
		return 1;
	}

	m_nProxyInListCtrlCopy = m_nProxyInListCtrl;
	if ( NULL != m_HQuitNowMust )
	{
		CloseHandle( m_HQuitNowMust );
	}
	if ( NULL != m_HQuitNowMustCopy )
	{
		CloseHandle( m_HQuitNowMustCopy );
	}
	if ( NULL != m_HThreadOK )
	{
		CloseHandle( m_HThreadOK );
	}
	m_HQuitNowMust = CreateEvent( 0 , 1 , 0 , 0 );
	m_HQuitNowMustCopy = CreateEvent( 0 , 1 , 0 , 0 );
	m_HThreadOK = CreateEvent( 0 , 1 , 0 , 0 );

	ResetEvent( m_HQuitNowMust );
	ResetEvent( m_HQuitNowMustCopy );
	ResetEvent( m_HThreadOK );

	m_nProxyInListCtrlMax = -1;
	m_nThreadWorkingNum = 0;
	m_nCreateStatus = 1;
	return 0;
}

UINT CThreadTestProxy::start()
{
	if ( 0 == m_nCreateStatus )
	{
		m_StrError = _T("û�г�ʼ��");
		return 1;
	}

	m_WinThread = AfxBeginThread( ThreadProc , this );

	return 0;
}

UINT CThreadTestProxy::stop()
{
	if ( 0 == m_nCreateStatus )
	{
		m_StrError = _T("û�г�ʼ��");
		return 1;
	}
	SetEvent( m_HQuitNowMust );
	SetEvent( m_HQuitNowMustCopy );
	deleteWinSock();
	return 0;
}

UINT CThreadTestProxy::deleteWinSock()
{
	if ( 0 == m_nCreateStatus )
	{
		m_StrError = _T("û�г�ʼ��");
		return 1;
	}

	m_nCreateStatus = 0;
	m_StrHtml = _T("");
	m_StrPass = _T("");
	m_nNeedThreadWorkNum = 0;
	if ( NULL != m_HQuitNowMust )
	{
		CloseHandle( m_HQuitNowMust );
	}
	if ( NULL != m_HQuitNowMustCopy )
	{
		CloseHandle( m_HQuitNowMustCopy );
	}
	if ( NULL != m_HThreadOK )
	{
		CloseHandle( m_HThreadOK );
	}

	m_HQuitNowMust = NULL;
	m_HQuitNowMustCopy = NULL;
	m_HThreadOK = NULL;

	return 0;
}

//�����̣߳������ܹ��̵�
UINT __cdecl CThreadTestProxy::ThreadProc( LPVOID pParam )
{
	CThreadTestProxy *pThis = ( CThreadTestProxy * )pParam;

	WSADATA wsaData;
	int iResult;
	//��ʼ����
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != NO_ERROR)
	{
		pThis->m_StrError = _T("��ʼ����ʧ��");
		return 1;
	}

	CString strWN;
	while ( 1 )
	{
		//����Ҫ���ԵĴ�������Ϊ0��ʱ������ѭ��
		if ( 0 == pThis->m_nProxyInListCtrl )
		{
			//pThis->m_StcStatus->SetWindowText( _T("ȫ������") );
			break;
		}
		//���ȵ���ǿ���˳��źŵ�ʱ�򣬽���
		if ( WAIT_OBJECT_0 == WaitForSingleObject( pThis->m_HQuitNowMust , 1 ) )
		{
			//���ȵ��˵ڶ����źŵ�ʱ��ǿ������
			if ( WAIT_OBJECT_0 == WaitForSingleObject( pThis->m_HQuitNowMustCopy , 1 ) )
			{
				//�˳�֮ǰ����ԭ�����ź�
				pThis->m_StcStatus->SetWindowText( _T("ǿ���˳�") );
				ResetEvent( pThis->m_HQuitNowMust );
				ResetEvent( pThis->m_HQuitNowMustCopy );
				break;
			}
			ResetEvent( pThis->m_HQuitNowMust );
		}
		//if ( WAIT_OBJECT_0 == WaitForSingleObject( pThis->m_HQuitNowMust , 1 ) )
		//{
		//	pThis->m_StcStatus->SetWindowText( _T("ǿ���˳�") );
		//	ResetEvent( pThis->m_HQuitNowMust );
		//	break;
		//}

		//�����ǰ�������߳����ˣ�����ȴ�
		while ( pThis->m_nNeedThreadWorkNum <= pThis->m_nThreadWorkingNum )
		{
			ADDLOCK
				(
				ResetEvent( pThis->m_HThreadOK );
				);
			//�ȴ�60�룬
			if ( WAIT_OBJECT_0 == WaitForSingleObject( pThis->m_HThreadOK , 60000 ) )
			{
			}
			//60���ڵȲ�������������������
			if ( 0 == pThis->m_nProxyInListCtrl )
			{
				//�˳�
				break;
			}
			//û����ɾͼ���
			//ADDLOCK
			//	(
			//	ResetEvent( pThis->m_HThreadOK );
			//	);
		}

		//��ʼ�ɻ�������߳̿���
		::QueueUserWorkItem(ThreadWorking, pParam, WT_EXECUTELONGFUNCTION);
		//�������߳����� + 1
		pThis->m_nThreadWorkingNum++;
		//ͳ�ƹ������߳�������Ȼ����ʾ
		strWN.Format( _T("%d���߳��ڹ���") , pThis->m_nThreadWorkingNum );
		pThis->m_StcStatus->SetWindowText( strWN );
		//С��һ�£�Ȼ�����
		Sleep( 5 );
	}
	while ( pThis->m_nThreadWorkingNum )
	{
		Sleep(1000);
		strWN.Format( _T("%d���߳��ڹ���") , pThis->m_nThreadWorkingNum );
		pThis->m_StcStatus->SetWindowText( strWN );
	}

	WSACleanup();
	pThis->deleteWinSock();
	return 0;
}

//�������̣߳�����ɻ��
DWORD WINAPI CThreadTestProxy::ThreadWorking( LPVOID pParam )
{
	CThreadTestProxy *pThis = ( CThreadTestProxy * )pParam;
	if ( 0 == pThis->m_nProxyInListCtrl )
	{	//�����Ҫ���Ե�����Ϊ0�������˳�
		ADDLOCK
			(
			pThis->m_nThreadWorkingNum--; 
			);
		return 1;
	}


	//��Ҫ���Ե������� 1 //����������ټӻ�ȥ
	pThis->m_nProxyInListCtrl--;

	//����SOCKET
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(INVALID_SOCKET == ConnectSocket)
	{	//���socket����ʧ�ܣ��˳�
		ADDLOCK
			(
			pThis->m_nProxyInListCtrl++;
			pThis->m_nThreadWorkingNum--;
			);
		return 1;
	}

	CStringA strA;
	CString strPort;
	//��ȡ��ǰ��������������
	int i = pThis->m_nProxyInListCtrlMax;

	//��ס�߳�λ�ã���ʼѰ����һ��Ҫ�����Ķ���
	ADDLOCK
		(	//����+1��ʼ��һֱ�����ң������Ǹ�����
		for ( i++ ; i < pThis->m_nProxyInListALL ; i++ )
		{
			if ( pThis->m_LclImportProxyList->GetCheck(i) )
			{	//�ҵ�������
				break;
			}
		}
		//���õ�ǰ��������Ҳ�����������
		pThis->m_nProxyInListCtrlMax = i;
		//������������ҵ��ַ�����Ϣ
		strPort = pThis->m_LclImportProxyList->GetItemText( i , 0 );
		);

	int port = strPort.Find( _T(':') );
	if ( -1 == port )
	{	//�����ˣ����������Ч�ִ���ֱ�ӷ���
		//��ǰҲ��������
		ADDLOCK
			(
			pThis->m_LclImportProxyList->SetItemText( i , 2 , _T("��ַ��Ч") );
			SetEvent( pThis->m_HThreadOK );
			pThis->m_nThreadWorkingNum--;
			);
		closesocket(ConnectSocket);
		return 1;
	}

	//һ�ж���ȷ���ͼ����ɣ���IP�Ͷ˿ڶ�������
	strA = strPort.Left( port );
	strPort = strPort.Right( strPort.GetLength() - port - 1 );
	port = stol( strPort , 0 , 10 );
	//����һ������
	struct sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr( strA );
	clientService.sin_port = htons( port );

	int iResult;
	//���ողŵ����ӣ���ʼ����
	iResult = connect( ConnectSocket, (SOCKADDR*) &clientService, sizeof(clientService) );
	if ( iResult == SOCKET_ERROR)
	{	//ʧ���˵Ļ����ص��˿ڣ�����
		closesocket (ConnectSocket);
		//�����ټ�һ��
		ADDLOCK
			(
			pThis->m_LclImportProxyList->SetItemText( i , 2 , _T("����ʧ�� connect") );
			SetEvent( pThis->m_HThreadOK );
			pThis->m_nThreadWorkingNum--;
			);
		//���Ӳ��ϣ�˵����������
		//���ﲻ��Ҫ�ָ�
		return 1;
	}

	strA = pThis->m_StrHtml;
	//��ղŴ��������ӷ�����Ϣ�����͵ľ����Ǹ���֤��ҳ����Ϣ
	iResult = send( ConnectSocket , strA , strA.GetLength() ,0 );
	if (iResult == SOCKET_ERROR)
	{	//��������ص����ӣ����ã����¿�ʼ
		closesocket(ConnectSocket);
		ADDLOCK
			(
			pThis->m_nProxyInListCtrl++;
			pThis->m_nThreadWorkingNum--;
			);
		return 1;
	}
	//���ܵ��ַ���
	char recvbuf[1024];
	memset( recvbuf , 0 , sizeof(recvbuf) );

	//��ʼ��ʱ��ֵ
	SYSTEMTIME stms , stme;
	GetSystemTime( &stms );
	WORD &tss = stms.wSecond ,
		&tsm = stms.wMilliseconds ,
		&tes = stme.wSecond ,
		&tem = stme.wMilliseconds ;
	CStringA strAP ;
	strAP = pThis->m_StrPass;
	pThis->m_LclImportProxyList->SetItemText( i , 2 , _T("��֤��...") );
	do {
		GetSystemTime( &stme );
		//��ʱ30�룬�Ͳ������ˣ�ֱ���˳�
		if ( ( tes - tss ) > 30000 )
		{
			ADDLOCK
				(
				pThis->m_LclImportProxyList->SetItemText( i , 2 , _T("��ʱ 30s") );
				SetEvent( pThis->m_HThreadOK );
				pThis->m_nThreadWorkingNum--;
				);
			break;
		}
		//��ʼ������Ϣ
		iResult = recv(ConnectSocket, recvbuf, 1023, 0);
		if ( iResult > 0 )
		{	//����յ�����Ϣ����0����ô��ʼ�ж�
			strA = recvbuf;
			if ( !strAP.IsEmpty() )
			{	//�Զ����ʶ�ǵ�һ��Ҫ�жϵ�
				iResult = strA.Find( strAP );
				if ( -1 != iResult )
				{	//�����Ϣ������ �Զ����ʶ Ҳ����˵����ȫ��ȷ���أ���ô����
					GetSystemTime( &stme );
					int t = ( tes - tss - ( ( ( tem < tsm ) ? 1 : 0 ) ) );
					strPort.Format( _T("%d.%d") ,
						( t < 0 ) ? ( t + 60 ) : ( t ) , 
						( tem - tsm + ( ( tem < tsm ) ? 1000 : 0 ) ) );
					//�����ʱ����Ϣ�����ϻ���Ȼ���˳�
					ADDLOCK
						(
						pThis->m_LclImportProxyList->SetItemText( i , 2 , strPort );
						SetEvent( pThis->m_HThreadOK );
						pThis->m_nThreadWorkingNum--;
						);
					break;
				}
			}

			iResult = strA.Find( "200 OK" );
			if ( -1 != iResult )
			{	//�����Ϣ������ "20 OK" Ҳ����˵����ȫ��ȷ���أ���ô����
				GetSystemTime( &stme );
				int t = ( tes - tss - ( ( ( tem < tsm ) ? 1 : 0 ) ) );
				strPort.Format( _T("%d.%d") ,
					( t < 0 ) ? ( t + 60 ) : ( t ) , 
					( tem - tsm + ( ( tem < tsm ) ? 1000 : 0 ) ) );
				//�����ʱ����Ϣ�����ϻ���Ȼ���˳�
				ADDLOCK
					(
					pThis->m_LclImportProxyList->SetItemText( i , 2 , strPort );
					SetEvent( pThis->m_HThreadOK );
					pThis->m_nThreadWorkingNum--;
					);
				break;
			}

			//��404
			iResult = strA.Find( "404 Not Found" );
			if ( -1 != iResult )
			{	//����� 404 ������˵�����Ҳ�������ô��ȫ���󣬽���
				//���÷ϻ���ֱ���˳�
				ADDLOCK
					(
					pThis->m_LclImportProxyList->SetItemText( i , 2 , _T("����ʧ�� 404") );
					SetEvent( pThis->m_HThreadOK );
					pThis->m_nThreadWorkingNum--;
					);
				break;
			}
			memset(recvbuf,0,sizeof(recvbuf));
		}
		//���� 0 ��˵�����ӽ���
		if ( iResult == 0 )
		{	//˵�����ӽ�����ʲô��û�ҵ������Ӿͽ����ˣ�Ӧ����δ֪
			ADDLOCK
				(
				pThis->m_LclImportProxyList->SetItemText( i , 2 , _T("δ֪ close") );
				SetEvent( pThis->m_HThreadOK );
				pThis->m_nThreadWorkingNum--;
				);
			break;
		}
		//С�� 0������
		if ( iResult < 0 )
		{
			ADDLOCK
				(
				pThis->m_LclImportProxyList->SetItemText( i , 2 , _T("����ʧ�� < 0") );
				);
			break;
		}

	} while( iResult > 0 );

	closesocket(ConnectSocket);

	//����ˣ��͸��ϴ��źţ��������������ˡ�
	ADDLOCK
		(
		SetEvent( pThis->m_HThreadOK );
		pThis->m_nProxyInListCtrlCopy --;
		);
	if ( 0 == pThis->m_nProxyInListCtrlCopy )
	{
		pThis->m_StcStatus->SetWindowText( _T("ȫ������") );
	}
	return 0;
}