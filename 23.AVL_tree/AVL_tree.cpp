#include "AVL_tree.h"

//template <class T1, class T2>
//pair<T1, T2> make_pair(T1 x, T2 y)
//{
//	return (pair<T1, T2>(x, y));
//} ����make_pairģ�庯��

void Test() {
	AVLtree<string, string> avl;

	avl.Insert(make_pair("insert", "����"));
	avl.Insert(make_pair("left", "��"));
	avl.Insert(make_pair("right", "��"));
	avl.Insert(make_pair("erase", "ɾ��"));
	avl.Insert(make_pair("search", "����"));

	avl.Inorder();

	if (avl.Is_balance())
		cout << "��ƽ���" << endl;
}

int main() {
	Test();

	return 0;
}