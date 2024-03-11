#define _CRT_SECURE_NO_WARNINGS 1

#include "BinaryTree.h"



int main() {
	BTnode* root = BT_creat_by_hand();

	//遍历
	PrevOrder(root);
	printf("\n");
	MidOrder(root);
	printf("\n");
	BackOrder(root);
	printf("\n");

	LevelOrder(root);
	printf("\n");

	//求节点个数
	printf("节点个数：%d ",BTreeSize(root));
	printf("\n");

	printf("第三层有%d个节点",Klevelsize(root, 3));
	printf("\n");


	printf("叶节点：%d", Leafsize(root));
	printf("\n");

	printf("深度：%d", BTreeHeight(root));
	printf("\n");

	if (BTreeFind(root, 4))
		printf("找到了！\n");
	return 0;
}