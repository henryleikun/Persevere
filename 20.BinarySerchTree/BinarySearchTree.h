#pragma once
#include <iostream>
using namespace std;

//������������ʵ�� �������ռ�����Ʋ���ͻ(֮ǰ�Ǹ�STL��һ��) �����Ͳ�����namespace��
//������ʵ��������������������ģ�ͣ�keyģ�ͺ�key-valueģ�� �������������ռ������� ��ʵ��Ӧʵ�ֲ��

namespace Key {
	//������������
	template<class K>
	struct BSTreeNode {
		BSTreeNode<K>* _left;
		BSTreeNode<K>* _right;
		K _key;

		BSTreeNode(const K& key = K()) : _key(key),_left(nullptr), _right(nullptr) {

		}
	};

	template<class K>
	class BStree {
		typedef BSTreeNode<K> BSnode;
	private:
		BSnode* _root = nullptr;
	public:
		BStree() = default;
	///��c++11��׼�У����������ҪĬ�ϵ���Ϊ�����ǿ���ͨ�������б����д�� = default
	//��Ҫ����������ɺϳ�Ĭ�Ϲ��캯����
	//���� = default�ȿ��Ժ�����һ�����������ڲ���Ҳ������Ϊ�������������ⲿ��
	// ��� = default������ڲ�����Ĭ�Ϲ��캯���������ģ������������ⲿ����ó�ԱĬ������²��������ġ�
	// ����:���������Լ��ô���ȥд���캯��

		BStree(const BStree<K>& rhs) {//��� �ݹ�
			//_root = nullptr;
			copy(_root,rhs._root);
		}
        
		//�ִ�д��
		BStree<K>& operator=(const BStree<K>& rhs) {
			BStree<K> temp(rhs);
			swap(_root, rhs._root);

			return *this;
		}

		~BStree() {
			Destroy(_root);
		}

		//�������ɾ�鶼���ǵݹ�ʵ�֣����Ǹ��ݶ�����������������ʵ��
		//��ɾ�����Ȳ��Ҷ�Ӧ��λ��
		bool Insert(const K& key) {
			if (_root == nullptr) {//����ֱ�ӽ�
				_root = new BSnode(key);
				return true;
			}

			BSnode* cur = _root;
			BSnode* prev = nullptr;//������¼���ĸ����Ҫ���µĺ���

			while (cur) {
				if (key < cur->_key) {//�ȵ�ǰ���С��������
					prev = cur;
					cur = cur->_left;
				}
				else if (key > cur->_key) {//�ȵ�ǰ����������
					prev = cur;
					cur = cur->_right;
				}
				else {
					return false;//���ֵ���� ���ò���
				}
			}

			//��ѭ�� �ҵ���Ӧ����λ�� �丸�ڵ���prev ����֪�������ӻ����Һ���
			//��Ҫ���ж�����ΪС��_key������Ϊ�ճ�ѭ���ģ����Ǵ���_key������Ϊ�ճ�ѭ����
			cur = new BSnode(key);

			if (key < prev->_key) {
				prev->_left = cur;
			}
			else {
				prev->_right = cur;
			}

			return true;
		}

		bool Find(const K& key) {//�Ϳ�һ�� �ҵ�û(Keyģ������û�е�����)
			BSnode* cur = _root;

			while (cur) {
				if (key < cur->_key) {//С���ұ���
					cur = cur->_left;
				}
				else if (key > cur->_key) {//�������
					cur = cur->_right;
				}
				else//�ҵ�
					return true;
			}

			return false;
		}
 
		//erase�Ƚ��鷳
		//�ڶ��� ����popһ��ֵ ���ƻ��ѵĽṹ������������������βԪ���滻 Ȼ�����µ����㶨
		//���ﲻ�������滻 ����Ҫ��������� ���������
		//ɾ���ڵ�����Ϊ�գ�ɾ���ý����ʹ��ɾ���ڵ��˫�׽��ָ��ɾ���ڵ���Һ��ӽ��--ֱ��ɾ��
	    //ɾ���������Ϊ�գ�ɾ���ý����ʹ��ɾ���ڵ��˫�׽��ָ��ɾ���������ӽ��--ֱ��ɾ��
		//ɾ���ڵ�����������Ϊ�գ���������������Ѱ�������µĵ�һ�����(key��С)��������ֵ�����ɾ���ڵ�
		//�У���������ý���ɾ������--�滻��ɾ��
		bool Erase(const K& key) {
			BSnode* cur = _root;
			BSnode* prev = nullptr;//��¼Ҫɾ�����ĸ��ڵ�
			
			while (cur) {
				if (key < cur->_key) {
					prev = cur;
					cur = cur->_left;
				}
				else if (key > cur->_key) {
					prev = cur;
					cur = cur->_right;
				}
				else {
					//�ҵ� ��ʼɾ��
					if (cur->_left == nullptr) {//��Ϊ�� Ҫָ��cur����
						if (cur == _root)//ɾ�����ڵ� ����ɾ��ԭ����_root�����Ѿ���_rootָ���䲻Ϊ�յ��Ƕ���
							_root = _root->_right;
						else {
							//��֪��Ҫɾ���Ľ���Ǹ��ڵ�������������� ���ﻹҪ���ж�
							if (prev->_left == cur) //������
								prev->_left = cur->_right;
							else 
								prev->_right = cur->_right;
						}

						delete cur;
					}
					else if (cur->_right == nullptr) {//��Ϊ�� ͬ��
						if (cur == _root)
							_root = _root->_left;
						else {
							if (prev->_left == cur) 
								prev->_left = cur->_left;
							else
								prev->_right = cur->_left;
						}

						delete cur;
					}
					else {//����Ϊ��
						//�滻 ������������������(����key)��Ҳ����ȥ������������(��С��key)
						//��Ϊ�ҵ��������� ���������ֵ�����һ�� �������϶�û���Һ���
						//�������϶�û������ ������֮�� �ٰ�������ķ���ɾ��
						//�������������������
						BSnode* sleft = cur->_right;
						prev = cur;

						while (sleft->_left) {
							prev = sleft;//������prev�ͳ䵱������Ҫɾ�����ĸ��ڵ�
                            //��Ҫɾ�����Ǹ��ڵ㣬prev = curҲ���˶�Ӧ������
							sleft = sleft->_left;
						}

						swap(cur->_key, sleft->_key);
						//�ҵ�������ڵ� ���������������Ϊ��
						if (prev->_left == sleft)
							prev->_left = sleft->_right;
						else
							prev->_right = sleft->_right;

						delete sleft;
					}

					return true;
				}
			}
			return false;
		}

		//����ݹ�ʵ��������� ����Ҫ���ڵ���β� ������Ϊ�ӿ� _root���ⲻ�ɼ�
		//����͸���ӵݹ�(���ⲻ�ɼ�)
		void Inorder() {
			InorderR(_root);
			cout << endl;
		}

		//����ʵ�����µݹ��Ľӿ� ��Inorderһ����Ҫ�ӵݹ麯��
		bool InsertR(const K& key) {
			return _InsertR(_root, key);
		}

		bool FindR(const K& key) {
			return _FindR(_root, key);
		}

		bool EraseR(const K& key) {
			return _EraseR(_root, key);
		}


	protected:
		void InorderR(BSnode* root) {
			if (root == nullptr)
				return;

			InorderR(root->_left);
			cout << root->_key << " ";
			InorderR(root->_right);
		}

		bool _InsertR(BSnode*& root,const K& key) {
			//������������ ���ҵ�Ҫ����ĵط���ʱ����ʹ��prev��
			//ֱ�ӾͿ��Բ�
			if (root == nullptr) {
				root = new BSnode(key);
				return true;
			}

			if (key < root->_key)
				_InsertR(root->_left, key);
			else if (key > root->_key)
				_InsertR(root->_right, key);
			else
				return false;
		}

		bool _FindR(BSnode* root, const K& key) {
			if (root == nullptr)
				return false;

			if (key < root->_key)
				return _FindR(root->_left, key);
			else if (key > root->_key)
				return _FindR(root->_right, key);
			else
				return true;

		}

		bool _EraseR(BSnode*& root, const K& key) {
			if (root == nullptr)
				return false;


			if (key < root->_key)
				return _EraseR(root->_left, key);
			else if (key > root->_key)
				return _EraseR(root->_right, key);
			else {//��ɾ
				if (root->_left == nullptr) {//����Ϊ�� ָ������
					BSnode* del = root;
					root = root->_right;//���õĺô����ֵ����쾡�� �������ùܸ��ڵ�
					delete del;
					return true;
				}
				else if (root->_right == nullptr) {
					BSnode* del = root;
					root = root->_left;
					delete del;
					return true;
				}
				else {//����Ϊ�� �滻�� ���ﻹ��ȥ��������������
					BSnode* cur = root->_right;

					while (cur->_left) {
						cur = cur->_left;
					}

					swap(root->_key, cur->_key);
					
					//return _EraseR(cur, key);���ﴫ����cur �Ƕ�Ӧ_root��ڵ�Ŀ���
					//���Ǵ������õ� �ݹ�ı�ľ���cur��ԭ����_root��ָ��û��Ӱ��

					return _EraseR(root->_right, key);//rootҲ��_root��������Ƕ�ԭ���Ĳ���
				}
			}
		}

		void Destroy(BSnode*& root) {//����ɾ��
			if (root == nullptr)
				return;

			Destroy(root->_left);
			Destroy(root->_right);
			delete root;

			root = nullptr;
		}

		void copy(BSnode*& root,BSnode* rhs_root) {
			if (rhs_root == nullptr)
				return;

			root = new BSnode(rhs_root->_key);
			copy(root->_left, rhs_root->_left);
			copy(root->_right, rhs_root->_right);
		}
	};
}

//key-valueģ�� �����ֵ�ÿ��keyֵ��Ӧһ��valueֵ
namespace kv {
	//������������
	template<class K,class V>
	struct BSTreeNode {
		BSTreeNode<K,V>* _left;
		BSTreeNode<K,V>* _right;
		K _key;
		V _value;

		BSTreeNode(const K& key = K(),const V& value = V()) 
			: _key(key),_value(value),_left(nullptr), _right(nullptr) {

		}
	};

	template<class K,class V>
	class BStree {
		typedef BSTreeNode<K,V> BSnode;
	private:
		BSnode* _root = nullptr;
	public:
		BStree() = default;

		BStree(const BStree<K,V>& rhs) {//��� �ݹ�
			//_root = nullptr;
			copy(_root, rhs._root);
		}

		//�ִ�д��
		BStree<K,V>& operator=(const BStree<K,V>& rhs) {
			BStree<K,V> temp(rhs);
			swap(_root, rhs._root);

			return *this;
		}

		~BStree() {
			Destroy(_root);
		}

		//�������ɾ�鶼���ǵݹ�ʵ�֣����Ǹ��ݶ�����������������ʵ��
		//��ɾ�����Ȳ��Ҷ�Ӧ��λ��
		bool Insert(const K& key,const V& value) {
			if (_root == nullptr) {//����ֱ�ӽ�
				_root = new BSnode(key,value);
				return true;
			}

			BSnode* cur = _root;
			BSnode* prev = nullptr;//������¼���ĸ����Ҫ���µĺ���

			while (cur) {
				if (key < cur->_key) {//�ȵ�ǰ���С��������
					prev = cur;
					cur = cur->_left;
				}
				else if (key > cur->_key) {//�ȵ�ǰ����������
					prev = cur;
					cur = cur->_right;
				}
				else {
					return false;//���ֵ���� ���ò���
				}
			}

			//��ѭ�� �ҵ���Ӧ����λ�� �丸�ڵ���prev ����֪�������ӻ����Һ���
			//��Ҫ���ж�����ΪС��_key������Ϊ�ճ�ѭ���ģ����Ǵ���_key������Ϊ�ճ�ѭ����
			cur = new BSnode(key,value);

			if (key < prev->_key) {
				prev->_left = cur;
			}
			else {
				prev->_right = cur;
			}

			return true;
		}

		BSnode* Find(const K& key) {//key-valueͨ��key��value ���ԾͲ����ж��ڲ��ڵ������� 
			BSnode* cur = _root;    //������bool������ֵ

			while (cur) {
				if (key < cur->_key) {//С���ұ���
					cur = cur->_left;
				}
				else if (key > cur->_key) {//�������
					cur = cur->_right;
				}
				else//�ҵ�
					return cur;
			}

			return nullptr;
		}

		bool Erase(const K& key) {
			BSnode* cur = _root;
			BSnode* prev = nullptr;//��¼Ҫɾ�����ĸ��ڵ�

			while (cur) {
				if (key < cur->_key) {
					prev = cur;
					cur = cur->_left;
				}
				else if (key > cur->_key) {
					prev = cur;
					cur = cur->_right;
				}
				else {
					//�ҵ� ��ʼɾ��
					if (cur->_left == nullptr) {//��Ϊ�� Ҫָ��cur����
						if (cur == _root)//ɾ�����ڵ� ����ɾ��ԭ����_root�����Ѿ���_rootָ���䲻Ϊ�յ��Ƕ���
							_root = _root->_right;
						else {
							//��֪��Ҫɾ���Ľ���Ǹ��ڵ�������������� ���ﻹҪ���ж�
							if (prev->_left == cur) //������
								prev->_left = cur->_right;
							else
								prev->_right = cur->_right;
						}

						delete cur;
					}
					else if (cur->_right == nullptr) {//��Ϊ�� ͬ��
						if (cur == _root)
							_root = _root->_left;
						else {
							if (prev->_left == cur)
								prev->_left = cur->_left;
							else
								prev->_right = cur->_left;
						}

						delete cur;
					}
					else {//����Ϊ��
						BSnode* sleft = cur->_right;
						prev = cur;

						while (sleft->_left) {
							prev = sleft;//������prev�ͳ䵱������Ҫɾ�����ĸ��ڵ�
							//��Ҫɾ�����Ǹ��ڵ㣬prev = curҲ���˶�Ӧ������
							sleft = sleft->_left;
						}

						swap(cur->_key, sleft->_key);
						//�ҵ�������ڵ� ���������������Ϊ��
						if (prev->_left == sleft)
							prev->_left = sleft->_right;
						else
							prev->_right = sleft->_right;

						delete sleft;
					}

					return true;
				}
			}
			return false;
		}

		//����ݹ�ʵ��������� ����Ҫ���ڵ���β� ������Ϊ�ӿ� _root���ⲻ�ɼ�
		//����͸���ӵݹ�(���ⲻ�ɼ�)
		void Inorder() {
			InorderR(_root);
			cout << endl;
		}

		//����Ͳ�д��Ӧ�ĵݹ���

	protected:
		void InorderR(BSnode* root) {
			if (root == nullptr)
				return;

			InorderR(root->_left);
			cout << root->_key << ": " << root->_value << endl;
			InorderR(root->_right);
		}

		void Destroy(BSnode*& root) {//����ɾ��
			if (root == nullptr)
				return;

			Destroy(root->_left);
			Destroy(root->_right);
			delete root;

			root = nullptr;
		}

		void copy(BSnode*& root, BSnode* rhs_root) {
			if (rhs_root == nullptr)
				return;

			root = new BSnode(rhs_root->_key,rhs_root->_value);
			copy(root->_left, rhs_root->_left);
			copy(root->_right, rhs_root->_right);
		}
	};
}
