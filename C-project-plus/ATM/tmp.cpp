#include <iostream>
#include<conio.h>
using namespace std;
static string inputPassword() {
	cout<<"Please enter a 6-digit bank card PIN :"; 
	string str;
	char c;
	int size = 6;
	int count = 0;
	char *password = new char[size]; // ��̬����ռ�
	while ((c = getch()) != '\r') {

		if (c == 8) { // �˸�
			if (count == 0) {
				continue;
			}
			putchar('\b'); // ����һ��
			putchar(' '); // ���һ���ո�ԭ����*����
			putchar('\b'); // �ٻ���һ��ȴ�����
			count--;
		}
		if (count == size) { // ��󳤶�Ϊsize-1
			//cout<<endl<<"To achieve the maximum password length"<<endl;
			continue;
		}
		if (c >= '0' && c <= '9') {  // ��ʵ���п�����ֻ�ɰ�������
			putchar('*');  // ���յ�һ���ַ���, ��ӡһ��*
			password[count] = c;
			count++;
		}
	}
	//password[count] = '\0';
	str = password;
    cout<<endl<<str<<endl;
	delete[] password; // �ͷſռ�
	return str; 
}
int main(){
	inputPassword();
}
