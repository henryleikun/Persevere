#define _CRT_SECURE_NO_WARNINGS 1

//��ת����

//���㵥�����ͷ�ڵ� head �����㷴ת���������ط�ת�������
//���룺head = [1,2,3,4,5]
//�����[5, 4, 3, 2, 1]


//-------------------------------------------------------------------------------------

//�����������ɺ���ǰ  ������������ Ӧ���� �½�һ������ �������������ͷ�嵽�������� ���Ա�β����һ��
//��������һ���Ƚ�nb�ķ���  ��������ָ�� p1 p2 p3�ֱ�ָ��NULL ListNode ListNode->next
//������Ϊ�� ��ListNode!=NULL ��ʱp2��nextָ��p1 ��p1����p2 p2����p3 p3����p3��next������ָ��
//���� ��Ȼ p3������ָ�� NULL�� ��ѭ����������p2������NULL ���Ի��ж�p3��һ������Ĵ��� 
//����˼��������� ��� p1ֵ��ת�����ͷָ��


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

//
//#include <stdio.h>
//typedef struct ListNode ListNode;
//
//struct ListNode* reverseList(struct ListNode* head) {
//	if (head == NULL)
//		return NULL;
//
//	//�����Ϊ��
//	ListNode* p1, * p2, * p3;
//	p1 = NULL;
//	p2 = head;
//	p3 = p2->next;
//
//	while (p2) {
//		p2->next = p1;
//		p1 = p2;
//		p2 = p3;
//
//		if (p3 != NULL)
//			p3 = p3->next;//p3����ָ��NULL ��������p2����ΪNULL��һ�غ�
//	}
//
//	return p1;
//}