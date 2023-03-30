#include <stdio.h>
#include <math.h>
#include <time.h>

void Merge(int list1[], int left, int mid, int right) {
	int b1 = left;
	int e1 = mid;
	int b2 = mid + 1;
	int e2 = right;
	int list_sorted[100];
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
	
	printf("�պ� :[");
	for (int i = left; i < mid + 1; i++)
		printf(" %d ", list1[i]);
	for (int i = mid + 1; i < right + 1; i++)
		printf(" %d ", list1[i]);
	printf("]\n");
}

void MergeSort(int list1[], int left, int right) {
	if (left < right)
	{
		int mid = floor((left + right) / 2);
		
		printf("���� :[");
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
void swap(int arr[], int x, int y) {
	int temp = arr[x];
	arr[x] = arr[y];
	arr[y] = temp;
}

int partition(int list2[], int left, int right) {
	int p = floor((left + right) / 2);
	printf("�Ǻ� ���� -> index : %d / num : %d\n", p, list2[p]);
	swap(list2, left, p); 
	printf("��Ƽ�� : [");
	for (int i = left + 1; i < p + 1; i++)
	{
		printf(" %d ", list2[i]);
	}
	printf("] ");
	printf("[");
	for (int i = p + 1; i <= right; i++)
	{
		printf(" %d ", list2[i]);
	}
	printf("]\n");
	int pivot = list2[left];
	int i = left + 1;
	int j = right;
	while (i <= j) {
		while (i <= right && list2[i] <= pivot) 
			i++;
		while (list2[j] > pivot) 
			j--;
		if (i < j)
		{
			printf("��ȯ : %d <-> %d\n", list2[i], list2[j]);
			swap(list2, i, j);
		}
	}
	swap(list2, left, j);

	printf("�߰� ��� : [");
	for (int i = left; i < j; i++)
	{
		printf(" %d ", list2[i]);
	}
	printf("] [");
	for (int i = j; i <= right; i++)
	{
		printf(" %d ", list2[i]);
	}
	printf("]\n");

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
	int list1[10];
	int choice;
	int a = 1;
	int list1_size = sizeof(list1) / sizeof(int);
	srand(time(NULL));
	while (a)
	{
		for (int i = 0; i < list1_size; i++)
		{
			list1[i] = rand() % 1000;
		}
		printf("�պ� ���� -> 1\n�� ���� -> 2\n���� -> 0\n��ȣ �Է� : ");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			printf("<<<<<< �պ� ���� ���� >>>>>>\n");
			printf("���� :[");
			for (int i = 0; i < list1_size; i++)
			{
				printf(" %d ", list1[i]);
			}
			printf("]\n");

			MergeSort(list1, 0, list1_size - 1);

			printf("��� :[");
			for (int i = 0; i < list1_size; i++)
			{
				printf(" %d ", list1[i]);
			}
			printf("]\n");
			printf("<<<<<< �պ� ���� ���� >>>>>>\n");
			printf("<<<<<< ���� �ʱ�ȭ >>>>>>\n");
			break;
		case 2:
			printf("<<<<<< �� ���� ���� >>>>>>\n");
			printf("���� :[");
			for (int i = 0; i < list1_size; i++)
			{
				printf(" %d ", list1[i]);
			}
			printf("]\n");

			QuickSort(list1, 0, list1_size - 1);

			printf("��� :[");
			for (int i = 0; i < list1_size; i++)
			{
				printf(" %d ", list1[i]);
			}
			printf("]\n");
			printf("<<<<<< �� ���� ���� >>>>>>\n");
			printf("<<<<<< ���� �ʱ�ȭ >>>>>>\n");
			break;
		case 0:
			a = 0;
			printf("<<<<<< ���� >>>>>>");
			break;
		}
	}
	
	

	
}
