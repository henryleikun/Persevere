#define _CRT_SECURE_NO_WARNINGS 1


//环形链表约瑟夫问题 （猴子称大王）

//编号为 1 到 n 的 n 个人围成一圈。从编号为 1 的人开始报数，报到 m 的人离开。
//下一个人继续从 1 开始报数。
//n - 1 轮结束以后，只剩下一个人，问最后留下的这个人编号是多少？


//---------------------------------------------------------------------------



//链表结点 的数据存储其编号 1-n 需要一个计数的变量num 当num%3==0时 free掉结点 并且num置零
//这里循环结束的条件是 结点指针等于结点的next



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
//    }//出循环 创建了n个长度的链表
//
//    listrear->next = listhead;//成环
//
//    int num = 1;
//    ListNode* move1 = listhead,*move2=listrear;
//    //当move1是三的时候 我需要知道他的前驱 这个就是move2
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
//    printf("请输入人数，和死亡数字\n");
//    scanf("%d%d", &num, &death);
//
//    int live = ysf(num, death);
//
//    printf("最后活下来的是%d号\n", live);
//
//    return 0;
//}