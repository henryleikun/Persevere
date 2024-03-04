#define _CRT_SECURE_NO_WARNINGS 1

#include "Queue.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

void InitiQueue(Queue* pq) {
	assert(pq);//������Ч��ָ��
	pq->phead = NULL;
	pq->ptail = NULL;
	pq->size = 0;
}


//���
void QueuePush(Queue* pq, Qdatatype elem) {
	assert(pq);

	QNode* newnode = (QNode*)malloc(sizeof(QNode));
	newnode->val = elem;
	newnode->next = NULL;

	if (pq->phead == NULL) {//�ն���
		pq->phead = pq->ptail = newnode;
	}
	else {
		pq->ptail->next = newnode;
		pq->ptail = newnode;
	}

	pq->size++;
}

//����
void QueuePop(Queue* pq) {
	assert(pq);

	assert(!Is_empty(pq));//����Ϊ��

	//ע�⵱ֻ��һ��Ԫ�ص�ʱ�� ֻfree����phead���� ptail����һ��Ұָ��
	if (pq->phead->next == NULL) {
		free(pq->phead);
		
		pq->phead = pq->ptail = NULL;

		pq->size--;

		return;
	}

	QNode* tmp = pq->phead;
	pq->phead = tmp->next;
	free(tmp);//ͷɾ

	pq->size--;
}

//���ض�βԪ��
Qdatatype QueueBack(Queue* pq) {
	assert(pq);

	assert(!Is_empty(pq));
	
	return pq->ptail->val;
}

//���ض�ͷԪ��
Qdatatype QueueFront(Queue* pq) {
	assert(pq);

	assert(!Is_empty(pq));
	
	return pq->phead->val;
}

//�ж϶ӿ�
bool Is_empty(Queue* pq) {
	assert(pq);
	
	return pq->size == 0;
}

//���ضӳ�
int Queuesize(Queue* pq) {
	assert(pq);

	return pq->size;
}

void DestroyQueue(Queue* pq) {
	assert(pq);

	if (Is_empty(pq))
		return;

	QNode* cur = pq->phead;

	while (cur) {

		if (pq->phead == pq->ptail) {//ֻ��һ���ڵ�ʱ ������free ptail
			free(pq->phead);

			pq->phead = pq->ptail = NULL;
			return;
		}

		cur = cur->next;
		free(pq->phead);

		pq->phead = cur;
	}
}
//
//MyStack* myStackCreate() {
//	MyStack* mystack = (MyStack*)malloc(sizeof(MyStack));
//
//	InitiQueue(&mystack->q1);
//	InitiQueue(&mystack->q2);
//
//	return mystack;
//}
//
//void myStackPush(MyStack* obj, int x) {
//	assert(obj);
//	if (!Is_empty(&obj->q1)) {
//		QueuePush(&obj->q1, x);
//	}
//	else {
//		QueuePush(&obj->q2, x);
//	}//����Ϊ�յĶ���push
//}
//
//int myStackPop(MyStack* obj) {
//	assert(obj);
//
//	assert(!myStackEmpty(obj)); // ����Ϊ��
//
//	Queue* Emptyqueue = &obj->q1;
//	Queue* Nonemptyqueue = &obj->q2;
//
//	if (!Is_empty(Emptyqueue)) {
//		Emptyqueue = &obj->q2;
//		Nonemptyqueue = &obj->q1;
//	} // ��ʱempty�ǿն����Ǹ�����
//
//	// �Ƚ���Ϊ�յĶ��е�Ԫ��ʣһ�����뵽�ն�����ȥ �ٰ�ʣ���Ǹ�Ԫ��Pop��
//	while (Queuesize(Nonemptyqueue) > 1) {
//		QueuePush(Emptyqueue, QueueFront(Nonemptyqueue));
//		QueuePop(Nonemptyqueue);
//	}
//
//	int ret = QueueFront(Nonemptyqueue);
//	QueuePop(Nonemptyqueue);
//
//	return ret;
//}
//
//int myStackTop(MyStack* obj) {
//	assert(obj);
//	assert(!myStackEmpty(obj));
//
//	// Queue* Emptyqueue = &obj->q1;
//	// Queue* Nonemptyqueue = &obj->q2;
//
//	// if (!Is_empty(Emptyqueue)) {
//	//     Emptyqueue = &obj->q2;
//	//     Nonemptyqueue = &obj->q1;
//	// } // ��ʱempty�ǿն�
//
//	if (!Is_empty(&obj->q1)) {
//		return QueueBack(&obj->q1);
//	}
//	else {
//		return QueueBack(&obj->q2);
//	}
//
//}
//
//bool myStackEmpty(MyStack* obj) {
//	return Is_empty(&obj->q1) && Is_empty(&obj->q2);
//}
//
//void myStackFree(MyStack* obj) {
//	DestroyQueue(&obj->q1);
//	DestroyQueue(&obj->q2);
//
//	free(obj);
//}



