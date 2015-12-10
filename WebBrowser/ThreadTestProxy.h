//////////////////////////////////////////////////////////////////////////
//
//	ThreadTestProxy.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#pragma once

#include <afxmt.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

//锁定位置
#define ADDLOCK( x )					\
		pThis->m_CtlStn.Lock();			\
		{ x }							\
		pThis->m_CtlStn.Unlock();

//字符串转化数字函数，只能这么重定义
#ifdef _UNICODE
#define stol wcstol
#else
#define stol strtol
#endif

class CThreadTestProxy
{
public:
	CThreadTestProxy();
	~CThreadTestProxy();

private:
	CStringA m_StrHtml;
	CStringA m_StrPass;
	CListCtrl * m_LclImportProxyList;
	CStatic * m_StcStatus;

	CWinThread * m_WinThread;

	//需要的工作者线程数量
	int m_nNeedThreadWorkNum;
	//正在工作的线程数量
	int m_nThreadWorkingNum;

	//列表框内，有多少个需要测试的
	int m_nProxyInListCtrl;
	int m_nProxyInListCtrlCopy;
	//列表框内，目前测试序数最大的一个
	int m_nProxyInListCtrlMax;
	//列表框内，一共有多少个
	int m_nProxyInListALL;

	//创建状态，如果为0表示没有创建，全部不许使用
	int m_nCreateStatus;

	//错误信息
	CString m_StrError;

	//强制退出信号
	HANDLE m_HQuitNowMust;
	HANDLE m_HQuitNowMustCopy;
	//线程完成信号
	HANDLE m_HThreadOK;
public:
	//线程同步临界区
	CCriticalSection m_CtlStn;

	//创建
	UINT creat( CStringA &strHtml ,	//测试用的网页命令
				CStringA &strPass ,	//测试通过字符
				CListCtrl *Lcl ,	//保存待测试代理的ListCtrl
				CStatic *Stc ,		//输出状态的Static
				int nWorkNum		//所需工作者线程数量
				);

	//开始
	UINT start();

	//停止
	UINT stop();

	//关闭
	UINT deleteWinSock();

	//工作者线程，负责干活的
	static DWORD WINAPI ThreadWorking( LPVOID pParam );

	//调度线程，负责总工程的
	static UINT __cdecl ThreadProc( LPVOID pParam );

};
