//////////////////////////////////////////////////////////////////////////
//
//	HTMLDlg.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
// HTMLDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

//������
#include "Notify.h"
//Cookies��
#include "CookiesMyHTML.h"


//��һ���Ի�������ļ�����ҳ��View���ļ�
#include "HtmlViewMy.h"
//�ڶ����Ի�������ļ������һ���
#include "DlgList.h"
//�������Ի�������ļ�������
#include "DlgProxy.h"
//���ĸ��Ի�������ļ�������̨�ڲ�������Ϣ�ĶԻ���
#include "DlgCommandListInfomation.h"
//������Ի�������ļ��������ʼ��Ի���
#include "DlgEMail.h"
//�������Ի�������ļ���HOOK�Ļ�����Ϣ�ļ�
#include "DlgHOOKBaseMessage.h"

//�����ͷ�ļ�
#include "wininet.h"

//���Լ��ض����A�汾�Ĵ������������Ϣ
typedef struct
{
	DWORD dwAccessType;
	LPCSTR lpszProxy;
	LPCSTR lpszProxyBypass;
} INTERNET_PROXY_INFOA, * LPINTERNET_PROXY_INFOA;

//�ַ���ת�����ֺ�����ֻ����ô�ض���
#ifdef _UNICODE
#define stol wcstol
#else
#define stol strtol
#endif

//��ҳ
#define THEHOMEPAGEDEFINE	_T("www.baidu.com")




class CHtmlViewMy;

// CHTMLDlg �Ի���
class CHTMLDlg : public CDialog
{
// ����
public:
	CHTMLDlg(CWnd* pParent = NULL);	// ��׼���캯��

	~CHTMLDlg(){}
// �Ի�������
	enum { IDD = IDD_HTML_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:

	HICON m_hIcon;

protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void OnCancel();
	virtual void OnOK();

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

public:
	afx_msg void OnBnClickedButtonTheHomePage();
	afx_msg void OnBnClickedButtonGoForward();
	afx_msg void OnBnClickedButtonGoBack();
	afx_msg void OnBnClickedButtonStartRecordView();
	afx_msg void OnBnClickedButtonStopRecordView();
	afx_msg void OnBnClickedButtonOpenTheUrl();
	afx_msg void OnBnClickedButtonFillTheForm();
	afx_msg void OnBnClickedButtonHtmlViewGetCookies();
	void SetDialogEnableWindow( int i = 1 );
public:
	//����
	CNotify m_NotifyMini;
	//����״̬
	UINT m_SW_SHOW_HIDE;

public:		//���Ի����ϵĶ���
	//��ַ��EDIT
	CEdit m_EdtURL;
	//��ַ���ڵĵ�ַ
	CString m_StrURL;
	//ˢ��ҳ��ĵ�ַ
	CString m_StrRecordURL;
	//TabCtrl�ϵ����ж���λ��
	CRect m_RetItem;
	//TABCTRL�ؼ�
	CTabCtrl m_TabCtrlAll;

public:		//���Ի����ϸ���С�Ի�����
	//TABCTRL�ϣ���һ��ҳ�棬Ҳ������ҳҳ������룬HTMLVIEWҳ��
	CHtmlViewMy *m_HtmlView;
	//TABCTRL�ϵڶ�ҳС�Ի���ҳ�棬Ҳ������Щ���֮������߰���Ķ���
	CDlgList m_DlgList;
	//TABCTRL�ϵ�����С�Ի���ҳ�棬Ҳ������Щ�����ܵ�ҳ��
	CDlgProxy m_DlgProxy;
	//TABCTRL�ϵ��ĸ�С�Ի���ҳ�棬����̨�ڲ��Զ�ִ�е���Ϣ��ҳ��
	CDlgCommandListInfomation m_DlgCLI;
	//TABCTRL�ϵ����С�Ի���ҳ�棬�ʼ��Ĳ���ҳ��
	CDlgEMail m_DlgEmail;
	//TABCTRL�ϵ�����С�Ի���ҳ�棬HOOK��ҳ������Ϣ
	CDlgHOOKBaseMessage m_DlgHookBaseMessage;

public:		//����ʹ��ʱ����Ҫ���࣬������ A �汾
	//Proxy
	CStringA m_StrProxy;
	CStringA m_StrProxyByPass;
	INTERNET_PROXY_INFOA ipi;
	CCookiesMyHTML m_Cookies;
	//�������������
	int SetMyIeProxy( CString str );
	//������������
	int DelMyIeProxy();
	//��ȡCookies
	int GetCookiesOnTheHtml( CString &str );

	CEdit m_EdtHtmlViewStatusTextOut;
	CProgressCtrl m_PrcTheHtmlViewOpenProcess;
	CEdit m_EdtHtmlViewCookies;
};
