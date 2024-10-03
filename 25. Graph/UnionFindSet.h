#pragma once
#include <map>
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

template<class T>
class UnionFindSet {
private:
	vector<int> _ufs; //并查集
	vector<T> _elems;//下标找元素  
	map<T, int> _indexMap;//元素找下标
public:
	UnionFindSet() = default;

	//用vector来初始化
	UnionFindSet(const vector<T>& elems) {
		size_t n = elems.size();
		_ufs.resize(n, -1);

		_elems.resize(n);
		for (int i = 0; i < n; i++) {
			_elems[i] = elems[i];
		}

		for (size_t i = 0; i < n; ++i) {
			//_indexMap.insert(make_pair(elems[i], i));
			_indexMap[elems[i]] = i;//不存在会自动插入的
		}
	}

	size_t GetIndex(const T& t) {
		auto it = _indexMap.find(t);
		if (it == _indexMap.end()) assert(false);

		return _indexMap[t];
	}

	//找对应元素的根节点
	size_t FindRoot(const T& t) {
		size_t root = GetIndex(t);

		int val = _ufs[root];
		while (val >= 0) {
			root = val;
			val = _ufs[root];
		}

		//路径压缩
		if (root != GetIndex(t)) {
			size_t parent;

			size_t index = GetIndex(t);
			while (_ufs[index] >= 0) {
				parent = _ufs[index];
				_ufs[index] = root;
				index = parent;
			}
		}

		return root;
	}

	//两个元素是否在一个集合里
	bool IsInSet(const T& t1, const T& t2) {
		return FindRoot(t1) == FindRoot(t2);
	}

	//合并两个元素到一个集合里 本来就在  那就上面都不做
	void Union(const T& t1, const T& t2) {
		size_t root1 = FindRoot(t1);
		size_t root2 = FindRoot(t2);

		if (root1 == root2)
			return;//啥都不做

		//集合少的个数合并集合大的个数
		if (abs(_ufs[root1]) < abs(_ufs[root2]))
			swap(root1, root2);
		//root1是集合大的

		_ufs[root1] += _ufs[root2];
		_ufs[root2] = root1;
	}

	//该并查集有多少个集合
	size_t SetSize() {
		size_t ret = 0;
		for (auto& e : _ufs) {
			if (e < 0)
				ret++;
		}

		return ret;
	}
};

