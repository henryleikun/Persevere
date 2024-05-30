#pragma once
#include "RBtree.h"

namespace Henry {
	template<class K,class V>
	class map {
		struct MapKeyofValue {
			const K& operator()(const pair<K,V>& kv) {
				return kv.first;
			}
		};
	private:
		//map虽然可以改value 但K还是不能改 作为红黑树结点的T去构造对应的普通迭代器的时候 
		//还是能改这个K 也就是对于map你不能在迭代器Ref operator*()那里去特别指明k是const 但这里可以直接
		//传一个对应的const K 去处理
		//RBtree<K, pair<K, V>, MapKeyofValue> rbtree;
		RBtree<K, pair<const K, V>, MapKeyofValue> rbtree;
	public:
		//不同与set的迭代器 因为map的键值对pair key值不能被修改但value值可以修改 这便是普通迭代器要完成的
		//而常迭代器要求的是first second都不能被修改
		typedef typename RBtree<K, pair<const K, V>, MapKeyofValue>::iterator iterator;
		typedef typename RBtree<K, pair<const K, V>, MapKeyofValue>::const_iterator const_iterator;

		pair<iterator, bool> insert(const pair<K,V>& kv) {
			return rbtree.Insert(kv);
		}

		void inorder() {
			rbtree.Inorder();
		}

		iterator find(const K& key) {
			return  rbtree.Find(key);
		}

		iterator begin() {
			return rbtree.begin();
		}

		iterator end() {
			return rbtree.end();
		}

		//typedef _RBtree_iterator<T, T&, T*> iterator;
		//typedef _RBtree_iterator<T, const T&, const T*> const_iterator;
		const_iterator cbegin() const {
			return rbtree.cbegin();
		}

		const_iterator cend() const {
			return rbtree.cend();
		}

		//map专有的一个运算符重载 [key] 返回对应key的value 并且能修改 故传引用
		//还有 如果key不存在 那就直接插入一个key
		//这就需要提一下 STL的实现里insert是返回pair<iterator,bool>的 
		//插入成功就是 新结点的迭代器和true失败就是已经存在结点的迭代器和false 这用来实现[]很好用
		V& operator[](const K& key) {
			//pair<K, V>& ret = *(rbtree.Insert(make_pair(key, V())).first);
			pair<iterator, bool> ret = rbtree.Insert(make_pair(key, V()));

			return ret.first->second;
			//ret.first对饮结点的迭代器 it it->second ---> it.operator->()->second
		}

	};
}