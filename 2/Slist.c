#define _CRT_SECURE_NO_WARNINGS 1
#include "Slist.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


//�����ڵ�
ListNode* BuyNode(Datatype elem) {
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->data = elem;
	newNode->next = NULL;
	return newNode;
}


//����
ListNode* Find(ListNode* phead, Datatype elem) {
	while (phead != NULL) {
		if (phead->data == elem)
			return phead;
		phead = phead->next;
	}
    //�����Ҳ�����һ��ͷָ��ĸ��� prev ��Ϊ����ͷָ������phead�������ĸ��� �Ҷ�phead���в���
	//����Ӱ�쵽 ͷָ���ָ�� ���õ��� �һ�������pheadȥ�������� ���Ҳ���ı�ͷָ���ָ��

	return NULL;//û�ҵ�����NULL
}


//�����
void Listinsert(ListNode** pphead, ListNode* pos, Datatype elem) {
	//pphead����ΪNULL ������� ָ�������ͷָ�붼��������
	assert(pphead);//����Ϊ�� ��ֹ����

	//*pheadΪ�� ��ζ�� ����Ϊ�� ��Ҫ��������
	if (*pphead == NULL) {
		*pphead = BuyNode(elem);
		return;
	}

	//����������� ��posΪNULLʱ ��Ϊ��β�� ��Ϊ��ʵ�ֵ��ǲ嵽pos��ǰ��
	if (pos == NULL) {
		ListNode* prev = *pphead;
		while (prev->next != NULL) {
			prev = prev->next;
		}//�����ѭ��˵��prevָ�����һ�����

		prev->next = BuyNode(elem);
		
		return;
	}

	//��pos=*pphead��Ϊ��ͷ��
	if (pos == *pphead) {
		ListNode* temp = BuyNode(elem);
		temp->next = *pphead;
		*pphead = temp;

		return;
	}

    //������ ��ǰ��
	ListNode* prev = *pphead;
	while (prev->next != pos) {
		prev = prev->next;
	}

	ListNode* temp = BuyNode(elem);
	temp->next = prev->next;
	prev->next = temp;
}

//����ɾ
void Listerase(ListNode** pphead, ListNode* pos) {
	//pphead����Ϊ�� ���ʾͷָ�벻����
	assert(pphead);

	//*pphead����Ϊ�� ���ʾ����Ϊ��
	assert(*pphead);

	//pos����Ϊ�� ����ɾ��NULL���
	assert(pos);

	//ͷɾ
	if (pos == *pphead) {
		if ((*pphead)->next == NULL) {//����ֻ��һ����� ɾ��ֱ���ÿ�
			free(pos);
			*pphead = NULL;//��Ϊ�ձ�
			return;
		}
		else {//��һ�����ʱ��ͷɾ �����������ͷɾ
			ListNode* del = *pphead;
			*pphead = (*pphead)->next;
			free(del);
			return;
		}
	}


	ListNode* prev = *pphead;
	while (prev->next != pos) {
		prev = prev->next;
	}//��ǰ��

	ListNode* del = prev->next;
	prev->next = prev->next->next;

	free(del);
}

//β��
void Pushback(ListNode** pphead, Datatype elem) {
	Listinsert(pphead,NULL,elem);
}

//ͷ��
void Pushfront(ListNode** pphead, Datatype elem) {
	Listinsert(pphead, *pphead, elem);
}


//βɾ
void Popback(ListNode** pphead) {

	ListNode* prev = *pphead;
	while (prev->next !=NULL) {
		prev = prev->next;
	}//�����һ�����

	Listerase(pphead, prev);
}


//ͷɾ
void Popfront(ListNode** pphead) {
	Listerase(pphead, *pphead);
}


//��ӡ
void Print(ListNode* phead) {
	while (phead != NULL) {
		printf("%d->", phead->data);
		phead = phead->next;
	}

	printf("NULL\n");
}


//�޸�
void  Modify(ListNode** pphead, ListNode* pos) {
	assert(pphead);//ͷָ��Ҫ��Ч
	assert(*pphead);//����Ϊ��
	assert(pos);//û�ҵ�Ҫ�޸ĵ�Ԫ�ز���

	Datatype temp;
	printf("��������Ҫ�޸ĵ�ֵ��");
	scanf("%d", &temp);//ע���޸�Ԫ������ʱ������ ���ռλ��Ҫ�� �Ͼ�����ģ��
	pos->data = temp;
	printf("�޸ĳɹ���\n");
}

//����
void Destroy(ListNode** pphead) {
	ListNode* temp = *pphead;
	while (*pphead != NULL) {
		*pphead=(*pphead)->next;
		free(temp);
		temp = *pphead;
	}

	*pphead = NULL;
}