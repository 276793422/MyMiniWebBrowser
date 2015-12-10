//////////////////////////////////////////////////////////////////////////
//
//	InstructTranslationAndRun.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#pragma once

class CHTMLDlg;
class CThreadCommandWork;

//指令表中指令数量
#define MY_INSTRUCT_NUM 23

typedef struct _InstructList
{
	CString m_StrInstruct;
	UINT m_nID;
}InstructList;

class CInstructTranslationAndRun
{
public:
	CInstructTranslationAndRun();
	~CInstructTranslationAndRun();

private:
	//指令表内指令数量
	UINT m_nInstructNum;
	//指令表
	InstructList m_InstructList[MY_INSTRUCT_NUM+1] ;

	//初始化创建表
	void Create();

	//报错
	CString m_StrError;

public:
	//线程指针
	CThreadCommandWork *m_pWorkThread;
	//父窗口指针
	CHTMLDlg *m_pParent;
	//重载取指令
	const InstructList & operator[]( int i )	{	return m_InstructList[i];	}
	//获取指令表中指令数量
	int GetInstructNum()						{	return m_nInstructNum;		}
	//得到错误信息
	const CString &GetInstructError()			{	return m_StrError;			}

	//判断指令的附加信息是否合法，返回值0为合法，1为不合法
	int TestInstruct( CListCtrl * const m_LclCmd );

	//翻译指令，返回值是翻译得到的指令值，-1为翻译失败，其他值为成功
	int TranslateInstruct( CString &strInstruct );

	//执行指令，返回值是指令是否正确执行，0为执行失败
	//参数1：当前指令类型，根据此参数来判断该执行何语句
	//参数2：当前指令的附加信息，也就是参数，是直接传进执行语句中的
	//参数3：当前指令的Sid，也就是执行到第几条指令了，输出用
	int RunInstruct( int nInstruct , CString &strInstruct , int Sid );


	//	0	，	1	两个位置没有指向，0为开始，1为终止
	UINT Fun2( CString &strInstruct , int Sid );
	UINT Fun3( CString &strInstruct , int Sid );
	UINT Fun4( CString &strInstruct , int Sid );
	UINT Fun5( CString &strInstruct , int Sid );
	UINT Fun6( CString &strInstruct , int Sid );
	UINT Fun7( CString &strInstruct , int Sid );
	UINT Fun8( CString &strInstruct , int Sid );
	UINT Fun9( CString &strInstruct , int Sid );
	UINT Fun10( CString &strInstruct , int Sid );
	UINT Fun11( CString &strInstruct , int Sid );
	UINT Fun12( CString &strInstruct , int Sid );
	UINT Fun13( CString &strInstruct , int Sid );
	UINT Fun14( CString &strInstruct , int Sid );
	UINT Fun15( CString &strInstruct , int Sid );
	UINT Fun16( CString &strInstruct , int Sid );
	UINT Fun17( CString &strInstruct , int Sid );
	UINT Fun18( CString &strInstruct , int Sid );
	UINT Fun19( CString &strInstruct , int Sid );
	UINT Fun20( CString &strInstruct , int Sid );
	UINT Fun21( CString &strInstruct , int Sid );
	UINT Fun22( CString &strInstruct , int Sid );
};
