
#include<stdio.h>
#include<stdlib.h>
#include"Queue.h"

typedef char BTDataType;
typedef struct BinaryTreeNode {
	BTDataType _data;
	struct BinaryTreeNode* _left;
	struct BinaryTreeNode* _right;
}BTNode;

//通过前序遍历的数组构建二叉树
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

//二叉树的销毁
void BinaryTreeDestroy(BTNode* root) {
	if (!root)
		return;

	BinaryTreeDestroy(root->_left);
	BinaryTreeDestroy(root->_right);

	free(root);
}

//二叉树第k层节点个数
int BinaryTreeLevelKSize(BTNode* root, int k) {
	if (!root)
		return 0;

	if (root)
		return 1;

	return BinaryTreeLevelKSize(root->_left, k - 1) + BinaryTreeLevelKSize(root->_right, k - 1);
}

//二叉树查找值为x的节点
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

//前序遍历
void PrevOrder(BTNode* root) {
	if (!root) {
		printf("NULL ");
		return;
	}
	printf("%c ", root->_data);
	PrevOrder(root->_left);
	PrevOrder(root->_right);
}

//中序遍历
void InOrder(BTNode* root) {
	if (!root) {
		printf("NULL ");
		return;
	}
	InOrder(root->_left);
	printf("%c ", root->_data);
	InOrder(root->_right);
}

//后序遍历
void PostOrder(BTNode* root) {
	if (!root) {
		printf("NULL ");
		return;
	}
	PostOrder(root->_left);
	PostOrder(root->_right);
	printf("%c ", root->_data);
}

//二叉树结点个数
int TreeSize(BTNode* root) {
	if (!root) return 0;
	
	int left = TreeSize(root->_left);
	int right = TreeSize(root->_right);
	return left + right + 1;
}
//1.全局变量--缺点：后续再次运行，会在基础上++；
//2.传指针参数，缺点：不美观
//3.return 值

//二叉树叶子节点的个数
int TreeLeafSize(BTNode* root) {
	if (!root) return 0;
	if (!root->_left && !root->_right) return 1;

	return TreeLeafSize(root->_left)+TreeLeafSize(root->_right);
}

//层序遍历
void BinaryTreeLevelInorder(BTNode* root) {
	//队列保存，1、根先进入。2、迭代，队列不为空，出对头数据，同时把出的结点的孩子带入。3、直至队列为空，结束

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

//判读二叉树是否是完全二叉树
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

//高度
int TreeDepth(BTNode* root) {
	if (!root) return 0;
	int LeftDepth = TreeDepth(root->_left);
	int RightDepth = TreeDepth(root->_right);
	return LeftDepth > RightDepth ? LeftDepth + 1 : RightDepth + 1;
}

//创建结点
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