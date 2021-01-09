
#include"Heap.h"

//堆的构建
void HeapCreate(Heap* hp, HPDataType* a, int n)
{
	hp->_a = (HPDataType*)malloc(sizeof(HPDataType) * n);
	//void *memcpy(void *destin, void *source, unsigned n);
	assert(hp->_a);
	memcpy(hp->_a, a, sizeof(HPDataType) * n);
	hp->_size = n;
	hp->_capacity = n;
	//向下调整法，从非叶子结点开始，建立小堆
	for (int i = (n - 2) / 2; i >= 0; --i) {
		AdjustDown(hp->_a,hp->_size,i);
	}
}
//向下调整
void AdjustDown(HPDataType* a, int n, int root) {
	int parent = root;
	int child = parent * 2 + 1;
	while (child < n) {
		//找出最小的孩子
		if (child + 1 < n && a[child] > a[child + 1]) {
			child++;
		}
		//判断父节点是否需要调整
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
//向上调整
void AdjustUp(HPDataType* a, int n, int child) {
	int parent = (child - 1) / 2;
	//parent > 0 是错的
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
//堆的销毁
void HeapDestory(Heap* hp) {
	assert(hp);
	free(hp->_a);
	hp->_a = NULL;
	hp->_capacity = hp->_size = 0;
}
//堆的插入
void HeapPush(Heap* hp, HPDataType x) {
	assert(hp);
	if (hp->_size == hp->_capacity) {
		HPDataType* temp = (HPDataType*)realloc(hp->_a, sizeof(HPDataType) * hp->_capacity * 2);
		assert(temp);
		hp->_a = temp;
		hp->_capacity *= 2;
	}
	hp->_a[hp->_size++] = x;
	//调整堆--向上调整
	AdjustUp(hp->_a, hp->_size, hp->_size - 1);
}
//堆的删除
void HeapPop(Heap* hp) {
	assert(hp);
	assert(hp->_size);
	Swap(&hp->_a[0], &hp->_a[hp->_size - 1]);
	hp->_size--;
	AdjustDown(hp->_a, hp->_size, 0);
}
//取堆顶的数据
HPDataType HeapTop(Heap* hp) {
	assert(hp);
	assert(hp->_size);
	return hp->_a[0];
}
//堆数据个数
int HeapSize(Heap* hp) {
	assert(hp);
	return hp->_size;
}
//堆的判空
int HeapEmpty(Heap* hp) {
	assert(hp);
	return hp->_size == 0 ? 1 : 0;
}
//交换数据
void Swap(HPDataType* t1, HPDataType* t2) {
	HPDataType temp = *t1;
	*t1 = *t2;
	*t2 = temp;
}
//堆数组进行堆排序
void HeapSort(int* a, int n) {
	
	//建堆
	for (int i = (n - 2) / 2; i >= 0; --i) {
		AdjustDown(a, n, i);
	}
	//时间复杂度：O（N*logN）
	//重建堆一共需要n-1次循环，每次循环的比较次数为log(i)，则相加为：log2+log3+…+log(n-1)+log(n)≈log(n!)。
	//向下调整,堆排序
	int end = n - 1;
	while (end > 0) {
		Swap(&a[0], &a[end]);
		AdjustDown(a, end, 0);
		end--;
	}
}
//TopK问题
void TestTopK(Heap* hp, int k) {
	//前k小的数字
	//时间复杂度 O (K*logN)
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