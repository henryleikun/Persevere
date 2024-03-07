#define _CRT_SECURE_NO_WARNINGS 1
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

//��������˳�����ʵ�ֵ�  ���䱾���߼�����ȫ������
//����ʵ��һ��С��

typedef int Hpdatatype;

typedef struct Heap {
	Hpdatatype* arr;
	int size;
	int capacity;
}Heap;




void HeapInit(Heap* hp);

// �ѵĹ���
void HeapCreate(Heap* hp, Hpdatatype* a, int n);
//��ú�����n������ ����ɶ� 

// �ѵ�����
void HeapDestory(Heap* hp);

//���ϵ��� ���Ϻ��Լ��ĸ��ڵ�ȴ�С
void AdjustUp(Hpdatatype* heap, int child);

//���µ��� ���º��Լ�������������Ľϴ�/С�߱ȴ�С
void AdjustDown(Hpdatatype* heap, int size, int parent);

// �ѵĲ���
void HeapPush(Heap* hp, Hpdatatype x);

// �ѵ�ɾ��
void HeapPop(Heap* hp);

// ȡ�Ѷ�������
Hpdatatype HeapTop(Heap* hp);

// �ѵ����ݸ���
int HeapSize(Heap* hp);

// �ѵ��п�
bool HeapEmpty(Heap* hp);

void Swap(Hpdatatype* a, Hpdatatype* b);

