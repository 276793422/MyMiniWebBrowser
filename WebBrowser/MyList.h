//////////////////////////////////////////////////////////////////////////
//
//	MyList.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
/*
	返回值：0正常返回

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
	//内部结构体
	struct UnUsed
	{
		UnUsed *pUp;
		UnUsed *pNext;
		TYPE data;
	};

	//内部元素数量
	UINT m_Count;
	//首元素
	UnUsed *m_pFirst;
	//尾元素
	UnUsed *m_pLast;

	//替换返回的临时变量
	TYPE rtn ;

public:
	CMyList(  );
	~CMyList(  );

	//在尾部添加元素，参数1为要添加的东西
	RETURN_TYPE AddItem( ARG_TYPE typeTemp );

	//获取最大个数，是基于1的
	RETURN_TYPE GetCount()	{	return m_Count;	}

	//清空，参数为内部方法，如果TYPE为指针的话，参数为1，可以调用内部清空
	RETURN_TYPE MakeEmpty( UINT deletePoint = 0 );

	//删除指定位置的，后面的接上，和数组一样，基于0的
	RETURN_TYPE DeleteOn( UINT index , UINT deletePoint = 0 );

	//按照位置插入，后面的后推，和数组一样，基于0的
	RETURN_TYPE InsertOn( ARG_TYPE typeTemp , UINT index );

	//按照数据寻找，返回值是基于0的索引，错误返回 -1 
	RETURN_TYPE FindItem( ARG_TYPE typeTemp );

	//替换内部的值，参数1：要替换的位置，参数二要替换的值
	RETURN_TYPE ToReplace( UINT index , ARG_TYPE typeTemp );

	//用数组的方法访问
	ARG_TYPE operator[]( UINT index );


};


template< class TYPE , class ARG_TYPE >
CMyList< TYPE , ARG_TYPE >::CMyList()
{
	//内部元素数量
	m_Count = 0;
	//首元素
	m_pFirst = NULL;
	//尾元素
	m_pLast = NULL;

}

template< class TYPE , class ARG_TYPE >
CMyList< TYPE , ARG_TYPE >::~CMyList()
{
	MakeEmpty();
}


template< class TYPE , class ARG_TYPE >
//添加元素
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
//清空
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
//删除指定位置的，后面的接上
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
//按照位置插入
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
//按照数据寻找
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
//替换内部的值，参数1：要替换的位置，参数二要替换的值
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
//用数组的方法访问
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