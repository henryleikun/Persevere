#define _CRT_SECURE_NO_WARNINGS 1
//主要就二叉树的非递归遍历和构造来进行实现
//后序可能还会补充一些二叉树的基础接口实现
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <vector>
using namespace std;
typedef int BTdatatype;

typedef struct BTnode {
	BTdatatype _val;
	BTnode* _left;
	BTnode* _right;

	BTnode(BTdatatype val = BTdatatype()):_val(val),_right(nullptr),_left(nullptr) {

	}
};//树节点

BTnode* BuyNode(BTdatatype val) {
	BTnode* newnode = new BTnode(val);
	
	return newnode;
}

BTnode* BT_creat_by_hand() {//Just for test
	BTnode* node1 = BuyNode(1);
	BTnode* node2 = BuyNode(2);
	BTnode* node3 = BuyNode(3);
	BTnode* node4 = BuyNode(4);
	BTnode* node5 = BuyNode(5);
	BTnode* node6 = BuyNode(6);
	BTnode* node7 = BuyNode(7);

	node1->_left = node2;
	node1->_right = node3;
	node2->_left = node4;
	node3->_left = node5;
	node3->_right = node6;
	node2->_right = node7;

	return node1;//返回根节点
}

int BTreeSize(BTnode* root) {//求二叉树的节点个数  个数等于左子树个数加上右子树个数加1
	if (root == NULL)
		return 0;

	return BTreeSize(root->_left) + BTreeSize(root->_right) + 1;
}


//后序销毁二叉树
void BTreeDestroy(BTnode* root) {
	if (root == NULL)
		return;

	BTreeDestroy(root->_left);
	BTreeDestroy(root->_right);
	delete root;
}

//从下到上 从右往左 层序遍历
//思想：从根开始进队列 出的时候将左右子树压入，但是先压入左，再压右，再将刚才出的进栈
void Level_order_reverse(BTnode* root) {
	if (root == nullptr)
		return;

	queue<BTnode*> q;
	stack<BTnode*> s;

	q.push(root);

	while (!q.empty()) {
		BTnode* temp_node = q.front();
		q.pop();

		if (temp_node->_left)
			q.push(temp_node->_left);

		if (temp_node->_right)
			q.push(temp_node->_right);

		s.push(temp_node);
	}

	while (!s.empty()) {
		cout << s.top()->_val << " ";
		s.pop();
	}

}

//非递归实现前序遍历和中序遍历
void Prevorder_noR(BTnode* root) {//前序
	BTnode* cur = root;

	vector<BTdatatype> v;//遍历的数存到v中
	stack<BTnode*> s;//存左树结点

	while (cur || !s.empty()) {//cur为空且s里也没有要处理的结点了
		
		while (cur) {//当前子树不为空 将其左树进栈
			v.push_back(cur->_val);//进栈的同时也是在访问

			s.push(cur);
			cur = cur->_left;
		}//在进栈的同时其实也已经访问了根 而最后一个结点的左是null 所以下一步就是访问右
		//访问完后这个结点也对应着上个父节点的左 所以接着访问右 也就是stack里的top
		

		BTnode* temp = s.top();
		s.pop();

		cur = temp->_right;
	}

	for (auto e : v) {
		cout << e << " ";
	}

	cout << endl;
}

void Inorder_noR(BTnode* root) {//中序
	BTnode* cur = root;//其实不用搞个cur 但我不想用root root在递归里看着比较舒服
	
	stack<BTnode*> s;
	vector<BTdatatype> v;


	//还是先让右树全入栈 但先不访问 从栈里取出来的时候再访问
	while (cur || !s.empty()) {
		while (cur) {
			s.push(cur);
			cur = cur->_left;
		}//出来的时候相当于已经访问过最左树了 下面就是访问栈里的那个

		BTnode* temp = s.top();
		s.pop();
		v.push_back(temp->_val);//这时候访问

		cur = temp->_right;
	}

	for (auto e : v) {
		cout << e << " ";
	}

	cout << endl;
}
//前序和中序类似 思路都是先遍历左树到底，然后进栈，变换访问顺序去进行遍历
//注意两个循环设立的意义

/*
非递归实现后序遍历
后序遍历相较于前中序有所不同 我可以像上面一样控制访问顺序
先让左树遍历入栈 然后访问 访问完后 访问右树 然后就要访问栈里第一个根 但访问这个根又要走一遍循环
同样的逻辑 又要走右树，其实已经走过了。利用一个flag可以？ 不行 因为要处理多个结点 多个结点不能用一个
flag表示 所以第一个方法就是给每个结点都配置一个flag 0表示没访问过，1表示访问过了
用一个栈来随着循环的进行来存储这些flag值  这个方法相对来讲比较浪费空间
这里有第二个方法就是利用一个prev指针来指向上一次访问的结点 核心思路是：
遍历左树并入栈 先拿到最左根 判断 根的右边是否为空 或者是否已访问过 为空或已访问过就对根处理 然后pop掉
接着对栈里下一个根处理;不为空 就对右树进行子问题处理 交给下一层循环*/
void Backorder_noR(BTnode* root) {
	BTnode* cur = root;
	BTnode* prev = nullptr;
	stack<BTnode*> s;
	vector<BTdatatype> v;

	while (cur || !s.empty()) {
		while (cur) {
			s.push(cur);
			cur = cur->_left;
		}//左树先全入栈

		BTnode* top = s.top();
		
        //top的右树为空或者右树已被访问过(prev == top->_right)
		if (top->_right == nullptr || prev == top->_right) {//访问过 或者不用访问 只需要处理top结点就行
			v.push_back(top->_val);
			s.pop();
			prev = top;//记录
		}
		else {//没访问过 对右子树利用子问题来处理
			cur = top->_right;
		}
	}

	for (auto e : v) {
		cout << e << " ";
	}

	cout << endl;
}


//已知前序和中序 构建对应二叉树
//我是如何去确定递归函数的参数的
//root用来构建树 肯定传引用 对应了两个序列也肯定要传
//i代表着preorder里的根的下标 [begin,end]是中序里要研究的区间
//因为通过前序和i可以找到根 而通过这个根可以将中序划分成两个区间begin k-1 k+1 end
//而i的下一个位置 i+1必定也是一个根 我们知道左树结点的个数(k-1 - begin + 1)
//i + 左树节点个数 + 1就是右树根的下标然后就是将对应左树右树的区间递归下去 根的下标也是
void _buildTree_by_pre_in(BTnode*& root, vector<int>& preorder, int i, vector<int>& inorder, int begin, int end) {
	if (begin == end) {
		root = new BTnode(inorder[begin]);
		return;
	}
	else if (begin > end)
		return;

	for (int k = begin; k <= end; k++) {
		if (preorder[i] == inorder[k]) {
			root = new BTnode(preorder[i]);
			//begin k-1 k+1 end
			_buildTree_by_pre_in(root->_left, preorder, i + 1, inorder, begin, k - 1);
			_buildTree_by_pre_in(root->_right, preorder, i + k - begin + 1, inorder, k + 1, end);
			return;
		}
	}
}

//杭哥的这个更简洁
BTnode* _buildTree_by_pre_in2(vector<int>& pre, int& prei, vector<int>& in,
	int begin, int end) {
	if (begin > end)
		return nullptr;

	int k = begin;
	while (k <= end) {
		if (pre[prei] == in[k]) {
			break;
		}

		k++;
	}

	//前序是先访问根 prei++就可以成为下一个根
	BTnode* root = new BTnode(pre[prei++]);
	root->_left = _buildTree_by_pre_in2(pre, prei, in, begin, k - 1);
	root->_right = _buildTree_by_pre_in2(pre, prei, in, k + 1, end);

	return root;
}
//我们两个的思路总体是一致的，主要两点不同，一是递归函数的返回值 我的是空
//我主要传入root的引用 直接在递归的同时串联起整个树 他的主要是 通过递归的返回值
//进行进行串联 二是 我对前序序列根位置的确定 他是通过prei的引用 每层都++
//而++代表了一个结点的使用 在划分区间的同时也遍历了前序的序列，而我是通过 
//前序的根先确定区间 再根据区间的长度(左子树 右子树的节点个数)直接跳到对应的
//树的根下标

BTnode* buildTree_by_pre_in(vector<int>& preorder, vector<int>& inorder) {
	BTnode* root;
	_buildTree_by_pre_in(root, preorder, 0, inorder, 0, inorder.size() - 1);
	return root;

	// int index = 0;
	// return _buildTree_by_pre_in2(preorder,index,inorder,0,inorder.size()-1);
}


//已知中序和后序构建对应二叉树
//按照前序 中序来 后序就倒着来 先根 再右子树 再左子树 这个就按杭哥的思路写的
BTnode* _buildTree_by_in_post(vector<int>& inorder, int begin, int end
	, vector<int>& postorder, int& index) {
	if (begin > end)
		return nullptr;

	int k = begin;
	while (k <= end) {
		if (inorder[k] == postorder[index])
			break;

		++k;
	}//找到k 划分中序区间为 begin k-1 k+1 end

	BTnode* root = new BTnode(postorder[index--]);
	root->_right = _buildTree_by_in_post(inorder, k + 1, end, postorder, index);
	root->_left = _buildTree_by_in_post(inorder, begin, k - 1, postorder, index);

	return root;
}


BTnode* buildTree_by_in_post(vector<int>& inorder, vector<int>& postorder) {
	int index = postorder.size() - 1;
	return _buildTree_by_in_post(inorder, 0, inorder.size() - 1, postorder, index);
}

int main() {
	//BTnode* root = BT_creat_by_hand();

	/*cout << "前序：";
	Prevorder_noR(root);
	cout << "中序：";
	Inorder_noR(root);
	cout << "后序：";
	Backorder_noR(root);*/

	//BTreeDestroy(root);

	//=======================================================
	vector<int> preorder{ 3,9,20,15,7 };
	vector<int> inorder{ 9,3,15,20,7 };

	BTnode* root = buildTree_by_pre_in(preorder,inorder);

	Backorder_noR(root);//后序遍历一下

	return 0;
}