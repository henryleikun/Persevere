#pragma once
#include <map>
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

template<class T>
class UnionFindSet {
private:
	vector<int> _ufs; //���鼯
	vector<T> _elems;//�±���Ԫ��  
	map<T, int> _indexMap;//Ԫ�����±�
public:
	UnionFindSet() = default;

	//��vector����ʼ��
	UnionFindSet(const vector<T>& elems) {
		size_t n = elems.size();
		_ufs.resize(n, -1);

		_elems.resize(n);
		for (int i = 0; i < n; i++) {
			_elems[i] = elems[i];
		}

		for (size_t i = 0; i < n; ++i) {
			//_indexMap.insert(make_pair(elems[i], i));
			_indexMap[elems[i]] = i;//�����ڻ��Զ������
		}
	}

	size_t GetIndex(const T& t) {
		auto it = _indexMap.find(t);
		if (it == _indexMap.end()) assert(false);

		return _indexMap[t];
	}

	//�Ҷ�ӦԪ�صĸ��ڵ�
	size_t FindRoot(const T& t) {
		size_t root = GetIndex(t);

		int val = _ufs[root];
		while (val >= 0) {
			root = val;
			val = _ufs[root];
		}

		//·��ѹ��
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

	//����Ԫ���Ƿ���һ��������
	bool IsInSet(const T& t1, const T& t2) {
		return FindRoot(t1) == FindRoot(t2);
	}

	//�ϲ�����Ԫ�ص�һ�������� ��������  �Ǿ����涼����
	void Union(const T& t1, const T& t2) {
		size_t root1 = FindRoot(t1);
		size_t root2 = FindRoot(t2);

		if (root1 == root2)
			return;//ɶ������

		//�����ٵĸ����ϲ����ϴ�ĸ���
		if (abs(_ufs[root1]) < abs(_ufs[root2]))
			swap(root1, root2);
		//root1�Ǽ��ϴ��

		_ufs[root1] += _ufs[root2];
		_ufs[root2] = root1;
	}

	//�ò��鼯�ж��ٸ�����
	size_t SetSize() {
		size_t ret = 0;
		for (auto& e : _ufs) {
			if (e < 0)
				ret++;
		}

		return ret;
	}
};

