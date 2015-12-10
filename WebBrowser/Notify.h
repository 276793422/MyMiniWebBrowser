//////////////////////////////////////////////////////////////////////////
//
//	Notify.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////


#ifndef _MY_NOTIFY_CLASS_
#define _MY_NOTIFY_CLASS_



class CNotify
{
public:
	CNotify();
	~CNotify();

	//以下创建函数参数
	//TCHAR *Str	：为托盘上显示的字符串
	//CWnd *pWnd	：为父窗口指针
	//UINT IconID	：为托盘图标ID
	//UINT MsgCB	：托盘消息类型	（默认为	WM_COMMAND	消息）
	//UINT Flg		：托盘风格		（默认值	NIF_ICON | NIF_MESSAGE | NIF_TIP）
	CNotify( TCHAR *Str , 
			CWnd *pWnd , 
			UINT IconID , 
			UINT MsgCB = WM_COMMAND , 
			UINT Flg = NIF_ICON | NIF_MESSAGE | NIF_TIP );

	//创建这个系统托盘图标
	void Create( TCHAR *Str , 
				CWnd *pWnd , 
				UINT IconID , 
				UINT MsgCB = WM_COMMAND , 
				UINT Flg = NIF_ICON | NIF_MESSAGE | NIF_TIP );

	//重建这个系统托盘图标，参数1：将要重建的图表索引
	void ReCreate( int NtiID , 
					TCHAR *Str , 
					CWnd *pWnd , 
					UINT IconID , 
					UINT MsgCB = WM_COMMAND , 
					UINT Flg = NIF_ICON | NIF_MESSAGE | NIF_TIP );
	//追加一个系统托盘图标
	void AddNotify( TCHAR *Str , 
					CWnd *pWnd , 
					UINT IconID , 
					UINT MsgCB = WM_COMMAND , 
					UINT Flg = NIF_ICON | NIF_MESSAGE | NIF_TIP );
	//自定义显示第几个托盘图标
	void MakeOut( int index );

	//清空托盘
	void MakeNull();
	//重建写入备用托盘变量
	void MakeBack();


	//系统托盘变量指针
	NOTIFYICONDATA *m_nd;
	//指针内有多少个托盘变量
	int m_nNtiNum;
	//当前显示的是第几个托盘变量
	int m_nNtiID;
	//备用系统托盘变量
	NOTIFYICONDATA m_ndback;


	//添加菜单
	void AddMenu( UINT MenuID );
	//弹出菜单
	void MakeOutMenu( CWnd * pWnd );
	//托盘菜单、ID
	UINT m_MenuID;

};


#endif