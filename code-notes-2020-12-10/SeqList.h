#pragma once
//动态顺序表
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int SLDataType;
typedef struct SeqList {
	SLDataType* array;
	size_t size;//unsight int
	size_t capacity;
}SL, SeqList;

//对数据的管理，增删查改
//初始化，扩容，销毁

void SeqListInit(SL* ps);
void SeqListPrint(SL* ps);
void SeqListCheckCapacity(SL* ps);
void SeqListDestory(SL* ps);
void SeqListPushBack(SL* ps, SLDataType x);
void SeqListPopBack(SL* ps);
void SeqListPushFront(SL* ps, SLDataType x);
void SeqListPopFront(SL* ps);
int SeqListFind(SeqList* ps, SLDataType x);
void SeqListInsert(SeqList* ps, size_t pos, SLDataType x);
void SeqListErase(SeqList* ps, size_t pos);
