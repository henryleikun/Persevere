#define _CRT_SECURE_NO_WARNINGS 1


//��������Լɪ������ �����ӳƴ�����

//���Ϊ 1 �� n �� n ����Χ��һȦ���ӱ��Ϊ 1 ���˿�ʼ���������� m �����뿪��
//��һ���˼����� 1 ��ʼ������
//n - 1 �ֽ����Ժ�ֻʣ��һ���ˣ���������µ�����˱���Ƕ��٣�


//---------------------------------------------------------------------------



//������ �����ݴ洢���� 1-n ��Ҫһ�������ı���num ��num%3==0ʱ free����� ����num����
//����ѭ�������������� ���ָ����ڽ���next



//
//#include <stdio.h>
//#include <stdlib.h>
//
//int ysf(int n, int m) {
//    if (n == 0)
//        return 0;
//
//    typedef struct ListNode {
//        int mark;
//        struct ListNode* next;
//    }ListNode;
//
//    ListNode* listhead, *listrear;
//
//    listhead=listrear=(ListNode*)malloc(sizeof(ListNode));
//
//    listhead->mark = 1;
//    listhead->next = NULL;
//
//    for (int i = 2; i < n+1; i++) {
//        listrear->next= (ListNode*)malloc(sizeof(ListNode));
//        listrear = listrear->next;
//        listrear->mark = i;
//        listrear->next = NULL;
//    }//��ѭ�� ������n�����ȵ�����
//
//    listrear->next = listhead;//�ɻ�
//
//    int num = 1;
//    ListNode* move1 = listhead,*move2=listrear;
//    //��move1������ʱ�� ����Ҫ֪������ǰ�� �������move2
//
//    while (move1 != move1->next) {
//        if (num % m == 0) {
//            ListNode* del = move1;
//            move2->next = move1->next;
//            move1 = move1->next;
//            free(del);
//            num = 1;
//        }
//        else {
//            num++;
//            move2 = move2->next;
//            move1 = move1->next;
//        }
//    }
//
//    return move1->mark;
//}
//
//int main() {
//    int num;
//    int death;
//
//    printf("����������������������\n");
//    scanf("%d%d", &num, &death);
//
//    int live = ysf(num, death);
//
//    printf("������������%d��\n", live);
//
//    return 0;
//}