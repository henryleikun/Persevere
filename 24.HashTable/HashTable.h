#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cassert>
using namespace std;

//��ϣ��Ĺ��� ��ϣ˼��(һ�ֽ��ؼ�����ĳ��ֵ����������˼��)--->���ݽṹʵ�ֹ�ϣ�� 
//��ϣ��ͻ�Ĳ�ͬ�����ʽ�ù�ϣ������˲�ͬ��ʵ�ַ�ʽ �����ͻ������̽��/����̽�� �ù�ϣ����һ����ȫ���ԵĽṹ
//��ʹ�ø�Ч��������/��ϣͰ�ķ��� �ù�ϣ����һ��������ʽ���ϵĽṹ 
//���� �һ���ʵ�� ����̽��Ĺ�ϣ�� ��ȥʵ�� ��ϣͰ�Ĺ�ϣ�� �����ǳ��� ���¾��ǳ���ȡ��ȥ������ϣӳ��
//�洢Ԫ����key value��(�����֮ǰ������һ�� �������ظ� keyֵ���ܱ��޸�)

//����̽��
namespace Linear_explore {
	enum state {
		EXIST,
		DELETE, //Ԥ��������ǰ��ֹ
		EMPTY //--size�Ĵ���
	};//��ÿ��Ҫ�洢�Ľ��ȥ����һ��״̬ Ҫ�Թ�ϣ��洢�����ݽ��з�װ 

	template<class K,class V>
	struct HashData {
		pair<K, V> _kv;
		state _s;

		HashData(const pair<K,V>& kv = pair<K,V>()):_kv(kv),_s(EMPTY) {
          
		}
	};

	//��K�ǲ��ܽ���ȡģ��������͵�ʱ�� ���ǻ�Ҫ��дһ��ӳ�� ��keyȥӳ���size_t
	//����º���
	template<class K>
	struct Hash {//��ǿת��size_t��ռ�����
		size_t operator()(const K& key) {
			return (size_t)key;
		}
	};

	template<>
	struct Hash<string> {//����ͽ���ʵ��һ��string���ػ� �����������˵
		size_t operator()(const string& str) {
			//�����ĵ� ����ַ�����ϣ�㷨 ���������ַ���ӳ���������ͻ
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
		vector<HashData> _table;//��ϣ���"��"�� ��������ͨ���Ա���ϣͰ��Ͱ�� 
		size_t _size;//��¼��ϣ���ڵ�Ԫ�� ��Ϊ��ϣ������� �������������˸�������(_size/_table.size())
	public:
		HashTable() {
			_table.resize(10);//Ĭ�ϴ�10��Ԫ��
			//ע�� ����ϣ��������size�Ǻ�capacity��ȵ�(�����[]����Խ�磬������Ҳ�������)
			//resize��ʹ�����ܹ�ȷ������
			_size = 0;
		}

		bool Insert(const pair<K,V>& kv) {
			HashFunc hash;
			if (Find(kv.first))
				return false;//���ظ�ֵ

			if (double(_size) / double(_table.size()) >= 0.7) {//������������Ϊ0.7 ����������
				//�������� ����� ��Ӧӳ���ϵ�ᷢ��ת�� �Ҳ���������ͬ���߼�ȥ���в��� �ҿ����������
				HashTable<K, V> newTable;
				newTable._table.resize(_table.size() * 2);
				size_t sz = _table.size();

				for (int i = 0; i < sz; i++) {
					if (_table[i]._s == EXIST)
						newTable.Insert(_table[i]._kv); //�ⲻ�ǵݹ� �ݹ����Լ����Լ� �����µĶ��� ȥ��
					                                   //һ����ͬ���߼� ��������µ�ӳ����newtable��size
				}
				
				_table.swap(newTable._table);//���������� ����������� newTable�Լ��ͷŵ�(������)
			}

			//����ȡ��ȡӳ���ַ
            //size_t hashi = kv.first % _table.size();
			size_t hashi = hash(kv.first) % _table.size();

			if (_table[hashi]._s != EXIST) {//delete empty�����Դ���
				_table[hashi] = HashData(kv);
				_table[hashi]._s = EXIST;
				++_size;
			}
			else {//��ͻ ��������̽��
				while (_table[hashi]._s == EXIST) {
					hashi = (hashi + 1) % _table.size();
				}//һ�����ҵ��յ� ��Ϊ�и�������������

				_table[hashi] = HashData(kv);
				_table[hashi]._s = EXIST;
				++_size;
			}
			
			return true;
		}

		bool Find(const K& key) {
			HashFunc hash;

			size_t hashi = hash(key) % _table.size();
			while (_table[hashi]._s != EMPTY) {//���ڿղ��ҽ���(Ҫô���� Ҫôɾ��)
				if (_table[hashi]._kv.first == key) {
					return true; //����ֱ�ӷ��ض�Ӧ��_kv �����bool�� 
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
//������Ļ����� ����ʵ�ֹ�ϣͰ ͬ����kvģ��

namespace Hash_Box {
	template<class K, class V>
	struct HashNode {
		pair<K, V> _kv;
		HashNode<K, V>* _next;

		HashNode(const pair<K, V>& kv = pair<K, V>()) :_kv(kv), _next(nullptr) {

		}
	};

	template<class K>
	struct Hash {//��ǿת��size_t��ռ�����
		size_t operator()(const K& key) {
			return (size_t)key;
		}
	};

	template<>
	struct Hash<string> {//����ͽ���ʵ��һ��string���ػ� �����������˵
		size_t operator()(const string& str) {
			//�����ĵ� ����ַ�����ϣ�㷨 ���������ַ���ӳ���������ͻ
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
		vector<PhashNode> _table;//ָ������
		size_t _size;
	public:
		HashTable() {
			_table.resize(10,nullptr);//Ĭ�ϴ�10��Ԫ��
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

			if (_size / _table.size() == 1) {//ƽ��һͰһ����ʱ�� ����
				HashTable<K, V> newTable;
				newTable._table.resize(_table.size() * 2);//���Ƕ�����
				newTable._size = _size;

				for (size_t i = 0; i < _table.size(); i++) {
					if (_table[i] != nullptr) {//��Ϊ�� �ͱ������ͰȻ������µĹ�ϣӳ�䵽�±���ȥ
						PhashNode cur = _table[i];
						size_t hashi = hash(_table[i]->_kv.first) % newTable._table.size();
						while (cur) {
							PhashNode next = cur->_next;//��ǰ��������cur����һ��

							cur->_next = newTable._table[hashi];
							newTable._table[hashi] = cur;
							cur = next;

							if (cur) {
								hashi = hash(cur->_kv.first) % newTable._table.size();
							}
						}//��ѭ�� ��iͰ��Ԫ�� �㶨

						_table[i] = nullptr;//�ÿ�
					}

				}//ÿһ��Ͱ���㶨

				_table.swap(newTable._table);//����������
			}

			//����ȡ��ȡӳ���ַ
			//size_t hashi = kv.first % _table.size();
			size_t hashi = hash(kv.first) % _table.size();

			if (_table[hashi] == nullptr) {//��Ͱ
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

		PhashNode Find(const K& key) {//���ض�Ӧ���ָ��� ��װ��ʱ�� ���Է��ص�����
			HashFunc hash;

			size_t hashi = hash(key) % _table.size();//��ֻ��Ҫ����hashi�µ�Ͱ������
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

			//keyֵһ������
			HashFunc hash;
			size_t hashi = hash(key) % _table.size();
			PhashNode cur = _table[hashi];//����ɾ���
			PhashNode prev = nullptr;
			
			while (cur) {
				if (cur->_kv.first == key) {
					if (prev == nullptr) //ͷɾ
						_table[hashi] = cur->_next;
					else
						prev->_next = cur->_next;

					delete cur;
					--_size;
					return true;
				}

				prev = cur;
				cur = cur->_next;
			}//һ���ҵĵ� �����ѭ��

		}

		void some() {//�鿴��ϣ���һЩ��Ϣ
			size_t buckets = 0;//�м����ǿ�Ͱ
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

			cout << "�ǿ�Ͱ�ĸ���Ϊ��" << buckets << endl;
			cout << "���Ͱ��Ϊ��" << maxbucketlen << endl;
			cout << "�ܵ�Ͱ�ĸ���Ϊ��" << _size << endl;
		}

	};
}

//=====================================================================================
//���������ϣͰʵ�ֵĹ�ϣ��Ļ����� ȥ��װ unordered_map unordered_set

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

	//ǰ������ �ҷ�װ������ ����Ҫ�й�ϣ��
	template<class K, class T, class KeyofValue, class HashFunc>
	class HashTable;

	//��װ������ �Թ�ϣ����ָ����з�װ
	template<class K,class T,class KeyofValue,class HashFunc,class Ref,class Ptr>
	struct Hash_iterator {
		typedef HashNode<T> Node;
		typedef Hash_iterator<K,T,KeyofValue,HashFunc,Ref,Ptr> self;
		typedef HashTable<K, T, KeyofValue, HashFunc> HT;

		Node* _pnode;
		const HT* _ptable;//ָ��Ҫ����Ĺ�ϣ��
		//�������ڶ����ڲ������ܽ��ն�����Ϊ����thisָ�����������
		Hash_iterator(Node* pnode = nullptr,HT* pt = nullptr)
			:_pnode(pnode),_ptable(pt) {

		}

		//const HT* ����const��this ������������_ptable����const ��������Ͱ�_ptableҲ�����const��
		//��ȷʵ���ı�ԭ�еĹ�ϣ�� ��ֻ�Ƕ�ָ����в��� �����ָ����_pnode����const �ҽ���const�ı�ָ��
		//���������޸ĵ�_pnode
		Hash_iterator(Node* pnode = nullptr,const HT* pt = nullptr)
			:_pnode(pnode), _ptable(pt) {

		}

		Ref operator*() {
			assert(_pnode != nullptr);//���ܶ���Ч������������
			
			return _pnode->_data;//���ص�ʱpair
		}

		Ptr operator->() {
			return &(_pnode->_data);
		}

		//��ε�++���Ǵӵ�һ���ǿ�Ͱ�ߵ����  ����ֻ�ܸ�һ�����ͺ����Ľ�� �ܲ���������ϣ��
		//��Ҫ����ϣ����Ϊģ�����
		self& operator++() {//ǰ��
			assert(_pnode != nullptr);//���������Ч������++

			KeyofValue getKey;
			HashFunc hash;
			size_t hashi = hash(getKey(_pnode->_data)) % _ptable->_table.size();//���ĸ�Ͱ��

			if (_pnode->_next == nullptr) {//Ҫ��Ͱ��
				//����Ҫ���ʹ�ϣ������ĳ�Ա ������Ҫ���������� ��ʵ�����������ȫ����ֻ���������
				//���ǰ��Ǹ�vector������������ ������������ϰ�Լ��Ĵ������� ������

				hashi += 1;
				//��������ı����Ǵӵ�һ����Ϊ�յ�Ͱ���������һ��Ͱ ���� �����hashi������_table.size()-1
				while (hashi != _ptable->_table.size() && _ptable->_table[hashi] == nullptr) {
					hashi += 1;
				}//����һ����Ϊ�յ�Ͱ

				//�����ͰȫΪ�� Ҳ����end��������涨һ��end����hashiΪ��Ĵ�С ָ��ָ��գ���ָ������ν
				if (hashi == _ptable->_table.size())
					_pnode = nullptr;
				else //˵���ҵ��˶�Ӧ�Ĳ�Ϊ�յ�Ͱ
					_pnode = _ptable->_table[hashi];

				return *this;
			}
			else {
				_pnode = _pnode->_next;
				return *this;
			}
		}

		self& operator++(int) {//����  һ�ῴ�ܲ��ܸ���
			self ret = *this;//Ĭ�ϵĸ�ֵ�����������

			assert(_pnode != nullptr);

			KeyofValue getKey;
			HashFunc hash;
			size_t hashi = hash(getKey(_pnode->_data)) % _ptable->_table.size();

			if (_pnode->_next == nullptr) {//Ҫ��Ͱ��
				hashi += 1;

				while (hashi != _ptable->_table.size() && _ptable->_table[hashi] == nullptr) {
					hashi += 1;
				}//����һ����Ϊ�յ�Ͱ

				if (hashi == _ptable->_table.size())
					_pnode = nullptr;
				else 
					_pnode = _ptable->_table[hashi];

			}
			else 
				_pnode = _pnode->_next;

			return ret;

		}

		self& operator--() {//ǰ��
			HashFunc getKey;

			if (_pnode == nullptr) {//��������end()
				size_t hashi = _ptable->_table.size() - 1;
				while (hashi != 0 && _ptable->_table[hashi] == nullptr) {
					--hashi;
				}//ǰ�治Ϊ�յ�Ͱ

				if (hashi == 0) //�ټ��һ�µ�һ��Ͱ
					if (_ptable->_table[hashi] != nullptr)
						_pnode = _ptable->_table[hashi];
					else
						assert(false);//Ϊ�վ�˵����ϣ��Ϊ��
				else //�ҵ���Ϊ�յ�Ͱ
					_pnode = _ptable->_table[hashi];
			}
			else {
				KeyofValue getKey;
				HashFunc hash;
				size_t hashi = hash(getKey(_pnode->_data)) % _ptable->_table.size();

				//�������Ͱ����һ�¿���û��ǰ�� û���ٻ�Ͱ
				Node* cur = _ptable->_table[hashi];
				Node* prev = nullptr;
				while (cur != _pnode) {
					prev = cur;
					cur = cur->_next;
				}

				if (prev == nullptr) {//��Ͱֻ��һ�� Ҫ��ǰ�ҵ�һ����Ϊ�յ�Ͱ
					if (hashi != 0) {
						--hashi;
					}

					while (hashi != 0 && _ptable->_table[hashi] == nullptr) {
						--hashi;
					}//ǰ�治Ϊ�յ�Ͱ

					if (hashi == 0)//�ټ��һ�µ�һ��Ͱ
						if (_ptable->_table[hashi] != nullptr)
							_pnode = _ptable->_table[hashi];
						else
							assert(false);
					else //�ҵ���Ϊ�յ�Ͱ
						_pnode = _ptable->_table[hashi];
				}
				else 
					_pnode = prev;
			}

			return *this;
		}

		self& operator--(int) {//����
			self ret = *this;

			if (_pnode == nullptr) {//��������end()
				size_t hashi = _ptable->_table.size() - 1;
				while (hashi != 0 && _ptable->_table[hashi] == nullptr) {
					--hashi;
				}//ǰ�治Ϊ�յ�Ͱ

				if (hashi == 0) //�ټ��һ�µ�һ��Ͱ
					if (_ptable->_table[hashi] != nullptr)
						_pnode = _ptable->_table[hashi];
					else
						assert(false);//Ϊ�վ�˵����ϣ��Ϊ��
				else //�ҵ���Ϊ�յ�Ͱ
					_pnode = _ptable->_table[hashi];
			}
			else {
				KeyofValue getKey;
				HashFunc hash;
				size_t hashi = hash(getKey(_pnode->_data)) % _ptable->_table.size();

				//�������Ͱ����һ�¿���û��ǰ�� û���ٻ�Ͱ
				Node* cur = _ptable->_table[hashi];
				Node* prev = nullptr;
				while (cur != _pnode) {
					prev = cur;
					cur = cur->_next;
				}

				if (prev == nullptr) {//��Ͱֻ��һ�� Ҫ��ǰ�ҵ�һ����Ϊ�յ�Ͱ
					if (hashi != 0) {
						--hashi;
					}

					while (hashi != 0 && _ptable->_table[hashi] == nullptr) {
						--hashi;
					}//ǰ�治Ϊ�յ�Ͱ

					if (hashi == 0)//�ټ��һ�µ�һ��Ͱ
						if (_ptable->_table[hashi] != nullptr)
							_pnode = _ptable->_table[hashi];
						else
							assert(false);
					else //�ҵ���Ϊ�յ�Ͱ
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
		vector<PhashNode> _table;//ָ������
		size_t _size;
	public:
		//��Ԫ������
		template<class K, class T, class KeyofValue, class HashFunc, class Ref, class Ptr >
		friend struct Hash_iterator;

		typedef Hash_iterator<K,T,KeyofValue,HashFunc,T&,T*> iterator;
		typedef Hash_iterator<K,T,KeyofValue,HashFunc,const T&,const T*> const_iterator;

		HashTable() {
			_table.resize(10, nullptr);//Ĭ�ϴ�10��Ԫ��
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

		//const���ε���this ���Ǳ߹��캯����HT*������Ȩ�޵ķŴ�
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

			if (_size / _table.size() == 1) {//ƽ��һͰһ����ʱ�� ����
				HashTable<K,T,KeyofValue> newTable;
				newTable._table.resize(_table.size() * 2);//���Ƕ�����
				newTable._size = _size;

				for (size_t i = 0; i < _table.size(); i++) {
					if (_table[i] != nullptr) {//��Ϊ�� �ͱ������ͰȻ������µĹ�ϣӳ�䵽�±���ȥ
						PhashNode cur = _table[i];
						size_t hashi = hash(getKey(_table[i]->_data)) % newTable._table.size();
						while (cur) {
							PhashNode next = cur->_next;//��ǰ��������cur����һ��

							cur->_next = newTable._table[hashi];
							newTable._table[hashi] = cur;
							cur = next;

							if (cur) {
								hashi = hash(getKey(cur->_data)) % newTable._table.size();
							}
						}//��ѭ�� ��iͰ��Ԫ�� �㶨

						_table[i] = nullptr;//�ÿ�
					}

				}//ÿһ��Ͱ���㶨

				_table.swap(newTable._table);//����������
			}

			//����ȡ��ȡӳ���ַ
			//size_t hashi = kv.first % _table.size();
			size_t hashi = hash(getKey(data)) % _table.size();

			if (_table[hashi] == nullptr) {//��Ͱ
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

		iterator Find(const K& key) {//���ض�Ӧ���ָ��� ��װ��ʱ�� ���Է��ص�����
			HashFunc hash;
			KeyofValue getKey;

			size_t hashi = hash(key) % _table.size();//��ֻ��Ҫ����hashi�µ�Ͱ������
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

			//keyֵһ������
			HashFunc hash;
			KeyofValue getKey;
			size_t hashi = hash(key) % _table.size();
			PhashNode cur = _table[hashi];//����ɾ���
			PhashNode prev = nullptr;

			while (cur) {
				if (getKey(cur->_data) == key) {
					if (prev == nullptr) //ͷɾ
						_table[hashi] = cur->_next;
					else
						prev->_next = cur->_next;

					delete cur;
					--_size;
					return true;
				}

				prev = cur;
				cur = cur->_next;
			}//һ���ҵĵ� �����ѭ��

		}
	};
}
