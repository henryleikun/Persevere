#define _CRT_SECURE_NO_WARNINGS 1


//合并两个有序链表

//将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 
//输入：l1 = [1,2,4], l2 = [1,3,4]
//输出：[1, 1, 2, 3, 4, 4]



//---------------------------------------------------------------------------------
//这个类似与那个顺序表的合并 那一个是倒序合并  并且合并在了已知的数组里
//该题的思想其实差不多  同时也是分别对两个链表遍历 利用两个指针
//然后比较这两个指针指向的结点的元素大小 小的 放到新链表中  两个指针一定会有一个先走到NULL
//在这之前 我已经判断了 两个表不能都为空 当一个为空的时候直接返回另一个 这里两表都不为空
//晚走到NULL的指针后面还有结点 直接一串拉过连连到 新表尾



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
//	//如果两表都不为空
//	ListNode* pl1, * pl2,*newhead,*newtail;
//	pl1 = list1;
//	pl2 = list2;
//	newhead = newtail = (ListNode*)malloc(sizeof(ListNode));//有头不用单独处理空表的情况
//
//	while (pl1 && pl2) {//两个有一个走到NULL都要退出循环
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
//	//两个有一个为NULL
//	if (pl1 == NULL) {
//		newtail->next = pl2;
//	}
//	if (pl2 == NULL) {
//		newtail->next = pl1;
//	}//这是拿一串
//
//	ListNode* ret = newhead -> next;
//	free(newhead);//自己开辟的要free掉
//
//	return ret;
//
//}