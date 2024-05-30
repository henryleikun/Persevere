#pragma once
#include <iostream>
#include <string>
#include <utility>
using namespace std;
//����һ��k,v�͵ĺ���� Ȼ�������������ȥ��װmap��set(���߶��ǵײ�Ϊ������Ĺ���ʽ����)
//set-->key��  map--->key value��
//��AVL��һ�� ��ʵ�� �����������ǲ����޸ĵ�

//enum Color {
//	RED,BLACK
//};//ö�� RED 0 BLACK 1
//
//template<class K,class V>
//struct RBtreeNode {
//	RBtreeNode<K, V>* _left;
//	RBtreeNode<K, V>* _right;
//	RBtreeNode<K, V>* _parent;//��AVL��һ������������
//
//	pair<K, V> _kv;
//
//	Color _col;//���������ɫ
//
//	RBtreeNode(const pair<K,V>& kv = pair<K,V>())
//	:_left(nullptr),_right(nullptr),_parent(nullptr),_kv(kv),_col(RED){
//		//�½ڵ�Ĭ���Ǻ�ɫ ���ܳ����� ����� Ĭ���Ǻ�ɫ�Ǿ�ÿ��·���������� ����֮ǰ���Ǻ���� 
//		//ÿ��·����ɫ�ڵ�������ͬ ������һ����������֪
//    
//	}
//};
//
//template<class K,class V>
//class RBtree {
//	typedef RBtreeNode<K, V> Node;
//private:
//	Node* _root = nullptr;//�൱��Ĭ�Ϲ���
//protected:
//	void RotateR(Node* parent) {//�ҵ���
//		Node* subL = parent->_left;
//		Node* subLR = subL->_right;
//		Node* parentparent = parent->_parent;
//
//		//�ȵ���ָ��
//		parent->_left = subLR;
//		subL->_right = parent;
//		//��ָ��ĸ��ڵ�
//		parent->_parent = subL;
//		if (parent == _root) {//ʧ���Ϊ���ڵ� Ҫ����_root��ָ�� parentparent == nullptr
//			_root = subL;
//		}
//		else {//���Ǹ��ڵ� Ҳ���������һ�þֲ����� Ҫ����parent��parent��ָ��
//			if (parentparent->_left == parent) {
//				parentparent->_left = subL;
//			}
//			else {
//				parentparent->_right = subL;
//			}
//		}
//		subL->_parent = parentparent;
//
//		if (subLR) {//subLR����Ϊ�� 
//			subLR->_parent = parent;
//		}
//	}
//
//	void RotateL(Node* parent) {//���� ���ҵ�������
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
//    //��Ҫ������ ��� �Ƿ��������ĺ��� ���ÿ��·���Ƿ��ɫ��㶼��ͬ
//    //��μ���ɫ������� ���ǿ�������һ��·��ȥ��¼����·���µĺ�ɫ������Ϊ�ο�ֵ 
//    //Ȼ��ȥ����ÿ��·�� ����������ʱ�� ���Ƿ���ref��� �����ֱ��false
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
//		else {//Ϊ�� һ������_root���ڵ� ��һ����parent
//			if (root->_parent->_col == RED)
//				return false;//�������ĸ���Ҳ�Ǻ��� �������
//		}
//
//		return Check(root->_right,ref,numBlack) && Check(root->_left,ref,numBlack);
//	}
//
//public:	//���� �������� ��ֵ�������ЩҲûʲôʵ������ �����õ� �Ͳ�ʵ����
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
//		cur = new Node(kv);//Ĭ��_col�Ѿ��Ǻ�ɫ��
//		if (kv.first < parent->_kv.first) {
//			parent->_left = cur;
//			cur->_parent = parent;
//		}
//		else {
//			parent->_right = cur;
//			cur->_parent = parent;
//		}
//
//		//��������˲��� �������Ҫ��� �Ƿ�Υ��������Ĺ��� �����е���
//
//		while (parent && parent->_col == RED) {//parent�������Ǻ�ɫ
//			Node* grandfather = parent->_parent;//parent����Ϊ���һ����_parent
//			
//			if (parent == grandfather->_left) {//p��g�����
//				Node* uncle = grandfather->_right;
//				/*     g
//					p     u
//				 c     c      */
//				if (uncle && uncle->_col == RED) {//uncle������Ϊ�� ����c���ı߶�һ��
//					parent->_col = uncle->_col = BLACK;
//					grandfather->_col = RED;
//
//					cur = grandfather;
//					parent = cur->_parent;
//
//					continue;//���ϵ��� ֱ��ȥ�ж� �±�ĺ��� �Ƿ��ֳ���˫������
//				}
//				else if(parent->_left == cur){//��uncle�����ڻ���uncleΪ��ʱ 
//					//uncle�����ڲ��� uncle��󶼲��ñ�ɫ ����ֻ��Ҫ��cur��parent���߽��з�����������
//					//Ҳ����uncleΪ�� Ҳ��uncle������������
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
//				break; //��Ժ�������� ����Ϳ���break��
//			}
//			else {//������
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
//		//��ѭ�����������ϵ������Ľ��ĸ����Ǻ�ɫ Ҳ�����ǵ�����_root��(���) ������Ҫ�������������
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
//	bool Is_RBtree() {//�ж��Ƿ��Ǻ����
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
//			cur = cur->_left;//��¼����·����numBlack
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


//���������ʵ�ֵĺ����(��ɾ��) ��Ҫ�������ʵ�ֻ����� ����map set���з�װ map��set�ײ㶼�Ǻ����
//�ֱ��Ӧkey-value key�� ���STL����ľ���ʵ�� ��Ҫ�Ժ������һЩ�����������ʺ�ȥ���εײ�Ľ�ɫ
//��Ϊ�ײ���ͬ �Ǻ������ģ�������Ҫ���������� ��Ϊmap������������pair ��set�ͽ����Ǹ�key ���ԶԺ����
//������� ����������Ӧ���Ǹ����� ������ȷ����pair

enum Color {
	RED, BLACK
};//ö�� RED 0 BLACK 1

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
//};����ô����ʵ���� ����ģ���ע��TҪôkey Ҫôpair ����ķ���ֵ������key��������δ�T�����ֳ�key��
//Ҳ��������RBtree<, , KeyofValue<key>/KeyofValue<pair<>>>������ �����ʵ�־ͻ������ ��ȷӦ����
//����rbtree�ĵط�ֱ�Ӷ�����Ե�KeyofValue


//���������������ʵ�� ���ֿɲο�list�ĵ����� 
//��list�Ĵ������� ����ͨ��һ��ģ��ȥ�㶨��ͨ�������ͳ������� ֻ��һ��ģ����� Ҫд���ģ�����ʵ������
//����ģ����� �Ϳ��Խ�������ظ�������
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

	self& operator++() {//ǰ�� 
		//�������� ���� �� ����
		if (_pnode->_right == nullptr) {//����
			Node* parent = _pnode->_parent;
			while (parent && parent->_right == _pnode) {
				_pnode = _pnode->_parent;
				parent = _pnode->_parent;
			}

			//if (parent == nullptr)//�ߵ�ͷ�� Ҳ����˵ԭ��pnode��ָ�������һ��Ԫ��
			//	_pnode = nullptr;
			//else //��Ϊ�� ��Ϊ�ҵ����ڵ�����ӵĶ�Ӧ���
			//	_pnode = parent;

			_pnode = parent;//����һ�仰�ͽ��
		}
		else {//������Ϊ�� ������������
			Node* cur = _pnode->_right;

			while (cur->_left) {
				cur = cur->_left;
			}

			_pnode = cur;
		}

		return *this;
	}

	//��ʵ����ûɶʵ������ ����������
	self& operator++(int) {//���� 
		self ret = *this;//Ĭ�ϵĿ���������� ָ��ָ�򴫹�ȥ��

		if (_pnode->_right == nullptr) {//����
			Node* parent = _pnode->_parent;
			while (parent && parent->_right == _pnode) {
				_pnode = _pnode->_parent;
				parent = _pnode->_parent;
			}

			_pnode = parent;
		}
		else {//������Ϊ�� ������������
			Node* cur = _pnode->_right;

			while (cur->_left) {
				cur = cur->_left;
			}

			_pnode = cur;
		}

		return ret;
	}

	self& operator--() {//--��++�����߾��� 
		//�������� ���� �� ����
		if (_pnode->_left == nullptr) {//����
			Node* parent = _pnode->_parent;
			while (parent && parent->_left == _pnode) {
				_pnode = _pnode->_parent;	
				parent = _pnode->_parent;
			}

			_pnode = parent;
		}
		else {//������Ϊ�� ������������
			Node* cur = _pnode->_left;

			while (cur->_right) {
				cur = cur->_right;
			}

			_pnode = cur;
		}

		return *this;
	}

	self& operator--(int) {//����
		self ret = *this;

		if (_pnode->_left == nullptr) {//����
			Node* parent = _pnode->_parent;
			while (parent && parent->_left == _pnode) {
				_pnode = _pnode->_parent;
				parent = _pnode->_parent;
			}

			_pnode = parent;
		}
		else {//������Ϊ�� ������������
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

//KeyofValue��������ȡ��T��key �ٲ����ʱ�� �������ʵ�ֱȽϴ�С�Ǳȵ�first����set(����pairʱ)
//first�Ͳ����� ������﷨���� ��Ҫ��һ�������͵ıȽ� ��ʵ����һ���º���
//��������Ĵ��� ��T���ģ�����ȥ������key ����key-value
//���ܻ���� ����TΪʲô��ҪK(K K��ʾset K pairȥ��ʾmap) K���������ṩT�Ĺؼ�������
//����Find��ʱ��Ҫ��key�Ĳ��� ����KeyofValue���ص���Keyֵ �����ṩ���� �� ���K�����б�Ҫ�� 
template<class K, class T,class KeyofValue>
class RBtree {
	typedef RBtreeNode<T> Node;
private:
	Node* _root = nullptr;
protected:
	void RotateR(Node* parent) {//�ҵ���
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* parentparent = parent->_parent;

		//�ȵ���ָ��
		parent->_left = subLR;
		subL->_right = parent;
		//��ָ��ĸ��ڵ�
		parent->_parent = subL;
		if (parent == _root) {//ʧ���Ϊ���ڵ� Ҫ����_root��ָ�� parentparent == nullptr
			_root = subL;
		}
		else {//���Ǹ��ڵ� Ҳ���������һ�þֲ����� Ҫ����parent��parent��ָ��
			if (parentparent->_left == parent) {
				parentparent->_left = subL;
			}
			else {
				parentparent->_right = subL;
			}
		}
		subL->_parent = parentparent;

		if (subLR) {//subLR����Ϊ�� 
			subLR->_parent = parent;
		}
	}

	void RotateL(Node* parent) {//���� ���ҵ�������
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
		//��Ҫ������ ��� �Ƿ��������ĺ��� ���ÿ��·���Ƿ��ɫ��㶼��ͬ
		//��μ���ɫ������� ���ǿ�������һ��·��ȥ��¼����·���µĺ�ɫ������Ϊ�ο�ֵ 
		//Ȼ��ȥ����ÿ��·�� ����������ʱ�� ���Ƿ���ref��� �����ֱ��false
		if (root == nullptr) {
			if (numBlack == ref)
				return true;
			else
				return false;
		}


		if (root->_col == BLACK)
			numBlack++;
		else {//Ϊ�� һ������_root���ڵ� ��һ����parent
			if (root->_parent->_col == RED)
				return false;//�������ĸ���Ҳ�Ǻ��� �������
		}

		return Check(root->_right, ref, numBlack) && Check(root->_left, ref, numBlack);
	}

public:	//���� �������� ��ֵ�������ЩҲûʲôʵ������ �����õ� �Ͳ�ʵ����
	//�ŵ�public����
	typedef _RBtree_iterator<T, T&, T*> iterator;
	typedef _RBtree_iterator<T, const T&, const T*> const_iterator;

	iterator begin() {//����������ָ��
	    Node* cur = _root;
		if (cur == nullptr)
			return iterator(cur);

		while (cur->_left)
			cur = cur->_left;

		return iterator(cur);
	}

	iterator end() {//end���ǿ�
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

	//bool ��ı�׼
	//pair<iterator,bool>���ʵ��
	//pair<Node*,bool>��һ�� ��Ҫ����pair<iterator,bool>��pair<const_iterator,bool>ת��
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

		cur = new Node(data);//Ĭ��_col�Ѿ��Ǻ�ɫ��
		if (Key(data) < Key(parent->_data)) {
			parent->_left = cur;
			cur->_parent = parent;
		}
		else {
			parent->_right = cur;
			cur->_parent = parent;
		}

		//��������˲��� �������Ҫ��� �Ƿ�Υ��������Ĺ��� �����е���

		while (parent && parent->_col == RED) {//parent�������Ǻ�ɫ
			Node* grandfather = parent->_parent;//parent����Ϊ���һ����_parent

			if (parent == grandfather->_left) {//p��g�����
				Node* uncle = grandfather->_right;
				/*     g
					p     u
				 c     c      */
				if (uncle && uncle->_col == RED) {//uncle������Ϊ�� ����c���ı߶�һ��
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;

					continue;//���ϵ��� ֱ��ȥ�ж� �±�ĺ��� �Ƿ��ֳ���˫������
				}
				else if (parent->_left == cur) {//��uncle�����ڻ���uncleΪ��ʱ 
					//uncle�����ڲ��� uncle��󶼲��ñ�ɫ ����ֻ��Ҫ��cur��parent���߽��з�����������
					//Ҳ����uncleΪ�� Ҳ��uncle������������
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

				break; //��Ժ�������� ����Ϳ���break��
			}
			else {//������
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
		//��ѭ�����������ϵ������Ľ��ĸ����Ǻ�ɫ Ҳ�����ǵ�����_root��(���) ������Ҫ�������������
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

	bool Is_RBtree() {//�ж��Ƿ��Ǻ����
		if (_root == nullptr)
			return true;

		Node* cur = _root;
		int ref = 0;

		while (cur) {
			if (cur->_col == BLACK)
				++ref;

			cur = cur->_left;//��¼����·����numBlack
		}

		return Check(_root, ref, 0);
	}

	~RBtree() {
		_Destory(_root);
	}
};

