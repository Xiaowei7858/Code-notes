#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

typedef int STDataType;
typedef struct Stack {
	STDataType* _a;
	int _top;       //ջ��
	int _capacity;  //����
}Stack;

//��ʼ��ջ
void StackInit(Stack* ps);
//��ջ
void StackPush(Stack* ps, STDataType data);
//��ջ
void StackPop(Stack* ps);
//��ȡջ��Ԫ��
STDataType StackTop(Stack* ps);
//��ȡջ����ЧԪ�صĸ���
int StackSize(Stack* ps);
//���ջ�Ƿ�Ϊ�գ����Ϊ�շ��ط�0����������Ϊ�գ�����0
int StackEmpty(Stack* ps);
//����ջ
void StackDestroy(Stack* ps);