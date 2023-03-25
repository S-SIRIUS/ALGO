#include<stdio.h>
quicksort(int arr[], int start, int end){
	if(start > end){
		return;
	}
	int key = start;
	int i = start+1;
	int j= end;
	int temp;
	
	while(i<=j){
		while(arr[i]<=arr[key]){
			i++;
			
		}
		
		while(arr[j]>=arr[key] && j > start){
			j--;
		}
		
		if( i > j){
			temp=arr[j];
			arr[j]=arr[key];
			arr[key]=temp;
		}
		else{
			temp=arr[i];
			arr[i]=arr[j];
			arr[j]=temp;
			
		}
	}
	quicksort(arr, start, j-1);
	quicksort(arr,j+1, end);
	
	
}

int main(){
	int arr[6]={7,2,5,100,3,99};
	int len=sizeof(arr)/sizeof(int);
	int i;
	quicksort(arr, 0, len-1);
	for(i=0; i<len; i++){
		printf("%d ", arr[i]);
	}
	
}
