#define _CRT_SECURE_NO_WARNINGS 1

#include "contact.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


//初始化    
void ContactInit(C_Node** pphead) {
	//头指针的是有效的
	assert(pphead);
	*pphead = NULL;
}

//创建结点  
C_Node* BuyNode(Datatype x) {
	C_Node* newnode = (C_Node*)malloc(sizeof(C_Node));
	newnode->info = x;
	newnode->next = NULL;

	return newnode;
}

//查找联系人 
C_Node* Find(C_Node** pphead, const char* name) {
	assert(pphead);//有效头指针
	if (*pphead == NULL) {
		printf("通讯录为空！\n");
		return NULL;
	}

	C_Node* pcur = *pphead;
	while (pcur) {
		if (strcmp(pcur->info.name, name) == 0) {
			return pcur;
		}

		pcur = pcur->next;
	}

	return pcur;//找不到返回NULL
}

//查找并显示(实用性)基于Find（）
void Searchcontact(C_Node** pphead, const char* name) {
	assert(pphead);//有效头指针
	if (*pphead == NULL) {
		printf("通讯录为空！\n");
		return;
	}

	C_Node* pshow = Find(pphead, name);

	if (pshow != NULL) {//找到了
		printf("%s信息如下：\n",name);
		printf("姓名：%s\n", pshow->info.name);
		printf("地址：%s\n", pshow->info.addr);
		printf("电话：%s\n", pshow->info.tel);
	}
	else
		printf("未找到！\n");
}

//打印通讯录
void Printcontact(C_Node** pphead) {
	assert(pphead);//有效头指针

	if (*pphead == NULL) {
		printf("通讯录为空！\n");
		return;
	}

	C_Node* pshow = *pphead;

	while (pshow) {
		printf("姓名：%s\n", pshow->info.name);
		printf("地址：%s\n", pshow->info.addr);
		printf("电话：%s\n", pshow->info.tel);
		printf("\n");

		pshow = pshow->next;
	}
}

//添加联系人 默认尾插
void Addcontact(C_Node** pphead) {
	assert(pphead);
	Datatype x;

	printf("请输入你要添加的联系人信息：\n");
	printf("姓名：");
	scanf("%s", x.name);
	printf("地址：");
	scanf("%s", x.addr);
	printf("电话：");
	scanf("%s", x.tel);


	if (*pphead == NULL) {//空表
		*pphead = BuyNode(x);
		return;
	}
   
	C_Node* ptai = *pphead;
	while (ptai->next != NULL)
		ptai = ptai->next;

	ptai->next = BuyNode(x);
	printf("添加成功！\n");
}

//删除联系人
void Deletecontact(C_Node** pphead,const char* name) {//任意位置删  
	assert(pphead);
	if (*pphead == NULL) {
		printf("通讯录为空！\n");
		return;
	}
	C_Node* pos = Find(pphead, name);

	if (pos == NULL) {
		printf("未找到该联系人!\n");
		return;
	}


	//头删
	if (pos == *pphead) {
		if ((*pphead)->next == NULL) {//链表只有一个结点 删完直接置空
			free(pos);
			*pphead = NULL;//置为空表
			return;
		}
		else {//非一个结点时的头删 即正常情况的头删
			C_Node* del = *pphead;
			*pphead = (*pphead)->next;
			free(del);
			return;
		}
	}


	//正常删
	C_Node* prev = *pphead;
	while (prev->next != pos) {
		prev = prev->next;
	}//找前驱

	C_Node* del = prev->next;
	prev->next = prev->next->next;

	free(del);
}

//修改联系人
void Modifycontact(C_Node* pos) {
	if (pos == NULL) {
		printf("未找到该联系人！\n");
		return;
	}

	Datatype tmp;
	printf("请输入你要修改的联系人信息：\n");
	printf("姓名：\n");
	scanf("%s", tmp.name);
	printf("地址：\n");
	scanf("%s", tmp.addr);
	printf("电话：\n");
	scanf("%s", tmp.tel);

	pos->info = tmp;
	printf("修改成功！\n");
}


//销毁通讯录
void Destroy(C_Node** pphead) {
	C_Node* temp = *pphead;

	while (temp) {
		*pphead = (*pphead)->next;
		free(temp);
		temp = *pphead;
	}
}
