#include"Stack.h"


//初始化栈
void StackInit(Stack* ps) {
	ps->_capacity = 4;
	ps->_a = (STDataType*)malloc(sizeof(STDataType) * ps->_capacity);
	ps->_top = 0;
}
//入栈
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
//出栈
void StackPop(Stack* ps) {
	assert(ps);
	ps->_top--;
}
//获取栈顶元素
STDataType StackTop(Stack* ps) {
	assert(ps);
	assert(!StackEmpty(ps));
	return ps->_a[ps->_top - 1];
}
//获取栈中有效元素的个数
int StackSize(Stack* ps) {
	assert(ps);
	return ps->_top;
}
//检测栈是否为空，如果为空返回非0结果，如果不为空，返回0
int StackEmpty(Stack* ps) {
	assert(ps);
	return ps->_top == 0 ? 1 : 0;
}
//销毁栈
void StackDestroy(Stack* ps) {
	assert(ps);
	free(ps->_a);
	ps->_capacity = ps->_top = 0;
	free(ps);
}