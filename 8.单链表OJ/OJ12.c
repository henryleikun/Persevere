#define _CRT_SECURE_NO_WARNINGS 1

//�������ĸ���

////����һ������Ϊ n ������ÿ���ڵ����һ���������ӵ����ָ�� random
// ��ָ�����ָ�������е��κνڵ��սڵ㡣
//������������ ����� ���Ӧ�������� n �� ȫ�� �ڵ����
// ����ÿ���½ڵ��ֵ����Ϊ���Ӧ��ԭ�ڵ��ֵ
// �½ڵ�� next ָ��� random ָ��Ҳ��Ӧָ���������е��½ڵ�
// ��ʹԭ����͸��������е���Щָ���ܹ���ʾ��ͬ������״̬
// ���������е�ָ�붼��Ӧָ��ԭ�����еĽڵ� ��
//���磬���ԭ�������� X �� Y �����ڵ㣬���� X.random-- > Y 
// ��ô�ڸ��������ж�Ӧ�������ڵ� x �� y ͬ���� x.random-- > y ��
//���ظ��������ͷ�ڵ㡣
//��һ���� n ���ڵ���ɵ���������ʾ����/����е����� ÿ���ڵ���һ��[val, random_index] ��ʾ��
//val��һ����ʾ Node.val ��������
//random_index�����ָ��ָ��Ľڵ���������Χ�� 0 �� n - 1���������ָ���κνڵ㣬��Ϊnull ��
//��Ĵ���ֻ����ԭ�����ͷ�ڵ� head ��Ϊ���������

//--------------------------------------------------------


//�ҵ�˼·�� ��deep copy ��random��ΪNULLȻ�� ����ԭ���� ÿ����һ����� ���ýڵ��random
//��¼��random_t�� �����±���ԭ���� ͬʱ���������� ����ָ��ָ�����������ͷ ͬʱ������ ��
//random_t�ҵ���Ӧ�Ľ�� ������λ��Ҳ��������Ľ���random��ָ�� �Դ����� 
//�ǲ������Ž��Ҳ����


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
    }//deep copy over  β��

    ListNode* random_t;
    ListNode* cur_t=head_t;//��������������
    cur = head;//��������ԭ���� ȷ��random
   
    while (cur) {
        random_t = cur->random;
        ListNode* prhead = head;//��������random_t����ԭ���� ȷ���������Ӧλ�õ�random
        ListNode* prhead_t = head_t;//��������ԭ����Ķ�Ӧrandom
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


