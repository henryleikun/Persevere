#define _CRT_SECURE_NO_WARNINGS 1

//分割链表

//给你一个链表的头节点 head 和一个特定值 x ，
// 请你对链表进行分隔，使得所有 小于 x 的节点都出现在 大于或等于 x 的节点之前。
//你不需要 保留 每个分区中各节点的初始相对位置。

//输入：head = [1, 4, 3, 2, 5, 2], x = 3
//输出：[1, 2, 2, 4, 3, 5]


//-------------------------------------------------------------------------------

//这个其实相对好想一点 对我这个算法写的不太多的人 还是多做点题 当然 基础也得行 ok思路是
//将x作为一个标准 建立两个新链表 遍历链表的同时与x作比较 小的插入到小链表上，大的插入到大链表上
//最后合并一下 将小链表的表尾指向 大链表的表头 不要忘了 让大链表的表尾指向空 因为很有可能表尾
//的next与原链表的关系并没有断开

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

//typedef struct ListNode ListNode;
//
//struct ListNode* partition(struct ListNode* head, int x) {
//	if (head == NULL)
//		return NULL;
//	
//	ListNode* lesshead, * lesstail, * greaterhead, * greatertail;
//	lesshead = lesstail = (ListNode*)malloc(sizeof(ListNode));
//	greaterhead = greatertail = (ListNode*)malloc(sizeof(ListNode));
//	
//	ListNode* prev = head;
//
//	while (prev) {
//		if (prev->val < x) {
//			lesstail->next = prev;
//			lesstail = lesstail->next;
//		}
//		else {
//			greatertail->next = prev;
//			greatertail = greatertail->next;
//		}
//
//		prev = prev->next;
//	}
//
//	greatertail->next = NULL;//防止成环
//
//	lesstail->next = greaterhead->next;
//
//	free(greaterhead);
//	ListNode* ret = lesshead->next;
//	free(lesshead);
//
//	return ret;
//
//	
//}
