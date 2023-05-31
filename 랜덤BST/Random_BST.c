#include <stdio.h>
#include <stdlib.h>
#include <time.h> //완전히 랜덤한값, 시간계산을 위한 헤더

typedef int BSTData; //실제 value 데이터도 구조체로 선언하였다. 

//이진트리의 노드를 표현한 구조체 
typedef struct _bTreeNode{
	BSTData data; // 실제 value 데이터 
	struct _bTreeNode * left; //bTreeNode의 자료형을 가지는 변수를 가리키는 포인터 변수 left(왼쪽 자식노드를 가리킴) 
	struct _bTreeNode * right;  //bTreeNode의 자료형을 가지는 변수를 가리키는 포인터 변수 right(오른쪽 자식노드를 가리킴)
	
} BTreeNode; // 구조체에 BTreeNode라는 이름 부여 

//노드에 저장된 데이터 반환 
BSTData GetData(BTreeNode * bt){ //BSTData형으로 포인터변수 bt를 받아서 그 bt의 데이터를 반환함
	return bt->data;
}

//이진트리 노드를 생성하여 그 주소 값을 반환함
BTreeNode * MakeBTreeNode(void){ 
	BTreeNode * nd = (BTreeNode*)malloc(sizeof(BTreeNode)); //BTreeNode의 사이즈만큼 메모리를 할당함, BTreeNode형 포인터로 형변환 
	nd->left = NULL; //nd변수의 left를 NULL로 초기화(left는 이제 아무것도 안가리킴) 
	nd->right = NULL; //nd변수의 right를 NULL로 초기화(right는 이제 아무것도 안가리킴) 
	return nd; //malloc으로 할당한 메모리의 시작 주소값 반환 
}

//노드에 데이터 저장, data로 전달된 값을 저장 
void SetData(BTreeNode * bt, BSTData data){ //data와 포인터변수 bt를 인자로 받아서 bt가 가리키는 노드의 data값을 인자로 받은 data로 저장  
	bt -> data = data;
}

//왼쪽 서브트리의 주소값 반환 
BTreeNode * GetLeftSubTree(BTreeNode * bt){ // 포인터변수 bt를 인자로 받아서 bt가 가리키는 노드의 왼쪽서브트리의 주소값을 반환함 
	return bt->left;
}

//오른쪽 서브트리의 주소값 반환 
BTreeNode * GetRightSubTree(BTreeNode * bt){// 포인터변수 bt를 인자로 받아서 bt가 가리키는 노드의 오른쪽서브트리의 주소값을 반환함
	return bt->right;
}

//왼쪽 서브트리를 연결함 
void MakeLeftSubTree(BTreeNode * main, BTreeNode *sub){ //왼쪽 서브트리를 연결하는 함수, 포인터변수 main과 sub를인자로 받는다. 
	if(main -> left != NULL){ //만약 main이 가리키는 노드의 left노드가 NULL이 아니라면(존재한다면) 
		free(main->left); //왼쪽에 해당하는 트리를 삭제함 
	}
	main -> left = sub; //왼쪽에 해당하는 트리에 sub트리붙임(sub트리의 주소값을 left노드를 가리키는 left 포인터변수에 저장) 
}

//오른쪽 서브트리를 연결함 
void MakeRightSubTree(BTreeNode * main, BTreeNode *sub){ //오른쪽 서브트리를 연결하는 함수, 포인터변수 main과 sub를인자로 받는다. 
	if(main -> right != NULL){ //만약 main이 가리키는 노드의 right노드가 NULL이 아니라면(존재한다면) 
		free(main->right); //오른쪽에 해당하는 트리를 삭제함 
	}
	main -> right = sub; //오른쪽에 해당하는 트리에 sub트리붙임(sub트리의 주소값을 right노드를 가리키는 right 포인터변수에 저장) 
}

//BST의 생성 및 초기화 
void BSTMakeAndInit(BTreeNode ** pRoot){ //이중포인터 변수 pRoot로 인자를 받음(bstRoot라는 포인터변수의 주소값) 
	*pRoot = NULL; // 루트노드를 가리키는 bstRoot포인터변수를 초기화 
}

//노드의 생성과정을 포함하여 BST를 대상으로 데이터를 저장 
void BSTInsert(BTreeNode ** pRoot, BSTData data){ //이중포인터 변수 PRoot를 인자로 받음(bstRoot라는 포인터변수의 주소값), 저장할 data도 인자로 받음 
	BTreeNode * pNode = NULL; //부모노드를 가리기는 포인터변수 pNode 초기화 
	BTreeNode * cNode = *pRoot; //현재노드를 가리키는 포인터 변수 CNode에 PRoot가 한번 가리키는 값(bstRoot포인터변수의 주소를 저장), bstRoot는 root노드를 가리킴 
	BTreeNode * nNode = NULL; // 새로운 노드를 가리키는 nNode 초기화 
	
	//새로운 노드가 추가될 위치를 찾음(pNode를 기준으로 추가할 예정) 
	while(cNode != NULL){ //CNode가 NULL이 아닌 경우에 계속 반복 
		if(data == GetData(cNode)){ // 현재노드의 value와 인자로 전달받은 데이터가 같으면 그대로 함수 종료(키의 중복을 허용하지 않는다.) 
			return;
		}
		pNode = cNode; //PNode변수에 CNode값 저장(현재노드가 부모노드가됨)
		
		 
		if(GetData(cNode) > data){ //만약 cNode의 value가 데이터보다 크다면 
			cNode = GetLeftSubTree(cNode); // cNode의 왼쪽 서브트리의 주소값을 cNode에 저장 
		}
		else{ //만약 value가 데이터보다 작거나 같다면 
			cNode = GetRightSubTree(cNode); //cNode의 오른쪽 서브트리의 주소값을 cNode에 저장 
		}
	}
	nNode = MakeBTreeNode(); //이진트리노드를 생성하여 그 주소값을 nNode에 저장 
	SetData(nNode, data); //nNode에 데이터 저장 
	
	//이제 nNode를 BST트리의 형식대로 원래의 노드에 연결해야함 
	
	if(pNode != NULL){ //만약 pNode가 NULL이 아니라면(새 노드가 루트노드가 아니라면, 처음추가하는 노드 아니라면) 
		if(data < GetData(pNode)){ //인자로받은 데이터보다 pNode의 데이터가 크다면 
			MakeLeftSubTree(pNode, nNode); //pNode의 왼쪽에 nNode를 붙임(bst의 성질, 부모노드는 왼쪽자식노드보다 크다) 
		}
		else{//만약 인자로받은 데이터보다 pNode의 데이터가 작거나 같다면 
			MakeRightSubTree(pNode, nNode); //pNode의 오른쪽에 nNode를 붙임(bst의 성질, 부모노드는 오른쪽자식노드보다 작다) 
		}
	}
	else{//새 노드가 루트노드라면(처음추가하는) 
		*pRoot = nNode; //pRoot포인터변수에 nNode주소 저장(루트가됨) 
	}
}

//루트에서부터 깊이를 찾는 findDepth함수 
int findDepth(BTreeNode * pRoot, int depth){//인자로  bstRoot를 가리키는 주소와, depth를 받는다. 
	BTreeNode * cNode = pRoot; // cNode포인터변수에 bstRoot가리키는 주소 저장 
	if (cNode==NULL){ //cNode가 NULL이면 현재 깊이를 반환 
		return depth;
	}
	int leftDepth =	findDepth(cNode->left, depth+1); //재귀호출로 cNode의 왼쪽 트리를 계속해서 호출해나간다, 깊이도 1씩 증가, 호출하다가 cNode의 값이 NULL이 되면 현재 깊이를 반환함 
	int rightDepth = findDepth(cNode->right, depth+1); //재귀호출로 cNode의 오른쪽 트리를 계속해서 호출해나간다, 깊이도 1씩 증가, 호출하다가 cNode의 값이 NULL이 되면 현재 깊이를 반환함
	
	//왼쪽서브트리 깊이와 오른쪽 서브트리 깊이르 비교하여 더 큰값을 반환 
	if (leftDepth > rightDepth){ 
		return leftDepth;
	}
	else{
		return rightDepth;
	}
	
	
}

// 트리구조가 만들어졌는지 확인하기위해 중간에 테스트 용도로 printTree함수를 작성하였다. 왼쪽부터 공백을 레벨로 하여 출력
// 실제 과제출력에는 안쓰임 
void printTree(BTreeNode* root, int level) {
    if (root == NULL) {
        return;
    }
    
    printTree(root->right, level + 1); // 오른쪽 자식 노드 출력
    int i;
    for (i = 0; i < level; i++) {
        printf("    "); // 레벨에 맞게 공백 출력
    }
    printf("%d\n", root->data); // 현재 노드 값 출력
    printTree(root->left, level + 1); // 왼쪽 자식 노드 출력
}


int main(){
	int k; //100번 반복용도의 변수 
	double alltime[100]={0}; //alltime의 자료형은 double이고 트리를 만드는부분에 소요되는 시간을 100회 마다 저장해서 최대와 최소를 찾을것이기 때문에 리스트로 작성 
	int alldepth[100]={0}; //alltime의 자료형은 int이고 트리는 매번 다르게 만들어지고 그 깊이도 달라진다. 100회 마다 저장해서 최대와 최소를 찾을것이기 때문에 리스트로 작성
	for(k=0; k<100; k++){ //100회 반복 
		clock_t start = clock(); //timer 시작
		
		BTreeNode * bstRoot; // bstRoot는 BST의 루트노드를 가리키는 포인터 변수 
		BSTMakeAndInit(&bstRoot); // BST의 생성 및 초기화함수 호출, 포인터변수의 주소값을 인자로 전달 
		
		int i,j; //랜덤값 반복에 사용될 변수 2개 
		int random=0; // random변수 초기화 
		int depth=0; // 깊이 변수 초기화 
		double treetime=0; // 트리만드는데 걸리는  시간 변수 초기화 
		srand((unsigned int)time(NULL)); // 시간으로 시드값을 계혹 바꾸어줌, 이렇게 하면 완전히 랜덤한 값으로 되어 값이 계속 바뀐다.
		int temp[1000]; //중복값 확인을 위한 배열
		for(i=0; i<=999; i++){ // 1000번 반복 
			random=rand()%1000; // 0~999 랜덤 변수 생성 
			
			for (j=0; j<=i; j++){ //중복값 검사 
				if(random==temp[j]){ //만약 지금생성한 random값이 temp안에 있으면 i를 한개 줄여서 돌아감, 그 후 random값 다시 생성 
					i--;
				}
			}
			
			
			temp[i]=random; // 만약 중복검사를 통과했다면 temp 배열에 저장 
			BSTInsert(&bstRoot, random); // 그후 BST에 삽입
			
		}
		clock_t end = clock(); //bst트리를 모두 만들었으므로 타이머 종료 
		treetime=(double)(end - start); // 타이머 종료시간(ms) - 타이머 시작시간(ms)
		printf("소요 시간: %lf ms\n", treetime); //소요시간 출력(단위 ms) 
		alltime[k]=treetime; // alltime배열에 소요시간 저장 
		depth=findDepth(bstRoot, 0); // depth계산하는 findDepth 함수 호출 
		alldepth[k]=depth; // alldepth배열에 찾은 depth 저장 
		printf("깊이: %d\n", depth); // 깊이 출력 
	}
	
	double all_time=0; //실수형의 all_time 변수선언 
	double all_depth=0; //실수형의 all_depth 변수 선언 
	double timemax=alltime[0]; //소요시간의 최대를 계산하기 위한 초기값 
	double timemin=alltime[0]; //소요시간의 최소를 계산하기 위한 초기값 
	int depthmax=alldepth[0];//깊이의 최대를 계산하기 위한 초기값 
	int depthmin=alldepth[0];//깊이의 최소를 계산하기 위한 초기값 
	int i;
	for (i=0; i<100; i++){ //100번 반복 
		all_time+=alltime[i]; //all_time에 계속 더해나감(나중에 평균 계산용도) 
		
		if(alltime[i]>timemax){ //계속 소요시간의 최대값을 개선해나감 
			timemax=alltime[i];
		}
		if(alltime[i]<timemin){ //계속 소요시간의 최소값을 개선해 나감 
			timemin=alltime[i];
		}
		
		all_depth+=alldepth[i]; //all_depth에 계속 더해나감(나중에 평균 계산용도) 
		
		if(alldepth[i]>depthmax){
			depthmax=alldepth[i]; //계속 깊이의 최대값을 개선해나감 
		}
		if(alldepth[i]<depthmin){
			depthmin=alldepth[i]; //계속 깊이의 최소값을 개선해나감 
		}

		
	}
	double avgtime=(all_time/100); //100번의 평균 시간 계산 
	double avgdepth = (all_depth/100); //100번의 평균 깊이 계산 
	printf("Time - AVG: %lfms Max: %lfms Min: %lfms\n", avgtime, timemax, timemin); //평균시간, 최대시간, 최소시간 출력 
	printf("Depth - AVG: %lf Max: %d Min: %d", avgdepth, depthmax, depthmin); //평균깊이, 최대깊이, 최소깊이 출력 
	
	return 0;//main함수 종료 
}
 
	
	
