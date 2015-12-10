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
	//	�õ�DOSͷ��
	IMAGE_DOS_HEADER* pImageDosHearder = (IMAGE_DOS_HEADER*)hModule;
	//	24���ֽڣ�Խ����PEͷ��ǰ����Ԫ�أ�ֱ�ӵ��˿�ѡӳ��ͷλ��
	IMAGE_OPTIONAL_HEADER* pImageOptionalHeader = (IMAGE_OPTIONAL_HEADER*)((DWORD)hModule+pImageDosHearder->e_lfanew+24);	
	//	������Ŀ¼�����棬ֱ���ҵ� IMAGE_DIRECTORY_ENTRY_IMPORT �����������ʼ RVA
	IMAGE_IMPORT_DESCRIPTOR* pImageImportDescriptor = (IMAGE_IMPORT_DESCRIPTOR*)((DWORD)hModule+
		pImageOptionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
	//	�����ַ��
	IMAGE_THUNK_DATA* pImageThunkData = NULL;
	//	ҳ���Եı�����ʽ
	DWORD Value = 0, OldProtect = 0, NewProtect = 0;
	//	����ָ����ʱ����
	LPDWORD FunctionAddress = NULL;
	//	ģ������
	char *TargetLibraryName = NULL;

	//	��������꣬������ pImageImportDescriptor ���ǵ�������ʼRVA
	while(pImageImportDescriptor->Name != 0)
	{
		//	����ģ������
		TargetLibraryName=(char *)((DWORD)hModule+pImageImportDescriptor->Name);
		//	Ѱ��ƥ���ģ����
		if( _stricmp ( TargetLibraryName , pImageName ) == 0)
		{
			//	�ҵ���Ŀ���ļ�����ȡ��ģ��
			pImageThunkData = (IMAGE_THUNK_DATA*)((DWORD)hModule + pImageImportDescriptor->FirstThunk);
			break; 
		} 
		pImageImportDescriptor++;   
	}
	if (pImageThunkData == NULL)
	{
		//	ģ��û�ҵ��ͷ����˳�
		return 1;
	}
	//	û�����˾��˳�
	while(pImageThunkData->u1.Function)   
	{
		//	����к�������ȡ��������ַ
		FunctionAddress = (LPDWORD)&(pImageThunkData->u1.Function);
		//	ѭ���ж��Ƿ����Լ�Ҫ�ҵĺ���
		if(*FunctionAddress == (DWORD)pTargetFuncAddr)
		{
			//	����ǣ��������ָ�뵽�������
			*pSrcFunProc = *FunctionAddress;
			//	��ҳ�������޸ĵ�ַ���ټ�ҳ����
			VirtualProtect(FunctionAddress, sizeof(DWORD), PAGE_READWRITE, &OldProtect);
			if(!WriteProcessMemory((HANDLE)-1, FunctionAddress, &pReplaceFuncAddr, 4, NULL))
			{
				return 1;
			}
			VirtualProtect(FunctionAddress, sizeof(DWORD), OldProtect, &NewProtect );   
			return 0; 
		}
		//	����Ҫ�ҵ��ģ��ͼ�������һ��
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
	{	//	���еĻ�û����
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
	{	//	�����д�
		return 1;
	}
	if ( m_pHookInfo == 0 || m_nHookNumber == 0 )
	{	//	û�г�ʼ��
		return 2;
	}
	if ( m_nHookNumber == m_nUseHookNumber )
	{	//	�ڲ� HOOK ����
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
	{	//	�ڲ� HOOK ���ˣ�û���ҵ�����ʹ�õĵط�
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

//	����ɾ��ĳ�� HOOK				��������ɾ��
long CIATHookAPI::DeleteHookFun( int index )
{
	if ( index < 0 || index >= m_nHookNumber )
	{	//	��������
		return 1;
	}
	if ( m_pHookInfo == 0 || m_nHookNumber == 0 )
	{	//	û�г�ʼ��
		return 2;
	}
	HOOKINFO *pHookInfo = m_pHookInfo;
	if ( pHookInfo[index].nIsUsing == 0 )
	{	//	��ǰ������û�б�ʹ��
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

//	����ɾ��ĳ�� HOOK				���ݺ�������ɾ��
long CIATHookAPI::DeleteHookFun( char* strFunName )
{
	if ( 0 == strFunName )
	{	//	��������
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

//	����ɾ��ĳ�� HOOK				����ģ�����ֺͺ�������ɾ��
long CIATHookAPI::DeleteHookFun( char* strModName , char* strFunName )
{
	if ( 0 == strFunName )
	{	//	��������
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

//	��ȡ�� HOOK �ĺ�����ʵ��ַ		�����������
long CIATHookAPI::GetHookFunAddress( int index , OUT unsigned long *pFunProc )
{
	if ( index < 0 || index >= m_nHookNumber ||  0 == pFunProc )
	{	//	��������
		return 1;
	}
	if ( m_pHookInfo == 0 || m_nHookNumber == 0 )
	{	//	û�г�ʼ��
		return 2;
	}
	HOOKINFO *pHookInfo = m_pHookInfo;
	if ( pHookInfo[index].nIsUsing == 0 )
	{	//	��ǰ��û�б�ʹ��
		return 3;
	}
	*pFunProc = pHookInfo[index].ulFunTrueAddress;
	if ( 0 == *pFunProc )
	{	//	��ȡ����ָ��ʧ��
		return 4;
	}
	return 0;
}

//	��ȡ�� HOOK �ĺ�����ʵ��ַ		���ݺ������ֻ�ã�����������
long CIATHookAPI::GetHookFunAddress( char* strFunName , OUT int *index , OUT unsigned long *pFunProc )
{
	if ( 0 == strFunName || index == 0 || pFunProc == 0 )
	{	//	��������
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

//	��ȡ�� HOOK �ĺ�����ʵ��ַ		����ģ�����֡��������ֻ�ã�����������
long CIATHookAPI::GetHookFunAddress( char* strModName , char* strFunName , OUT int *index , OUT unsigned long *pFunProc )
{
	if ( 0 == strFunName || 0 == strModName || index == 0 || pFunProc == 0 )
	{	//	��������
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

//	���� HOOK		������������
long CIATHookAPI::HookAPI( int index )
{
	if ( index < 0 || index >= m_nHookNumber )
	{	//	��������
		return 1;
	}
	if ( m_pHookInfo == 0 || m_nHookNumber == 0 )
	{	//	û�г�ʼ��
		return 2;
	}
	HOOKINFO *pHookInfo = m_pHookInfo;
	if ( pHookInfo[index].nIsUsing == 0 || pHookInfo[index].nIsHooking == 1 )
	{	//	��ǰ��û�б�ʹ�ã������Ѿ��� HOOK
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

//	���� HOOK		���ݺ������ֿ�������������
long CIATHookAPI::HookAPI( char* strFunName , OUT int *index)
{
	if ( 0 == strFunName )
	{	//	��������
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

//	���� HOOK		����ģ�����֣��������ֻ�ã���������
long CIATHookAPI::HookAPI( char* strModName , char* strFunName , OUT int *index )
{

	if ( 0 == strFunName || 0 == strModName )
	{	//	��������
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

//	�ر� HOOK		���������ر�
long CIATHookAPI::UnHookAPI( int index )
{
	if ( index < 0 || index >= m_nHookNumber )
	{	//	��������
		return 1;
	}
	if ( m_pHookInfo == 0 || m_nHookNumber == 0 )
	{	//	û�г�ʼ��
		return 2;
	}
	HOOKINFO *pHookInfo = m_pHookInfo;
	if ( pHookInfo[index].nIsUsing == 0 || pHookInfo[index].nIsHooking == 0 )
	{	//	��ǰ��û�б�ʹ�ã�����û���� HOOK
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

//	�ر� HOOK		���ݺ������ֹرգ���������
long CIATHookAPI::UnHookAPI( char* strFunName , int *index )
{
	if ( 0 == strFunName )
	{	//	��������
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

//	�ر� HOOK		����ģ�����֣��������ֹرգ���������
long CIATHookAPI::UnHookAPI( char* strModName , char* strFunName , int *index )
{
	if ( 0 == strFunName || 0 == strModName )
	{	//	��������
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
