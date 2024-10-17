#include <iostream>
using namespace std;
class a{
	public:
		a(int i):a1(i){cout<<"a:"<<a1<<endl;}
		~a(){
			cout<<"Delete a"<<endl;
		}
	private:
		int a1;
};
class b{
	public:
		b(int j):b1(j){cout<<"b:"<<b1<<endl;}
		~b(){
			cout<<"Delete b"<<endl;
		}
	private:
		int b1;
};
class c:public b,public a{
	public:
		c(int i,int j,int k):a(i),b(j),c1(k){
			cout<<"c:"<<c1<<endl;
		}
		~c(){
			cout<<"Delete c"<<endl;
		}
	private:
		int c1;
};
int main(){
	class c t(1,2,3);
} 
