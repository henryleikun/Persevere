#define _CRT_SECURE_NO_WARNINGS 1

#include "Date.h"

//ȫȱʡ�Ĺ��캯��(ͬʱ�䵱Ĭ�Ϲ��캯��)
Date::Date(int year, int month, int day) {
	_year = year;
	_month = month;
	_day = day;
}

//�������캯��  ����û���漰��̬�ڴ�(��Դ����),��ʵʹ�ñ��������ľ��� ����ֻ������ϰ
Date::Date(const Date& rhs) {
	_year = rhs._year;
	_month = rhs._month;
	_day = rhs._day;
}

//���������

// = ��ֵ���������
Date& Date::operator=(const Date& rhs) {
	_year = rhs._year;
	_month = rhs._month;
	_day = rhs._day;

	return *this;
}

//+���ڼ�����û������ ���ڼ������� �������ʲô����
//������Ҫ��ʵ��+=������ ʵ��+��Ϊ�����ʵ��+ ������ֲ����� Ȼ���漰����ֵ ��Ҫ����������
//Ч�ʵ� ��ʵ��+=ֱ�Ӷ�*this���� ���ص����� �������ʵ��+�����

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
	if (days < 0) {//��-���ڼ�+
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

//+  ����ı���ö���
Date Date::operator+(int days)const {
	Date tmp(*this);
	tmp += days;

	return tmp;
}

//ͬ�����Ҳ�� ���������Ҫ�������� ���ڼ������� ���ڼ����Ǽ���ǰ��ʲô����

//������
//-=
Date& Date::operator-=(int days) {
	if (days < 0) {//��-���ڼ�+
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

//������ ����һ������
int Date::operator-(const Date& rhs)const {
	Date maxd = *this;
	Date mind = rhs;

	if (maxd < mind) {
		maxd = rhs;
		mind = *this;
	}

	int count = 0;

	while (maxd != mind) {
		++mind;//������ǰ�� Ч�ʸߵ�
		count++;
	}

	return count;
}

//ǰ��++
Date& Date::operator++() {
	*this += 1;

	return *this;
}

//����==
Date Date::operator++(int) {//int�������� ǿ������
	Date tmp(*this);
	++(*this);

	return tmp;//�ȷ��� ��++
}

//ͬ��--
//ǰ��--
Date& Date::operator--() {
	(*this) -= 1;

	return *this;
}

//����--
Date Date::operator--(int) {
	Date tmp(*this);
	--(*this);

	return tmp;
}

//==   ��ϵ�����ע�������
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












