//////////////////////////////////////////////////////////////////////////
//
//						HOOKAPI��
//
//			ȫANSI�ַ�����
//	��ʼ���ڲ���ԱΪ��			void Clean();
//	���ش�����Ϣ				TCHAR * GetLastError() {	return m_strError;	};
//	��ʼ��ȫ����Ա׼��HOOK		UINT Create( char* strFunName , char* strLibName , LPVOID m_unMakeFunAdd );
//	��HOOK						UINT HookApi();
//	��HOOK						UINT UnHookApi();
//
//////////////////////////////////////////////////////////////////////////




#pragma once


class CHookApi
{
private:
	//������Ϣ
	TCHAR *m_strError;
	//ҪHOOK�ĺ�����ַ				//ҪHOOK�ĺ�����ַ��ԭ����5���ֽ�����
	LPVOID m_unSysFunAdd;			UCHAR m_ucFunHead[5];
	//Ҫ�ĳɵĺ�����ַ				//HOOKʱ��Ҫ�ĵ���ת���Զ��庯������Ϣ
	LPVOID m_unMyFunAdd;			UCHAR m_ucFunJMP[5];

	//HOOK״̬��1Ϊ��HOOK��0ΪδHOOK
	UINT m_unHookStatus;

public:
	CHookApi();
	~CHookApi();

	//ȫ�ֳ�ʼ��
	void Clean();
	//���ش�����Ϣ
	TCHAR * GetLastError() {	return m_strError;	};
	//����һ��HOOK
	//����1��ҪHOOK�ĺ���
	//����2���ú������ڿ��ȫ������׺
	//����3��ҪHOOK�ĺ�����ַ
	UINT Create( char* strFunName , char* strLibName , LPVOID m_unMakeFunAdd );
	//��HOOK
	UINT HookApi();
	//��HOOK
	UINT UnHookApi();
};
