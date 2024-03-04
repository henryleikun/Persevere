#define _CRT_SECURE_NO_WARNINGS 1

//���ͬһ���ǿ�ָ���ͷ����κ���
#include "Queue.h"
#include <stdio.h>

int main() {
	Queue q;
	InitiQueue(&q);

	QueuePush(&q, 1);
	QueuePush(&q, 2);
	QueuePush(&q, 3);
	QueuePush(&q, 4);
	QueuePush(&q, 5);

	while (!Is_empty(&q)) {
		printf("%d ", QueueFront(&q));
		QueuePop(&q);//ʵ��Ӧ�þ��������ó�
	}

	DestroyQueue(&q);

	return 0;
}


//int main() {
//	MyStack* obj = myStackCreate();
//
//	myStackPush(obj, 1);
//	myStackPush(obj, 2);
//	myStackPush(obj, 3);
//	myStackPush(obj, 4);
//
//	myStackPop(obj);
//
//	int val = myStackTop(obj);
//
//	printf("%d\n", val);
//
//	myStackFree(obj);
//	return 0;
//}
