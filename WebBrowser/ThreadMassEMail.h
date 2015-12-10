//////////////////////////////////////////////////////////////////////////
//
//	ThreadMassEMail.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include <afxmt.h>

class CDlgEMail;



class CThreadMassEMail
{
public:
	CThreadMassEMail();
	~CThreadMassEMail();

	CDlgEMail *m_pDlgEMail;

	//�����źţ������߳�
	HANDLE m_hStop;

//////////////////////////////////////////////////////////////////////////
// ״̬Ч���߳�

	static UINT ThreadProcStatus( LPVOID pParam );

//////////////////////////////////////////////////////////////////////////
//	�ʼ�Ⱥ��

	static UINT ThreadProcTime( LPVOID pParam );

	void StartTime();

	void StopTime();

//////////////////////////////////////////////////////////////////////////
//	�����ʼ�����

	static UINT ThreadProcOnce( LPVOID pParam );

	void StartOnce();

//////////////////////////////////////////////////////////////////////////
//	�����ը

	static UINT ThreadProcLoop( LPVOID pParam );

	void StartLoop();

	void StopLoop();

//////////////////////////////////////////////////////////////////////////
//	���̷߳��ͣ���ز����̳߳�

	//�������߳�
	static UINT ThreadProcThread( LPVOID pParam );

	//�������߳�
	static UINT ThreadProcThreadWork( LPVOID pParam );

	//���������ʱ����ź�
	HANDLE m_hThreadWorkOK;

	//����������
	UINT m_UnWorkerNum;

	//��ǰʹ�õ�����ִ�����
	int m_nIndexString;

	void StartThread();

	void StopThread();

	//�߳�ͬ���õ��ٽ���
	CCriticalSection m_CISLock;
};
