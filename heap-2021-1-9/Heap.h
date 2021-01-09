//向上调整--插入数据
//向下调整--排序、删除数据
//时间复杂度

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

typedef int HPDataType;
typedef struct Heap {
	HPDataType* _a;
	int _size;
	int _capacity;
}Heap;

//堆的构建
void HeapCreate(Heap* hp, HPDataType* a, int n);
//向下调整
void AdjustDown(HPDataType* a, int n, int root);
//向上调整
void AdjustUp(HPDataType* a,int n, int child);
//堆的销毁
void HeapDestory(Heap* hp);
//堆的插入
void HeapPush(Heap* hp, HPDataType x);
//堆的删除
void HeapPop(Heap* hp);
//取堆顶的数据
HPDataType HeapTop(Heap* hp);
//堆数据个数
int HeapSize(Heap* hp);
//堆的判空
int HeapEmpty(Heap* hp);
//交换数据
void Swap(HPDataType* t1, HPDataType* t2);
//堆数组进行堆排序
void HeapSort(int* a, int n);
//TopK问题
void TestTopK(Heap* hp, int k);
void PrintTopK(Heap* hp, int n, int k);
