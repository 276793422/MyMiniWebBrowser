//////////////////////////////////////////////////////////////////////////
//
//	ThreadCommandWork.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#pragma once
class CThreadCommandWork;


typedef struct {
	CString *Str;
	int nStack;
}StrStack;



//字符串转化数字函数，只能这么重定义
#ifdef _UNICODE
#define stol wcstol
#else
#define stol strtol
#endif

class CHTMLDlg;

class CThreadCommandWork
{
public:
	CThreadCommandWork();
	~CThreadCommandWork();

	static UINT __cdecl pfnThreadProc( LPVOID pParam );

	enum{
		THREAD_CREATE = 0 ,		//创建状态
		THREAD_START ,			//启动状态
		THREAD_PAUSE ,			//停止状态
		THREAD_STOP ,			//结束状态
		THREAD_CLEAR			//清理状态
		};
	//线程执行状态，为上表枚举状态
	int m_nStatus;
	//线程当前使用的代理
	int m_nProxyIndex;
	//当前打开的控制信息的网页索引
	int m_nURLPageIndex;


	//总父类对话框
	CHTMLDlg *m_pHtmlDlg;

	//内部维护的一个线程指针
	CWinThread *m_WinThread;

	//工作流程
	CListCtrl *m_ListCtrl;

	//暂停的信号，暂停时没有信号，有信号了就继续
	HANDLE m_hPause;
	//停止的信号，要停止时有信号，没有信号就不停止
	HANDLE m_hStop;

	//下两个组合起来，就是执行该条指令的函数ID
	//指令表
	short *nASM;
	//当前执行指令
	int nEIP;

	//判断标志位
	//	<=	<	==	>	>=
	//	1	2	3	4	5
	char nFlag;
	//输出Edit
	CEdit *m_pEdtCmdTxUt;


	//默认延迟时间
	int m_nSleep;
	//标识数量
	int m_nStrStack;
	//标识结构体，标志名字，和值
	StrStack *m_pStrStack;
	//释放内部资源
	void DeleteStrStack();
	//创建并初始化线程
	UINT Create( CHTMLDlg *Wnd );
	//启动线程
	UINT Start();
	//暂停线程
	UINT Pause();
	//停止线程
	UINT Stop();
	//清空线程信息
	UINT Clear();

};
