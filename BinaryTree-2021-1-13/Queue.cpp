#include "Queue.h"

//��ʼ������
void QueueInit(Queue* q) {
	assert(q);
	q->_front = NULL;
	q->_rear = q->_front;
}
//��β�����
void QueuePush(Queue* q, QDataType data) {
	assert(q);
	QNode* newnode = (QNode*)malloc(sizeof(QNode));
	newnode->_data = data;
	newnode->_next = NULL;
	if (q->_front == NULL) {
		q->_front = q->_rear = newnode;
	}
	q->_rear->_next = newnode;
	q->_rear = newnode;
}
//��ͷ������
void QueuePop(Queue* q) {
	assert(q);
	assert(q->_front);
	QNode* newhead = q->_front->_next;
	free(q->_front);
	q->_front = newhead;
	//��ֹҰָ��
	if (q->_front == NULL) q->_rear = NULL;
}
//��ȡ����ͷ��Ԫ��
QDataType QueueFront(Queue* q) {
	assert(q);
	assert(q->_front);
	return q->_front->_data;
}
//��ȡ���ж�βԪ��
QDataType QueueBack(Queue* q) {
	assert(q);
	assert(q->_rear);
	return q->_rear->_data;
}
//��ȡ��������ЧԪ�صĸ���
int QueueSize(Queue* q) {
	assert(q);
	QNode* cur = q->_front;
	int count = 0;
	while (cur) {
		count++;
		cur = cur->_next;
	}
	return count;
}
//�������Ƿ�Ϊ�գ����Ϊ�շ��ط������������Ϊ�գ�����0
int QueueEmpty(Queue* q) {
	assert(q);
	if (q->_front == q->_rear) return 1;
	return 0;
}
//���ٶ���
void QueueDestroy(Queue* q) {
	assert(q);
	QNode* cur = q->_front;
	while (cur != q->_rear) {
		QNode* next = cur->_next;
		free(cur);
		cur = next;
	}
	q->_front = q->_rear = NULL;
}