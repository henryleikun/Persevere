#pragma once
#include "RBtree.h"

namespace Henry {
	template<class K>
	class set {
		struct SetKeyofValue {
			const K& operator()(const K& key) {
				return key;
			}
		};
	private:
		RBtree<K, K, SetKeyofValue> rbtree;
	public:
		//key值是不允许被修改的 而set只有一个key值 所以其迭代器和常迭代器都是由红黑树的常迭代器定义的
		//这里有个小知识点 就是类的作用域限定符::的结果要么是类中的静态成员或成员函数要么是对应的内置类型比如
		//内部类 而在类没有实例化时去搞这个typedef 编译器并不知道下面的const_iterator是静态成员还是
		//内置类型 而这时要加上typename告诉编译器 这是内置类型
		typedef typename RBtree<K, K, SetKeyofValue>::const_iterator iterator;
		typedef typename RBtree<K, K, SetKeyofValue>::const_iterator const_iterator;

		pair<iterator,bool> insert(const K& key) {
			return rbtree.Insert(key);//返回的pair里的iterator是普通迭代器 但这里的iterator
			//实际上是const_iterator 不能转换 
			//但是 template<class U, class V> pair (const pair<U,V>& pr);这是pair的复制构造函数
			//这个构造函数很nb 是一个模板函数 如果U V和本pair的模板参数相同就是普通的复制构造 但如果不同
			//并且支持 U V对应成员可以去初始化本pair的成员即first(pr.first)这样 那就是一个构造函数 
			//所以这里的问题就是iterator能否去初始化const_iterator显然不行 库里是实现了const_iterator的构造函数
			//能够接收iterator作为参数构造 这里就使用一种更好理解的 让Insert返回pair<Node*,bool>Node* 可以
			//构造iterator也能构造const_iterator
		}

		void inorder() {
			rbtree.Inorder();
		}

		bool find(const K& key) {//set的find就是看有没有
			if (rbtree.Find(key)._pnode) {//Find返回迭代器
				return true;
			}
			else {
				return false;
			}
		}
        
		//下面两个方法普通对象和常对象都可以调用 没有区别 因为这里的iterator实际是const_iterator
		//不用分别实现 普通版本和常版本
		iterator begin() const {
			return rbtree.cbegin();
		}

		iterator end() const{
			return rbtree.cend();
		}

	};
}
