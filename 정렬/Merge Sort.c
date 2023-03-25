#include<stdio.h>
int sorting[6];

mergesort(int arr[],int start, int end){
	int middle;
	if(start < end){
		middle=(start+end)/2;
		mergesort(arr,start,middle);
		mergesort(arr,middle+1,end);
		merge(arr,start,middle, end);
	}
	
}
merge(int arr[],int start,int middle,int end){
	int i= start;
	int j=middle+1;
	int k=start;
	int l;
	while(i<=middle && j<=end){
		if(arr[i]<arr[j]){
			sorting[k]=arr[i];
			i++;
		}
		else{
			sorting[k]=arr[j];
			j++;
		}
		k++;
	}
	if(i > middle){
		for(l=j; l<=end; l++){
		sorting[k]=arr[l];
		k++;
	}
	}
	else{
		for(l=i; l<=middle; l++){
			sorting[k]=arr[l];
			k++;
		}
	}
	for (l=start; l<=end; l++){
		arr[l]=sorting[l];
	}
	
}


int main(){
	int arr[6]={5,2,10,3,4,100};
	int i=0;
	int len=sizeof(arr)/sizeof(int);
	mergesort(arr,0,len-1);
	for(i=0; i<len; i++){
		printf("%d ",arr[i]);
	}
	
}
