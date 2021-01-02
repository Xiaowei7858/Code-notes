
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
//˫���ͷ����

typedef int LTDataType;
typedef struct ListNode {
	LTDataType _data;
	struct ListNode* _next;
	struct ListNode* _prev;
}ListNode;


//������
ListNode* BuyNode(LTDataType x);
//�������������ͷ���
ListNode* ListCreate();
//˫���������
void ListClear(ListNode** ppHead);
//˫����������
void ListDestory(ListNode* pHead);
//˫�������ӡ
void ListPrint(ListNode* pHead);
//˫������β��
void ListPushBack(ListNode* pHead, LTDataType x);
//˫������βɾ
void ListPopBack(ListNode* pHead, LTDataType x);
//˫������ͷ��
void ListPushFront(ListNode* pHead, LTDataType x);
//˫������ͷɾ
void ListPopFront(ListNode* pHead);
//˫���������
ListNode* ListFind(ListNode* pHead, LTDataType x);
//˫��������pos��ǰ����в���
void ListInsert(ListNode* pHead, LTDataType x);
//˫������ɾ��posλ�õĽ��
void ListErase(ListNode* pos);