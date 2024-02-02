#define _CRT_SECURE_NO_WARNINGS 1

//环形链表
//给你一个链表的头节点 head ，判断链表中是否有环。
//如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 
// 为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置
// （索引从 0 开始）。
//注意：pos 不作为参数进行传递 。仅仅是为了标识链表的实际情况。
//如果链表中存在环 ，则返回 true 。 否则，返回 false 。


//--------------------------------------------------------------------------------

//一个链表若是环形链表  则其尾结点的next不会是NULL，这样就不能像正常的单链表一样去遍历了
//因为只要遍历 就一定是死循环 循环链表是环形链表的特殊情况 这里环形链表的解决方法 也是链表OJ
//里的经典方法 快慢指针法 这种依靠两个指针来解决问题的思想很重要 希望自己能 深入吸收内部的思想

//在找链表中间节点题中 利用了快慢指针 其实我觉得这是一种物理(追击相遇)和逻辑思维思想，
//这里在判断环形链表时 slow一次一步，fast一次两步，若不成环 循环条件和找中间结点一样 
// fast&&fast->next，若成环，直接返回true 截断条件是 fast 与slow指向了一个结点 
//为什么会指向一个结点 fast的速度是slow的两倍 fast先进环 slow后进环 假设slow进环的时候与fast
//距离为x(x>=0&&x<环长) 速度差为1 每回合追上一步 那最终一定会追上 因为这是在环里面


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
//typedef struct ListNode ListNode;
//
//bool hasCycle(struct ListNode* head) {
//    if (head == NULL)
//        return NULL;
//
//    ListNode* slow, * fast;
//    slow = fast = head;
//
//    while (fast && fast->next) {
//        slow = slow->next;
//        fast = fast->next->next;
//
//        if (fast == slow)
//            return true;
//    }
//
//    return false;
//} 

//这里想讨论一下 如果 slow和fast的速度差不是单位1 也就是每回合追上slow进环之后与fast的距离
//不是1，能否出现slow等于fast的情况呢？或者说 slow与fast会错开吗？


//假设表头到入环点的距离是L 环长是C slow进入环与fast的距离是D
//讨论 当速度差是2的时候：
//每回合追上两步 即D-2n(n=1,2,...)，如果D是偶数 那么就可以追上 即可以判断是否成环
//但如果 D是奇数 就会错开 错开后 fast与slow之间的距离刷新 刷新成为C-1如果C-1是偶数 
//那也可以判断 他们会相遇 
//如果C是偶数，C-1是奇数那就会一直错开 因为C-1是奇数 每次都是追到刷新长度
//一直循环下去 这样就不能判断是否成环了 就不能出while循环了 永远不会相遇

//那么 D是奇数和C是偶数的情况会出现吗
//假设slow=1，fast=3 slow进环的时候fast已经走了n圈零(C-D) 且fast的路程是slow的三倍 列方程
//3L=nC+C-D+L-->(n+1)C-D=2L 这个式子可以看出（n+1）C和D不可能是一奇一偶
//当D是奇数的时候 (n+1)C必须是奇数 C和n+1必是奇数 不会出现D是奇数 C是偶数
//故 slow=1，fast=3的时候还是可以判断是否成环 nb