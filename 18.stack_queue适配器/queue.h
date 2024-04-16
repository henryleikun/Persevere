#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include  <cassert>
#include <list>

using namespace std;

//queue也是个适配器 底层容器可以用list来实现
//queue要实现的方法 front back push(尾) pop(头) empty
namespace Henry {//和刚才的stack在一个命名空间 注意名称冲突
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