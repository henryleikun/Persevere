#define _CRT_SECURE_NO_WARNINGS 1


//�ϲ�������������

//��������������ϲ�Ϊһ���µ� ���� �������ء���������ͨ��ƴ�Ӹ�����������������нڵ���ɵġ� 
//���룺l1 = [1,2,4], l2 = [1,3,4]
//�����[1, 1, 2, 3, 4, 4]



//---------------------------------------------------------------------------------
//����������Ǹ�˳���ĺϲ� ��һ���ǵ���ϲ�  ���Һϲ�������֪��������
//�����˼����ʵ���  ͬʱҲ�Ƿֱ������������� ��������ָ��
//Ȼ��Ƚ�������ָ��ָ��Ľ���Ԫ�ش�С С�� �ŵ���������  ����ָ��һ������һ�����ߵ�NULL
//����֮ǰ ���Ѿ��ж��� �������ܶ�Ϊ�� ��һ��Ϊ�յ�ʱ��ֱ�ӷ�����һ�� ����������Ϊ��
//���ߵ�NULL��ָ����滹�н�� ֱ��һ������������ �±�β



  //Definition for singly-linked list.
//  struct ListNode {
//      int val;
//      struct ListNode *next;
//  };
//
//#include <stdio.h>
//
//typedef struct ListNode ListNode;
//
//struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
//	if (list1 == NULL && list2 == NULL)
//		return NULL;
//
//	if (list1 == NULL)
//		return list2;
//
//	if (list2 == NULL)
//		return list1;
//	
//	//���������Ϊ��
//	ListNode* pl1, * pl2,*newhead,*newtail;
//	pl1 = list1;
//	pl2 = list2;
//	newhead = newtail = (ListNode*)malloc(sizeof(ListNode));//��ͷ���õ�������ձ�����
//
//	while (pl1 && pl2) {//������һ���ߵ�NULL��Ҫ�˳�ѭ��
//		if (pl1->val < pl2->val) {
//			newtail->next = pl1;
//			newtail = newtail->next;
//			pl1 = pl1->next;
//		}
//		else {
//			newtail->next = pl2;
//			newtail = newtail->next;
//			pl2 = pl2->next;
//		}
//
//	}
//	//������һ��ΪNULL
//	if (pl1 == NULL) {
//		newtail->next = pl2;
//	}
//	if (pl2 == NULL) {
//		newtail->next = pl1;
//	}//������һ��
//
//	ListNode* ret = newhead -> next;
//	free(newhead);//�Լ����ٵ�Ҫfree��
//
//	return ret;
//
//}