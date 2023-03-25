#include<stdio.h>
int main(){
	int i, j, len, temp;
	int arr[6]={6,3,1,5,8,10};
	len=sizeof(arr)/sizeof(int);
	
	for(i=0; i<len; i++){
		int j=i-1;
		while(j>=0 &&  (arr[j+1]<arr[j])){
			temp=arr[j];
			arr[j]=arr[j+1];
			arr[j+1]=temp;
			j--;
		}
	}
	for(i=0; i<len; i++){
		printf("%d ",arr[i]);
	}
	return 0;
}
