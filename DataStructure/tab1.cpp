#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
int arr[1000];
int n=0,p=1;
void show()
{
	printf("----------------------------- \n");
	printf(" the function of the list\n");
	printf("1: insert\n");
	printf("2: delete\n");
	printf("3: save new element\n");
	printf("4: read list\n");
	printf("5: check\n");
	printf("6: the length of the list\n");
	printf("0: end\n");
	printf("----------------------------- \n");
}
void insert(){
	int index,value;
	printf("the list's index: ");
	scanf("%d",&index);
	if(index>=999||index>n||index<0){
		printf("No space");
	
		return;
	}
	printf("enter the elements:");
	scanf("%d",&value);
	for(int i= n-1;i>index;i--){
		arr[i+1]=arr[i];
	}
	arr[index-1]=value;
	n++;
	printf("OK\n");
}
void remove(){
	int index;
	printf("enter the index:");
	scanf("%d",&index);
	if(index>=999||index>n||index<0){
		printf("No space");
		return;
	}
	for(int i= index-1;i<n-1;i++){
		arr[i]=arr[i+1];
	}
	n--;
	printf("OK\n");
}
void save(){
	int value;
	printf("enter the elements:");
	scanf("%d",&value);
	arr[n]=value;
	n++;
	printf("ok\n");
}
void read(){
	for(int i =0;i<n;i++){
		printf("index:%d --- value :%d\n",i,arr[i]);
	}
}
void check(){
	int index;
	printf("enter the index:");
	scanf("%d",&index);
	printf("\n");
	if(index>=999||index>n||index<0){
		printf("No space\n");
		return;
	}
	printf("the list's element: %d\n",arr[index-1]);
}
void length(){
	printf("the length of the list : %d\n",n);
}
int main(){
	do{
		printf("please input the length of list:");
		scanf("%d",&n);
		printf("\n");
		if(n<0&&n>1000) printf("ERRO"),n=0;
	}while(n<0&&n>1000);
	printf("enter the elements \n");
	for(int i =0;i<n;i++){
		scanf("%d",&arr[i]);
		
	}
	while(1){
		show();
		printf("what's your option: ");
		scanf("%d",&p);
		switch(p){
			case 0:
				printf("Thanks using ");
				return 0;
			case 1:
				insert();
				system("pause");
				system("cls");
				break;
			case 2:
				remove();
				system("pause");
				system("cls");
				break;
			case 3:
				save();
				system("pause");
				system("cls");
				break;
			case 4:
				read();
				system("pause");
				system("cls");
				break;
			case 5:
				check();
				system("pause");
				system("cls");
				break;
		    case 6:
		    	length();
		    	system("pause");
		    	system("cls");
		    	break;
		    default:
		    	system("cls");
		}
	}
	return 0;
} 
