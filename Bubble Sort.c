#include <Stdio.h>
int main(){
	int i, j, temp, len;
	int arr[6]={6,3,9,1,2,10};
	len = sizeof(arr)/sizeof(int);
	for (i=0; i<len-1; i++){
		for (j=0; j<len-1; j++){
			if(arr[j]>arr[j+1]){
			temp=arr[j];
			arr[j]=arr[j+1];
			arr[j+1]=temp;
		}
		}
	}
	for (i=0; i<len; i++){
		printf("%d",arr[i]);
	}
	
	return 0;
}
