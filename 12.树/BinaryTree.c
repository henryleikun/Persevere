#define _CRT_SECURE_NO_WARNINGS 1

#include "BinaryTree.h"


BTnode* BuyNode(BTdatatype val) {
	BTnode* newnode = (BTnode*)malloc(sizeof(BTnode));
	newnode->val = val;
	newnode->left = NULL;
	newnode->right = NULL;

	return newnode;
}

BTnode* BT_creat_by_hand() {
	BTnode* node1 = BuyNode(1);
	BTnode* node2 = BuyNode(2);
	BTnode* node3 = BuyNode(4);
	BTnode* node4 = BuyNode(3);
	BTnode* node5 = BuyNode(5);
	BTnode* node6 = BuyNode(6);
	//BTnode* node7 = BuyNode(7);

	node1->left = node2;
	node1->right = node3;
	node2->left = node4;
	node3->left = node5;
	node3->right = node6;
	//node4->left = node7;

	return node1;//���ظ��ڵ�
}

void  PrevOrder(BTnode* root) {//ǰ�� �� ������ ������
	if (root == NULL) {//����
		printf("N ");
		return;
	}

	printf("%d ", root->val);
	PrevOrder(root->left);
	PrevOrder(root->right);
}

void  MidOrder(BTnode* root) {//����  ������ �� ������
	if (root == NULL) {//����
		printf("N ");
		return;
	}

	MidOrder(root->left);
	printf("%d ", root->val);
	MidOrder(root->right);
}

void  BackOrder(BTnode* root) {//����  ������ ������ ��
	if (root == NULL) {//����
		printf("N ");
		return;
	}

	BackOrder(root->left);
	BackOrder(root->right);
	printf("%d ", root->val);
}


void LevelOrder(BTnode* root) {//������� ������ ���� ������� ���׳���ʱ��������Ӵ�������
	if (root == NULL)
		return;

	Queue q;
	InitiQueue(&q);

	QueuePush(&q, root);
	
	while (!Is_empty(&q)) {
		//ȡ���ڵ�
		BTnode* front = QueueFront(&q);
		QueuePop(&q);

		/*if (front == NULL) {
			printf("N ");
			continue;
		}*/

		printf("%d ", front->val);
		
		//���ӽڵ�
		//QueuePush(&q, front->left);
		//QueuePush(&q, front->right);  ����Ǵ�ӡN�İ汾


		if (front->left)
			QueuePush(&q, front->left);

		if (front->right)
			QueuePush(&q, front->right);
	}

	DestroyQueue(&q);
}


int BTreeSize(BTnode* root) {//��������Ľڵ����  ����������������������������������1
	if (root == NULL)
		return 0;

	return BTreeSize(root->left) + BTreeSize(root->right) + 1;
}

int Klevelsize(BTnode* root, int k) {//��k��ڵ�ĸ���
	assert(k > 0);

	if (root == NULL)
		return 0;

	if (k == 1)
		return 1;

	return Klevelsize(root->left,k-1) + Klevelsize(root->right,k-1);
}

int Leafsize(BTnode* root) {//Ҷ�ڵ����
	if (root == NULL)
		return 0;

	if (root->left == NULL && root->right == NULL)
		return 1;

	return Leafsize(root->left) + Leafsize(root->right);
}

int BTreeHeight(BTnode* root) {//���������
	if (root == NULL)
		return 0;

	/*if (root->left == NULL && root->right == NULL)
		return 1;*/ //����е���� �����return�ܴ�����������

	int leftheight = BTreeHeight(root->left);
	int rightheight = BTreeHeight(root->right);

	return  (leftheight > rightheight ? leftheight : rightheight) + 1;

	//return BTreeHeight(root->left) > BTreeHeight(root->right)
    // ? BTreeHeight(root->left) + 1 : BTreeHeight(root->right) + 1;

	//�ܾ���� ���̫�ֲ��� �ݹ�������κ�ȷ���˴�С ��û��ȷ��ֵ ��Ҫ���µݹ����Ǹ�����
	//���������ȱȽϴ󶥲�ĵ���Ҫ������������Ĵ��� �ֲܿ�����д

}


BTnode* BTreeFind(BTnode* root, BTdatatype x) {//��Ϊx�Ľڵ�
	if (root == NULL)
		return NULL;

	if (root->val == x)
		return root;

	BTnode* tmp = BTreeFind(root->left, x);
	if (tmp)
		return tmp;
	
	return BTreeFind(root->right, x);
}
