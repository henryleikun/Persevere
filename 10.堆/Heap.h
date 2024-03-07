#define _CRT_SECURE_NO_WARNINGS 1
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

//堆是利用顺序表来实现的  但其本质逻辑是完全二叉树
//这里实现一个小堆

typedef int Hpdatatype;

typedef struct Heap {
	Hpdatatype* arr;
	int size;
	int capacity;
}Heap;




void HeapInit(Heap* hp);

// 堆的构建
void HeapCreate(Heap* hp, Hpdatatype* a, int n);
//向该函数传n个数据 让其成堆 

// 堆的销毁
void HeapDestory(Heap* hp);

//向上调整 往上和自己的父节点比大小
void AdjustUp(Hpdatatype* heap, int child);

//向下调整 往下和自己的两个孩子里的较大/小者比大小
void AdjustDown(Hpdatatype* heap, int size, int parent);

// 堆的插入
void HeapPush(Heap* hp, Hpdatatype x);

// 堆的删除
void HeapPop(Heap* hp);

// 取堆顶的数据
Hpdatatype HeapTop(Heap* hp);

// 堆的数据个数
int HeapSize(Heap* hp);

// 堆的判空
bool HeapEmpty(Heap* hp);

void Swap(Hpdatatype* a, Hpdatatype* b);

