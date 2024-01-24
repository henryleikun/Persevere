#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

//基于单链表实现通讯录 在单链表的基础上 将结点数据改为 联系人信息

#define NAME 20
#define ADDR 20
#define TEL 20

typedef struct PersonInfo {
    char name[NAME];
    char addr[ADDR];
    char tel[TEL];
}Info;//联系人信息结构体

typedef Info Datatype;

typedef struct ListNode {
    Datatype info;
    struct ListNode* next;
}C_Node;

//考虑到通讯录的实用性 这里的链表实现 像插入就弄个尾插 更多的功能在同目录下的slist里有相关实现
//这里实用性为主 因为是无头 且是C语言实现

//初始化    //无头链表在创建时头指针要先指向NULL再进行操作
void ContactInit(C_Node** pphead);

//创建结点  
C_Node* BuyNode(Datatype x);

//查找联系人 
C_Node* Find(C_Node** pphead, const char* name);//按名字

//查找并显示(实用性)基于Find（）
void Searchcontact(C_Node** pphead, const char* name);

//打印通讯录
void Printcontact(C_Node** pphead);

//添加联系人 这里默认尾插
void Addcontact(C_Node** pphead);

//删除联系人
void Deletecontact(C_Node** pphead, const char* name);

//修改联系人
void Modifycontact(C_Node* pos);


//销毁通讯录
void Destroy(C_Node** pphead);




