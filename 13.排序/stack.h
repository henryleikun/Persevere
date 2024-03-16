#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef int STdatatype;

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