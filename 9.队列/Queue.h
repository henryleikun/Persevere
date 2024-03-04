#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdbool.h>

//队列 最好使用链表来实现 Fisrt in First out

typedef int Qdatatype;

typedef struct QNode {//定义队列的每个结点
	Qdatatype val;
	struct QNode* next;//C语言必须加+struct
}QNode;

//考虑到 单链表队列头删尾插的效率 这里要使用两个指针phead ptail 且想要记录队列的长度
//在实现链表的时候 只需要定义一个结点结构体 利用指向链表的头指针这一个参数 来对链表
//进行操作 而这里 可以类比栈 栈是由顺序表和容量又封装成一个结构体来实现栈
//队列就要将指向队列头和尾还有长度来封装成一个队列数据结构

typedef struct Queue {
	QNode* phead;
	QNode* ptail;
	int size;
}Queue;
//这样将指向队列的指针封装起来 传参只需传结构体指针 避免了使用二级指针来指向队列
//因为是通过结构体指针来操控指向队列的指针 这样就不会存在指向队列指针的副本的情况
//当队列Queue一创建 这两个指针就是直接被操控的


//下面实现相关的标准方法

void InitiQueue(Queue* pq);

void DestroyQueue(Queue* pq);

//入队
void QueuePush(Queue* pq, Qdatatype elem);

//出队
void QueuePop(Queue* pq);

//返回队尾元素
Qdatatype QueueBack(Queue* pq);

//返回队头元素
Qdatatype QueueFront(Queue* pq);

//判断队空
bool Is_empty(Queue* pq);

//返回队长
int Queuesize(Queue* pq);



//两个队列实现一个栈
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


