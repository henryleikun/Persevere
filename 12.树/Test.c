#define _CRT_SECURE_NO_WARNINGS 1

#include "BinaryTree.h"



int main() {
	BTnode* root = BT_creat_by_hand();

	//����
	PrevOrder(root);
	printf("\n");
	MidOrder(root);
	printf("\n");
	BackOrder(root);
	printf("\n");

	LevelOrder(root);
	printf("\n");

	//��ڵ����
	printf("�ڵ������%d ",BTreeSize(root));
	printf("\n");

	printf("��������%d���ڵ�",Klevelsize(root, 3));
	printf("\n");


	printf("Ҷ�ڵ㣺%d", Leafsize(root));
	printf("\n");

	printf("��ȣ�%d", BTreeHeight(root));
	printf("\n");

	if (BTreeFind(root, 4))
		printf("�ҵ��ˣ�\n");
	return 0;
}