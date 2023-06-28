#include<stdio.h>
#include <time.h> //시간계산을 위한 헤더

long long recursive_fibo(int count, long long * memo){ //출력 return 자료형이 long long 임(count가 49를 넘어가면 그 값을 담을수가 없음)

	long long result; // 결과를 저장할 result를 long long 자료형으로 선언 
	if(count==0){ //만약 재귀를 돌다가 count가 0이면 0을 리턴하고 함수 종료함(트리의 끝) 
		return 0;
	}
	if(count==1){ // 만약 재귀를 돌다가 count가 1이면 1을 리턴하고 함수 종료함(트리의 끝) 
		return 1;
	}
	
	result =recursive_fibo(count-1,memo)+recursive_fibo(count-2,memo);//  재귀호출을 2번함(count-1, count-2) 그렇게 하다보면 함수를 쭉 호출하고 밑에서부터 다시 리턴 
	return result; // result를 계속 return함 
}

long long dp(int count){ //출력 return 자료형이 long long 임(count가 49를 넘어가면 그 값을 담을수가 없음), count는 기준이 되는값
	int i; // 반복문을 위한 i 변수 
	long long dp_table[count+1]; //dp테이블에는 실제 정답이 담기기에 long long 자료형 으로 선언 
	for(i=0; i <= count; i++){ //반복문 돌리면서 dp_table을 초기화 
		dp_table[i]=0;
	}
	dp_table[1]=1; //dp_table의 첫번째 값 1로 fix, 1부터 시작하는것으로 rule 정함 
	dp_table[2]=1; //dp_table의 두번째 값 2로 fix 
	for (i=1; i<=count-2; i++){ // 1부터 우리의 count값까지 피보나치 계산하면서 dp테이블에 메모이제이션함, 따라서 값을 저장된 공간(테이블)에서 가져오면됨 
		dp_table[i+2]=dp_table[i+1]+dp_table[i];
	}
	return dp_table[count]; //원하는 위치의 값을 dp테이블에서 리턴 
	
}

int main(){
	int count; // 피보나치의 몇번째 항을 볼것인가의 숫자를 위한 변수 
	long long recur_ans; //recursive_fibo 함수의  반환값 저장을 위한 변수 값이 클 수 있기에 long long 자료형 
	long long dp_ans; // dp 함수의 반환값 저장을 위한 변수 값이 클 수 있기에 long long 자료형
	int i; // 반복문을 위한 변수 i 
	printf("Input:"); //Input 프린트 
	scanf("%d",&count); // 입력값 count 변수에 저장 
	
	long long memo[count+1]; // memo배열 longlong으로 선언, 반환된 값을 저장해야 하기 때문 
	for(i=0; i <= count; i++){ // 
		memo[i]=-1; //방문여부와 value 저장하는 memo 배열 -1로 초기화함 
	}
	
	double recursive_time=0; //recursive_fibo 함수의 수행시간 저장변수 
	double dp_time=0;//dp 함수의 수행시간 저장변수 
	
	clock_t start1 = clock(); //타이머 시작
	recur_ans=recursive_fibo(count, memo); //recursive_fibo 함수 호출 후 최종 출력값 저장 
	clock_t end1 = clock(); // 타이머 종료
	recursive_time=(double)(end1 - start1); // 타이머 종료시간(ms) - 타이머 시작시간(ms)
	
	clock_t start2 = clock(); //타이머 시작
	dp_ans=dp(count);//dp함수 호출 후 최종 출력값 저장 
	clock_t end2 = clock(); //타이머 종료
	dp_time=(double)(end2 - start2); // 타이머 종료시간(ms) - 타이머 시작시간(ms)
	
	printf("Output:\n"); //Output출력 시작 
	printf("Recursive: %lld / %lf msec\n", recur_ans, recursive_time); // recursive_fibo의 리턴값과 수행시간 출력 
	printf("Dynamic: %lld / %lf msec",dp_ans, dp_time);// dp함수의 리턴값과 수행시간 출력
	
	return 0;//main함수 종료 
}
