#define _CRT_SECURE_NO_WARNINGS 1

//移除单链表中的元素

//给你一个链表的头节点 head 和一个整数 val ，
//请你删除链表中所有满足 Node.val == val 的节点，并返回 新的头节点 。

//输入：head = [1,2,6,3,4,5,6], val = 6
//输出：[1, 2, 3, 4, 5]

//----------------------------------------------------------------------------------


//传统的方法是遍历链表 找到确定的元素 然后就正常删除
//考虑到 这个元素很多的时候要执行很多次这个删除操作 这个操作涉及到指针的转移 时间上会大打折扣

//上面一种适合当链表中val元素比较少的时候 当比较多的时候建议下面一种
//新建一个链表 将原本不是val的结点搞到这个链表里去  注意别忘了最后吧新链表的尾部断开连接
//结点别人开辟过了 我只需要 排布结点就行

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
//	}//表不能为空
//
//	ListNode* newhead, * newtail;
//	newhead = newtail = (ListNode*)malloc(sizeof(ListNode));//新链表是有头的 主要是好操作
//
//	ListNode* prev = head;//这里直接用head也没事 但还是稳点
//	while (prev) {
//		if (prev->val !=val) {
//			newtail->next = prev;
//			newtail = newtail->next;
//		}
//
//		prev = prev->next;	
//	}
//
//	newtail->next = NULL;//将新表的表尾与原表断开联系
//	ListNode* ret = newhead->next;
//	free(newhead);//自己开辟的头节点别忘记free 我要返回的是无效结点（头节点）的下一位
//
//	return ret;
//	
//}