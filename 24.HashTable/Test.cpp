#include "Myunordered_map.h"
#include "Myunordered_set.h"
//#include <unordered_map>
//using namespace std;
using namespace Henry;

void Test1() {//线性探测
	/*HashTable<string, string> hash;
	hash.Insert(make_pair("Insert", "插入"));
	hash.Insert(make_pair("left", "左"));
	hash.Insert(make_pair("right", "右"));
	hash.Insert(make_pair("erase", "删"));
	hash.Insert(make_pair("empty", "空"));*/


	Linear_explore::HashTable<int, int> hash;
	hash.Insert(make_pair(1, 1));
	hash.Insert(make_pair(4, 4));
	hash.Insert(make_pair(14, 14));
	hash.Insert(make_pair(24, 24));
	hash.Insert(make_pair(6, 6));
	hash.Insert(make_pair(9, 9));

	//来点扩容的
	hash.Insert(make_pair(26, 26));
	hash.Insert(make_pair(7, 7));
}

void Test2() {//哈希桶
	Hash_Box::HashTable<int, int> hash;

	hash.Insert(make_pair(1, 1));
	hash.Insert(make_pair(4, 4));
	hash.Insert(make_pair(14, 14));
	hash.Insert(make_pair(24, 24));
	hash.Insert(make_pair(6, 6));
	hash.Insert(make_pair(9, 9));

	//hash.some();

	//涉及扩容 注意负载因子是1
	hash.Insert(make_pair(26, 26));
	hash.Insert(make_pair(29, 29));
	hash.Insert(make_pair(34, 34));
	hash.Insert(make_pair(10, 10));
	hash.Insert(make_pair(11, 11));//这一步扩
	hash.some();
}

//int main() {
//	//Test1();
//	//Test2();
//	//unordered_map<int, int> umap;
//	//umap.insert(make_pair(1, 1));
//	//umap.insert(make_pair(2, 2));
//	//umap.insert(make_pair(3, 3));
//
//	//unordered_map<int, int>::iterator it = umap.begin();
//	//it++;指向end 不能++
//	//it--;为空就不能-- 也就是迭代器你记住 只能再左闭右开的区间内移动
//
//	return 0;
//}

int main() {
	unordered_map<int, int> umap;
	umap.insert(make_pair(1, 1));
	umap.insert(make_pair(2, 2));
	umap.insert(make_pair(3, 3));

	//unordered_map<int, int>::iterator it = umap.end();
	/*it--;
	for (; it != umap.begin(); --it) {
		cout << (*it).first <<":" << (*it).second << endl;
	}*/

	unordered_map<int, int>::iterator it = umap.begin();

	//但其实库里面的哈希表遍历是按照插入顺序遍历的 这种实现是再哈希表结点中增加一个
	//新指针去维护插入的元素顺序形成一个 遍历用的链表 都还好
	for (; it != umap.end(); ++it) {
		cout << (*it).first << ":" << (*it).second << endl;
	}
	cout << endl;

	umap[4] = 4;
    
	it = umap.begin();
	for (; it != umap.end(); ++it) {
		cout << (*it).first << ":" << (*it).second << endl;
	}

	cout << endl;

	cout << (umap.find(4))->first << endl;

	umap.erase(2);
	it = umap.begin();
	for (; it != umap.end(); ++it) {
		cout << (*it).first << ":" << (*it).second << endl;
	}

	return 0;
}