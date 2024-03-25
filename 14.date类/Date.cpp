#define _CRT_SECURE_NO_WARNINGS 1

#include "Date.h"

//全缺省的构造函数(同时充当默认构造函数)
Date::Date(int year, int month, int day) {
	_year = year;
	_month = month;
	_day = day;
}

//拷贝构造函数  这里没有涉及动态内存(资源管理),其实使用编译器给的就行 这里只是做练习
Date::Date(const Date& rhs) {
	_year = rhs._year;
	_month = rhs._month;
	_day = rhs._day;
}

//运算符重载

// = 赋值运算符重载
Date& Date::operator=(const Date& rhs) {
	_year = rhs._year;
	_month = rhs._month;
	_day = rhs._day;

	return *this;
}

//+日期加日期没有意义 日期加天数有 几天后是什么日期
//但这里要先实现+=在重用 实现+因为如果先实现+ 会引入局部对象 然后涉及返回值 又要调拷贝函数
//效率低 而实现+=直接对*this操作 返回的引用 重用这个实现+会更好

int Date::GetMonthdays(int month) {
	int Monthdays[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

	if (month == 2 && ((_year % 4 == 0 && _year % 100 != 0) || _year % 400 == 0)) {
		return 29;
	}
	else {
		return Monthdays[month];
	}
}

//+=
Date& Date::operator+=(int days) {
	if (days < 0) {//加-等于减+
		(*this) -= -days;

		return *this;
	}

	_day += days;

	while (_day > GetMonthdays(_month)) {
		
		_day -= GetMonthdays(_month);
		_month++;
		if (_month > 12) {
			_year++;
			_month = 1;
		}
	}

	return *this;
}

//+  不会改变调用对象
Date Date::operator+(int days)const {
	Date tmp(*this);
	tmp += days;

	return tmp;
}

//同理减法也是 但这里减法要更有意义 日期减是相差几天 日期减天是几天前是什么日期

//减天数
//-=
Date& Date::operator-=(int days) {
	if (days < 0) {//减-等于加+
		(*this) += -days;
		return *this;
	}

	_day -= days;

	while (_day <= 0) {
		_month--;

		if (_month == 0) {
			_month = 12;
			_year--;
		}

		_day += GetMonthdays(_month);
	}

	return *this;
}

//-
Date Date::operator-(int days)const {
	Date tmp(*this);

	tmp -= days;
	
	return tmp;
}

//减日期 这是一个重载
int Date::operator-(const Date& rhs)const {
	Date maxd = *this;
	Date mind = rhs;

	if (maxd < mind) {
		maxd = rhs;
		mind = *this;
	}

	int count = 0;

	while (maxd != mind) {
		++mind;//尽量用前置 效率高点
		count++;
	}

	return count;
}

//前置++
Date& Date::operator++() {
	*this += 1;

	return *this;
}

//后置==
Date Date::operator++(int) {//int来做区分 强制重载
	Date tmp(*this);
	++(*this);

	return tmp;//先返回 在++
}

//同理--
//前置--
Date& Date::operator--() {
	(*this) -= 1;

	return *this;
}

//后置--
Date Date::operator--(int) {
	Date tmp(*this);
	--(*this);

	return tmp;
}

//==   关系运算符注意好重用
bool Date::operator==(const Date& rhs)const {
	
	return _year == rhs._year
		&& _month == rhs._month
		&& _day == rhs._day;
}

//>
bool Date::operator>(const Date& rhs)const {

	return _year > rhs._year
		|| (_year == rhs._year && _month > rhs._month)
		|| (_year == rhs._year && _month == rhs._month && _day > rhs._day);
    
}

//>=
bool Date::operator>=(const Date& rhs)const {

	return (*this) == rhs || (*this) > rhs;
}

//<
bool Date::operator<(const Date& rhs)const {
	
	return !((*this) >= rhs);
}

//<=
bool Date::operator<=(const Date& rhs)const {

	return (*this) < rhs || (*this) == rhs;
}

//!=
bool Date::operator!=(const Date& rhs)const {
	return !((*this) == rhs);
}

ostream& operator<<(ostream& os, const Date& rhs) {
	os << rhs._year << "/" << rhs._month << "/" << rhs._day<<" ";

	return os;
}

istream& operator>>(istream& is, Date& rhs) {
	is >> rhs._year >> rhs._month >> rhs._day;

	return is;
}












