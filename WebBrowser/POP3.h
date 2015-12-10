//////////////////////////////////////////////////////////////////////////
//
//	POP3.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//			返回值：0为正常返回
//					其他值为操作指令宏的ID
//
//////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#endif




#pragma once

#include <WinSock2.h>
#include "MyList.h"
#pragma comment(lib, "ws2_32.lib")


//报错机制
#define GETWRONG( AAA , BBB , CCC )	if( (AAA) ){ MessageBox( 0 , (BBB) , _T("信息处理出错") , 0 );	return (CCC) ; }

//#define POP_
//连接指令
#define	POP_CONNECT_SERVER			1	//连接服务器，同时获取信件
#define	POP_DISCONNECT_SERVER		2	//断开服务器连接
#define	POP_TOP						3	//获取主题				TOP
#define	POP_RETR					4	//获取邮件正文			RETR
#define	POP_DELE					5	//设置邮件删除标记		DELE
#define POP_RSET					6	//立刻删除有标记的邮件、RSET
#define	POP_NOOP					7	//空指令，心跳包		NOOP
#define POP_STAT					8	//获取邮箱状态			STAT
#define POP_LIST					9	//获取邮件状态			LIST
#define POP_GET_EMAIL_NUM			10	//得到信件数量

#define POP_SET_SERVER				0x10000000	//设置服务器信息
#define POP_SET_PORT				0x20000000	//设置端口
#define POP_SET_USER_NAME			0x30000000	//设置用户名
#define POP_SET_PASS_WORD			0x40000000	//设置密码

#define POP_GET_SERVER				0x50000000	//获取保存的服务器信息
#define POP_GET_PORT				0x60000000	//获取保存的端口信息
#define POP_GET_USER_NAME			0x70000000	//获取保存的用户名信息
#define POP_GET_PASS_WORD			0x80000000	//获取保存的密码信息


//用户名密码结构体
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
	//外部接口，工作函数，第一个参数为工作类型，第二个参数为工作需要返回、设置的参数
	UINT StartWork( UINT nWorkType , LPVOID pTag = NULL , LPVOID pTagS = NULL );
	//得到邮件数量
	UINT GetNumOfEMail()					{	return m_unNumOfEMail;	}
	//获取出错信息
	CString GetLastError()					{	return m_StrError;	}
	//获取正确返回信息
	CStringA GetReturn()					{	return m_StrReturn ;	}
	//数组方式直接获得链表中内容
	EMailInfo * operator[]( int i )			{	return m_ListEMailInfo[i];	}
	//全部清空
	void MakeEmpty()						{	ListMakeEmpty();	}

private:
//////////////////////////////////////////////////////////////////////////
	//连接服务器
	UINT Connect();
	//关闭套接字
	UINT CloseSocket();
	//接收信息
	UINT RecvMessage( char* buffer = NULL , UINT lenth = 0 , int Mod = 1 );
	//解析信息
	UINT RecvTranslateMessage(  char* buffer = NULL , UINT lenth = 0 , int Mod = 1 );
//////////////////////////////////////////////////////////////////////////
	//获取邮箱状态、STAT
	UINT STAT();
	//获取邮件状态、LIST
	UINT LIST( UINT index );
	//获取邮件正文、RETR
	UINT RETR( UINT index );
	//设置邮件删除标记、DELE
	UINT DELE( UINT index );
	//立刻删除有标记的邮件、RSET
	UINT RSET();
	//获取主题、TOP
	UINT TOP( UINT index , UINT Line = 1 );
	//空指令，心跳包、NOOP
	UINT NOOP();
//////////////////////////////////////////////////////////////////////////
	//功能发送信息集合
	UINT SendCapa( CStringA &strTemp , UINT mod = 1 );
//////////////////////////////////////////////////////////////////////////
	//服务器信息，用户名密码操作
	UINT POPInfomation( UINT mod , CStringA *pStr );
	//send
	int SEND( char *buffer , int lenth )	{	return send( m_socket , buffer , lenth , 0 );	}
	//recv
	int RECV( char *buffer , int lenth )	{	return recv( m_socket , buffer , lenth , 0 );	}
private:
	//全局使用的SOCKET
	SOCKET m_socket;
	//用户名和密码结构
	SUser m_SUserInfomation;
	//错误信息
	CString m_StrError;
	//返回消息，包含各种返回信息，是正确的返回信息，错误的返回信息不靠这个返回
	CStringA m_StrReturn;
	//套接字连接状态
	UINT m_unStatus;
	//邮箱中，邮件数量
	UINT m_unNumOfEMail;
	//邮件信息链表
	CMyList< EMailInfo * , EMailInfo * > m_ListEMailInfo;

	//把链表清空
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
