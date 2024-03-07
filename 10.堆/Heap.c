#define _CRT_SECURE_NO_WARNINGS 1

#include "Heap.h"


// 堆的构建
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

// 堆的销毁
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

//向上调整 push后
void AdjustUp(Hpdatatype* heap, int child) {
	assert(heap);//数组是有效的

	int parent = (child - 1) / 2;

	while (child>0) {//小堆
		if (heap[parent] > heap[child]) {//小的上移
			Swap(&heap[parent], &heap[child]);

			child = parent;
			parent = (child - 1) / 2;
		}
		else {
			break;
		}
	}
}

//向下调整 pop后
void AdjustDown(Hpdatatype* heap, int size, int parent) {
	assert(heap);

	//小堆 我要和两个儿子的较小者比 先找两个儿子的较小者
	int child = parent * 2 + 1;//默认左儿子小
	while (child < size) {
		if ((child+1)<size && heap[child] > heap[child + 1]) {
			child++;
		}

		if (heap[child] < heap[parent]) {
			Swap(&heap[child], &heap[parent]);
			parent = child;
			child = parent * 2 + 1;//默认左儿子大
		}
		else
			break;
	}
}

// 堆的插入
void HeapPush(Heap* hp, Hpdatatype x) {
	assert(hp);

	//空或者满进行扩容
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

// 堆的删除
void HeapPop(Heap* hp) {
	//删除堆顶元素 如果采用和顺序表一样的方法 即覆盖 将后续元素前移
	//这样会导致后后面的父子关系混乱 破坏堆的结构 很大可能不是堆了
	//这里采用 向下调整 怎么个方法呢 让堆顶元素和堆最后一个元素交换 size-- 屏蔽掉最后一个元素
	//然后让刚才到堆顶的元素向下调整 成为一个堆 向上/下调整的前提就是调整的对象是个堆
	//而堆顶元素下面一个左子树一个右子树都是堆(除开屏蔽的元素)
	assert(hp);
	assert(!HeapEmpty(hp));

	Swap(&hp->arr[0], &hp->arr[hp->size - 1]);
	hp->size--;
	AdjustDown(hp->arr, hp->size, 0);
}

// 取堆顶的数据
Hpdatatype HeapTop(Heap* hp) {
	assert(hp);
	assert(!HeapEmpty(hp));
	
	return hp->arr[0];
}

// 堆的数据个数
int HeapSize(Heap* hp) {
	assert(hp);

	return hp->size;
}

// 堆的判空
bool HeapEmpty(Heap* hp) {
	assert(hp);

	return hp->size == 0;
}


