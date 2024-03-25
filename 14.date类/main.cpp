#define _CRT_SECURE_NO_WARNINGS 1

#include "Date.h"

void Test() {
	Date date(2024, 3, 23);
	//Date date(2024, 3, 23);

	Date tmp = date + 100;//copy constructor
	cout <<"2024/3/23 100天后是" << tmp;
	cout << endl;

	tmp = date - 100;//assignment
	cout << "2024/3/23 100天前是" << tmp;
	cout<<endl;

	++date;
	cout << "2024/3/23 1天后是" << date;
	cout << endl;

	--date;
	cout << "2024/3/24 1天前是" << date;
	cout << endl;

	Date date1(2026, 3, 23);
	if (date1 > date) {
		cout << date1 << "大" << endl;
	}

	cout << date1 << "与" << date << "相差" << date1 - date << "天" << endl;

}

void Test1() {
	Date date(2024, 3, 23);

	//Date tmp = date - 100;
	date -= 100;

	cout << date << "100天前是" <<date<<endl;
}

int main() {
	Test();
	//Test1();

	return 0;
}