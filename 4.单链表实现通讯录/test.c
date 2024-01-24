#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include "contact.h"

typedef struct ListNode Contact;

void menu();

int main() {
	Contact* pcon;
	ContactInit(&pcon);//�ձ���
	int choice;
	char name[NAME];
	menu();
	printf("����������ѡ��");
	scanf("%d", &choice);

	while (1) {
		if (choice <= 7 && choice >= 1) {
			switch (choice) {
			case 1: {
				Addcontact(&pcon);
				break;
			}
			case 2: {
				printf("����������Ҫɾ������ϵ��������");
				scanf("%s", name);
				Deletecontact(&pcon, name);
				printf("ɾ���ɹ���\n");
				break;
			}
			case 3: {
				printf("����������Ҫ���ҵ���ϵ��������");
				scanf("%s", name);
				Searchcontact(&pcon, name);
				break;
			}
			case 4: {
				printf("����������Ҫ�޸ĵ���ϵ��������");
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
				printf("���ٳɹ���\n");
				break;
			}
			case 7: {
				printf("�����˳���...\n");
				system("pause");
				exit(EXIT_SUCCESS);
			}

			}
			system("pause");
			system("cls");

			menu();
			printf("����������Ҫִ�еĹ��ܣ�");
			scanf("%d", &choice);
		}
		else {
			printf("��������������ѡ��!\n");
			system("pause");
			system("cls");
			menu();
			printf("����������Ҫִ�еĹ��ܣ�");
			scanf("%d", &choice);
		}
	}

	return 0;
}

void menu() {
	printf("***********ͨѶ¼����ϵͳ***********\n");
	printf("***********1.�����ϵ��***********\n");
	printf("***********2.ɾ����ϵ��***********\n");
	printf("***********3.������ϵ��***********\n");
	printf("***********4.�޸���ϵ��***********\n");
	printf("***********5.չʾͨѶ¼***********\n");
	printf("***********6.����ͨѶ¼***********\n");
	printf("***********7.�˳�     ***********\n");
}