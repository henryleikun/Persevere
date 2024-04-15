#pragma once

#include <iostream>
//#include <list>
#include "list.h"

using namespace Henry;

int main() {
	list<int> ls;
	ls.push_back(1);
	ls.push_back(2);
	ls.push_back(3);
	ls.push_back(4);
	ls.push_back(5);

	list<int>::iterator it(ls.begin());

	/*for (; it != ls.end(); it++) {
		cout << *it << " ";
	}*/

	for (auto e : ls) {//底层是迭代器
		cout << e << " ";
	}
	cout << endl;

	const list<int> ll(ls.begin(),ls.end());
	list<int>::const_iterator constit = ll.begin();//调用对应const版本

	//*constit = 1; 不允许

	ls.pop_back();
	ls.pop_front();

	for (auto e : ls) {//底层是迭代器
		cout << e << " ";
	}
	cout << endl;

	ls.push_front(1);
	for (auto e : ls) {//底层是迭代器
		cout << e << " ";
	}
	cout << endl;

	struct S {
		int a;

		S(int _a = 0) :a(_a) {

		}
	};

	list<S> lls;
	lls.push_back(1);
	lls.push_back(2);
	lls.push_back(3);

	list<S>::iterator sit = lls.begin();

	cout << (*sit).a << endl;//你不能直接*sit 自定义类型 没有重载流插入
	//既然迭代器看作指针 那我 可以 sit->a
	//根据实现的-> sit->a ==>  sit.operator->()->a(sit->->a)但为了代码的可读性 以及像指针
	//靠拢 这里省略了中间的->
	sit++;
	cout << sit->a << endl;
	const list<S> clls(lls.begin(),lls.end());
	list<S>::const_iterator csit = clls.begin();
	//csit->a = 1; 不允许

	return 0;
}