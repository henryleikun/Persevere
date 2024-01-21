#define _CRT_SECURE_NO_WARNINGS 1
#include "Slist.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


//创建节点
ListNode* BuyNode(Datatype elem) {
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->data = elem;
	newNode->next = NULL;
	return newNode;
}


//查找
ListNode* Find(ListNode* phead, Datatype elem) {
	while (phead != NULL) {
		if (phead->data == elem)
			return phead;
		phead = phead->next;
	}
    //这里我不设置一个头指针的副本 prev 因为对于头指针来讲phead就是他的副本 我对phead进行操作
	//不会影响到 头指针的指向 更好的是 我还可以用phead去处理链表 并且不会改变头指针的指向

	return NULL;//没找到返回NULL
}


//任意插
void Listinsert(ListNode** pphead, ListNode* pos, Datatype elem) {
	//pphead不能为NULL 这代表着 指向链表的头指针都还不存在
	assert(pphead);//条件为假 终止程序

	//*phead为空 意味着 链表为空 我要创建链表
	if (*pphead == NULL) {
		*pphead = BuyNode(elem);
		return;
	}

	//考虑特殊情况 当pos为NULL时 认为是尾插 因为我实现的是插到pos的前面
	if (pos == NULL) {
		ListNode* prev = *pphead;
		while (prev->next != NULL) {
			prev = prev->next;
		}//出这个循环说明prev指向最后一个结点

		prev->next = BuyNode(elem);
		
		return;
	}

	//当pos=*pphead认为是头插
	if (pos == *pphead) {
		ListNode* temp = BuyNode(elem);
		temp->next = *pphead;
		*pphead = temp;

		return;
	}

    //正常插 找前驱
	ListNode* prev = *pphead;
	while (prev->next != pos) {
		prev = prev->next;
	}

	ListNode* temp = BuyNode(elem);
	temp->next = prev->next;
	prev->next = temp;
}

//任意删
void Listerase(ListNode** pphead, ListNode* pos) {
	//pphead不能为空 这表示头指针不存在
	assert(pphead);

	//*pphead不能为空 这表示链表为空
	assert(*pphead);

	//pos不能为空 不能删除NULL结点
	assert(pos);

	//头删
	if (pos == *pphead) {
		if ((*pphead)->next == NULL) {//链表只有一个结点 删完直接置空
			free(pos);
			*pphead = NULL;//置为空表
			return;
		}
		else {//非一个结点时的头删 即正常情况的头删
			ListNode* del = *pphead;
			*pphead = (*pphead)->next;
			free(del);
			return;
		}
	}


	ListNode* prev = *pphead;
	while (prev->next != pos) {
		prev = prev->next;
	}//找前驱

	ListNode* del = prev->next;
	prev->next = prev->next->next;

	free(del);
}

//尾插
void Pushback(ListNode** pphead, Datatype elem) {
	Listinsert(pphead,NULL,elem);
}

//头插
void Pushfront(ListNode** pphead, Datatype elem) {
	Listinsert(pphead, *pphead, elem);
}


//尾删
void Popback(ListNode** pphead) {

	ListNode* prev = *pphead;
	while (prev->next !=NULL) {
		prev = prev->next;
	}//找最后一个结点

	Listerase(pphead, prev);
}


//头删
void Popfront(ListNode** pphead) {
	Listerase(pphead, *pphead);
}


//打印
void Print(ListNode* phead) {
	while (phead != NULL) {
		printf("%d->", phead->data);
		phead = phead->next;
	}

	printf("NULL\n");
}


//修改
void  Modify(ListNode** pphead, ListNode* pos) {
	assert(pphead);//头指针要有效
	assert(*pphead);//表不能为空
	assert(pos);//没找到要修改的元素不行

	Datatype temp;
	printf("请输入你要修改的值：");
	scanf("%d", &temp);//注意修改元素类型时别忘了 这个占位符要改 毕竟不是模板
	pos->data = temp;
	printf("修改成功！\n");
}

//销毁
void Destroy(ListNode** pphead) {
	ListNode* temp = *pphead;
	while (*pphead != NULL) {
		*pphead=(*pphead)->next;
		free(temp);
		temp = *pphead;
	}

	*pphead = NULL;
}