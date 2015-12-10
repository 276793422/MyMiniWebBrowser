//////////////////////////////////////////////////////////////////////////
//
//	Notify.cpp
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Notify.h"



CNotify::CNotify()
{
	m_nd = NULL;
	m_MenuID = -1;
	m_nNtiNum = 0;
	m_nNtiID = 0;
	m_ndback.cbSize = 0;
}

CNotify::~CNotify()
{
	::Shell_NotifyIcon( NIM_DELETE , m_nd );
	if ( NULL != m_nd )
	{
		free( m_nd );
	}
}


CNotify::CNotify( TCHAR *Str , 
				 CWnd *pWnd , 
				 UINT IconID , 
				 UINT MsgCB , 
				 UINT Flg )
{
	if ( NULL != m_nd )
	{
		free( m_nd );
	}
	m_nd = (NOTIFYICONDATA *) malloc( sizeof ( NOTIFYICONDATA ) );

	m_nd[0].cbSize=(sizeof(NOTIFYICONDATA));
	m_nd[0].hWnd = pWnd->m_hWnd;
	m_nd[0].hIcon = AfxGetApp()->LoadIcon(IconID);
	m_nd[0].uCallbackMessage = MsgCB;
	m_nd[0].uID = 0;
	m_nd[0].uFlags = Flg;
	wcscpy_s( m_nd[0].szTip , _T("黑色") );
	::Shell_NotifyIcon( NIM_ADD , &m_nd[0] );

	m_nNtiID = 1;
	m_nNtiNum = 1;
	memcpy_s( &m_ndback , sizeof(m_ndback) , m_nd , sizeof(NOTIFYICONDATA) );
}

void CNotify::Create( TCHAR *Str , 
					 CWnd *pWnd , 
					 UINT IconID , 
					 UINT MsgCB , 
					 UINT Flg )
{
	if ( NULL != m_nd )
	{
		free( m_nd );
		m_nNtiNum = 0;
	}
	m_nd = (NOTIFYICONDATA *) malloc( sizeof ( NOTIFYICONDATA ) );

	m_nd[0].cbSize=(sizeof(NOTIFYICONDATA));
	m_nd[0].hWnd = pWnd->m_hWnd;
	m_nd[0].hIcon = AfxGetApp()->LoadIcon(IconID);
	m_nd[0].uCallbackMessage = MsgCB;
	m_nd[0].uID = 0;
	m_nd[0].uFlags = Flg;
	wcscpy_s( m_nd[0].szTip , Str );
	::Shell_NotifyIcon( NIM_ADD , &m_nd[0] );

	m_nNtiID = 1;
	m_nNtiNum = 1;
	memcpy_s( &m_ndback , sizeof(m_ndback) , m_nd , sizeof(NOTIFYICONDATA) );
}

void CNotify::ReCreate( int NtiID , 
					   TCHAR *Str , 
					   CWnd *pWnd , 
					   UINT IconID , 
					   UINT MsgCB , 
					   UINT Flg )
{
	if ( NtiID < 1 || m_nNtiNum < NtiID )
	{
		return;
	}
	m_nd[NtiID - 1].cbSize=(sizeof(NOTIFYICONDATA));
	m_nd[NtiID - 1].hWnd = pWnd->m_hWnd;
	m_nd[NtiID - 1].hIcon = AfxGetApp()->LoadIcon(IconID);
	m_nd[NtiID - 1].uCallbackMessage = MsgCB;
	m_nd[NtiID - 1].uID = 0;
	m_nd[NtiID - 1].uFlags = Flg;
	wcscpy_s( m_nd[NtiID - 1].szTip , Str );

}

//追加一个系统托盘图标
void CNotify::AddNotify( TCHAR *Str , 
						CWnd *pWnd , 
						UINT IconID , 
						UINT MsgCB, 
						UINT Flg )
{
	if ( 0 == m_nNtiNum )
	{
		return;
	}

	NOTIFYICONDATA *tnd =  (NOTIFYICONDATA *) malloc( sizeof ( NOTIFYICONDATA ) * ( m_nNtiNum + 1 ) );

	tnd[m_nNtiNum].cbSize = ( sizeof ( NOTIFYICONDATA ) );
	tnd[m_nNtiNum].hWnd = pWnd->m_hWnd;
	tnd[m_nNtiNum].hIcon = AfxGetApp()->LoadIcon(IconID);
	tnd[m_nNtiNum].uCallbackMessage = MsgCB;
	tnd[m_nNtiNum].uID = 0;
	tnd[m_nNtiNum].uFlags = Flg;
	wcscpy_s( tnd[m_nNtiNum].szTip , Str );

	memcpy_s( tnd , sizeof(NOTIFYICONDATA) , m_nd , sizeof(NOTIFYICONDATA) * m_nNtiNum );
	m_nNtiNum++;

	free( m_nd );
	m_nd = tnd;
}

//清空托盘
void CNotify::MakeNull()
{
	m_nNtiNum = 0;
	if ( NULL != m_nd )
	{
		free( m_nd );
		m_nd = NULL;
	}
}

//重建写入备用托盘变量
void CNotify::MakeBack()
{
	if ( 0 == m_ndback.cbSize )
	{
		return;
	}
	if ( NULL != m_nd )
	{
		free( m_nd );
		m_nd = NULL;
	}

	m_nd = (NOTIFYICONDATA *) malloc( sizeof ( NOTIFYICONDATA ) );

	memcpy_s( m_nd , sizeof(NOTIFYICONDATA) , &m_ndback , sizeof(m_ndback) );
	m_nNtiNum = 1;

}

//自定义显示第几个托盘图标
void CNotify::MakeOut( int index )
{
	if ( index < 1 || m_nNtiNum < index )
	{
		return;
	}

	::Shell_NotifyIcon( NIM_MODIFY , &m_nd[ index - 1 ] );
	m_nNtiID = index;
}

//添加菜单
void CNotify::AddMenu( UINT MenuID )
{
	m_MenuID = MenuID;
}

//弹出菜单
void CNotify::MakeOutMenu( CWnd * pWnd )
{
	if ( -1 == m_MenuID )
	{
		return;
	}

	CMenu m_mymenu;

	m_mymenu.LoadMenu(m_MenuID);

	CPoint point;

	GetCursorPos(&point);

	m_mymenu.GetSubMenu(0)->TrackPopupMenu( TPM_LEFTALIGN ,
											point.x ,
											point.y ,
											pWnd );

	m_mymenu.Detach();
}
