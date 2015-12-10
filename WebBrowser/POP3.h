//////////////////////////////////////////////////////////////////////////
//
//	POP3.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//			����ֵ��0Ϊ��������
//					����ֵΪ����ָ����ID
//
//////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#endif




#pragma once

#include <WinSock2.h>
#include "MyList.h"
#pragma comment(lib, "ws2_32.lib")


//�������
#define GETWRONG( AAA , BBB , CCC )	if( (AAA) ){ MessageBox( 0 , (BBB) , _T("��Ϣ�������") , 0 );	return (CCC) ; }

//#define POP_
//����ָ��
#define	POP_CONNECT_SERVER			1	//���ӷ�������ͬʱ��ȡ�ż�
#define	POP_DISCONNECT_SERVER		2	//�Ͽ�����������
#define	POP_TOP						3	//��ȡ����				TOP
#define	POP_RETR					4	//��ȡ�ʼ�����			RETR
#define	POP_DELE					5	//�����ʼ�ɾ�����		DELE
#define POP_RSET					6	//����ɾ���б�ǵ��ʼ���RSET
#define	POP_NOOP					7	//��ָ�������		NOOP
#define POP_STAT					8	//��ȡ����״̬			STAT
#define POP_LIST					9	//��ȡ�ʼ�״̬			LIST
#define POP_GET_EMAIL_NUM			10	//�õ��ż�����

#define POP_SET_SERVER				0x10000000	//���÷�������Ϣ
#define POP_SET_PORT				0x20000000	//���ö˿�
#define POP_SET_USER_NAME			0x30000000	//�����û���
#define POP_SET_PASS_WORD			0x40000000	//��������

#define POP_GET_SERVER				0x50000000	//��ȡ����ķ�������Ϣ
#define POP_GET_PORT				0x60000000	//��ȡ����Ķ˿���Ϣ
#define POP_GET_USER_NAME			0x70000000	//��ȡ������û�����Ϣ
#define POP_GET_PASS_WORD			0x80000000	//��ȡ�����������Ϣ


//�û�������ṹ��
typedef struct _SUser
{
	CStringA strServer;
	CStringA strPort;
	CStringA strUserName;
	CStringA strPassWord;
} SUser;

typedef struct _EMailInfo
{
	CStringA strEMailIndex;
	CStringA strEMailTop;
	CStringA strEMailLenth;
}EMailInfo;

class CPOP3
{
public:
	CPOP3();
	~CPOP3();
	CEdit *m_edt;

public:
	//�ⲿ�ӿڣ�������������һ������Ϊ�������ͣ��ڶ�������Ϊ������Ҫ���ء����õĲ���
	UINT StartWork( UINT nWorkType , LPVOID pTag = NULL , LPVOID pTagS = NULL );
	//�õ��ʼ�����
	UINT GetNumOfEMail()					{	return m_unNumOfEMail;	}
	//��ȡ������Ϣ
	CString GetLastError()					{	return m_StrError;	}
	//��ȡ��ȷ������Ϣ
	CStringA GetReturn()					{	return m_StrReturn ;	}
	//���鷽ʽֱ�ӻ������������
	EMailInfo * operator[]( int i )			{	return m_ListEMailInfo[i];	}
	//ȫ�����
	void MakeEmpty()						{	ListMakeEmpty();	}

private:
//////////////////////////////////////////////////////////////////////////
	//���ӷ�����
	UINT Connect();
	//�ر��׽���
	UINT CloseSocket();
	//������Ϣ
	UINT RecvMessage( char* buffer = NULL , UINT lenth = 0 , int Mod = 1 );
	//������Ϣ
	UINT RecvTranslateMessage(  char* buffer = NULL , UINT lenth = 0 , int Mod = 1 );
//////////////////////////////////////////////////////////////////////////
	//��ȡ����״̬��STAT
	UINT STAT();
	//��ȡ�ʼ�״̬��LIST
	UINT LIST( UINT index );
	//��ȡ�ʼ����ġ�RETR
	UINT RETR( UINT index );
	//�����ʼ�ɾ����ǡ�DELE
	UINT DELE( UINT index );
	//����ɾ���б�ǵ��ʼ���RSET
	UINT RSET();
	//��ȡ���⡢TOP
	UINT TOP( UINT index , UINT Line = 1 );
	//��ָ���������NOOP
	UINT NOOP();
//////////////////////////////////////////////////////////////////////////
	//���ܷ�����Ϣ����
	UINT SendCapa( CStringA &strTemp , UINT mod = 1 );
//////////////////////////////////////////////////////////////////////////
	//��������Ϣ���û����������
	UINT POPInfomation( UINT mod , CStringA *pStr );
	//send
	int SEND( char *buffer , int lenth )	{	return send( m_socket , buffer , lenth , 0 );	}
	//recv
	int RECV( char *buffer , int lenth )	{	return recv( m_socket , buffer , lenth , 0 );	}
private:
	//ȫ��ʹ�õ�SOCKET
	SOCKET m_socket;
	//�û���������ṹ
	SUser m_SUserInfomation;
	//������Ϣ
	CString m_StrError;
	//������Ϣ���������ַ�����Ϣ������ȷ�ķ�����Ϣ������ķ�����Ϣ�����������
	CStringA m_StrReturn;
	//�׽�������״̬
	UINT m_unStatus;
	//�����У��ʼ�����
	UINT m_unNumOfEMail;
	//�ʼ���Ϣ����
	CMyList< EMailInfo * , EMailInfo * > m_ListEMailInfo;

	//���������
	void ListMakeEmpty()
	{
		for ( UINT i = 0 ; i < m_ListEMailInfo.GetCount() ; i++ )
		{
			delete m_ListEMailInfo[i];
		}
		m_ListEMailInfo.MakeEmpty();
	}
	void InitVariable()
	{
		m_socket = INVALID_SOCKET;
		m_SUserInfomation.strServer = "";
		m_SUserInfomation.strPort = "";
		m_SUserInfomation.strUserName = "";
		m_SUserInfomation.strPassWord = "";
		m_StrError = _T("");
		m_unStatus = 0;
		m_unNumOfEMail = 0;
	}
};
