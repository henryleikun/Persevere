#define _CRT_SECURE_NO_WARNINGS 1
#include <string>
#include "BinarySearchTree.h"
//using namespace Key;
using namespace kv;

void TestBSTree()
{
	BStree<string, string> dict;
	dict.Insert("insert", "插入");
	dict.Insert("erase", "删除");
	dict.Insert("left", "左边");
	dict.Insert("string", "字符串");

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
			cout << "单词拼写错误" << endl;
		}
	}

	string strs[] = { "苹果", "西瓜", "苹果", "樱桃", "苹果", "樱桃", "苹果", "樱桃", "苹果" };
	// 统计水果出现的次数
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
		cout << "找到了" << endl;

	bs.EraseR(8);
	bs.Inorder();*/
	TestBSTree();

	return 0;
}
