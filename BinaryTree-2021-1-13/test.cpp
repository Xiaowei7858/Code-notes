
#include<stdio.h>
#include<stdlib.h>
#include"Queue.h"

typedef char BTDataType;
typedef struct BinaryTreeNode {
	BTDataType _data;
	struct BinaryTreeNode* _left;
	struct BinaryTreeNode* _right;
}BTNode;

//ͨ��ǰ����������鹹��������
//ABCD##EF####
BTNode* BinaryTreeCreate(BTDataType* a, int n, int* p) {
	if (a[*p] == '#') {
		++(*p);
		return NULL;
	}

	BTNode* root = (BTNode*)malloc(sizeof(BTNode));
	root->_data = a[(*p)++];
	root->_left = BinaryTreeCreate(a, n, p);
	root->_right = BinaryTreeCreate(a, n, p);

	return root;
}

//������������
void BinaryTreeDestroy(BTNode* root) {
	if (!root)
		return;

	BinaryTreeDestroy(root->_left);
	BinaryTreeDestroy(root->_right);

	free(root);
}

//��������k��ڵ����
int BinaryTreeLevelKSize(BTNode* root, int k) {
	if (!root)
		return 0;

	if (root)
		return 1;

	return BinaryTreeLevelKSize(root->_left, k - 1) + BinaryTreeLevelKSize(root->_right, k - 1);
}

//����������ֵΪx�Ľڵ�
BTNode* BinaryTreeFind(BTNode* root, BTDataType x) {
	if (!root)
		return NULL;

	if (root->_data == x)
		return root;

	BTNode* node = BinaryTreeFind(root->_left, x);
	if (node)
		return node;
	node = BinaryTreeFind(root->_right, x);
	if (node)
		return node;

	return NULL;
 }

//ǰ�����
void PrevOrder(BTNode* root) {
	if (!root) {
		printf("NULL ");
		return;
	}
	printf("%c ", root->_data);
	PrevOrder(root->_left);
	PrevOrder(root->_right);
}

//�������
void InOrder(BTNode* root) {
	if (!root) {
		printf("NULL ");
		return;
	}
	InOrder(root->_left);
	printf("%c ", root->_data);
	InOrder(root->_right);
}

//�������
void PostOrder(BTNode* root) {
	if (!root) {
		printf("NULL ");
		return;
	}
	PostOrder(root->_left);
	PostOrder(root->_right);
	printf("%c ", root->_data);
}

//������������
int TreeSize(BTNode* root) {
	if (!root) return 0;
	
	int left = TreeSize(root->_left);
	int right = TreeSize(root->_right);
	return left + right + 1;
}
//1.ȫ�ֱ���--ȱ�㣺�����ٴ����У����ڻ�����++��
//2.��ָ�������ȱ�㣺������
//3.return ֵ

//������Ҷ�ӽڵ�ĸ���
int TreeLeafSize(BTNode* root) {
	if (!root) return 0;
	if (!root->_left && !root->_right) return 1;

	return TreeLeafSize(root->_left)+TreeLeafSize(root->_right);
}

//�������
void BinaryTreeLevelInorder(BTNode* root) {
	//���б��棬1�����Ƚ��롣2�����������в�Ϊ�գ�����ͷ���ݣ�ͬʱ�ѳ��Ľ��ĺ��Ӵ��롣3��ֱ������Ϊ�գ�����

	Queue q;
	QueueInit(&q);
	if (!root)
		return;
	QueuePush(&q,root);
	while (!QueueEmpty(&q)) {
		BTNode* front = QueueFront(&q);
		QueuePop(&q);

		printf("%d ", front->_data);
		if (front->_left) {
			QueuePush(&q, front->_left);
		}

		if (front->_right) {
			QueuePush(&q, front->_right);
		}
	}
	QueueDestroy(&q);
	printf("\n");
}

//�ж��������Ƿ�����ȫ������
int BinaryTreeComplete(BTNode* root) {
	Queue q;
	QueueInit(&q);
	if (!root)
		return 1;
	QueuePush(&q, root);
	while (!QueueEmpty(&q)) {
		BTNode* front = QueueFront(&q);
		QueuePop(&q);

		if (!front)
			break;
		QueuePush(&q, front->_left);
		QueuePush(&q, front->_right);
	}
	while (!QueueEmpty(&q)) {
		BTNode* front = QueueFront(&q);
		QueuePop(&q);

		if (front) {
			QueueDestroy(&q);
			return 0;
		}
	}

	QueueDestroy(&q);
	return 1;
}

//�߶�
int TreeDepth(BTNode* root) {
	if (!root) return 0;
	int LeftDepth = TreeDepth(root->_left);
	int RightDepth = TreeDepth(root->_right);
	return LeftDepth > RightDepth ? LeftDepth + 1 : RightDepth + 1;
}

//�������
BTNode* CreateNode(char x) {
	BTNode* node = (BTNode*)malloc(sizeof(BTNode));
	node->_data = x;
	node->_left = NULL;
	node->_right = NULL;
	return node;
}

int main() {
	BTNode* A = CreateNode('A');
	BTNode* B = CreateNode('B');
	BTNode* C = CreateNode('C');
	BTNode* D = CreateNode('D');
	BTNode* E = CreateNode('E');
	A->_left = B;
	A->_right = C;
	B->_left = D;
	B->_right = E;
	//PostOrder(A);
	//printf("%d", TreeSize(A));
	//printf("\n");
	//printf("%d ",TreeLeafSize(A));
	printf("%d", TreeDepth(A));

	getchar();
	return 0;
}