#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>


typedef int QDataType;
typedef struct QListNode {
	struct QListNode* _next;
	QDataType _data;
}QNode;

typedef struct Queue {
	QNode* _front;
	QNode* _rear;
}Queue;

//��ʼ������
void QueueInit(Queue* q);
//��β�����
void QueuePush(Queue* q, QDataType data);
//��ͷ������
void QueuePop(Queue* q);
//��ȡ����ͷ��Ԫ��
QDataType QueueFront(Queue* q);
//��ȡ���ж�βԪ��
QDataType QueueBack(Queue* q);
//��ȡ��������ЧԪ�صĸ���
int QueueSize(Queue* q);
//�������Ƿ�Ϊ�գ����Ϊ�շ��ط������������Ϊ�գ�����0
int QueueEmpty(Queue* q);
//���ٶ���
void QueueDestroy(Queue* q);