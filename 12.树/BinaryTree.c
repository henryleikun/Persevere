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

	return node1;//返回根节点
}

void  PrevOrder(BTnode* root) {//前序 根 左子树 右子树
	if (root == NULL) {//空树
		printf("N ");
		return;
	}

	printf("%d ", root->val);
	PrevOrder(root->left);
	PrevOrder(root->right);
}

void  MidOrder(BTnode* root) {//中序  左子树 根 右子树
	if (root == NULL) {//空树
		printf("N ");
		return;
	}

	MidOrder(root->left);
	printf("%d ", root->val);
	MidOrder(root->right);
}

void  BackOrder(BTnode* root) {//后序  左子树 右子树 根
	if (root == NULL) {//空树
		printf("N ");
		return;
	}

	BackOrder(root->left);
	BackOrder(root->right);
	printf("%d ", root->val);
}


void LevelOrder(BTnode* root) {//层序遍历 迭代法 利用 队列完成 父亲出的时候把他孩子带进队列
	if (root == NULL)
		return;

	Queue q;
	InitiQueue(&q);

	QueuePush(&q, root);
	
	while (!Is_empty(&q)) {
		//取父节点
		BTnode* front = QueueFront(&q);
		QueuePop(&q);

		/*if (front == NULL) {
			printf("N ");
			continue;
		}*/

		printf("%d ", front->val);
		
		//入子节点
		//QueuePush(&q, front->left);
		//QueuePush(&q, front->right);  这个是打印N的版本


		if (front->left)
			QueuePush(&q, front->left);

		if (front->right)
			QueuePush(&q, front->right);
	}

	DestroyQueue(&q);
}


int BTreeSize(BTnode* root) {//求二叉树的节点个数  个数等于左子树个数加上右子树个数加1
	if (root == NULL)
		return 0;

	return BTreeSize(root->left) + BTreeSize(root->right) + 1;
}

int Klevelsize(BTnode* root, int k) {//第k层节点的个数
	assert(k > 0);

	if (root == NULL)
		return 0;

	if (k == 1)
		return 1;

	return Klevelsize(root->left,k-1) + Klevelsize(root->right,k-1);
}

int Leafsize(BTnode* root) {//叶节点个数
	if (root == NULL)
		return 0;

	if (root->left == NULL && root->right == NULL)
		return 1;

	return Leafsize(root->left) + Leafsize(root->right);
}

int BTreeHeight(BTnode* root) {//二叉树深度
	if (root == NULL)
		return 0;

	/*if (root->left == NULL && root->right == NULL)
		return 1;*/ //这句有点多余 下面的return能处理这个给情况

	int leftheight = BTreeHeight(root->left);
	int rightheight = BTreeHeight(root->right);

	return  (leftheight > rightheight ? leftheight : rightheight) + 1;

	//return BTreeHeight(root->left) > BTreeHeight(root->right)
    // ? BTreeHeight(root->left) + 1 : BTreeHeight(root->right) + 1;

	//拒绝这个 这个太恐怖了 递归调用两次后确定了大小 但没有确定值 又要重新递归大的那个子树
	//如果树的深度比较大顶层的调用要调根本不敢想的次数 很恐怖这样写

}


BTnode* BTreeFind(BTnode* root, BTdatatype x) {//找为x的节点
	if (root == NULL)
		return NULL;

	if (root->val == x)
		return root;

	BTnode* tmp = BTreeFind(root->left, x);
	if (tmp)
		return tmp;
	
	return BTreeFind(root->right, x);
}
