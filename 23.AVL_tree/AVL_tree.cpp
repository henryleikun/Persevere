#include "AVL_tree.h"

//template <class T1, class T2>
//pair<T1, T2> make_pair(T1 x, T2 y)
//{
//	return (pair<T1, T2>(x, y));
//} 关于make_pair模板函数

void Test() {
	AVLtree<string, string> avl;

	avl.Insert(make_pair("insert", "插入"));
	avl.Insert(make_pair("left", "左"));
	avl.Insert(make_pair("right", "右"));
	avl.Insert(make_pair("erase", "删除"));
	avl.Insert(make_pair("search", "查找"));

	avl.Inorder();

	if (avl.Is_balance())
		cout << "是平衡的" << endl;
}

int main() {
	Test();

	return 0;
}