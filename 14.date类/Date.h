#pragma once
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::ostream;
using std::istream;

//实现一个日期类 主要也是归纳类的相关知识  类的构造 析构 拷贝构造 运算符重载
//和一些日期的计算算法 友元  这里的类不涉及动态内存管理

class Date {
private:
	int _year;
	int _month;
	int _day;
	
protected:
	int GetMonthdays(int month);//辅助函数 写到protected中

public:
	//全缺省的构造函数(同时充当默认构造函数)
	Date(int year = 0, int month = 0, int day = 0);

	//拷贝构造函数
	Date(const Date& rhs);

	//析构函数
	~Date(){}//类内定义函数 被编译器看作内联函数


	//运算符重载

	// = 赋值运算符重载
	Date& operator=(const Date& rhs);

	//+日期加日期没有意义 日期加天数有 几天后是什么日期
	//但这里要先实现+=在重用 实现+因为如果先实现+ 会引入局部对象 然后涉及返回值 又要调拷贝函数
	//效率低 而实现+=直接对*this操作 返回的引用 重用这个实现+会更好

	//+=
	Date& operator+=(int days);

	//+
	Date operator+(int days)const;
	
	//同理减法也是 但这里减法要更有意义 日期减是相差几天 日期减天是几天前是什么日期
	
	//减天数
	//-=
	Date& operator-=(int days);

	//-
	Date operator-(int days)const;

	//减日期 这是一个重载
	int operator-(const Date& rhs)const;

	//前置++
	Date& operator++();

	//后置==
	Date operator++(int);//如果没int就有二义性 这里强行重载 区分前后置 而且是先返回在++所以不是返回
	//引用

	//同理--
	//前置--
	Date& operator--();

	//后置--
	Date operator--(int);

	//==   关系运算符注意好重用
	bool operator==(const Date& rhs)const;

	//>
	bool operator>(const Date& rhs)const;

	//>=
	bool operator>=(const Date& rhs)const;

	//<
	bool operator<(const Date& rhs)const;

	//<=
	bool operator<=(const Date& rhs)const;

	//!=
	bool operator!=(const Date& rhs)const;

	friend ostream& operator<<(ostream& os, const Date& rhs);
	friend istream& operator>>(istream& is, Date& rhs);
};
