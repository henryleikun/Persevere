#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include "contact.h"

typedef struct ListNode Contact;

void menu();

int main() {
	Contact* pcon;
	ContactInit(&pcon);//空表建成
	int choice;
	char name[NAME];
	menu();
	printf("请输入您的选择：");
	scanf("%d", &choice);

	while (1) {
		if (choice <= 7 && choice >= 1) {
			switch (choice) {
			case 1: {
				Addcontact(&pcon);
				break;
			}
			case 2: {
				printf("请输入您想要删除的联系人姓名：");
				scanf("%s", name);
				Deletecontact(&pcon, name);
				printf("删除成功！\n");
				break;
			}
			case 3: {
				printf("请输入您想要查找的联系人姓名：");
				scanf("%s", name);
				Searchcontact(&pcon, name);
				break;
			}
			case 4: {
				printf("请输入您想要修改的联系人姓名：");
				scanf("%s", name);
				Contact* temp = Find(&pcon, name);
				Modifycontact(temp);
				break;
			}
			case 5: {
				Printcontact(&pcon);
				break;
			}
			case 6: {
				Destroy(&pcon);
				printf("销毁成功！\n");
				break;
			}
			case 7: {
				printf("程序退出中...\n");
				system("pause");
				exit(EXIT_SUCCESS);
			}

			}
			system("pause");
			system("cls");

			menu();
			printf("请输入您想要执行的功能：");
			scanf("%d", &choice);
		}
		else {
			printf("请重新输入您的选择!\n");
			system("pause");
			system("cls");
			menu();
			printf("请输入您想要执行的功能：");
			scanf("%d", &choice);
		}
	}

	return 0;
}

void menu() {
	printf("***********通讯录管理系统***********\n");
	printf("***********1.添加联系人***********\n");
	printf("***********2.删除联系人***********\n");
	printf("***********3.查找联系人***********\n");
	printf("***********4.修改联系人***********\n");
	printf("***********5.展示通讯录***********\n");
	printf("***********6.销毁通讯录***********\n");
	printf("***********7.退出     ***********\n");
}