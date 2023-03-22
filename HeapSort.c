


#include<stdio.h>
void heapify(int *arr, int size){
	int i;
	for(i=1; i<size; ++i){
		int child=i;
		do{
			int root = (child-1)/2;
			if(arr[root]<arr[child]){
				int temp = arr[root];
				arr[root]=arr[child];
				arr[child]=temp;
			}
			child=root;
			
		}while(child!=0);
	}
	
}

void heap(int *arr, int *size){
	int temp=arr[0];
	arr[0]=arr[*size-1];
	arr[*size-1]=temp;
	--(*size);
}


int main(){
	int arr[10] = {5, 6, 10, 4, 3, 8, 7, 1, 2, 9};
	int size=sizeof(arr)/sizeof(int);
	int len=size;
	int i;
	
	for(i=0; i<len; ++i){
		heapify(arr, size);
		heap(arr,&size);
	}	
	for(i=0; i<len; ++i){
		printf("%d ", arr[i]);
	}
	return 0;
}
