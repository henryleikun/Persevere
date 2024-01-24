#define _CRT_SECURE_NO_WARNINGS 1

#include "contact.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


//��ʼ��    
void ContactInit(C_Node** pphead) {
	//ͷָ�������Ч��
	assert(pphead);
	*pphead = NULL;
}

//�������  
C_Node* BuyNode(Datatype x) {
	C_Node* newnode = (C_Node*)malloc(sizeof(C_Node));
	newnode->info = x;
	newnode->next = NULL;

	return newnode;
}

//������ϵ�� 
C_Node* Find(C_Node** pphead, const char* name) {
	assert(pphead);//��Чͷָ��
	if (*pphead == NULL) {
		printf("ͨѶ¼Ϊ�գ�\n");
		return NULL;
	}

	C_Node* pcur = *pphead;
	while (pcur) {
		if (strcmp(pcur->info.name, name) == 0) {
			return pcur;
		}

		pcur = pcur->next;
	}

	return pcur;//�Ҳ�������NULL
}

//���Ҳ���ʾ(ʵ����)����Find����
void Searchcontact(C_Node** pphead, const char* name) {
	assert(pphead);//��Чͷָ��
	if (*pphead == NULL) {
		printf("ͨѶ¼Ϊ�գ�\n");
		return;
	}

	C_Node* pshow = Find(pphead, name);

	if (pshow != NULL) {//�ҵ���
		printf("%s��Ϣ���£�\n",name);
		printf("������%s\n", pshow->info.name);
		printf("��ַ��%s\n", pshow->info.addr);
		printf("�绰��%s\n", pshow->info.tel);
	}
	else
		printf("δ�ҵ���\n");
}

//��ӡͨѶ¼
void Printcontact(C_Node** pphead) {
	assert(pphead);//��Чͷָ��

	if (*pphead == NULL) {
		printf("ͨѶ¼Ϊ�գ�\n");
		return;
	}

	C_Node* pshow = *pphead;

	while (pshow) {
		printf("������%s\n", pshow->info.name);
		printf("��ַ��%s\n", pshow->info.addr);
		printf("�绰��%s\n", pshow->info.tel);
		printf("\n");

		pshow = pshow->next;
	}
}

//�����ϵ�� Ĭ��β��
void Addcontact(C_Node** pphead) {
	assert(pphead);
	Datatype x;

	printf("��������Ҫ��ӵ���ϵ����Ϣ��\n");
	printf("������");
	scanf("%s", x.name);
	printf("��ַ��");
	scanf("%s", x.addr);
	printf("�绰��");
	scanf("%s", x.tel);


	if (*pphead == NULL) {//�ձ�
		*pphead = BuyNode(x);
		return;
	}
   
	C_Node* ptai = *pphead;
	while (ptai->next != NULL)
		ptai = ptai->next;

	ptai->next = BuyNode(x);
	printf("��ӳɹ���\n");
}

//ɾ����ϵ��
void Deletecontact(C_Node** pphead,const char* name) {//����λ��ɾ  
	assert(pphead);
	if (*pphead == NULL) {
		printf("ͨѶ¼Ϊ�գ�\n");
		return;
	}
	C_Node* pos = Find(pphead, name);

	if (pos == NULL) {
		printf("δ�ҵ�����ϵ��!\n");
		return;
	}


	//ͷɾ
	if (pos == *pphead) {
		if ((*pphead)->next == NULL) {//����ֻ��һ����� ɾ��ֱ���ÿ�
			free(pos);
			*pphead = NULL;//��Ϊ�ձ�
			return;
		}
		else {//��һ�����ʱ��ͷɾ �����������ͷɾ
			C_Node* del = *pphead;
			*pphead = (*pphead)->next;
			free(del);
			return;
		}
	}


	//����ɾ
	C_Node* prev = *pphead;
	while (prev->next != pos) {
		prev = prev->next;
	}//��ǰ��

	C_Node* del = prev->next;
	prev->next = prev->next->next;

	free(del);
}

//�޸���ϵ��
void Modifycontact(C_Node* pos) {
	if (pos == NULL) {
		printf("δ�ҵ�����ϵ�ˣ�\n");
		return;
	}

	Datatype tmp;
	printf("��������Ҫ�޸ĵ���ϵ����Ϣ��\n");
	printf("������\n");
	scanf("%s", tmp.name);
	printf("��ַ��\n");
	scanf("%s", tmp.addr);
	printf("�绰��\n");
	scanf("%s", tmp.tel);

	pos->info = tmp;
	printf("�޸ĳɹ���\n");
}


//����ͨѶ¼
void Destroy(C_Node** pphead) {
	C_Node* temp = *pphead;

	while (temp) {
		*pphead = (*pphead)->next;
		free(temp);
		temp = *pphead;
	}
}
