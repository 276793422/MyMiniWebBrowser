#include "StdAfx.h"
#include "HookApi.h"

CHookApi::CHookApi()
{
	m_unHookStatus = 0;
	Clean();
}

CHookApi::~CHookApi()
{
}

void CHookApi::Clean()
{
	if ( 1 == m_unHookStatus )
	{
		UnHookApi();
	}

	m_strError = _T("");
	m_unSysFunAdd = 0;
	m_unMyFunAdd = 0;

	m_ucFunHead[0]	= 0;
	m_ucFunHead[1]	= 0;
	m_ucFunHead[2]	= 0;
	m_ucFunHead[3]	= 0;
	m_ucFunHead[4]	= 0;
	m_ucFunJMP[0]	= 0;
	m_ucFunJMP[1]	= 0;
	m_ucFunJMP[2]	= 0;
	m_ucFunJMP[3]	= 0;
	m_ucFunJMP[4]	= 0;

	m_unHookStatus = 0;
}

//创建一个HOOK
//参数1：要HOOK的函数
//参数2：该函数所在库的全名带后缀
//参数3：要改成的函数地址
UINT CHookApi::Create( char* strFunName , char* strLibName , LPVOID m_unMyFunAdd )
{
	if ( 0 != this->m_unSysFunAdd || 0 != this->m_unMyFunAdd )
	{
		m_strError = _T("内部已经HOOK一个函数了，需要取消并初始化HOOK");
		return 1;
	}

	if ( 0 == m_unMyFunAdd )
	{
		m_strError = _T("内部响应函数地址不正确");
		return 2;
	}

	//加载库
	HMODULE hModule = ::LoadLibraryA( strLibName );
	if ( 0 == hModule )
	{
		m_strError = _T("加载库失败");
		return 3;
	}

	//从库中获得函数的地址
	m_unSysFunAdd = GetProcAddress( hModule , strFunName );
	if ( 0 == m_unSysFunAdd )
	{
		m_strError = _T("获取函数地址失败");
		return 4;
	}
	//要HOOK的函数地址
	this->m_unMyFunAdd = m_unMyFunAdd;

	//构造跳转的5个字节
	m_ucFunJMP[0] = 0xE9;
	*(UINT*)(&m_ucFunJMP[1]) = (UINT)this->m_unMyFunAdd - (UINT)m_unSysFunAdd - 5;

	//保存原来的5个字节
	memcpy( m_ucFunHead , m_unSysFunAdd , 5 );

	return 0;
}


//加HOOK
UINT CHookApi::HookApi()
{
	if ( 1 == m_unHookStatus )
	{
		m_strError = _T("已HOOK，不用加");
		return 1;
	}

	if ( 0 == m_unSysFunAdd )
	{
		m_strError = _T("未初始化");
		return 2;
	}
	DWORD dwBytes;
	BOOL b = WriteProcessMemory(
		GetCurrentProcess(),
		m_unSysFunAdd,
		m_ucFunJMP,
		5,
		&dwBytes);

	m_unHookStatus = 1;
	return !b;
}

//解HOOK
UINT CHookApi::UnHookApi()
{
	if ( 0 == m_unHookStatus )
	{
		m_strError = _T("未HOOK，无解");
		return 1;
	}

	if ( 0 == m_unSysFunAdd )
	{
		m_strError = _T("未初始化");
		return 2;
	}
	DWORD dwBytes;
	BOOL b = WriteProcessMemory(
		GetCurrentProcess(),
		m_unSysFunAdd,
		m_ucFunHead,
		5,
		&dwBytes);

	m_unHookStatus = 0;
	return !b;
}