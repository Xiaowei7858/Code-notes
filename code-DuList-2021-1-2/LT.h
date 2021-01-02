
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
//双向带头链表

typedef int LTDataType;
typedef struct ListNode {
	LTDataType _data;
	struct ListNode* _next;
	struct ListNode* _prev;
}ListNode;


//申请结点
ListNode* BuyNode(LTDataType x);
//创建返回链表的头结点
ListNode* ListCreate();
//双向链表清空
void ListClear(ListNode** ppHead);
//双向链表销毁
void ListDestory(ListNode* pHead);
//双向链表打印
void ListPrint(ListNode* pHead);
//双向链表尾插
void ListPushBack(ListNode* pHead, LTDataType x);
//双向链表尾删
void ListPopBack(ListNode* pHead, LTDataType x);
//双向链表头插
void ListPushFront(ListNode* pHead, LTDataType x);
//双向链表头删
void ListPopFront(ListNode* pHead);
//双向链表查找
ListNode* ListFind(ListNode* pHead, LTDataType x);
//双向链表在pos的前面进行插入
void ListInsert(ListNode* pHead, LTDataType x);
//双向链表删除pos位置的结点
void ListErase(ListNode* pos);