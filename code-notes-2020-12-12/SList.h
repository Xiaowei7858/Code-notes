#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


typedef int SLTDataType;
typedef struct SListNode {
	SLTDataType data;
	struct SListNode* next;
}SListNode;

//��̬����ڵ�
SListNode* BuySListNode(SLTDataType x);
//�������ӡ
void SListPrint(SListNode* plist);
//������β��
void SListPushBack(SListNode** plist, SLTDataType x);
//������ͷ��
void SListPushFront(SListNode** plist, SLTDataType x);
//������βɾ
void SListPopBack(SListNode** plist);
//������ͷɾ
void SListPopFront(SListNode** plist);
//���������
SListNode* SListFind(SListNode* plist, SLTDataType x);
//��������posλ��֮�����x
void SListInsertAfter(SListNode* pos, SLTDataType x);
//������ɾ��pos֮���ֵ
void SListEraseAfter(SListNode* pos);
//�����������
void SListDestroy(SListNode* plist);

