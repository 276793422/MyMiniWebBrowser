//////////////////////////////////////////////////////////////////////////
//
//	HTMLDlg.h
//
//	Copyright(C) 2011 Zoo
//
//////////////////////////////////////////////////////////////////////////
// HTMLDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

//托盘类
#include "Notify.h"
//Cookies类
#include "CookiesMyHTML.h"


//第一个对话框的类文件，网页的View类文件
#include "HtmlViewMy.h"
//第二个对话框的类文件，填表一类的
#include "DlgList.h"
//第三个对话框的类文件，代理
#include "DlgProxy.h"
//第四个对话框的类文件，控制台内部控制信息的对话框
#include "DlgCommandListInfomation.h"
//第五个对话框的类文件，电子邮件对话框
#include "DlgEMail.h"
//第六个对话框的类文件，HOOK的基本信息文件
#include "DlgHOOKBaseMessage.h"

//代理的头文件
#include "wininet.h"

//我自己重定义的A版本的代理服务器的信息
typedef struct
{
	DWORD dwAccessType;
	LPCSTR lpszProxy;
	LPCSTR lpszProxyBypass;
} INTERNET_PROXY_INFOA, * LPINTERNET_PROXY_INFOA;

//字符串转化数字函数，只能这么重定义
#ifdef _UNICODE
#define stol wcstol
#else
#define stol strtol
#endif

//主页
#define THEHOMEPAGEDEFINE	_T("www.baidu.com")




class CHtmlViewMy;

// CHTMLDlg 对话框
class CHTMLDlg : public CDialog
{
// 构造
public:
	CHTMLDlg(CWnd* pParent = NULL);	// 标准构造函数

	~CHTMLDlg(){}
// 对话框数据
	enum { IDD = IDD_HTML_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:

	HICON m_hIcon;

protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void OnCancel();
	virtual void OnOK();

	// 生成的消息映射函数
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
	//托盘
	CNotify m_NotifyMini;
	//隐藏状态
	UINT m_SW_SHOW_HIDE;

public:		//主对话框上的东西
	//地址栏EDIT
	CEdit m_EdtURL;
	//地址栏内的地址
	CString m_StrURL;
	//刷新页面的地址
	CString m_StrRecordURL;
	//TabCtrl上的所有东西位置
	CRect m_RetItem;
	//TABCTRL控件
	CTabCtrl m_TabCtrlAll;

public:		//主对话框上各个小对话框类
	//TABCTRL上，第一个页面，也就是网页页面软编码，HTMLVIEW页面
	CHtmlViewMy *m_HtmlView;
	//TABCTRL上第二页小对话框页面，也就是那些填表之类的乱七八糟的东西
	CDlgList m_DlgList;
	//TABCTRL上第三个小对话框页面，也就是那些代理功能的页面
	CDlgProxy m_DlgProxy;
	//TABCTRL上第四个小对话框页面，控制台内部自动执行的信息的页面
	CDlgCommandListInfomation m_DlgCLI;
	//TABCTRL上第五个小对话框页面，邮件的操作页面
	CDlgEMail m_DlgEmail;
	//TABCTRL上第六个小对话框页面，HOOK网页基本信息
	CDlgHOOKBaseMessage m_DlgHookBaseMessage;

public:		//代理使用时候需要的类，必须用 A 版本
	//Proxy
	CStringA m_StrProxy;
	CStringA m_StrProxyByPass;
	INTERNET_PROXY_INFOA ipi;
	CCookiesMyHTML m_Cookies;
	//设置浏览器代理
	int SetMyIeProxy( CString str );
	//清除浏览器代理
	int DelMyIeProxy();
	//获取Cookies
	int GetCookiesOnTheHtml( CString &str );

	CEdit m_EdtHtmlViewStatusTextOut;
	CProgressCtrl m_PrcTheHtmlViewOpenProcess;
	CEdit m_EdtHtmlViewCookies;
};
