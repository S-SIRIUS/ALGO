#include <stdio.h>
#include <stdlib.h>
#include <time.h>  //시간계산을 위한 헤더


//트리 
typedef struct Node {
    int data; //정수형의 데이터 키값 
    struct Node * children[3]; // Node 자료형을 가지는(나 자신) 길이 3의 포인터 배열선언(3명의 자식의 주소를 저장할 것임) 
} Node; // 트리노드의 구조체 선언 


Node* createNode(int data) { //노드를 생성하는 함수, 인자로 정수형의 data를 받고 반환은 그 노드의 주소값임 
	int i; // 반복문읠 위한 i 
    Node* newNode = (Node*)malloc(sizeof(Node)); // 동적할당을 통해 Node 사이즈만큼 동적할당하여 newNode 생성 
    newNode->data = data; // newNode 포인터 변수가 가리키는 변수의 data에 인자로 받은 데이터를 넣는다. 
    for (i = 0; i < 3; i++) { // 3번 반복함(0, 1, 2) 
        newNode->children[i] = NULL;  // newNode 포인터변수가 가리키는 변수의 배열값을 NULL로 초기화(자식을 가리키는 포인터배열 주소 초기화) 
    }
    return newNode; // 다만들고 newNode 포인터변수가 저장하고 있던 주소 반환함 
}

//큐 
typedef struct _node{
	Node* data; // Node의 주소가 데이터임 
	struct _node * next;  
} Node2; // 

typedef struct _1Queue
{
	Node2 * front; 
	Node2 * rear; 
 } Queue; // 자료구조 Queue 


void QueueInit(Queue *pq) //큐 초기화 함수 
{
	pq->front = NULL; //front를 NULL로 
	pq->rear=NULL; //rear를 NULL로 
}

int QIsEmpty(Queue *pq) //큐가 비어있는지 확인하는 함수 
{
	if(pq -> front == NULL){ // front에 NULL이 저장되어 있다면 
		return 1; // 큐가 비어있는 것이기에 1을 반환 
	}
	else{
		return 0; //아니면 큐가 차있는것이기에 0을 반환 
	}
}

void Enqueue(Queue * pq, Node* data) //큐아 데이터 삽입하는 함수 
{
	Node2 * newNode = (Node2*)malloc(sizeof(Node2)); // 동적할당을 통해 Node2 사이즈만큼 동적할당하여 newNode 생성 
	newNode->next = NULL; //newNode의 next를 NULL로 초기화  
	newNode->data = data; //newNode의 데이터에 인자로 받은 data저장(주소값임) 
	
	if(QIsEmpty(pq)) // 첫번째 노드의 삽입이라면 
	{
		pq->front = newNode; // font가 새 노드를 가리키게 하고 
		pq->rear = newNode; // rear도 새 노드를 가리키게 한다 
	}
	else // 첫번쨰 노드삽입이 아니라면 
	{
		pq->rear->next = newNode; // 마지막 노드가 새 노드를 가리키게하고 
		pq->rear = newNode; // rear가 새노드를 가리키게한다. 
	}
}

Node *  Dequeue(Queue * pq) //데이터 삭제함수 
{
	Node2 * delNode; 
	Node * retData; 
	if(QIsEmpty(pq)) // 큐가 비어있다면 
	{
		printf("Queue Memory Error!"); // 큐메모리에러 출력 
		exit(-1);
	}
	
	delNode = pq -> front; // 삭제할 노드의 주소값을 저장 
	retData = delNode->data; // 삭제할 노드가 지닌 값을 저장 
	pq->front = pq->front ->next; // 삭제할 노드의 다음 노드를 front가 가리킨다. 
	
	free(delNode); //free함수로 delNode 메모리 해제 
	return retData; 
}

//트리 출력하는 함수(장식용) 
void printTree(Node* root, int depth) {
    if (root == NULL) return;

    int i;
    for (i = 0; i < depth; i++) {
        printf("\t");
    }
    printf("%d\n", root->data);

    for (i = 0; i < 3; i++) {
        printTree(root->children[i], depth + 1);
    }
}

int findDepth(Node * root, int depth){//인자로 root의 주소와  depth를 받는다. 
	int i; // 반복문을 위한 i 
	if (root==NULL){ //cNode가 NULL이면 현재 깊이를 반환 
		return depth;
	}
	int maxDepth = depth; // 현재받은 변수를 우선 maxDepth로 설정함 점차 증가 
    for (i = 0; i < 3; i++) { // 3번반복함(자식이 최대 3이기 때문임) 
        int childDepth = findDepth(root->children[i], depth + 1); // 재귀호출을 하여 한칸씩 내려감, 그자식의 주소들이  다시 인자인 root가 된다. 
        if (childDepth > maxDepth) { // 만약 반환된 childDepth가 maxDepth보다 크다면 
            maxDepth = childDepth; // maxDepth 업데이트 
        }
    }

    return maxDepth; // 계속 반환하다가 마지막에는 가장크게 업데이트된 Depth가 반환됨 
	
	
}
// 트리에 노드 삽입 함수
Node* insertNode(Node* root, int data, int depth) { //root의 주소, 데이터, 깊이를 인자로 받음 
    Queue q; // 큐 자료형의 변수 q선언 
	QueueInit(&q); // q초기화 
	root = createNode(data); // 데이터를 값으로 가지는 root트리 노드 생성 
	Enqueue(&q, root); // 큐에 root 넣는다 
	int temp_rand; // 랜덤값을 위한 변수임 
	temp_rand=7; //랜덤값을 7로 초기화, 만약 1,2,3,4,5,6에 해당하지 않는경우 자식이 없어짐 
	int count=0; // count변수는 0임 
	while(!QIsEmpty(&q)){ // q가 완전히 비어있을때까지 반복 
		Node* current=Dequeue(&q); // q에서 값을 꺼낸다. 그것을 current 포인터 변수에 저장함 (선입선출) 

	
		temp_rand = rand() % 7;// case 0, 1, 2, 3, 4, 5, 6 중 한개가 랜덤값으로 나온다. -> 자식이 있을경우의 모든 경우의 수는 7가지임 
			 
			switch (temp_rand){
				case 0: // 랜덤값이 0인경우 자식이 chldren[0] 1개 
					data+=1; //데이터 1증가 
					current->children[0]=createNode(data); // 데이터를 가지고 트리노드 하나  만들어서 그 주소를 current가 가리키는 변수의 children[0]에 저장 
					Enqueue(&q, current->children[0]); // 그 children[0]에 담긴 주소를 q에 넣는다
					break;//case0에 해당하면 switch문 종료 
				case 1: //랜덤값이 1인경우 자식이 children[1] 1개 
					data+=1; //데이터 1증가
					current->children[1]=createNode(data); // 데이터를 가지고 트리노드 하나  만들어서 그 주소를 current가 가리키는 변수의 children[1]에 저장 
					Enqueue(&q, current->children[1]);// 그 children[1]에 담긴 주소를 q에 넣는다
					break;//case1에 해당하면 switch문 종료
				case 2: //랜덤값이 2인경우 자식이 children[2] 1개 
					data+=1;//데이터 1증가
					current->children[2]=createNode(data);// 데이터를 가지고 트리노드 하나  만들어서 그 주소를 current가 가리키는 변수의 children[2]에 저장 
					Enqueue(&q, current->children[2]);// 그 children[2]에 담긴 주소를 q에 넣는다
					break;//case2에 해당하면 switch문 종료
				case 3: //랜덤값이 3인경우 자식이 children[0] children[1] 2개 
					data+=1;//데이터 1증가
					current->children[0]=createNode(data); // 데이터를 가지고 트리노드 하나  만들어서 그 주소를 current가 가리키는 변수의 children[0]에 저장
					data+=1;//데이터 1증가
					current->children[1]=createNode(data);// 데이터를 가지고 트리노드 하나  만들어서 그 주소를 current가 가리키는 변수의 children[1]에 저장
					Enqueue(&q, current->children[0]); // 그 children[0]에 담긴 주소를 q에 넣는다
					Enqueue(&q, current->children[1]);// 그 children[1]에 담긴 주소를 q에 넣는다
					break;//case3에 해당하면 switch문 종료
				case 4: //랜덤값이 4인경우 자식이 children[0] children[2] 2개 
					data+=1;//데이터 1증가
					current->children[0]=createNode(data);// 데이터를 가지고 트리노드 하나  만들어서 그 주소를 current가 가리키는 변수의 children[0]에 저장
					data+=1;//데이터 1증가
					current->children[2]=createNode(data);// 데이터를 가지고 트리노드 하나  만들어서 그 주소를 current가 가리키는 변수의 children[2]에 저장
					Enqueue(&q, current->children[0]); // 그 children[0]에 담긴 주소를 q에 넣는다
					Enqueue(&q, current->children[2]); // 그 children[2]에 담긴 주소를 q에 넣는다
					break;//case4에 해당하면 switch문 종료
				case 5: //랜덤값이 5인경우 자식이 children[1] children[2] 2개 
					data+=1;//데이터 1증가
					current->children[1]=createNode(data);// 데이터를 가지고 트리노드 하나  만들어서 그 주소를 current가 가리키는 변수의 children[1]에 저장
					data+=1;//데이터 1증가
					current->children[2]=createNode(data);// 데이터를 가지고 트리노드 하나  만들어서 그 주소를 current가 가리키는 변수의 children[2]에 저장
					Enqueue(&q, current->children[1]);// 그 children[1]에 담긴 주소를 q에 넣는다
					Enqueue(&q, current->children[2]);// 그 children[2]에 담긴 주소를 q에 넣는다
					break;//case5에 해당하면 switch문 종료
					
				case 6: //랜덤값이 6인경우 자식이 children[0] children[1] children[2] 3개 
					data+=1;//데이터 1증가
					current->children[0]=createNode(data);// 데이터를 가지고 트리노드 하나  만들어서 그 주소를 current가 가리키는 변수의 children[0]에 저장
					data+=1;//데이터 1증가
					current->children[1]=createNode(data);// 데이터를 가지고 트리노드 하나  만들어서 그 주소를 current가 가리키는 변수의 children[1]에 저장
					data+=1;//데이터 1증가
					current->children[2]=createNode(data);// 데이터를 가지고 트리노드 하나  만들어서 그 주소를 current가 가리키는 변수의 children[2]에 저장
					Enqueue(&q, current->children[0]);// 그 children[0]에 담긴 주소를 q에 넣는다
					Enqueue(&q, current->children[1]);// 그 children[1]에 담긴 주소를 q에 넣는다
					Enqueue(&q, current->children[2]);// 그 children[2]에 담긴 주소를 q에 넣는다
					break;//case6에 해당하면 switch문 종료
					
			}
			
		//Depth를 계산하여 만약 depth보다 큰 시점이 오면 방금 만든 자식들은 모두 NULL로 초기화(제거한다) 
		if (findDepth(root, 0)>depth){
			current->children[0]=NULL;
			current->children[1]=NULL;
			current->children[2]=NULL;
			
			break; // depth 조건 만족했으므로 while문에서 벗어남 
			
		}
		
	}
	

	 
        
    return root; // 함수의 끝은 root의 주소 반환 
	
	
}

int dfs_count=0; // 출력형태를 위한 변수 

//dfs함수(재귀함수로 트리를 계속 타고 가게끔 코딩) 
void dfs(Node * root){ //root를 인자로 받는다 
	if(root==NULL){ //root가 NULL이면 더이상 안내려가면 return 
		return;
	}
	if(dfs_count==0){ //출력형태 조정를 위한 if문 첫출력은 화살표 없이 출력 
		printf("%d",root->data);
		dfs_count+=1;	
	}
	else{ //그다음부터는  화살표추가해서 출력 
		printf("->%d",root->data);
	}
	dfs(root->children[0]); // 재귀함수로 children[0]의 자식노드를 타고 간다. 
	dfs(root->children[1]); // 재귀함수로 children[1]의 자식노드를 타고 간다. 
	dfs(root->children[2]); // 재귀함수로 children[2]의 자식노드를 타고 간다. 
}


//bfs함수(큐에 값이 사라지기 전까지 계속 넣고 출력한다) 
void bfs(Node * root){ //root를 인자로 받음 
	Queue q; // 큐생성 
	QueueInit(&q); //큐 초기화 
	int i; //반복문을 위한 i 
	int count=0; //출력형태를 위한 변수 
	Enqueue(&q, root); //큐에 루트 삽입 
	
	
	while(!QIsEmpty(&q)){ //큐에 값이 없을때까지 while문 반복 
		root=Dequeue(&q); // 큐에서 값 빼서 root에 저장 
		if(count==0){ //첫출력은 값만 출력 
			printf("%d",root->data);
			count+=1;
		}
		else{ //두번쨰 출력부터는 화살표도 출력 
			printf("->%d",root->data);
		}
		for(i=0; i<3; i++){ // 자식이 최대 3개이므로 3번 반복 
			if(root->children[i]!=NULL){ //만약 자식이 NULL이 아니면 
				Enqueue(&q, root->children[i]); // 그 자식을 큐에 삽입함 
			}
		}	
	}
	
}


int main() {
    int depth; //depth 저장 위한 정수형 변수 
    printf("Input:");
    scanf("%d", &depth); // depth입력받음 
    
    
    double dfs_time=0; //dfs 함수의 수행시간 저장변수 
	double bfs_time=0;//bfs 함수의 수행시간 저장변수
	
    Node* root = NULL; //root 포인터 변수 선언 
    
	srand((unsigned int)time(NULL)); // 랜덤한 변수를 위한 선언 
	root = insertNode(root,0, depth); // root에 노드 생성해서 그 주소 저장 


    printf("생성된 트리: \n");
    printTree(root, 0);
    printf("\n");
    
    
    printf("Output:");
    printf("\n");
    printf("DFS: ");
	clock_t start1 = clock(); //타이머 시작
	dfs(root); // dfs 호출 
	clock_t end1 = clock(); // 타이머 종료
	dfs_time=(double)(end1 - start1); // 타이머 종료시간(ms) - 타이머 시작시간(ms)
    printf(" / %lf msec", dfs_time);
	printf("\n");
    printf("BFS: ");
    clock_t start2 = clock(); //타이머 시작
	bfs(root); //bfs 호출 
	clock_t end2 = clock(); // 타이머 종료
	bfs_time=(double)(end2 - start2); // 타이머 종료시간(ms) - 타이머 시작시간(ms)
	printf(" / %lf msec", bfs_time);
    printf("\n");


    return 0; //main함수 종료 
}



