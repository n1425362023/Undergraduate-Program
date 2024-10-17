#pragma once
#include "afxdialogex.h"
#include "CEXPLORER2.h"


// LiveDlg 对话框

class LiveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LiveDlg)

public:
	LiveDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~LiveDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEXPLORER2 m_live;
	afx_msg void OnBnClickedButton1();
};
