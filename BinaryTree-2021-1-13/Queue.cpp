#include "Queue.h"

//初始化队列
void QueueInit(Queue* q) {
	assert(q);
	q->_front = NULL;
	q->_rear = q->_front;
}
//队尾入队列
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
//队头出队列
void QueuePop(Queue* q) {
	assert(q);
	assert(q->_front);
	QNode* newhead = q->_front->_next;
	free(q->_front);
	q->_front = newhead;
	//防止野指针
	if (q->_front == NULL) q->_rear = NULL;
}
//获取队列头部元素
QDataType QueueFront(Queue* q) {
	assert(q);
	assert(q->_front);
	return q->_front->_data;
}
//获取队列队尾元素
QDataType QueueBack(Queue* q) {
	assert(q);
	assert(q->_rear);
	return q->_rear->_data;
}
//获取队列中有效元素的个数
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
//检测队列是否为空，如果为空返回非零结果，如果不为空，返回0
int QueueEmpty(Queue* q) {
	assert(q);
	if (q->_front == q->_rear) return 1;
	return 0;
}
//销毁队列
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