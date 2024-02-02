#define _CRT_SECURE_NO_WARNINGS 1

//随机链表的复制

////给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random
// 该指针可以指向链表中的任何节点或空节点。
//构造这个链表的 深拷贝。 深拷贝应该正好由 n 个 全新 节点组成
// 其中每个新节点的值都设为其对应的原节点的值
// 新节点的 next 指针和 random 指针也都应指向复制链表中的新节点
// 并使原链表和复制链表中的这些指针能够表示相同的链表状态
// 复制链表中的指针都不应指向原链表中的节点 。
//例如，如果原链表中有 X 和 Y 两个节点，其中 X.random-- > Y 
// 那么在复制链表中对应的两个节点 x 和 y 同样有 x.random-- > y 。
//返回复制链表的头节点。
//用一个由 n 个节点组成的链表来表示输入/输出中的链表 每个节点用一个[val, random_index] 表示：
//val：一个表示 Node.val 的整数。
//random_index：随机指针指向的节点索引（范围从 0 到 n - 1）；如果不指向任何节点，则为null 。
//你的代码只接受原链表的头节点 head 作为传入参数。

//--------------------------------------------------------


//我的思路是 先deep copy 将random设为NULL然后 遍历原链表 每遍历一个结点 将该节点的random
//记录到random_t里 并重新遍历原链表 同时遍历新链表 两个指针指向两个链表的头 同时往后走 当
//random_t找到对应的结点 这个相对位置也是新链表的结点的random的指向 以此类推 
//是不是最优解我不清楚


#include <stdio.h>
#include <stdlib.h>

// Definition for a Node.
struct Node {
     int val;
     struct Node *next;
     struct Node *random;
  };
 
typedef struct Node ListNode;

struct Node* copyRandomList(struct Node* head) {
    if (head == NULL)
        return NULL;

    //deep copy
    ListNode* head_t = (ListNode*)malloc(sizeof(ListNode));
    ListNode* tail = head_t;
    head_t->next = head_t->random = NULL;
    head_t->val = head->val;

    ListNode* cur = head->next;
    while (cur) {
        tail->next = (ListNode*)malloc(sizeof(ListNode));
        tail = tail->next;
        tail->val = cur -> val;
        tail->next = tail->random = NULL;
        cur = cur->next;
    }//deep copy over  尾插

    ListNode* random_t;
    ListNode* cur_t=head_t;//用来遍历新链表
    cur = head;//用来遍历原链表 确定random
   
    while (cur) {
        random_t = cur->random;
        ListNode* prhead = head;//用来基于random_t遍历原链表 确定新链表对应位置的random
        ListNode* prhead_t = head_t;//用来跟踪原链表的对应random
        while (prhead!= random_t) {
             prhead_t= prhead_t->next;
             prhead = prhead->next;
        }

        cur_t->random = prhead_t;
        cur_t = cur_t->next;
        cur = cur->next;
    }

    return head_t;
}

int main() {
    ListNode* phead = (ListNode*)malloc(sizeof(ListNode));
    phead->val = 1;
    phead->next = NULL;
    phead->random = phead;
    ListNode* tail = phead;

    for (int i = 2; i < 5; i++) {
        tail->next= (ListNode*)malloc(sizeof(ListNode));
        tail = tail->next;
        tail->val = i;
        tail->random = tail;
        tail->next = NULL;
    }


    ListNode* cpylist = copyRandomList(phead);
    return 0;
}


