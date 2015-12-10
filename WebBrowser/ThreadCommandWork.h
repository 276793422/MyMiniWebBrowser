//////////////////////////////////////////////////////////////////////////
//
//	ThreadCommandWork.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#pragma once
class CThreadCommandWork;


typedef struct {
	CString *Str;
	int nStack;
}StrStack;



//�ַ���ת�����ֺ�����ֻ����ô�ض���
#ifdef _UNICODE
#define stol wcstol
#else
#define stol strtol
#endif

class CHTMLDlg;

class CThreadCommandWork
{
public:
	CThreadCommandWork();
	~CThreadCommandWork();

	static UINT __cdecl pfnThreadProc( LPVOID pParam );

	enum{
		THREAD_CREATE = 0 ,		//����״̬
		THREAD_START ,			//����״̬
		THREAD_PAUSE ,			//ֹͣ״̬
		THREAD_STOP ,			//����״̬
		THREAD_CLEAR			//����״̬
		};
	//�߳�ִ��״̬��Ϊ�ϱ�ö��״̬
	int m_nStatus;
	//�̵߳�ǰʹ�õĴ���
	int m_nProxyIndex;
	//��ǰ�򿪵Ŀ�����Ϣ����ҳ����
	int m_nURLPageIndex;


	//�ܸ���Ի���
	CHTMLDlg *m_pHtmlDlg;

	//�ڲ�ά����һ���߳�ָ��
	CWinThread *m_WinThread;

	//��������
	CListCtrl *m_ListCtrl;

	//��ͣ���źţ���ͣʱû���źţ����ź��˾ͼ���
	HANDLE m_hPause;
	//ֹͣ���źţ�Ҫֹͣʱ���źţ�û���źžͲ�ֹͣ
	HANDLE m_hStop;

	//�������������������ִ�и���ָ��ĺ���ID
	//ָ���
	short *nASM;
	//��ǰִ��ָ��
	int nEIP;

	//�жϱ�־λ
	//	<=	<	==	>	>=
	//	1	2	3	4	5
	char nFlag;
	//���Edit
	CEdit *m_pEdtCmdTxUt;


	//Ĭ���ӳ�ʱ��
	int m_nSleep;
	//��ʶ����
	int m_nStrStack;
	//��ʶ�ṹ�壬��־���֣���ֵ
	StrStack *m_pStrStack;
	//�ͷ��ڲ���Դ
	void DeleteStrStack();
	//��������ʼ���߳�
	UINT Create( CHTMLDlg *Wnd );
	//�����߳�
	UINT Start();
	//��ͣ�߳�
	UINT Pause();
	//ֹͣ�߳�
	UINT Stop();
	//����߳���Ϣ
	UINT Clear();

};
