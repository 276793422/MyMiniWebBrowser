//////////////////////////////////////////////////////////////////////////
//
//	IATHookAPI.cpp
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "IATHookAPI.h"

#include <stdlib.h>
#include <string.h>
#include <windows.h>

CIATHookAPI::CIATHookAPI(void)
{
	m_pHookInfo = 0;
	m_nHookNumber = 0;
	m_nUseHookNumber = 0;
}

CIATHookAPI::~CIATHookAPI(void)
{
	if( 0 != m_pHookInfo )
	{
		free( m_pHookInfo );
		m_nHookNumber = 0;
	}
}

long CIATHookAPI::ImportAddressTableHook (
											IN unsigned long hModule ,
											IN char* pImageName ,
											IN void* pTargetFuncAddr ,
											IN void* pReplaceFuncAddr ,
											OUT unsigned long* pSrcFunProc )
{
	//	得到DOS头部
	IMAGE_DOS_HEADER* pImageDosHearder = (IMAGE_DOS_HEADER*)hModule;
	//	24个字节，越过了PE头的前两个元素，直接到了可选映像头位置
	IMAGE_OPTIONAL_HEADER* pImageOptionalHeader = (IMAGE_OPTIONAL_HEADER*)((DWORD)hModule+pImageDosHearder->e_lfanew+24);	
	//	从数据目录表里面，直接找到 IMAGE_DIRECTORY_ENTRY_IMPORT （导入表）的起始 RVA
	IMAGE_IMPORT_DESCRIPTOR* pImageImportDescriptor = (IMAGE_IMPORT_DESCRIPTOR*)((DWORD)hModule+
		pImageOptionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
	//	导入地址表
	IMAGE_THUNK_DATA* pImageThunkData = NULL;
	//	页属性的保护方式
	DWORD Value = 0, OldProtect = 0, NewProtect = 0;
	//	函数指针临时变量
	LPDWORD FunctionAddress = NULL;
	//	模块名称
	char *TargetLibraryName = NULL;

	//	上面解析完，到这里 pImageImportDescriptor 就是导入表的起始RVA
	while(pImageImportDescriptor->Name != 0)
	{
		//	遍历模块名字
		TargetLibraryName=(char *)((DWORD)hModule+pImageImportDescriptor->Name);
		//	寻找匹配的模块名
		if( _stricmp ( TargetLibraryName , pImageName ) == 0)
		{
			//	找到了目标文件名，取出模块
			pImageThunkData = (IMAGE_THUNK_DATA*)((DWORD)hModule + pImageImportDescriptor->FirstThunk);
			break; 
		} 
		pImageImportDescriptor++;   
	}
	if (pImageThunkData == NULL)
	{
		//	模块没找到就返回退出
		return 1;
	}
	//	没函数了就退出
	while(pImageThunkData->u1.Function)   
	{
		//	如果有函数，就取出函数地址
		FunctionAddress = (LPDWORD)&(pImageThunkData->u1.Function);
		//	循环判断是否是自己要找的函数
		if(*FunctionAddress == (DWORD)pTargetFuncAddr)
		{
			//	如果是，保存这个指针到输出参数
			*pSrcFunProc = *FunctionAddress;
			//	解页保护，修改地址，再加页保护
			VirtualProtect(FunctionAddress, sizeof(DWORD), PAGE_READWRITE, &OldProtect);
			if(!WriteProcessMemory((HANDLE)-1, FunctionAddress, &pReplaceFuncAddr, 4, NULL))
			{
				return 1;
			}
			VirtualProtect(FunctionAddress, sizeof(DWORD), OldProtect, &NewProtect );   
			return 0; 
		}
		//	不是要找到的，就继续找下一个
		pImageThunkData++;
	}
	return 1;
}

long CIATHookAPI::InitHook( int num )
{
	if ( num <= 0 )
	{
		return 1;
	}
	m_pHookInfo = (HOOKINFO*)malloc( sizeof(HOOKINFO) * num );
	if( 0 == m_pHookInfo )
	{
		return 2;
	}
	m_nHookNumber = num;
	memset( m_pHookInfo , 0 , sizeof( HOOKINFO ) * num );
	return 0;
}

long CIATHookAPI::CleanHook()
{
	HOOKINFO *pHookInfo = m_pHookInfo;
	int i = 0;
	for ( i = 0 ; i < m_nHookNumber ; i++ )
	{
		if ( pHookInfo->nIsUsing == 1 && pHookInfo->nIsHooking == 1 )
		{
			if ( 0 != DeleteHookFun( i ) )
			{
				return 1;
			}
		}
		pHookInfo++;
	}
	free( m_pHookInfo );
	m_pHookInfo = 0;
	return 0;
}

long CIATHookAPI::AppendHook( int num )
{
	if ( num <= 0 )
	{
		return 1;
	}
	if ( m_nHookNumber == 0 )
	{
		return 2;
	}
	if ( m_nHookNumber != m_nUseHookNumber )
	{	//	现有的还没用完
		return 3;
	}
	HOOKINFO *pHookInfo = (HOOKINFO*)malloc( sizeof(HOOKINFO) * ( num + m_nHookNumber ) );
	if( 0 == pHookInfo )
	{
		return 4;
	}
	memcpy_s( pHookInfo , sizeof(HOOKINFO) * ( num + m_nHookNumber ) , m_pHookInfo , sizeof( HOOKINFO ) * m_nHookNumber );
	memset( pHookInfo + m_nHookNumber , 0 , sizeof( HOOKINFO ) * num );
	free( m_pHookInfo );
	m_pHookInfo = pHookInfo;
	m_nHookNumber += num;

	return 0;
}

long CIATHookAPI::CreateHookFun( char* strModuleName , char* strModName , char* strFunName , unsigned long ulFunHookAddress , OUT int *index )
{
	if ( 0 == strModName || 0 == strFunName || 0 == ulFunHookAddress )
	{	//	参数有错
		return 1;
	}
	if ( m_pHookInfo == 0 || m_nHookNumber == 0 )
	{	//	没有初始化
		return 2;
	}
	if ( m_nHookNumber == m_nUseHookNumber )
	{	//	内部 HOOK 满了
		return 3;
	}
	HOOKINFO *pHookInfo = m_pHookInfo;
	int i = 0;
	for ( i = 0 ; i < m_nHookNumber ; i++ )
	{
		if ( pHookInfo->nIsUsing == 0 )
		{
			break;
		}
		pHookInfo++;
	}
	if ( i >= m_nHookNumber )
	{	//	内部 HOOK 满了，没有找到可以使用的地方
		return 4;
	}
	*index = i;
	memset( pHookInfo , 0 , sizeof(*pHookInfo) );
	if ( 0 == strModuleName )
	{
		pHookInfo->strModuleName[0] = '\0';
	}
	else
	{
		strcpy_s( pHookInfo->strModuleName , strModuleName );
	}
	pHookInfo->hModule = (unsigned long)GetModuleHandleA( strModuleName );
	strcpy_s( pHookInfo->strModName , sizeof(pHookInfo->strModName) , strModName );
	strcpy_s( pHookInfo->strFunName , sizeof(pHookInfo->strFunName) , strFunName );
	pHookInfo->ulFunAPIAddress = (unsigned long)GetProcAddress( LoadLibraryA( strModName ) , strFunName );
	pHookInfo->ulFunHookAddress = ulFunHookAddress;
	pHookInfo->nIsUsing = 1;
	m_nUseHookNumber++;

	return 0;
}

//	设置删除某个 HOOK				根据索引删除
long CIATHookAPI::DeleteHookFun( int index )
{
	if ( index < 0 || index >= m_nHookNumber )
	{	//	参数有误
		return 1;
	}
	if ( m_pHookInfo == 0 || m_nHookNumber == 0 )
	{	//	没有初始化
		return 2;
	}
	HOOKINFO *pHookInfo = m_pHookInfo;
	if ( pHookInfo[index].nIsUsing == 0 )
	{	//	当前索引块没有被使用
		return 3;
	}
	if ( pHookInfo[index].nIsHooking == 1 )
	{
		UnHookAPI( index );
	}
	pHookInfo[index].nIsUsing = 0;
	m_nUseHookNumber--;

	return 0;
}

//	设置删除某个 HOOK				根据函数名字删除
long CIATHookAPI::DeleteHookFun( char* strFunName )
{
	if ( 0 == strFunName )
	{	//	名字有误
		return 1;
	}
	HOOKINFO *pHookInfo = m_pHookInfo;
	int i;
	for ( i = 0 ; i <  m_nHookNumber ; i++ )
	{
		if ( 0 == strcmp( pHookInfo[i].strFunName , strFunName ) )
		{
			break;
		}
	}
	if ( i >= m_nHookNumber )
	{
		return 2;
	}

	return DeleteHookFun( i );
}

//	设置删除某个 HOOK				根据模块名字和函数名字删除
long CIATHookAPI::DeleteHookFun( char* strModName , char* strFunName )
{
	if ( 0 == strFunName )
	{	//	名字有误
		return 1;
	}
	HOOKINFO *pHookInfo = m_pHookInfo;
	int i;
	for ( i = 0 ; i <  m_nHookNumber ; i++ )
	{
		if ( 0 == strcmp( pHookInfo[i].strFunName , strFunName ) &&
			 0 == strcmp( pHookInfo[i].strModName , strModName ) )
		{
			break;
		}
	}
	if ( i >= m_nHookNumber )
	{
		return 2;
	}

	return DeleteHookFun( i );
}

//	获取被 HOOK 的函数真实地址		根据索引获得
long CIATHookAPI::GetHookFunAddress( int index , OUT unsigned long *pFunProc )
{
	if ( index < 0 || index >= m_nHookNumber ||  0 == pFunProc )
	{	//	参数有误
		return 1;
	}
	if ( m_pHookInfo == 0 || m_nHookNumber == 0 )
	{	//	没有初始化
		return 2;
	}
	HOOKINFO *pHookInfo = m_pHookInfo;
	if ( pHookInfo[index].nIsUsing == 0 )
	{	//	当前块没有被使用
		return 3;
	}
	*pFunProc = pHookInfo[index].ulFunTrueAddress;
	if ( 0 == *pFunProc )
	{	//	获取函数指针失败
		return 4;
	}
	return 0;
}

//	获取被 HOOK 的函数真实地址		根据函数名字获得，并返回索引
long CIATHookAPI::GetHookFunAddress( char* strFunName , OUT int *index , OUT unsigned long *pFunProc )
{
	if ( 0 == strFunName || index == 0 || pFunProc == 0 )
	{	//	名字有误
		return 1;
	}
	HOOKINFO *pHookInfo = m_pHookInfo;
	int i;
	for ( i = 0 ; i <  m_nHookNumber ; i++ )
	{
		if ( 0 == strcmp( pHookInfo[i].strFunName , strFunName ) )
		{
			break;
		}
	}
	if ( i >= m_nHookNumber )
	{
		return 2;
	}
	int ret = GetHookFunAddress( i , pFunProc );
	if ( ret == 0 )
	{
		*index = i;
	}

	return ret;
}

//	获取被 HOOK 的函数真实地址		根据模块名字、函数名字获得，并返回索引
long CIATHookAPI::GetHookFunAddress( char* strModName , char* strFunName , OUT int *index , OUT unsigned long *pFunProc )
{
	if ( 0 == strFunName || 0 == strModName || index == 0 || pFunProc == 0 )
	{	//	名字有误
		return 1;
	}
	HOOKINFO *pHookInfo = m_pHookInfo;
	int i;
	for ( i = 0 ; i <  m_nHookNumber ; i++ )
	{
		if ( 0 == strcmp( pHookInfo[i].strFunName , strFunName ) &&
			0 == strcmp( pHookInfo[i].strModName , strModName ) )
		{
			break;
		}
	}
	if ( i >= m_nHookNumber )
	{
		return 2;
	}
	int ret = GetHookFunAddress( i , pFunProc );
	if ( ret == 0 )
	{
		*index = i;
	}

	return ret;
}

//	开启 HOOK		根据索引开启
long CIATHookAPI::HookAPI( int index )
{
	if ( index < 0 || index >= m_nHookNumber )
	{	//	参数有误
		return 1;
	}
	if ( m_pHookInfo == 0 || m_nHookNumber == 0 )
	{	//	没有初始化
		return 2;
	}
	HOOKINFO *pHookInfo = m_pHookInfo;
	if ( pHookInfo[index].nIsUsing == 0 || pHookInfo[index].nIsHooking == 1 )
	{	//	当前块没有被使用，或者已经在 HOOK
		return 3;
	}
	int i = ImportAddressTableHook( pHookInfo[index].hModule ,
									pHookInfo[index].strModName ,
									(void *)pHookInfo[index].ulFunAPIAddress ,
									(void *)pHookInfo[index].ulFunHookAddress ,
									&(pHookInfo[index].ulFunTrueAddress) );
	if ( 0 == i )
	{
		pHookInfo[index].nIsHooking = 1;
	}

	return i;
}

//	开启 HOOK		根据函数名字开启，返回索引
long CIATHookAPI::HookAPI( char* strFunName , OUT int *index)
{
	if ( 0 == strFunName )
	{	//	名字有误
		return 1;
	}
	HOOKINFO *pHookInfo = m_pHookInfo;
	int i;
	for ( i = 0 ; i <  m_nHookNumber ; i++ )
	{
		if ( 0 == strcmp( pHookInfo[i].strFunName , strFunName ) )
		{
			break;
		}
	}
	if ( i >= m_nHookNumber )
	{
		return 2;
	}
	int ret = HookAPI( i );
	if ( ret == 0 )
	{
		*index = i;
	}

	return ret;
}

//	开启 HOOK		根据模块名字，函数名字获得，返回索引
long CIATHookAPI::HookAPI( char* strModName , char* strFunName , OUT int *index )
{

	if ( 0 == strFunName || 0 == strModName )
	{	//	名字有误
		return 1;
	}
	HOOKINFO *pHookInfo = m_pHookInfo;
	int i;
	for ( i = 0 ; i <  m_nHookNumber ; i++ )
	{
		if ( 0 == strcmp( pHookInfo[i].strFunName , strFunName ) &&
			 0 == strcmp( pHookInfo[i].strModName , strModName ) )
		{
			break;
		}
	}
	if ( i >= m_nHookNumber )
	{
		return 2;
	}
	int ret = HookAPI( i );
	if ( ret == 0 )
	{
		*index = i;
	}

	return ret;
}

//	关闭 HOOK		根据索引关闭
long CIATHookAPI::UnHookAPI( int index )
{
	if ( index < 0 || index >= m_nHookNumber )
	{	//	参数有误
		return 1;
	}
	if ( m_pHookInfo == 0 || m_nHookNumber == 0 )
	{	//	没有初始化
		return 2;
	}
	HOOKINFO *pHookInfo = m_pHookInfo;
	if ( pHookInfo[index].nIsUsing == 0 || pHookInfo[index].nIsHooking == 0 )
	{	//	当前块没有被使用，或者没有在 HOOK
		return 3;
	}

	unsigned long temp;
	int i = ImportAddressTableHook( pHookInfo[index].hModule ,
									pHookInfo[index].strModName ,
									(void *)pHookInfo[index].ulFunHookAddress ,
									(void *)pHookInfo[index].ulFunTrueAddress ,
									&temp );
	if ( 0 == i )
	{
		pHookInfo[index].nIsHooking = 0;
	}
	return i;
}

//	关闭 HOOK		根据函数名字关闭，返回索引
long CIATHookAPI::UnHookAPI( char* strFunName , int *index )
{
	if ( 0 == strFunName )
	{	//	名字有误
		return 1;
	}
	HOOKINFO *pHookInfo = m_pHookInfo;
	int i;
	for ( i = 0 ; i <  m_nHookNumber ; i++ )
	{
		if ( 0 == strcmp( pHookInfo[i].strFunName , strFunName ) )
		{
			break;
		}
	}
	if ( i >= m_nHookNumber )
	{
		return 2;
	}
	int ret = UnHookAPI( i );
	if ( ret == 0 )
	{
		*index = i;
	}

	return ret;
}

//	关闭 HOOK		根据模块名字，函数名字关闭，返回索引
long CIATHookAPI::UnHookAPI( char* strModName , char* strFunName , int *index )
{
	if ( 0 == strFunName || 0 == strModName )
	{	//	名字有误
		return 1;
	}
	HOOKINFO *pHookInfo = m_pHookInfo;
	int i;
	for ( i = 0 ; i <  m_nHookNumber ; i++ )
	{
		if ( 0 == strcmp( pHookInfo[i].strFunName , strFunName ) &&
			 0 == strcmp( pHookInfo[i].strModName , strModName ) )
		{
			break;
		}
	}
	if ( i >= m_nHookNumber )
	{
		return 2;
	}
	int ret = UnHookAPI( i );
	if ( ret == 0 )
	{
		*index = i;
	}

	return ret;
}
