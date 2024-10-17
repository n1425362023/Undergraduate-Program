// ChangeDlg.cpp: 实现文件
//

#include "pch.h"
#include "count.h"
#include "afxdialogex.h"
#include "ChangeDlg.h"
#include "count.h"
#include "Speak.h"
// ChangeDlg 对话框
IMPLEMENT_DYNAMIC(ChangeDlg, CDialogEx)

ChangeDlg::ChangeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ChangeDlg, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

ChangeDlg::~ChangeDlg()
{
}

void ChangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ChangeDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ChangeDlg::OnBnClickedOk)
	ON_EN_CHANGE(m_password1, &ChangeDlg::OnEnChangepassword1)
	ON_EN_CHANGE(m_password2, &ChangeDlg::OnEnChangepassword2)
END_MESSAGE_MAP()


// ChangeDlg 消息处理程序


void ChangeDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString new_pssword1="0";
	CString new_pssword2="0";
	GetDlgItem(m_password1)->GetWindowTextA(new_pssword1);
	GetDlgItem(m_password2)->GetWindowTextA(new_pssword2);
	
	/*while (file.ReadString(line)) {
		Account m_tmp;
		CString token;
		int pos = 0;
		int index = 0;
		m_tmp.Number = (line.Tokenize(_T(","), pos));
		m_tmp.Password = (line.Tokenize(_T(","), pos));
		data.push_back(m_tmp);
	}
	*/
	bool flag = false;
	for (std::vector<Account>::iterator it1 = data.begin();it1 != data.end();it1++) {
		if (strcmp(account.Number, it1->Number) == 0 &&  strcmp(new_pssword1, new_pssword2) == 0) {
			it1->Password = new_pssword2;
			it1->money = account.money;
			CStdioFile  file;
			file.Open("./account.csv", CFile::modeCreate| CFile::modeWrite);
			for (std::vector<Account>::iterator it2 = data.begin();it2 != data.end();it2++) {
				file.WriteString(it2->Number + ",");
				file.WriteString(it2->Password + ",");
				CString moneyString;
				moneyString.Format(_T("%d"), it2->money);
				file.WriteString(moneyString + "\n");
			}
			file.Close();
			flag = true;
			Say_init("successful");
			MessageBox("successful");
			CDialogEx::OnOK();
			break;
		}
		
		
	}
	if(!flag) {
			Say_init("fail,please enter again");
			MessageBox("fail,please enter again");
		}
}

void ChangeDlg::OnEnChangepassword1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
void ChangeDlg::OnEnChangepassword2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
