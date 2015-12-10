//////////////////////////////////////////////////////////////////////////
//
//						HOOKAPI类
//
//			全ANSI字符操作
//	初始化内部成员为空			void Clean();
//	返回错误信息				TCHAR * GetLastError() {	return m_strError;	};
//	初始化全部成员准备HOOK		UINT Create( char* strFunName , char* strLibName , LPVOID m_unMakeFunAdd );
//	加HOOK						UINT HookApi();
//	解HOOK						UINT UnHookApi();
//
//////////////////////////////////////////////////////////////////////////




#pragma once


class CHookApi
{
private:
	//错误信息
	TCHAR *m_strError;
	//要HOOK的函数地址				//要HOOK的函数地址上原来的5个字节数据
	LPVOID m_unSysFunAdd;			UCHAR m_ucFunHead[5];
	//要改成的函数地址				//HOOK时需要改的跳转到自定义函数的信息
	LPVOID m_unMyFunAdd;			UCHAR m_ucFunJMP[5];

	//HOOK状态，1为已HOOK，0为未HOOK
	UINT m_unHookStatus;

public:
	CHookApi();
	~CHookApi();

	//全局初始化
	void Clean();
	//返回错误信息
	TCHAR * GetLastError() {	return m_strError;	};
	//创建一个HOOK
	//参数1：要HOOK的函数
	//参数2：该函数所在库的全名带后缀
	//参数3：要HOOK的函数地址
	UINT Create( char* strFunName , char* strLibName , LPVOID m_unMakeFunAdd );
	//加HOOK
	UINT HookApi();
	//解HOOK
	UINT UnHookApi();
};
