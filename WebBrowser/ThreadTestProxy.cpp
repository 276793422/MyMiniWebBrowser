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

UINT CThreadTestProxy::creat( CStringA &strHtml ,	//测试用的网页命令
							 CStringA &strPass ,		//测试通过字符
							 CListCtrl *Lcl ,		//保存待测试代理的ListCtrl
							 CStatic *Stc ,			//输出状态的Static
							 int nWorkNum )			//所需工作者线程数量
{
	if ( 1 == m_nCreateStatus )
	{
		m_StrError = _T("已经初始化");
		return 1;
	}

	m_StrHtml = strHtml;				//测试用的网页命令
	m_StrPass = strPass;				//测试通过字符
	m_LclImportProxyList = Lcl;			//保存待测试代理的ListCtrl
	m_StcStatus = Stc;					//输出状态的Static
	m_nNeedThreadWorkNum = nWorkNum;	//所需工作者线程数量

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
		m_StcStatus->SetWindowText( _T("没有要验证的阿") );
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
		m_StrError = _T("没有初始化");
		return 1;
	}

	m_WinThread = AfxBeginThread( ThreadProc , this );

	return 0;
}

UINT CThreadTestProxy::stop()
{
	if ( 0 == m_nCreateStatus )
	{
		m_StrError = _T("没有初始化");
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
		m_StrError = _T("没有初始化");
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

//调度线程，负责总工程的
UINT __cdecl CThreadTestProxy::ThreadProc( LPVOID pParam )
{
	CThreadTestProxy *pThis = ( CThreadTestProxy * )pParam;

	WSADATA wsaData;
	int iResult;
	//初始化库
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != NO_ERROR)
	{
		pThis->m_StrError = _T("初始化库失败");
		return 1;
	}

	CString strWN;
	while ( 1 )
	{
		//当需要测试的代理数量为0的时候，跳出循环
		if ( 0 == pThis->m_nProxyInListCtrl )
		{
			//pThis->m_StcStatus->SetWindowText( _T("全部结束") );
			break;
		}
		//当等到了强制退出信号的时候，进入
		if ( WAIT_OBJECT_0 == WaitForSingleObject( pThis->m_HQuitNowMust , 1 ) )
		{
			//当等到了第二个信号的时候，强制跳出
			if ( WAIT_OBJECT_0 == WaitForSingleObject( pThis->m_HQuitNowMustCopy , 1 ) )
			{
				//退出之前，复原两个信号
				pThis->m_StcStatus->SetWindowText( _T("强制退出") );
				ResetEvent( pThis->m_HQuitNowMust );
				ResetEvent( pThis->m_HQuitNowMustCopy );
				break;
			}
			ResetEvent( pThis->m_HQuitNowMust );
		}
		//if ( WAIT_OBJECT_0 == WaitForSingleObject( pThis->m_HQuitNowMust , 1 ) )
		//{
		//	pThis->m_StcStatus->SetWindowText( _T("强制退出") );
		//	ResetEvent( pThis->m_HQuitNowMust );
		//	break;
		//}

		//如果当前工作者线程满了，进入等待
		while ( pThis->m_nNeedThreadWorkNum <= pThis->m_nThreadWorkingNum )
		{
			ADDLOCK
				(
				ResetEvent( pThis->m_HThreadOK );
				);
			//等待60秒，
			if ( WAIT_OBJECT_0 == WaitForSingleObject( pThis->m_HThreadOK , 60000 ) )
			{
			}
			//60秒内等不到，如果工作都完成了
			if ( 0 == pThis->m_nProxyInListCtrl )
			{
				//退出
				break;
			}
			//没有完成就继续
			//ADDLOCK
			//	(
			//	ResetEvent( pThis->m_HThreadOK );
			//	);
		}

		//开始干活，工作者线程开干
		::QueueUserWorkItem(ThreadWorking, pParam, WT_EXECUTELONGFUNCTION);
		//工作者线程数量 + 1
		pThis->m_nThreadWorkingNum++;
		//统计工作者线程数量，然后显示
		strWN.Format( _T("%d条线程在工作") , pThis->m_nThreadWorkingNum );
		pThis->m_StcStatus->SetWindowText( strWN );
		//小等一下，然后继续
		Sleep( 5 );
	}
	while ( pThis->m_nThreadWorkingNum )
	{
		Sleep(1000);
		strWN.Format( _T("%d条线程在工作") , pThis->m_nThreadWorkingNum );
		pThis->m_StcStatus->SetWindowText( strWN );
	}

	WSACleanup();
	pThis->deleteWinSock();
	return 0;
}

//工作者线程，负责干活的
DWORD WINAPI CThreadTestProxy::ThreadWorking( LPVOID pParam )
{
	CThreadTestProxy *pThis = ( CThreadTestProxy * )pParam;
	if ( 0 == pThis->m_nProxyInListCtrl )
	{	//如果需要测试的数量为0，立即退出
		ADDLOCK
			(
			pThis->m_nThreadWorkingNum--; 
			);
		return 1;
	}


	//需要测试的数量减 1 //后面出错了再加回去
	pThis->m_nProxyInListCtrl--;

	//创建SOCKET
	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(INVALID_SOCKET == ConnectSocket)
	{	//如果socket创建失败，退出
		ADDLOCK
			(
			pThis->m_nProxyInListCtrl++;
			pThis->m_nThreadWorkingNum--;
			);
		return 1;
	}

	CStringA strA;
	CString strPort;
	//获取当前操作的最大的索引
	int i = pThis->m_nProxyInListCtrlMax;

	//锁住线程位置，开始寻找下一个要操作的东西
	ADDLOCK
		(	//索引+1开始，一直往后找，就找那个可以
		for ( i++ ; i < pThis->m_nProxyInListALL ; i++ )
		{
			if ( pThis->m_LclImportProxyList->GetCheck(i) )
			{	//找到了跳出
				break;
			}
		}
		//设置当前的索引，也就是最高索引
		pThis->m_nProxyInListCtrlMax = i;
		//按照最高索引找到字符串信息
		strPort = pThis->m_LclImportProxyList->GetItemText( i , 0 );
		);

	int port = strPort.Find( _T(':') );
	if ( -1 == port )
	{	//出错了，这个不是有效字串，直接返回
		//当前也不测试了
		ADDLOCK
			(
			pThis->m_LclImportProxyList->SetItemText( i , 2 , _T("地址无效") );
			SetEvent( pThis->m_HThreadOK );
			pThis->m_nThreadWorkingNum--;
			);
		closesocket(ConnectSocket);
		return 1;
	}

	//一切都正确，就继续吧，把IP和端口都处理了
	strA = strPort.Left( port );
	strPort = strPort.Right( strPort.GetLength() - port - 1 );
	port = stol( strPort , 0 , 10 );
	//创建一个连接
	struct sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr( strA );
	clientService.sin_port = htons( port );

	int iResult;
	//按照刚才的连接，开始连接
	iResult = connect( ConnectSocket, (SOCKADDR*) &clientService, sizeof(clientService) );
	if ( iResult == SOCKET_ERROR)
	{	//失败了的话，关掉端口，继续
		closesocket (ConnectSocket);
		//总数再加一个
		ADDLOCK
			(
			pThis->m_LclImportProxyList->SetItemText( i , 2 , _T("连接失败 connect") );
			SetEvent( pThis->m_HThreadOK );
			pThis->m_nThreadWorkingNum--;
			);
		//连接不上，说明它有问题
		//这里不需要恢复
		return 1;
	}

	strA = pThis->m_StrHtml;
	//向刚才创建的连接发送信息，发送的就是那个验证网页的信息
	iResult = send( ConnectSocket , strA , strA.GetLength() ,0 );
	if (iResult == SOCKET_ERROR)
	{	//如果出错，关掉连接，重置，重新开始
		closesocket(ConnectSocket);
		ADDLOCK
			(
			pThis->m_nProxyInListCtrl++;
			pThis->m_nThreadWorkingNum--;
			);
		return 1;
	}
	//接受的字符串
	char recvbuf[1024];
	memset( recvbuf , 0 , sizeof(recvbuf) );

	//开始的时间值
	SYSTEMTIME stms , stme;
	GetSystemTime( &stms );
	WORD &tss = stms.wSecond ,
		&tsm = stms.wMilliseconds ,
		&tes = stme.wSecond ,
		&tem = stme.wMilliseconds ;
	CStringA strAP ;
	strAP = pThis->m_StrPass;
	pThis->m_LclImportProxyList->SetItemText( i , 2 , _T("验证中...") );
	do {
		GetSystemTime( &stme );
		//超时30秒，就不管它了，直接退出
		if ( ( tes - tss ) > 30000 )
		{
			ADDLOCK
				(
				pThis->m_LclImportProxyList->SetItemText( i , 2 , _T("超时 30s") );
				SetEvent( pThis->m_HThreadOK );
				pThis->m_nThreadWorkingNum--;
				);
			break;
		}
		//开始接受信息
		iResult = recv(ConnectSocket, recvbuf, 1023, 0);
		if ( iResult > 0 )
		{	//如果收到的信息大于0，那么开始判断
			strA = recvbuf;
			if ( !strAP.IsEmpty() )
			{	//自定义标识是第一个要判断的
				iResult = strA.Find( strAP );
				if ( -1 != iResult )
				{	//如果信息里面有 自定义标识 也就是说，完全正确返回，那么进来
					GetSystemTime( &stme );
					int t = ( tes - tss - ( ( ( tem < tsm ) ? 1 : 0 ) ) );
					strPort.Format( _T("%d.%d") ,
						( t < 0 ) ? ( t + 60 ) : ( t ) , 
						( tem - tsm + ( ( tem < tsm ) ? 1000 : 0 ) ) );
					//调理好时间信息，不废话，然后退出
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
			{	//如果信息里面有 "20 OK" 也就是说，完全正确返回，那么进来
				GetSystemTime( &stme );
				int t = ( tes - tss - ( ( ( tem < tsm ) ? 1 : 0 ) ) );
				strPort.Format( _T("%d.%d") ,
					( t < 0 ) ? ( t + 60 ) : ( t ) , 
					( tem - tsm + ( ( tem < tsm ) ? 1000 : 0 ) ) );
				//调理好时间信息，不废话，然后退出
				ADDLOCK
					(
					pThis->m_LclImportProxyList->SetItemText( i , 2 , strPort );
					SetEvent( pThis->m_HThreadOK );
					pThis->m_nThreadWorkingNum--;
					);
				break;
			}

			//找404
			iResult = strA.Find( "404 Not Found" );
			if ( -1 != iResult )
			{	//如果有 404 ，就是说根本找不到，那么完全错误，进来
				//不用废话，直接退出
				ADDLOCK
					(
					pThis->m_LclImportProxyList->SetItemText( i , 2 , _T("连接失败 404") );
					SetEvent( pThis->m_HThreadOK );
					pThis->m_nThreadWorkingNum--;
					);
				break;
			}
			memset(recvbuf,0,sizeof(recvbuf));
		}
		//等于 0 ，说明连接结束
		if ( iResult == 0 )
		{	//说明连接结束，什么都没找到，连接就结束了，应该是未知
			ADDLOCK
				(
				pThis->m_LclImportProxyList->SetItemText( i , 2 , _T("未知 close") );
				SetEvent( pThis->m_HThreadOK );
				pThis->m_nThreadWorkingNum--;
				);
			break;
		}
		//小于 0，错了
		if ( iResult < 0 )
		{
			ADDLOCK
				(
				pThis->m_LclImportProxyList->SetItemText( i , 2 , _T("连接失败 < 0") );
				);
			break;
		}

	} while( iResult > 0 );

	closesocket(ConnectSocket);

	//完成了，就给老大发信号，告诉他，完事了。
	ADDLOCK
		(
		SetEvent( pThis->m_HThreadOK );
		pThis->m_nProxyInListCtrlCopy --;
		);
	if ( 0 == pThis->m_nProxyInListCtrlCopy )
	{
		pThis->m_StcStatus->SetWindowText( _T("全部结束") );
	}
	return 0;
}