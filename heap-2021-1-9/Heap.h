//���ϵ���--��������
//���µ���--����ɾ������
//ʱ�临�Ӷ�

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

//�ѵĹ���
void HeapCreate(Heap* hp, HPDataType* a, int n);
//���µ���
void AdjustDown(HPDataType* a, int n, int root);
//���ϵ���
void AdjustUp(HPDataType* a,int n, int child);
//�ѵ�����
void HeapDestory(Heap* hp);
//�ѵĲ���
void HeapPush(Heap* hp, HPDataType x);
//�ѵ�ɾ��
void HeapPop(Heap* hp);
//ȡ�Ѷ�������
HPDataType HeapTop(Heap* hp);
//�����ݸ���
int HeapSize(Heap* hp);
//�ѵ��п�
int HeapEmpty(Heap* hp);
//��������
void Swap(HPDataType* t1, HPDataType* t2);
//��������ж�����
void HeapSort(int* a, int n);
//TopK����
void TestTopK(Heap* hp, int k);
void PrintTopK(Heap* hp, int n, int k);
