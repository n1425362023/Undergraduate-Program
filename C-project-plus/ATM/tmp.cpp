#include <iostream>
#include<conio.h>
using namespace std;
static string inputPassword() {
	cout<<"Please enter a 6-digit bank card PIN :"; 
	string str;
	char c;
	int size = 6;
	int count = 0;
	char *password = new char[size]; // 动态申请空间
	while ((c = getch()) != '\r') {

		if (c == 8) { // 退格
			if (count == 0) {
				continue;
			}
			putchar('\b'); // 回退一格
			putchar(' '); // 输出一个空格将原来的*隐藏
			putchar('\b'); // 再回退一格等待输入
			count--;
		}
		if (count == size) { // 最大长度为size-1
			//cout<<endl<<"To achieve the maximum password length"<<endl;
			continue;
		}
		if (c >= '0' && c <= '9') {  // 现实银行卡密码只可包含数字
			putchar('*');  // 接收到一个字符后, 打印一个*
			password[count] = c;
			count++;
		}
	}
	//password[count] = '\0';
	str = password;
    cout<<endl<<str<<endl;
	delete[] password; // 释放空间
	return str; 
}
int main(){
	inputPassword();
}
