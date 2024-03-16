#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef int STdatatype;

typedef struct Stack {
	STdatatype* arr;
	int top;//����size������
	int capacity;
}ST;

//����ջ������֮ǰ����ô�๦�� �����ض������ݽṹ �����Լ��ض��Ľӿ� ֻ��Push��Pop

//��ʼ��ջ
void STiniti(ST* st);

//��ջ
void STPush(ST* st, STdatatype elem);

//��ջ
void STPop(ST* st);

//Ϊ�գ�
bool STisEmpty(ST* st);

//��ȡջ��Ԫ�ظ���
int STsize(ST* st);

//��ȡջ��Ԫ��
STdatatype STtop(ST* st);

//����ջ
void STdestroy(ST* st);