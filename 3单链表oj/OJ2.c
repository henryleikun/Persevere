#define _CRT_SECURE_NO_WARNINGS 1

//反转链表

//给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
//输入：head = [1,2,3,4,5]
//输出：[5, 4, 3, 2, 1]


//-------------------------------------------------------------------------------------

//单向链表不能由后向前  可以想起来的 应该是 新建一个链表 对老链表遍历并头插到新链表中 最后对表尾处理一下
//但这里用一个比较nb的方法  创建三个指针 p1 p2 p3分别指向NULL ListNode ListNode->next
//当链表不为空 即ListNode!=NULL 这时p2的next指向p1 让p1等于p2 p2等于p3 p3等于p3的next即三个指针
//后移 当然 p3是最先指向 NULL的 但循环的条件是p2不能是NULL 所以还有对p3做一个特殊的处理 
//整个思想就是这样 最后 p1值反转链表的头指针


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
//	//如果不为空
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
//			p3 = p3->next;//p3最先指向NULL 但条件是p2不能为NULL等一回合
//	}
//
//	return p1;
//}