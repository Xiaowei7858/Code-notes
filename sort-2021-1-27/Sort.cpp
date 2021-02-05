
#include"Sort.h"

// ��������
void InsertSort(int* a, int n) {
	assert(a);

	//end+1�����ݲ���[0,end]����������
	for (int i = 0; i <= n; ++i) {
		int end = i;
		int temp = a[end + 1];
		while (end >= 0) {
			if (a[end] > temp) {
				a[end + 1] = a[end];
				end--;
			}
			else {
				break;
			}
		}
		a[end + 1] = temp;
	}
}

// ϣ������ʹ�ò�������ķ���������ʹ�������򣬼�С���Ӷ� O(N^1.3 - N^2)
//1��Ԥ����  2��ֱ�Ӳ�������
void ShellSort(int* a, int n) {
	assert(a);
	int gap = n;

	while (gap > 1) {
		gap = gap/3 + 1;//��֤���һ��Ϊ1
		for (int i = 0; i < n - gap; ++i) {
			//���鲢��
			int end = i;
			int temp = a[end + gap];
			while (end >= 0) {
				if (a[end] > temp) {
					a[end + gap] = a[end];
					end -= gap;
				}
				else {
					break;
				}
			}
			a[end + gap] = temp;
		}
	}

}

// ѡ������
void Swap(int* p1, int* p2) {
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}
void SelectSort(int* a, int n) {
	int begin = 0; int end = n - 1;
	int maxi, mini;

	while (begin < end) {
		maxi = mini = begin;
		for (int i = begin + 1; i <= end; ++i) {
			if (a[i] < a[mini]) {
				mini = i;
			}
			if (a[i] > a[maxi]) {
				maxi = i;
			}
		}

		Swap(&a[begin], &a[mini]);
		if (begin = maxi) {
			//���begin��maxiλ���ص�������Ҫ�޸�maxi��λ��
			maxi = mini;
		}
		Swap(&a[end], &a[maxi]);

		begin++;
		end--;
	}
}

// ������
void AdjustDwon(int* a, int n, int root) {
	int parent = root;
	int child = parent * 2 + 1;
	while (child < n) {
		if (child + 1 < n && a[child] < a[child + 1]) {
			child++;
		}
		if (a[parent] < a[child]) {
			Swap(&a[parent], &a[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else {
			break;
		}
	}
}
//O(N*logN)
void HeapSort(int* a, int n) {
	for (int i = (n - 1 - 1) / 2; i >= 0; --i) {
		AdjustDwon(a, n, i);
	}

	int end = n - 1;
	while (end > 0) {
		Swap(&a[0], &a[end]);
		AdjustDwon(a, end, 0);
		end--;
	}
}

// ð������
void BubbleSort(int* a, int n) {
	int end = n;
	while (end > 0) {
		int exchange = 0;
		for (int i = 1; i < n; ++i) {
			if (a[i - 1] > a[i]) {
				Swap(&a[i - 1], &a[i]);
				exchange = 1;
			}
		}

		//��һ��ð�ݱȽ�Ϊ�������������������������
		if (exchange == 0) {
			break;
		}
	}
}

// ��������ݹ�ʵ��
//����ȡ��:��֤�м�ֵ��end��λ��
int GetMidIndex(int* a, int begin, int end) {
	int mid = ((end - begin) >> 1) + begin;

	//a[begin]<a[end]    ����λ�ã�
	if (a[begin] > a[end]) {
		Swap(&a[begin], &a[end]);
	}
	if (a[mid] < a[begin]) {
		Swap(&a[mid], &a[begin]);
	}
	if (a[end] > a[mid]) {
		Swap(&a[end], &a[mid]);
	}
}
// ��������hoare�汾
int PartSort1(int* a, int left, int right) {
	int begin = left, end = right;
	int index = end;

	while (begin < end) {
		//�Ҵ�
		while (begin < end && a[begin] <= a[index]) {
			begin++;
		}
		//��С
		while (begin < end && a[end] >= a[index]) {
			end--;
		}

		Swap(&a[begin], &a[end]);
	}

	Swap(&a[begin], &a[index]);
	return  begin;
}

// ���������ڿӷ�
int PartSort2(int* a, int left, int right) {
	int begin = left, end = right;
	int index = end;
	int value = a[end];

	while (begin < end) {
		while (begin < end && a[begin] <= value) {
			begin++;
		}
		a[index] = a[begin];
		index = begin;

		while (begin < end && a[end] >= value) {
			end--;
		}
		a[index] = a[end];
		index = end;
	}

	a[index] = value;
	return index;
}

// ��������ǰ��ָ�뷨
int PartSort3(int* a, int left, int right) {
	int cur = left, prev = left - 1;
	int index = right;

	while (cur < right) {
		if (a[cur] < a[index] && ++prev != cur) {
			Swap(&a[cur], &a[prev]);
		}

		cur++;
	}

	Swap(&a[++prev], &a[index]);

	return prev;
}
void QuickSort(int* a, int left, int right) {
	if (left >= right)
		return;

	int div = PartSort1(a, left, right);
	QuickSort(a, left, div - 1);
	QuickSort(a, div + 1, right);
}

// �������� �ǵݹ�ʵ��
void QuickSortNonR(int* a, int left, int right) {

}

// �鲢����ݹ�ʵ��
void _MergeArr(int* a, int begin1, int end1, int begin2, int end2, int* temp) {
	int index = begin1, left = begin1, right = end2;

	while (begin1 < end1 && begin2 < end2) {
		if (a[begin1] < a[begin2]) {
			temp[index++] = a[begin1++];
		}
		else {
			temp[index++] = a[begin2++];
		}
	}
	while (begin1 < end1) {
		temp[index++] = a[begin1++];
	}
	while (begin2 < end2) {
		temp[index++] = a[begin2++];
	}

	//������ԭ����
	for (int i = left; i <= right; i++) {
		a[i] = temp[i];
	}

}
void _MergeSort(int* a, int left, int right, int*temp) {
	if (left >= right)
		return;

	int mid = (right - left) >> 1 + left;
	_MergeSort(a, left, mid, temp);
	_MergeSort(a, mid + 1, right, temp);

	//�鲢[left,right]
	_MergeArr(a, left, mid, mid + 1, right, temp);
}
void MergeSort(int* a, int n) {
	assert(a);
	int* temp = (int*)malloc(sizeof(int) * n);

	_MergeSort(a, 0, n, temp);
	int i = 0;
	while (n) {
		a[i++] = temp[i++];
	}
	free(temp);
}

// �鲢����ǵݹ�ʵ��
void MergeSortNonR(int* a, int n) {

}

// ��������
void CountSort(int* a, int n) {

}