
#include"Heap.h"


int main() {
	int a[] = { 27, 15, 19, 18, 28, 34, 65, 49, 25, 37 };
	//HeapSort(a, sizeof(a) / sizeof(HPDataType));

	Heap hp;
	HeapCreate(&hp, a, sizeof(a) / sizeof(HPDataType));
	//HeapPush(&hp, 13);
	TestTopK(&hp, 5);
	PrintTopK(&hp, sizeof(a) / sizeof(HPDataType), 5);

	HeapDestory(&hp);
	return 0;
}