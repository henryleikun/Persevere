#define _CRT_SECURE_NO_WARNINGS 1


#include "Slist.h"
#include <stdio.h>


int main() {
	ListNode* plist;//ͷָ��
	plist = BuyNode(1);
	Pushback(&plist,2);
	Pushfront(&plist, 0);
	ListNode* temp = Find(plist,2);//�ҵ�2���ڵĽ��

	Listinsert(&plist, temp, 3);//�ڶ�Ӧ2�Ľ��ǰ�����3
	//Print(plist);

	Listerase(&plist, temp);//ɾ��2
	Print(plist);

	return 0;
}