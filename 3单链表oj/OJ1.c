#define _CRT_SECURE_NO_WARNINGS 1

//�Ƴ��������е�Ԫ��

//����һ�������ͷ�ڵ� head ��һ������ val ��
//����ɾ���������������� Node.val == val �Ľڵ㣬������ �µ�ͷ�ڵ� ��

//���룺head = [1,2,6,3,4,5,6], val = 6
//�����[1, 2, 3, 4, 5]

//----------------------------------------------------------------------------------


//��ͳ�ķ����Ǳ������� �ҵ�ȷ����Ԫ�� Ȼ�������ɾ��
//���ǵ� ���Ԫ�غܶ��ʱ��Ҫִ�кܶ�����ɾ������ ��������漰��ָ���ת�� ʱ���ϻ����ۿ�

//����һ���ʺϵ�������valԪ�رȽ��ٵ�ʱ�� ���Ƚ϶��ʱ��������һ��
//�½�һ������ ��ԭ������val�Ľ��㵽���������ȥ  ע������������������β���Ͽ�����
//�����˿��ٹ��� ��ֻ��Ҫ �Ų�������

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
//#include <stdio.h>
//typedef struct ListNode ListNode;
//
//struct ListNode* removeElements(struct ListNode* head, int val) {
//	if (head==NULL) {
//		return NULL;
//	}//����Ϊ��
//
//	ListNode* newhead, * newtail;
//	newhead = newtail = (ListNode*)malloc(sizeof(ListNode));//����������ͷ�� ��Ҫ�Ǻò���
//
//	ListNode* prev = head;//����ֱ����headҲû�� �������ȵ�
//	while (prev) {
//		if (prev->val !=val) {
//			newtail->next = prev;
//			newtail = newtail->next;
//		}
//
//		prev = prev->next;	
//	}
//
//	newtail->next = NULL;//���±�ı�β��ԭ��Ͽ���ϵ
//	ListNode* ret = newhead->next;
//	free(newhead);//�Լ����ٵ�ͷ�ڵ������free ��Ҫ���ص�����Ч��㣨ͷ�ڵ㣩����һλ
//
//	return ret;
//	
//}