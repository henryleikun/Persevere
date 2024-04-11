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

		vector(const vector& rhs) {
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
		}

		//还有一个迭代器区间构造函数
	    // [first, last)  而这个构造函数是一个模板函数 根据传入的形参来推断对应类型
		//是指针 还是迭代器 还是下标都可以
		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
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
			if (_finish == _end) {//满了 2倍扩
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