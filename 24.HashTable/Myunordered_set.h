#pragma once
#include "HashTable.h"

namespace Henry {
	template<class K>
	class unordered_set {
		struct setkeyofvalue {
			K operator()(const K& key) {//����const K&Ҳ�� ������
				return key;
			}
		};
	private:
		HashTable<K, K, setkeyofvalue> ht;
	public:
		typedef typename HashTable<K, K, setkeyofvalue>::cosnt_iterator iterator;
		typedef typename HashTable<K, K, setkeyofvalue>::cosnt_iterator const_iterator;

		//set�����Ͳ��ܸ� iteratorҲ��const_iterator
		iterator begin() {
			return ht.cbegin();
		}

		iterator end() {
			return ht.cend();
		}

		const_iterator cbegin()const {
			return ht.cbegin();
		}

		const_iterator cend()const {
			return ht.cend();
		}

		bool insert(const K& key) {
			auto ret = ht.Insert(key);
			return ret.second;
		}

		bool erase(const K& key) {
			return ht.Erase(key);
		}

		bool find(const K& key) {
			auto ret = ht.Find(key);
			return ret != ht.end();
		}
	};
}
