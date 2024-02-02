#define _CRT_SECURE_NO_WARNINGS 1

//环形链表Ⅱ

//给定一个链表的头节点  head ，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。
//如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 
//为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置
//（索引从 0 开始）。如果 pos 是 - 1，则在该链表中没有环。注意：pos 不作为参数进行传递
// 仅仅是为了标识链表的实际情况。不允许修改 链表。

//---------------------------------------------------------

//经过OJ10的分析 这里只需在那个基础上 返回入环点就行 这里取slow=1，fast=2 下面就知道为什么
//要取二倍关系 因为是二倍关系 速度差为单位1所以一定可以相遇 
//假设表头到入环点的距离是L 环长是C  相遇点距入环点的距离是X
//分析知 因为速度差为1 所以在slow进入环后 在被追上之前 一定不会走的超过一圈
//因为fast是一步一步的追的 slow如果走了一圈 那fast就走两圈 这个过程一定会和slow相遇
//所以slow与fast相遇时 slow走的距离是L+X 假设fast在与slow相遇之前走了n圈则
//fast走了nC+L+X 列方程：2(L+X)=nC+L+X-->L=nC-X;
//这个式子很秒 因为L是表头到入环点的距离 这里让fast从新指向表头 并且速度和slow一样 两个指针
//同时开始走slow走n-1圈零X步时刚好和fast在入环点会和
//OK



/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
//typedef struct ListNode ListNode;
//struct ListNode* detectCycle(struct ListNode* head) {
//	if (head == NULL) {
//		return NULL;
//	}
//
//	ListNode* slow, * fast;
//	slow = fast = head;
//
//	while (fast && fast->next) {
//		slow = slow->next;
//		fast = fast->next->next;
//
//		if (slow == fast) {//相遇点
//			fast = head;
//			while (fast != slow) {
//				fast = fast->next;
//				slow = slow->next;
//			}
//
//			return fast;
//		}
//	}
//
//	return NULL;//不成环
//}



//其实还有一个结合之前方法的方法
//找到相遇点之后  将ListNode* head_t=fast(slow)—>next,
//在将fast(slow)—>next=NULL 转变成了相交链表找交点的问题