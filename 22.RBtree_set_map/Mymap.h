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
		//map��Ȼ���Ը�value ��K���ǲ��ܸ� ��Ϊ���������Tȥ�����Ӧ����ͨ��������ʱ�� 
		//�����ܸ����K Ҳ���Ƕ���map�㲻���ڵ�����Ref operator*()����ȥ�ر�ָ��k��const ���������ֱ��
		//��һ����Ӧ��const K ȥ����
		//RBtree<K, pair<K, V>, MapKeyofValue> rbtree;
		RBtree<K, pair<const K, V>, MapKeyofValue> rbtree;
	public:
		//��ͬ��set�ĵ����� ��Ϊmap�ļ�ֵ��pair keyֵ���ܱ��޸ĵ�valueֵ�����޸� �������ͨ������Ҫ��ɵ�
		//����������Ҫ�����first second�����ܱ��޸�
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

		//mapר�е�һ����������� [key] ���ض�Ӧkey��value �������޸� �ʴ�����
		//���� ���key������ �Ǿ�ֱ�Ӳ���һ��key
		//�����Ҫ��һ�� STL��ʵ����insert�Ƿ���pair<iterator,bool>�� 
		//����ɹ����� �½��ĵ�������trueʧ�ܾ����Ѿ����ڽ��ĵ�������false ������ʵ��[]�ܺ���
		V& operator[](const K& key) {
			//pair<K, V>& ret = *(rbtree.Insert(make_pair(key, V())).first);
			pair<iterator, bool> ret = rbtree.Insert(make_pair(key, V()));

			return ret.first->second;
			//ret.first�������ĵ����� it it->second ---> it.operator->()->second
		}

	};
}