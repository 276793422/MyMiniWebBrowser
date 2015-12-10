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

//��������Ϣ���û����������
UINT CPOP3::POPInfomation( UINT mod , CStringA *pStr )
{
	int Ret;
	Ret = (pStr)->IsEmpty();
	if ( Ret )
	{
		m_StrError = _T("�ǲ���Ҫдһ��");
		return mod;
	}
	switch( mod )
	{
//////////////////////////////////////////////////////////////////////////
//		��������Ϣ���û�����������
	case POP_SET_SERVER:							//���÷�������Ϣ
		m_SUserInfomation.strServer = (*pStr);
		break;
	case POP_SET_PORT:								//���ö˿�
		m_SUserInfomation.strPort = (*pStr);
		break;
	case POP_SET_USER_NAME:							//�����û���
		m_SUserInfomation.strUserName = (*pStr);
		break;
	case POP_SET_PASS_WORD:							//��������
		m_SUserInfomation.strPassWord = (*pStr);
		break;
//////////////////////////////////////////////////////////////////////////
//		��������Ϣ���û��������ȡ
	case POP_GET_SERVER:							//��ȡ����ķ�������Ϣ
		(*pStr) = m_SUserInfomation.strServer;
		break;
	case POP_GET_PORT:								//��ȡ����Ķ˿���Ϣ
		(*pStr) = m_SUserInfomation.strPort;
		break;
	case POP_GET_USER_NAME:							//��ȡ������û�����Ϣ
		(*pStr) = m_SUserInfomation.strUserName;
		break;
	case POP_GET_PASS_WORD:							//��ȡ�����������Ϣ
		(*pStr) = m_SUserInfomation.strPassWord;
		break;
	}

	return 0;
}

//�ⲿ�ӿڣ�������������һ������Ϊ�������ͣ��ڶ�������Ϊ������Ҫ���ء����õĲ���
UINT CPOP3::StartWork( UINT nWorkType , LPVOID pTag , LPVOID pTagS )
{
	int Ret;
	switch( nWorkType )
	{
	case POP_CONNECT_SERVER:								//���ӷ�������ͬʱ��ȡ�ż�
		Ret = Connect();
		GETWRONG( Ret ,	_T("���ӷ�����ʧ��") , nWorkType );
		break;
	case POP_DISCONNECT_SERVER:								//�Ͽ�����������
		Ret = CloseSocket();
		GETWRONG( Ret ,	_T("�Ͽ�����������ʧ��") , nWorkType );
		break;
	case POP_TOP:											//��ȡ����				TOP
		Ret = TOP( (UINT)pTag , (UINT)pTagS );
		GETWRONG( Ret ,	_T("��ȡ����ʧ��") , nWorkType );
		break;
	case POP_RETR:											//��ȡ�ʼ�����			RETR
		Ret = RETR( (UINT)pTag );
		GETWRONG( Ret ,	_T("��ȡ�ʼ�����ʧ��") , nWorkType );
		break;
	case POP_DELE:											//�����ʼ�ɾ�����		DELE
		Ret = DELE( (UINT)pTag );
		GETWRONG( Ret ,	_T("�����ʼ�ɾ�����ʧ��") , nWorkType );
		break;
	case POP_RSET:											//����ɾ���б�ǵ��ʼ�	RSET
		Ret = RSET(  );
		GETWRONG( Ret ,	_T("����ɾ���б�ǵ��ʼ�ʧ��") , nWorkType );
		break;
	case POP_NOOP		:									//��ָ�������		NOOP
		Ret = NOOP(  );
		GETWRONG( Ret ,	_T("��ָ�����������ʧ��") , nWorkType );
		break;
	case POP_STAT:											//��ȡ����״̬			STAT
		Ret = STAT(  );
		GETWRONG( Ret ,	_T("��ȡ����״̬ʧ��") , nWorkType );
		break;
	case POP_LIST:											//��ȡ�ʼ�״̬			LIST
		Ret = LIST( (UINT)pTag );
		GETWRONG( Ret ,	_T("��ȡ�ʼ�״̬ʧ��") , nWorkType );
		break;
	case POP_GET_EMAIL_NUM:									//�õ��ż�����
		*(UINT*)pTag = m_unNumOfEMail;
		break;
//////////////////////////////////////////////////////////////////////////
//		��������Ϣ���û����������á���ȡ
	case POP_SET_SERVER:			//���÷�������Ϣ
	case POP_SET_PORT:				//���ö˿�
	case POP_SET_USER_NAME:			//�����û���
	case POP_SET_PASS_WORD:			//��������
	case POP_GET_SERVER:			//��ȡ����ķ�������Ϣ
	case POP_GET_PORT:				//��ȡ����Ķ˿���Ϣ
	case POP_GET_USER_NAME:			//��ȡ������û�����Ϣ
	case POP_GET_PASS_WORD:			//��ȡ�����������Ϣ
		Ret = POPInfomation( nWorkType , (CStringA *)pTag );
		GETWRONG( Ret ,	m_StrError , nWorkType );
		break;
//////////////////////////////////////////////////////////////////////////
//		�����ˡ�������
	default:
		break;
	}
	return 0;
}


//���ӷ�����
UINT CPOP3::Connect()
{
	CString str;
	int Ret = 0;
//////////////////////////////////////////////////////////////////////////
	//��ʼ����
	WORD wRequestVersion;
	WSADATA wsaData;
	wRequestVersion = MAKEWORD(2,2);
	WSAStartup(wRequestVersion, &wsaData);
//////////////////////////////////////////////////////////////////////////
	// ��ʼ�������׽���
	m_socket = socket( AF_INET , SOCK_STREAM , IPPROTO_TCP );
	if (m_socket == INVALID_SOCKET)
	{
		m_StrError = _T("��ʼ���׽���ʧ��");
		return 1;
	}
//////////////////////////////////////////////////////////////////////////
	//��ʼ��Զ�̵�ַ
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
			m_StrError = _T("�޷�������ַ");
			return 2;
		}
	}
//////////////////////////////////////////////////////////////////////////
	//����Զ�̷�����
	Ret = connect( m_socket ,(SOCKADDR *)(&sockAddr),sizeof(sockAddr));
	m_unStatus = 1;
	if ( SOCKET_ERROR == Ret )
	{
		m_StrError = _T("�޷����������������");
		return 3;
	}
//////////////////////////////////////////////////////////////////////////
	//����������Ӧ��Ϣ
	Ret = RecvMessage( 0 , 0 , 1 );
	if ( Ret )
	{
		m_StrError = _T("���ӷ�����ʧ��");
		return 4;
	}
//////////////////////////////////////////////////////////////////////////
	//�����û���
	m_StrReturn.Format( "USER %s\r\n" , m_SUserInfomation.strUserName );
	Ret = SEND( m_StrReturn.GetBuffer() , m_StrReturn.GetLength() );
	m_StrReturn.ReleaseBuffer();
	if ( SOCKET_ERROR == Ret )
	{
		// �����û���ʧ��
		m_StrError = _T("�����û���ʧ��!");
		CloseSocket();
		return 5;
	}
//////////////////////////////////////////////////////////////////////////
	//����������Ӧ��Ϣ
	Ret = RecvMessage( 0 , 0 , 1 );
	if ( Ret )
	{
		m_StrError = _T("���ӷ�����ʧ��");
		CloseSocket();
		return 6;
	}
//////////////////////////////////////////////////////////////////////////
	// ��������
	m_StrReturn.Format( "PASS %s\r\n" , m_SUserInfomation.strPassWord );
	Ret = SEND( m_StrReturn.GetBuffer() , m_StrReturn.GetLength() );
	m_StrReturn.ReleaseBuffer();
	if ( SOCKET_ERROR == Ret )
	{
		// ��������ʧ��
		m_StrError = _T("��������ʧ��!");
		CloseSocket();
		return 7;
	}
//////////////////////////////////////////////////////////////////////////
	//����������Ӧ��Ϣ
	Ret = RecvMessage( 0 , 0 , 1 );
	if ( Ret )
	{
		m_StrError = _T("���ӷ�����ʧ��");
		CloseSocket();
		return 8;
	}

	//AfxMessageBox( (CString)m_StrReturn );
	return 0;
}

//�ر��׽���
UINT CPOP3::CloseSocket()
{
	// �������������״̬��Ͽ�
	int Ret = 0;
	if ( m_unStatus )
	{
		CStringA strSend = "QUIT\r\n";
		// ���ͶϿ�����
		Ret = SEND( strSend.GetBuffer() , strSend.GetLength() );
		strSend.ReleaseBuffer();
		if ( SOCKET_ERROR == Ret )
		{
			AfxMessageBox(_T("���ͶϿ�����ʧ��"));
			return FALSE;
		}
		RecvMessage( 0 , 0 , 1 );


		// �ر��׽���
		closesocket( m_socket );
	}
	// ���йصı�����λ
	InitVariable();

	return 0;
}

//���ղ�������Ϣ
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

//������Ϣ
UINT CPOP3::RecvTranslateMessage( char* buffer , UINT lenth , int Mod )
{
	//׼�������������2��
	timeval timeout = {2, 0};
	fd_set fd;
	FD_ZERO( &fd );
	FD_SET( m_socket , &fd );
	int nStatus = 0;

	//һ���������Σ��ж��׽����Ƿ��ǿɶ���
	nStatus = select( 0 , &fd , NULL , NULL , &timeout );
	//����ֱ����
	if ( nStatus == SOCKET_ERROR )
	{
		buffer[0] = '\0';
		// �׽��ֲ��ɶ�
		m_StrError = _T("�׽��ֶ�ȡ����");
		m_StrReturn = "";
		return 1;
	}
	for ( int i = 0 ;  ; i++ )
	{
		memset( buffer , 0 , lenth );
		//�������ˣ����Զ�����ʼ��
		nStatus = RECV( buffer , lenth - 1 );
		//���������������˳�
		if (nStatus == SOCKET_ERROR)
		{
			buffer[0] = '\0';
			// �׽��ִ���
			m_StrError = _T("δ�ܴ��׽������յ�����!");
			// ���浱ǰ��Ӧ��Ϣ
			m_StrReturn = "";
			return 2; 
		}
		//�����Ӹ�������
		buffer[ lenth - 1 ] = '\0';
		//�����յ��Ķ���
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

	//�жϷ�����Ϣ�Ƿ���Ч
	m_StrReturn.MakeUpper();
	nStatus = m_StrReturn.Find( "+OK" );
	if ( -1 == nStatus )
	{
		//������Ϣ��Ч
		m_StrReturn = "";
		m_StrError = _T("������Ϣ����");
		return 4;
	}
	//�����Ч��ɾ��������
	m_StrReturn.Delete( nStatus , 3 );

	return 0;
}

//��ȡ����״̬��STAT
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

//��ȡ�ʼ�״̬��LIST
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

//��ȡ�ʼ����ġ�RETR
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
	// ��CONTENT-DISPOSITION: INLINEΪ��ʼ��־
	m_StrReturn.MakeUpper();
	int nStart = m_StrReturn.Find("<HTML>");
	m_StrReturn.Delete( 0 , nStart );

	//	<HTML> �����Ŀ�ʼ </HTML>  ���Ǹ���
	//	���ﻹ��Ҫ�����������Ҳ��ᡣ��������

	return 0;
}

//�����ʼ�ɾ����ǡ�DELE
UINT CPOP3::DELE( UINT index )
{
	CStringA strTemp = "DELE\r\n";
	return SendCapa( strTemp );
}

//����ɾ���б�ǵ��ʼ���RSET
UINT CPOP3::RSET()
{
	CStringA strTemp = "RSET\r\n";
	return SendCapa( strTemp );
}

//��ȡ���⡢TOP
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
				m_StrReturn = "�������⣩";
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

//��ָ���������NOOP
UINT CPOP3::NOOP()
{
	CStringA strTemp = "NOOP\r\n";
	return SendCapa( strTemp );
}

//���ܷ�����Ϣ����
UINT CPOP3::SendCapa( CStringA &strTemp , UINT mod )
{
	if ( 0 == m_unStatus )
	{
		return 1;
	}

	int Ret = 0;
	// ����RSET����
	Ret = SEND( strTemp.GetBuffer() , strTemp.GetLength() );
	strTemp.ReleaseBuffer();
	if ( SOCKET_ERROR == Ret )
	{
		m_StrError = _T("����ָ��ʧ��");
		return 2;
	}
	Sleep( 550 );

	// ���ջ�Ӧ��Ϣ
	//����������Ӧ��Ϣ
	Ret = RecvMessage( 0 , 0 , mod );
	if ( Ret )
	{
		m_StrError = _T("����ָ��ʧ��");
		CloseSocket();
		return 3;
	}
	return 0;
}