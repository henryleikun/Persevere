#pragma once
#include <iostream>
#include <cassert>
#include <string>
using namespace std;
//AVL树 在二叉搜索树的基础上 多了平衡的操作
//插入和删除都涉及到失衡的调整 有平衡因子的概念 这里也要实现处理失衡的算法即旋转的算法
//这里就实现一个key-value模型的AVL树 主要是想借此也了解一下pair(map容器里的value_type)

// 首先要说明 AVL树和红黑树都是了解性的学习 主要学习其内部实现原理 是否能手撕 放到其次
// 这里研究这两棵树 主要是为了把对应树的性质 原理掌握清楚就行 AVL树和后续红黑树的删除其实
// 在了解了插入后 对了解这两棵树的性质帮助就不是那么大了 其实就是 插入就已经很有代表性了 但是删除也要了解
// 这里会看情况 进行手撕 删除 无非就是情况 更复杂 其实都还好

template<class K,class V>
struct AVLtreeNode {
	AVLtreeNode<K, V>* _left;
	AVLtreeNode<K, V>* _right;
	AVLtreeNode<K, V>* _parent;
	//AVL树结点是一个三叉链 _parent指向自己的父亲这样在自己平衡因子变化的时候
	//才能迅速去更新父节点的平衡因子
	pair<K, V> _val;
	
	int _bf;//平衡因子

	AVLtreeNode(const pair<K, V>& val = pair<K, V>()) 
		:_val(val), _left(nullptr),_right(nullptr),_parent(nullptr),_bf(0){

	}
};

template<class K,class V>
class AVLtree {
	typedef AVLtreeNode<K,V> Node;
private:
	Node* _root = nullptr;
protected:
	//先旋转 再调整平衡因子
	void RotateR(Node* parent) {//右单旋
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* parentparent = parent->_parent;

		//先调整指向
		parent->_left = subLR;
		subL->_right = parent;
		//调指向的父节点
		parent->_parent = subL;
		if (parent == _root) {//失衡点为根节点 要更新_root的指向 parentparent == nullptr
			_root = subL;
		}
		else {//不是根节点 也即处理的是一棵局部的树 要调节parent的parent的指向
			if (parentparent->_left == parent) {
				parentparent->_left = subL;
			}
			else {
				parentparent->_right = subL;
			}
		}
		subL->_parent = parentparent;

		if (subLR) {//subLR可能为空 
			subLR->_parent = parent;
		}

		//调平衡因子
		subL->_bf = 0;
		parent->_bf = 0;
	}

	void RotateL(Node* parent) {//左单旋 跟右单旋类似
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* parentparent = parent->_parent;

		parent->_right = subRL;
		subR->_left = parent;

		parent->_parent = subR;
		if (subRL)
			subRL->_parent = parent;

		if (parent == _root) {
			_root = subR;
		}
		else {
			if (parentparent->_left == parent)
				parentparent->_left = subR;
			else
				parentparent->_right = subR;
		}
		subR->_parent = parentparent;

		parent->_bf = subR->_bf = 0;

	}

	//下面两个可以复用上面两个函数 平衡因子需要再处理一下
	void RotateLR(Node* parent) {//左单旋再右单旋
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(parent->_left);
		RotateR(parent);

		//调节bf
		if (bf == 0) {//subLR自己就是新增结点 即对应h为零
			subL->_bf = subLR->_bf = parent->_bf = 0;//其实再Rotate里就已经搞成0了
		}
		else if (bf == -1) {
			subL->_bf = subLR->_bf = 0;
			parent->_bf = 1;
		}
		else if(bf == 1){
			parent->_bf = subLR->_bf = 0;
			subL->_bf = -1;
		}
		else {
			assert(false);
		}
	}

	void RotateRL(Node* parent) {//右单旋再左单旋
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		RotateL(parent->_right);
		RotateR(parent);

		//调节bf
		if (bf == 0) {//subRL自己就是新增结点 即对应h为零
			subRL->_bf = subR->_bf = parent->_bf = 0;//其实再Rotate里就已经搞成0了
		}
		else if (bf == -1) {
			subR->_bf = 1;
			parent->_bf = subRL->_bf = 0;
		}
		else if(bf == 1){
			parent->_bf = -1;
			subR->_bf = subRL->_bf = 0;
		}
		else {
			assert(false);
		}
	}

	void _Inorder(Node* root) {
		if (root == nullptr)
			return;

		_Inorder(root->_left);
		cout << root->_val.first << " " << root->_val.second << endl;
		_Inorder(root->_right);
	}

	int Height(Node* root) {
		if (root == nullptr)
			return 0;

		int left_height = Height(root->_left);
		int right_height = Height(root->_right);

		return left_height > right_height ? left_height + 1 : right_height + 1;
	}
	
	bool _Is_balance(Node* root) {
		if (root == nullptr) {
			return true;
		}

		int left = Height(root->_left);
		int right = Height(root->_right);

		if (right - left != root->_bf)//用来测试
		{
			cout << root->_val.first << "平衡因子异常" << endl;
			return false;
		}

		if (abs(left - right) > 1)	
			return false;

		return _Is_balance(root->_left) && _Is_balance(root->_right);
	}

	void _Destory(Node* root) {
		if (root == nullptr)
			return;

		_Destory(root->_left);
		_Destory(root->_right);

		delete root;
	}
public:
	AVLtree() = default;

	bool Insert(const pair<K,V>& val) {
		if (_root == nullptr) {
			_root = new Node(val);
			return true;
		}

		Node* prev = nullptr;
		Node* cur = _root;
		while (cur) {
			if (val.first < cur->_val.first) {
				prev = cur;
				cur = cur->_left;
			}
			else if (val.first > cur->_val.first) {
				prev = cur;
				cur = cur->_right;
			}
			else {
				return false;
			}
		}

		cur = new Node(val);//cur是prev->_left or _right的copy 这个指向不会改变原树 要重新设置prev的指向

		if (val.first < prev->_val.first) {
			prev->_left = cur;
			cur->_parent = prev;
		}
		else {
			prev->_right = cur;
			cur->_parent = prev;
		}
		//以上便是 正常BStree的插入过程 这里调了一下_parent
		//下面便是对平衡因子和失衡的处理 

		//cur现在指向新插入的结点 而prev指向对应父节点 新插入的结点的bf是0
		//记住 插入的对象也是AVL树，所以插入之前的树的所有节点的平衡因子绝对值都小于2
		//循环是为了向上更新平衡因子或者找到第一个失衡的结点 或者是插入成功
		while (prev) {//调节到头 即prev==_root->_parent
			if (prev->_left == cur) {
				prev->_bf--;//插到左边 平衡因子-1
			}
			else {
				prev->_bf++;//插到右边 bf(balance factor)+1
			}


			if (prev->_bf == 0) {//插入之前一定是+-1 插入后的平衡因子为0 一定平衡
				return true;
			}
			else if (prev->_bf == 1 || prev->_bf == -1) {//在变成+-1之前 自己一定是0
				                                        //这时是会影响上面的平衡因子的，需要向上更新平衡因子
				cur = prev;
				prev = prev->_parent;
			}
			else if (prev->_bf == -2 || prev->_bf == 2) {//发现失衡的因子 进行处理
				//失衡的因子右四种情况 分别也右不同的旋转处理方法
				if (prev->_bf == -2 && cur->_bf == -1) {//LL 右单旋
					RotateR(prev);
				}
				else if (prev->_bf == 2 && cur->_bf == 1) {//RR 左单旋
					RotateL(prev);
				}
				else if (prev->_bf == -2 && cur->_bf == 1) {//LR 先左单旋再右单旋
					RotateLR(prev);
				}
				else if (prev->_bf == 2 && cur->_bf == -1) {//RL 先右单旋再左单旋
					RotateRL(prev);
				}
				else {
					assert(false);
				}

				//旋转后 这棵树在原来的基础上一定平衡了 
				//旋转降低了这颗子树的高度，恢复到跟插入前一样的高度，所以对上一层没有影响，不用继续更新
				//所以旋转完之后 就完成了插入动作
				return true;
			}
			else {//绝对值超出2 说明 树已经不是AVL树了 处理的机会都没有了
				assert(false);
			}
		}
		
		return true;
	}

	bool Erase(const pair<K,V>& val) {

	}//删除 做了解 不要求可以手撕 但要知道流程 这个先放在这 
	//目前的大思路还是 查找 删除 调整
	//先按二叉搜索树的的查找方式查找val.first 然后同二叉搜索树一样
	//删除的结点有三种情况 左树空(删除该节点 父节点指向其右子树) 右树空(删除该节点 父节点指向其左子树) 
	//俩都不为空(替换 去右树找最左结点 替换成上两种情况)
	//对于调整 如果是删除左树 父节点bf++ 删除右树bf-- 再看是否需要调节平衡因子
	//如果bf变为1 or -1则不需要改变 删除成功原来是0(两边肯定都有) 删完子树高度不变
	//bf为0 向上更新平衡因子(原来一定有一边高) bf为-2 or 2旋转
	//具体实现的源码 这里暂时放一下 之后再算法导论和数据结构黑书里学习 

	bool Is_balance() {//判断是否平衡 无非就是看两边树的高度是否相差小于2
		return _Is_balance(_root);
	}

	void Inorder() {
		_Inorder(_root);
	}

	Node* Find(const pair<K,V>& val) {
		Node* cur = _root;

		while (cur) {
			if (val.first < cur->_val.first) {
				cur = cur->_left;
			}
			else if (val.first > cur->_val.first) {
				cur = cur->_right;
			}
			else {
				return cur;
			}
		}

		return nullptr;
	}

	~AVLtree() {
		_Destory(_root);
	}
};
