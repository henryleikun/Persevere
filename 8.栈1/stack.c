#define _CRT_SECURE_NO_WARNINGS 1

#include "stack.h"

//初始化栈
void STiniti(ST* st) {
	st->arr = NULL;
	st->top = 0;//这里有两种处理方式 一种是我这种 top为一 可以将他认为是
	//栈中元素的个数 top指向栈顶元素的下一个位置 入栈的时候先入在++
	//还可以让top=-1，意为直接指向栈顶的元素 入栈时先++在入 推荐第一种
	//因为在起栈顶指针的作用同时也能起到 size的作用
	st->capacity = 0;
}

//入栈
void STPush(ST* st, STdatatype elem) {
	assert(st);

	//判断是否扩容
	if (st->top == st->capacity) {
		int newcapacity = st->capacity == 0 ? 4 : 2 * st->capacity;
		STdatatype* tmp = (STdatatype*)realloc(st->arr,newcapacity * sizeof(STdatatype));
		//realloc当arr为空的时候 功能等同于malloc
		if (tmp == NULL) {
			perror("realloc failed!\n");
			return;
		}

		st->arr = tmp;
		st->capacity = newcapacity;
	}
	
	 st->arr[st->top++] = elem;
}

//出栈
void STPop(ST* st) {
	assert(st);
	if(!STisEmpty(st))
	    st->top--;
	else
		printf("Empty stack!\n");
}

//为空？
bool STisEmpty(ST* st) {
	assert(st);

	return st->top == 0;
}

//获取栈中元素个数
int STsize(ST* st) {
	assert(st);
	return st->top;
}

//获取栈顶元素
STdatatype STtop(ST* st) {
	assert(st);

	if (!STisEmpty(st))
		return st->arr[st->top - 1];
	else {
		printf("Empty stack! return '\0'\n");
		return '\0';//返回STdatatype 里表示无效的字面量
	}
}

//销毁栈
void STdestroy(ST* st) {
	free(st->arr);
	st->arr = NULL;

	st->top = st->capacity = 0;
}