//#include "RBtree.h"
#include <iostream>
#include <utility>
#include <map>
#include <set>

using std::make_pair;
using std::cout;
using std::endl;
using std::map;
using std::set;
using std::multimap;
using std::multiset;//multi允许有重复key值

//void Test_Rbtree() {
//	RBtree<string, string> rb;
//	rb.Insert(make_pair("insert", "插入"));
//	rb.Insert(make_pair("erase", "删除"));
//	rb.Insert(make_pair("left", "左"));
//	rb.Insert(make_pair("right", "右"));
//	rb.Insert(make_pair("sort", "排序"));
//
//	rb.Inorder();
//
//	cout << rb.size() << endl;
//	
//	if (rb.Is_RBtree()) {
//		cout << "是红黑树" << endl;
//	}
//}

void Test_stan_set() {
	int a[] = { 8,9,5,0,10,20,50,11,33,90 };

	set<int> s;//key型红黑树 去重 排序 查找
	
	for (auto e : a) {
		s.insert(e);
	}

	set<int>::iterator it;
	for (it = s.begin(); it != s.end(); it++) {
		cout << *it << " ";
	}

	cout << endl;

	set<int>::iterator it1,it2;
	//cout << s.count(5) << endl;//看5有几个 主要针对multi来设计 这里只有0 1
	it1 = s.lower_bound(5);//lower_bound 返回第一个>=5的迭代器
	it2 = s.upper_bound(20);//upper_bound返回第一个>20的迭代器 it2指向33
	s.erase(it1,it2);//注意erase的迭代器区间是左闭右开

	for (it = s.begin(); it != s.end(); it++) {
		cout << *it << " ";
	}//0 33 50 90 
	cout << endl;

	set<int>::iterator it3;
	auto itr = s.equal_range(33);//返回一个pair<iterator,iterator>左闭右开一段相等元素的范围
	//也是主要是为multi系列做准备 第二个迭代器指向最后一个相同元素的下一个
	//元素不存在就 返回两个指向同一个元素的迭代器 这个元素是>这个元素的第一个 没有就报错

	for (it3 = itr.first; it3 != itr.second; it3++)
		cout << *it3 << " ";
	cout << endl;

	it3 = itr.first;
	cout << *it3 << endl;
	it3 = itr.second;
	cout << *it3 << endl;
}

void Test_stan_map() {
	int a[] = { 8,9,5,0,10,20,50,11,33,90 };

	map<int, int> m;//key-value型的红黑树实现 去重 排序 查找
	for (auto e : a) {
		m.insert(make_pair(e,e));
	}

	map<int, int>::iterator it;
	for (it = m.begin(); it != m.end(); it++) {
		cout << it->first << " ";
	}

	cout << endl;

	it = m.find(33);//找的是key 这不管是map还是set 查找的关键永远是key值 没找到返回end()(nullptr)
	cout << it->first << endl;
	//其他方法 都和set里的类似 map的特殊之处 就是他的重载[]
	//重载[]就是 传入key值 返回对应value的引用 也就是你可以借此机会修改value值
	//并且这也是一个插入的过程 如果key值不存在 那就插入对应key值value默认
	m[20] = 21;
	m[22];//仅仅插入
	m[22] = 22;

	for (it = m.begin(); it != m.end(); it++) {
		cout << it->first << ":" << it->second << endl; 
	}
}
//multi系列 就不说明了 具体定制接口在set那里也说了 主要是 能存重复元素 底层还是能存相同元素的红黑树实现

int main1() {
	//Test_Rbtree();
	//Test_stan_set();
	//Test_stan_map();

	return 0;
}