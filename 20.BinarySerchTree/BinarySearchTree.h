#pragma once
#include <iostream>
using namespace std;

//二叉搜索树的实现 跟命名空间的名称不冲突(之前是跟STL里一致) 本来就不用用namespace了
//但这里实现了搜索二叉树的两种模型，key模型和key-value模型 搞了两个命名空间来区分 其实对应实现差不多

namespace Key {
	//定义二叉树结点
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
	///在c++11标准中，如果我们需要默认的行为，我们可以通过参数列表后面写上 = default
	//来要求编译器生成合成默认构造函数。
	//其中 = default既可以和声明一起出现在类的内部，也可以作为定义出现在类的外部。
	// 如果 = default在类的内部，则默认构造函数是内联的，如果他在类的外部，则该成员默认情况下不是内联的。
	// 作用:不用我们自己敲代码去写构造函数

		BStree(const BStree<K>& rhs) {//深拷贝 递归
			//_root = nullptr;
			copy(_root,rhs._root);
		}
        
		//现代写法
		BStree<K>& operator=(const BStree<K>& rhs) {
			BStree<K> temp(rhs);
			swap(_root, rhs._root);

			return *this;
		}

		~BStree() {
			Destroy(_root);
		}

		//下面的增删查都不是递归实现，都是根据二叉搜索树的性质来实现
		//增删都是先查找对应的位置
		bool Insert(const K& key) {
			if (_root == nullptr) {//空树直接建
				_root = new BSnode(key);
				return true;
			}

			BSnode* cur = _root;
			BSnode* prev = nullptr;//用来记录是哪个结点要有新的孩子

			while (cur) {
				if (key < cur->_key) {//比当前结点小到左树插
					prev = cur;
					cur = cur->_left;
				}
				else if (key > cur->_key) {//比当前结点大到右树插
					prev = cur;
					cur = cur->_right;
				}
				else {
					return false;//这个值存在 不用插入
				}
			}

			//出循环 找到对应插入位置 其父节点是prev 但不知道是左孩子还是右孩子
			//需要再判断是因为小于_key右子树为空出循环的，还是大于_key左子树为空出循环的
			cur = new BSnode(key);

			if (key < prev->_key) {
				prev->_left = cur;
			}
			else {
				prev->_right = cur;
			}

			return true;
		}

		bool Find(const K& key) {//就看一下 找到没(Key模型是有没有的问题)
			BSnode* cur = _root;

			while (cur) {
				if (key < cur->_key) {//小到右边找
					cur = cur->_left;
				}
				else if (key > cur->_key) {//大到左边找
					cur = cur->_right;
				}
				else//找到
					return true;
			}

			return false;
		}
 
		//erase比较麻烦
		//在堆中 我们pop一个值 会破坏堆的结构，解决方法是让他与堆尾元素替换 然后向下调整搞定
		//这里不能这样替换 我们要分情况来搞 有四种情况
		//删除节点左树为空：删除该结点且使被删除节点的双亲结点指向被删除节点的右孩子结点--直接删除
	    //删除结点右树为空：删除该结点且使被删除节点的双亲结点指向被删除结点的左孩子结点--直接删除
		//删除节点左右树都不为空：在它的右子树中寻找中序下的第一个结点(key最小)，用它的值填补到被删除节点
		//中，再来处理该结点的删除问题--替换法删除
		bool Erase(const K& key) {
			BSnode* cur = _root;
			BSnode* prev = nullptr;//记录要删除结点的父节点
			
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
					//找到 开始删除
					if (cur->_left == nullptr) {//左为空 要指向cur的右
						if (cur == _root)//删除根节点 后面删掉原本的_root这里已经将_root指向其不为空的那端了
							_root = _root->_right;
						else {
							//不知道要删除的结点是父节点的左树还是右树 这里还要再判断
							if (prev->_left == cur) //是左孩子
								prev->_left = cur->_right;
							else 
								prev->_right = cur->_right;
						}

						delete cur;
					}
					else if (cur->_right == nullptr) {//右为空 同上
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
					else {//都不为空
						//替换 可以在左树找最右树(最大的key)，也可以去右树找最左树(最小的key)
						//因为找到的这个结点 必是上两种的其中一种 最右树肯定没有右孩子
						//最左树肯定没有左孩子 交换完之后 再按照上面的方法删除
						//这里就找右树的最左结点
						BSnode* sleft = cur->_right;
						prev = cur;

						while (sleft->_left) {
							prev = sleft;//在这里prev就充当交换后要删除结点的父节点
                            //当要删除的是根节点，prev = cur也起到了对应的作用
							sleft = sleft->_left;
						}

						swap(cur->_key, sleft->_key);
						//找的是最左节点 是上面情况的左树为空
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

		//这里递归实现中序遍历 但需要根节点的形参 但是作为接口 _root对外不可见
		//这里就搞个子递归(对外不可见)
		void Inorder() {
			InorderR(_root);
			cout << endl;
		}

		//下面实现以下递归版的接口 和Inorder一样需要子递归函数
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
			//这里用了引用 在找到要插入的地方的时候不用使用prev了
			//直接就可以插
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
			else {//开删
				if (root->_left == nullptr) {//左树为空 指向右树
					BSnode* del = root;
					root = root->_right;//引用的好处体现的淋漓尽致 根本不用管父节点
					delete del;
					return true;
				}
				else if (root->_right == nullptr) {
					BSnode* del = root;
					root = root->_left;
					delete del;
					return true;
				}
				else {//都不为空 替换法 这里还是去右子树找最左结点
					BSnode* cur = root->_right;

					while (cur->_left) {
						cur = cur->_left;
					}

					swap(root->_key, cur->_key);
					
					//return _EraseR(cur, key);这里传的是cur 是对应_root里节点的拷贝
					//你是传的引用但 递归改变的就是cur对原本的_root的指向没有影响

					return _EraseR(root->_right, key);//root也是_root里的引用是对原树的查找
				}
			}
		}

		void Destroy(BSnode*& root) {//中序删除
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

//key-value模型 例如字典每个key值对应一个value值
namespace kv {
	//定义二叉树结点
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

		BStree(const BStree<K,V>& rhs) {//深拷贝 递归
			//_root = nullptr;
			copy(_root, rhs._root);
		}

		//现代写法
		BStree<K,V>& operator=(const BStree<K,V>& rhs) {
			BStree<K,V> temp(rhs);
			swap(_root, rhs._root);

			return *this;
		}

		~BStree() {
			Destroy(_root);
		}

		//下面的增删查都不是递归实现，都是根据二叉搜索树的性质来实现
		//增删都是先查找对应的位置
		bool Insert(const K& key,const V& value) {
			if (_root == nullptr) {//空树直接建
				_root = new BSnode(key,value);
				return true;
			}

			BSnode* cur = _root;
			BSnode* prev = nullptr;//用来记录是哪个结点要有新的孩子

			while (cur) {
				if (key < cur->_key) {//比当前结点小到左树插
					prev = cur;
					cur = cur->_left;
				}
				else if (key > cur->_key) {//比当前结点大到右树插
					prev = cur;
					cur = cur->_right;
				}
				else {
					return false;//这个值存在 不用插入
				}
			}

			//出循环 找到对应插入位置 其父节点是prev 但不知道是左孩子还是右孩子
			//需要再判断是因为小于_key右子树为空出循环的，还是大于_key左子树为空出循环的
			cur = new BSnode(key,value);

			if (key < prev->_key) {
				prev->_left = cur;
			}
			else {
				prev->_right = cur;
			}

			return true;
		}

		BSnode* Find(const K& key) {//key-value通过key找value 所以就不是判断在不在的问题了 
			BSnode* cur = _root;    //不能用bool做返回值

			while (cur) {
				if (key < cur->_key) {//小到右边找
					cur = cur->_left;
				}
				else if (key > cur->_key) {//大到左边找
					cur = cur->_right;
				}
				else//找到
					return cur;
			}

			return nullptr;
		}

		bool Erase(const K& key) {
			BSnode* cur = _root;
			BSnode* prev = nullptr;//记录要删除结点的父节点

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
					//找到 开始删除
					if (cur->_left == nullptr) {//左为空 要指向cur的右
						if (cur == _root)//删除根节点 后面删掉原本的_root这里已经将_root指向其不为空的那端了
							_root = _root->_right;
						else {
							//不知道要删除的结点是父节点的左树还是右树 这里还要再判断
							if (prev->_left == cur) //是左孩子
								prev->_left = cur->_right;
							else
								prev->_right = cur->_right;
						}

						delete cur;
					}
					else if (cur->_right == nullptr) {//右为空 同上
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
					else {//都不为空
						BSnode* sleft = cur->_right;
						prev = cur;

						while (sleft->_left) {
							prev = sleft;//在这里prev就充当交换后要删除结点的父节点
							//当要删除的是根节点，prev = cur也起到了对应的作用
							sleft = sleft->_left;
						}

						swap(cur->_key, sleft->_key);
						//找的是最左节点 是上面情况的左树为空
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

		//这里递归实现中序遍历 但需要根节点的形参 但是作为接口 _root对外不可见
		//这里就搞个子递归(对外不可见)
		void Inorder() {
			InorderR(_root);
			cout << endl;
		}

		//这里就不写对应的递归了

	protected:
		void InorderR(BSnode* root) {
			if (root == nullptr)
				return;

			InorderR(root->_left);
			cout << root->_key << ": " << root->_value << endl;
			InorderR(root->_right);
		}

		void Destroy(BSnode*& root) {//中序删除
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
