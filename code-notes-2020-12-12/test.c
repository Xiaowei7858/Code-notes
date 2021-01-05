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
	
	//ͷ��
	SListPushFront(&plist,2);
	SListPrint(plist);
	
	//������βɾ
	SListPopBack(&plist);
	SListPrint(plist);
	
	//������ͷɾ
	SListPopFront(&plist);
	SListPrint(plist);

	//���������
	SListFind(plist,2);
	SListPrint(plist);
	
	//��������posλ��֮�����x
	SListInsertAfter(plist->next->next, 2);
	SListPrint(plist);
	
	//������ɾ��pos֮���ֵ
	SListEraseAfter(plist->next->next);
	SListPrint(plist);
	
	//�����������
	SListDestroy(plist);
	SListPrint(plist);
}

int main() {
	test();
	return 0;
}