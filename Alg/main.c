#include <stdio.h>
#include <math.h>

void Merge(int list1[], int left, int mid, int right) {
	int b1 = left;
	int e1 = mid;
	int b2 = mid + 1;
	int e2 = right;
	int list_sorted[10];
	int index = 0;

	while (b1 <= e1 && b2 <= e2) {
		if (list1[b1] < list1[b2]) {
			list_sorted[index] = list1[b1];
			b1++;
			index++;
		}
		else {
			list_sorted[index] = list1[b2];
			b2++;
			index++;
		}
	}

	while (b1 <= e1) {
		list_sorted[index] = list1[b1];
		b1++;
		index++;
	}

	while (b2 <= e2) {
		list_sorted[index] = list1[b2];
		b2++;
		index++;
	}

	for (int i = left; i <= right; i++) {
		list1[i] = list_sorted[i - left];
	}
	
	printf("합병 :[");
	for (int i = left; i < mid + 1; i++)
		printf(" %d ", list1[i]);
	printf("] [");
	for (int i = mid + 1; i < right + 1; i++)
		printf(" %d ", list1[i]);
	printf("]\n");
}

void MergeSort(int list1[], int left, int right) {
	if (left < right)
	{
		int mid = floor((left + right) / 2);
		
		printf("분할 :[");
		for (int i = left; i < mid + 1; i++)
			printf(" %d ", list1[i]);
		printf("] [");
		for (int i = mid + 1; i < right + 1; i++)
			printf(" %d ", list1[i]);
		printf("]\n");
		MergeSort(list1, left, mid);
		MergeSort(list1, mid + 1, right);
		Merge(list1, left, mid, right);
	}
}
void swap(int* x, int* y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

int partition(int list2[], int left, int right) {
	int p = floor((left + right) / 2);
	swap(list2[left], list2[p]); 
	int pivot = list2[left];
	int i = left + 1;
	int j = right;
	while (i < j) {
		while (i < right && list2[i] < pivot) i++;
		while (j > left + 1 && list2[j] > pivot) j--;
		if (i < j) swap(list2[i], list2[j]);
	}
	swap(list2[left], list2[j]);
	return j;
}

void QuickSort(int list2[], int left, int right) {
	if (left < right) {
		int p = partition(list2, left, right);
		QuickSort(list2, left, p - 1);
		QuickSort(list2, p + 1, right);
	}
}



void  main()
{
	int list1[10] = { 1,7,4,8,3,5,0,9,2,6 };
	int list2[10] = { 1,7,4,8,3,5,0,9,2,6 };
	
	printf("<<<<<< 합병 정렬 시작 >>>>>>\n");
	printf("기존 :[");
	for (int i = 0; i < 10; i++)
	{
		printf(" %d ", list1[i]);
	}
	printf("]\n");

	MergeSort(list1, 0, 9);

	printf("결과 :[");
	for (int i = 0; i < 10; i++)
	{
		printf(" %d ", list1[i]);
	}
	printf("]\n");
	printf("<<<<<< 합병 정렬 종료 >>>>>>\n");
}
