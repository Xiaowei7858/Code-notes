
#include"LT.h"



ListNode* BuyNode(LTDataType x) {
	ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));
	newnode->_data = x;
	newnode->_prev = NULL;
	newnode->_next = NULL;
	return newnode;
}
//创建返回链表的头结点
ListNode* ListCreate() {
	ListNode* pHead = BuyNode(-1);
	pHead->_next = pHead;
	pHead->_prev = pHead;
	return pHead;
}
//双向链表清空
void ListClear(ListNode* pHead) {
	assert(pHead);
	ListNode* cur = pHead->_next;
	while (cur != pHead) {
		ListNode* next = cur->_next;
		free(cur);
		cur = next;
	}
	pHead->_next = pHead;
	pHead->_prev = pHead;
}
//双向链表销毁
void ListDestory(ListNode** ppHead) {
	ListClear(*ppHead);
	free(*ppHead);
	*ppHead = NULL;
}
//双向链表打印
void ListPrint(ListNode* pHead) {
	assert(pHead);
	ListNode* cur = pHead->_next;
	while (cur != pHead) {
		printf("%d", cur->_data);
		cur = cur->_next;
	}
	printf("\n");
}
//双向链表尾插
void ListPushBack(ListNode* pHead, LTDataType x) {
	assert(pHead);
	ListNode* tail = pHead->_prev;
	ListNode* newnode = BuyNode(x);
	tail->_next = newnode;
	newnode->_prev = tail;
	newnode->_next = pHead;
	pHead->_prev = newnode;
}
//双向链表尾删
void ListPopBack(ListNode* pHead, LTDataType x) {
	assert(pHead);
	assert(pHead->_next != NULL);
	ListNode* tail = pHead->_prev;
	ListNode* tailprev = tail->_prev;
	tailprev->_next = pHead;
	pHead->_prev = tailprev;
	free(tail);
}
//双向链表头插
void ListPushFront(ListNode* pHead, LTDataType x) {
	assert(pHead);
	ListNode* first = pHead->_next;
	ListNode* newnode = BuyNode(x);
	pHead->_next = newnode;
	newnode->_next = first;
	first->_prev = newnode;
	newnode->_prev = pHead;
}
//双向链表头删
void ListPopFront(ListNode* pHead) {
	assert(pHead);
	assert(pHead->_next);
	ListNode* first = pHead->_next;
	pHead->_next = first->_next;
	first->_next->_prev = pHead;
	free(first);
}
//双向链表查找
ListNode* ListFind(ListNode* pHead, LTDataType x) {
	assert(pHead);
	ListNode* cur = pHead->_next;
	while (cur != pHead) {
		if (cur->_data == x) {
			return cur;
		}
		cur = cur->_next;
	}
	return NULL;
}
//双向链表在pos的前面进行插入
void ListInsert(ListNode* pos, LTDataType x) {
	assert(pos);
	ListNode* newnode = BuyNode(x);
	ListNode* posprev = pos->_prev;
	posprev->_next = newnode;
	newnode->_prev = posprev;
	newnode->_next = pos;
	pos->_prev = newnode;
}
//双向链表删除pos位置的结点
void ListErase(ListNode* pos) {
	assert(pos);
	assert(pos->_next != pos);
	ListNode* posprev = pos->_prev;
	posprev->_next = pos->_next;
	pos->_next->_prev = pos;
	free(pos);
}