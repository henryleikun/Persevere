#define _CRT_SECURE_NO_WARNINGS 1

#include "string.h"
//这里说个问题  const size_t string::npos = -1; 这一句放到头文件里 这里就会重定义
//因为命名空间的开放性 你这里包含了头文件 编译器会将展开后的头文件里的同名命名空间 和这个命名空间
//合并 这样 头文件里的静态成员定义一次 这里合并后有定义一次 但如果在这里定义 不放到头文件里 那就只
// 定义一次  


namespace Henry {//命名空间的开放性
	const size_t string::npos = -1;

	string::string(const char* str) {//默认字符串构造
		
		_capacity = strlen(str) == 0 ? 4 : strlen(str);
		_str = new char[_capacity + 1];
		_size = strlen(str);//默认_capcity = 4 _size = 0 

		strcpy(_str, str);
	}

	string::string(const string& s):_capacity(s._capacity),_size(s._size) {//深拷贝
		_str = new char[_capacity + 1];
		strcpy(_str, s._str);
	}

	string& string::operator=(const string& s) {

		if (this == &s) {
			return *this;
		}//防止自赋值

		delete[]_str;//释放之前的空间

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


	// iterator 这里的迭代器处理按指针来处理了 这个对于连续内存是可行的 后续在list等容器的实现
	//会搞真正的迭代器，这里就先利用简单的迭代器
	string::iterator string::begin() {
		return _str;
	}

	string::iterator string::end() {
		return _str + _size;//左闭右开 返回最后一个的下一位即指向'\0'的指针
	}

	// modify
	void string::push_back(char c) {
		if (_capacity == _size) {
			reserve(_capacity * 2);//二倍扩
		}

		_str[_size++] = c;
		_str[_size] = '\0';//把原来的'\0'覆盖了别忘了在搞出来
	}

	string& string::operator+=(char c) {
		if (_size == _capacity)
			reserve(_capacity * 2);

		_str[_size++] = c;
		_str[_size] = '\0';

		//insert(_size, c);//重用完成
		
		return *this;
	}

	void string::append(const char* str) {//附加一段字符串
		/*for (int i = 0; i < strlen(str); i++) {
			*this += str[i];
		}
		_size += strlen(str)*/

		size_t sz = strlen(str);

		if (_size + sz > _capacity)
			reserve(_size + sz);//还是二倍扩_capacity的话你不能保证扩完一定大于_size+sz

		strcpy(_str + _size, str);//这个比上面好点 上面那个this的要一直调用函数
		                      //调函数就要创栈帧 懂得都懂
		//strcat(_str,str)

		_size += sz;

		//insert(_size, str);//重用！
	}

	string& string::operator+=(const char* str) {//这个和append其实一样
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

	//标准库 swap(string& a,string& b);
	//a.swap(b) 下面好 上面太多拷贝构造了 每次深拷贝相比开销太大 
	void string::swap(string& s) {
		std::swap(_str, s._str);
		std::swap(_size, s._size);
		std::swap(_capacity, s._capacity);//内置类型 swap还是很快的
	}

	const char* string::c_str()const {//将string转换为C风格的字符串
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

	void string::resize(size_t n, char c) {//c默认是'\0'
    //resize跟reserve有点像 但还是很不一样的 在我用string的经验上
	//resize的数小于_capacity 大于_size的时候就仅是改变_size 
	//小于_size的时候 不动_capacity让字符串的有效位变为resize即 _size也变成resize
	//大于capacity的时候就扩容 扩到能容纳对应的数时 且多的位置用c来初始化 reserve是不初始化的
		if (n <= _size) {
			_str[n] = '\0';
			_size = n;
		}
		else {
			if (n > _capacity) {//别忘了初始化
				reserve(n);
			}

			while (_size < n) {
				_str[_size++] = c;
			}

			_str[_size] = '\0';

		}
	}

	void string::reserve(size_t n) {//string里的reserve 是小于等于capacity说明都不干 
		                            //大于capacity 才去扩容
		if (n > _capacity) {
			//C++里不像C的malloc 有realloc 这里没有renew 手动扩

			char* tmp = new char[n + 1];//new错了会抛异常 多开一个存'\0'
			//开n个是让你用n个 '\0'只是标识位不算string里(末尾的)
			_capacity = n;
			strcpy(tmp, _str);
			delete[]_str;

			_str = tmp;
		}
		//其实实际上 是n只是一个尺度，还是以最开始的capacity为基准2倍扩，扩到能容纳n为止
		//这里考虑到可读性  就n多少就申请多少
	}

	// access
	char& string::operator[](size_t index) {
		assert(index < _size && index >= 0);

		return _str[index];
	}

	const char& string::operator[](size_t index)const {//上面的重载 const修饰this
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

		if (i == _size && i < s._size) {//本字符串先走完
			return true;
		}
		else
			return false;//包括相等
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
			}//出循环说明两个必相等

			return true;
		}
		else
			return false;

	}

	bool string::operator!=(const string& s)const {
		return !(*this == s);
	}


	// 返回c在string中第一次出现的位置
	size_t string::find(char c, size_t pos) const {//声明里有缺省参数 默认从0开始找
		assert(pos < _size && pos >= 0);

		for (int i = 0; i < _size; i++) {
			if (_str[i] == c)
				return i;
		}

		return npos;
	}

	// 返回子串s在string中第一次出现的位置
	size_t string::find(const char* s, size_t pos)const {
		//找字串 用封装好的函数 自己也可以实现 这里使用C里面的strstr
		//strstr底层是BF(暴力求解)  实际中暴力求解其实没问题 反倒是KMP这种理论很完美的算法用的不多
		//但这里也有一个很吊的 BM算法找子串 后续再说这个 这个很复杂难懂

		//strstr返回char*

		assert(pos < _size && pos >= 0);

		char* tmp = strstr(_str,s);//但我要返回下标 指针相减的中间元素个数ok?
		if (tmp == nullptr)
			return npos;

		return tmp - _str;
	}

	// 在pos位置上插入字符c/字符串str，并返回该字符的位置
	string& string::insert(size_t pos, char c) {
		assert(pos <= _size && pos >= 0);//等于_size的时候 就是尾插

		if (_size + 1 > _capacity)
			reserve(_size + 1);//先确保能够 存下

		//后移
		size_t end = _size + 1;//这里这样处理是为了 能够让当pos为零的时候 循环的终止条件
		//不会有-1 >= 0而退出 因为这样退不出 size_t的-1懂得都懂 这样做就能让循环条件变成0 > 0而退出 
		while (end > pos) {
			_str[end] = _str[end - 1];
			--end;
		}

		//插入
		_str[pos] = c;
		_size++;

		return *this;//这个return完全是按照 标准库的接口来的 一般实际意义不大 只是一个接收
	}

	string& string::insert(size_t pos, const char* str) {
		assert(pos <= _size && pos >= 0);//等于_size的时候 就是尾插

		size_t len = strlen(str);
		size_t end = _size;//指向'\0'

		size_t move = end - pos + 1;//求得要移动字符的个数
		//move个数统一向后移动len个位置
		for (int i = 0; i < move; i++) {
			_str[end + len] = _str[end];
			--end;
		}

		//插入
		strncpy(_str + pos, str, len);
		//当然也可以手动循环插入

		return *this;
	}



	// 删除pos位置上的元素
	string& string::erase(size_t pos, size_t len) {//默认pos后删完
		assert(pos < _size && pos >= 0);

		if (len == npos || len + pos >= _size) {//处理了npos和pos后要全搞的情况
			//上述如果没有npos == len的条件判断 len == npos npos + len就会溢出绕回去 变成小值
			_str[pos] = '\0';
			_size = pos;
		}
		else {//pos后的元素同意向前挪动len个位置
			//这里可以memmove(内存重叠的挪动) 也可以strcpy 也可以手动挪
			strcpy(_str + pos, _str + pos + len);
			_size -= len;
		}

		return *this;
	}

	//返回对应长度子串
	string string::substr(size_t pos, size_t len) {//默认长度 是pos后边所有
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
		//考虑到这是string 而不是C风格字符串 这种字符串里的字符是会有'\0'的
		//不能 cout<<s.c_str()<<endl;因为对于指针 是到'\0'结束 包括一些cstring里的函数
		//所以在搞C++的string时要考虑到中间有'\0'的适配性

		for (int i = 0; i < s.size(); i++) {
			os << s[i];
		}

		return os;
	}

	istream& operator>>(istream& is, string& s) {
		//流插入 当s已经有数据的时候 要先将s清空再去插入
		//而且这个插入 是一个字符一个字符的插入  因为我要实现
		//输入 123 456最后是123 cin和scanf都不会处理缓冲区的不可见字符 而且cin还会删掉
		//cin cin.get cin.getline()我已经做过详细的分析了 这里就不赘述了
		//cin.get()是会读取这种字符的

		if (!s.empty()) {
			s.clear();
		}

		char tmp;
		tmp = is.get();

		while (tmp != ' ' && tmp != '\n') {//条件改为tmp != '\n'就完成的是输入123 456
			                               //输出123 456--->cin.geiline()的功能
			s += tmp;//里面会扩容 并处理'\0'

			tmp = is.get();
		}

		return is;
	}

		//这里考虑到当输入的字符特别多时 +=要频繁开辟空间 因为是二倍扩 其实也没什么
		//只是这里给出一个相对更优的方法 搞一个缓冲区 让输入的字符先进入缓冲区存
		//缓冲区满了在+= 
		/*char buffer[128];

		int i = 0;
		while (tmp != ' ' && tmp != '\n') {
			
			if (i == 127) {//缓冲区满了
				buffer[i] = '\0';//这是个字符串 必须要有'\0' 后续的+=里面还要对他strlen

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
