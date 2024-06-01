#pragma once
#include <iostream>
#include <cassert>
#include <string>
using namespace std;
//AVL�� �ڶ����������Ļ����� ����ƽ��Ĳ���
//�����ɾ�����漰��ʧ��ĵ��� ��ƽ�����ӵĸ��� ����ҲҪʵ�ִ���ʧ����㷨����ת���㷨
//�����ʵ��һ��key-valueģ�͵�AVL�� ��Ҫ������Ҳ�˽�һ��pair(map�������value_type)

// ����Ҫ˵�� AVL���ͺ���������˽��Ե�ѧϰ ��Ҫѧϰ���ڲ�ʵ��ԭ�� �Ƿ�����˺ �ŵ����
// �����о��������� ��Ҫ��Ϊ�˰Ѷ�Ӧ�������� ԭ������������� AVL���ͺ����������ɾ����ʵ
// ���˽��˲���� ���˽��������������ʰ����Ͳ�����ô���� ��ʵ���� ������Ѿ����д������� ����ɾ��ҲҪ�˽�
// ����ῴ��� ������˺ ɾ�� �޷Ǿ������ ������ ��ʵ������

template<class K,class V>
struct AVLtreeNode {
	AVLtreeNode<K, V>* _left;
	AVLtreeNode<K, V>* _right;
	AVLtreeNode<K, V>* _parent;
	//AVL�������һ�������� _parentָ���Լ��ĸ����������Լ�ƽ�����ӱ仯��ʱ��
	//����Ѹ��ȥ���¸��ڵ��ƽ������
	pair<K, V> _val;
	
	int _bf;//ƽ������

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
	//����ת �ٵ���ƽ������
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

		//��ƽ������
		subL->_bf = 0;
		parent->_bf = 0;
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

		parent->_bf = subR->_bf = 0;

	}

	//�����������Ը��������������� ƽ��������Ҫ�ٴ���һ��
	void RotateLR(Node* parent) {//�������ҵ���
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(parent->_left);
		RotateR(parent);

		//����bf
		if (bf == 0) {//subLR�Լ������������ ����ӦhΪ��
			subL->_bf = subLR->_bf = parent->_bf = 0;//��ʵ��Rotate����Ѿ����0��
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

	void RotateRL(Node* parent) {//�ҵ���������
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		RotateL(parent->_right);
		RotateR(parent);

		//����bf
		if (bf == 0) {//subRL�Լ������������ ����ӦhΪ��
			subRL->_bf = subR->_bf = parent->_bf = 0;//��ʵ��Rotate����Ѿ����0��
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

		if (right - left != root->_bf)//��������
		{
			cout << root->_val.first << "ƽ�������쳣" << endl;
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

		cur = new Node(val);//cur��prev->_left or _right��copy ���ָ�򲻻�ı�ԭ�� Ҫ��������prev��ָ��

		if (val.first < prev->_val.first) {
			prev->_left = cur;
			cur->_parent = prev;
		}
		else {
			prev->_right = cur;
			cur->_parent = prev;
		}
		//���ϱ��� ����BStree�Ĳ������ �������һ��_parent
		//������Ƕ�ƽ�����Ӻ�ʧ��Ĵ��� 

		//cur����ָ���²���Ľ�� ��prevָ���Ӧ���ڵ� �²���Ľ���bf��0
		//��ס ����Ķ���Ҳ��AVL�������Բ���֮ǰ���������нڵ��ƽ�����Ӿ���ֵ��С��2
		//ѭ����Ϊ�����ϸ���ƽ�����ӻ����ҵ���һ��ʧ��Ľ�� �����ǲ���ɹ�
		while (prev) {//���ڵ�ͷ ��prev==_root->_parent
			if (prev->_left == cur) {
				prev->_bf--;//�嵽��� ƽ������-1
			}
			else {
				prev->_bf++;//�嵽�ұ� bf(balance factor)+1
			}


			if (prev->_bf == 0) {//����֮ǰһ����+-1 ������ƽ������Ϊ0 һ��ƽ��
				return true;
			}
			else if (prev->_bf == 1 || prev->_bf == -1) {//�ڱ��+-1֮ǰ �Լ�һ����0
				                                        //��ʱ�ǻ�Ӱ�������ƽ�����ӵģ���Ҫ���ϸ���ƽ������
				cur = prev;
				prev = prev->_parent;
			}
			else if (prev->_bf == -2 || prev->_bf == 2) {//����ʧ������� ���д���
				//ʧ���������������� �ֱ�Ҳ�Ҳ�ͬ����ת������
				if (prev->_bf == -2 && cur->_bf == -1) {//LL �ҵ���
					RotateR(prev);
				}
				else if (prev->_bf == 2 && cur->_bf == 1) {//RR ����
					RotateL(prev);
				}
				else if (prev->_bf == -2 && cur->_bf == 1) {//LR ���������ҵ���
					RotateLR(prev);
				}
				else if (prev->_bf == 2 && cur->_bf == -1) {//RL ���ҵ���������
					RotateRL(prev);
				}
				else {
					assert(false);
				}

				//��ת�� �������ԭ���Ļ�����һ��ƽ���� 
				//��ת��������������ĸ߶ȣ��ָ���������ǰһ���ĸ߶ȣ����Զ���һ��û��Ӱ�죬���ü�������
				//������ת��֮�� ������˲��붯��
				return true;
			}
			else {//����ֵ����2 ˵�� ���Ѿ�����AVL���� ����Ļ��ᶼû����
				assert(false);
			}
		}
		
		return true;
	}

	bool Erase(const pair<K,V>& val) {

	}//ɾ�� ���˽� ��Ҫ�������˺ ��Ҫ֪������ ����ȷ����� 
	//Ŀǰ�Ĵ�˼·���� ���� ɾ�� ����
	//�Ȱ������������ĵĲ��ҷ�ʽ����val.first Ȼ��ͬ����������һ��
	//ɾ���Ľ����������� ������(ɾ���ýڵ� ���ڵ�ָ����������) ������(ɾ���ýڵ� ���ڵ�ָ����������) 
	//������Ϊ��(�滻 ȥ������������ �滻�����������)
	//���ڵ��� �����ɾ������ ���ڵ�bf++ ɾ������bf-- �ٿ��Ƿ���Ҫ����ƽ������
	//���bf��Ϊ1 or -1����Ҫ�ı� ɾ���ɹ�ԭ����0(���߿϶�����) ɾ�������߶Ȳ���
	//bfΪ0 ���ϸ���ƽ������(ԭ��һ����һ�߸�) bfΪ-2 or 2��ת
	//����ʵ�ֵ�Դ�� ������ʱ��һ�� ֮�����㷨���ۺ����ݽṹ������ѧϰ 

	bool Is_balance() {//�ж��Ƿ�ƽ�� �޷Ǿ��ǿ��������ĸ߶��Ƿ����С��2
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
