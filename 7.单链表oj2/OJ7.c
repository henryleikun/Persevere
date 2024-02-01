#define _CRT_SECURE_NO_WARNINGS 1

//链表中倒数第k个结点

//描述
//输入一个链表，输出该链表中倒数第k个结点。


//单链表不能由后往前 所以 这里我的想法是 反转链表 从头节点往后走K次
//我还有个 先遍历一遍知道链表长度 n 然后 正常访问n-k次
//但是还有一个更吊的 快慢指针法 主要是利用平移 将快指针和慢指针 间隔k个结点 两个同步移动
//知道平移到快指针指向NULL时

/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 * };
 */

 /**
  *
  * @param pListHead ListNode类
  * @param k int整型
  * @return ListNode类
  */
typedef struct ListNode ListNode;


/*
struct ListNode* reverse(struct ListNode* phead) {
    if (phead == NULL)
        return NULL;
    
    ListNode* p1, * p2, * p3;
    p1 = NULL;
    p2 = phead;
    p3 = p2->next;
    while (p2) {
        p2->next = p1;
        p1 = p2;
        p2 = p3;

        if (p3 != NULL)
            p3 = p3->next;
    }

    return p1;


}

struct ListNode* FindKthToTail(struct ListNode* pListHead, int k) {
    // write code here
    ListNode* cur = reverse(pListHead);

    for (int i = 1; i < k; i++) {
        cur = cur->next;
    }

    return cur;


}*/

//
//struct ListNode* FindKthToTail(struct ListNode* pListHead, int k) {
//    // write code here
//    int length = 0;
//    ListNode* cur = pListHead;
//    while (cur) {
//        length++;
//        cur = cur->next;
//    }
//    if (length < k)
//        return NULL;
//
//    cur = pListHead;
//    for (int i = 0; i < length - k; i++) {
//        cur = cur->next;
//    }
//
//    return cur;
//
//
//}

