#include "Mymap.h"
#include "Myset.h"
using namespace Henry;

void Test_Myset() {
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

	s.inorder();

	if (s.find(33)) {
		cout << "找到了" << endl;
	 }
}

void Test_Mymap() {
	int a[] = { 8,9,5,0,10,20,50,11,33,90 };

	map<int, int> m;//key-value型的红黑树实现 去重 排序 查找
	for (auto e : a) {
		m.insert(make_pair(e, e));
	}

	map<int, int>::iterator it;
	for (it = m.begin(); it != m.end(); it++) {
		cout << it->first << " ";
	}

	cout << endl;

	it = m.find(33);//找的是key 这不管是map还是set 查找的关键永远是key值 没找到返回end()(nullptr)
	cout << it->first << endl;

	m[20] = 21;
	m[22];//仅仅插入
	m[22] = 22;

	for (it = m.begin(); it != m.end(); it++) {
		cout << it->first << ":" << it->second << endl;
	}
}

void Test_Mymap2() {
	string strs[] = { "苹果", "西瓜", "苹果", "樱桃", "苹果", "樱桃", "苹果", "樱桃", "苹果" };

	map<string, int> countMap;
	map<string, int>::iterator it;

	for (auto e : strs) {
		it = countMap.find(e);
		if (it == countMap.end()) {//没找到
			countMap[e]++;//插入+修改
		}
		else {//找到
			it->second++;
		}
	}

	for (it = countMap.begin(); it != countMap.end(); it++) {
		cout << it->first << ":" << it->second << endl;
	}
}

int main() {
	//Test_Myset();
	//Test_Mymap();
	Test_Mymap2();

	return 0;
}