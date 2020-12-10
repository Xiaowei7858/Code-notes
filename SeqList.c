#include"SeqList.h"
//��ʼ��
void SeqListInit(SL* ps) {
	assert(ps);

	ps->array = (SLDataType*)malloc(sizeof(SLDataType) * 4);
	assert(ps->array);
	ps->size = 0;
	ps->capacity = 4;
}
void SeqListPrint(SL* ps) {
	assert(ps);
	for (size_t i = 0; i < ps->size; ++i) {
		printf("%d ", ps->array[i]);
	}
}
//����
void SeqListCheckCapacity(SL* ps) {
	assert(ps);
	int temp = ps->capacity;
	if (ps->size >= ps->capacity) {
		SLDataType* ptr = (SLDataType*)realloc(ps->array, sizeof(SLDataType) * (ps->capacity) * 2);
		//ps->a = (SLDataType*)realloc(ps->a, sizeof(SLDataType)*ps->capacity);
		if (ptr == NULL) {
			exit(-1);
		}
		ps->array = ptr;
		ps->capacity = 2 * temp;
	}
}
//����
void SeqListDestory(SL* ps) {
	free(ps->array);
	ps->array = NULL;//��ֹҰָ��
	ps->size = ps->capacity = 0;
}
//β��
void SeqListPushBack(SL* ps, SLDataType x) {
	assert(ps);
	SeqListCheckCapacity(ps);
	ps->size++;
	ps->array[ps->size - 1] = x;
}
//βɾ
void SeqListPopBack(SL* ps) {
	assert(ps);
	if (ps->size != 0)
		ps->size--;
}
//ͷ��
void SeqListPushFront(SL* ps, SLDataType x) {
	assert(ps);
	SeqListCheckCapacity(ps);
	ps->size++;
	int end = ps->size - 1;
	while (end >= 1) {
		ps->array[end] = ps->array[end - 1];
		end--;
	}
	ps->array[ps->size - 1] = x;
}
//ͷɾ
void SeqListPopFront(SL* ps) {
	assert(ps);
	size_t start = 0;
	while (start < ps->size) {
		ps->array[start] = ps->array[start + 1];
		start++;
	}
	ps->size--;
}
//����
int SeqListFind(SeqList* ps, SLDataType x) {
	assert(ps);
	int start = 0;
	int end = ps->size;
	int middle = ps->size / 2;
	while (start != end) {
		if (ps->array[middle] == x) {
			return middle;
		}
		else if (ps->array[middle] > x) {
			end = middle;
			middle = (end + start) / 2;
		}
		else {
			start = middle;
			middle = (start + end) / 2;
		}
	}
	return -1;
}
//�м����
void SeqListInsert(SeqList* ps, size_t pos, SLDataType x) {
	assert(ps);
	assert(ps->size > pos && pos > 0);
	SeqListCheckCapacity(ps);
	ps->size++;
	size_t end = ps->size - 1;
	while (end >= pos) {
		ps->array[end + 1] = ps->array[end];
		end--;
	}
	ps->array[pos] = x;
}
//�м�ɾ��
void SeqListErase(SeqList* ps, size_t pos) {
	assert(ps);
	assert(ps->size > pos && pos > 0);
	size_t middle = pos + 1;
	while (middle < ps->size) {
		ps->array[middle - 1] = ps->array[middle];
		middle++;
	}
	ps->size--;
}