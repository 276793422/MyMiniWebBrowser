//////////////////////////////////////////////////////////////////////////
//
//	HtmlViewMy.cpp
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
// HtmlViewMy.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HTML.h"
#include "HtmlViewMy.h"

#include "comutil.h"


// CHtmlViewMy

IMPLEMENT_DYNCREATE(CHtmlViewMy, CHtmlView)

CHtmlViewMy::CHtmlViewMy()
{

}

CHtmlViewMy::~CHtmlViewMy()
{
}

void CHtmlViewMy::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHtmlViewMy, CHtmlView)
END_MESSAGE_MAP()


// CHtmlViewMy ���

#ifdef _DEBUG
void CHtmlViewMy::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CHtmlViewMy::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG


// CHtmlViewMy ��Ϣ�������

void CHtmlViewMy::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
}

void CHtmlViewMy::OnStatusTextChange(LPCTSTR lpszText)
{
	// TODO: �ڴ����ר�ô����/����û���
	m_pParent->m_EdtHtmlViewStatusTextOut.SetWindowText( lpszText );
	TRACE( lpszText );
	TRACE( "\n" );

	//CHtmlView::OnStatusTextChange(lpszText);
}

UINT CHtmlViewMy::FillTheList()
{
	IHTMLDocument2 *pHTMLDocument2=(IHTMLDocument2*)(this->GetHtmlDocument());
	if ( NULL == pHTMLDocument2 )
	{
		return 10;
	}
	//pHTMLDocument2->clear();
	IHTMLElementCollection* pColl;
	IHTMLWindow2 *win;
	IHTMLFormElement *form;
	HRESULT hr;
	hr = pHTMLDocument2->get_links( &pColl );
	ERROR_MESSAGE( hr , _T("get_linksʧ��") , 1 );

	LONG celem;
	hr = pColl->get_length( &celem );
	ERROR_MESSAGE( hr , _T("get_lenthʧ��") , 2 );

	VARIANT varIndex,var2;
	for( int i = 0 ; i < celem ; i++ )
	{
		varIndex.vt = VT_UINT;
		varIndex.lVal = i;
		VariantInit( &var2 );
		IDispatch* pDisp;
		hr = pColl->item( varIndex , var2 , &pDisp );
		if( hr == S_OK )
		{
			BSTR bs;
			IHTMLAnchorElement *pa;
			hr = pDisp->QueryInterface( IID_IHTMLAnchorElement , (void**)&pa );
			pa->get_href( &bs );
			TRACE( bs );
			CString u( bs );
			if( u == "D:\\HTML\\reg.asp.htm" )
			{
				Navigate2( u , NULL , NULL );
			}
		}
	}

	hr = pHTMLDocument2->get_all( &pColl );
	ERROR_MESSAGE( hr , _T("get_allʧ��") , 3 );

	hr = pColl->get_length( &celem );
	ERROR_MESSAGE( hr , _T("get_lengthʧ��") , 4 );

	for( int i = 0 ; i < celem ; i++ )
	{
		varIndex.vt = VT_UINT;
		varIndex.lVal = i;
		VariantInit( &var2 );
		IDispatch* pDisp;
		hr = pColl->item( varIndex , var2 , &pDisp );

		if( hr == S_OK )
		{
			IHTMLElement *pElem;
			hr = pDisp->QueryInterface( IID_IHTMLElement , (void**)&pElem );
			if( hr == S_OK )
			{
				CString ts,ts1,tss;
				tss="";
				BSTR bs;
				pElem->get_tagName( &bs );
				ts = CString( bs );

				//������if�����ж�����ʲô��
				if( ts == "SELECT" )
				{
					IHTMLSelectElement *pp;
					hr = pDisp->QueryInterface( IID_IHTMLSelectElement ,
												(void**)&pp);
					pp->get_name( &bs );
					ts = CString( bs );
					if( ts == "sltCountry" )
					{
						pp->put_selectedIndex(0);
					}
					if( ts == "sltProvinceId" )
					{
						pp->put_selectedIndex( 1 );
						pHTMLDocument2->get_parentWindow( &win );
						CString sq1,sq2;
						sq1 = "SelectProvice()";
						sq2 = "javascript";
						hr = win->execScript( sq1.AllocSysString() ,
												sq2.AllocSysString() ,
												&var2 );
						if( hr != S_OK )
						{
							MessageBox( _T("error") );
						}
					}
					if(ts=="sltAllLocId")
					{
						pp->put_selectedIndex(0);
					}
				}

				//�ڶ����жϱ�
				if( ts == "FORM" )
				{
					hr = pDisp->QueryInterface( IID_IHTMLFormElement ,
												(void**)&form);
					if(hr!=S_OK)
					{
						MessageBox( _T("error form") );
					}
					continue;
				}

				//�����Ҫ�����
				if( ts == "INPUT" )
				{
					IHTMLInputElement* input;
					hr = pDisp->QueryInterface( IID_IHTMLInputElement ,
												(void**)&input);
					input->get_name( &bs );
					ts = CString( bs );
					int all = m_pParent->m_DlgList.m_LBX[0].GetCount();
					CString str;
					for ( int j = 0 ; j < all ; j++ )
					{
						m_pParent->m_DlgList.m_LBX[0].GetText( j , str );
						//Ӧ���ǿ�ʼ�ж��ֶ���
						if( ts == str )
						{
							m_pParent->m_DlgList.m_LBX[1].GetText( j , str );
							//ֵ
							if ( str == _T("*****") )
							{
								ts1 = SrandString();
							}
							else
							{
								ts1 = str;
							}
							input->put_value( ts1.AllocSysString() );
							TRACE("input->put_value( ts1.AllocSysString() )\n");
						}
					}
				}
				TRACE("%d:%s\n",i,ts);
			}
		}
	}
	return 0;
}


CString CHtmlViewMy::SrandString()
{
	time_t lrand = time( 0 );
	lrand = lrand << ( lrand & 0x1F );
	CString str;
	str.Format( _T("%10ud") , lrand );

	return str;
}


void CHtmlViewMy::OnProgressChange(long nProgress, long nProgressMax)
{
	// TODO: �ڴ����ר�ô����/����û���
	//m_pParent->m_PrcTheHtmlViewOpenProcess.SetWindowText( _T("123") );
	if ( -1 == nProgress )
	{
		m_pParent->m_PrcTheHtmlViewOpenProcess.SetPos( 100 );
		return;
	}
	if ( 0 == nProgressMax )
	{
		m_pParent->m_PrcTheHtmlViewOpenProcess.SetPos( 100 );
		return;
	}

	m_pParent->m_PrcTheHtmlViewOpenProcess.SetPos( nProgress * 100 / nProgressMax );

	CHtmlView::OnProgressChange(nProgress, nProgressMax);
}

void CHtmlViewMy::OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel)
{
	// TODO: �ڴ����ר�ô����/����û���

	CString str = lpszURL;
	if ( str.Left(7) != _T("http://") )
	{
		CHtmlView::OnBeforeNavigate2(lpszURL, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
		return;
	}

	if ( _T("about:blank") == str )
	{
		return;
	}

	m_pParent->m_EdtURL.SetWindowText( lpszURL );

	m_pParent->OnBnClickedButtonHtmlViewGetCookies();

	CHtmlView::OnBeforeNavigate2(lpszURL, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
}

UINT CHtmlViewMy::ClickButton( CString strBtnName )
{

	//IHTMLDocument * pDoc = (IHTMLDocument *)GetHtmlDocument();

	//CComQIPtr<IHTMLDocument3> pDoc3(pDoc);
	//CComQIPtr<IHTMLDocument4> pDoc4(pDoc);
	//if( pDoc3 && pDoc4 )
	//{
	//	IHTMLElement * pElem = NULL;
	//	pDoc3->getElementById( _bstr_t("btnTest"), &pElem);

	//	CComQIPtr<IHTMLElement3> pElem3(pElem);
	//	if( pElem3 )
	//	{
	//		CComPtr<IHTMLEventObj> pEvent;
	//		pDoc4->createEventObject( NULL, &pEvent);

	//		if( pEvent )
	//		{
	//			_variant_t vEvent(pEvent);
	//			VARIANT_BOOL vbSuccess = VARIANT_FALSE;
	//			pElem3->fireEvent( _bstr_t("onclick")
	//				, &vEvent
	//				, &vbSuccess
	//				);
	//		}

	//	}
	//} 

	return 0;
}