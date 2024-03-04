#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdbool.h>

//���� ���ʹ��������ʵ�� Fisrt in First out

typedef int Qdatatype;

typedef struct QNode {//������е�ÿ�����
	Qdatatype val;
	struct QNode* next;//C���Ա����+struct
}QNode;

//���ǵ� ���������ͷɾβ���Ч�� ����Ҫʹ������ָ��phead ptail ����Ҫ��¼���еĳ���
//��ʵ�������ʱ�� ֻ��Ҫ����һ�����ṹ�� ����ָ�������ͷָ����һ������ ��������
//���в��� ������ �������ջ ջ����˳���������ַ�װ��һ���ṹ����ʵ��ջ
//���о�Ҫ��ָ�����ͷ��β���г�������װ��һ���������ݽṹ

typedef struct Queue {
	QNode* phead;
	QNode* ptail;
	int size;
}Queue;
//������ָ����е�ָ���װ���� ����ֻ�贫�ṹ��ָ�� ������ʹ�ö���ָ����ָ�����
//��Ϊ��ͨ���ṹ��ָ�����ٿ�ָ����е�ָ�� �����Ͳ������ָ�����ָ��ĸ��������
//������Queueһ���� ������ָ�����ֱ�ӱ��ٿص�


//����ʵ����صı�׼����

void InitiQueue(Queue* pq);

void DestroyQueue(Queue* pq);

//���
void QueuePush(Queue* pq, Qdatatype elem);

//����
void QueuePop(Queue* pq);

//���ض�βԪ��
Qdatatype QueueBack(Queue* pq);

//���ض�ͷԪ��
Qdatatype QueueFront(Queue* pq);

//�ж϶ӿ�
bool Is_empty(Queue* pq);

//���ضӳ�
int Queuesize(Queue* pq);



//��������ʵ��һ��ջ
//typedef struct {
//    Queue q1;
//    Queue q2;
//} MyStack;
//
//bool myStackEmpty(MyStack* obj);
//
//MyStack* myStackCreate();
//
//void myStackPush(MyStack* obj, int x);
//
//int myStackPop(MyStack* obj);
//
//int myStackTop(MyStack* obj);
//
//void myStackFree(MyStack* obj);


