#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include "dlist.h"
#include <stdlib.h>
#include <assert.h>


//初始化 
void Listinit(ListNode** pphead) {
	assert(pphead);//头指针得有效

	*pphead = BuyNode(-1);//这里让哨兵位(头节点得无效数据)置为-1
	(*pphead)->next = (*pphead)->prev = *pphead;
}

//开辟节点
ListNode* BuyNode(Datatype elem) {
	ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));
	newnode->data = elem;
	newnode->prev = newnode->next = NULL;
	return newnode;
}

//查找
ListNode* Find(ListNode* phead, Datatype elem) {
	assert(phead);

	ListNode* pcur = phead->next;

	while (pcur != pcur->next) {
		if (pcur->data == elem)
			return pcur;

		pcur = pcur->next;
	}

	return NULL;//空表或者是没找到返回NULL
}


//尾插
void Push_back(ListNode* phead, Datatype elem) {
	//如果传给我一个空指针 或者是一个没有初始化的指针怎么办
	assert(phead);//空指针  没有初始化 编译都过不去 不用写判断条件
	

	//双向链表为什么实现起来简单 就是因为他有头
	//不用特殊处理空表的情况(删除除外).且循环 即可以由一般到特殊的思想去写代码

	ListNode* ptail = phead->prev;
	ListNode* newnode = BuyNode(elem);
	//phead newnode ptail

	newnode->next = phead;
	newnode->prev = ptail;

	phead->prev = newnode;

	ptail->next = newnode;
}

//头插  头插是在phead(头节点之后插)
void Push_front(ListNode* phead, Datatype elem) {
	assert(phead);

	ListNode* newnode = BuyNode(elem);

	ListNode* first = phead->next;
	//phead newnode first

	newnode->next = first;
	newnode->prev = phead;

	phead->next = newnode;;
	first->prev = newnode;
}

//任意插 （这里默认pos后边插） 
void Listinsert(ListNode* pos, Datatype elem) {//用不上头结点 因为这是双向链表 知道一个结点是可以
	//知道前面的结点的

	assert(pos);

	ListNode* newnode = BuyNode(elem);
	ListNode* next = pos->next;

	//prev pos next
	newnode->next = next;
	newnode->prev = pos;

	pos->next = newnode;
	next->prev = newnode;
}

//头删
void Pop_front(ListNode* phead) {
	assert(phead);
	assert(phead != phead->next);//不能是空表

	ListNode* del = phead->next;
	ListNode* next = del->next;
	//phead del next

	phead->next = next;
	next->prev = phead;
	free(del);
}

//尾删
void Pop_back(ListNode* phead) {
	assert(phead);
	assert(phead->next != phead);

	ListNode* del = phead->prev;
	ListNode* prev = del->prev;
	//prev del phead

	prev->next = phead;
	phead->prev = prev;
	free(del);
}

//任意删
void Listerase(ListNode* pos) {
	assert(pos);

	ListNode* prev = pos->prev;
	ListNode* next = pos->next;

	prev->next = next;
	next->prev = prev;

	free(pos);
}

//打印
void Print(ListNode* phead) {
	assert(phead);

	ListNode* pcur = phead->next;
	while (pcur != phead) {
		printf("%d->", pcur->data);
		pcur = pcur->next;
	}

	printf("循环结束\n");
}

//销毁 这个改变了头指针的指向 但考虑接口的一致性 这里用一级指针处理
//通过phead释放掉所有开辟过的空间 最后在外部将phead指向NULL
void Destroy(ListNode* phead) {
	assert(phead);

	ListNode* pcur = phead->next;
	ListNode* tmp = pcur;
	while (pcur->next != phead) {
		pcur = pcur->next;
		free(tmp);
		tmp = pcur;
	}//free 掉除头节点的所有结点

	free(phead);
	//phead=NULL 这是个一级指针 不能在这里改变他的值 在外部手动改变

}