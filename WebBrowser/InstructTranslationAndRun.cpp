//////////////////////////////////////////////////////////////////////////
//
//	InstructTranslationAndRun.cpp
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "InstructTranslationAndRun.h"
#include "HTMLDlg.h"
#include "ThreadCommandWork.h"

CInstructTranslationAndRun::CInstructTranslationAndRun()
{
	Create();
}

CInstructTranslationAndRun::~CInstructTranslationAndRun()
{
}

void CInstructTranslationAndRun::Create()
{

	m_InstructList[0].m_StrInstruct = _T("开始工作：工作从此处开始，有且只能有一个") ;
	m_InstructList[0].m_nID = 0;

	m_InstructList[1].m_StrInstruct = _T("结束工作：工作从此处结束，有且只能有一个") ;
	m_InstructList[1].m_nID = 1;

	m_InstructList[2].m_StrInstruct = _T("使用代理：自动使用代理页代理表中的选择的代理") ;
	m_InstructList[2].m_nID = 2;

	m_InstructList[3].m_StrInstruct = _T("停止代理：停止使用代理") ;
	m_InstructList[3].m_nID = 3;

	m_InstructList[4].m_StrInstruct = _T("重选代理：选择下一个代理") ;
	m_InstructList[4].m_nID = 4;

	m_InstructList[5].m_StrInstruct = _T("刷新页面：刷新当前网页") ;
	m_InstructList[5].m_nID = 5;

	m_InstructList[6].m_StrInstruct = _T("自动填表：照左表填写") ;
	m_InstructList[6].m_nID = 6;

	m_InstructList[7].m_StrInstruct = _T("延迟？秒：附加信息为延迟时间，单位毫秒") ;
	m_InstructList[7].m_nID = 7;

	m_InstructList[8].m_StrInstruct = _T("点击按钮：附加信息为按钮上的名字，不一定成功") ;
	m_InstructList[8].m_nID = 8;

	m_InstructList[9].m_StrInstruct = _T("打开指定：附加信息为打开网页的地址") ;
	m_InstructList[9].m_nID = 9;

	m_InstructList[10].m_StrInstruct = _T("设置标志：附加信息为标志，在开始工作之前设置，相同标志，整个程序只能拥有一个") ;
	m_InstructList[10].m_nID = 10;

	m_InstructList[11].m_StrInstruct = _T("操作标志：附加信息为要操作的标志，操作类型可以是算数运算") ;
	m_InstructList[11].m_nID = 11;

	m_InstructList[12].m_StrInstruct = _T("判断标志：附加信息为标志及条件，可以是标志或者关键字，结果保留到下次条件跳") ;
	m_InstructList[12].m_nID = 12;

	m_InstructList[13].m_StrInstruct = _T("成功则跳：附加信息为跳转的位置，上一句为判断标志，标志判断成功，此句跳转") ;
	m_InstructList[13].m_nID = 13;

	m_InstructList[14].m_StrInstruct = _T("失败则跳：附加信息为跳转的位置，上一句为判断标志，标志判断失败，此句跳转") ;
	m_InstructList[14].m_nID = 14;

	m_InstructList[15].m_StrInstruct = _T("无条件跳：附加信息为跳转的流程位置") ;
	m_InstructList[15].m_nID = 15;

	m_InstructList[16].m_StrInstruct = _T("循环起点：附加信息为数字，为循环次数下一句就是循环开始，下一个循环终点就是结尾") ;
	m_InstructList[16].m_nID = 16;

	m_InstructList[17].m_StrInstruct = _T("循环终点：附加信息为数字，为循环起始的位置，如果目标位置不是循环起点，那么此点无效") ;
	m_InstructList[17].m_nID = 17;

	m_InstructList[18].m_StrInstruct = _T("默认延迟：附加信息为默认延迟时间，单位毫秒，需在整个流程最开始处定义") ;
	m_InstructList[18].m_nID = 18;

	m_InstructList[19].m_StrInstruct = _T("打开网页：打开控制信息中，列表中的当前索引的网页") ;
	m_InstructList[19].m_nID = 19;

	m_InstructList[20].m_StrInstruct = _T("重选网页：选择控制信息中，列表中的下一个网页") ;
	m_InstructList[20].m_nID = 20;

	m_InstructList[21].m_StrInstruct = _T("提取连接：按照控制信息中，提取连接标记中的信息来提取网页连接") ;
	m_InstructList[21].m_nID = 21;

	m_InstructList[22].m_StrInstruct = _T("保存信息：按照控制信息中，地址栏给出的文件位置保存信息为文件") ;
	m_InstructList[22].m_nID = 22;

	m_InstructList[23].m_StrInstruct = _T("") ;
	m_InstructList[23].m_nID = 0xFFFFFFFF;

	//m_InstructList[23].m_StrInstruct = _T("等待网页：等待网页加载成功，不成功就一直等待") ;
	//m_InstructList[23].m_nID = 23;
	m_nInstructNum = MY_INSTRUCT_NUM;
}

//执行指令，返回值是指令是否正确执行，0为执行失败，参数1：执行的指令类型，参数2：指令参数
int CInstructTranslationAndRun::RunInstruct( int nInstruct , CString &strInstruct , int Sid )
{
	int rtn = 0;
	switch(nInstruct)
	{
	case 2:		rtn = Fun2(strInstruct , Sid );		break;/*完	*/	// 2	使用代理：自动使用代理页代理表中的选择的代理
	case 3:		rtn = Fun3(strInstruct , Sid );		break;/*完	*/	// 3	停止代理：停止使用代理
	case 4:		rtn = Fun4(strInstruct , Sid );		break;/*完	*/	// 4	重选代理：选择下一个代理
	case 5:		rtn = Fun5(strInstruct , Sid );		break;/*完	*/	// 5	刷新页面：刷新上一个打开的网页
	case 6:		rtn = Fun6(strInstruct , Sid );		break;/*完	*/	// 6	自动填表：照左表填写
	case 7:		rtn = Fun7(strInstruct , Sid );		break;/*完	*/	// 7	延迟？秒：附加信息为延迟时间，单位毫秒
	case 8:		rtn = Fun8(strInstruct , Sid );		break;			// 8	点击按钮：附加信息为按钮上的名字，不一定成功
	case 9:		rtn = Fun9(strInstruct , Sid );		break;/*完	*/	// 9	打开网页：附加信息为打开网页的地址
	case 11:	rtn = Fun11(strInstruct , Sid );	break;/*完	*/	// 11	操作标志：附加信息为要操作的标志，操作类型可以是逻辑运算与算数运算
	case 12:	rtn = Fun12(strInstruct , Sid );	break;/*完	*/	// 12	判断标志：附加信息为标志及条件，可以是标志或者关键字，结果只保留到下一语句
	case 13:	rtn = Fun13(strInstruct , Sid );	break;/*完	*/	// 13	成功则跳：附加信息为跳转的位置，上一句为判断标志，标志判断成功，此句跳转
	case 14:	rtn = Fun14(strInstruct , Sid );	break;/*完	*/	// 14	失败则跳：附加信息为跳转的位置，上一句为判断标志，标志判断失败，此句跳转
	case 15:	rtn = Fun15(strInstruct , Sid );	break;/*完	*/	// 15	无条件跳：附加信息为跳转的流程位置
	case 16:	rtn = Fun16(strInstruct , Sid );	break;/*完	*/	// 16	循环起点：附加信息为数字，为循环次数下一句就是循环开始，下一个循环终点就是结尾
	case 17:	rtn = Fun17(strInstruct , Sid );	break;/*完	*/	// 17	循环终点：附加信息为数字，为循环起始的位置，如果目标位置不是循环起点，那么将是死循环
	case 18:	rtn = Fun18(strInstruct , Sid );	break;/*完	*/	// 18	默认延迟：附加信息为默认延迟时间，单位毫秒，需在整个流程最开始处定义
	case 19:	rtn = Fun19(strInstruct , Sid );	break;/*完	*/	// 19	打开网页：打开控制信息中，列表中的当前索引的网页
	case 20:	rtn = Fun20(strInstruct , Sid );	break;/*完	*/	// 20	重选网页：选择控制信息中，列表中的下一个网页
	case 21:	rtn = Fun21(strInstruct , Sid );	break;/*完	*/	// 21	提取连接：按照控制信息中，提取连接标记中的信息来提取网页连接
	case 22:	rtn = Fun22(strInstruct , Sid );	break;			// 22	保存信息：按照控制信息中，地址栏给出的文件位置保存信息为文件
	}

	return rtn;
}

//判断指令的附加信息是否合法，返回值0为合法，1为不合法
int CInstructTranslationAndRun::TestInstruct( CListCtrl * const m_LclCmd )
{

	//	0	序号	1	指令解释	2	附加信息
	int all = m_LclCmd[0].GetItemCount();
	short *nbs = (short *)malloc( sizeof(short) * all );
	memset( nbs , 0 , ( sizeof(short) * all ) );
	CString str;
	int i = 0;
	//////////////////////////////////////////////////////////////////////////
	//取全部指令的编号
	for ( i = 0 ; i < all ; i++ )
	{
		nbs[i] = TranslateInstruct( m_LclCmd[0].GetItemText( i , 1 ) );
	}
	//////////////////////////////////////////////////////////////////////////
	//判断最开始是否有且只有一个设置基础延迟
	if ( 18 != nbs[0] )
	{
		m_StrError.Format( _T("第一个必须是默认延迟时间\r\n序号：%d") , i );
		free( nbs );
		nbs = NULL;
		return 1;
	}
	for ( i = 1 ; i < all ; i++ )
	{
		if ( 18 == nbs[i] )
		{
			m_StrError.Format( _T("只能有一个默认延迟时间\r\n序号：%d") , i );
			free( nbs );
			nbs = NULL;
			return 1;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//判断开始点是否存在
	for ( i = 0 ; i < all ; i++ )
	{
		if ( 0 == nbs[i] )
		{
			break;
		}
	}
	if ( i == all )
	{
		m_StrError.Format( _T("必须要有一个开始\r\n序号：%d") , i );
		free( nbs );
		nbs = NULL;
		return 1;
	}
	//////////////////////////////////////////////////////////////////////////
	//查看开始之前，是否有杂项
	for ( i = 0 ; i < all ; i++ )
	{
		if ( 0 == nbs[i] )
		{
			for ( i = i - 1 ; i > 0 ; i-- )
			{
				if ( 10 != nbs[i] )
				{
					m_StrError.Format( _T("开始之前只能有设置标志和默认延迟\r\n序号：%d") , i );
					free( nbs );
					nbs = NULL;
					return 1;
				}
			}
			if ( i <= 0 )
			{
				break;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//判断结束点是否存在
	for ( i = 0 ; i < all ; i++ )
	{
		if ( 1 == nbs[i] )
		{
			break;
		}
	}
	if ( i == all )
	{
		m_StrError.Format( _T("必须有一个结束\r\n序号：%d") , i );
		free( nbs );
		nbs = NULL;
		return 1;
	}
	if ( i != all - 1 )
	{
		m_StrError.Format( _T("结束必须在指令的最尾部\r\n序号：%d") , i );
		free( nbs );
		nbs = NULL;
		return 1;
	}
	//////////////////////////////////////////////////////////////////////////
	//判断是否有多个开始标志
	for ( i = 0 ; i < all ; i++ )
	{
		if ( 0 == nbs[i] )
		{
			for ( i++ ; i < all ; i++ )
			{
				if ( 0 == nbs[i] )
				{
					m_StrError.Format( _T("只能有一个开始\r\n序号：%d") , i );
					free( nbs );
					nbs = NULL;
					return 1;
				}
				if ( 10 == nbs[i] )
				{
					m_StrError.Format( _T("标志必须在开始前设定\r\n序号：%d") , i );
					free( nbs );
					nbs = NULL;
					return 1;
				}
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//判断是否有多个结束标志
	for ( i = 0 ; i < all ; i++ )
	{
		if ( 1 == nbs[i] )
		{
			for ( i++ ; i < all ; i++ )
			{
				if ( 1 == nbs[i] )
				{
					m_StrError.Format( _T("只能有一个结束\r\n序号：%d") , i );
					free( nbs );
					nbs = NULL;
					return 1;
				}
				if ( 0 == nbs[i] )
				{
					m_StrError.Format( _T("开始必须在结束前\r\n序号：%d") , i );
					free( nbs );
					nbs = NULL;
					return 1;
				}
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//判断延迟信息是否合法，不合法则纠正，不会报错
	for ( i = 0 ; i < all ; i++ )
	{
		if ( 18 == nbs[i] || 7 == nbs[i] )
		{
			str = m_LclCmd[0].GetItemText( i , 2 );
			if ( stol( str , 0 , 10 ) < 1 )
			{
				str = _T("0");
			}
			m_LclCmd[0].SetItemText( i , 2 , str );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//判断网页格式
	for ( i = 0 ; i < all ; i++ )
	{
		if ( 5 == nbs[i] || 9 == nbs[i] )
		{
			str = m_LclCmd[0].GetItemText( i , 2 );
			int m , n;
			m = str.Find( _T('.') );
			n = str.ReverseFind( _T('.') );
			if ( 0 == m || ( m + 1 ) == n || n == ( str.GetLength() - 1 ) )
			{
				m_StrError.Format( _T("要打开的网页格式不对\r\n序号：%d") , i );
				free( nbs );
				nbs = NULL;
				return 1;
			}
			m_LclCmd[0].SetItemText( i , 2 , str );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//操作格式
	for ( i = 0 ; i < all ; i++ )
	{
		if ( 11 == nbs[i] )
		{
			int j = 0;
			int k = 0;
			str = m_LclCmd[0].GetItemText( i , 2 );
			TCHAR tchar[] = { _T('+') , _T('-') , _T('*') , _T('/') , _T('%') , _T('=') };
			for ( k = 0 ; k < 6 ; k++ )
			{
				j = str.Find( tchar[k] );
				if( -1 != j )
				{
					break;
				}
			}
			if ( k == 6 )
			{
				m_StrError.Format( _T("错误操作\r\n序号：%d") , i );
				free( nbs );
				nbs = NULL;
				return 1;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//判断格式
	for ( i = 0 ; i < all ; i++ )
	{
		if ( 12 == nbs[i] )
		{
			int j = 0;
			int k = 0;
			str = m_LclCmd[0].GetItemText( i , 2 );
			TCHAR *tchar[] = { _T("<=") , _T("<") , _T(">=") , _T(">") , _T("==") };
			for ( k = 0 ; k < 5 ; k++ )
			{
				j = str.Find( tchar[k] );
				if( -1 != j )
				{
					break;
				}
			}
			if ( k == 5 )
			{
				m_StrError.Format( _T("判断操作\r\n序号：%d") , i );
				free( nbs );
				nbs = NULL;
				return 1;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//判断循环终点
	int j = 0;
	for ( i = 0 ; i < all ; i++ )
	{
		if ( 0 == nbs[i] )
		{
			j = i ;
		}
		if ( 17 == nbs[i] )
		{
			if ( TranslateInstruct( m_LclCmd[0].GetItemText( i , 1 ) ) < ( j + 1 ) )
			{
				m_StrError.Format( _T("循环错误，不能循环回开始点之前\r\n序号：%d") , i );
				free( nbs );
				nbs = NULL;
				return 1;
			}
			if ( stol( str , 0 , 10 ) == i )
			{
				m_StrError.Format( _T("循环错误，不能指向自己\r\n序号：%d") , i );
				free( nbs );
				nbs = NULL;
				return 1;
			}
		}
	}


	free( nbs );
	nbs = NULL;
	return 0;
}

//翻译指令，返回值是翻译得到的指令值，-1为翻译失败，其他值为成功
int CInstructTranslationAndRun::TranslateInstruct( CString &strInstruct )
{
	for ( UINT i = 0 ; i < m_nInstructNum ; i++ )
	{
		if ( strInstruct.Left(4) == m_InstructList[i].m_StrInstruct.Left(4) )
		{
			return i;
		}
	}
	return -1;
}


// 2	使用代理：自动使用代理页代理表中的选择的代理
UINT CInstructTranslationAndRun::Fun2( CString &strInstruct , int Sid )
{
	strInstruct = m_pParent->m_DlgProxy.m_LclProxyList.GetItemText( m_pWorkThread->m_nProxyIndex , 0 );
	if ( 0 == m_pParent->SetMyIeProxy( strInstruct ) )
	{
		strInstruct.Format( _T("%d：使用失败：%d|%s") , Sid , m_pWorkThread->m_nProxyIndex , strInstruct );
		m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
		return 1;
	}
	strInstruct.Format( _T("%d：使用成功：%d|%s") , Sid , m_pWorkThread->m_nProxyIndex , strInstruct );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
	return 0;
}

// 3	停止代理：停止使用代理
UINT CInstructTranslationAndRun::Fun3( CString &strInstruct , int Sid )
{
	if ( 0 == m_pParent->DelMyIeProxy(  ) )
	{
		strInstruct.Format( _T("%d：停用失败：%d") , Sid , m_pWorkThread->m_nProxyIndex  );
		m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
		return 1;
	}
	strInstruct.Format( _T("%d：停用成功：%d") , Sid , m_pWorkThread->m_nProxyIndex  );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
	return 0;
}

// 4	重选代理：选择下一个代理
UINT CInstructTranslationAndRun::Fun4( CString &strInstruct , int Sid )
{
	CString str ;
	m_pWorkThread->m_nProxyIndex++;
	if ( m_pParent->m_DlgProxy.m_LclProxyList.GetItemCount() == m_pWorkThread->m_nProxyIndex )
	{
		m_pWorkThread->m_nProxyIndex = 0;
	}
	strInstruct = m_pParent->m_DlgProxy.m_LclProxyList.GetItemText( m_pWorkThread->m_nProxyIndex , 0 );
	str.Format( _T("%d：重选代理成功：%d|%s") , Sid , m_pWorkThread->m_nProxyIndex , strInstruct );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( str );
	return 0;
}

// 5	刷新页面：刷新上一个打开的网页
UINT CInstructTranslationAndRun::Fun5( CString &strInstruct , int Sid )
{
	m_pParent->m_EdtURL.GetWindowText( strInstruct );
	m_pParent->m_HtmlView->Navigate2( strInstruct );;
	strInstruct.Format( _T("%d：刷新页面成功：%s") , Sid , strInstruct );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
	return 0;
}

// 6	自动填表：照左表填写
UINT CInstructTranslationAndRun::Fun6( CString &strInstruct , int Sid )
{
	m_pParent->OnBnClickedButtonFillTheForm();
	strInstruct.Format( _T("%d：自动填表成功") , Sid );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
	return 0;
}

// 7	延迟？秒：附加信息为延迟时间，单位毫秒
UINT CInstructTranslationAndRun::Fun7( CString &strInstruct , int Sid )
{
	CString str ;
	Sleep( stol( strInstruct , 0 , 10 ) );
	str.Format( _T("%d：延迟成功：%s") , Sid , strInstruct );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( str );

	return 0;
}

// 8	点击按钮：附加信息为按钮上的名字，但不一定成功
UINT CInstructTranslationAndRun::Fun8( CString &strInstruct , int Sid )
{
	m_pParent->m_HtmlView->ClickButton( strInstruct );

	return 0;
}

// 9	打开网页：附加信息为打开网页的地址
UINT CInstructTranslationAndRun::Fun9( CString &strInstruct , int Sid )
{
	m_pParent->m_HtmlView->Navigate2( strInstruct );
	CString str = strInstruct;
	strInstruct.Format( _T("%d：网页打开成功：%s") , Sid , str );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
	return 0;
}

// 10	设置标志：附加信息为标志，在开始工作之前设置，相同标志，整个程序只能拥有一个
UINT CInstructTranslationAndRun::Fun10( CString &strInstruct , int Sid )
{
	m_pWorkThread->m_pStrStack[Sid-1].Str = new CString( strInstruct );
	*(m_pWorkThread->m_pStrStack[Sid-1].Str) = strInstruct.Left( 5 );
	m_pWorkThread->m_pStrStack[Sid-1].nStack = 0;
	strInstruct.Format( _T("%d：设置标识：%s = 0") , Sid , *(m_pWorkThread->m_pStrStack[Sid-1].Str) );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
	return 0;
}

// 11	操作标志：附加信息为要操作的标志，操作类型可以是逻辑运算与算数运算
UINT CInstructTranslationAndRun::Fun11( CString &strInstruct , int Sid )
{
	CString str2;
	int i = 0;
	int j = 0;
	TCHAR tchar[] = { _T('+') , _T('-') , _T('*') , _T('/') , _T('%') , _T('=') };
	for ( i = 0 ; i < 6 ; i++ )
	{
		j = strInstruct.Find( tchar[i] );
		if( -1 != j )
		{
			break;
		}
	}
	if ( 6 == i )
	{
		strInstruct.Format( _T("%d：字串不符合要求") , Sid );
		m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
		return 0;
	}
	str2 = strInstruct.Left( j );
	strInstruct.Delete( 0 , j + 1 );
	int k = i;
	// str2 是标志  i 是符号  strInstruct 是值
	for ( i = 0 ; i < m_pWorkThread->m_nStrStack ; i++ )
	{
		if ( *(m_pWorkThread->m_pStrStack[i].Str) == str2 )
		{
			break;
		}
	}
	if ( i == m_pWorkThread->m_nStrStack )
	{
		strInstruct.Format( _T("%d：找不到匹配标志") , Sid );
		m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
		return 0;
	}
	switch( k )
	{//{ _T('+') , _T('-') , _T('*') , _T('/') , _T('%') , _T('=') };
	case 0:	m_pWorkThread->m_pStrStack[i].nStack += stol( strInstruct , 0 , 10 );	break;
	case 1:	m_pWorkThread->m_pStrStack[i].nStack -= stol( strInstruct , 0 , 10 );	break;
	case 2:	m_pWorkThread->m_pStrStack[i].nStack *= stol( strInstruct , 0 , 10 );	break;
	case 3:	m_pWorkThread->m_pStrStack[i].nStack /= stol( strInstruct , 0 , 10 );	break;
	case 4:	m_pWorkThread->m_pStrStack[i].nStack %= stol( strInstruct , 0 , 10 );	break;
	case 5:	m_pWorkThread->m_pStrStack[i].nStack = stol( strInstruct , 0 , 10 );	break;
	}

	strInstruct.Format( _T("%d：标识操作完成：%d") , Sid , m_pWorkThread->m_pStrStack[i].nStack );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
	return 0;
}

// 12	判断标志：附加信息为标志及条件，可以是标志或者关键字，结果只保留到下一语句
UINT CInstructTranslationAndRun::Fun12( CString &strInstruct , int Sid )
{
	CString str2;
	int i = 0;
	int j = 0;
	TCHAR *tchar[] = { _T("<=") , _T("<") , _T(">=") , _T(">") , _T("==") };
	for ( i = 0 ; i < 5 ; i++ )
	{
		j = strInstruct.Find( tchar[i] );
		if( -1 != j )
		{
			break;
		}
	}
	if ( 5 == i )
	{
		strInstruct.Format( _T("%d：字串不符合要求") , Sid );
		m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
		return 0;
	}
	str2 = strInstruct.Left( j );
	if ( i == 1 || i == 3 )
	{
		strInstruct.Delete( 0 , j + 1 );
	}
	else
	{
		strInstruct.Delete( 0 , j + 2 );
	}
	int k = i;
	// str2 是标志  i 是符号  strInstruct 是值
	for ( i = 0 ; i < m_pWorkThread->m_nStrStack ; i++ )
	{
		if ( *(m_pWorkThread->m_pStrStack[i].Str) == str2 )
		{
			break;
		}
	}
	if ( i == m_pWorkThread->m_nStrStack )
	{
		strInstruct.Format( _T("%d：找不到匹配标志") , Sid );
		m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
		return 0;
	}
	switch( k )
	{//{ _T("<=") , _T("<") , _T(">=") , _T(">") , _T("==") };
	case 0:	m_pWorkThread->nFlag = ( m_pWorkThread->m_pStrStack[i].nStack <= stol( strInstruct , 0 , 10 ) ) ;	break;
	case 1:	m_pWorkThread->nFlag = ( m_pWorkThread->m_pStrStack[i].nStack < stol( strInstruct , 0 , 10 ) ) ;	break;
	case 2:	m_pWorkThread->nFlag = ( m_pWorkThread->m_pStrStack[i].nStack >= stol( strInstruct , 0 , 10 ) ) ;	break;
	case 3:	m_pWorkThread->nFlag = ( m_pWorkThread->m_pStrStack[i].nStack > stol( strInstruct , 0 , 10 ) ) ;	break;
	case 4:	m_pWorkThread->nFlag = ( m_pWorkThread->m_pStrStack[i].nStack == stol( strInstruct , 0 , 10 ) ) ;	break;
	}

	strInstruct.Format( _T("%d：标识判断完成：%d") , Sid , m_pWorkThread->nFlag );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
	return 0;
}

// 13	成功则跳：附加信息为跳转的位置，上一句为判断标志，标志判断成功，此句跳转
UINT CInstructTranslationAndRun::Fun13( CString &strInstruct , int Sid )
{
	if ( 0 == m_pWorkThread->nFlag )
	{
		m_pWorkThread->nFlag = -1;
		strInstruct.Format( _T("%d：跳转失败") , Sid );
		m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
		return 0;
	}
	m_pWorkThread->nEIP = stol( strInstruct , 0 , 10 );
	strInstruct.Format( _T("%d：跳转成功，目标：%d") , Sid , m_pWorkThread->nEIP );
	m_pWorkThread->nFlag = -1;
	m_pWorkThread->nEIP--;
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
	return 0;
}

// 14	失败则跳：附加信息为跳转的位置，上一句为判断标志，标志判断失败，此句跳转
UINT CInstructTranslationAndRun::Fun14( CString &strInstruct , int Sid )
{
	if ( 1 == m_pWorkThread->nFlag )
	{
		m_pWorkThread->nFlag = -1;
		strInstruct.Format( _T("%d：跳转失败") , Sid );
		m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
		return 0;
	}
	strInstruct = m_pWorkThread->m_ListCtrl->GetItemText( Sid , 2 );
	m_pWorkThread->nEIP = stol( strInstruct , 0 , 10 );
	strInstruct.Format( _T("%d：跳转成功，目标：%d") , Sid , m_pWorkThread->nEIP );
	m_pWorkThread->nFlag = -1;
	m_pWorkThread->nEIP--;
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );

	return 0;
}

// 15	无条件跳：附加信息为跳转的流程位置
UINT CInstructTranslationAndRun::Fun15( CString &strInstruct , int Sid )
{
	m_pWorkThread->nEIP = stol( strInstruct , 0 , 10 );
	strInstruct.Format( _T("%d：跳转成功：%d") , Sid , m_pWorkThread->nEIP );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
	m_pWorkThread->nEIP--;
	return 0;
}

// 16	循环起点：附加信息为数字，为循环次数下一句就是循环开始，下一个循环终点就是结尾
UINT CInstructTranslationAndRun::Fun16( CString &strInstruct , int Sid )
{	//循环起点，什么都不用做知道有这么回事就行了。一切工作由循环终点操作。
	strInstruct.Format( _T("%d：循环起点设置成功：%s次") , Sid ,
											m_pWorkThread->m_ListCtrl->GetItemText( Sid , 2 ) );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
	return 0;
}

// 17	循环终点：附加信息为数字，为循环起始的位置，如果目标位置不是循环起点，那么此点无效
UINT CInstructTranslationAndRun::Fun17( CString &strInstruct , int Sid )
{
	CString str;
	int i = stol( strInstruct , 0 , 10 );
	str = m_pWorkThread->m_ListCtrl->GetItemText( i , 1 );
	if ( 16 == TranslateInstruct( str ) )
	{	//如果目标点是循环起点
		str = m_pWorkThread->m_ListCtrl->GetItemText( i , 2 );
		int j = stol( str , 0 , 10 );
		if ( j > 0 )
		{	//如果循环次数大于0
			j--;
			str.Format( _T("%d") , j );
			m_pWorkThread->m_ListCtrl->SetItemText( i , 2 , str );
			m_pWorkThread->nEIP = i;
			m_pWorkThread->nEIP--;
			str.Format( _T("%d：循环成功，跳转至：%d") , Sid , i );
			m_pParent->m_DlgList.SetWindowTextToCommandEdit( str );
			return 0;
		}
	}
	str.Format( _T("%d：目标点不是起点，或循环结束") , Sid );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( str );
	return 0;
}

// 18	默认延迟：附加信息为默认延迟时间，单位毫秒，需在整个流程最开始处定义
UINT CInstructTranslationAndRun::Fun18( CString &strInstruct , int Sid )
{
	m_pWorkThread->m_nSleep = stol( strInstruct , 0 , 10 );
	m_StrError.Format( _T("0：默认延迟设置完成：%d毫秒") , m_pWorkThread->m_nSleep );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( m_StrError );
	return 0;
}

UINT CInstructTranslationAndRun::Fun19( CString &strInstruct , int Sid )
{
	strInstruct = m_pParent->m_DlgCLI.m_LclCLICommandOpenURLList.GetItemText( 
							m_pWorkThread->m_nURLPageIndex , 0 );
	m_pParent->m_HtmlView->Navigate2( strInstruct );
	CString str;
	str.Format( _T("%d：网页打开成功：%s") , Sid , strInstruct );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( str );
	return 0;
}

UINT CInstructTranslationAndRun::Fun20( CString &strInstruct , int Sid )
{
	m_pWorkThread->m_nURLPageIndex++;
	if ( m_pWorkThread->m_nURLPageIndex >= 
				m_pParent->m_DlgCLI.m_LclCLICommandOpenURLList.GetItemCount() )
	{
		m_pWorkThread->m_nURLPageIndex = 0;
	}
	strInstruct.Format( _T("%d：重选网页成功，第：%d个") , Sid , m_pWorkThread->m_nURLPageIndex );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );

	return 0;
}

UINT CInstructTranslationAndRun::Fun21( CString &strInstruct , int Sid )
{
	while ( m_pParent->m_PrcTheHtmlViewOpenProcess.GetPos() != 100 )
	{
		Sleep( 20 );
	}

	CString str;
	m_pParent->m_HtmlView->GetSource( str );
	CString strFrom;
	CString strTo;
	CString strNum;
	CString strTemp;
	int i = 0;
	
	m_pParent->m_DlgCLI.m_EdtCLIGetTheURLOnPageWithHandSymbol.GetWindowText( strFrom );
	m_pParent->m_DlgCLI.m_EdtCLIGetTheURLOnPageWithHandAndLastNum.GetWindowText( strNum );
	m_pParent->m_DlgCLI.m_EdtCLIGetTheURLOnPageWithLastSymbol.GetWindowText( strTo );
	if ( strTo.IsEmpty() || strNum.IsEmpty() )
	{
		while ( 1 )
		{
			i = str.Find( strFrom );
			if ( -1 == i )
			{
				strInstruct.Format( _T("%d：获取资源成功，共：%d个") , Sid , 
							m_pParent->m_DlgCLI.m_LclCLIToGetTheElementFromPage.GetItemCount() );
				m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
				return 0;
			}
			str.Delete( 0 , i );
			i = str.Find( _T('\"') );
			strTemp = str.Left( i );
			m_pParent->m_DlgCLI.m_LclCLIToGetTheElementFromPage.InsertItem( 0 , strTemp );
			strTo.Format( _T("%d") , m_pParent->m_DlgCLI.m_LclCLIToGetTheElementFromPage.GetItemCount() + 1 );
			m_pParent->m_DlgCLI.m_StcCLIElementListCount.SetWindowText( strTo );
			str.Delete( 0 , i + 1 );
		}
	}

	int lenth = strFrom.GetLength();
	int nbt = 0 ;
	int j = 0;
	if ( strNum == _T('*') )
	{
		nbt = -1;
	}
	else
	{
		nbt = stol( strNum , 0 , 10 );
	}
	lenth += nbt;
	nbt = strTo.GetLength();
	while ( 1 )
	{
		i = str.Find( strFrom );
		if ( -1 == i )
		{
			strInstruct.Format( _T("%d：获取资源成功，共：%d个") , Sid , 
						m_pParent->m_DlgCLI.m_LclCLIToGetTheElementFromPage.GetItemCount() );
			m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
			return 0;
		}
		str.Delete( 0 , i + strFrom.GetLength() );
		i = 0;
		j = str.Find( strTo );
		if ( i == j )
		{
			continue;
		}
		strTemp = str.Left( j /*+ nbt*/ );
		m_pParent->m_DlgCLI.m_LclCLIToGetTheElementFromPage.InsertItem( 0 , strTemp );
		strTemp.Format( _T("%d") , m_pParent->m_DlgCLI.m_LclCLIToGetTheElementFromPage.GetItemCount() + 1 );
		m_pParent->m_DlgCLI.m_StcCLIElementListCount.SetWindowText( strTemp );
		str.Delete( 0 , j + nbt );
	}

	return 0;
}

UINT CInstructTranslationAndRun::Fun22( CString &strInstruct , int Sid )
{
	return 0;
}