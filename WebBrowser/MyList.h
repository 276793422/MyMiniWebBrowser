//////////////////////////////////////////////////////////////////////////
//
//	MyList.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
/*
	����ֵ��0��������

*/
typedef unsigned int UINT;
#ifndef NULL
#define NULL 0
#endif

#ifndef _MY_LIST_CLASS_
#define _MY_LIST_CLASS_

#define RETURN_TYPE UINT

template< class TYPE = void * , class ARG_TYPE = const TYPE& >
class CMyList
{
private:
	//�ڲ��ṹ��
	struct UnUsed
	{
		UnUsed *pUp;
		UnUsed *pNext;
		TYPE data;
	};

	//�ڲ�Ԫ������
	UINT m_Count;
	//��Ԫ��
	UnUsed *m_pFirst;
	//βԪ��
	UnUsed *m_pLast;

	//�滻���ص���ʱ����
	TYPE rtn ;

public:
	CMyList(  );
	~CMyList(  );

	//��β�����Ԫ�أ�����1ΪҪ��ӵĶ���
	RETURN_TYPE AddItem( ARG_TYPE typeTemp );

	//��ȡ���������ǻ���1��
	RETURN_TYPE GetCount()	{	return m_Count;	}

	//��գ�����Ϊ�ڲ����������TYPEΪָ��Ļ�������Ϊ1�����Ե����ڲ����
	RETURN_TYPE MakeEmpty( UINT deletePoint = 0 );

	//ɾ��ָ��λ�õģ�����Ľ��ϣ�������һ��������0��
	RETURN_TYPE DeleteOn( UINT index , UINT deletePoint = 0 );

	//����λ�ò��룬����ĺ��ƣ�������һ��������0��
	RETURN_TYPE InsertOn( ARG_TYPE typeTemp , UINT index );

	//��������Ѱ�ң�����ֵ�ǻ���0�����������󷵻� -1 
	RETURN_TYPE FindItem( ARG_TYPE typeTemp );

	//�滻�ڲ���ֵ������1��Ҫ�滻��λ�ã�������Ҫ�滻��ֵ
	RETURN_TYPE ToReplace( UINT index , ARG_TYPE typeTemp );

	//������ķ�������
	ARG_TYPE operator[]( UINT index );


};


template< class TYPE , class ARG_TYPE >
CMyList< TYPE , ARG_TYPE >::CMyList()
{
	//�ڲ�Ԫ������
	m_Count = 0;
	//��Ԫ��
	m_pFirst = NULL;
	//βԪ��
	m_pLast = NULL;

}

template< class TYPE , class ARG_TYPE >
CMyList< TYPE , ARG_TYPE >::~CMyList()
{
	MakeEmpty();
}


template< class TYPE , class ARG_TYPE >
//���Ԫ��
RETURN_TYPE CMyList< TYPE , ARG_TYPE >::AddItem( ARG_TYPE typeTemp )
{
	UnUsed *temp = new UnUsed;
	if ( 0 == m_Count )
	{
		if ( NULL != m_pFirst )
		{
			delete m_pFirst;
			m_pFirst = NULL;
		}
		if ( NULL != m_pLast )
		{
			delete m_pLast;
			m_pLast = NULL;
		}
		m_pFirst = temp;
	}
	temp->pUp = m_pLast;
	temp->pNext = NULL;
	if ( NULL != m_pLast )
	{
		m_pLast->pNext = temp;
	}
	m_pLast = temp;

	temp->data = typeTemp;

	m_Count++;

	return 0;
}

template< class TYPE , class ARG_TYPE >
//���
RETURN_TYPE CMyList< TYPE , ARG_TYPE >::MakeEmpty( UINT deletePoint /* = 0 */ )
{
	UnUsed * temp = m_pFirst;
	if ( 1 == deletePoint )
	{
		while ( NULL != temp )
		{
			delete temp->data;
			temp = temp->pNext;
		}
	}

	while ( NULL != m_pFirst )
	{
		temp = m_pFirst;
		m_pFirst = m_pFirst->pNext;
		delete temp;
	}
	m_pFirst = NULL;
	m_pLast = NULL;
	m_Count = 0;

	return 0;
}

template< class TYPE , class ARG_TYPE >
//ɾ��ָ��λ�õģ�����Ľ���
RETURN_TYPE CMyList< TYPE , ARG_TYPE >::DeleteOn( UINT index , UINT deletePoint /* = 0 */ )
{
	if ( index < 0 || index >= m_Count )
	{
		return 1;
	}

	UnUsed * temp = NULL;
	if ( 0 == index )
	{
		if ( 1 == m_Count )
		{
			delete m_pFirst;
			m_pFirst = NULL;
			m_Count--;
			return 0;
		}

		temp = m_pFirst;
		m_pFirst = m_pFirst->pNext;
		m_pFirst->pUp = NULL;
		if ( 1 == deletePoint )
		{
			delete temp->data;
		}
		delete temp;
		m_Count--;
		return 0;
	}
	if ( ( m_Count - 1 ) == index )
	{
		temp = m_pLast;
		m_pLast = m_pLast->pUp;
		m_pLast->pNext = NULL;
		if ( 1 == deletePoint )
		{
			delete temp->data;
		}
		delete temp;
		m_Count--;
		return 0;
	}

	temp = m_pFirst;
	for ( UINT i = 0 ; i < index ; i++ )
	{
		temp = temp->pNext;
	}
	temp->pUp->pNext = temp->pNext;
	temp->pNext->pUp = temp->pUp;
	if ( 1 == deletePoint )
	{
		delete temp->data;
	}
	delete temp;
	m_Count--;
	return 0;
}

template< class TYPE , class ARG_TYPE >
//����λ�ò���
RETURN_TYPE CMyList< TYPE , ARG_TYPE >::InsertOn( ARG_TYPE typeTemp , UINT index )
{
	if ( index < 0 || index > m_Count )
	{
		return 1;
	}

	UnUsed *temp = new UnUsed;

	temp->data = typeTemp;

	if ( 0 == index )
	{
		temp->pNext = m_pFirst;
		m_pFirst->pUp = temp;
		m_pFirst = temp;
		m_pFirst->pUp = NULL;
		m_Count++;
		return 0;
	}

	if ( m_Count == index )
	{
		m_pLast->pNext = temp;
		temp->pUp = m_pLast;
		temp->pNext = NULL;
		m_pLast = temp;
		m_Count++;
		return 0;
	}

	UnUsed *temp2 = m_pFirst;
	for ( UINT i = 0 ; i < index ; i++ )
	{
		temp2 = temp2->pNext;
	}
	temp->pNext = temp2;
	temp->pUp = temp2->pUp;
	temp->pUp->pNext = temp;
	temp2->pUp = temp;
	m_Count++;
	return 0;

}

template< class TYPE , class ARG_TYPE >
//��������Ѱ��
RETURN_TYPE CMyList< TYPE , ARG_TYPE >::FindItem( ARG_TYPE typeTemp )
{
	UINT i = 0;
	int j = 0;
	UnUsed * temp = m_pFirst;
	for ( i = 0 ; i < m_Count ; i++ )
	{
		j = memcmp( &( temp->data ) , &typeTemp , sizeof(typeTemp) );
		if ( 0 == j )
		{
			break;
		}
		temp = temp->pNext;
	}
	if ( i == m_Count )
	{
		return 0xFFFFFFFF;
	}
	return i;
}

template< class TYPE , class ARG_TYPE >
//�滻�ڲ���ֵ������1��Ҫ�滻��λ�ã�������Ҫ�滻��ֵ
RETURN_TYPE CMyList< TYPE , ARG_TYPE >::ToReplace( UINT index , ARG_TYPE typeTemp )
{
	if ( index < 0 || index >= m_Count )
	{
		return 1;
	}

	UnUsed *temp = m_pFirst;

	for ( UINT i = 0 ; i < index ; i++ )
	{
		temp = temp->pNext;
	}

	rtn = temp->data;
	temp->data = typeTemp;
	typeTemp = rtn;

	return 0;
}

template< class TYPE , class ARG_TYPE >
//������ķ�������
ARG_TYPE CMyList< TYPE , ARG_TYPE >::operator[]( UINT index )
{
	if ( index < 0 || index >= m_Count )
	{
		memset( &rtn , 0xFF , sizeof(rtn) );
		return rtn;
	}

	UnUsed *temp = m_pFirst;

	for ( UINT i = 0 ; i < index ; i++ )
	{
		temp = temp->pNext;
	}
	return temp->data;
}





#endif