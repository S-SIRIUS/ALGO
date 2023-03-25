#include <stdio.h>


int main(){
	int all[7]={1,4,2,9,3,17,6};
	int i, j, temp, len;
	len = (sizeof(all)/sizeof(int));
	for(i=0; i<len; i++){
		for(j=0; j<=i; j++){
			if(all[j] > all[i]){
				temp=all[j];
				all[j]=all[i];
				all[i]=temp;
			}
		}
	}

	for(i=0; i< len; i++){
		printf("%d",all[i]);
	}
	return 0;
}
