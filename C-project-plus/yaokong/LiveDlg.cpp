// LiveDlg.cpp: 实现文件
//

#include "pch.h"
#include "yaokong.h"
#include "afxdialogex.h"
#include "LiveDlg.h"


// LiveDlg 对话框

IMPLEMENT_DYNAMIC(LiveDlg, CDialogEx)

LiveDlg::LiveDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

LiveDlg::~LiveDlg()
{
}

void LiveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER2, m_live);
}


BEGIN_MESSAGE_MAP(LiveDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &LiveDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &LiveDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// LiveDlg 消息处理程序


void LiveDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void LiveDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_live.Navigate(_T("http://tool.pfan.cn/m3u8?url=http%3A%2F%2Fcdn3.toronto360.tv%3A8081%2Ftoronto360%2Fhd%2Fplaylist.m3u8"), NULL, NULL, NULL, NULL);
}
