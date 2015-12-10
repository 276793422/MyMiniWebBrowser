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

//����һ��HOOK
//����1��ҪHOOK�ĺ���
//����2���ú������ڿ��ȫ������׺
//����3��Ҫ�ĳɵĺ�����ַ
UINT CHookApi::Create( char* strFunName , char* strLibName , LPVOID m_unMyFunAdd )
{
	if ( 0 != this->m_unSysFunAdd || 0 != this->m_unMyFunAdd )
	{
		m_strError = _T("�ڲ��Ѿ�HOOKһ�������ˣ���Ҫȡ������ʼ��HOOK");
		return 1;
	}

	if ( 0 == m_unMyFunAdd )
	{
		m_strError = _T("�ڲ���Ӧ������ַ����ȷ");
		return 2;
	}

	//���ؿ�
	HMODULE hModule = ::LoadLibraryA( strLibName );
	if ( 0 == hModule )
	{
		m_strError = _T("���ؿ�ʧ��");
		return 3;
	}

	//�ӿ��л�ú����ĵ�ַ
	m_unSysFunAdd = GetProcAddress( hModule , strFunName );
	if ( 0 == m_unSysFunAdd )
	{
		m_strError = _T("��ȡ������ַʧ��");
		return 4;
	}
	//ҪHOOK�ĺ�����ַ
	this->m_unMyFunAdd = m_unMyFunAdd;

	//������ת��5���ֽ�
	m_ucFunJMP[0] = 0xE9;
	*(UINT*)(&m_ucFunJMP[1]) = (UINT)this->m_unMyFunAdd - (UINT)m_unSysFunAdd - 5;

	//����ԭ����5���ֽ�
	memcpy( m_ucFunHead , m_unSysFunAdd , 5 );

	return 0;
}


//��HOOK
UINT CHookApi::HookApi()
{
	if ( 1 == m_unHookStatus )
	{
		m_strError = _T("��HOOK�����ü�");
		return 1;
	}

	if ( 0 == m_unSysFunAdd )
	{
		m_strError = _T("δ��ʼ��");
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

//��HOOK
UINT CHookApi::UnHookApi()
{
	if ( 0 == m_unHookStatus )
	{
		m_strError = _T("δHOOK���޽�");
		return 1;
	}

	if ( 0 == m_unSysFunAdd )
	{
		m_strError = _T("δ��ʼ��");
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