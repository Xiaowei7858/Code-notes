#include"SList.h"

//动态申请节点
SListNode* BuySListNode(SLTDataType x) {
	SListNode* Node = (SListNode*)malloc(sizeof(SListNode));
	if (Node == NULL) {
		printf("请求失败");
		return NULL;
	}
	Node->data = x;
	return Node;
}
//单链表打印
void SListPrint(SListNode* plist) {
	assert(plist);
	SListNode* cur = NULL;
	cur = plist->next;
	while (cur != NULL) {
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");
}
//单链表尾插
void SListPushBack(SListNode* plist, SLTDataType x) {
	assert(plist);
	SListNode* cur = plist;
	SListNode* Node = BuySListNode(x);
	while (cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = Node;
	Node->next = NULL;
}
//单链表头插
void SListPushFront(SListNode* plist, SLTDataType x) {
	assert(plist);
	SListNode* Node = BuySListNode(x);
	SListNode* cur = plist->next;
	plist->next = Node;
	Node->next = cur;
}
//单链表尾删
void SListPopBack(SListNode* plist) {
	assert(plist);
	if (plist->next == NULL) return;
	if (plist->next->next == NULL) {
		SListNode* last = plist->next;
		plist->next = NULL;
		free(last);
	}
	SListNode* cur = plist;
	while (cur->next->next != NULL) {
		cur = cur->next;
	}
	SListNode* last = cur->next;
	cur->next = NULL;
	free(last);
}
//单链表头删
void SListPopFront(SListNode* plist) {
	assert(plist);
	if (plist->next->next == NULL) {
		SListNode* front = plist->next;
		plist->next = NULL;
		free(front);
	}
	SListNode* front = plist->next;
	plist->next = plist->next->next;
	free(front);
}
//单链表查找
SListNode* SListFind(SListNode* plist, SLTDataType x) {
	assert(plist);
	SListNode* cur = plist->next;
	while (cur != NULL) {
		if (cur->data == x) {
			return cur;
		}
		cur = cur->next;
	}
	printf("没找到");
	return NULL;
}
//单链表在pos位置之后插入x
void SListInsertAfter(SListNode* pos, SLTDataType x) {
	if (pos == NULL) {
		return;
	}
	SListNode* Node = BuySListNode(x);
	SListNode* cur = pos->next;
	pos->next = Node;
	Node->next = cur;
}
//单链表删除pos之后的值
void SListEraseAfter(SListNode* pos) {
	if (pos == NULL || pos->next == NULL) return;
	SListNode* after = pos->next;
	pos->next = pos->next->next;
	free(after);
}
//单链表的销毁
void SListDestroy(SListNode* plist) {
	if (plist->next == NULL) {
		return;
	}
	SListNode* cur = plist->next;
	SListNode* after = cur->next;
	while (cur != NULL) {
		free(cur);
		if (after == NULL) {
			break;
		}
		cur = after;
		after = after->next;
	}
	plist->next = NULL;
}