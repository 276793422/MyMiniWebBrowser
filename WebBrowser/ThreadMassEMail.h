//////////////////////////////////////////////////////////////////////////
//
//	ThreadMassEMail.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include <afxmt.h>

class CDlgEMail;



class CThreadMassEMail
{
public:
	CThreadMassEMail();
	~CThreadMassEMail();

	CDlgEMail *m_pDlgEMail;

	//公用信号，结束线程
	HANDLE m_hStop;

//////////////////////////////////////////////////////////////////////////
// 状态效果线程

	static UINT ThreadProcStatus( LPVOID pParam );

//////////////////////////////////////////////////////////////////////////
//	邮件群发

	static UINT ThreadProcTime( LPVOID pParam );

	void StartTime();

	void StopTime();

//////////////////////////////////////////////////////////////////////////
//	单封邮件发送

	static UINT ThreadProcOnce( LPVOID pParam );

	void StartOnce();

//////////////////////////////////////////////////////////////////////////
//	邮箱轰炸

	static UINT ThreadProcLoop( LPVOID pParam );

	void StartLoop();

	void StopLoop();

//////////////////////////////////////////////////////////////////////////
//	多线程发送，这回不用线程池

	//管理者线程
	static UINT ThreadProcThread( LPVOID pParam );

	//工作者线程
	static UINT ThreadProcThreadWork( LPVOID pParam );

	//工作者完成时候的信号
	HANDLE m_hThreadWorkOK;

	//工作者数量
	UINT m_UnWorkerNum;

	//当前使用的最高字串索引
	int m_nIndexString;

	void StartThread();

	void StopThread();

	//线程同步用的临界区
	CCriticalSection m_CISLock;
};
