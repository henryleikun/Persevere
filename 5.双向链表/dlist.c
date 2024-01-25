#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include "dlist.h"
#include <stdlib.h>
#include <assert.h>


//��ʼ�� 
void Listinit(ListNode** pphead) {
	assert(pphead);//ͷָ�����Ч

	*pphead = BuyNode(-1);//�������ڱ�λ(ͷ�ڵ����Ч����)��Ϊ-1
	(*pphead)->next = (*pphead)->prev = *pphead;
}

//���ٽڵ�
ListNode* BuyNode(Datatype elem) {
	ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));
	newnode->data = elem;
	newnode->prev = newnode->next = NULL;
	return newnode;
}

//����
ListNode* Find(ListNode* phead, Datatype elem) {
	assert(phead);

	ListNode* pcur = phead->next;

	while (pcur != pcur->next) {
		if (pcur->data == elem)
			return pcur;

		pcur = pcur->next;
	}

	return NULL;//�ձ������û�ҵ�����NULL
}


//β��
void Push_back(ListNode* phead, Datatype elem) {
	//���������һ����ָ�� ������һ��û�г�ʼ����ָ����ô��
	assert(phead);//��ָ��  û�г�ʼ�� ���붼����ȥ ����д�ж�����
	

	//˫������Ϊʲôʵ�������� ������Ϊ����ͷ
	//�������⴦��ձ�����(ɾ������).��ѭ�� ��������һ�㵽�����˼��ȥд����

	ListNode* ptail = phead->prev;
	ListNode* newnode = BuyNode(elem);
	//phead newnode ptail

	newnode->next = phead;
	newnode->prev = ptail;

	phead->prev = newnode;

	ptail->next = newnode;
}

//ͷ��  ͷ������phead(ͷ�ڵ�֮���)
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

//����� ������Ĭ��pos��߲壩 
void Listinsert(ListNode* pos, Datatype elem) {//�ò���ͷ��� ��Ϊ����˫������ ֪��һ������ǿ���
	//֪��ǰ��Ľ���

	assert(pos);

	ListNode* newnode = BuyNode(elem);
	ListNode* next = pos->next;

	//prev pos next
	newnode->next = next;
	newnode->prev = pos;

	pos->next = newnode;
	next->prev = newnode;
}

//ͷɾ
void Pop_front(ListNode* phead) {
	assert(phead);
	assert(phead != phead->next);//�����ǿձ�

	ListNode* del = phead->next;
	ListNode* next = del->next;
	//phead del next

	phead->next = next;
	next->prev = phead;
	free(del);
}

//βɾ
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

//����ɾ
void Listerase(ListNode* pos) {
	assert(pos);

	ListNode* prev = pos->prev;
	ListNode* next = pos->next;

	prev->next = next;
	next->prev = prev;

	free(pos);
}

//��ӡ
void Print(ListNode* phead) {
	assert(phead);

	ListNode* pcur = phead->next;
	while (pcur != phead) {
		printf("%d->", pcur->data);
		pcur = pcur->next;
	}

	printf("ѭ������\n");
}

//���� ����ı���ͷָ���ָ�� �����ǽӿڵ�һ���� ������һ��ָ�봦��
//ͨ��phead�ͷŵ����п��ٹ��Ŀռ� ������ⲿ��pheadָ��NULL
void Destroy(ListNode* phead) {
	assert(phead);

	ListNode* pcur = phead->next;
	ListNode* tmp = pcur;
	while (pcur->next != phead) {
		pcur = pcur->next;
		free(tmp);
		tmp = pcur;
	}//free ����ͷ�ڵ�����н��

	free(phead);
	//phead=NULL ���Ǹ�һ��ָ�� ����������ı�����ֵ ���ⲿ�ֶ��ı�

}