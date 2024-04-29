#pragma once
#include <iostream>
#include <cassert>
using namespace std;
//实现list(带头双向循环链表) 总体是跟数据结构实现差不多的 但这个
//要好好实现迭代器  熟悉模板

//库里面链表还实现了size resize 额 这里就不实现了 没啥用
//这里就只是实现一些常用的接口

//C++ struct也可以看作是类

//链表的迭代器 和vector和string的有本质的区别 因为后两个 是顺序存储
//普通迭代器可以使用原生指针间接实现 但对于链式存储的list来说 单纯的原生指针 是
//完成不了对应的任务的 比如iterator++ 后的指向 不一定是下一个结点 
//这里必须要完成 对指针的封装 利用struct(class)封装它  封装后还是按指针来使用
namespace Henry {
	template<class T>
	struct ListNode {
		T data;
		ListNode<T>* prev;
		ListNode<T>* next;

		ListNode(const T& rhs = T()) :data(rhs), prev(nullptr), next(nullptr) {

		}//提供构造函数
	};

	//封装结点指针pnode成为迭代器对象 构造函数确定pnode指向哪个结点 
	//迭代器要模仿指针的行为 除了解引用还有++之外 还有一个比较特殊的: ->
	//这种情况出现在迭代器指向的结点的data是一个自定义类型
	template<class T,class Ref,class Ptr>
	struct _list_iterator {
		typedef ListNode<T> Node;
		typedef _list_iterator<T,Ref,Ptr> self;

		Node* pnode;

		//幽默模板_list_iterator<T>(Node* node = nullptr):pnode(node)
		//加<T>说的是形参和返回值,类型 跟你函数名有什么关系 疯了？
		_list_iterator(Node* node = nullptr) :pnode(node) {

		}//it(list.begin())是拷贝构造 默认即可赋值运算符同理
		//这里不给出析构函数 我只是借用以下这个结点指针对节点的数据进行操作
		//肯定不会释放两次 结点指针 你只有使用权 没有归属权那是属于链表对象的

		Ref operator *() {
			return pnode->data;
		}

		self& operator++() {//前缀
			//return pnode->next; 这个不对啊 这返回的要是一个迭代器 你返回结点指针
			//结点指针隐式类型转换成临时的迭代器对象 况且这还是个引用
			pnode = pnode->next;

			return *this;
		}

		self operator++(int) {//后缀
			self ret(pnode);
			pnode = pnode->next;

			return ret;
		}

		//双向迭代器 要实现--
		self& operator--() {//前缀
			pnode = pnode->prev;
			return *this;
		}

		self operator--(int) {//后缀
			self ret(pnode);
			pnode = pnode->prev;

			return ret;
		}

		Ptr operator->() {//试想 struct Node* ps, ps->是Node的成员
			return &pnode->data;//当data是自定义类型时 
		}
        //这里考虑到 会有const链表调用const迭代器 const迭代器调用->() 所以这里也要求
		//const 迭代器 是不能改变 ->的指向的 即返回的应该是const T* 同T& 这里在加一个模板参数

		bool operator!=(const self& rhs) {
			return pnode != rhs.pnode;
		}

		bool operator==(const self& rhs) {
			return pnode == rhs.pnode;
		}
	};


	//像下面这样去实现 const T* p的迭代器 指向的内容不变 但迭代器可变
	//这里只需要在上面的基础上 将解引用的返回值搞一个const就行 其他都是针对迭代器的
	//只有这个是针对迭代器指向的结点的
	//在list类中 typedef _list_const_iterator<T> const_iterator
	//思考 实现一个const迭代器 需要使用这么重复度高的代码吗？
    //不需要 这样太冗余了 两个类只有解引用的返回值有差异 T&和const T&
    //这里有一个非常吊 非常nb的设计 就是通过增加一个迭代器模板参数Ref来标识
	//不同的返回值 普通迭代器：<T,T&> 只读迭代器:<T,const T&>
	//Ref接收第二个模板参数 并作为*的返回值 ok
	//template<class T>
	//struct _list_const_iterator {
	//	typedef ListNode<T> Node;
	//	typedef _list_const_iterator<T> self;

	//	Node* pnode;

	//	_list_const_iterator(Node* node = nullptr) :pnode(node) {

	//	}

	//	const T& operator *() {
	//		return pnode->data;
	//	}

	//	self& operator++() {//前缀
	//		pnode = pnode->next;

	//		return *this;
	//	}

	//	self operator++(int) {//后缀
	//		self ret(pnode);
	//		pnode = pnode->next;

	//		return ret;
	//	}

	//	self& operator--() {//前缀
	//		pnode = pnode->prev;
	//		return *this;
	//	}

	//	self operator--(int) {//后缀
	//		self ret(pnode);
	//		pnode = pnode->prev;

	//		return ret;
	//	}

	//	bool operator!=(const self& rhs) {
	//		return pnode != rhs.pnode;
	//	}

	//	bool operator==(const self& rhs) {
	//		return pnode == rhs.pnode;
	//	}
	//};

	//实现反向迭代器 反向迭代器在刚开始的认知里就是迭代器反过来 让反向迭代器的++就是迭代器的--
	//确实如此，那么会有rbegin和rend函数 这两个管理的范围是什么样？跟迭代器(begin指向第一个end指向最后一个的
	// 下一个)反过来吗(rbegin指向最后一个，而rend指向第一个的前一个)？库里面不是这样的，他是让这个范围刚好对称
	//过来 也就是rbegin指向最后一个的下一个 rend指向第一个 是刚好对称的

	//同时 迭代器是对结点指针Node*的封装 反向迭代器也不例外 他也要实现++ --等操作 也要进行封装 那问题来了
	//需=需要再完全写一个和迭代器一样的struct吗 因为大部分功能的逻辑其实适合迭代器对象相反的，能不能复用
	//一下呢？    答案是能  可以把反向迭代器当作一个适配器 通过别的已经封装好的迭代器去实现自己的功能
	// 熟练运用好迭代器的接口就行
	//上面也说了 反向的++是正向的--且反向的rbegin是指向最后一个的下一个所以在解引用的时候应该先移动再解引用
	//所以有如下：
    template<class Iterator,class Ref,class Ptr>
	struct ReverseIterator {
		typedef ReverseIterator<Iterator,Ref,Ptr> self;

		Iterator it;

		ReverseIterator(Iterator _it):it(_it) {

		}

		Ref operator*() {//因为对it的解引用再迭代器里就是返回Ref 这里返回的类型是一样的
			             //下面对->的重载同理
			Iterator cur = it;
			return *--cur;
		}

		self& operator++() {//前置
			//return --it;  self是反向迭代器 it是正向迭代器 你在干什么？
			--it;

			return *this;
		}

		self operator++(int) {//后置
			self cur = *this;
			--it;
		
			return cur;
		}

		self& operator--() {//前置
			//return ++it;
			++it;

			return *this;
		}

		self operator--(int) {//后置
			self cur = *this;
			++it;

			return cur;
		}

		//你的反向迭代器的解引用和->永远是处理it指向的前一个的内容 因为你获取迭代器的方式只有
		//rbegin() rend() 就比如如果你解引用rend的话 你想要的就是他指的而不是他的前一个
		//但有没有想过 你在用迭代器的时候 你不会直接去解引用end() 因为你知道他是指向最后一个的下一个
		//解引用没用 那你会让他--再去解引用，这里也是一样啊 你表面上看起来的反向迭代器是rbegin()指向最后一个
		//rend()指向第一个的前一个 所以你也不能直接解引用 rend 你要让他--，其实这时候rend()指向的是你想要的
		//下一个但是 你解引用的实现就是刚好拿到你想要的那个 所以你清楚他们的实现 你也要清楚 他们的接口(表面
		// 的呈现)样子  
		Ptr operator->() {
			Iterator cur = it;
			--cur;

			return cur.operator->();
		}

		bool operator==(const self& rhs) {
			return it == rhs.it;
		}

		bool operator!=(const self& rhs) {
			return it != rhs.it;
		}
	};


	//记住是带头双向循环链表
	template<class T>
	class list {
		typedef ListNode<T> Node;//链表节点(模板)类型由 类模板参数决定
	public:
		typedef _list_iterator<T,T&,T*> iterator;//这是public 外界要用 但结点就要是private
		                                  //其类型也是又类模板参数决定
		typedef _list_iterator<T, const T&,const T*> const_iterator;
		typedef ReverseIterator<iterator, T&, T*> reverse_iterator;
		typedef ReverseIterator<iterator, const T&, const T*> const_reverse_iterator;
 	private:
		Node* _head;
	public:
		void empty_initialize() {
			_head = new Node;
			_head->data = -1;
			_head->next = _head;
			_head->prev = _head;
		}//一个小小的初始化 默认构造函数内置类型不做处理 vs处理了 但正常是不处理的
		//构造函数调成员函数 来完成这个创建头节点的初始化

		list() {
			empty_initialize();
		}

		iterator begin() {
			//return _head->next; 这种写法可读性不强 虽然结点指针能隐式转换成迭代器对象
			return iterator(_head->next);
			//拷贝就拷贝呗 反正是都是操控的迭代器指向的位置 而且 这个迭代器的默认拷贝函数完全够用
		}

		iterator end() {
			return iterator(_head);
		}

	    //const iterator begin()const {
		//}

		//const iterator end()const {
		//}
		
		// 当是const 链表取得迭代器时 在vector里(指针实现)就是直接搞个const const修饰this
		// 指针你不能改变vector里的_start等指针指向的值 但只是后缀的const修饰this指针
		// 是保证不改变指针的 但返回的也是拷贝 这都无所谓 所以要保证指向的值不变 vector
		// 返回的是 const_iterator(const T*)
		// 但是上述const保证_head不被改变 让const对象能调用 但不能保证 迭代器指向的结点不会
		// 被改变 你要类比vector的返回 我上面写的const iterator完全没道理 他这是让迭代器不能
		// 改变了 就相当于 int *const p了 那还怎么遍历解引用呢
		// 所以基于 vector这里要返回一个const_iterator 主要是怎么实现这个只读迭代器 而且这个迭代器
		// 是一个对象 对象里面有pnode我要做的就是 const pnode 不能改变pnode指向的值 但可以改变
		// pnode的指向(即支持 遍历 解引用等) 

		const_iterator begin()const {
			return const_iterator(_head->prev);
		}

		const_iterator end()const {
			return const_iterator(_head);
		}


		//反向迭代器
		reverse_iterator rbegin() {
			return reverse_iterator(end());
		}

		reverse_iterator rend() {
			return reverse_iterator(begin());
		}

		const_reverse_iterator rbegin()const {
			return const_reverse_iterator(end());
		}

		const_reverse_iterator rend()const {
			return const_reverse_iterator(begin());
		}
	    
		//模板构造函数
		template<class Inputiterator>
		list(Inputiterator first,Inputiterator last) {//接收迭代器 指针
			empty_initialize();//没有这个初始化 _head会是随机值(不考虑vs额外的处理)
            
			while (first != last) {
				push_back(*first);
				first++;
			}
		}

		void swap(list<T>& rhs) {
			std::swap(_head, rhs._head);
		}

		//这里的拷贝构造和赋值运算符重载现代式写法ok 就不手动深拷贝了
		list(const list<T>& rhs) {
			//empty_initialize();
			/*list ls(rhs.begin(),rhs.end());
			swap(ls);*/

			//如果是一个const对象调用 拷贝构造 这里面的empty_这个函数不是const也能调用
			//可以 const对象在声明定义的时候不认为是只读的要不然怎么赋值
			empty_initialize();
			for (auto e : rhs) {
				push_back(e);
			}
		}

		list<T>& operator=(const list<T>& rhs) {
			list ls(rhs.begin(), rhs.end());
			swap(ls);
		}

		~list() {
			clear();
			delete _head;
			_head = nullptr;
		}

		bool empty() {
			return _head == _head->next;
		}

		void insert(iterator pos,const T& val) {//这个迭代器不会失效 pos该指向谁还是指向谁
			Node* cur = pos.pnode;
			Node* pre = cur->prev;

			Node* newnode = new Node(val);
			newnode->next = cur;
			newnode->prev = pre;

			pre->next = newnode;
			cur->prev = newnode;
		}

		iterator erase(iterator pos) {//这个迭代器必失效 勾八都变成野指针了 比vector明显多了
			assert(!empty());

			Node* cur = pos.pnode;
			Node* pre = cur->prev;
			Node* nex = cur->next;

			pre->next = nex;
			nex->prev = pre;
			delete cur;

			return iterator(nex);
		}

		//在有insert 和 erase后面实现头插头删 尾插尾删直接重用就行
		void push_back(const T& val) {
			/*Node* rail = _head->prev;
			Node* newnode = new Node(val);

			newnode->prev = rail;
			newnode->next = _head;
			rail->next = newnode;
			_head->prev = newnode;*/

			insert(end(), val);
		}

		void push_front(const T& val) {
			insert(begin(), val);
		}

		void pop_back() {
			erase(--end());//这里要--end()
		}

		void pop_front() {
			erase(begin());
		}

		T& front() {
			return _head->next->data;
		}

		T& back() {
			return _head->prev->data;
		}

		void clear() {//清空所有结点(除了头结点) 析构可以复用 
			/*Node* cur = _head ->next;
			Node* tmp = cur;
			while (cur != _head) {
				cur = cur->next;
				delete tmp;
				tmp = cur;
			}*/

			iterator it = begin();
			while (it != end()) {
				it = erase(it);//但迭代器会失效 库里面的erase会返回一个删掉后的下一个有效迭代器
			}
		}
	};
}
