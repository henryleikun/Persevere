#pragma once
#include "HashTable.h"

namespace Henry {
	template<class K,class V>
	class unordered_map {
		struct mapkeyofvalue {
			K operator()(const pair<K,V>& kv) {
				return kv.first;
			}
		};
	private:
		HashTable<K, pair<const K,V>, mapkeyofvalue> ht;
	public:
		typedef typename HashTable<K, pair<const K, V>, mapkeyofvalue>::iterator iterator;
		typedef typename HashTable<K, pair<const K, V>, mapkeyofvalue>::const_iterator const_iterator;

		iterator begin() {
			return ht.begin();
		}

		iterator end() {
			return ht.end();
		}

		const_iterator cbegin() const {
			return ht.cbegin();
		}

		const_iterator cend() const {
			return ht.cend();
		}

		pair<iterator,bool> insert(const pair<K,V>& data) {
			return ht.Insert(data);
		}

		bool erase(const K& key) {
			return ht.Erase(key);
		}

		iterator find(const K& key) {
			auto ret = ht.Find(key);
			return ret;
		}

		V& operator[](const K& key) {
			auto ret = ht.Insert(make_pair(key, V()));
			return ret.first->second;
		}
	};
}

