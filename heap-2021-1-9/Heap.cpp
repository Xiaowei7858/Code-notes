
#include"Heap.h"

//�ѵĹ���
void HeapCreate(Heap* hp, HPDataType* a, int n)
{
	hp->_a = (HPDataType*)malloc(sizeof(HPDataType) * n);
	//void *memcpy(void *destin, void *source, unsigned n);
	assert(hp->_a);
	memcpy(hp->_a, a, sizeof(HPDataType) * n);
	hp->_size = n;
	hp->_capacity = n;
	//���µ��������ӷ�Ҷ�ӽ�㿪ʼ������С��
	for (int i = (n - 2) / 2; i >= 0; --i) {
		AdjustDown(hp->_a,hp->_size,i);
	}
}
//���µ���
void AdjustDown(HPDataType* a, int n, int root) {
	int parent = root;
	int child = parent * 2 + 1;
	while (child < n) {
		//�ҳ���С�ĺ���
		if (child + 1 < n && a[child] > a[child + 1]) {
			child++;
		}
		//�жϸ��ڵ��Ƿ���Ҫ����
		if (a[parent] > a[child]) {
			Swap(&a[parent], &a[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else {
			break;
		}
	}
}
//���ϵ���
void AdjustUp(HPDataType* a, int n, int child) {
	int parent = (child - 1) / 2;
	//parent > 0 �Ǵ��
	while (child > 0) {
		if (a[parent] > a[child]) {
			Swap(&a[parent], &a[child]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else {
			break;
		}
	}
}
//�ѵ�����
void HeapDestory(Heap* hp) {
	assert(hp);
	free(hp->_a);
	hp->_a = NULL;
	hp->_capacity = hp->_size = 0;
}
//�ѵĲ���
void HeapPush(Heap* hp, HPDataType x) {
	assert(hp);
	if (hp->_size == hp->_capacity) {
		HPDataType* temp = (HPDataType*)realloc(hp->_a, sizeof(HPDataType) * hp->_capacity * 2);
		assert(temp);
		hp->_a = temp;
		hp->_capacity *= 2;
	}
	hp->_a[hp->_size++] = x;
	//������--���ϵ���
	AdjustUp(hp->_a, hp->_size, hp->_size - 1);
}
//�ѵ�ɾ��
void HeapPop(Heap* hp) {
	assert(hp);
	assert(hp->_size);
	Swap(&hp->_a[0], &hp->_a[hp->_size - 1]);
	hp->_size--;
	AdjustDown(hp->_a, hp->_size, 0);
}
//ȡ�Ѷ�������
HPDataType HeapTop(Heap* hp) {
	assert(hp);
	assert(hp->_size);
	return hp->_a[0];
}
//�����ݸ���
int HeapSize(Heap* hp) {
	assert(hp);
	return hp->_size;
}
//�ѵ��п�
int HeapEmpty(Heap* hp) {
	assert(hp);
	return hp->_size == 0 ? 1 : 0;
}
//��������
void Swap(HPDataType* t1, HPDataType* t2) {
	HPDataType temp = *t1;
	*t1 = *t2;
	*t2 = temp;
}
//��������ж�����
void HeapSort(int* a, int n) {
	
	//����
	for (int i = (n - 2) / 2; i >= 0; --i) {
		AdjustDown(a, n, i);
	}
	//ʱ�临�Ӷȣ�O��N*logN��
	//�ؽ���һ����Ҫn-1��ѭ����ÿ��ѭ���ıȽϴ���Ϊlog(i)�������Ϊ��log2+log3+��+log(n-1)+log(n)��log(n!)��
	//���µ���,������
	int end = n - 1;
	while (end > 0) {
		Swap(&a[0], &a[end]);
		AdjustDown(a, end, 0);
		end--;
	}
}
//TopK����
void TestTopK(Heap* hp, int k) {
	//ǰkС������
	//ʱ�临�Ӷ� O (K*logN)
	while (k) {
		HeapPop(hp);
		k--;
	}
}
void PrintTopK(Heap* hp, int n, int k) {
	while (k) {
		printf("%d ",hp->_a[n - k]);
		k--;
	}
}