//////////////////////////////////////////////////////////////////////////
//
//	InstructTranslationAndRun.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#pragma once

class CHTMLDlg;
class CThreadCommandWork;

//ָ�����ָ������
#define MY_INSTRUCT_NUM 23

typedef struct _InstructList
{
	CString m_StrInstruct;
	UINT m_nID;
}InstructList;

class CInstructTranslationAndRun
{
public:
	CInstructTranslationAndRun();
	~CInstructTranslationAndRun();

private:
	//ָ�����ָ������
	UINT m_nInstructNum;
	//ָ���
	InstructList m_InstructList[MY_INSTRUCT_NUM+1] ;

	//��ʼ��������
	void Create();

	//����
	CString m_StrError;

public:
	//�߳�ָ��
	CThreadCommandWork *m_pWorkThread;
	//������ָ��
	CHTMLDlg *m_pParent;
	//����ȡָ��
	const InstructList & operator[]( int i )	{	return m_InstructList[i];	}
	//��ȡָ�����ָ������
	int GetInstructNum()						{	return m_nInstructNum;		}
	//�õ�������Ϣ
	const CString &GetInstructError()			{	return m_StrError;			}

	//�ж�ָ��ĸ�����Ϣ�Ƿ�Ϸ�������ֵ0Ϊ�Ϸ���1Ϊ���Ϸ�
	int TestInstruct( CListCtrl * const m_LclCmd );

	//����ָ�����ֵ�Ƿ���õ���ָ��ֵ��-1Ϊ����ʧ�ܣ�����ֵΪ�ɹ�
	int TranslateInstruct( CString &strInstruct );

	//ִ��ָ�����ֵ��ָ���Ƿ���ȷִ�У�0Ϊִ��ʧ��
	//����1����ǰָ�����ͣ����ݴ˲������жϸ�ִ�к����
	//����2����ǰָ��ĸ�����Ϣ��Ҳ���ǲ�������ֱ�Ӵ���ִ������е�
	//����3����ǰָ���Sid��Ҳ����ִ�е��ڼ���ָ���ˣ������
	int RunInstruct( int nInstruct , CString &strInstruct , int Sid );


	//	0	��	1	����λ��û��ָ��0Ϊ��ʼ��1Ϊ��ֹ
	UINT Fun2( CString &strInstruct , int Sid );
	UINT Fun3( CString &strInstruct , int Sid );
	UINT Fun4( CString &strInstruct , int Sid );
	UINT Fun5( CString &strInstruct , int Sid );
	UINT Fun6( CString &strInstruct , int Sid );
	UINT Fun7( CString &strInstruct , int Sid );
	UINT Fun8( CString &strInstruct , int Sid );
	UINT Fun9( CString &strInstruct , int Sid );
	UINT Fun10( CString &strInstruct , int Sid );
	UINT Fun11( CString &strInstruct , int Sid );
	UINT Fun12( CString &strInstruct , int Sid );
	UINT Fun13( CString &strInstruct , int Sid );
	UINT Fun14( CString &strInstruct , int Sid );
	UINT Fun15( CString &strInstruct , int Sid );
	UINT Fun16( CString &strInstruct , int Sid );
	UINT Fun17( CString &strInstruct , int Sid );
	UINT Fun18( CString &strInstruct , int Sid );
	UINT Fun19( CString &strInstruct , int Sid );
	UINT Fun20( CString &strInstruct , int Sid );
	UINT Fun21( CString &strInstruct , int Sid );
	UINT Fun22( CString &strInstruct , int Sid );
};
