#define _CRT_SECURE_NO_WARNINGS 1

#include "Queue.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

void InitiQueue(Queue* pq) {
	assert(pq);//得是有效的指针
	pq->phead = NULL;
	pq->ptail = NULL;
	pq->size = 0;
}


//入队
void QueuePush(Queue* pq, Qdatatype elem) {
	assert(pq);

	QNode* newnode = (QNode*)malloc(sizeof(QNode));
	newnode->val = elem;
	newnode->next = NULL;

	if (pq->phead == NULL) {//空队列
		pq->phead = pq->ptail = newnode;
	}
	else {
		pq->ptail->next = newnode;
		pq->ptail = newnode;
	}

	pq->size++;
}

//出队
void QueuePop(Queue* pq) {
	assert(pq);

	assert(!Is_empty(pq));//不能为空

	//注意当只有一个元素的时候 只free掉了phead这样 ptail会是一个野指针
	if (pq->phead->next == NULL) {
		free(pq->phead);
		
		pq->phead = pq->ptail = NULL;

		pq->size--;

		return;
	}

	QNode* tmp = pq->phead;
	pq->phead = tmp->next;
	free(tmp);//头删

	pq->size--;
}

//返回队尾元素
Qdatatype QueueBack(Queue* pq) {
	assert(pq);

	assert(!Is_empty(pq));
	
	return pq->ptail->val;
}

//返回队头元素
Qdatatype QueueFront(Queue* pq) {
	assert(pq);

	assert(!Is_empty(pq));
	
	return pq->phead->val;
}

//判断队空
bool Is_empty(Queue* pq) {
	assert(pq);
	
	return pq->size == 0;
}

//返回队长
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

		if (pq->phead == pq->ptail) {//只有一个节点时 别忘了free ptail
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
//	}//往不为空的队列push
//}
//
//int myStackPop(MyStack* obj) {
//	assert(obj);
//
//	assert(!myStackEmpty(obj)); // 不能为空
//
//	Queue* Emptyqueue = &obj->q1;
//	Queue* Nonemptyqueue = &obj->q2;
//
//	if (!Is_empty(Emptyqueue)) {
//		Emptyqueue = &obj->q2;
//		Nonemptyqueue = &obj->q1;
//	} // 此时empty是空队列那个不是
//
//	// 先将不为空的队列的元素剩一个导入到空队列里去 再把剩下那个元素Pop掉
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
//	// } // 此时empty是空队
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



