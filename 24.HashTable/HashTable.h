#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cassert>
using namespace std;

//哈希表的构建 哈希思想(一种将关键字与某个值建立关联的思想)--->数据结构实现哈希表 
//哈希冲突的不同解决方式让哈希表呈现了不同的实现方式 解决冲突有线性探测/二次探测 让哈希表是一个完全线性的结构
//而使用高效的拉链法/哈希桶的方法 让哈希表是一个线性链式相结合的结构 
//下面 我会先实现 线性探测的哈希表 再去实现 哈希桶的哈希表 后者是常规 以下均是除留取余去建立哈希映射
//存储元素是key value型(规则和之前的搜索一样 不允许重复 key值不能被修改)

//线性探测
namespace Linear_explore {
	enum state {
		EXIST,
		DELETE, //预防遍历提前终止
		EMPTY //--size的处理
	};//给每个要存储的结点去定义一个状态 要对哈希表存储的数据进行封装 

	template<class K,class V>
	struct HashData {
		pair<K, V> _kv;
		state _s;

		HashData(const pair<K,V>& kv = pair<K,V>()):_kv(kv),_s(EMPTY) {
          
		}
	};

	//当K是不能进行取模运算的类型的时候 我们还要再写一个映射 让key去映射成size_t
	//搞个仿函数
	template<class K>
	struct Hash {//能强转成size_t的占大多数
		size_t operator()(const K& key) {
			return (size_t)key;
		}
	};

	template<>
	struct Hash<string> {//这里就仅仅实现一个string的特化 如果有其他再说
		size_t operator()(const string& str) {
			//查阅文档 搞个字符串哈希算法 尽可能让字符串映射的数不冲突
			size_t hash = 0;
	        
			for (size_t i = 0; i < str.size(); i++) {
				hash = hash * 31 + str[i];
			}
			
			return hash;
		}
	};

	template<class K,class V,class HashFunc = Hash<K>>
	class HashTable {
		typedef HashData<K, V> HashData;
	private:
		vector<HashData> _table;//哈希表的"表"字 可能是普通线性表或哈希桶的桶列 
		size_t _size;//记录哈希表内的元素 因为哈希表会扩容 而扩容又引入了负载因子(_size/_table.size())
	public:
		HashTable() {
			_table.resize(10);//默认存10个元素
			//注意 我们希望这个表的size是和capacity相等的(不相等[]会检查越界，而且这也会简化扩容)
			//resize的使用是能够确保这点的
			_size = 0;
		}

		bool Insert(const pair<K,V>& kv) {
			HashFunc hash;
			if (Find(kv.first))
				return false;//有重复值

			if (double(_size) / double(_table.size()) >= 0.7) {//负载因子设置为0.7 超过就扩容
				//二倍扩吧 扩完后 对应映射关系会发生转变 我不想在走相同的逻辑去进行插入 且看我下面操作
				HashTable<K, V> newTable;
				newTable._table.resize(_table.size() * 2);
				size_t sz = _table.size();

				for (int i = 0; i < sz; i++) {
					if (_table[i]._s == EXIST)
						newTable.Insert(_table[i]._kv); //这不是递归 递归是自己调自己 这是新的对象 去走
					                                   //一遍相同的逻辑 里面会是新的映射是newtable的size
				}
				
				_table.swap(newTable._table);//交换两个表 出这个作用域 newTable自己释放掉(老数据)
			}

			//除留取余取映射地址
            //size_t hashi = kv.first % _table.size();
			size_t hashi = hash(kv.first) % _table.size();

			if (_table[hashi]._s != EXIST) {//delete empty都可以存入
				_table[hashi] = HashData(kv);
				_table[hashi]._s = EXIST;
				++_size;
			}
			else {//冲突 进行线性探测
				while (_table[hashi]._s == EXIST) {
					hashi = (hashi + 1) % _table.size();
				}//一定能找到空的 因为有负载因子限制着

				_table[hashi] = HashData(kv);
				_table[hashi]._s = EXIST;
				++_size;
			}
			
			return true;
		}

		bool Find(const K& key) {
			HashFunc hash;

			size_t hashi = hash(key) % _table.size();
			while (_table[hashi]._s != EMPTY) {//等于空查找结束(要么存在 要么删除)
				if (_table[hashi]._kv.first == key) {
					return true; //可以直接返回对应的_kv 这里就bool了 
				}
				else {
					hashi = (hashi + 1) % _table.size();
				}
			}

			return false;
		}

		bool Erase(const K& key) {
			if (!Find(key))
				return false;

			HashFunc hash;
			size_t hashi = hash(key) % _table.size();
			while (_table[hashi]._kv.first != key) {
				hashi = (hashi + 1) % _table.size();
			}

			_table[hashi]._s = DELETE;
			--_size;
			return true;
		}
	};
}

//=================================================================================================
//在上面的基础上 下面实现哈希桶 同样是kv模型

namespace Hash_Box {
	template<class K, class V>
	struct HashNode {
		pair<K, V> _kv;
		HashNode<K, V>* _next;

		HashNode(const pair<K, V>& kv = pair<K, V>()) :_kv(kv), _next(nullptr) {

		}
	};

	template<class K>
	struct Hash {//能强转成size_t的占大多数
		size_t operator()(const K& key) {
			return (size_t)key;
		}
	};

	template<>
	struct Hash<string> {//这里就仅仅实现一个string的特化 如果有其他再说
		size_t operator()(const string& str) {
			//查阅文档 搞个字符串哈希算法 尽可能让字符串映射的数不冲突
			size_t hash = 0;

			for (size_t i = 0; i < str.size(); i++) {
				hash = hash * 31 + str[i];
			}

			return hash;
		}
	};

	template<class K, class V, class HashFunc = Hash<K>>
	class HashTable {
		typedef HashNode<K, V>* PhashNode;
		typedef HashNode<K, V> HashNode;
	private:
		vector<PhashNode> _table;//指针数组
		size_t _size;
	public:
		HashTable() {
			_table.resize(10,nullptr);//默认存10个元素
			_size = 0;
		}

		~HashTable() {
			for (size_t i = 0; i < _table.size(); i++) {
				if (_table[i] != nullptr) {
					PhashNode cur = _table[i];
					PhashNode p = nullptr;

					while (cur) {
						p = cur->_next;
						delete cur;
						cur = p;
					}
				}

				_table[i] = nullptr;
			}
		}

		bool Insert(const pair<K, V>& kv) {
			HashFunc hash;
			if (Find(kv.first) != nullptr)
				return false;

			if (_size / _table.size() == 1) {//平均一桶一个的时候 扩容
				HashTable<K, V> newTable;
				newTable._table.resize(_table.size() * 2);//还是二倍扩
				newTable._size = _size;

				for (size_t i = 0; i < _table.size(); i++) {
					if (_table[i] != nullptr) {//不为空 就遍历这个桶然后算出新的哈希映射到新表里去
						PhashNode cur = _table[i];
						size_t hashi = hash(_table[i]->_kv.first) % newTable._table.size();
						while (cur) {
							PhashNode next = cur->_next;//提前保存下来cur的下一个

							cur->_next = newTable._table[hashi];
							newTable._table[hashi] = cur;
							cur = next;

							if (cur) {
								hashi = hash(cur->_kv.first) % newTable._table.size();
							}
						}//出循环 第i桶的元素 搞定

						_table[i] = nullptr;//置空
					}

				}//每一个桶都搞定

				_table.swap(newTable._table);//交换两个表
			}

			//除留取余取映射地址
			//size_t hashi = kv.first % _table.size();
			size_t hashi = hash(kv.first) % _table.size();

			if (_table[hashi] == nullptr) {//空桶
				_table[hashi] = new HashNode(kv);
			}
			else {
				PhashNode newNode = new HashNode(kv);
				newNode->_next = _table[hashi];
				_table[hashi] = newNode;
			}

			++_size;
			return true;
		}

		PhashNode Find(const K& key) {//返回对应结点指针吧 封装的时候 可以返回迭代器
			HashFunc hash;

			size_t hashi = hash(key) % _table.size();//我只需要考虑hashi下的桶就行了
			PhashNode cur = _table[hashi];
			while (cur) {
				if (cur->_kv.first == key)
					return cur;

				cur = cur->_next;
			}
		    
			return nullptr;
		}

		bool Erase(const K& key) {
			if (Find(key) == nullptr)
				return false;

			//key值一定存在
			HashFunc hash;
			size_t hashi = hash(key) % _table.size();
			PhashNode cur = _table[hashi];//链表删结点
			PhashNode prev = nullptr;
			
			while (cur) {
				if (cur->_kv.first == key) {
					if (prev == nullptr) //头删
						_table[hashi] = cur->_next;
					else
						prev->_next = cur->_next;

					delete cur;
					--_size;
					return true;
				}

				prev = cur;
				cur = cur->_next;
			}//一定找的到 不会出循环

		}

		void some() {//查看哈希表的一些信息
			size_t buckets = 0;//有几个非空桶
			size_t maxbucketlen = 0;

			for (size_t i = 0; i < _table.size(); ++i) {
				PhashNode cur = _table[i];

				if (cur != nullptr)
					++buckets;

				size_t bucketlen = 0;
				while (cur) {
					++bucketlen;
					cur = cur->_next;
				}

				if (bucketlen > maxbucketlen) {
					maxbucketlen = bucketlen;
				}
			}

			cout << "非空桶的个数为：" << buckets << endl;
			cout << "最长的桶长为：" << maxbucketlen << endl;
			cout << "总的桶的个数为：" << _size << endl;
		}

	};
}

//=====================================================================================
//再在上面哈希桶实现的哈希表的基础上 去封装 unordered_map unordered_set

namespace Henry {
	template<class T>
	struct HashNode {
		T _data;
		HashNode<T>* _next;

		HashNode(const T& data = T()) :_data(data), _next(nullptr) {

		}
	};

	template<class K>
	struct Hash {
		size_t operator()(const K& key) {
			return (size_t)key;
		}
	};

	template<>
	struct Hash<string> {
		size_t operator()(const string& str) {
			size_t hash = 0;

			for (size_t i = 0; i < str.size(); i++) {
				hash = hash * 31 + str[i];
			}

			return hash;
		}
	};

	//前置声明 我封装迭代器 里面要有哈希表
	template<class K, class T, class KeyofValue, class HashFunc>
	class HashTable;

	//封装迭代器 对哈希结点的指针进行封装
	template<class K,class T,class KeyofValue,class HashFunc,class Ref,class Ptr>
	struct Hash_iterator {
		typedef HashNode<T> Node;
		typedef Hash_iterator<K,T,KeyofValue,HashFunc,Ref,Ptr> self;
		typedef HashTable<K, T, KeyofValue, HashFunc> HT;

		Node* _pnode;
		const HT* _ptable;//指向要处理的哈希表
		//迭代器在对象内部，不能接收对象作为参数this指针就起到了作用
		Hash_iterator(Node* pnode = nullptr,HT* pt = nullptr)
			:_pnode(pnode),_ptable(pt) {

		}

		//const HT* 接收const的this 那问题又来了_ptable不是const 所以这里就把_ptable也处理成const了
		//我确实不改变原有的哈希表 我只是对指针进行操作 而这个指针是_pnode不是const 我借助const的表指针
		//来操作可修改的_pnode
		Hash_iterator(Node* pnode = nullptr,const HT* pt = nullptr)
			:_pnode(pnode), _ptable(pt) {

		}

		Ref operator*() {
			assert(_pnode != nullptr);//不能对无效迭代器解引用
			
			return _pnode->_data;//返回的时pair
		}

		Ptr operator->() {
			return &(_pnode->_data);
		}

		//这次的++就是从第一个非空桶走到最后  但我只能搞一个结点和后续的结点 管不了整个哈希表
		//我要传哈希表作为模板参数
		self& operator++() {//前置
			assert(_pnode != nullptr);//不允许对无效迭代器++

			KeyofValue getKey;
			HashFunc hash;
			size_t hashi = hash(getKey(_pnode->_data)) % _ptable->_table.size();//在哪个桶里

			if (_pnode->_next == nullptr) {//要换桶了
				//我需要访问哈希表里面的成员 所以我要是他的朋友 其实这个迭代器完全可以只传个表过来
				//就是把那个vector传过来就行了 但这样更能练习自己的代码能力 不是吗？

				hashi += 1;
				//我们这里的遍历是从第一个不为空的桶遍历到最后一个桶 所以 这里的hashi最多就是_table.size()-1
				while (hashi != _ptable->_table.size() && _ptable->_table[hashi] == nullptr) {
					hashi += 1;
				}//找下一个不为空的桶

				//后面的桶全为空 也就是end情况我来规定一下end就是hashi为表的大小 指针指向空，表指针无所谓
				if (hashi == _ptable->_table.size())
					_pnode = nullptr;
				else //说明找到了对应的不为空的桶
					_pnode = _ptable->_table[hashi];

				return *this;
			}
			else {
				_pnode = _pnode->_next;
				return *this;
			}
		}

		self& operator++(int) {//后置  一会看能不能复用
			self ret = *this;//默认的赋值运算符可以用

			assert(_pnode != nullptr);

			KeyofValue getKey;
			HashFunc hash;
			size_t hashi = hash(getKey(_pnode->_data)) % _ptable->_table.size();

			if (_pnode->_next == nullptr) {//要换桶了
				hashi += 1;

				while (hashi != _ptable->_table.size() && _ptable->_table[hashi] == nullptr) {
					hashi += 1;
				}//找下一个不为空的桶

				if (hashi == _ptable->_table.size())
					_pnode = nullptr;
				else 
					_pnode = _ptable->_table[hashi];

			}
			else 
				_pnode = _pnode->_next;

			return ret;

		}

		self& operator--() {//前置
			HashFunc getKey;

			if (_pnode == nullptr) {//迭代器是end()
				size_t hashi = _ptable->_table.size() - 1;
				while (hashi != 0 && _ptable->_table[hashi] == nullptr) {
					--hashi;
				}//前面不为空的桶

				if (hashi == 0) //再检查一下第一个桶
					if (_ptable->_table[hashi] != nullptr)
						_pnode = _ptable->_table[hashi];
					else
						assert(false);//为空就说明哈希表为空
				else //找到不为空的桶
					_pnode = _ptable->_table[hashi];
			}
			else {
				KeyofValue getKey;
				HashFunc hash;
				size_t hashi = hash(getKey(_pnode->_data)) % _ptable->_table.size();

				//先在这个桶里找一下看有没有前驱 没有再换桶
				Node* cur = _ptable->_table[hashi];
				Node* prev = nullptr;
				while (cur != _pnode) {
					prev = cur;
					cur = cur->_next;
				}

				if (prev == nullptr) {//该桶只有一个 要往前找第一个不为空的桶
					if (hashi != 0) {
						--hashi;
					}

					while (hashi != 0 && _ptable->_table[hashi] == nullptr) {
						--hashi;
					}//前面不为空的桶

					if (hashi == 0)//再检查一下第一个桶
						if (_ptable->_table[hashi] != nullptr)
							_pnode = _ptable->_table[hashi];
						else
							assert(false);
					else //找到不为空的桶
						_pnode = _ptable->_table[hashi];
				}
				else 
					_pnode = prev;
			}

			return *this;
		}

		self& operator--(int) {//后置
			self ret = *this;

			if (_pnode == nullptr) {//迭代器是end()
				size_t hashi = _ptable->_table.size() - 1;
				while (hashi != 0 && _ptable->_table[hashi] == nullptr) {
					--hashi;
				}//前面不为空的桶

				if (hashi == 0) //再检查一下第一个桶
					if (_ptable->_table[hashi] != nullptr)
						_pnode = _ptable->_table[hashi];
					else
						assert(false);//为空就说明哈希表为空
				else //找到不为空的桶
					_pnode = _ptable->_table[hashi];
			}
			else {
				KeyofValue getKey;
				HashFunc hash;
				size_t hashi = hash(getKey(_pnode->_data)) % _ptable->_table.size();

				//先在这个桶里找一下看有没有前驱 没有再换桶
				Node* cur = _ptable->_table[hashi];
				Node* prev = nullptr;
				while (cur != _pnode) {
					prev = cur;
					cur = cur->_next;
				}

				if (prev == nullptr) {//该桶只有一个 要往前找第一个不为空的桶
					if (hashi != 0) {
						--hashi;
					}

					while (hashi != 0 && _ptable->_table[hashi] == nullptr) {
						--hashi;
					}//前面不为空的桶

					if (hashi == 0)//再检查一下第一个桶
						if (_ptable->_table[hashi] != nullptr)
							_pnode = _ptable->_table[hashi];
						else
							assert(false);
					else //找到不为空的桶
						_pnode = _ptable->_table[hashi];
				}
				else
					_pnode = prev;
			}
			
			return ret;
		}

		bool operator!=(const self& rhs) {
			return _pnode != rhs._pnode;
		}

		bool operator==(const self& rhs) {
			return _pnode == rhs._pnode;
		}
	};

	template<class K, class T, class KeyofValue,class HashFunc = Hash<K>>
	class HashTable {
		typedef HashNode<T>* PhashNode;
		typedef HashNode<T> HashNode;
	private:
		vector<PhashNode> _table;//指针数组
		size_t _size;
	public:
		//友元迭代器
		template<class K, class T, class KeyofValue, class HashFunc, class Ref, class Ptr >
		friend struct Hash_iterator;

		typedef Hash_iterator<K,T,KeyofValue,HashFunc,T&,T*> iterator;
		typedef Hash_iterator<K,T,KeyofValue,HashFunc,const T&,const T*> const_iterator;

		HashTable() {
			_table.resize(10, nullptr);//默认存10个元素
			_size = 0;
		}

		~HashTable() {
			for (size_t i = 0; i < _table.size(); i++) {
				if (_table[i] != nullptr) {
					PhashNode cur = _table[i];
					PhashNode p = nullptr;

					while (cur) {
						p = cur->_next;
						delete cur;
						cur = p;
					}
				}

				_table[i] = nullptr;
			}
		}

		iterator begin() {
			for (size_t i = 0; i < _table.size(); i++) {
				if (_table[i] != nullptr)
					return iterator(_table[i], this);
			}

			return iterator(nullptr, this);
		}

		iterator end() {
			return iterator(nullptr, this);
		}

		//const修饰的是this 而那边构造函数是HT*接收是权限的放大
		const_iterator cbegin()const {
			for (size_t i = 0; i < _table.size(); i++) {
				if (_table[i] != nullptr)
					return const_iterator(_table[i], this);
			}

			return const_iterator(nullptr, this);
		}

		const_iterator cend()const {
			return const_iterator(nullptr, this);
		}

		pair<iterator, bool> Insert(const T& data) {
			HashFunc hash;
			KeyofValue getKey;

			iterator ret = Find(getKey(data));
			if (ret._pnode != nullptr)
				return make_pair(ret,false);

			if (_size / _table.size() == 1) {//平均一桶一个的时候 扩容
				HashTable<K,T,KeyofValue> newTable;
				newTable._table.resize(_table.size() * 2);//还是二倍扩
				newTable._size = _size;

				for (size_t i = 0; i < _table.size(); i++) {
					if (_table[i] != nullptr) {//不为空 就遍历这个桶然后算出新的哈希映射到新表里去
						PhashNode cur = _table[i];
						size_t hashi = hash(getKey(_table[i]->_data)) % newTable._table.size();
						while (cur) {
							PhashNode next = cur->_next;//提前保存下来cur的下一个

							cur->_next = newTable._table[hashi];
							newTable._table[hashi] = cur;
							cur = next;

							if (cur) {
								hashi = hash(getKey(cur->_data)) % newTable._table.size();
							}
						}//出循环 第i桶的元素 搞定

						_table[i] = nullptr;//置空
					}

				}//每一个桶都搞定

				_table.swap(newTable._table);//交换两个表
			}

			//除留取余取映射地址
			//size_t hashi = kv.first % _table.size();
			size_t hashi = hash(getKey(data)) % _table.size();

			if (_table[hashi] == nullptr) {//空桶
				_table[hashi] = new HashNode(data);
			}
			else {
				PhashNode newNode = new HashNode(data);
				newNode->_next = _table[hashi];
				_table[hashi] = newNode;
			}

			++_size;
			return make_pair(iterator(_table[hashi],this),true);
		}

		iterator Find(const K& key) {//返回对应结点指针吧 封装的时候 可以返回迭代器
			HashFunc hash;
			KeyofValue getKey;

			size_t hashi = hash(key) % _table.size();//我只需要考虑hashi下的桶就行了
			PhashNode cur = _table[hashi];
			while (cur) {
				if (getKey(cur->_data) == key)
					return iterator(cur,this);

				cur = cur->_next;
			}

			return iterator(nullptr,this);
		}

		bool Erase(const K& key) {
			if (Find(key) == end())
				return false;

			//key值一定存在
			HashFunc hash;
			KeyofValue getKey;
			size_t hashi = hash(key) % _table.size();
			PhashNode cur = _table[hashi];//链表删结点
			PhashNode prev = nullptr;

			while (cur) {
				if (getKey(cur->_data) == key) {
					if (prev == nullptr) //头删
						_table[hashi] = cur->_next;
					else
						prev->_next = cur->_next;

					delete cur;
					--_size;
					return true;
				}

				prev = cur;
				cur = cur->_next;
			}//一定找的到 不会出循环

		}
	};
}
