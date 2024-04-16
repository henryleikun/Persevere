#pragma once
//stack 和queue不同于前面的vector和list这两个不是容器 而是
//STL六大组件(容器 迭代器 仿函数 空间配置器 适配器 算法)里的适配器
//包括后续的优先级队列也是

//适配器 没有迭代器的实现 适配器就像 手机充电器 220v的电进行变压 适配特定的电器
//以stack为例 stack作为适配器 通过其他底层容器的接口来实现自己的接口

//1.stack是一种容器适配器，专门用在具有后进先出操作的上下文环境中，其删除只能从容器的一端进行
//元素的插入与提取操作。
//2. stack是作为容器适配器被实现的，容器适配器即是对特定类封装作为其底层的容器，并提供一组特定
//的成员函数来访问其元素，将特定类作为其底层的，元素特定容器的尾部(即栈顶)被压入和弹出。
//3. stack的底层容器可以是任何标准的容器类模板或者一些其他特定的容器类，这些容器类应该支持以下
//操作：
//empty：判空操作
//back：获取尾部元素操作
//push_back：尾部插入元素操作
//pop_back：尾部删除元素操作
//4. 标准容器vector、deque、list均符合这些需求，默认情况下，如果没有为stack指定特定的底层容器，
//默认情况下使用deque。

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include  <cassert>

using namespace std;

//默认是deque其实 vector更适合这个底层容器
//stack要实现的接口 pop push size top empty 
namespace Henry {
	template<class T,class Container = deque<T>>
	class stack {
	private:
		Container _con;
	public:
		stack() {//默认调用_con的的默认构造
			     //析构也是自动调用
		}

		void push(const T& val) {
			_con.push_back(val);
		}

		void pop() {
			assert(!empty());
			_con.pop_back();
		}

		size_t size() {
			return _con.size();
		}

		bool empty() {
			return _con.size() == 0;
		}

		T& top() {
			assert(!empty());
			return _con.back();
		}
	};
}