#define _CRT_SECURE_NO_WARNINGS 1

//�����е�����k�����

//����
//����һ����������������е�����k����㡣


//���������ɺ���ǰ ���� �����ҵ��뷨�� ��ת���� ��ͷ�ڵ�������K��
//�һ��и� �ȱ���һ��֪�������� n Ȼ�� ��������n-k��
//���ǻ���һ�������� ����ָ�뷨 ��Ҫ������ƽ�� ����ָ�����ָ�� ���k����� ����ͬ���ƶ�
//֪��ƽ�Ƶ���ָ��ָ��NULLʱ

/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 * };
 */

 /**
  *
  * @param pListHead ListNode��
  * @param k int����
  * @return ListNode��
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

