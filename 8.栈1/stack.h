#define _CRT_SECURE_NO_WARNINGS 1

//对于数据结构栈 其实现可以用单链表也可以用 数组 栈是后入先出 所以对于改数据结构的端口
//应只有一端 当用单链表实现的时候 这一端应是头 因为对于出操作 头不需要重新遍历链表
//对于链表 是头插和头删 但是数组实现的话 直接在尾部进行操作 效率极高 而且cpu高速缓存效率也高
//唯一不太好的地方就是 要扩容 但这只是小问题 所以 栈的实现 用数组来是实现是最好的
//当然 这里是用顺序表来实现

//在c++的类设计里 我有设计过 栈 可以用模板类 来调整栈中存储的元素 这里typedef 也凑合
//基本实现的思想是差不多的
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef char STdatatype;

typedef struct Stack {
	STdatatype* arr;
	int top;//起着size的作用
	int capacity;
}ST;

//对于栈不用像之前搞那么多功能 这种特定的数据结构 有着自己特定的接口 只有Push和Pop

//初始化栈
void STiniti(ST* st);

//入栈
void STPush(ST* st, STdatatype elem);

//出栈
void STPop(ST* st);

//为空？
bool STisEmpty(ST* st);

//获取栈中元素个数
int STsize(ST* st);

//获取栈顶元素
STdatatype STtop(ST* st);

//销毁栈
void STdestroy(ST* st);