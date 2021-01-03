#include"Stack.h"


//��ʼ��ջ
void StackInit(Stack* ps) {
	ps->_capacity = 4;
	ps->_a = (STDataType*)malloc(sizeof(STDataType) * ps->_capacity);
	ps->_top = 0;
}
//��ջ
void StackPush(Stack* ps, STDataType data) {
	assert(ps);
	if (ps->_top == ps->_capacity) {
		STDataType* temp = (STDataType*)realloc(ps->_a,sizeof(STDataType) * ps->_capacity * 2);
		ps->_a = temp;
		ps->_capacity *= 2;
	}
	ps->_a[ps->_top] = data;
	ps->_top++;
}
//��ջ
void StackPop(Stack* ps) {
	assert(ps);
	ps->_top--;
}
//��ȡջ��Ԫ��
STDataType StackTop(Stack* ps) {
	assert(ps);
	assert(!StackEmpty(ps));
	return ps->_a[ps->_top - 1];
}
//��ȡջ����ЧԪ�صĸ���
int StackSize(Stack* ps) {
	assert(ps);
	return ps->_top;
}
//���ջ�Ƿ�Ϊ�գ����Ϊ�շ��ط�0����������Ϊ�գ�����0
int StackEmpty(Stack* ps) {
	assert(ps);
	return ps->_top == 0 ? 1 : 0;
}
//����ջ
void StackDestroy(Stack* ps) {
	assert(ps);
	free(ps->_a);
	ps->_capacity = ps->_top = 0;
	free(ps);
}