//////////////////////////////////////////////////////////////////////////
//
//	IATHookAPI.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//						IAT	HOOK��
//	ʹ�÷�����
//			1��		InitHook
//			2��		CreateHookFun
//			3��		HookAPI
//			4��		GetHookFunAddress
//			5��		......
//			6��		UnHookAPI
//			7��		CleanHook
//
//	����һ������
//				AppendHook
//				�����ڳ�ʼ��֮������֮ǰ������ʱ������Ի�ȡ����HOOK�ռ�
//
//	��ȷ����ֵ��Ϊ 0
//	�� 0 ������κη���ֵ��Ϊ���󷵻�ֵ
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
	char strModuleName[260];//	ҪHOOK��ĳ��ģ������
	unsigned long hModule;	//	ҪHOOK�µ�ǰģ��ľ��

	char strModName[260];	//	ҪHOOK�ĺ�������ģ�����֣�DLL ����
	char strFunName[260];	//	ҪHOOK�ĺ���������
	unsigned long ulFunAPIAddress;	//	ҪHOOK�ĺ��������ַ

	unsigned long ulFunHookAddress;	//	HOOK �����ĵ�ַ

	unsigned long ulFunTrueAddress;	//	�� HOOK ��������ʵ��ַ�����ӵ���ʱ��ʹ����

	int nIsHooking;			//	���� HOOK 
	//								0 δ HOOK ״̬
	//								1 �� HOOK ״̬
	int nIsUsing;			//	��ǰԪ���Ƿ�����ʹ��
	//								0 δ��ʹ�ã�����ʹ��
	//								1 �ѱ�ʹ�ã�������ʹ��
} HOOKINFO ;

class CIATHookAPI
{
public:
	CIATHookAPI(void);
	~CIATHookAPI(void);

public:
	HOOKINFO* m_pHookInfo;	//	HOOK �ṹ��ָ��
	int m_nHookNumber;		//	HOOK �ṹ���ڲ�Ԫ����������ÿһ��Ԫ�ض�Ӧ HOOK һ������
	int m_nUseHookNumber;	//	����ʹ�õ� HOOK �ṹ������

private:
	long ImportAddressTableHook (
								IN unsigned long hModule,
								IN char* pImageName,
								IN void* pTargetFuncAddr,
								IN void* pReplaceFuncAddr,
								OUT unsigned long* pSrcFunProc );	
public:	//	��ʼ�� HOOK

	//	��ʼ�� HOOK ��
	long InitHook( int num );

	//	���� HOOK ��
	long CleanHook();

	//	׷�� HOOK ����
	long AppendHook( int num );

public:	//	�� HOOK

	//	���� HOOK ĳ������
	long CreateHookFun( char* lpModuleName , char* strModName , char* strFunName , unsigned long ulFunHookAddress , OUT int *index );

public:	//	ɾ HOOK

	//	����ɾ��ĳ�� HOOK				��������ɾ��
	long DeleteHookFun( int index );

	//	����ɾ��ĳ�� HOOK				���ݺ�������ɾ��
	long DeleteHookFun( char* strFunName );

	//	����ɾ��ĳ�� HOOK				����ģ�����ֺͺ�������ɾ��
	long DeleteHookFun( char* strModName , char* strFunName );

public:	//	ȡ HOOK

	//	��ȡ�� HOOK �ĺ�����ʵ��ַ		�����������
	long GetHookFunAddress( int index , OUT unsigned long *pFunProc );

	//	��ȡ�� HOOK �ĺ�����ʵ��ַ		���ݺ������ֻ�ã�����������
	long GetHookFunAddress( char* strFunName , OUT int *index , OUT unsigned long *pFunProc );

	//	��ȡ�� HOOK �ĺ�����ʵ��ַ		����ģ�����֡��������ֻ�ã�����������
	long GetHookFunAddress( char* strModName , char* strFunName , OUT int *index , OUT unsigned long *pFunProc );

public:	//	�� HOOK

	//	���� HOOK		������������
	long HookAPI( int index );

	//	���� HOOK		���ݺ������ֿ�������������
	long HookAPI( char* strFunName , OUT int *index);

	//	���� HOOK		����ģ�����֣��������ֿ�������������
	long HookAPI( char* strModName , char* strFunName , OUT int *index );

public:	//	�� HOOK

	//	�ر� HOOK		���������ر�
	long UnHookAPI( int index );

	//	�ر� HOOK		���ݺ������ֹرգ���������
	long UnHookAPI( char* strFunName , int *index );

	//	�ر� HOOK		����ģ�����֣��������ֹرգ���������
	long UnHookAPI( char* strModName , char* strFunName , int *index );

};
