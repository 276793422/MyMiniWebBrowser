//////////////////////////////////////////////////////////////////////////
//
//	ThreadRecvEMail.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#pragma once





class CDlgEMail;

class CThreadRecvEMail
{
public:
	CThreadRecvEMail();
	~CThreadRecvEMail();


	CDlgEMail *m_pParent;

public:
	//ȫ�̳�ʼ��
	UINT Create( CDlgEMail *parent );
private:
	//�ȴ�״̬�߳�
	static UINT ThreadProcWait( LPVOID pParam );
private:
	//������״̬
	int m_Status;
	//���������������Ҳ���˳�������
	HANDLE m_HClose;
	//�������߳�
	static UINT ThreadProcNOOP( LPVOID pParam );
public:
	//����������������һֱ����
	UINT StartNOOP();
	//������ֹͣ������
	UINT Stop();

public:
	//�����߳�
	static UINT ThreadProcOpen( LPVOID pParam );
	UINT OpenEMail( int i );
	int m_nOpenIndex;
public:
	//��ȡ�ʼ��б�
	static UINT ThreadProcRecv( LPVOID pParam );
	UINT RecvEMail();
};
