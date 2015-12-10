//////////////////////////////////////////////////////////////////////////
//
//	InstructTranslationAndRun.cpp
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "InstructTranslationAndRun.h"
#include "HTMLDlg.h"
#include "ThreadCommandWork.h"

CInstructTranslationAndRun::CInstructTranslationAndRun()
{
	Create();
}

CInstructTranslationAndRun::~CInstructTranslationAndRun()
{
}

void CInstructTranslationAndRun::Create()
{

	m_InstructList[0].m_StrInstruct = _T("��ʼ�����������Ӵ˴���ʼ������ֻ����һ��") ;
	m_InstructList[0].m_nID = 0;

	m_InstructList[1].m_StrInstruct = _T("���������������Ӵ˴�����������ֻ����һ��") ;
	m_InstructList[1].m_nID = 1;

	m_InstructList[2].m_StrInstruct = _T("ʹ�ô����Զ�ʹ�ô���ҳ������е�ѡ��Ĵ���") ;
	m_InstructList[2].m_nID = 2;

	m_InstructList[3].m_StrInstruct = _T("ֹͣ����ֹͣʹ�ô���") ;
	m_InstructList[3].m_nID = 3;

	m_InstructList[4].m_StrInstruct = _T("��ѡ����ѡ����һ������") ;
	m_InstructList[4].m_nID = 4;

	m_InstructList[5].m_StrInstruct = _T("ˢ��ҳ�棺ˢ�µ�ǰ��ҳ") ;
	m_InstructList[5].m_nID = 5;

	m_InstructList[6].m_StrInstruct = _T("�Զ�����������д") ;
	m_InstructList[6].m_nID = 6;

	m_InstructList[7].m_StrInstruct = _T("�ӳ٣��룺������ϢΪ�ӳ�ʱ�䣬��λ����") ;
	m_InstructList[7].m_nID = 7;

	m_InstructList[8].m_StrInstruct = _T("�����ť��������ϢΪ��ť�ϵ����֣���һ���ɹ�") ;
	m_InstructList[8].m_nID = 8;

	m_InstructList[9].m_StrInstruct = _T("��ָ����������ϢΪ����ҳ�ĵ�ַ") ;
	m_InstructList[9].m_nID = 9;

	m_InstructList[10].m_StrInstruct = _T("���ñ�־��������ϢΪ��־���ڿ�ʼ����֮ǰ���ã���ͬ��־����������ֻ��ӵ��һ��") ;
	m_InstructList[10].m_nID = 10;

	m_InstructList[11].m_StrInstruct = _T("������־��������ϢΪҪ�����ı�־���������Ϳ�������������") ;
	m_InstructList[11].m_nID = 11;

	m_InstructList[12].m_StrInstruct = _T("�жϱ�־��������ϢΪ��־�������������Ǳ�־���߹ؼ��֣�����������´�������") ;
	m_InstructList[12].m_nID = 12;

	m_InstructList[13].m_StrInstruct = _T("�ɹ�������������ϢΪ��ת��λ�ã���һ��Ϊ�жϱ�־����־�жϳɹ����˾���ת") ;
	m_InstructList[13].m_nID = 13;

	m_InstructList[14].m_StrInstruct = _T("ʧ��������������ϢΪ��ת��λ�ã���һ��Ϊ�жϱ�־����־�ж�ʧ�ܣ��˾���ת") ;
	m_InstructList[14].m_nID = 14;

	m_InstructList[15].m_StrInstruct = _T("����������������ϢΪ��ת������λ��") ;
	m_InstructList[15].m_nID = 15;

	m_InstructList[16].m_StrInstruct = _T("ѭ����㣺������ϢΪ���֣�Ϊѭ��������һ�����ѭ����ʼ����һ��ѭ���յ���ǽ�β") ;
	m_InstructList[16].m_nID = 16;

	m_InstructList[17].m_StrInstruct = _T("ѭ���յ㣺������ϢΪ���֣�Ϊѭ����ʼ��λ�ã����Ŀ��λ�ò���ѭ����㣬��ô�˵���Ч") ;
	m_InstructList[17].m_nID = 17;

	m_InstructList[18].m_StrInstruct = _T("Ĭ���ӳ٣�������ϢΪĬ���ӳ�ʱ�䣬��λ���룬�������������ʼ������") ;
	m_InstructList[18].m_nID = 18;

	m_InstructList[19].m_StrInstruct = _T("����ҳ���򿪿�����Ϣ�У��б��еĵ�ǰ��������ҳ") ;
	m_InstructList[19].m_nID = 19;

	m_InstructList[20].m_StrInstruct = _T("��ѡ��ҳ��ѡ�������Ϣ�У��б��е���һ����ҳ") ;
	m_InstructList[20].m_nID = 20;

	m_InstructList[21].m_StrInstruct = _T("��ȡ���ӣ����տ�����Ϣ�У���ȡ���ӱ���е���Ϣ����ȡ��ҳ����") ;
	m_InstructList[21].m_nID = 21;

	m_InstructList[22].m_StrInstruct = _T("������Ϣ�����տ�����Ϣ�У���ַ���������ļ�λ�ñ�����ϢΪ�ļ�") ;
	m_InstructList[22].m_nID = 22;

	m_InstructList[23].m_StrInstruct = _T("") ;
	m_InstructList[23].m_nID = 0xFFFFFFFF;

	//m_InstructList[23].m_StrInstruct = _T("�ȴ���ҳ���ȴ���ҳ���سɹ������ɹ���һֱ�ȴ�") ;
	//m_InstructList[23].m_nID = 23;
	m_nInstructNum = MY_INSTRUCT_NUM;
}

//ִ��ָ�����ֵ��ָ���Ƿ���ȷִ�У�0Ϊִ��ʧ�ܣ�����1��ִ�е�ָ�����ͣ�����2��ָ�����
int CInstructTranslationAndRun::RunInstruct( int nInstruct , CString &strInstruct , int Sid )
{
	int rtn = 0;
	switch(nInstruct)
	{
	case 2:		rtn = Fun2(strInstruct , Sid );		break;/*��	*/	// 2	ʹ�ô����Զ�ʹ�ô���ҳ������е�ѡ��Ĵ���
	case 3:		rtn = Fun3(strInstruct , Sid );		break;/*��	*/	// 3	ֹͣ����ֹͣʹ�ô���
	case 4:		rtn = Fun4(strInstruct , Sid );		break;/*��	*/	// 4	��ѡ����ѡ����һ������
	case 5:		rtn = Fun5(strInstruct , Sid );		break;/*��	*/	// 5	ˢ��ҳ�棺ˢ����һ���򿪵���ҳ
	case 6:		rtn = Fun6(strInstruct , Sid );		break;/*��	*/	// 6	�Զ�����������д
	case 7:		rtn = Fun7(strInstruct , Sid );		break;/*��	*/	// 7	�ӳ٣��룺������ϢΪ�ӳ�ʱ�䣬��λ����
	case 8:		rtn = Fun8(strInstruct , Sid );		break;			// 8	�����ť��������ϢΪ��ť�ϵ����֣���һ���ɹ�
	case 9:		rtn = Fun9(strInstruct , Sid );		break;/*��	*/	// 9	����ҳ��������ϢΪ����ҳ�ĵ�ַ
	case 11:	rtn = Fun11(strInstruct , Sid );	break;/*��	*/	// 11	������־��������ϢΪҪ�����ı�־���������Ϳ������߼���������������
	case 12:	rtn = Fun12(strInstruct , Sid );	break;/*��	*/	// 12	�жϱ�־��������ϢΪ��־�������������Ǳ�־���߹ؼ��֣����ֻ��������һ���
	case 13:	rtn = Fun13(strInstruct , Sid );	break;/*��	*/	// 13	�ɹ�������������ϢΪ��ת��λ�ã���һ��Ϊ�жϱ�־����־�жϳɹ����˾���ת
	case 14:	rtn = Fun14(strInstruct , Sid );	break;/*��	*/	// 14	ʧ��������������ϢΪ��ת��λ�ã���һ��Ϊ�жϱ�־����־�ж�ʧ�ܣ��˾���ת
	case 15:	rtn = Fun15(strInstruct , Sid );	break;/*��	*/	// 15	����������������ϢΪ��ת������λ��
	case 16:	rtn = Fun16(strInstruct , Sid );	break;/*��	*/	// 16	ѭ����㣺������ϢΪ���֣�Ϊѭ��������һ�����ѭ����ʼ����һ��ѭ���յ���ǽ�β
	case 17:	rtn = Fun17(strInstruct , Sid );	break;/*��	*/	// 17	ѭ���յ㣺������ϢΪ���֣�Ϊѭ����ʼ��λ�ã����Ŀ��λ�ò���ѭ����㣬��ô������ѭ��
	case 18:	rtn = Fun18(strInstruct , Sid );	break;/*��	*/	// 18	Ĭ���ӳ٣�������ϢΪĬ���ӳ�ʱ�䣬��λ���룬�������������ʼ������
	case 19:	rtn = Fun19(strInstruct , Sid );	break;/*��	*/	// 19	����ҳ���򿪿�����Ϣ�У��б��еĵ�ǰ��������ҳ
	case 20:	rtn = Fun20(strInstruct , Sid );	break;/*��	*/	// 20	��ѡ��ҳ��ѡ�������Ϣ�У��б��е���һ����ҳ
	case 21:	rtn = Fun21(strInstruct , Sid );	break;/*��	*/	// 21	��ȡ���ӣ����տ�����Ϣ�У���ȡ���ӱ���е���Ϣ����ȡ��ҳ����
	case 22:	rtn = Fun22(strInstruct , Sid );	break;			// 22	������Ϣ�����տ�����Ϣ�У���ַ���������ļ�λ�ñ�����ϢΪ�ļ�
	}

	return rtn;
}

//�ж�ָ��ĸ�����Ϣ�Ƿ�Ϸ�������ֵ0Ϊ�Ϸ���1Ϊ���Ϸ�
int CInstructTranslationAndRun::TestInstruct( CListCtrl * const m_LclCmd )
{

	//	0	���	1	ָ�����	2	������Ϣ
	int all = m_LclCmd[0].GetItemCount();
	short *nbs = (short *)malloc( sizeof(short) * all );
	memset( nbs , 0 , ( sizeof(short) * all ) );
	CString str;
	int i = 0;
	//////////////////////////////////////////////////////////////////////////
	//ȡȫ��ָ��ı��
	for ( i = 0 ; i < all ; i++ )
	{
		nbs[i] = TranslateInstruct( m_LclCmd[0].GetItemText( i , 1 ) );
	}
	//////////////////////////////////////////////////////////////////////////
	//�ж��ʼ�Ƿ�����ֻ��һ�����û����ӳ�
	if ( 18 != nbs[0] )
	{
		m_StrError.Format( _T("��һ��������Ĭ���ӳ�ʱ��\r\n��ţ�%d") , i );
		free( nbs );
		nbs = NULL;
		return 1;
	}
	for ( i = 1 ; i < all ; i++ )
	{
		if ( 18 == nbs[i] )
		{
			m_StrError.Format( _T("ֻ����һ��Ĭ���ӳ�ʱ��\r\n��ţ�%d") , i );
			free( nbs );
			nbs = NULL;
			return 1;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//�жϿ�ʼ���Ƿ����
	for ( i = 0 ; i < all ; i++ )
	{
		if ( 0 == nbs[i] )
		{
			break;
		}
	}
	if ( i == all )
	{
		m_StrError.Format( _T("����Ҫ��һ����ʼ\r\n��ţ�%d") , i );
		free( nbs );
		nbs = NULL;
		return 1;
	}
	//////////////////////////////////////////////////////////////////////////
	//�鿴��ʼ֮ǰ���Ƿ�������
	for ( i = 0 ; i < all ; i++ )
	{
		if ( 0 == nbs[i] )
		{
			for ( i = i - 1 ; i > 0 ; i-- )
			{
				if ( 10 != nbs[i] )
				{
					m_StrError.Format( _T("��ʼ֮ǰֻ�������ñ�־��Ĭ���ӳ�\r\n��ţ�%d") , i );
					free( nbs );
					nbs = NULL;
					return 1;
				}
			}
			if ( i <= 0 )
			{
				break;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//�жϽ������Ƿ����
	for ( i = 0 ; i < all ; i++ )
	{
		if ( 1 == nbs[i] )
		{
			break;
		}
	}
	if ( i == all )
	{
		m_StrError.Format( _T("������һ������\r\n��ţ�%d") , i );
		free( nbs );
		nbs = NULL;
		return 1;
	}
	if ( i != all - 1 )
	{
		m_StrError.Format( _T("����������ָ�����β��\r\n��ţ�%d") , i );
		free( nbs );
		nbs = NULL;
		return 1;
	}
	//////////////////////////////////////////////////////////////////////////
	//�ж��Ƿ��ж����ʼ��־
	for ( i = 0 ; i < all ; i++ )
	{
		if ( 0 == nbs[i] )
		{
			for ( i++ ; i < all ; i++ )
			{
				if ( 0 == nbs[i] )
				{
					m_StrError.Format( _T("ֻ����һ����ʼ\r\n��ţ�%d") , i );
					free( nbs );
					nbs = NULL;
					return 1;
				}
				if ( 10 == nbs[i] )
				{
					m_StrError.Format( _T("��־�����ڿ�ʼǰ�趨\r\n��ţ�%d") , i );
					free( nbs );
					nbs = NULL;
					return 1;
				}
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//�ж��Ƿ��ж��������־
	for ( i = 0 ; i < all ; i++ )
	{
		if ( 1 == nbs[i] )
		{
			for ( i++ ; i < all ; i++ )
			{
				if ( 1 == nbs[i] )
				{
					m_StrError.Format( _T("ֻ����һ������\r\n��ţ�%d") , i );
					free( nbs );
					nbs = NULL;
					return 1;
				}
				if ( 0 == nbs[i] )
				{
					m_StrError.Format( _T("��ʼ�����ڽ���ǰ\r\n��ţ�%d") , i );
					free( nbs );
					nbs = NULL;
					return 1;
				}
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//�ж��ӳ���Ϣ�Ƿ�Ϸ������Ϸ�����������ᱨ��
	for ( i = 0 ; i < all ; i++ )
	{
		if ( 18 == nbs[i] || 7 == nbs[i] )
		{
			str = m_LclCmd[0].GetItemText( i , 2 );
			if ( stol( str , 0 , 10 ) < 1 )
			{
				str = _T("0");
			}
			m_LclCmd[0].SetItemText( i , 2 , str );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//�ж���ҳ��ʽ
	for ( i = 0 ; i < all ; i++ )
	{
		if ( 5 == nbs[i] || 9 == nbs[i] )
		{
			str = m_LclCmd[0].GetItemText( i , 2 );
			int m , n;
			m = str.Find( _T('.') );
			n = str.ReverseFind( _T('.') );
			if ( 0 == m || ( m + 1 ) == n || n == ( str.GetLength() - 1 ) )
			{
				m_StrError.Format( _T("Ҫ�򿪵���ҳ��ʽ����\r\n��ţ�%d") , i );
				free( nbs );
				nbs = NULL;
				return 1;
			}
			m_LclCmd[0].SetItemText( i , 2 , str );
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//������ʽ
	for ( i = 0 ; i < all ; i++ )
	{
		if ( 11 == nbs[i] )
		{
			int j = 0;
			int k = 0;
			str = m_LclCmd[0].GetItemText( i , 2 );
			TCHAR tchar[] = { _T('+') , _T('-') , _T('*') , _T('/') , _T('%') , _T('=') };
			for ( k = 0 ; k < 6 ; k++ )
			{
				j = str.Find( tchar[k] );
				if( -1 != j )
				{
					break;
				}
			}
			if ( k == 6 )
			{
				m_StrError.Format( _T("�������\r\n��ţ�%d") , i );
				free( nbs );
				nbs = NULL;
				return 1;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//�жϸ�ʽ
	for ( i = 0 ; i < all ; i++ )
	{
		if ( 12 == nbs[i] )
		{
			int j = 0;
			int k = 0;
			str = m_LclCmd[0].GetItemText( i , 2 );
			TCHAR *tchar[] = { _T("<=") , _T("<") , _T(">=") , _T(">") , _T("==") };
			for ( k = 0 ; k < 5 ; k++ )
			{
				j = str.Find( tchar[k] );
				if( -1 != j )
				{
					break;
				}
			}
			if ( k == 5 )
			{
				m_StrError.Format( _T("�жϲ���\r\n��ţ�%d") , i );
				free( nbs );
				nbs = NULL;
				return 1;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//�ж�ѭ���յ�
	int j = 0;
	for ( i = 0 ; i < all ; i++ )
	{
		if ( 0 == nbs[i] )
		{
			j = i ;
		}
		if ( 17 == nbs[i] )
		{
			if ( TranslateInstruct( m_LclCmd[0].GetItemText( i , 1 ) ) < ( j + 1 ) )
			{
				m_StrError.Format( _T("ѭ�����󣬲���ѭ���ؿ�ʼ��֮ǰ\r\n��ţ�%d") , i );
				free( nbs );
				nbs = NULL;
				return 1;
			}
			if ( stol( str , 0 , 10 ) == i )
			{
				m_StrError.Format( _T("ѭ�����󣬲���ָ���Լ�\r\n��ţ�%d") , i );
				free( nbs );
				nbs = NULL;
				return 1;
			}
		}
	}


	free( nbs );
	nbs = NULL;
	return 0;
}

//����ָ�����ֵ�Ƿ���õ���ָ��ֵ��-1Ϊ����ʧ�ܣ�����ֵΪ�ɹ�
int CInstructTranslationAndRun::TranslateInstruct( CString &strInstruct )
{
	for ( UINT i = 0 ; i < m_nInstructNum ; i++ )
	{
		if ( strInstruct.Left(4) == m_InstructList[i].m_StrInstruct.Left(4) )
		{
			return i;
		}
	}
	return -1;
}


// 2	ʹ�ô����Զ�ʹ�ô���ҳ������е�ѡ��Ĵ���
UINT CInstructTranslationAndRun::Fun2( CString &strInstruct , int Sid )
{
	strInstruct = m_pParent->m_DlgProxy.m_LclProxyList.GetItemText( m_pWorkThread->m_nProxyIndex , 0 );
	if ( 0 == m_pParent->SetMyIeProxy( strInstruct ) )
	{
		strInstruct.Format( _T("%d��ʹ��ʧ�ܣ�%d|%s") , Sid , m_pWorkThread->m_nProxyIndex , strInstruct );
		m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
		return 1;
	}
	strInstruct.Format( _T("%d��ʹ�óɹ���%d|%s") , Sid , m_pWorkThread->m_nProxyIndex , strInstruct );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
	return 0;
}

// 3	ֹͣ����ֹͣʹ�ô���
UINT CInstructTranslationAndRun::Fun3( CString &strInstruct , int Sid )
{
	if ( 0 == m_pParent->DelMyIeProxy(  ) )
	{
		strInstruct.Format( _T("%d��ͣ��ʧ�ܣ�%d") , Sid , m_pWorkThread->m_nProxyIndex  );
		m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
		return 1;
	}
	strInstruct.Format( _T("%d��ͣ�óɹ���%d") , Sid , m_pWorkThread->m_nProxyIndex  );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
	return 0;
}

// 4	��ѡ����ѡ����һ������
UINT CInstructTranslationAndRun::Fun4( CString &strInstruct , int Sid )
{
	CString str ;
	m_pWorkThread->m_nProxyIndex++;
	if ( m_pParent->m_DlgProxy.m_LclProxyList.GetItemCount() == m_pWorkThread->m_nProxyIndex )
	{
		m_pWorkThread->m_nProxyIndex = 0;
	}
	strInstruct = m_pParent->m_DlgProxy.m_LclProxyList.GetItemText( m_pWorkThread->m_nProxyIndex , 0 );
	str.Format( _T("%d����ѡ����ɹ���%d|%s") , Sid , m_pWorkThread->m_nProxyIndex , strInstruct );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( str );
	return 0;
}

// 5	ˢ��ҳ�棺ˢ����һ���򿪵���ҳ
UINT CInstructTranslationAndRun::Fun5( CString &strInstruct , int Sid )
{
	m_pParent->m_EdtURL.GetWindowText( strInstruct );
	m_pParent->m_HtmlView->Navigate2( strInstruct );;
	strInstruct.Format( _T("%d��ˢ��ҳ��ɹ���%s") , Sid , strInstruct );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
	return 0;
}

// 6	�Զ�����������д
UINT CInstructTranslationAndRun::Fun6( CString &strInstruct , int Sid )
{
	m_pParent->OnBnClickedButtonFillTheForm();
	strInstruct.Format( _T("%d���Զ����ɹ�") , Sid );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
	return 0;
}

// 7	�ӳ٣��룺������ϢΪ�ӳ�ʱ�䣬��λ����
UINT CInstructTranslationAndRun::Fun7( CString &strInstruct , int Sid )
{
	CString str ;
	Sleep( stol( strInstruct , 0 , 10 ) );
	str.Format( _T("%d���ӳٳɹ���%s") , Sid , strInstruct );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( str );

	return 0;
}

// 8	�����ť��������ϢΪ��ť�ϵ����֣�����һ���ɹ�
UINT CInstructTranslationAndRun::Fun8( CString &strInstruct , int Sid )
{
	m_pParent->m_HtmlView->ClickButton( strInstruct );

	return 0;
}

// 9	����ҳ��������ϢΪ����ҳ�ĵ�ַ
UINT CInstructTranslationAndRun::Fun9( CString &strInstruct , int Sid )
{
	m_pParent->m_HtmlView->Navigate2( strInstruct );
	CString str = strInstruct;
	strInstruct.Format( _T("%d����ҳ�򿪳ɹ���%s") , Sid , str );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
	return 0;
}

// 10	���ñ�־��������ϢΪ��־���ڿ�ʼ����֮ǰ���ã���ͬ��־����������ֻ��ӵ��һ��
UINT CInstructTranslationAndRun::Fun10( CString &strInstruct , int Sid )
{
	m_pWorkThread->m_pStrStack[Sid-1].Str = new CString( strInstruct );
	*(m_pWorkThread->m_pStrStack[Sid-1].Str) = strInstruct.Left( 5 );
	m_pWorkThread->m_pStrStack[Sid-1].nStack = 0;
	strInstruct.Format( _T("%d�����ñ�ʶ��%s = 0") , Sid , *(m_pWorkThread->m_pStrStack[Sid-1].Str) );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
	return 0;
}

// 11	������־��������ϢΪҪ�����ı�־���������Ϳ������߼���������������
UINT CInstructTranslationAndRun::Fun11( CString &strInstruct , int Sid )
{
	CString str2;
	int i = 0;
	int j = 0;
	TCHAR tchar[] = { _T('+') , _T('-') , _T('*') , _T('/') , _T('%') , _T('=') };
	for ( i = 0 ; i < 6 ; i++ )
	{
		j = strInstruct.Find( tchar[i] );
		if( -1 != j )
		{
			break;
		}
	}
	if ( 6 == i )
	{
		strInstruct.Format( _T("%d���ִ�������Ҫ��") , Sid );
		m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
		return 0;
	}
	str2 = strInstruct.Left( j );
	strInstruct.Delete( 0 , j + 1 );
	int k = i;
	// str2 �Ǳ�־  i �Ƿ���  strInstruct ��ֵ
	for ( i = 0 ; i < m_pWorkThread->m_nStrStack ; i++ )
	{
		if ( *(m_pWorkThread->m_pStrStack[i].Str) == str2 )
		{
			break;
		}
	}
	if ( i == m_pWorkThread->m_nStrStack )
	{
		strInstruct.Format( _T("%d���Ҳ���ƥ���־") , Sid );
		m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
		return 0;
	}
	switch( k )
	{//{ _T('+') , _T('-') , _T('*') , _T('/') , _T('%') , _T('=') };
	case 0:	m_pWorkThread->m_pStrStack[i].nStack += stol( strInstruct , 0 , 10 );	break;
	case 1:	m_pWorkThread->m_pStrStack[i].nStack -= stol( strInstruct , 0 , 10 );	break;
	case 2:	m_pWorkThread->m_pStrStack[i].nStack *= stol( strInstruct , 0 , 10 );	break;
	case 3:	m_pWorkThread->m_pStrStack[i].nStack /= stol( strInstruct , 0 , 10 );	break;
	case 4:	m_pWorkThread->m_pStrStack[i].nStack %= stol( strInstruct , 0 , 10 );	break;
	case 5:	m_pWorkThread->m_pStrStack[i].nStack = stol( strInstruct , 0 , 10 );	break;
	}

	strInstruct.Format( _T("%d����ʶ������ɣ�%d") , Sid , m_pWorkThread->m_pStrStack[i].nStack );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
	return 0;
}

// 12	�жϱ�־��������ϢΪ��־�������������Ǳ�־���߹ؼ��֣����ֻ��������һ���
UINT CInstructTranslationAndRun::Fun12( CString &strInstruct , int Sid )
{
	CString str2;
	int i = 0;
	int j = 0;
	TCHAR *tchar[] = { _T("<=") , _T("<") , _T(">=") , _T(">") , _T("==") };
	for ( i = 0 ; i < 5 ; i++ )
	{
		j = strInstruct.Find( tchar[i] );
		if( -1 != j )
		{
			break;
		}
	}
	if ( 5 == i )
	{
		strInstruct.Format( _T("%d���ִ�������Ҫ��") , Sid );
		m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
		return 0;
	}
	str2 = strInstruct.Left( j );
	if ( i == 1 || i == 3 )
	{
		strInstruct.Delete( 0 , j + 1 );
	}
	else
	{
		strInstruct.Delete( 0 , j + 2 );
	}
	int k = i;
	// str2 �Ǳ�־  i �Ƿ���  strInstruct ��ֵ
	for ( i = 0 ; i < m_pWorkThread->m_nStrStack ; i++ )
	{
		if ( *(m_pWorkThread->m_pStrStack[i].Str) == str2 )
		{
			break;
		}
	}
	if ( i == m_pWorkThread->m_nStrStack )
	{
		strInstruct.Format( _T("%d���Ҳ���ƥ���־") , Sid );
		m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
		return 0;
	}
	switch( k )
	{//{ _T("<=") , _T("<") , _T(">=") , _T(">") , _T("==") };
	case 0:	m_pWorkThread->nFlag = ( m_pWorkThread->m_pStrStack[i].nStack <= stol( strInstruct , 0 , 10 ) ) ;	break;
	case 1:	m_pWorkThread->nFlag = ( m_pWorkThread->m_pStrStack[i].nStack < stol( strInstruct , 0 , 10 ) ) ;	break;
	case 2:	m_pWorkThread->nFlag = ( m_pWorkThread->m_pStrStack[i].nStack >= stol( strInstruct , 0 , 10 ) ) ;	break;
	case 3:	m_pWorkThread->nFlag = ( m_pWorkThread->m_pStrStack[i].nStack > stol( strInstruct , 0 , 10 ) ) ;	break;
	case 4:	m_pWorkThread->nFlag = ( m_pWorkThread->m_pStrStack[i].nStack == stol( strInstruct , 0 , 10 ) ) ;	break;
	}

	strInstruct.Format( _T("%d����ʶ�ж���ɣ�%d") , Sid , m_pWorkThread->nFlag );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
	return 0;
}

// 13	�ɹ�������������ϢΪ��ת��λ�ã���һ��Ϊ�жϱ�־����־�жϳɹ����˾���ת
UINT CInstructTranslationAndRun::Fun13( CString &strInstruct , int Sid )
{
	if ( 0 == m_pWorkThread->nFlag )
	{
		m_pWorkThread->nFlag = -1;
		strInstruct.Format( _T("%d����תʧ��") , Sid );
		m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
		return 0;
	}
	m_pWorkThread->nEIP = stol( strInstruct , 0 , 10 );
	strInstruct.Format( _T("%d����ת�ɹ���Ŀ�꣺%d") , Sid , m_pWorkThread->nEIP );
	m_pWorkThread->nFlag = -1;
	m_pWorkThread->nEIP--;
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
	return 0;
}

// 14	ʧ��������������ϢΪ��ת��λ�ã���һ��Ϊ�жϱ�־����־�ж�ʧ�ܣ��˾���ת
UINT CInstructTranslationAndRun::Fun14( CString &strInstruct , int Sid )
{
	if ( 1 == m_pWorkThread->nFlag )
	{
		m_pWorkThread->nFlag = -1;
		strInstruct.Format( _T("%d����תʧ��") , Sid );
		m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
		return 0;
	}
	strInstruct = m_pWorkThread->m_ListCtrl->GetItemText( Sid , 2 );
	m_pWorkThread->nEIP = stol( strInstruct , 0 , 10 );
	strInstruct.Format( _T("%d����ת�ɹ���Ŀ�꣺%d") , Sid , m_pWorkThread->nEIP );
	m_pWorkThread->nFlag = -1;
	m_pWorkThread->nEIP--;
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );

	return 0;
}

// 15	����������������ϢΪ��ת������λ��
UINT CInstructTranslationAndRun::Fun15( CString &strInstruct , int Sid )
{
	m_pWorkThread->nEIP = stol( strInstruct , 0 , 10 );
	strInstruct.Format( _T("%d����ת�ɹ���%d") , Sid , m_pWorkThread->nEIP );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
	m_pWorkThread->nEIP--;
	return 0;
}

// 16	ѭ����㣺������ϢΪ���֣�Ϊѭ��������һ�����ѭ����ʼ����һ��ѭ���յ���ǽ�β
UINT CInstructTranslationAndRun::Fun16( CString &strInstruct , int Sid )
{	//ѭ����㣬ʲô��������֪������ô���¾����ˡ�һ�й�����ѭ���յ������
	strInstruct.Format( _T("%d��ѭ��������óɹ���%s��") , Sid ,
											m_pWorkThread->m_ListCtrl->GetItemText( Sid , 2 ) );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
	return 0;
}

// 17	ѭ���յ㣺������ϢΪ���֣�Ϊѭ����ʼ��λ�ã����Ŀ��λ�ò���ѭ����㣬��ô�˵���Ч
UINT CInstructTranslationAndRun::Fun17( CString &strInstruct , int Sid )
{
	CString str;
	int i = stol( strInstruct , 0 , 10 );
	str = m_pWorkThread->m_ListCtrl->GetItemText( i , 1 );
	if ( 16 == TranslateInstruct( str ) )
	{	//���Ŀ�����ѭ�����
		str = m_pWorkThread->m_ListCtrl->GetItemText( i , 2 );
		int j = stol( str , 0 , 10 );
		if ( j > 0 )
		{	//���ѭ����������0
			j--;
			str.Format( _T("%d") , j );
			m_pWorkThread->m_ListCtrl->SetItemText( i , 2 , str );
			m_pWorkThread->nEIP = i;
			m_pWorkThread->nEIP--;
			str.Format( _T("%d��ѭ���ɹ�����ת����%d") , Sid , i );
			m_pParent->m_DlgList.SetWindowTextToCommandEdit( str );
			return 0;
		}
	}
	str.Format( _T("%d��Ŀ��㲻����㣬��ѭ������") , Sid );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( str );
	return 0;
}

// 18	Ĭ���ӳ٣�������ϢΪĬ���ӳ�ʱ�䣬��λ���룬�������������ʼ������
UINT CInstructTranslationAndRun::Fun18( CString &strInstruct , int Sid )
{
	m_pWorkThread->m_nSleep = stol( strInstruct , 0 , 10 );
	m_StrError.Format( _T("0��Ĭ���ӳ�������ɣ�%d����") , m_pWorkThread->m_nSleep );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( m_StrError );
	return 0;
}

UINT CInstructTranslationAndRun::Fun19( CString &strInstruct , int Sid )
{
	strInstruct = m_pParent->m_DlgCLI.m_LclCLICommandOpenURLList.GetItemText( 
							m_pWorkThread->m_nURLPageIndex , 0 );
	m_pParent->m_HtmlView->Navigate2( strInstruct );
	CString str;
	str.Format( _T("%d����ҳ�򿪳ɹ���%s") , Sid , strInstruct );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( str );
	return 0;
}

UINT CInstructTranslationAndRun::Fun20( CString &strInstruct , int Sid )
{
	m_pWorkThread->m_nURLPageIndex++;
	if ( m_pWorkThread->m_nURLPageIndex >= 
				m_pParent->m_DlgCLI.m_LclCLICommandOpenURLList.GetItemCount() )
	{
		m_pWorkThread->m_nURLPageIndex = 0;
	}
	strInstruct.Format( _T("%d����ѡ��ҳ�ɹ����ڣ�%d��") , Sid , m_pWorkThread->m_nURLPageIndex );
	m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );

	return 0;
}

UINT CInstructTranslationAndRun::Fun21( CString &strInstruct , int Sid )
{
	while ( m_pParent->m_PrcTheHtmlViewOpenProcess.GetPos() != 100 )
	{
		Sleep( 20 );
	}

	CString str;
	m_pParent->m_HtmlView->GetSource( str );
	CString strFrom;
	CString strTo;
	CString strNum;
	CString strTemp;
	int i = 0;
	
	m_pParent->m_DlgCLI.m_EdtCLIGetTheURLOnPageWithHandSymbol.GetWindowText( strFrom );
	m_pParent->m_DlgCLI.m_EdtCLIGetTheURLOnPageWithHandAndLastNum.GetWindowText( strNum );
	m_pParent->m_DlgCLI.m_EdtCLIGetTheURLOnPageWithLastSymbol.GetWindowText( strTo );
	if ( strTo.IsEmpty() || strNum.IsEmpty() )
	{
		while ( 1 )
		{
			i = str.Find( strFrom );
			if ( -1 == i )
			{
				strInstruct.Format( _T("%d����ȡ��Դ�ɹ�������%d��") , Sid , 
							m_pParent->m_DlgCLI.m_LclCLIToGetTheElementFromPage.GetItemCount() );
				m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
				return 0;
			}
			str.Delete( 0 , i );
			i = str.Find( _T('\"') );
			strTemp = str.Left( i );
			m_pParent->m_DlgCLI.m_LclCLIToGetTheElementFromPage.InsertItem( 0 , strTemp );
			strTo.Format( _T("%d") , m_pParent->m_DlgCLI.m_LclCLIToGetTheElementFromPage.GetItemCount() + 1 );
			m_pParent->m_DlgCLI.m_StcCLIElementListCount.SetWindowText( strTo );
			str.Delete( 0 , i + 1 );
		}
	}

	int lenth = strFrom.GetLength();
	int nbt = 0 ;
	int j = 0;
	if ( strNum == _T('*') )
	{
		nbt = -1;
	}
	else
	{
		nbt = stol( strNum , 0 , 10 );
	}
	lenth += nbt;
	nbt = strTo.GetLength();
	while ( 1 )
	{
		i = str.Find( strFrom );
		if ( -1 == i )
		{
			strInstruct.Format( _T("%d����ȡ��Դ�ɹ�������%d��") , Sid , 
						m_pParent->m_DlgCLI.m_LclCLIToGetTheElementFromPage.GetItemCount() );
			m_pParent->m_DlgList.SetWindowTextToCommandEdit( strInstruct );
			return 0;
		}
		str.Delete( 0 , i + strFrom.GetLength() );
		i = 0;
		j = str.Find( strTo );
		if ( i == j )
		{
			continue;
		}
		strTemp = str.Left( j /*+ nbt*/ );
		m_pParent->m_DlgCLI.m_LclCLIToGetTheElementFromPage.InsertItem( 0 , strTemp );
		strTemp.Format( _T("%d") , m_pParent->m_DlgCLI.m_LclCLIToGetTheElementFromPage.GetItemCount() + 1 );
		m_pParent->m_DlgCLI.m_StcCLIElementListCount.SetWindowText( strTemp );
		str.Delete( 0 , j + nbt );
	}

	return 0;
}

UINT CInstructTranslationAndRun::Fun22( CString &strInstruct , int Sid )
{
	return 0;
}