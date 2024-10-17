#include <bits/stdc++.h>
using namespace std;
int main() {
	for(int i =101;i<600;i++){
		if(i%100>20&&i<400) continue;
		else if(i%100>5&&i>400&&i<500) continue;
		else if(i%100>3&&i>500&&i<600) continue;
		cout<<i<<",";
		switch (i/100){
			case 1:
				cout<<"Single Room,"<<123<<endl;
				break;
			case 2:
				cout<<"Double Room,"<<176<<endl;
				break;
			case 3:
				cout<<"Triple Room,"<<223<<endl;
				break;
			case 4:
				if(i%10<=3) cout<<"Standard Suite,"<<500<<endl;
				else if(i%10>3&&i%10<=6) cout<<"Deluxe Suite,"<<900<<endl;
				break;
			case 5:
				cout<<"Presidential Suite,"<<1600<<endl;
				break;
		}
	} 
    return 0;
}
