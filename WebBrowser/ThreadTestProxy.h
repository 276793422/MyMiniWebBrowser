//////////////////////////////////////////////////////////////////////////
//
//	ThreadTestProxy.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#pragma once

#include <afxmt.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

//����λ��
#define ADDLOCK( x )					\
		pThis->m_CtlStn.Lock();			\
		{ x }							\
		pThis->m_CtlStn.Unlock();

//�ַ���ת�����ֺ�����ֻ����ô�ض���
#ifdef _UNICODE
#define stol wcstol
#else
#define stol strtol
#endif

class CThreadTestProxy
{
public:
	CThreadTestProxy();
	~CThreadTestProxy();

private:
	CStringA m_StrHtml;
	CStringA m_StrPass;
	CListCtrl * m_LclImportProxyList;
	CStatic * m_StcStatus;

	CWinThread * m_WinThread;

	//��Ҫ�Ĺ������߳�����
	int m_nNeedThreadWorkNum;
	//���ڹ������߳�����
	int m_nThreadWorkingNum;

	//�б���ڣ��ж��ٸ���Ҫ���Ե�
	int m_nProxyInListCtrl;
	int m_nProxyInListCtrlCopy;
	//�б���ڣ�Ŀǰ������������һ��
	int m_nProxyInListCtrlMax;
	//�б���ڣ�һ���ж��ٸ�
	int m_nProxyInListALL;

	//����״̬�����Ϊ0��ʾû�д�����ȫ������ʹ��
	int m_nCreateStatus;

	//������Ϣ
	CString m_StrError;

	//ǿ���˳��ź�
	HANDLE m_HQuitNowMust;
	HANDLE m_HQuitNowMustCopy;
	//�߳�����ź�
	HANDLE m_HThreadOK;
public:
	//�߳�ͬ���ٽ���
	CCriticalSection m_CtlStn;

	//����
	UINT creat( CStringA &strHtml ,	//�����õ���ҳ����
				CStringA &strPass ,	//����ͨ���ַ�
				CListCtrl *Lcl ,	//��������Դ����ListCtrl
				CStatic *Stc ,		//���״̬��Static
				int nWorkNum		//���蹤�����߳�����
				);

	//��ʼ
	UINT start();

	//ֹͣ
	UINT stop();

	//�ر�
	UINT deleteWinSock();

	//�������̣߳�����ɻ��
	static DWORD WINAPI ThreadWorking( LPVOID pParam );

	//�����̣߳������ܹ��̵�
	static UINT __cdecl ThreadProc( LPVOID pParam );

};
