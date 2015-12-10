//////////////////////////////////////////////////////////////////////////
//
//	IATHookAPI.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//						IAT	HOOK类
//	使用方法：
//			1：		InitHook
//			2：		CreateHookFun
//			3：		HookAPI
//			4：		GetHookFunAddress
//			5：		......
//			6：		UnHookAPI
//			7：		CleanHook
//
//	还有一个函数
//				AppendHook
//				可以在初始化之后，清理之前，任意时候调用以获取更多HOOK空间
//
//	正确返回值均为 0
//	非 0 以外的任何返回值均为错误返回值
//


#pragma once

#ifndef IN
#define IN 
#endif
#ifndef OUT
#define OUT 
#endif

typedef struct 
{
	char strModuleName[260];//	要HOOK的某个模块名字
	unsigned long hModule;	//	要HOOK德当前模块的句柄

	char strModName[260];	//	要HOOK的函数所在模块名字，DLL 名字
	char strFunName[260];	//	要HOOK的函数的名字
	unsigned long ulFunAPIAddress;	//	要HOOK的函数导入地址

	unsigned long ulFunHookAddress;	//	HOOK 函数的地址

	unsigned long ulFunTrueAddress;	//	被 HOOK 函数的真实地址，钩子调用时，使用它

	int nIsHooking;			//	正在 HOOK 
	//								0 未 HOOK 状态
	//								1 已 HOOK 状态
	int nIsUsing;			//	当前元素是否正在使用
	//								0 未被使用，可以使用
	//								1 已被使用，不可以使用
} HOOKINFO ;

class CIATHookAPI
{
public:
	CIATHookAPI(void);
	~CIATHookAPI(void);

public:
	HOOKINFO* m_pHookInfo;	//	HOOK 结构体指针
	int m_nHookNumber;		//	HOOK 结构体内部元素总数量，每一个元素对应 HOOK 一个函数
	int m_nUseHookNumber;	//	正在使用的 HOOK 结构体数量

private:
	long ImportAddressTableHook (
								IN unsigned long hModule,
								IN char* pImageName,
								IN void* pTargetFuncAddr,
								IN void* pReplaceFuncAddr,
								OUT unsigned long* pSrcFunProc );	
public:	//	初始化 HOOK

	//	初始化 HOOK 类
	long InitHook( int num );

	//	清理 HOOK 类
	long CleanHook();

	//	追加 HOOK 数量
	long AppendHook( int num );

public:	//	设 HOOK

	//	设置 HOOK 某个函数
	long CreateHookFun( char* lpModuleName , char* strModName , char* strFunName , unsigned long ulFunHookAddress , OUT int *index );

public:	//	删 HOOK

	//	设置删除某个 HOOK				根据索引删除
	long DeleteHookFun( int index );

	//	设置删除某个 HOOK				根据函数名字删除
	long DeleteHookFun( char* strFunName );

	//	设置删除某个 HOOK				根据模块名字和函数名字删除
	long DeleteHookFun( char* strModName , char* strFunName );

public:	//	取 HOOK

	//	获取被 HOOK 的函数真实地址		根据索引获得
	long GetHookFunAddress( int index , OUT unsigned long *pFunProc );

	//	获取被 HOOK 的函数真实地址		根据函数名字获得，并返回索引
	long GetHookFunAddress( char* strFunName , OUT int *index , OUT unsigned long *pFunProc );

	//	获取被 HOOK 的函数真实地址		根据模块名字、函数名字获得，并返回索引
	long GetHookFunAddress( char* strModName , char* strFunName , OUT int *index , OUT unsigned long *pFunProc );

public:	//	加 HOOK

	//	开启 HOOK		根据索引开启
	long HookAPI( int index );

	//	开启 HOOK		根据函数名字开启，返回索引
	long HookAPI( char* strFunName , OUT int *index);

	//	开启 HOOK		根据模块名字，函数名字开启，返回索引
	long HookAPI( char* strModName , char* strFunName , OUT int *index );

public:	//	解 HOOK

	//	关闭 HOOK		根据索引关闭
	long UnHookAPI( int index );

	//	关闭 HOOK		根据函数名字关闭，返回索引
	long UnHookAPI( char* strFunName , int *index );

	//	关闭 HOOK		根据模块名字，函数名字关闭，返回索引
	long UnHookAPI( char* strModName , char* strFunName , int *index );

};
