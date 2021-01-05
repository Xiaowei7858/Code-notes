#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


typedef int SLTDataType;
typedef struct SListNode {
	SLTDataType data;
	struct SListNode* next;
}SListNode;

//动态申请节点
SListNode* BuySListNode(SLTDataType x);
//单链表打印
void SListPrint(SListNode* plist);
//单链表尾插
void SListPushBack(SListNode** plist, SLTDataType x);
//单链表头插
void SListPushFront(SListNode** plist, SLTDataType x);
//单链表尾删
void SListPopBack(SListNode** plist);
//单链表头删
void SListPopFront(SListNode** plist);
//单链表查找
SListNode* SListFind(SListNode* plist, SLTDataType x);
//单链表在pos位置之后插入x
void SListInsertAfter(SListNode* pos, SLTDataType x);
//单链表删除pos之后的值
void SListEraseAfter(SListNode* pos);
//单链表的销毁
void SListDestroy(SListNode* plist);

