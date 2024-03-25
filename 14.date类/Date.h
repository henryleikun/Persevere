#pragma once
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::ostream;
using std::istream;

//ʵ��һ�������� ��ҪҲ�ǹ���������֪ʶ  ��Ĺ��� ���� �������� ���������
//��һЩ���ڵļ����㷨 ��Ԫ  ������಻�漰��̬�ڴ����

class Date {
private:
	int _year;
	int _month;
	int _day;
	
protected:
	int GetMonthdays(int month);//�������� д��protected��

public:
	//ȫȱʡ�Ĺ��캯��(ͬʱ�䵱Ĭ�Ϲ��캯��)
	Date(int year = 0, int month = 0, int day = 0);

	//�������캯��
	Date(const Date& rhs);

	//��������
	~Date(){}//���ڶ��庯�� ��������������������


	//���������

	// = ��ֵ���������
	Date& operator=(const Date& rhs);

	//+���ڼ�����û������ ���ڼ������� �������ʲô����
	//������Ҫ��ʵ��+=������ ʵ��+��Ϊ�����ʵ��+ ������ֲ����� Ȼ���漰����ֵ ��Ҫ����������
	//Ч�ʵ� ��ʵ��+=ֱ�Ӷ�*this���� ���ص����� �������ʵ��+�����

	//+=
	Date& operator+=(int days);

	//+
	Date operator+(int days)const;
	
	//ͬ�����Ҳ�� ���������Ҫ�������� ���ڼ������� ���ڼ����Ǽ���ǰ��ʲô����
	
	//������
	//-=
	Date& operator-=(int days);

	//-
	Date operator-(int days)const;

	//������ ����һ������
	int operator-(const Date& rhs)const;

	//ǰ��++
	Date& operator++();

	//����==
	Date operator++(int);//���ûint���ж����� ����ǿ������ ����ǰ���� �������ȷ�����++���Բ��Ƿ���
	//����

	//ͬ��--
	//ǰ��--
	Date& operator--();

	//����--
	Date operator--(int);

	//==   ��ϵ�����ע�������
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
