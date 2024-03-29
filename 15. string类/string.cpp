#define _CRT_SECURE_NO_WARNINGS 1

#include "string.h"
//����˵������  const size_t string::npos = -1; ��һ��ŵ�ͷ�ļ��� ����ͻ��ض���
//��Ϊ�����ռ�Ŀ����� �����������ͷ�ļ� �������Ὣչ�����ͷ�ļ����ͬ�������ռ� ����������ռ�
//�ϲ� ���� ͷ�ļ���ľ�̬��Ա����һ�� ����ϲ����ж���һ�� ����������ﶨ�� ���ŵ�ͷ�ļ��� �Ǿ�ֻ
// ����һ��  


namespace Henry {//�����ռ�Ŀ�����
	const size_t string::npos = -1;

	string::string(const char* str) {//Ĭ���ַ�������
		
		_capacity = strlen(str) == 0 ? 4 : strlen(str);
		_str = new char[_capacity + 1];
		_size = strlen(str);//Ĭ��_capcity = 4 _size = 0 

		strcpy(_str, str);
	}

	string::string(const string& s):_capacity(s._capacity),_size(s._size) {//���
		_str = new char[_capacity + 1];
		strcpy(_str, s._str);
	}

	string& string::operator=(const string& s) {

		if (this == &s) {
			return *this;
		}//��ֹ�Ը�ֵ

		delete[]_str;//�ͷ�֮ǰ�Ŀռ�

		_capacity = s._capacity;
		_size = s._size;

		_str = new char[_capacity + 1];
		strcpy(_str, s._str);
	}

	string::~string() {
		delete[]_str;
		_str = nullptr;
		_capacity = _size = 0;
	}


	// iterator ����ĵ���������ָ���������� ������������ڴ��ǿ��е� ������list��������ʵ��
	//��������ĵ�����������������ü򵥵ĵ�����
	string::iterator string::begin() {
		return _str;
	}

	string::iterator string::end() {
		return _str + _size;//����ҿ� �������һ������һλ��ָ��'\0'��ָ��
	}

	// modify
	void string::push_back(char c) {
		if (_capacity == _size) {
			reserve(_capacity * 2);//������
		}

		_str[_size++] = c;
		_str[_size] = '\0';//��ԭ����'\0'�����˱������ڸ����
	}

	string& string::operator+=(char c) {
		if (_size == _capacity)
			reserve(_capacity * 2);

		_str[_size++] = c;
		_str[_size] = '\0';

		//insert(_size, c);//�������
		
		return *this;
	}

	void string::append(const char* str) {//����һ���ַ���
		/*for (int i = 0; i < strlen(str); i++) {
			*this += str[i];
		}
		_size += strlen(str)*/

		size_t sz = strlen(str);

		if (_size + sz > _capacity)
			reserve(_size + sz);//���Ƕ�����_capacity�Ļ��㲻�ܱ�֤����һ������_size+sz

		strcpy(_str + _size, str);//���������õ� �����Ǹ�this��Ҫһֱ���ú���
		                      //��������Ҫ��ջ֡ ���ö���
		//strcat(_str,str)

		_size += sz;

		//insert(_size, str);//���ã�
	}

	string& string::operator+=(const char* str) {//�����append��ʵһ��
		/*for (int i = 0; i < strlen(str); i++) {
			*this += str[i];
		}
		_size += strlen(str);

		return *this;*/

		size_t sz = strlen(str);

		if (_size + sz > _capacity)
			reserve(_size + sz);

		strcpy(_str + _size, str);

		_size += sz;

		//insert(_size, str);

		return *this;

	}

	string& string::operator+=(const string& str) {
		size_t sz = str._size;

		if (_size + sz > _capacity)
			reserve(_size + sz);

		strcpy(_str + _size, str.c_str());

		_size += sz;

		return *this;
	}

	void string::clear() {
		_str[0] = '\0';
		_size = 0;
	}

	//��׼�� swap(string& a,string& b);
	//a.swap(b) ����� ����̫�࿽�������� ÿ�������ȿ���̫�� 
	void string::swap(string& s) {
		std::swap(_str, s._str);
		std::swap(_size, s._size);
		std::swap(_capacity, s._capacity);//�������� swap���Ǻܿ��
	}

	const char* string::c_str()const {//��stringת��ΪC�����ַ���
		return _str;
	}

	// capacity
	size_t string::size()const {
		return _size;
	}

	size_t string::capacity()const {
		return _capacity;
	}

	bool string::empty()const {
		return _size == 0;
	}

	void string::resize(size_t n, char c) {//cĬ����'\0'
    //resize��reserve�е��� �����Ǻܲ�һ���� ������string�ľ�����
	//resize����С��_capacity ����_size��ʱ��ͽ��Ǹı�_size 
	//С��_size��ʱ�� ����_capacity���ַ�������Чλ��Ϊresize�� _sizeҲ���resize
	//����capacity��ʱ������� ���������ɶ�Ӧ����ʱ �Ҷ��λ����c����ʼ�� reserve�ǲ���ʼ����
		if (n <= _size) {
			_str[n] = '\0';
			_size = n;
		}
		else {
			if (n > _capacity) {//�����˳�ʼ��
				reserve(n);
			}

			while (_size < n) {
				_str[_size++] = c;
			}

			_str[_size] = '\0';

		}
	}

	void string::reserve(size_t n) {//string���reserve ��С�ڵ���capacity˵�������� 
		                            //����capacity ��ȥ����
		if (n > _capacity) {
			//C++�ﲻ��C��malloc ��realloc ����û��renew �ֶ���

			char* tmp = new char[n + 1];//new���˻����쳣 �࿪һ����'\0'
			//��n����������n�� '\0'ֻ�Ǳ�ʶλ����string��(ĩβ��)
			_capacity = n;
			strcpy(tmp, _str);
			delete[]_str;

			_str = tmp;
		}
		//��ʵʵ���� ��nֻ��һ���߶ȣ��������ʼ��capacityΪ��׼2����������������nΪֹ
		//���￼�ǵ��ɶ���  ��n���پ��������
	}

	// access
	char& string::operator[](size_t index) {
		assert(index < _size && index >= 0);

		return _str[index];
	}

	const char& string::operator[](size_t index)const {//��������� const����this
		assert(index < _size && index >= 0);

		return _str[index];
	}

	//relational operators
	bool string::operator<(const string& s)const {
		int i = 0;
		for (i = 0; i < _size && i < s._size; i++) {
			if (_str[i] > s._str[i])
				return false;
			if (_str[i] < s._str[i])
				return true;
		}

		if (i == _size && i < s._size) {//���ַ���������
			return true;
		}
		else
			return false;//�������
	}

	bool string::operator<=(const string& s)const {
		return *this < s || *this == s;
	}

	bool string::operator>(const string& s)const {
		return !(*this <= s);
	}

	bool string::operator>=(const string& s)const {
		return !(*this < s);
	}

	bool string::operator==(const string& s)const {
		if (_size == s._size) {
			for (int i = 0; i < _size; i++) {
				if (_str[i] != s._str[i])
					return false;
			}//��ѭ��˵�����������

			return true;
		}
		else
			return false;

	}

	bool string::operator!=(const string& s)const {
		return !(*this == s);
	}


	// ����c��string�е�һ�γ��ֵ�λ��
	size_t string::find(char c, size_t pos) const {//��������ȱʡ���� Ĭ�ϴ�0��ʼ��
		assert(pos < _size && pos >= 0);

		for (int i = 0; i < _size; i++) {
			if (_str[i] == c)
				return i;
		}

		return npos;
	}

	// �����Ӵ�s��string�е�һ�γ��ֵ�λ��
	size_t string::find(const char* s, size_t pos)const {
		//���ִ� �÷�װ�õĺ��� �Լ�Ҳ����ʵ�� ����ʹ��C�����strstr
		//strstr�ײ���BF(�������)  ʵ���б��������ʵû���� ������KMP�������ۺ��������㷨�õĲ���
		//������Ҳ��һ���ܵ��� BM�㷨���Ӵ� ������˵��� ����ܸ����Ѷ�

		//strstr����char*

		assert(pos < _size && pos >= 0);

		char* tmp = strstr(_str,s);//����Ҫ�����±� ָ��������м�Ԫ�ظ���ok?
		if (tmp == nullptr)
			return npos;

		return tmp - _str;
	}

	// ��posλ���ϲ����ַ�c/�ַ���str�������ظ��ַ���λ��
	string& string::insert(size_t pos, char c) {
		assert(pos <= _size && pos >= 0);//����_size��ʱ�� ����β��

		if (_size + 1 > _capacity)
			reserve(_size + 1);//��ȷ���ܹ� ����

		//����
		size_t end = _size + 1;//��������������Ϊ�� �ܹ��õ�posΪ���ʱ�� ѭ������ֹ����
		//������-1 >= 0���˳� ��Ϊ�����˲��� size_t��-1���ö��� ������������ѭ���������0 > 0���˳� 
		while (end > pos) {
			_str[end] = _str[end - 1];
			--end;
		}

		//����
		_str[pos] = c;
		_size++;

		return *this;//���return��ȫ�ǰ��� ��׼��Ľӿ����� һ��ʵ�����岻�� ֻ��һ������
	}

	string& string::insert(size_t pos, const char* str) {
		assert(pos <= _size && pos >= 0);//����_size��ʱ�� ����β��

		size_t len = strlen(str);
		size_t end = _size;//ָ��'\0'

		size_t move = end - pos + 1;//���Ҫ�ƶ��ַ��ĸ���
		//move����ͳһ����ƶ�len��λ��
		for (int i = 0; i < move; i++) {
			_str[end + len] = _str[end];
			--end;
		}

		//����
		strncpy(_str + pos, str, len);
		//��ȻҲ�����ֶ�ѭ������

		return *this;
	}



	// ɾ��posλ���ϵ�Ԫ��
	string& string::erase(size_t pos, size_t len) {//Ĭ��pos��ɾ��
		assert(pos < _size && pos >= 0);

		if (len == npos || len + pos >= _size) {//������npos��pos��Ҫȫ������
			//�������û��npos == len�������ж� len == npos npos + len�ͻ�����ƻ�ȥ ���Сֵ
			_str[pos] = '\0';
			_size = pos;
		}
		else {//pos���Ԫ��ͬ����ǰŲ��len��λ��
			//�������memmove(�ڴ��ص���Ų��) Ҳ����strcpy Ҳ�����ֶ�Ų
			strcpy(_str + pos, _str + pos + len);
			_size -= len;
		}

		return *this;
	}

	//���ض�Ӧ�����Ӵ�
	string string::substr(size_t pos, size_t len) {//Ĭ�ϳ��� ��pos�������
		string sub;

		if (len == npos || pos + len >= _size) {
			for (int i = pos; i < _size; i++) {
				sub += _str[i];
			}
			//sub.reserve(_size - pos);
			//strcpy(sub._str,_str+pos);
			//sub._size = _size - pos;
			return sub;
		}

		sub.reserve(len);
		strncpy(sub._str, _str + pos,len);
		sub._size = len;

		return sub;
	}


	ostream& operator<<(ostream& os, const string& s) {
		//���ǵ�����string ������C����ַ��� �����ַ�������ַ��ǻ���'\0'��
		//���� cout<<s.c_str()<<endl;��Ϊ����ָ�� �ǵ�'\0'���� ����һЩcstring��ĺ���
		//�����ڸ�C++��stringʱҪ���ǵ��м���'\0'��������

		for (int i = 0; i < s.size(); i++) {
			os << s[i];
		}

		return os;
	}

	istream& operator>>(istream& is, string& s) {
		//������ ��s�Ѿ������ݵ�ʱ�� Ҫ�Ƚ�s�����ȥ����
		//����������� ��һ���ַ�һ���ַ��Ĳ���  ��Ϊ��Ҫʵ��
		//���� 123 456�����123 cin��scanf�����ᴦ�������Ĳ��ɼ��ַ� ����cin����ɾ��
		//cin cin.get cin.getline()���Ѿ�������ϸ�ķ����� ����Ͳ�׸����
		//cin.get()�ǻ��ȡ�����ַ���

		if (!s.empty()) {
			s.clear();
		}

		char tmp;
		tmp = is.get();

		while (tmp != ' ' && tmp != '\n') {//������Ϊtmp != '\n'����ɵ�������123 456
			                               //���123 456--->cin.geiline()�Ĺ���
			s += tmp;//��������� ������'\0'

			tmp = is.get();
		}

		return is;
	}

		//���￼�ǵ���������ַ��ر��ʱ +=ҪƵ�����ٿռ� ��Ϊ�Ƕ����� ��ʵҲûʲô
		//ֻ���������һ����Ը��ŵķ��� ��һ�������� ��������ַ��Ƚ��뻺������
		//������������+= 
		/*char buffer[128];

		int i = 0;
		while (tmp != ' ' && tmp != '\n') {
			
			if (i == 127) {//����������
				buffer[i] = '\0';//���Ǹ��ַ��� ����Ҫ��'\0' ������+=���滹Ҫ����strlen

				s += buffer;

				i = 0;
			}

			buffer[i] = tmp;
			i++;

			tmp = is.get();
		}

		if (i != 0) {
			buffer[i] = '\0';
			s += buffer;
		}

		return is;*/
	
}
