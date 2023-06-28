#include <stdio.h>
#include <stdlib.h>
#include <time.h>  //�ð������ ���� ���


//Ʈ�� 
typedef struct Node {
    int data; //�������� ������ Ű�� 
    struct Node * children[3]; // Node �ڷ����� ������(�� �ڽ�) ���� 3�� ������ �迭����(3���� �ڽ��� �ּҸ� ������ ����) 
} Node; // Ʈ������� ����ü ���� 


Node* createNode(int data) { //��带 �����ϴ� �Լ�, ���ڷ� �������� data�� �ް� ��ȯ�� �� ����� �ּҰ��� 
	int i; // �ݺ����� ���� i 
    Node* newNode = (Node*)malloc(sizeof(Node)); // �����Ҵ��� ���� Node �����ŭ �����Ҵ��Ͽ� newNode ���� 
    newNode->data = data; // newNode ������ ������ ����Ű�� ������ data�� ���ڷ� ���� �����͸� �ִ´�. 
    for (i = 0; i < 3; i++) { // 3�� �ݺ���(0, 1, 2) 
        newNode->children[i] = NULL;  // newNode �����ͺ����� ����Ű�� ������ �迭���� NULL�� �ʱ�ȭ(�ڽ��� ����Ű�� �����͹迭 �ּ� �ʱ�ȭ) 
    }
    return newNode; // �ٸ���� newNode �����ͺ����� �����ϰ� �ִ� �ּ� ��ȯ�� 
}

//ť 
typedef struct _node{
	Node* data; // Node�� �ּҰ� �������� 
	struct _node * next;  
} Node2; // 

typedef struct _1Queue
{
	Node2 * front; 
	Node2 * rear; 
 } Queue; // �ڷᱸ�� Queue 


void QueueInit(Queue *pq) //ť �ʱ�ȭ �Լ� 
{
	pq->front = NULL; //front�� NULL�� 
	pq->rear=NULL; //rear�� NULL�� 
}

int QIsEmpty(Queue *pq) //ť�� ����ִ��� Ȯ���ϴ� �Լ� 
{
	if(pq -> front == NULL){ // front�� NULL�� ����Ǿ� �ִٸ� 
		return 1; // ť�� ����ִ� ���̱⿡ 1�� ��ȯ 
	}
	else{
		return 0; //�ƴϸ� ť�� ���ִ°��̱⿡ 0�� ��ȯ 
	}
}

void Enqueue(Queue * pq, Node* data) //ť�� ������ �����ϴ� �Լ� 
{
	Node2 * newNode = (Node2*)malloc(sizeof(Node2)); // �����Ҵ��� ���� Node2 �����ŭ �����Ҵ��Ͽ� newNode ���� 
	newNode->next = NULL; //newNode�� next�� NULL�� �ʱ�ȭ  
	newNode->data = data; //newNode�� �����Ϳ� ���ڷ� ���� data����(�ּҰ���) 
	
	if(QIsEmpty(pq)) // ù��° ����� �����̶�� 
	{
		pq->front = newNode; // font�� �� ��带 ����Ű�� �ϰ� 
		pq->rear = newNode; // rear�� �� ��带 ����Ű�� �Ѵ� 
	}
	else // ù���� �������� �ƴ϶�� 
	{
		pq->rear->next = newNode; // ������ ��尡 �� ��带 ����Ű���ϰ� 
		pq->rear = newNode; // rear�� ����带 ����Ű���Ѵ�. 
	}
}

Node *  Dequeue(Queue * pq) //������ �����Լ� 
{
	Node2 * delNode; 
	Node * retData; 
	if(QIsEmpty(pq)) // ť�� ����ִٸ� 
	{
		printf("Queue Memory Error!"); // ť�޸𸮿��� ��� 
		exit(-1);
	}
	
	delNode = pq -> front; // ������ ����� �ּҰ��� ���� 
	retData = delNode->data; // ������ ��尡 ���� ���� ���� 
	pq->front = pq->front ->next; // ������ ����� ���� ��带 front�� ����Ų��. 
	
	free(delNode); //free�Լ��� delNode �޸� ���� 
	return retData; 
}

//Ʈ�� ����ϴ� �Լ�(��Ŀ�) 
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

int findDepth(Node * root, int depth){//���ڷ� root�� �ּҿ�  depth�� �޴´�. 
	int i; // �ݺ����� ���� i 
	if (root==NULL){ //cNode�� NULL�̸� ���� ���̸� ��ȯ 
		return depth;
	}
	int maxDepth = depth; // ������� ������ �켱 maxDepth�� ������ ���� ���� 
    for (i = 0; i < 3; i++) { // 3���ݺ���(�ڽ��� �ִ� 3�̱� ������) 
        int childDepth = findDepth(root->children[i], depth + 1); // ���ȣ���� �Ͽ� ��ĭ�� ������, ���ڽ��� �ּҵ���  �ٽ� ������ root�� �ȴ�. 
        if (childDepth > maxDepth) { // ���� ��ȯ�� childDepth�� maxDepth���� ũ�ٸ� 
            maxDepth = childDepth; // maxDepth ������Ʈ 
        }
    }

    return maxDepth; // ��� ��ȯ�ϴٰ� ���������� ����ũ�� ������Ʈ�� Depth�� ��ȯ�� 
	
	
}
// Ʈ���� ��� ���� �Լ�
Node* insertNode(Node* root, int data, int depth) { //root�� �ּ�, ������, ���̸� ���ڷ� ���� 
    Queue q; // ť �ڷ����� ���� q���� 
	QueueInit(&q); // q�ʱ�ȭ 
	root = createNode(data); // �����͸� ������ ������ rootƮ�� ��� ���� 
	Enqueue(&q, root); // ť�� root �ִ´� 
	int temp_rand; // �������� ���� ������ 
	temp_rand=7; //�������� 7�� �ʱ�ȭ, ���� 1,2,3,4,5,6�� �ش����� �ʴ°�� �ڽ��� ������ 
	int count=0; // count������ 0�� 
	while(!QIsEmpty(&q)){ // q�� ������ ������������� �ݺ� 
		Node* current=Dequeue(&q); // q���� ���� ������. �װ��� current ������ ������ ������ (���Լ���) 

	
		temp_rand = rand() % 7;// case 0, 1, 2, 3, 4, 5, 6 �� �Ѱ��� ���������� ���´�. -> �ڽ��� ��������� ��� ����� ���� 7������ 
			 
			switch (temp_rand){
				case 0: // �������� 0�ΰ�� �ڽ��� chldren[0] 1�� 
					data+=1; //������ 1���� 
					current->children[0]=createNode(data); // �����͸� ������ Ʈ����� �ϳ�  ���� �� �ּҸ� current�� ����Ű�� ������ children[0]�� ���� 
					Enqueue(&q, current->children[0]); // �� children[0]�� ��� �ּҸ� q�� �ִ´�
					break;//case0�� �ش��ϸ� switch�� ���� 
				case 1: //�������� 1�ΰ�� �ڽ��� children[1] 1�� 
					data+=1; //������ 1����
					current->children[1]=createNode(data); // �����͸� ������ Ʈ����� �ϳ�  ���� �� �ּҸ� current�� ����Ű�� ������ children[1]�� ���� 
					Enqueue(&q, current->children[1]);// �� children[1]�� ��� �ּҸ� q�� �ִ´�
					break;//case1�� �ش��ϸ� switch�� ����
				case 2: //�������� 2�ΰ�� �ڽ��� children[2] 1�� 
					data+=1;//������ 1����
					current->children[2]=createNode(data);// �����͸� ������ Ʈ����� �ϳ�  ���� �� �ּҸ� current�� ����Ű�� ������ children[2]�� ���� 
					Enqueue(&q, current->children[2]);// �� children[2]�� ��� �ּҸ� q�� �ִ´�
					break;//case2�� �ش��ϸ� switch�� ����
				case 3: //�������� 3�ΰ�� �ڽ��� children[0] children[1] 2�� 
					data+=1;//������ 1����
					current->children[0]=createNode(data); // �����͸� ������ Ʈ����� �ϳ�  ���� �� �ּҸ� current�� ����Ű�� ������ children[0]�� ����
					data+=1;//������ 1����
					current->children[1]=createNode(data);// �����͸� ������ Ʈ����� �ϳ�  ���� �� �ּҸ� current�� ����Ű�� ������ children[1]�� ����
					Enqueue(&q, current->children[0]); // �� children[0]�� ��� �ּҸ� q�� �ִ´�
					Enqueue(&q, current->children[1]);// �� children[1]�� ��� �ּҸ� q�� �ִ´�
					break;//case3�� �ش��ϸ� switch�� ����
				case 4: //�������� 4�ΰ�� �ڽ��� children[0] children[2] 2�� 
					data+=1;//������ 1����
					current->children[0]=createNode(data);// �����͸� ������ Ʈ����� �ϳ�  ���� �� �ּҸ� current�� ����Ű�� ������ children[0]�� ����
					data+=1;//������ 1����
					current->children[2]=createNode(data);// �����͸� ������ Ʈ����� �ϳ�  ���� �� �ּҸ� current�� ����Ű�� ������ children[2]�� ����
					Enqueue(&q, current->children[0]); // �� children[0]�� ��� �ּҸ� q�� �ִ´�
					Enqueue(&q, current->children[2]); // �� children[2]�� ��� �ּҸ� q�� �ִ´�
					break;//case4�� �ش��ϸ� switch�� ����
				case 5: //�������� 5�ΰ�� �ڽ��� children[1] children[2] 2�� 
					data+=1;//������ 1����
					current->children[1]=createNode(data);// �����͸� ������ Ʈ����� �ϳ�  ���� �� �ּҸ� current�� ����Ű�� ������ children[1]�� ����
					data+=1;//������ 1����
					current->children[2]=createNode(data);// �����͸� ������ Ʈ����� �ϳ�  ���� �� �ּҸ� current�� ����Ű�� ������ children[2]�� ����
					Enqueue(&q, current->children[1]);// �� children[1]�� ��� �ּҸ� q�� �ִ´�
					Enqueue(&q, current->children[2]);// �� children[2]�� ��� �ּҸ� q�� �ִ´�
					break;//case5�� �ش��ϸ� switch�� ����
					
				case 6: //�������� 6�ΰ�� �ڽ��� children[0] children[1] children[2] 3�� 
					data+=1;//������ 1����
					current->children[0]=createNode(data);// �����͸� ������ Ʈ����� �ϳ�  ���� �� �ּҸ� current�� ����Ű�� ������ children[0]�� ����
					data+=1;//������ 1����
					current->children[1]=createNode(data);// �����͸� ������ Ʈ����� �ϳ�  ���� �� �ּҸ� current�� ����Ű�� ������ children[1]�� ����
					data+=1;//������ 1����
					current->children[2]=createNode(data);// �����͸� ������ Ʈ����� �ϳ�  ���� �� �ּҸ� current�� ����Ű�� ������ children[2]�� ����
					Enqueue(&q, current->children[0]);// �� children[0]�� ��� �ּҸ� q�� �ִ´�
					Enqueue(&q, current->children[1]);// �� children[1]�� ��� �ּҸ� q�� �ִ´�
					Enqueue(&q, current->children[2]);// �� children[2]�� ��� �ּҸ� q�� �ִ´�
					break;//case6�� �ش��ϸ� switch�� ����
					
			}
			
		//Depth�� ����Ͽ� ���� depth���� ū ������ ���� ��� ���� �ڽĵ��� ��� NULL�� �ʱ�ȭ(�����Ѵ�) 
		if (findDepth(root, 0)>depth){
			current->children[0]=NULL;
			current->children[1]=NULL;
			current->children[2]=NULL;
			
			break; // depth ���� ���������Ƿ� while������ ��� 
			
		}
		
	}
	

	 
        
    return root; // �Լ��� ���� root�� �ּ� ��ȯ 
	
	
}

int dfs_count=0; // ������¸� ���� ���� 

//dfs�Լ�(����Լ��� Ʈ���� ��� Ÿ�� ���Բ� �ڵ�) 
void dfs(Node * root){ //root�� ���ڷ� �޴´� 
	if(root==NULL){ //root�� NULL�̸� ���̻� �ȳ������� return 
		return;
	}
	if(dfs_count==0){ //������� ������ ���� if�� ù����� ȭ��ǥ ���� ��� 
		printf("%d",root->data);
		dfs_count+=1;	
	}
	else{ //�״������ʹ�  ȭ��ǥ�߰��ؼ� ��� 
		printf("->%d",root->data);
	}
	dfs(root->children[0]); // ����Լ��� children[0]�� �ڽĳ�带 Ÿ�� ����. 
	dfs(root->children[1]); // ����Լ��� children[1]�� �ڽĳ�带 Ÿ�� ����. 
	dfs(root->children[2]); // ����Լ��� children[2]�� �ڽĳ�带 Ÿ�� ����. 
}


//bfs�Լ�(ť�� ���� ������� ������ ��� �ְ� ����Ѵ�) 
void bfs(Node * root){ //root�� ���ڷ� ���� 
	Queue q; // ť���� 
	QueueInit(&q); //ť �ʱ�ȭ 
	int i; //�ݺ����� ���� i 
	int count=0; //������¸� ���� ���� 
	Enqueue(&q, root); //ť�� ��Ʈ ���� 
	
	
	while(!QIsEmpty(&q)){ //ť�� ���� ���������� while�� �ݺ� 
		root=Dequeue(&q); // ť���� �� ���� root�� ���� 
		if(count==0){ //ù����� ���� ��� 
			printf("%d",root->data);
			count+=1;
		}
		else{ //�ι��� ��º��ʹ� ȭ��ǥ�� ��� 
			printf("->%d",root->data);
		}
		for(i=0; i<3; i++){ // �ڽ��� �ִ� 3���̹Ƿ� 3�� �ݺ� 
			if(root->children[i]!=NULL){ //���� �ڽ��� NULL�� �ƴϸ� 
				Enqueue(&q, root->children[i]); // �� �ڽ��� ť�� ������ 
			}
		}	
	}
	
}


int main() {
    int depth; //depth ���� ���� ������ ���� 
    printf("Input:");
    scanf("%d", &depth); // depth�Է¹��� 
    
    
    double dfs_time=0; //dfs �Լ��� ����ð� ���庯�� 
	double bfs_time=0;//bfs �Լ��� ����ð� ���庯��
	
    Node* root = NULL; //root ������ ���� ���� 
    
	srand((unsigned int)time(NULL)); // ������ ������ ���� ���� 
	root = insertNode(root,0, depth); // root�� ��� �����ؼ� �� �ּ� ���� 


    printf("������ Ʈ��: \n");
    printTree(root, 0);
    printf("\n");
    
    
    printf("Output:");
    printf("\n");
    printf("DFS: ");
	clock_t start1 = clock(); //Ÿ�̸� ����
	dfs(root); // dfs ȣ�� 
	clock_t end1 = clock(); // Ÿ�̸� ����
	dfs_time=(double)(end1 - start1); // Ÿ�̸� ����ð�(ms) - Ÿ�̸� ���۽ð�(ms)
    printf(" / %lf msec", dfs_time);
	printf("\n");
    printf("BFS: ");
    clock_t start2 = clock(); //Ÿ�̸� ����
	bfs(root); //bfs ȣ�� 
	clock_t end2 = clock(); // Ÿ�̸� ����
	bfs_time=(double)(end2 - start2); // Ÿ�̸� ����ð�(ms) - Ÿ�̸� ���۽ð�(ms)
	printf(" / %lf msec", bfs_time);
    printf("\n");


    return 0; //main�Լ� ���� 
}



