#define _CRT_SECURE_NO_WARNINGS 1


//������м�ڵ�

//���㵥�����ͷ��� head �������ҳ�������������м��㡣

//����������м��㣬�򷵻صڶ����м��㡣

//���룺head = [1,2,3,4,5]
//�����[3, 4, 5]
//���ͣ�����ֻ��һ���м��㣬ֵΪ 3 ��

//-----------------------------------------------------------------------------------------


//����Ŀ���������  ��������� ���Զ� �õ�һ���� �ڱ����������
//���� ��һ���ܲ����˼�� ����ָ�뷨 ��˼���� ��������ָ��fast slow fastһ���ƶ�������� slowһ��һ��
//��� ����ָ���ٶ���2��1��ͬʱ���� ·�̱�Ҳ��2��1���Ե�fast����β��ʱ�� slow���� ���м� ���ؾ���
//ѭ���������� fast&&fast->next  ��Ϊ���ȿ����ż�Ҷ��߲��ܽ�����λ�� ��Ϊ�������Ļ� fast->next
//�ǲ����ڵ�


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
//#include <stdio.h>
//
//typedef struct ListNode ListNode;
//
//struct ListNode* middleNode(struct ListNode* head) {
//	if (head == NULL)
//		return NULL;
//
//	//��Ϊ��
//	ListNode* fast, * slow;
//	fast = slow = head;
//
//	while (fast && fast->next) {
//		fast = fast->next->next;
//		slow = slow->next;
//	}
//
//	return slow;
//}