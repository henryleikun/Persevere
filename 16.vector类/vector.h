#pragma once
#include <iostream>
#include <cassert>

using namespace std;

//根据SGI(g++)使用的STL版本 去实现这个vector
//这里的实现不像上一个string那个本身就是模板的实例化 这里要使用模板定义
//模板的实现和声明要放在一个文件里

//注意好 insert和erase实现的时候迭代器失效的问题
//野指针 不是原来元素位置而是新元素位置 返回最新位置

//涉及到深拷贝 就不要去使用memcpy了 memcpy本质就是一个浅拷贝

//关于函数形参 返回值等 是用vector<T> 还是vector 这里在类作用域内 哪个都行
//但类外 必须 是vector<T>而且还要带上特定的 模板类声明 
//这里给出建议 都用vector<T>就行 可读性也强
namespace Henry {

	template<typename T>
	class vector {
	private:
		//标准vector利用三个指针来控制顺序表
		T* _start;
		T* _finish;
		T* _end;
	public:
		typedef T* iterator;
		typedef const T* const_iterator;


		vector():_start(nullptr), _finish(nullptr), _end(nullptr) {

		}

		vector(int n, const T& val) {
			_start = new T[n];
			_finish = _end = _start + n;

			for (int i = 0; i < n; i++) {
				_start[i] = val;
			}
		}

		/*vector(const vector& rhs) {
			_start = new T[rhs.capacity()];
			_finish = _start + rhs.size();
			_end = _start + rhs.capacity();

			for (int i = 0; i < rhs.size(); i++) {
				_start[i] = rhs._start[i];
			}
		}

		vector& operator=(const vector& rhs) {
			delete[] _start;
			_start = new T[rhs.capacity()];
			_finish = _start + rhs.size();
			_end = _start + rhs.capacity();
			
			for (int i = 0; i < rhs.size(); i++) {
				_start[i] = rhs._start[i];
			}

			return *this;
		}*/


		//上面两种 是老的写法 这里给出现代写法 “借刀杀人”
		//方便

		void swap(vector<T>& rhs) {
			//对里面的内置类型 进行标准库的调用
			std::swap(_start, rhs._start);
			std::swap(_finish, rhs._finish);
			std::swap(_end, rhs._end);
		}

		vector(const vector<T>& rhs) {
			vector<T> v(rhs._start, rhs._finish);//利用这个去拷贝rhs 在借他杀人
			swap(v);//通过临时对象v间接实现了 拷贝
			//v调用自己的析构函数 来释放 那块临时空间
		}

		vector<T>& operator=(const vector<T>& rhs) {
			vector<T> v(rhs._start, rhs._finish);
			//这个就算是自己赋值自己也无妨
			swap(v);
			return *this;
		}

		//还有一个迭代器区间构造函数
	    // [first, last)  而这个构造函数是一个模板函数 根据传入的形参来推断对应类型
		//是指针 还是迭代器 还是下标都可以
		//注意这里他也是个构造函数 意味着 他要对成员变量进行初始化
		//注意这里是 这个编译器 自动帮那几个成员变量初始化了 实际上
		//在前面也说过 默认构造函数 对内置类型是不做处理的 这里是编译器帮你处理了
		//严谨起见 还是先初始化列表以下。
		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
		:_start(nullptr), _finish(nullptr), _end(nullptr)
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}


		~vector() {
			delete[] _start;
			_start = _finish = _end = nullptr;
		}

		iterator begin() {
			return _start;
		}

		iterator end() {
			return _finish;
		}

		const_iterator begin()const {
			return _start;
		}

		const_iterator end()const {
			return _finish;
		}


		size_t size()const {
			return _finish - _start;
		}

		size_t capacity()const {
			return _end - _start;
		}

		bool empty()const {
			return size() == 0;
		}

		T& operator[](size_t pos){
			assert(pos >= 0);
			assert(_start + pos < _finish);

			return _start[pos];
		}

		const T& operator[](size_t pos) const {
			assert(pos >= 0);
			assert(_start + pos < _finish);

			return _start[pos];
		}


		//resize和reserve和string的处理一样
		void reserve(int n) {

			if (n > (_end - _start)) {
				T* temp = new T[n];
				T* _free = _start;

				size_t sz = size();

				_start = temp;
				
				for (int i = 0; i < sz; i++) {
					temp[i] = _free[i];
				}


				_finish = _start + sz;
				_end = _start + n;

				delete[] _free;
			}
		}

		//为了迎合模板 内置类型 也可以有默认构造
		void resize(int n,const T& val = T()) {//val初始化的元素
			if (n < size()) {
				_finish = _start + n;
				return;
			}
			else{

				if (n > capacity()) {
					reserve(n);
				}
			
				T* cur = _finish;
				while (cur != _start + n) {
					*cur = val;
					cur++;
				}
			}
		}

		void push_back(const T& val) {
			if (_finish == _end) {//满了(空了) 2倍扩
				int newcapacity = capacity() == 0 ? 4 : 2 * capacity();
				reserve(newcapacity);
				//reserve里面处理了指针的关系
			}

			*_finish = val;
			_finish++;
		}

		void pop_back() {
			assert(!empty());

			_finish--;
		}

	    iterator insert(iterator pos, const T& val) {
			assert(pos <= _finish);
			assert(pos - _start >= 0);

			if (_finish == _end) {//满了 2倍扩
				int newcapacity = capacity() == 0 ? 4 : 2 * capacity();
				size_t sz = pos - _start;

				reserve(newcapacity);
				//reserve里面处理了指针的关系
				//这里注意是异地扩 pos还是指向原来的位置 这是要更新pos 让pos指向新空间相对于
				//_start的位置处  这是一种迭代器失效（野指针）

				pos = _start + sz;
			}

			//右移
			T* move = _finish - 1;

			while (move - pos >= 0) {
				*(move + 1) = *move;
				--move;
			}
			_finish++;

			*pos = val;
			return pos;//返回指向插入新元素位置的pos
		}

		iterator erase(iterator pos) { //vs(不同的STL实现) erase是强制检查 使用完的pos禁止使用
			       //g++没有强制检查 但也有报错情况 这里强制检查最好 
				   //但vs的强制检查是建立在迭代器是自定义类型 我这里是原生指针 知道就行
				   //不能强制检查 为什么强制检查最好 当erase的是最后一个元素 你还想在外边
				   // 访问这块空间 这就是非法访问了 所以这里就记住erase之后的迭代器不能再使用了
		    assert(!empty());
			assert(pos < _finish);

			T* move = pos;

			while (move + 1 != _finish) {
				*move = *(move + 1);
				move++;
 			}
			
			--_finish;

			return pos;
			//返回删除元素的下一个元素的位置 这在vs的标准里是允许的 参考删除序列的偶数 有偶数
			//连续出现的情况 删除后要更新迭代器的值 反正一句话 erase后的迭代器 就是失效的
		}



	};
}