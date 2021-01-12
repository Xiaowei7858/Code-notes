
#include<stdio.h>
#include<stdlib.h>

typedef char BTDataType;
typedef struct BinaryTreeNode {
	BTDataType _data;
	struct BinaryTreeNode* _left;
	struct BinaryTreeNode* _right;
}BTNode;

void PrevOrder(BTNode* root) {
	if (!root) {
		printf("NULL ");
		return;
	}
	printf("%c ", root->_data);
	PrevOrder(root->_left);
	PrevOrder(root->_right);
}

void InOrder(BTNode* root) {
	if (!root) {
		printf("NULL ");
		return;
	}
	InOrder(root->_left);
	printf("%c ", root->_data);
	InOrder(root->_right);
}

void PostOrder(BTNode* root) {
	if (!root) {
		printf("NULL ");
		return;
	}
	PostOrder(root->_left);
	PostOrder(root->_right);
	printf("%c ", root->_data);
}

int TreeSize(BTNode* root) {
	if (!root) return 0;
	
	int left = TreeSize(root->_left);
	int right = TreeSize(root->_right);
	return left + right + 1;
}
//1.全局变量--缺点：后续再次运行，会在基础上++；
//2.传指针参数，缺点：不美观
//3.return 值
int TreeLeafSize(BTNode* root) {
	if (!root) return 0;
	if (!root->_left && !root->_right) return 1;

	return TreeLeafSize(root->_left)+TreeLeafSize(root->_right);
}

int TreeDepth(BTNode* root) {
	if (!root) return 0;
	int LeftDepth = TreeDepth(root->_left);
	int RightDepth = TreeDepth(root->_right);
	return LeftDepth > RightDepth ? LeftDepth + 1 : RightDepth + 1;
}
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