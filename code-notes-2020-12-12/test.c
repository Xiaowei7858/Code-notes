#include"SList.h"


void test() {
	SListNode* plist = (SListNode*)malloc(sizeof(SListNode));

	SListPushBack(&plist, 1);
	SListPushBack(&plist, 2);
	SListPushBack(&plist, 3);
	SListPushBack(&plist, 4);
	SListPushBack(&plist, 5);
	SListPushBack(&plist, 7);
	SListPushBack(&plist, 8);
	SListPrint(plist);
	
	//头插
	SListPushFront(&plist,2);
	SListPrint(plist);
	
	//单链表尾删
	SListPopBack(&plist);
	SListPrint(plist);
	
	//单链表头删
	SListPopFront(&plist);
	SListPrint(plist);

	//单链表查找
	SListFind(plist,2);
	SListPrint(plist);
	
	//单链表在pos位置之后插入x
	SListInsertAfter(plist->next->next, 2);
	SListPrint(plist);
	
	//单链表删除pos之后的值
	SListEraseAfter(plist->next->next);
	SListPrint(plist);
	
	//单链表的销毁
	SListDestroy(plist);
	SListPrint(plist);
}

int main() {
	test();
	return 0;
}