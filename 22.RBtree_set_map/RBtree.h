#pragma once
#include <iostream>
#include <string>
#include <utility>
using namespace std;
//构建一棵k,v型的红黑树 然后在这个基础上去封装map和set(二者都是底层为红黑树的关联式容器)
//set-->key型  map--->key value型
//和AVL树一样 不实现 而且搜索树是不能修改的

//enum Color {
//	RED,BLACK
//};//枚举 RED 0 BLACK 1
//
//template<class K,class V>
//struct RBtreeNode {
//	RBtreeNode<K, V>* _left;
//	RBtreeNode<K, V>* _right;
//	RBtreeNode<K, V>* _parent;//和AVL树一样都是三叉链
//
//	pair<K, V> _kv;
//
//	Color _col;//红黑树的特色
//
//	RBtreeNode(const pair<K,V>& kv = pair<K,V>())
//	:_left(nullptr),_right(nullptr),_parent(nullptr),_kv(kv),_col(RED){
//		//新节点默认是红色 可能出问题 但如果 默认是黑色那就每条路径都出问题 插入之前就是红黑树 
//		//每条路径黑色节点数量相同 插入后多一个后果可想而知
//    
//	}
//};
//
//template<class K,class V>
//class RBtree {
//	typedef RBtreeNode<K, V> Node;
//private:
//	Node* _root = nullptr;//相当于默认构造
//protected:
//	void RotateR(Node* parent) {//右单旋
//		Node* subL = parent->_left;
//		Node* subLR = subL->_right;
//		Node* parentparent = parent->_parent;
//
//		//先调整指向
//		parent->_left = subLR;
//		subL->_right = parent;
//		//调指向的父节点
//		parent->_parent = subL;
//		if (parent == _root) {//失衡点为根节点 要更新_root的指向 parentparent == nullptr
//			_root = subL;
//		}
//		else {//不是根节点 也即处理的是一棵局部的树 要调节parent的parent的指向
//			if (parentparent->_left == parent) {
//				parentparent->_left = subL;
//			}
//			else {
//				parentparent->_right = subL;
//			}
//		}
//		subL->_parent = parentparent;
//
//		if (subLR) {//subLR可能为空 
//			subLR->_parent = parent;
//		}
//	}
//
//	void RotateL(Node* parent) {//左单旋 跟右单旋类似
//		Node* subR = parent->_right;
//		Node* subRL = subR->_left;
//		Node* parentparent = parent->_parent;
//
//		parent->_right = subRL;
//		subR->_left = parent;
//
//		parent->_parent = subR;
//		if (subRL)
//			subRL->_parent = parent;
//
//		if (parent == _root) {
//			_root = subR;
//		}
//		else {
//			if (parentparent->_left == parent)
//				parentparent->_left = subR;
//			else
//				parentparent->_right = subR;
//		}
//		subR->_parent = parentparent;
//
//	}
//
//	void _Inorder(Node* root) {
//		if (root == nullptr)
//			return;
//
//		_Inorder(root->_left);
//		cout << root->_kv.first << "-" << root->_kv.second << endl;
//		_Inorder(root->_right);
//	}
//
//	void _Destory(Node* root) {
//		if (root == nullptr)
//			return;
//
//		_Destory(root->_left);
//		_Destory(root->_right);
//
//		delete root;
//	}
//
//	size_t _size(Node* root) {
//		if (root == nullptr)
//			return 0;
//
//		return _size(root->_left) + _size(root->_right) + 1;
//	}
//
//	int _Height(Node* root) {
//		if (root == nullptr)
//			return 0;
//
//		int leftHeight = _Height(root->_left);
//		int rightHeight = _Height(root->_right);
//	
//		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
// 	}
//
//	bool Check(Node* root,size_t ref,size_t numBlack) {
//    //主要看两点 检查 是否用连续的红结点 检查每条路径是否黑色结点都相同
//    //如何检查黑色结点数量 我们可以先走一条路径去记录这条路径下的黑色数量作为参考值 
//    //然后去遍历每条路径 遍历到最后的时候 看是否与ref相等 不相等直接false
//		if (root == nullptr) {
//			if (numBlack == ref)
//				return true;
//			else
//				return false;
//		}
//
//
//		if (root->_col == BLACK)
//			numBlack++;
//		else {//为红 一定不是_root根节点 就一定有parent
//			if (root->_parent->_col == RED)
//				return false;//如果红结点的父亲也是红结点 则出问题
//		}
//
//		return Check(root->_right,ref,numBlack) && Check(root->_left,ref,numBlack);
//	}
//
//public:	//构造 拷贝构造 赋值运算符这些也没什么实际意义 不会用到 就不实现了
//	bool Insert(const pair<K, V>& kv) {
//		if (_root == nullptr) {
//			_root = new Node(kv);
//			_root->_col = BLACK;
//			return true;
//		}
//
//		Node* cur = _root;
//		Node* parent = nullptr;
//
//		while (cur) {
//			if (kv.first < cur->_kv.first) {
//				parent = cur;
//				cur = cur->_left;
//			}
//			else if(kv.first > cur->_kv.first){
//				parent = cur;
//				cur = cur->_right;
//			}
//			else {
//				return false;
//			}
//		}
//
//		cur = new Node(kv);//默认_col已经是红色了
//		if (kv.first < parent->_kv.first) {
//			parent->_left = cur;
//			cur->_parent = parent;
//		}
//		else {
//			parent->_right = cur;
//			cur->_parent = parent;
//		}
//
//		//上述完成了插入 而下面就要检查 是否违反红黑树的规则 并进行调整
//
//		while (parent && parent->_col == RED) {//parent存在且是红色
//			Node* grandfather = parent->_parent;//parent存在为红就一定有_parent
//			
//			if (parent == grandfather->_left) {//p在g的左边
//				Node* uncle = grandfather->_right;
//				/*     g
//					p     u
//				 c     c      */
//				if (uncle && uncle->_col == RED) {//uncle存在且为红 不管c在哪边都一样
//					parent->_col = uncle->_col = BLACK;
//					grandfather->_col = RED;
//
//					cur = grandfather;
//					parent = cur->_parent;
//
//					continue;//向上调整 直接去判断 新变的红结点 是否又出现双红的情况
//				}
//				else if(parent->_left == cur){//当uncle不存在或者uncle为黑时 
//					//uncle不管在不在 uncle最后都不用变色 这里只需要对cur在parent两边进行分情况处理就行
//					//也就是uncle为空 也把uncle当作黑来处理
//					RotateR(grandfather);
//					parent->_col = BLACK;
//					grandfather->_col = RED;
//				}
//				else {//parent->_right == cur
//					RotateL(parent);
//					RotateR(grandfather);
//					cur->_col = BLACK;
//					grandfather->_col = RED;
//				}
//
//				break; //针对后两种情况 旋完就可以break了
//			}
//			else {//镜像处理
//				/*     g
//					u     p
//				       c     c      */
//				Node* uncle = grandfather->_left;
//				if (uncle && uncle->_col == RED) {
//					parent->_col = uncle->_col = BLACK;
//					grandfather->_col = RED;
//
//					cur = grandfather;
//					parent = cur->_parent;
//
//					continue;
//				}
//				else if (parent->_right == cur) {
//					RotateL(grandfather);
//					parent->_col = BLACK;
//					grandfather->_col = RED;
//				}
//				else {//parent->_left == cur
//					RotateR(parent);
//					RotateL(grandfather);
//
//					cur->_col = BLACK;
//					grandfather->_col = RED;
//				}
//
//				break;
//			}
//		}
//		//出循环可能是向上调整变红的结点的父亲是黑色 也可能是调整到_root了(变红) 故这里要对这种情况处理
//		_root->_col = BLACK;
//
//		return true;
//	}
//
//	Node* Find(const pair<K, V>& kv) {
//		if (_root == nullptr)
//			return nullptr;
//
//		Node* cur = _root;
//
//		while (cur) {
//			if (kv.first < cur->_kv.first) {
//				cur = cur->_left;
//			}
//			else if (kv.first > cur->_kv.first) {
//				cur = cur->_right;
//			}
//			else {
//				return cur;
//			}
//		}
//
//		return nullptr;
//    }
//
//	void Inorder() {
//		_Inorder(_root);
//		cout << endl;
//	}
//
//	int size() {
//		return _size(_root);
//	}
//
//	int Height() {
//		return _Height(_root);
//	}
//
//	bool Is_RBtree() {//判断是否是红黑树
//		if (_root == nullptr)
//			return true;
//
//		Node* cur = _root;
//		int ref = 0;
//
//		while (cur) {
//			if (cur->_col == BLACK)
//				++ref;
//
//			cur = cur->_left;//记录最左路径的numBlack
//		}
//
//		return Check(_root, ref, 0);
//	}
//
//	~RBtree() {
//		_Destory(_root);
//	}
//};
//=======================================================================================================


//上面仅仅是实现的红黑树(无删除) 先要在上面的实现基础上 来对map set进行封装 map和set底层都是红黑树
//分别对应key-value key型 结合STL库里的具体实现 需要对红黑树做一些休整让他更适合去担任底层的角色
//因为底层相同 那红黑树的模板参数就要再重新设置 因为map的数据类型是pair 而set就仅仅是个key 所以对红黑树
//结点来讲 结点里的数据应该是个泛型 而不是确定的pair

enum Color {
	RED, BLACK
};//枚举 RED 0 BLACK 1

template<class T>
struct RBtreeNode {
	RBtreeNode<T>* _left;
	RBtreeNode<T>* _right;
	RBtreeNode<T>* _parent;

	T _data;

	Color _col;

	RBtreeNode(const T& data = T())
		:_left(nullptr), _right(nullptr), _parent(nullptr), _data(data), _col(RED) {

	}
};

//template<class T>
//struct KeyofValue {
//	operator()(const T& data) {
//
//	}
//};这怎么可能实现呢 你是模板就注定T要么key 要么pair 而你的返回值又想是key但你又如何从T里区分出key呢
//也就是你想RBtree<, , KeyofValue<key>/KeyofValue<pair<>>>这样吗 那你的实现就会出问题 正确应该在
//调用rbtree的地方直接定义各自的KeyofValue


//红黑树迭代器大致实现 部分可参考list的迭代器 
//和list的处理类似 我想通过一个模板去搞定普通迭代器和常迭代器 只有一个模板参数 要写多个模板才能实现那种
//引入模板参数 就可以解决代码重复的问题
template<class T,class Ref,class Ptr>
struct _RBtree_iterator {
	typedef RBtreeNode<T> Node;
	typedef _RBtree_iterator<T,Ref,Ptr> self;
	Node* _pnode;

	_RBtree_iterator(Node* pnode = nullptr) :_pnode(pnode) {

	}

	Ref operator*() {
		return _pnode->_data;
	}

	self& operator++() {//前置 
		//按中序走 左树 根 右树
		if (_pnode->_right == nullptr) {//回退
			Node* parent = _pnode->_parent;
			while (parent && parent->_right == _pnode) {
				_pnode = _pnode->_parent;
				parent = _pnode->_parent;
			}

			//if (parent == nullptr)//走到头了 也就是说原本pnode就指向了最后一个元素
			//	_pnode = nullptr;
			//else //不为空 作为找到父节点的左孩子的对应结点
			//	_pnode = parent;

			_pnode = parent;//上述一句话就解决
		}
		else {//右树不为空 找右树最左树
			Node* cur = _pnode->_right;

			while (cur->_left) {
				cur = cur->_left;
			}

			_pnode = cur;
		}

		return *this;
	}

	//其实后置没啥实际意义 但还是能用
	self& operator++(int) {//后置 
		self ret = *this;//默认的拷贝构造就行 指针指向传过去了

		if (_pnode->_right == nullptr) {//回退
			Node* parent = _pnode->_parent;
			while (parent && parent->_right == _pnode) {
				_pnode = _pnode->_parent;
				parent = _pnode->_parent;
			}

			_pnode = parent;
		}
		else {//右树不为空 找右树最左树
			Node* cur = _pnode->_right;

			while (cur->_left) {
				cur = cur->_left;
			}

			_pnode = cur;
		}

		return ret;
	}

	self& operator--() {//--跟++倒着走就行 
		//按中序走 右树 根 左树
		if (_pnode->_left == nullptr) {//回退
			Node* parent = _pnode->_parent;
			while (parent && parent->_left == _pnode) {
				_pnode = _pnode->_parent;	
				parent = _pnode->_parent;
			}

			_pnode = parent;
		}
		else {//左树不为空 找左树最右树
			Node* cur = _pnode->_left;

			while (cur->_right) {
				cur = cur->_right;
			}

			_pnode = cur;
		}

		return *this;
	}

	self& operator--(int) {//后置
		self ret = *this;

		if (_pnode->_left == nullptr) {//回退
			Node* parent = _pnode->_parent;
			while (parent && parent->_left == _pnode) {
				_pnode = _pnode->_parent;
				parent = _pnode->_parent;
			}

			_pnode = parent;
		}
		else {//左树不为空 找左树最右树
			Node* cur = _pnode->_left;

			while (cur->_right) {
				cur = cur->_right;
			}

			_pnode = cur;
		}

		return ret;
	}

	Ptr operator->() {
		return &_pnode->_data;
	}

	bool operator==(const self& rhs) {
		return _pnode == rhs._pnode;
	}

	bool operator!=(const self& rhs) {
		return _pnode != rhs._pnode;
	}

};

//KeyofValue的作用是取得T的key 再插入的时候 按上面的实现比较大小是比的first但当set(不是pair时)
//first就不存在 这就是语法错误 我要有一个更泛型的比较 其实就是一个仿函数
//红黑树结点的处理 让T这个模板参数去决定是key 还是key-value
//可能会觉得 有了T为什么还要K(K K表示set K pair去表示map) K的作用是提供T的关键字类型
//比如Find的时候要传key的参数 但是KeyofValue返回的是Key值 不能提供类型 故 这个K还是有必要的 
template<class K, class T,class KeyofValue>
class RBtree {
	typedef RBtreeNode<T> Node;
private:
	Node* _root = nullptr;
protected:
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

	}

	void _Inorder(Node* root) {
		KeyofValue key;

		if (root == nullptr)
			return;

		_Inorder(root->_left);
		cout << key(root->_data) << endl;
		_Inorder(root->_right);
	}

	void _Destory(Node* root) {
		if (root == nullptr)
			return;

		_Destory(root->_left);
		_Destory(root->_right);

		delete root;
	}

	size_t _size(Node* root) {
		if (root == nullptr)
			return 0;

		return _size(root->_left) + _size(root->_right) + 1;
	}

	int _Height(Node* root) {
		if (root == nullptr)
			return 0;

		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);

		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}

	bool Check(Node* root, size_t ref, size_t numBlack) {
		//主要看两点 检查 是否用连续的红结点 检查每条路径是否黑色结点都相同
		//如何检查黑色结点数量 我们可以先走一条路径去记录这条路径下的黑色数量作为参考值 
		//然后去遍历每条路径 遍历到最后的时候 看是否与ref相等 不相等直接false
		if (root == nullptr) {
			if (numBlack == ref)
				return true;
			else
				return false;
		}


		if (root->_col == BLACK)
			numBlack++;
		else {//为红 一定不是_root根节点 就一定有parent
			if (root->_parent->_col == RED)
				return false;//如果红结点的父亲也是红结点 则出问题
		}

		return Check(root->_right, ref, numBlack) && Check(root->_left, ref, numBlack);
	}

public:	//构造 拷贝构造 赋值运算符这些也没什么实际意义 不会用到 就不实现了
	//放到public里面
	typedef _RBtree_iterator<T, T&, T*> iterator;
	typedef _RBtree_iterator<T, const T&, const T*> const_iterator;

	iterator begin() {//返回最左结点指针
	    Node* cur = _root;
		if (cur == nullptr)
			return iterator(cur);

		while (cur->_left)
			cur = cur->_left;

		return iterator(cur);
	}

	iterator end() {//end就是空
		return iterator(nullptr);
	}

	const_iterator cbegin() const {
		Node* cur = _root;
		if (cur == nullptr)
			return const_iterator(cur);

		while (cur->_left)
			cur = cur->_left;

		return const_iterator(cur);
	}

	const_iterator cend() const {
		return const_iterator(nullptr);
	}

	//bool 库的标准
	//pair<iterator,bool>库的实现
	//pair<Node*,bool>简化一下 主要能让pair<iterator,bool>向pair<const_iterator,bool>转换
	pair<Node*,bool> Insert(const T& data) {
		KeyofValue Key;

		if (_root == nullptr) {
			_root = new Node(data);
			_root->_col = BLACK;
			return make_pair(_root,true);
		}

		Node* cur = _root;
		Node* parent = nullptr;

		while (cur) {
			if (Key(data) < Key(cur->_data)) {
				parent = cur;
				cur = cur->_left;
			}
			else if (Key(data) > Key(cur->_data)) {
				parent = cur;
				cur = cur->_right;
			}
			else {
				return make_pair(cur, false);
			}
		}

		cur = new Node(data);//默认_col已经是红色了
		if (Key(data) < Key(parent->_data)) {
			parent->_left = cur;
			cur->_parent = parent;
		}
		else {
			parent->_right = cur;
			cur->_parent = parent;
		}

		//上述完成了插入 而下面就要检查 是否违反红黑树的规则 并进行调整

		while (parent && parent->_col == RED) {//parent存在且是红色
			Node* grandfather = parent->_parent;//parent存在为红就一定有_parent

			if (parent == grandfather->_left) {//p在g的左边
				Node* uncle = grandfather->_right;
				/*     g
					p     u
				 c     c      */
				if (uncle && uncle->_col == RED) {//uncle存在且为红 不管c在哪边都一样
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;

					continue;//向上调整 直接去判断 新变的红结点 是否又出现双红的情况
				}
				else if (parent->_left == cur) {//当uncle不存在或者uncle为黑时 
					//uncle不管在不在 uncle最后都不用变色 这里只需要对cur在parent两边进行分情况处理就行
					//也就是uncle为空 也把uncle当作黑来处理
					RotateR(grandfather);
					parent->_col = BLACK;
					grandfather->_col = RED;
				}
				else {//parent->_right == cur
					RotateL(parent);
					RotateR(grandfather);
					cur->_col = BLACK;
					grandfather->_col = RED;
				}

				break; //针对后两种情况 旋完就可以break了
			}
			else {//镜像处理
				/*     g
					u     p
					   c     c      */
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_col == RED) {
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;

					continue;
				}
				else if (parent->_right == cur) {
					RotateL(grandfather);
					parent->_col = BLACK;
					grandfather->_col = RED;
				}
				else {//parent->_left == cur
					RotateR(parent);
					RotateL(grandfather);

					cur->_col = BLACK;
					grandfather->_col = RED;
				}

				break;
			}
		}
		//出循环可能是向上调整变红的结点的父亲是黑色 也可能是调整到_root了(变红) 故这里要对这种情况处理
		_root->_col = BLACK;

		return make_pair(cur,true);
	}

	//Node*
	iterator Find(const K& key) {
		KeyofValue Key;

		if (_root == nullptr)
			return iterator(nullptr);

		Node* cur = _root;

		while (cur) {
			if (key < Key(cur->_data)) {
				cur = cur->_left;
			}
			else if (key > Key(cur->_data)) {
				cur = cur->_right;
			}
			else {
				return iterator(cur);
			}
		}

		return iterator(nullptr);
	}

	void Inorder() {
		_Inorder(_root);
		cout << endl;
	}

	int size() {
		return _size(_root);
	}

	int Height() {
		return _Height(_root);
	}

	bool Is_RBtree() {//判断是否是红黑树
		if (_root == nullptr)
			return true;

		Node* cur = _root;
		int ref = 0;

		while (cur) {
			if (cur->_col == BLACK)
				++ref;

			cur = cur->_left;//记录最左路径的numBlack
		}

		return Check(_root, ref, 0);
	}

	~RBtree() {
		_Destory(_root);
	}
};

