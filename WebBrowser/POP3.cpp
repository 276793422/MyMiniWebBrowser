//////////////////////////////////////////////////////////////////////////
//
//	POP3.cpp
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "POP3.h"

CPOP3::CPOP3()
{
	InitVariable();
}

CPOP3::~CPOP3()
{
	ListMakeEmpty();
}

//服务器信息，用户名密码操作
UINT CPOP3::POPInfomation( UINT mod , CStringA *pStr )
{
	int Ret;
	Ret = (pStr)->IsEmpty();
	if ( Ret )
	{
		m_StrError = _T("是不是要写一下");
		return mod;
	}
	switch( mod )
	{
//////////////////////////////////////////////////////////////////////////
//		服务器信息，用户名密码设置
	case POP_SET_SERVER:							//设置服务器信息
		m_SUserInfomation.strServer = (*pStr);
		break;
	case POP_SET_PORT:								//设置端口
		m_SUserInfomation.strPort = (*pStr);
		break;
	case POP_SET_USER_NAME:							//设置用户名
		m_SUserInfomation.strUserName = (*pStr);
		break;
	case POP_SET_PASS_WORD:							//设置密码
		m_SUserInfomation.strPassWord = (*pStr);
		break;
//////////////////////////////////////////////////////////////////////////
//		服务器信息，用户名密码获取
	case POP_GET_SERVER:							//获取保存的服务器信息
		(*pStr) = m_SUserInfomation.strServer;
		break;
	case POP_GET_PORT:								//获取保存的端口信息
		(*pStr) = m_SUserInfomation.strPort;
		break;
	case POP_GET_USER_NAME:							//获取保存的用户名信息
		(*pStr) = m_SUserInfomation.strUserName;
		break;
	case POP_GET_PASS_WORD:							//获取保存的密码信息
		(*pStr) = m_SUserInfomation.strPassWord;
		break;
	}

	return 0;
}

//外部接口，工作函数，第一个参数为工作类型，第二个参数为工作需要返回、设置的参数
UINT CPOP3::StartWork( UINT nWorkType , LPVOID pTag , LPVOID pTagS )
{
	int Ret;
	switch( nWorkType )
	{
	case POP_CONNECT_SERVER:								//连接服务器，同时获取信件
		Ret = Connect();
		GETWRONG( Ret ,	_T("连接服务器失败") , nWorkType );
		break;
	case POP_DISCONNECT_SERVER:								//断开服务器连接
		Ret = CloseSocket();
		GETWRONG( Ret ,	_T("断开服务器连接失败") , nWorkType );
		break;
	case POP_TOP:											//获取主题				TOP
		Ret = TOP( (UINT)pTag , (UINT)pTagS );
		GETWRONG( Ret ,	_T("获取主题失败") , nWorkType );
		break;
	case POP_RETR:											//获取邮件正文			RETR
		Ret = RETR( (UINT)pTag );
		GETWRONG( Ret ,	_T("获取邮件正文失败") , nWorkType );
		break;
	case POP_DELE:											//设置邮件删除标记		DELE
		Ret = DELE( (UINT)pTag );
		GETWRONG( Ret ,	_T("设置邮件删除标记失败") , nWorkType );
		break;
	case POP_RSET:											//立刻删除有标记的邮件	RSET
		Ret = RSET(  );
		GETWRONG( Ret ,	_T("立刻删除有标记的邮件失败") , nWorkType );
		break;
	case POP_NOOP		:									//空指令，心跳包		NOOP
		Ret = NOOP(  );
		GETWRONG( Ret ,	_T("空指令，心跳包发送失败") , nWorkType );
		break;
	case POP_STAT:											//获取邮箱状态			STAT
		Ret = STAT(  );
		GETWRONG( Ret ,	_T("获取邮箱状态失败") , nWorkType );
		break;
	case POP_LIST:											//获取邮件状态			LIST
		Ret = LIST( (UINT)pTag );
		GETWRONG( Ret ,	_T("获取邮件状态失败") , nWorkType );
		break;
	case POP_GET_EMAIL_NUM:									//得到信件数量
		*(UINT*)pTag = m_unNumOfEMail;
		break;
//////////////////////////////////////////////////////////////////////////
//		服务器信息，用户名密码设置、获取
	case POP_SET_SERVER:			//设置服务器信息
	case POP_SET_PORT:				//设置端口
	case POP_SET_USER_NAME:			//设置用户名
	case POP_SET_PASS_WORD:			//设置密码
	case POP_GET_SERVER:			//获取保存的服务器信息
	case POP_GET_PORT:				//获取保存的端口信息
	case POP_GET_USER_NAME:			//获取保存的用户名信息
	case POP_GET_PASS_WORD:			//获取保存的密码信息
		Ret = POPInfomation( nWorkType , (CStringA *)pTag );
		GETWRONG( Ret ,	m_StrError , nWorkType );
		break;
//////////////////////////////////////////////////////////////////////////
//		传错了。。。。
	default:
		break;
	}
	return 0;
}


//连接服务器
UINT CPOP3::Connect()
{
	CString str;
	int Ret = 0;
//////////////////////////////////////////////////////////////////////////
	//初始化库
	WORD wRequestVersion;
	WSADATA wsaData;
	wRequestVersion = MAKEWORD(2,2);
	WSAStartup(wRequestVersion, &wsaData);
//////////////////////////////////////////////////////////////////////////
	// 初始化本地套接字
	m_socket = socket( AF_INET , SOCK_STREAM , IPPROTO_TCP );
	if (m_socket == INVALID_SOCKET)
	{
		m_StrError = _T("初始化套接字失败");
		return 1;
	}
//////////////////////////////////////////////////////////////////////////
	//初始化远程地址
	SOCKADDR_IN sockAddr;
	memset(&sockAddr, 0 ,sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons((u_short)(atoi(m_SUserInfomation.strPort)) );
	sockAddr.sin_addr.s_addr = inet_addr( m_SUserInfomation.strServer );
	if (sockAddr.sin_addr.s_addr == INADDR_NONE)
	{
		LPHOSTENT lphost;
		lphost = gethostbyname(m_SUserInfomation.strServer);
		if (lphost)
		{
			sockAddr.sin_addr.s_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
		}
		else
		{
			m_StrError = _T("无法解析地址");
			return 2;
		}
	}
//////////////////////////////////////////////////////////////////////////
	//连接远程服务器
	Ret = connect( m_socket ,(SOCKADDR *)(&sockAddr),sizeof(sockAddr));
	m_unStatus = 1;
	if ( SOCKET_ERROR == Ret )
	{
		m_StrError = _T("无法与服务器建立连接");
		return 3;
	}
//////////////////////////////////////////////////////////////////////////
	//检查服务器回应信息
	Ret = RecvMessage( 0 , 0 , 1 );
	if ( Ret )
	{
		m_StrError = _T("连接服务器失败");
		return 4;
	}
//////////////////////////////////////////////////////////////////////////
	//发送用户名
	m_StrReturn.Format( "USER %s\r\n" , m_SUserInfomation.strUserName );
	Ret = SEND( m_StrReturn.GetBuffer() , m_StrReturn.GetLength() );
	m_StrReturn.ReleaseBuffer();
	if ( SOCKET_ERROR == Ret )
	{
		// 发送用户名失败
		m_StrError = _T("发送用户名失败!");
		CloseSocket();
		return 5;
	}
//////////////////////////////////////////////////////////////////////////
	//检查服务器回应信息
	Ret = RecvMessage( 0 , 0 , 1 );
	if ( Ret )
	{
		m_StrError = _T("连接服务器失败");
		CloseSocket();
		return 6;
	}
//////////////////////////////////////////////////////////////////////////
	// 发送密码
	m_StrReturn.Format( "PASS %s\r\n" , m_SUserInfomation.strPassWord );
	Ret = SEND( m_StrReturn.GetBuffer() , m_StrReturn.GetLength() );
	m_StrReturn.ReleaseBuffer();
	if ( SOCKET_ERROR == Ret )
	{
		// 发送密码失败
		m_StrError = _T("发送密码失败!");
		CloseSocket();
		return 7;
	}
//////////////////////////////////////////////////////////////////////////
	//检查服务器回应信息
	Ret = RecvMessage( 0 , 0 , 1 );
	if ( Ret )
	{
		m_StrError = _T("连接服务器失败");
		CloseSocket();
		return 8;
	}

	//AfxMessageBox( (CString)m_StrReturn );
	return 0;
}

//关闭套接字
UINT CPOP3::CloseSocket()
{
	// 如果还保持连接状态则断开
	int Ret = 0;
	if ( m_unStatus )
	{
		CStringA strSend = "QUIT\r\n";
		// 发送断开请求
		Ret = SEND( strSend.GetBuffer() , strSend.GetLength() );
		strSend.ReleaseBuffer();
		if ( SOCKET_ERROR == Ret )
		{
			AfxMessageBox(_T("发送断开请求失败"));
			return FALSE;
		}
		RecvMessage( 0 , 0 , 1 );


		// 关闭套接字
		closesocket( m_socket );
	}
	// 将有关的变量复位
	InitVariable();

	return 0;
}

//接收并解析信息
UINT CPOP3::RecvMessage( char* buffer , UINT lenth , int Mod )
{
	if ( 0 == lenth )
	{
		buffer = ( char * )malloc( sizeof(char)*1024 );
		memset( buffer , 0 , 1024 );
	}

	m_StrReturn = "";
	int Ret = RecvTranslateMessage( buffer , ( lenth ? lenth : 1024 ) , Mod );

	if ( 0 == lenth )
	{
		free( buffer );
	}
	return Ret;
}

//解析信息
UINT CPOP3::RecvTranslateMessage( char* buffer , UINT lenth , int Mod )
{
	//准备监听，监听最长2秒
	timeval timeout = {2, 0};
	fd_set fd;
	FD_ZERO( &fd );
	FD_SET( m_socket , &fd );
	int nStatus = 0;

	//一共测试六次，判断套接字是否是可读的
	nStatus = select( 0 , &fd , NULL , NULL , &timeout );
	//出错直接走
	if ( nStatus == SOCKET_ERROR )
	{
		buffer[0] = '\0';
		// 套接字不可读
		m_StrError = _T("套接字读取出错");
		m_StrReturn = "";
		return 1;
	}
	for ( int i = 0 ;  ; i++ )
	{
		memset( buffer , 0 , lenth );
		//数据来了，可以读，开始读
		nStatus = RECV( buffer , lenth - 1 );
		//读不出来东西，退出
		if (nStatus == SOCKET_ERROR)
		{
			buffer[0] = '\0';
			// 套接字错误
			m_StrError = _T("未能从套接字中收到数据!");
			// 保存当前回应信息
			m_StrReturn = "";
			return 2; 
		}
		//在最后加个结束符
		buffer[ lenth - 1 ] = '\0';
		//保存收到的东西
		m_StrReturn += buffer;

		if ( 1 == Mod )
		{
			nStatus = ( m_StrReturn.Right( 2 ) == "\r\n" );
			nStatus = nStatus + ( 2 << 4 );
		}
		if ( 2 == Mod )
		{
			nStatus = ( m_StrReturn.Right( 5 ) == "\r\n.\r\n" );
			nStatus = nStatus + ( 5 << 4 );
		}
		if ( nStatus & 1 )
		{
			m_StrReturn.Delete( ( m_StrReturn.GetLength() - ( nStatus >> 4 ) ) , ( nStatus >> 4 ) );
			break;
		}
	}

	//判断返回信息是否有效
	m_StrReturn.MakeUpper();
	nStatus = m_StrReturn.Find( "+OK" );
	if ( -1 == nStatus )
	{
		//返回信息无效
		m_StrReturn = "";
		m_StrError = _T("返回信息错误");
		return 4;
	}
	//如果有效，删了这三个
	m_StrReturn.Delete( nStatus , 3 );

	return 0;
}

//获取邮箱状态、STAT
UINT CPOP3::STAT()
{
	int Ret = 0;
	CStringA strTemp = "STAT\r\n";
	Ret = SendCapa( strTemp );
	if ( Ret )
	{
		return Ret;
	}
	m_unNumOfEMail = atoi( m_StrReturn );
	
	return 0;
}

//获取邮件状态、LIST
UINT CPOP3::LIST( UINT index )
{
	CStringA strTemp ;
	int Ret = 0;
	EMailInfo *pTemp;
	if ( 0 == index )
	{
		ListMakeEmpty();
		STAT();
		for ( UINT i = 0 ; i < m_unNumOfEMail ; i++ )
		{
			LIST( i + 1 );
			pTemp = new EMailInfo;
			strTemp = m_StrReturn;
			strTemp.TrimLeft( ' ' );
			Ret = strTemp.Find( ' ' );
			pTemp->strEMailIndex = strTemp.Left( Ret );
			strTemp.Delete( 0 , Ret + 1 );
			pTemp->strEMailLenth = strTemp;
			m_ListEMailInfo.AddItem( pTemp );
		}
		Ret = 0;
	}
	else
	{
		strTemp.Format( "LIST %d\r\n" , index );
		Ret = SendCapa( strTemp );
	}
	return Ret;
}

//获取邮件正文、RETR
UINT CPOP3::RETR( UINT index )
{
	CStringA strTemp ;
	int Ret = 0;
	strTemp.Format( "RETR %d\r\n" , index );
	Ret = SendCapa( strTemp , 2 );
	if ( Ret )
	{
		return Ret;
	}
	// 以CONTENT-DISPOSITION: INLINE为起始标志
	m_StrReturn.MakeUpper();
	int nStart = m_StrReturn.Find("<HTML>");
	m_StrReturn.Delete( 0 , nStart );

	//	<HTML> 是正文开始 </HTML>  后是附件
	//	这里还需要解析附件，我不会。。。。。

	return 0;
}

//设置邮件删除标记、DELE
UINT CPOP3::DELE( UINT index )
{
	CStringA strTemp = "DELE\r\n";
	return SendCapa( strTemp );
}

//立刻删除有标记的邮件、RSET
UINT CPOP3::RSET()
{
	CStringA strTemp = "RSET\r\n";
	return SendCapa( strTemp );
}

//获取主题、TOP
UINT CPOP3::TOP( UINT index , UINT Line )
{
	CStringA strTemp ;
	int Ret = 0;
	if ( 0 == index && 0 == Line )
	{
		if ( 0 == m_ListEMailInfo.GetCount() )
		{
			LIST( 0 );
		}
		for ( UINT i = 0 ; i < m_ListEMailInfo.GetCount() ; i++ )
		{
			TOP( i + 1 , 0 );
			if ( " \r" == m_StrReturn )
			{
				m_StrReturn = "（无主题）";
			}
			m_ListEMailInfo[i]->strEMailTop = m_StrReturn;
		}
		return 0;
	}
	strTemp.Format( "TOP %d %d\r\n" , index , Line );
	Ret = SendCapa( strTemp );
	if ( Ret )
	{
		return Ret;
	}
	m_StrReturn.MakeUpper();
	Ret = m_StrReturn.Find( "SUBJECT:" );
	if ( -1 == Ret )
	{
		return 1;
	}
	m_StrReturn.Delete( 0 , Ret + 8 );
	Ret = m_StrReturn.Find( "\n" );
	if ( -1 == Ret )
	{
		return 2;
	}
	m_StrReturn = m_StrReturn.Left( Ret );

	return 0;
}

//空指令，心跳包、NOOP
UINT CPOP3::NOOP()
{
	CStringA strTemp = "NOOP\r\n";
	return SendCapa( strTemp );
}

//功能发送信息集合
UINT CPOP3::SendCapa( CStringA &strTemp , UINT mod )
{
	if ( 0 == m_unStatus )
	{
		return 1;
	}

	int Ret = 0;
	// 发送RSET命令
	Ret = SEND( strTemp.GetBuffer() , strTemp.GetLength() );
	strTemp.ReleaseBuffer();
	if ( SOCKET_ERROR == Ret )
	{
		m_StrError = _T("发送指令失败");
		return 2;
	}
	Sleep( 550 );

	// 接收回应信息
	//检查服务器回应信息
	Ret = RecvMessage( 0 , 0 , mod );
	if ( Ret )
	{
		m_StrError = _T("接受指令失败");
		CloseSocket();
		return 3;
	}
	return 0;
}