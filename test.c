#include "SeqList.h"


void test() {
	SL s;
	SeqListInit(&s);
	SeqListPushBack(&s, 1);
	SeqListPushBack(&s, 2);
	SeqListPushBack(&s, 3);
	SeqListPushBack(&s, 4);
	SeqListPushBack(&s, 5);
	SeqListPushBack(&s, 6);
	SeqListPushBack(&s, 7);
	SeqListPopBack(&s);
	SeqListPushFront(&s, 12);
	SeqListPopFront(&s);
	SeqListFind(&s, 5);
	SeqListInsert(&s, 2, 13);
	SeqListErase(&s, 2);
	SeqListPrint(&s);
}

int main() {
	test();
	return 0;
}