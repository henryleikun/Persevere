#define _CRT_SECURE_NO_WARNINGS 1

#include "stack.h"

//��ʼ��ջ
void STiniti(ST* st) {
	st->arr = NULL;
	st->top = 0;//���������ִ���ʽ һ���������� topΪһ ���Խ�����Ϊ��
	//ջ��Ԫ�صĸ��� topָ��ջ��Ԫ�ص���һ��λ�� ��ջ��ʱ��������++
	//��������top=-1����Ϊֱ��ָ��ջ����Ԫ�� ��ջʱ��++���� �Ƽ���һ��
	//��Ϊ����ջ��ָ�������ͬʱҲ���� size������
	st->capacity = 0;
}

//��ջ
void STPush(ST* st, STdatatype elem) {
	assert(st);

	//�ж��Ƿ�����
	if (st->top == st->capacity) {
		int newcapacity = st->capacity == 0 ? 4 : 2 * st->capacity;
		STdatatype* tmp = (STdatatype*)realloc(st->arr,newcapacity * sizeof(STdatatype));
		//realloc��arrΪ�յ�ʱ�� ���ܵ�ͬ��malloc
		if (tmp == NULL) {
			perror("realloc failed!\n");
			return;
		}

		st->arr = tmp;
		st->capacity = newcapacity;
	}
	
	 st->arr[st->top++] = elem;
}

//��ջ
void STPop(ST* st) {
	assert(st);
	if(!STisEmpty(st))
	    st->top--;
	else
		printf("Empty stack!\n");
}

//Ϊ�գ�
bool STisEmpty(ST* st) {
	assert(st);

	return st->top == 0;
}

//��ȡջ��Ԫ�ظ���
int STsize(ST* st) {
	assert(st);
	return st->top;
}

//��ȡջ��Ԫ��
STdatatype STtop(ST* st) {
	assert(st);

	if (!STisEmpty(st))
		return st->arr[st->top - 1];
	else {
		printf("Empty stack! return '\0'\n");
		return '\0';//����STdatatype ���ʾ��Ч��������
	}
}

//����ջ
void STdestroy(ST* st) {
	free(st->arr);
	st->arr = NULL;

	st->top = st->capacity = 0;
}