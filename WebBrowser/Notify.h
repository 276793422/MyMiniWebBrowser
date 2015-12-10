//////////////////////////////////////////////////////////////////////////
//
//	Notify.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////


#ifndef _MY_NOTIFY_CLASS_
#define _MY_NOTIFY_CLASS_



class CNotify
{
public:
	CNotify();
	~CNotify();

	//���´�����������
	//TCHAR *Str	��Ϊ��������ʾ���ַ���
	//CWnd *pWnd	��Ϊ������ָ��
	//UINT IconID	��Ϊ����ͼ��ID
	//UINT MsgCB	��������Ϣ����	��Ĭ��Ϊ	WM_COMMAND	��Ϣ��
	//UINT Flg		�����̷��		��Ĭ��ֵ	NIF_ICON | NIF_MESSAGE | NIF_TIP��
	CNotify( TCHAR *Str , 
			CWnd *pWnd , 
			UINT IconID , 
			UINT MsgCB = WM_COMMAND , 
			UINT Flg = NIF_ICON | NIF_MESSAGE | NIF_TIP );

	//�������ϵͳ����ͼ��
	void Create( TCHAR *Str , 
				CWnd *pWnd , 
				UINT IconID , 
				UINT MsgCB = WM_COMMAND , 
				UINT Flg = NIF_ICON | NIF_MESSAGE | NIF_TIP );

	//�ؽ����ϵͳ����ͼ�꣬����1����Ҫ�ؽ���ͼ������
	void ReCreate( int NtiID , 
					TCHAR *Str , 
					CWnd *pWnd , 
					UINT IconID , 
					UINT MsgCB = WM_COMMAND , 
					UINT Flg = NIF_ICON | NIF_MESSAGE | NIF_TIP );
	//׷��һ��ϵͳ����ͼ��
	void AddNotify( TCHAR *Str , 
					CWnd *pWnd , 
					UINT IconID , 
					UINT MsgCB = WM_COMMAND , 
					UINT Flg = NIF_ICON | NIF_MESSAGE | NIF_TIP );
	//�Զ�����ʾ�ڼ�������ͼ��
	void MakeOut( int index );

	//�������
	void MakeNull();
	//�ؽ�д�뱸�����̱���
	void MakeBack();


	//ϵͳ���̱���ָ��
	NOTIFYICONDATA *m_nd;
	//ָ�����ж��ٸ����̱���
	int m_nNtiNum;
	//��ǰ��ʾ���ǵڼ������̱���
	int m_nNtiID;
	//����ϵͳ���̱���
	NOTIFYICONDATA m_ndback;


	//��Ӳ˵�
	void AddMenu( UINT MenuID );
	//�����˵�
	void MakeOutMenu( CWnd * pWnd );
	//���̲˵���ID
	UINT m_MenuID;

};


#endif