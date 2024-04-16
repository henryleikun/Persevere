#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include  <cassert>
#include <list>

using namespace std;

//queueҲ�Ǹ������� �ײ�����������list��ʵ��
//queueҪʵ�ֵķ��� front back push(β) pop(ͷ) empty
namespace Henry {//�͸ղŵ�stack��һ�������ռ� ע�����Ƴ�ͻ
	template<class T,class Container = deque<T>>
	class queue {
	private:
		Container _con;
	public:
		queue() {

		}

		void push(const T& val) {
			_con.push_back(val);
		}

		void pop() {
			assert(!empty());
			_con.pop_front();
		}

		size_t size() {
			return _con.size();
		}

		bool empty() {
			return size() == 0;
		}

		T& front() {
			return _con.front();
		}

		T& back() {
			return _con.back();
		}
	};
}