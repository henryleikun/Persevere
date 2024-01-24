#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

//���ڵ�����ʵ��ͨѶ¼ �ڵ�����Ļ����� ��������ݸ�Ϊ ��ϵ����Ϣ

#define NAME 20
#define ADDR 20
#define TEL 20

typedef struct PersonInfo {
    char name[NAME];
    char addr[ADDR];
    char tel[TEL];
}Info;//��ϵ����Ϣ�ṹ��

typedef Info Datatype;

typedef struct ListNode {
    Datatype info;
    struct ListNode* next;
}C_Node;

//���ǵ�ͨѶ¼��ʵ���� ���������ʵ�� ������Ū��β�� ����Ĺ�����ͬĿ¼�µ�slist�������ʵ��
//����ʵ����Ϊ�� ��Ϊ����ͷ ����C����ʵ��

//��ʼ��    //��ͷ�����ڴ���ʱͷָ��Ҫ��ָ��NULL�ٽ��в���
void ContactInit(C_Node** pphead);

//�������  
C_Node* BuyNode(Datatype x);

//������ϵ�� 
C_Node* Find(C_Node** pphead, const char* name);//������

//���Ҳ���ʾ(ʵ����)����Find����
void Searchcontact(C_Node** pphead, const char* name);

//��ӡͨѶ¼
void Printcontact(C_Node** pphead);

//�����ϵ�� ����Ĭ��β��
void Addcontact(C_Node** pphead);

//ɾ����ϵ��
void Deletecontact(C_Node** pphead, const char* name);

//�޸���ϵ��
void Modifycontact(C_Node* pos);


//����ͨѶ¼
void Destroy(C_Node** pphead);




