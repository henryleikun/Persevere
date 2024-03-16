#define _CRT_SECURE_NO_WARNINGS 1

#include "Sort.h"

void Print_arr(int* arr, int sz) {
	for (int i = 0; i < sz; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void Test_time() {
	const int N = 10000;//堆的内存很大

	int* a1 = (int*)malloc(sizeof(int) * N);
	int* a2 = (int*)malloc(sizeof(int) * N);
	int* a3 = (int*)malloc(sizeof(int) * N);
	int* a4 = (int*)malloc(sizeof(int) * N);
	int* a5 = (int*)malloc(sizeof(int) * N);
	int* a6 = (int*)malloc(sizeof(int) * N);
	int* a7 = (int*)malloc(sizeof(int) * N);

	for (int i = 0; i < N; i++) {
		a1[i] = rand();
		a2[i] = a1[i];
		a3[i] = a1[i];
		a4[i] = a1[i];
		a5[i] = a1[i];
		a6[i] = a1[i];
		a7[i] = a1[i];
	}

	int begin1 = clock();
	InsertSort(a1, N);
	int end1 = clock();

	int begin2 = clock();
	ShellSort(a2, N);
	int end2 = clock();

	int begin3 = clock();
	BubbleSort(a3, N);
	int end3 = clock();

	int begin4 = clock();
	QuickSort(a4,0,N-1);
	int end4 = clock();

	int begin5 = clock();
	HeapSort(a5, N);
	int end5 = clock();

	int begin6 = clock();
	SelectSort(a6, N);
	int end6 = clock();

	int begin7 = clock();
	MergeSort(a7, N);
	int end7 = clock();

	printf("Insert: %dms\n", end1 - begin1);
	printf("Shell: %dms\n", end2 - begin2);
	printf("Bubble: %dms\n", end3 - begin3);
	printf("Quick: %dms\n", end4 - begin4);
	printf("Heap: %dms\n", end5 - begin5);
	printf("Select: %dms\n", end6 - begin6);
	printf("Merge: %dms\n", end7 - begin7);


	free(a1);
	free(a2);
	free(a3);
	free(a4);
	free(a5);
	free(a6);
	free(a7);
}

void TestInsertsort() {
	int arr[] = { 4,1,8,9,7,2,6,3,5,0 };
	int sz = sizeof(arr) / sizeof(arr[0]);

	Print_arr(arr, sz);
	InsertSort(arr, sz);
	Print_arr(arr, sz);
}

void TestShellsort() {
	int arr[] = { 4,1,8,9,7,2,6,3,5,0 };
	int sz = sizeof(arr) / sizeof(arr[0]);

	Print_arr(arr, sz);
	ShellSort(arr, sz);
	Print_arr(arr, sz);
}

void TestBubblesort() {
	int arr[] = { 4,1,8,9,7,2,6,3,5,0 };
	int sz = sizeof(arr) / sizeof(arr[0]);

	Print_arr(arr, sz);
	BubbleSort(arr, sz);
	Print_arr(arr, sz);
}

void TestHeapsort() {
	int arr[] = { 4,1,8,9,7,2,6,3,5,0 };
	int sz = sizeof(arr) / sizeof(arr[0]);

	Print_arr(arr, sz);
	HeapSort(arr, sz);
	Print_arr(arr, sz);
}

void TestSelectsort() {
	int arr[] = { 4,1,8,9,7,2,6,3,5,0 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	
	Print_arr(arr, sz);
	SelectSort(arr, sz);
	Print_arr(arr, sz);
}

void TestQuicksort() {
	int arr[] = { 4,1,8,9,7,2,6,3,5,0 };
	int sz = sizeof(arr) / sizeof(arr[0]);

	Print_arr(arr, sz);
	QuickSort(arr, 0,sz-1);
	Print_arr(arr, sz);
}

void TestMergesort() {
	int arr[] = { 4,1,8,9,7,2,6,3,5,0 };
	int sz = sizeof(arr) / sizeof(arr[0]);

	Print_arr(arr, sz);
	MergeSort_noR(arr, sz);
	Print_arr(arr, sz);
}	


void TestCountsort() {
	int arr[] = { 4,1,8,9,7,2,6,3,5,0 };
	int sz = sizeof(arr) / sizeof(arr[0]);

	Print_arr(arr, sz);
	CountSort(arr, sz);
	Print_arr(arr, sz);
}




int main() {
	srand(time(0));

	//TestInsertsort();
	//TestShellsort();
	//TestBubblesort();
	//TestHeapsort();
	//TestSelectsort();
	//TestQuicksort();
	//TestMergesort();
	//TestCountsort();
	
	Test_time();
	return 0;
}