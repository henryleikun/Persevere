#pragma once
#include <iostream>
#include <cassert>
#include <cstring>
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::istream;

//按标准库里的string接口来写 其中string本来就是basic_string<char>的实例化 不涉及模板
//string类认为'\0'是标识符 不算字符 _size == strlen(_str)  搞_capacity的时候别忘了给'\0'预留空间   
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


		// 返回c在string中第一次出现的位置
		size_t find(char c, size_t pos = 0) const;

		// 返回子串s在string中第一次出现的位置
		size_t find(const char* s, size_t pos = 0) const;

		// 在pos位置上插入字符c/字符串str
		string& insert(size_t pos, char c);
		string& insert(size_t pos, const char* str);

		// 删除pos位置上的元素
		string& erase(size_t pos, size_t len = npos);

		//返回对应长度子串
		string substr(size_t pos, size_t len = npos);


		friend ostream& operator<<(ostream& os, const string& s);
		friend istream& operator>>(istream& is, string& s);
	};
}
