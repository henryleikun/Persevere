#define _CRT_SECURE_NO_WARNINGS 1

#include "Heap.h"

int main() {
	int arr[7] = { 5,9,8,7,4,1,2 };
	int sz = sizeof(arr) / sizeof(arr[0]);

	Heap heap;
	HeapInit(&heap);

	HeapCreate(&heap, arr, sz);

	for (int i = 0; i < sz; i++) {
		int temp = HeapTop(&heap);
		HeapPop(&heap);

		arr[i] = temp;
		printf("%d ", arr[i]);
	}

	HeapDestory(&heap);

	return 0;
}
