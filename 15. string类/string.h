#pragma once
#include <iostream>
#include <cassert>
#include <cstring>
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::istream;

//����׼�����string�ӿ���д ����string��������basic_string<char>��ʵ���� ���漰ģ��
//string����Ϊ'\0'�Ǳ�ʶ�� �����ַ� _size == strlen(_str)  ��_capacity��ʱ������˸�'\0'Ԥ���ռ�   
namespace Henry {
	class string {
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		static const size_t npos;
	public:
		typedef char* iterator;

		string(const char* str = "");
		string(const string& s);
		string& operator=(const string& s);
		~string();



		// iterator
		iterator begin();
		iterator end();

		// modify
		void push_back(char c);
		string& operator+=(char c);
		void append(const char* str);
		string& operator+=(const char* str);
		string& operator+=(const string& str);
		void clear();
		void swap(string& s);
		const char* c_str()const;

		// capacity
		size_t size()const;
		size_t capacity()const;
		bool empty()const;
		void resize(size_t n, char c = '\0');
		void reserve(size_t n);

		// access
		char& operator[](size_t index);
		const char& operator[](size_t index)const;

		//relational operators
		bool operator<(const string& s)const;
		bool operator<=(const string& s)const;
		bool operator>(const string& s)const;
		bool operator>=(const string& s)const;
		bool operator==(const string& s)const;
		bool operator!=(const string& s)const;


		// ����c��string�е�һ�γ��ֵ�λ��
		size_t find(char c, size_t pos = 0) const;

		// �����Ӵ�s��string�е�һ�γ��ֵ�λ��
		size_t find(const char* s, size_t pos = 0) const;

		// ��posλ���ϲ����ַ�c/�ַ���str
		string& insert(size_t pos, char c);
		string& insert(size_t pos, const char* str);

		// ɾ��posλ���ϵ�Ԫ��
		string& erase(size_t pos, size_t len = npos);

		//���ض�Ӧ�����Ӵ�
		string substr(size_t pos, size_t len = npos);


		friend ostream& operator<<(ostream& os, const string& s);
		friend istream& operator>>(istream& is, string& s);
	};
}
