#define _CRT_SECURE_NO_WARNINGS 1

#include "Heap.h"


// �ѵĹ���
void HeapCreate(Heap* hp, Hpdatatype* a, int n) {
	assert(hp);

	HeapInit(hp);

	for (int i = 0; i < n; i++) {
		HeapPush(hp, a[i]);
	}
}

void HeapInit(Heap* hp) {
	hp->arr = NULL;
	hp->capacity = 0;
	hp->size = 0;
}

// �ѵ�����
void HeapDestory(Heap* hp) {
	free(hp->arr);
	hp->arr = NULL;
	hp->capacity = 0;
	hp->size = 0;
}

void Swap(Hpdatatype* a, Hpdatatype* b) {
	Hpdatatype temp = *a;
	*a = *b;
	*b = temp;
}

//���ϵ��� push��
void AdjustUp(Hpdatatype* heap, int child) {
	assert(heap);//��������Ч��

	int parent = (child - 1) / 2;

	while (child>0) {//С��
		if (heap[parent] > heap[child]) {//С������
			Swap(&heap[parent], &heap[child]);

			child = parent;
			parent = (child - 1) / 2;
		}
		else {
			break;
		}
	}
}

//���µ��� pop��
void AdjustDown(Hpdatatype* heap, int size, int parent) {
	assert(heap);

	//С�� ��Ҫ���������ӵĽ�С�߱� �����������ӵĽ�С��
	int child = parent * 2 + 1;//Ĭ�������С
	while (child < size) {
		if ((child+1)<size && heap[child] > heap[child + 1]) {
			child++;
		}

		if (heap[child] < heap[parent]) {
			Swap(&heap[child], &heap[parent]);
			parent = child;
			child = parent * 2 + 1;//Ĭ������Ӵ�
		}
		else
			break;
	}
}

// �ѵĲ���
void HeapPush(Heap* hp, Hpdatatype x) {
	assert(hp);

	//�ջ�������������
	if (hp->size == hp->capacity) {
	  int newcapacity = hp->capacity == 0 ? 4 : hp->capacity * 2;
	  Hpdatatype* tmp = (Hpdatatype*)realloc(hp->arr,sizeof(Hpdatatype) * newcapacity);

	  if (tmp == NULL) {
		  perror("realloc failed");
	  }

	  hp->arr = tmp;
	  hp->capacity = newcapacity;
	}

	hp->arr[hp->size++] = x;

	AdjustUp(hp->arr, hp->size - 1);
}

// �ѵ�ɾ��
void HeapPop(Heap* hp) {
	//ɾ���Ѷ�Ԫ�� ������ú�˳���һ���ķ��� ������ ������Ԫ��ǰ��
	//�����ᵼ�º����ĸ��ӹ�ϵ���� �ƻ��ѵĽṹ �ܴ���ܲ��Ƕ���
	//������� ���µ��� ��ô�������� �öѶ�Ԫ�غͶ����һ��Ԫ�ؽ��� size-- ���ε����һ��Ԫ��
	//Ȼ���øղŵ��Ѷ���Ԫ�����µ��� ��Ϊһ���� ����/�µ�����ǰ����ǵ����Ķ����Ǹ���
	//���Ѷ�Ԫ������һ��������һ�����������Ƕ�(�������ε�Ԫ��)
	assert(hp);
	assert(!HeapEmpty(hp));

	Swap(&hp->arr[0], &hp->arr[hp->size - 1]);
	hp->size--;
	AdjustDown(hp->arr, hp->size, 0);
}

// ȡ�Ѷ�������
Hpdatatype HeapTop(Heap* hp) {
	assert(hp);
	assert(!HeapEmpty(hp));
	
	return hp->arr[0];
}

// �ѵ����ݸ���
int HeapSize(Heap* hp) {
	assert(hp);

	return hp->size;
}

// �ѵ��п�
bool HeapEmpty(Heap* hp) {
	assert(hp);

	return hp->size == 0;
}


