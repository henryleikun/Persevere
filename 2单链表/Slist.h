#define _CRT_SECURE_NO_WARNINGS 1

//本设计实现一个单向无头链表  
//链表使用比较多的就是单向无头不循环链表和 双向有头循环链表

#ifndef _SLIST_H
#define _SLIST_H

typedef int Datatype;

typedef struct ListNode {
	Datatype data;
	struct ListNode* next;
}ListNode;
//结点

//对于无头的链表在开辟新节点以及删除结点时要考虑 头指针的处理 
//所以在插入/删除函数的参数中 如果 是对头指针进行操作的话 应该传二级指针 因为你是想改变指针的指向
//（让头指针指向新的结点  可以是插入也可以是删除导致的）
//即使是一级指针 其实是指针的值 对于指针来说 这是值传递 所以 不能改变原指针的指向 对于指针指向的位置是
//地址传递 但插入操作我可能会想操作指针本身 所以 参数应搞为二级指针
//一级指针 phead反映的是 链表的第一个节点是否创建的问题(*phead ~ListNode)
// 二级指针 pphead反映的是 指向链表第一个结点的指针有没有的问题(*pphead~&ListNode)
 

//在c++linkedlist类设计里面 因为Node* head是一个public成员调用方法时一直是对这个头指针进行操作
//所以c++类中 一级指针就ok  在 那个学生信息管理系统中 没有涉及到二级指针 是因为 那是个有头链表
//在开辟新节点的时候 是对head->next进行操作 即head指向的位置操作 不是对指针本身进行操作
//所以也是一级指针  

//综上 想要对无头单向不循环链表进行操作的话  就要考虑到二级指针的问题 对函数传参的值传递和地址传递
//有更加深入的了解

//创建节点
ListNode* BuyNode(Datatype elem);



//链表的插入和删除 可以按元素来 即利用find函数去找到存储对应元素结点的地址
//找到的话 进行对应插入删除 
// 也可以按位置来进行插入和删除 对应函数的参数是一个结点的地址 接着对其操作
// 上述两种方法 为非是对于Find函数的使用范围不同 第一种是在函数内部使用Find 第二种是在函数外部
// 提前使用Find得到结点地址传入函数 这里使用后者


//任意插
void Listinsert(ListNode** pphead,ListNode* pos, Datatype elem);//这里是在pos位置的前面插
//注意要求得pos指向结点的前驱

//任意删
void Listerase(ListNode** pphead,ListNode* pos);

//尾插
void Pushback(ListNode** pphead, Datatype elem);
//利用insert函数 对应pos为NULL的情况就行

//头插
void Pushfront(ListNode** pphead, Datatype elem);


//尾删
void Popback(ListNode** pphead);


//头删
void Popfront(ListNode** pphead);


//打印
void Print(ListNode* phead);//这个一级指针就行 是对链表操作 不会对头指针操作


//查找
ListNode* Find(ListNode* phead, Datatype elem);


//修改
void  Modify(ListNode** pphead, ListNode* pos);

//销毁
void Destroy(ListNode** pphead);

#endif


