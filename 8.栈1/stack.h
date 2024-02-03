#define _CRT_SECURE_NO_WARNINGS 1

//�������ݽṹջ ��ʵ�ֿ����õ�����Ҳ������ ���� ջ�Ǻ����ȳ� ���Զ��ڸ����ݽṹ�Ķ˿�
//Ӧֻ��һ�� ���õ�����ʵ�ֵ�ʱ�� ��һ��Ӧ��ͷ ��Ϊ���ڳ����� ͷ����Ҫ���±�������
//�������� ��ͷ���ͷɾ ��������ʵ�ֵĻ� ֱ����β�����в��� Ч�ʼ��� ����cpu���ٻ���Ч��Ҳ��
//Ψһ��̫�õĵط����� Ҫ���� ����ֻ��С���� ���� ջ��ʵ�� ����������ʵ������õ�
//��Ȼ ��������˳�����ʵ��

//��c++��������� ������ƹ� ջ ������ģ���� ������ջ�д洢��Ԫ�� ����typedef Ҳ�պ�
//����ʵ�ֵ�˼���ǲ���
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef char STdatatype;

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