#include<stdio.h>
#include <time.h> //�ð������ ���� ���

long long recursive_fibo(int count, long long * memo){ //��� return �ڷ����� long long ��(count�� 49�� �Ѿ�� �� ���� �������� ����)

	long long result; // ����� ������ result�� long long �ڷ������� ���� 
	if(count==0){ //���� ��͸� ���ٰ� count�� 0�̸� 0�� �����ϰ� �Լ� ������(Ʈ���� ��) 
		return 0;
	}
	if(count==1){ // ���� ��͸� ���ٰ� count�� 1�̸� 1�� �����ϰ� �Լ� ������(Ʈ���� ��) 
		return 1;
	}
	
	result =recursive_fibo(count-1,memo)+recursive_fibo(count-2,memo);//  ���ȣ���� 2����(count-1, count-2) �׷��� �ϴٺ��� �Լ��� �� ȣ���ϰ� �ؿ������� �ٽ� ���� 
	return result; // result�� ��� return�� 
}

long long dp(int count){ //��� return �ڷ����� long long ��(count�� 49�� �Ѿ�� �� ���� �������� ����), count�� ������ �Ǵ°�
	int i; // �ݺ����� ���� i ���� 
	long long dp_table[count+1]; //dp���̺��� ���� ������ ���⿡ long long �ڷ��� ���� ���� 
	for(i=0; i <= count; i++){ //�ݺ��� �����鼭 dp_table�� �ʱ�ȭ 
		dp_table[i]=0;
	}
	dp_table[1]=1; //dp_table�� ù��° �� 1�� fix, 1���� �����ϴ°����� rule ���� 
	dp_table[2]=1; //dp_table�� �ι�° �� 2�� fix 
	for (i=1; i<=count-2; i++){ // 1���� �츮�� count������ �Ǻ���ġ ����ϸ鼭 dp���̺� �޸������̼���, ���� ���� ����� ����(���̺�)���� ��������� 
		dp_table[i+2]=dp_table[i+1]+dp_table[i];
	}
	return dp_table[count]; //���ϴ� ��ġ�� ���� dp���̺��� ���� 
	
}

int main(){
	int count; // �Ǻ���ġ�� ���° ���� �����ΰ��� ���ڸ� ���� ���� 
	long long recur_ans; //recursive_fibo �Լ���  ��ȯ�� ������ ���� ���� ���� Ŭ �� �ֱ⿡ long long �ڷ��� 
	long long dp_ans; // dp �Լ��� ��ȯ�� ������ ���� ���� ���� Ŭ �� �ֱ⿡ long long �ڷ���
	int i; // �ݺ����� ���� ���� i 
	printf("Input:"); //Input ����Ʈ 
	scanf("%d",&count); // �Է°� count ������ ���� 
	
	long long memo[count+1]; // memo�迭 longlong���� ����, ��ȯ�� ���� �����ؾ� �ϱ� ���� 
	for(i=0; i <= count; i++){ // 
		memo[i]=-1; //�湮���ο� value �����ϴ� memo �迭 -1�� �ʱ�ȭ�� 
	}
	
	double recursive_time=0; //recursive_fibo �Լ��� ����ð� ���庯�� 
	double dp_time=0;//dp �Լ��� ����ð� ���庯�� 
	
	clock_t start1 = clock(); //Ÿ�̸� ����
	recur_ans=recursive_fibo(count, memo); //recursive_fibo �Լ� ȣ�� �� ���� ��°� ���� 
	clock_t end1 = clock(); // Ÿ�̸� ����
	recursive_time=(double)(end1 - start1); // Ÿ�̸� ����ð�(ms) - Ÿ�̸� ���۽ð�(ms)
	
	clock_t start2 = clock(); //Ÿ�̸� ����
	dp_ans=dp(count);//dp�Լ� ȣ�� �� ���� ��°� ���� 
	clock_t end2 = clock(); //Ÿ�̸� ����
	dp_time=(double)(end2 - start2); // Ÿ�̸� ����ð�(ms) - Ÿ�̸� ���۽ð�(ms)
	
	printf("Output:\n"); //Output��� ���� 
	printf("Recursive: %lld / %lf msec\n", recur_ans, recursive_time); // recursive_fibo�� ���ϰ��� ����ð� ��� 
	printf("Dynamic: %lld / %lf msec",dp_ans, dp_time);// dp�Լ��� ���ϰ��� ����ð� ���
	
	return 0;//main�Լ� ���� 
}
