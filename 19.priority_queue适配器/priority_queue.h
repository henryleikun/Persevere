#pragma once
//优先级队列 其实就是堆，高优先级低优先级对应大堆小堆，且优先级队列也是适配器
//这里要涉及到STL六大特性里的另一大特性：仿函数 仿函数是针对于C语言中复杂的函数指针
//在C语言的qsort函数里，
//void qsort (void* base, size_t num, size_t size,int (*compar)(const void*, const void*));
//第三个参数是一个函数指针指向一个能够比大小函数，在qsort里再回调函数从而实现“自定义泛型”函数的复用
//但函数指针太复杂了 有时候都要看个半天 C++的函数对象(仿函数)对这个问题做了很好的处理 
//再类中重载()运算符 实现一个表面上的函数 实际上是调用成员函数 而我需要的只是一个调用这个函数的对象
//再优先级队列里，我需要一个仿函数来确定是高还是低优先级
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;


//本质是堆 堆的接口 pop push top empty size
//优先级队列作为适配器其容器除了满足接口要求外 还要支持下标访问
//下面以一个小堆为例
namespace Henry {
	template<class T>//构造仿函数对象 结构体更适合
	struct less {
		bool operator()(const T& x, const T& y) {
			return x < y;//如果T是自定义类型 确保其重载了对应的比较运算符
		}
	};

	template<class T>
	struct greater {
		bool operator()(const T& x, const T& y) {
			return x > y;
		}
	};

	//默认底层使用vector 仿函数是小的 但其实蛮奇怪 这里默认是less但其实实现的是大堆(库里是这样的)
	//但都还好 如果你想让less对应小堆 其实只要改变比较操作数的顺序就行
	//我这里按库里面来
	//其实这个模板参数分布很奇怪 应该compare在中间 因为 Container一般都不会变1反而Compare会经常变
	template<class T, class Container = vector<T>, class Compare = less<T>>
	class priority_queue {
	private:
		Container con;
	public:
		void adjust_up(int child) {//向上调整(push时会用)
			//assert(child >= 0 && child < con.size());

			int parent = (child - 1) / 2;

			while (child > 0) {

				//if (con[parent] > con[child]) {//这是小堆
				if (Compare()(con[parent], con[child])) {//匿名对象 因为默认是less故应是大堆
					swap(con[parent], con[child]);

					child = parent;
					parent = (child - 1) / 2;
				}
				else {
					break;
				}
			}
		}

		void adjust_down(int parent) {//向下调整(pop时会用，向下调整建堆可能也用)
			//assert(parent >= 0 && parent < con.size());//仅仅只是为了严谨
            //当元素只有一个的时候且执行pop会有问题 这个其实也没必要。。。

			int child = parent * 2 + 1;//默认使用左孩子 小堆 两个孩子里最小的比父大

			while (child < con.size()) {//这里con.size()的返回值是size_t

				                                  //con[child + 1] < con[child]小堆 
				if (child + 1 < con.size() - 1 && Compare()(con[child],con[child + 1])) {
					++child;
				}//找出两个孩子里Compare的

				//if (con[child] < con[parent]) {
				if (Compare()(con[parent],con[child])) {
					swap(con[child], con[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else {
					break;
				}
			}
		}

		void pop() {
			assert(!empty());

			swap(con[0], con[size() - 1]);
			con.pop_back();

			adjust_down(0);
		}

		void push(const T& val) {
			con.push_back(val);
			adjust_up(con.size() - 1);
		}

		T top()const {
			return con[0];
		}

		bool empty()const {
			return con.empty();
			//return con.size() == 0;
		}

		size_t size()const {
			return con.size();
		}
	};
}