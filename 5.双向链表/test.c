#define _CRT_SECURE_NO_WARNINGS 1


#include <stdio.h>
#include "dlist.h"
#include <stdlib.h>


int main() {
	ListNode* dlist;
	Listinit(&dlist);//必须要先初始化

	/*Push_back(dlist, 1);
	Push_back(dlist, 2);
	Push_back(dlist, 3);
	Push_back(dlist, 4);*/
	//Print(dlist);  //1 2 3 4

	Push_front(dlist, 1);
	Push_front(dlist, 2);
	Push_front(dlist, 3);
	Push_front(dlist, 4);
	
	Print(dlist);//4 3 2 1

	/*ListNode* ret = Find(dlist, 6);
	if (ret == NULL)
		printf("没找到！\n");*/

	//ListNode* ret = Find(dlist, 1);
	//Listinsert(ret, 5);
	//Print(dlist);//4 3 2 1 5

	//Pop_front(dlist);
	//Print(dlist);//3 2 1

	//Pop_back(dlist);
	//Print(dlist);//4 3 2

	ListNode* ret=Find(dlist, 3);
	Listerase(ret);
	Print(dlist);//4 2 1

	Destroy(dlist);
	dlist = NULL;

	return 0;
}