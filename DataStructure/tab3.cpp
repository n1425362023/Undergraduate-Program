#include "stdio.h"
#include "stdlib.h"
#include "time.h"
int Paritition(int arr[] ,int low,int high){
    int privot = arr[low];
    while (low<high){
        while(low<high&&arr[high]>=privot){
            high--;
        }
        arr[low]=arr[high];
        while(low<high&&arr[low]<=privot){
            low++;
        }
        arr[high]=arr[low];
        arr[low]=privot;
    }
    return low;
}
void Quick(int arr[],int low,int high){
    if(low<high){
        int privot = Paritition(arr,low,high);
        Quick (arr,low,privot-1);
        Quick (arr,privot+1,high);
    }
}
int main(){
    srand(time(nullptr));
    int n=rand()%100;
    int arr[n];
    printf("原始顺序\n");
    for(int i=0; i<n;i++){
        arr[i] = rand()%1000;
    }
    for(int i=0; i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    Quick(arr,0,n-1);
    printf("快速排序\n");
    for(int i=0; i<n;i++){
        printf("%d ",arr[i]);
    }
    return 0;
}
