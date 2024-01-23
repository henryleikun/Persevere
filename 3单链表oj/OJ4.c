#define _CRT_SECURE_NO_WARNINGS 1


//链表的中间节点

//给你单链表的头结点 head ，请你找出并返回链表的中间结点。

//如果有两个中间结点，则返回第二个中间结点。

//输入：head = [1,2,3,4,5]
//输出：[3, 4, 5]
//解释：链表只有一个中间结点，值为 3 。

//-----------------------------------------------------------------------------------------


//好想的可以是这样  求出链表长度 除以二 得到一个数 在遍历这个数次
//但是 有一个很不错的思想 快慢指针法 其思想是 定义两个指针fast slow fast一次移动两个结点 slow一次一个
//结点 两个指针速度是2：1相同时间内 路程比也是2：1所以当fast到表尾的时候 slow就在 表中间 返回就行
//循环结束条件 fast&&fast->next  因为长度可奇可偶且二者不能将交换位置 因为如果是奇的话 fast->next
//是不存在的


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
//	//不为空
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