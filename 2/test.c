#define _CRT_SECURE_NO_WARNINGS 1


#include "Slist.h"
#include <stdio.h>


int main() {
	ListNode* plist;//头指针
	plist = BuyNode(1);
	Pushback(&plist,2);
	Pushfront(&plist, 0);
	ListNode* temp = Find(plist,2);//找到2所在的结点

	Listinsert(&plist, temp, 3);//在对应2的结点前面插上3
	//Print(plist);

	Listerase(&plist, temp);//删除2
	Print(plist);

	return 0;
}