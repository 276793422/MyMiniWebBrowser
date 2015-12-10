//////////////////////////////////////////////////////////////////////////
//
//	ThreadRecvEMail.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#pragma once





class CDlgEMail;

class CThreadRecvEMail
{
public:
	CThreadRecvEMail();
	~CThreadRecvEMail();


	CDlgEMail *m_pParent;

public:
	//全盘初始化
	UINT Create( CDlgEMail *parent );
private:
	//等待状态线程
	static UINT ThreadProcWait( LPVOID pParam );
private:
	//心跳包状态
	int m_Status;
	//心跳包结束句柄，也是退出服务句柄
	HANDLE m_HClose;
	//心跳包线程
	static UINT ThreadProcNOOP( LPVOID pParam );
public:
	//心跳包启动，保持一直在线
	UINT StartNOOP();
	//心跳包停止，下线
	UINT Stop();

public:
	//打开信线程
	static UINT ThreadProcOpen( LPVOID pParam );
	UINT OpenEMail( int i );
	int m_nOpenIndex;
public:
	//获取邮件列表
	static UINT ThreadProcRecv( LPVOID pParam );
	UINT RecvEMail();
};
