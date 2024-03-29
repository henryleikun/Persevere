#define _CRT_SECURE_NO_WARNINGS 1
#include "string.h"
//#include <string>

//using std::string;
using Henry::string;

void Test() {

	string s1 = "0123456";
	string s2 = "9876543";
	//cin >> s1;
	//cout << s1;  cin cout +=字符 ok

	//s1.insert(0, '9');
	//cout << s1;	 insert ok

	//cout << (s1 > s2) << endl;  关系操作符没问题

	/*cout << s1.capacity()<<endl;
	
	s1.reserve(3);
	cout << s1.capacity() << endl;
	
	s1.reserve(9);
	cout << s1.capacity() << endl;*/  //reserve ok

	/*cout << "capcacity: " << s1.capacity() << endl;
	cout << "size: " << s1.size() << endl;

	s1.resize(3);
	cout << "capcacity: " << s1.capacity() << endl;
	cout << "size: " << s1.size() << endl;

	s1.resize(9,'x');
	cout << "capcacity: " << s1.capacity() << endl;
	cout << "size: " << s1.size() << endl;

	cout << s1 << endl;*/ //resize ok

	//for (auto e : s1) {
		//cout << e;
	//}//基于范围的for循环底层是迭代器 但这个迭代器实现就只是类似宏的替换 提供迭代器的名字必须
	//是begin() 和end()   迭代器 ok

	/*char str[] = "******";
	s1 += str;
	cout << s1 << endl;

	s2.push_back('x');
	cout << s2 << endl;*/ //+=字符串 push_back ok

	/*char str[] = "******";
	s1.append(str);
	cout << s1 << endl;*/ //append 没问题

	/*s1.erase(3,2);
	cout << s1 << endl;*/ //erase ok

	//size_t pos = s1.find('4', 0);//从下标为零出开始找 4
	////if (pos != s1.npos) {//npos 是private

	////}

	//if (pos != -1) {
	//	cout << s1[pos];
	//}                    find字符  []  ok

	size_t pos = s1.find("234");
	string sub = s1.substr(pos);
	cout << sub << endl;  //substr find子串  ok
}

int main() {
	Test();

	return 0;
}