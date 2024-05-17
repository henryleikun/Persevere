#define _CRT_SECURE_NO_WARNINGS 1
#include <string>
#include "BinarySearchTree.h"
//using namespace Key;
using namespace kv;

void TestBSTree()
{
	BStree<string, string> dict;
	dict.Insert("insert", "����");
	dict.Insert("erase", "ɾ��");
	dict.Insert("left", "���");
	dict.Insert("string", "�ַ���");

	string str;
	while (cin >> str)
	{
		auto ret = dict.Find(str);
		if (ret)
		{
			cout << str << ":" << ret->_value << endl;
		}
		else
		{
			cout << "����ƴд����" << endl;
		}
	}

	string strs[] = { "ƻ��", "����", "ƻ��", "ӣ��", "ƻ��", "ӣ��", "ƻ��", "ӣ��", "ƻ��" };
	// ͳ��ˮ�����ֵĴ���
	BStree<string, int> countTree;
	for (auto str : strs)
	{
		auto ret = countTree.Find(str);
		if (ret == NULL)
		{
			countTree.Insert(str, 1);
		}
		else
		{
			ret->_value++;
		}
	}
	countTree.Inorder();
}

int main() {
	/*BStree<int> bs;

	bs.InsertR(8);
	bs.InsertR(3);
	bs.InsertR(10);
	bs.InsertR(1);
	bs.InsertR(6);
	bs.InsertR(4);
	bs.InsertR(7);

	bs.Inorder();

	if (bs.FindR(7))
		cout << "�ҵ���" << endl;

	bs.EraseR(8);
	bs.Inorder();*/
	TestBSTree();

	return 0;
}
