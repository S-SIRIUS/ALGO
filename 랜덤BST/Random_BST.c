#include <stdio.h>
#include <stdlib.h>
#include <time.h> //������ �����Ѱ�, �ð������ ���� ���

typedef int BSTData; //���� value �����͵� ����ü�� �����Ͽ���. 

//����Ʈ���� ��带 ǥ���� ����ü 
typedef struct _bTreeNode{
	BSTData data; // ���� value ������ 
	struct _bTreeNode * left; //bTreeNode�� �ڷ����� ������ ������ ����Ű�� ������ ���� left(���� �ڽĳ�带 ����Ŵ) 
	struct _bTreeNode * right;  //bTreeNode�� �ڷ����� ������ ������ ����Ű�� ������ ���� right(������ �ڽĳ�带 ����Ŵ)
	
} BTreeNode; // ����ü�� BTreeNode��� �̸� �ο� 

//��忡 ����� ������ ��ȯ 
BSTData GetData(BTreeNode * bt){ //BSTData������ �����ͺ��� bt�� �޾Ƽ� �� bt�� �����͸� ��ȯ��
	return bt->data;
}

//����Ʈ�� ��带 �����Ͽ� �� �ּ� ���� ��ȯ��
BTreeNode * MakeBTreeNode(void){ 
	BTreeNode * nd = (BTreeNode*)malloc(sizeof(BTreeNode)); //BTreeNode�� �����ŭ �޸𸮸� �Ҵ���, BTreeNode�� �����ͷ� ����ȯ 
	nd->left = NULL; //nd������ left�� NULL�� �ʱ�ȭ(left�� ���� �ƹ��͵� �Ȱ���Ŵ) 
	nd->right = NULL; //nd������ right�� NULL�� �ʱ�ȭ(right�� ���� �ƹ��͵� �Ȱ���Ŵ) 
	return nd; //malloc���� �Ҵ��� �޸��� ���� �ּҰ� ��ȯ 
}

//��忡 ������ ����, data�� ���޵� ���� ���� 
void SetData(BTreeNode * bt, BSTData data){ //data�� �����ͺ��� bt�� ���ڷ� �޾Ƽ� bt�� ����Ű�� ����� data���� ���ڷ� ���� data�� ����  
	bt -> data = data;
}

//���� ����Ʈ���� �ּҰ� ��ȯ 
BTreeNode * GetLeftSubTree(BTreeNode * bt){ // �����ͺ��� bt�� ���ڷ� �޾Ƽ� bt�� ����Ű�� ����� ���ʼ���Ʈ���� �ּҰ��� ��ȯ�� 
	return bt->left;
}

//������ ����Ʈ���� �ּҰ� ��ȯ 
BTreeNode * GetRightSubTree(BTreeNode * bt){// �����ͺ��� bt�� ���ڷ� �޾Ƽ� bt�� ����Ű�� ����� �����ʼ���Ʈ���� �ּҰ��� ��ȯ��
	return bt->right;
}

//���� ����Ʈ���� ������ 
void MakeLeftSubTree(BTreeNode * main, BTreeNode *sub){ //���� ����Ʈ���� �����ϴ� �Լ�, �����ͺ��� main�� sub�����ڷ� �޴´�. 
	if(main -> left != NULL){ //���� main�� ����Ű�� ����� left��尡 NULL�� �ƴ϶��(�����Ѵٸ�) 
		free(main->left); //���ʿ� �ش��ϴ� Ʈ���� ������ 
	}
	main -> left = sub; //���ʿ� �ش��ϴ� Ʈ���� subƮ������(subƮ���� �ּҰ��� left��带 ����Ű�� left �����ͺ����� ����) 
}

//������ ����Ʈ���� ������ 
void MakeRightSubTree(BTreeNode * main, BTreeNode *sub){ //������ ����Ʈ���� �����ϴ� �Լ�, �����ͺ��� main�� sub�����ڷ� �޴´�. 
	if(main -> right != NULL){ //���� main�� ����Ű�� ����� right��尡 NULL�� �ƴ϶��(�����Ѵٸ�) 
		free(main->right); //�����ʿ� �ش��ϴ� Ʈ���� ������ 
	}
	main -> right = sub; //�����ʿ� �ش��ϴ� Ʈ���� subƮ������(subƮ���� �ּҰ��� right��带 ����Ű�� right �����ͺ����� ����) 
}

//BST�� ���� �� �ʱ�ȭ 
void BSTMakeAndInit(BTreeNode ** pRoot){ //���������� ���� pRoot�� ���ڸ� ����(bstRoot��� �����ͺ����� �ּҰ�) 
	*pRoot = NULL; // ��Ʈ��带 ����Ű�� bstRoot�����ͺ����� �ʱ�ȭ 
}

//����� ���������� �����Ͽ� BST�� ������� �����͸� ���� 
void BSTInsert(BTreeNode ** pRoot, BSTData data){ //���������� ���� PRoot�� ���ڷ� ����(bstRoot��� �����ͺ����� �ּҰ�), ������ data�� ���ڷ� ���� 
	BTreeNode * pNode = NULL; //�θ��带 ������� �����ͺ��� pNode �ʱ�ȭ 
	BTreeNode * cNode = *pRoot; //�����带 ����Ű�� ������ ���� CNode�� PRoot�� �ѹ� ����Ű�� ��(bstRoot�����ͺ����� �ּҸ� ����), bstRoot�� root��带 ����Ŵ 
	BTreeNode * nNode = NULL; // ���ο� ��带 ����Ű�� nNode �ʱ�ȭ 
	
	//���ο� ��尡 �߰��� ��ġ�� ã��(pNode�� �������� �߰��� ����) 
	while(cNode != NULL){ //CNode�� NULL�� �ƴ� ��쿡 ��� �ݺ� 
		if(data == GetData(cNode)){ // �������� value�� ���ڷ� ���޹��� �����Ͱ� ������ �״�� �Լ� ����(Ű�� �ߺ��� ������� �ʴ´�.) 
			return;
		}
		pNode = cNode; //PNode������ CNode�� ����(�����尡 �θ��尡��)
		
		 
		if(GetData(cNode) > data){ //���� cNode�� value�� �����ͺ��� ũ�ٸ� 
			cNode = GetLeftSubTree(cNode); // cNode�� ���� ����Ʈ���� �ּҰ��� cNode�� ���� 
		}
		else{ //���� value�� �����ͺ��� �۰ų� ���ٸ� 
			cNode = GetRightSubTree(cNode); //cNode�� ������ ����Ʈ���� �ּҰ��� cNode�� ���� 
		}
	}
	nNode = MakeBTreeNode(); //����Ʈ����带 �����Ͽ� �� �ּҰ��� nNode�� ���� 
	SetData(nNode, data); //nNode�� ������ ���� 
	
	//���� nNode�� BSTƮ���� ���Ĵ�� ������ ��忡 �����ؾ��� 
	
	if(pNode != NULL){ //���� pNode�� NULL�� �ƴ϶��(�� ��尡 ��Ʈ��尡 �ƴ϶��, ó���߰��ϴ� ��� �ƴ϶��) 
		if(data < GetData(pNode)){ //���ڷι��� �����ͺ��� pNode�� �����Ͱ� ũ�ٸ� 
			MakeLeftSubTree(pNode, nNode); //pNode�� ���ʿ� nNode�� ����(bst�� ����, �θ���� �����ڽĳ�庸�� ũ��) 
		}
		else{//���� ���ڷι��� �����ͺ��� pNode�� �����Ͱ� �۰ų� ���ٸ� 
			MakeRightSubTree(pNode, nNode); //pNode�� �����ʿ� nNode�� ����(bst�� ����, �θ���� �������ڽĳ�庸�� �۴�) 
		}
	}
	else{//�� ��尡 ��Ʈ�����(ó���߰��ϴ�) 
		*pRoot = nNode; //pRoot�����ͺ����� nNode�ּ� ����(��Ʈ����) 
	}
}

//��Ʈ�������� ���̸� ã�� findDepth�Լ� 
int findDepth(BTreeNode * pRoot, int depth){//���ڷ�  bstRoot�� ����Ű�� �ּҿ�, depth�� �޴´�. 
	BTreeNode * cNode = pRoot; // cNode�����ͺ����� bstRoot����Ű�� �ּ� ���� 
	if (cNode==NULL){ //cNode�� NULL�̸� ���� ���̸� ��ȯ 
		return depth;
	}
	int leftDepth =	findDepth(cNode->left, depth+1); //���ȣ��� cNode�� ���� Ʈ���� ����ؼ� ȣ���س�����, ���̵� 1�� ����, ȣ���ϴٰ� cNode�� ���� NULL�� �Ǹ� ���� ���̸� ��ȯ�� 
	int rightDepth = findDepth(cNode->right, depth+1); //���ȣ��� cNode�� ������ Ʈ���� ����ؼ� ȣ���س�����, ���̵� 1�� ����, ȣ���ϴٰ� cNode�� ���� NULL�� �Ǹ� ���� ���̸� ��ȯ��
	
	//���ʼ���Ʈ�� ���̿� ������ ����Ʈ�� ���̸� ���Ͽ� �� ū���� ��ȯ 
	if (leftDepth > rightDepth){ 
		return leftDepth;
	}
	else{
		return rightDepth;
	}
	
	
}

// Ʈ�������� ����������� Ȯ���ϱ����� �߰��� �׽�Ʈ �뵵�� printTree�Լ��� �ۼ��Ͽ���. ���ʺ��� ������ ������ �Ͽ� ���
// ���� ������¿��� �Ⱦ��� 
void printTree(BTreeNode* root, int level) {
    if (root == NULL) {
        return;
    }
    
    printTree(root->right, level + 1); // ������ �ڽ� ��� ���
    int i;
    for (i = 0; i < level; i++) {
        printf("    "); // ������ �°� ���� ���
    }
    printf("%d\n", root->data); // ���� ��� �� ���
    printTree(root->left, level + 1); // ���� �ڽ� ��� ���
}


int main(){
	int k; //100�� �ݺ��뵵�� ���� 
	double alltime[100]={0}; //alltime�� �ڷ����� double�̰� Ʈ���� ����ºκп� �ҿ�Ǵ� �ð��� 100ȸ ���� �����ؼ� �ִ�� �ּҸ� ã�����̱� ������ ����Ʈ�� �ۼ� 
	int alldepth[100]={0}; //alltime�� �ڷ����� int�̰� Ʈ���� �Ź� �ٸ��� ��������� �� ���̵� �޶�����. 100ȸ ���� �����ؼ� �ִ�� �ּҸ� ã�����̱� ������ ����Ʈ�� �ۼ�
	for(k=0; k<100; k++){ //100ȸ �ݺ� 
		clock_t start = clock(); //timer ����
		
		BTreeNode * bstRoot; // bstRoot�� BST�� ��Ʈ��带 ����Ű�� ������ ���� 
		BSTMakeAndInit(&bstRoot); // BST�� ���� �� �ʱ�ȭ�Լ� ȣ��, �����ͺ����� �ּҰ��� ���ڷ� ���� 
		
		int i,j; //������ �ݺ��� ���� ���� 2�� 
		int random=0; // random���� �ʱ�ȭ 
		int depth=0; // ���� ���� �ʱ�ȭ 
		double treetime=0; // Ʈ������µ� �ɸ���  �ð� ���� �ʱ�ȭ 
		srand((unsigned int)time(NULL)); // �ð����� �õ尪�� ��Ȥ �ٲپ���, �̷��� �ϸ� ������ ������ ������ �Ǿ� ���� ��� �ٲ��.
		int temp[1000]; //�ߺ��� Ȯ���� ���� �迭
		for(i=0; i<=999; i++){ // 1000�� �ݺ� 
			random=rand()%1000; // 0~999 ���� ���� ���� 
			
			for (j=0; j<=i; j++){ //�ߺ��� �˻� 
				if(random==temp[j]){ //���� ���ݻ����� random���� temp�ȿ� ������ i�� �Ѱ� �ٿ��� ���ư�, �� �� random�� �ٽ� ���� 
					i--;
				}
			}
			
			
			temp[i]=random; // ���� �ߺ��˻縦 ����ߴٸ� temp �迭�� ���� 
			BSTInsert(&bstRoot, random); // ���� BST�� ����
			
		}
		clock_t end = clock(); //bstƮ���� ��� ��������Ƿ� Ÿ�̸� ���� 
		treetime=(double)(end - start); // Ÿ�̸� ����ð�(ms) - Ÿ�̸� ���۽ð�(ms)
		printf("�ҿ� �ð�: %lf ms\n", treetime); //�ҿ�ð� ���(���� ms) 
		alltime[k]=treetime; // alltime�迭�� �ҿ�ð� ���� 
		depth=findDepth(bstRoot, 0); // depth����ϴ� findDepth �Լ� ȣ�� 
		alldepth[k]=depth; // alldepth�迭�� ã�� depth ���� 
		printf("����: %d\n", depth); // ���� ��� 
	}
	
	double all_time=0; //�Ǽ����� all_time �������� 
	double all_depth=0; //�Ǽ����� all_depth ���� ���� 
	double timemax=alltime[0]; //�ҿ�ð��� �ִ븦 ����ϱ� ���� �ʱⰪ 
	double timemin=alltime[0]; //�ҿ�ð��� �ּҸ� ����ϱ� ���� �ʱⰪ 
	int depthmax=alldepth[0];//������ �ִ븦 ����ϱ� ���� �ʱⰪ 
	int depthmin=alldepth[0];//������ �ּҸ� ����ϱ� ���� �ʱⰪ 
	int i;
	for (i=0; i<100; i++){ //100�� �ݺ� 
		all_time+=alltime[i]; //all_time�� ��� ���س���(���߿� ��� ���뵵) 
		
		if(alltime[i]>timemax){ //��� �ҿ�ð��� �ִ밪�� �����س��� 
			timemax=alltime[i];
		}
		if(alltime[i]<timemin){ //��� �ҿ�ð��� �ּҰ��� ������ ���� 
			timemin=alltime[i];
		}
		
		all_depth+=alldepth[i]; //all_depth�� ��� ���س���(���߿� ��� ���뵵) 
		
		if(alldepth[i]>depthmax){
			depthmax=alldepth[i]; //��� ������ �ִ밪�� �����س��� 
		}
		if(alldepth[i]<depthmin){
			depthmin=alldepth[i]; //��� ������ �ּҰ��� �����س��� 
		}

		
	}
	double avgtime=(all_time/100); //100���� ��� �ð� ��� 
	double avgdepth = (all_depth/100); //100���� ��� ���� ��� 
	printf("Time - AVG: %lfms Max: %lfms Min: %lfms\n", avgtime, timemax, timemin); //��սð�, �ִ�ð�, �ּҽð� ��� 
	printf("Depth - AVG: %lf Max: %d Min: %d", avgdepth, depthmax, depthmin); //��ձ���, �ִ����, �ּұ��� ��� 
	
	return 0;//main�Լ� ���� 
}
 
	
	
