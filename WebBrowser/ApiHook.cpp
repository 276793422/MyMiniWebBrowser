//////////////////////////////////////////////////////////////////////////
//
//	IATHookAPI.cpp
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "apihook.h"
#include <Windows.h>



//////////////////////////////////////////////////////////////////////////
//					HookWin32ApiS
//	功能：
//		Win32 Api 加HOOK函数
//	参数：
//		hook		一个要HOOK的函数信息结构体
//	返回值：
//		0		正确返回
//		非0		失败返回
//	注意：
//	警告：
//////////////////////////////////////////////////////////////////////////
int HookWin32ApiS( HOOK_STRUCT *hook )
{
	int ret = -1;
	if ( hook == NULL || hook == 0 )
	{
		return 1;
	}
	ret = HookWin32Api( hook->srcFunction , hook->destFunction , &(hook->newFunction) );
	if ( ret == 0 )
	{
		hook->Hooking = 1;
	}
	return ret;
}

//////////////////////////////////////////////////////////////////////////
//					UnHookWin32ApiS
//	功能：
//		Win32 Api 解HOOK函数
//	参数：
//		hook		一个要解HOOK的函数信息结构体
//	返回值：
//		0		正确返回
//		非0		失败返回
//	注意：
//	警告：
//////////////////////////////////////////////////////////////////////////
int UnHookWin32ApiS( HOOK_STRUCT *hook )
{
	int ret = -1;
	if ( hook == NULL || hook == 0 )
	{
		return 1;
	}
	ret = UnHookWin32Api( hook->srcFunction );
	if ( ret == 0 )
	{
		hook->Hooking = 0;
	}
	return ret;
}

//////////////////////////////////////////////////////////////////////////
//					HookWin32Api
//	功能：
//		Win32 Api 加HOOK函数
//	参数：
//		srcFunction		要HOOK的 Win32 Api 函数地址
//		destFunction	HOOK Api 的函数地址
//		newFunction		返回参数，正确调用源 Api 的时候，要调用的地址
//	返回值：
//		0		正确返回
//		非0		失败返回
//	注意：
//	警告：
//////////////////////////////////////////////////////////////////////////
int HookWin32Api( void *srcFunction , void *destFunction , void **newFunction )
{
	BYTE buf[7];
	if ( srcFunction == NULL || srcFunction == 0 || 
		destFunction == NULL || destFunction == 0 || 
		newFunction == NULL || newFunction == 0 )
	{
		return 1;
	}
	ReadProcessMemory( (HANDLE)-1 , (LPCVOID)((DWORD)srcFunction - 5) , buf , sizeof(buf) , NULL );
	if ( !( (buf[0] == 0x90) && (buf[1] == 0x90) && (buf[2] == 0x90) && (buf[3] == 0x90) && (buf[4] == 0x90) && (buf[5] == 0x8B) && (buf[6] == 0xFF) ) )
	{
		return 1;
	}
	buf[5] = 0xEB;
	buf[6] = 0xFE - 5;
	buf[0] = 0xE9;
	*(DWORD*)&(buf[1]) = (DWORD)destFunction - (DWORD)srcFunction;

	WriteProcessMemory( (HANDLE)-1 , (LPVOID)((DWORD)srcFunction - 5) , buf , sizeof(buf) , NULL );

	*newFunction = (void *)((LONG_PTR)srcFunction + 2);
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//					UnHookWin32Api
//	功能：
//		Win32 Api 解HOOK函数
//	参数：
//		srcFunction		要解HOOK的 Win32 Api 函数地址
//	返回值：
//		0		正确返回
//		非0		失败返回
//	注意：
//	警告：
//////////////////////////////////////////////////////////////////////////
int UnHookWin32Api( void *srcFunction )
{
	BYTE buf[7] = { 0x90 , 0x90 , 0x90 , 0x90 , 0x90 , 0x8B , 0xFF };
	if ( srcFunction == NULL || srcFunction == 0 )
	{
		return 1;
	}
	WriteProcessMemory( (HANDLE)-1 , (LPVOID)((DWORD)srcFunction - 5) , buf , sizeof(buf) , NULL );
	return 0;
}