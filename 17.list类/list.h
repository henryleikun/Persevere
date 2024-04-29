#pragma once
#include <iostream>
#include <cassert>
using namespace std;
//ʵ��list(��ͷ˫��ѭ������) �����Ǹ����ݽṹʵ�ֲ��� �����
//Ҫ�ú�ʵ�ֵ�����  ��Ϥģ��

//����������ʵ����size resize �� ����Ͳ�ʵ���� ûɶ��
//�����ֻ��ʵ��һЩ���õĽӿ�

//C++ structҲ���Կ�������

//����ĵ����� ��vector��string���б��ʵ����� ��Ϊ������ ��˳��洢
//��ͨ����������ʹ��ԭ��ָ����ʵ�� ��������ʽ�洢��list��˵ ������ԭ��ָ�� ��
//��ɲ��˶�Ӧ������� ����iterator++ ���ָ�� ��һ������һ����� 
//�������Ҫ��� ��ָ��ķ�װ ����struct(class)��װ��  ��װ���ǰ�ָ����ʹ��
namespace Henry {
	template<class T>
	struct ListNode {
		T data;
		ListNode<T>* prev;
		ListNode<T>* next;

		ListNode(const T& rhs = T()) :data(rhs), prev(nullptr), next(nullptr) {

		}//�ṩ���캯��
	};

	//��װ���ָ��pnode��Ϊ���������� ���캯��ȷ��pnodeָ���ĸ���� 
	//������Ҫģ��ָ�����Ϊ ���˽����û���++֮�� ����һ���Ƚ������: ->
	//������������ڵ�����ָ��Ľ���data��һ���Զ�������
	template<class T,class Ref,class Ptr>
	struct _list_iterator {
		typedef ListNode<T> Node;
		typedef _list_iterator<T,Ref,Ptr> self;

		Node* pnode;

		//��Ĭģ��_list_iterator<T>(Node* node = nullptr):pnode(node)
		//��<T>˵�����βκͷ���ֵ,���� ���㺯������ʲô��ϵ ���ˣ�
		_list_iterator(Node* node = nullptr) :pnode(node) {

		}//it(list.begin())�ǿ������� Ĭ�ϼ��ɸ�ֵ�����ͬ��
		//���ﲻ������������ ��ֻ�ǽ�������������ָ��Խڵ�����ݽ��в���
		//�϶������ͷ����� ���ָ�� ��ֻ��ʹ��Ȩ û�й���Ȩ����������������

		Ref operator *() {
			return pnode->data;
		}

		self& operator++() {//ǰ׺
			//return pnode->next; ������԰� �ⷵ�ص�Ҫ��һ�������� �㷵�ؽ��ָ��
			//���ָ����ʽ����ת������ʱ�ĵ��������� �����⻹�Ǹ�����
			pnode = pnode->next;

			return *this;
		}

		self operator++(int) {//��׺
			self ret(pnode);
			pnode = pnode->next;

			return ret;
		}

		//˫������� Ҫʵ��--
		self& operator--() {//ǰ׺
			pnode = pnode->prev;
			return *this;
		}

		self operator--(int) {//��׺
			self ret(pnode);
			pnode = pnode->prev;

			return ret;
		}

		Ptr operator->() {//���� struct Node* ps, ps->��Node�ĳ�Ա
			return &pnode->data;//��data���Զ�������ʱ 
		}
        //���￼�ǵ� ����const�������const������ const����������->() ��������ҲҪ��
		//const ������ �ǲ��ܸı� ->��ָ��� �����ص�Ӧ����const T* ͬT& �����ڼ�һ��ģ�����

		bool operator!=(const self& rhs) {
			return pnode != rhs.pnode;
		}

		bool operator==(const self& rhs) {
			return pnode == rhs.pnode;
		}
	};


	//����������ȥʵ�� const T* p�ĵ����� ָ������ݲ��� ���������ɱ�
	//����ֻ��Ҫ������Ļ����� �������õķ���ֵ��һ��const���� ����������Ե�������
	//ֻ���������Ե�����ָ��Ľ���
	//��list���� typedef _list_const_iterator<T> const_iterator
	//˼�� ʵ��һ��const������ ��Ҫʹ����ô�ظ��ȸߵĴ�����
    //����Ҫ ����̫������ ������ֻ�н����õķ���ֵ�в��� T&��const T&
    //������һ���ǳ��� �ǳ�nb����� ����ͨ������һ��������ģ�����Ref����ʶ
	//��ͬ�ķ���ֵ ��ͨ��������<T,T&> ֻ��������:<T,const T&>
	//Ref���յڶ���ģ����� ����Ϊ*�ķ���ֵ ok
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

	//	self& operator++() {//ǰ׺
	//		pnode = pnode->next;

	//		return *this;
	//	}

	//	self operator++(int) {//��׺
	//		self ret(pnode);
	//		pnode = pnode->next;

	//		return ret;
	//	}

	//	self& operator--() {//ǰ׺
	//		pnode = pnode->prev;
	//		return *this;
	//	}

	//	self operator--(int) {//��׺
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

	//ʵ�ַ�������� ����������ڸտ�ʼ����֪����ǵ����������� �÷����������++���ǵ�������--
	//ȷʵ��ˣ���ô����rbegin��rend���� ����������ķ�Χ��ʲô������������(beginָ���һ��endָ�����һ����
	// ��һ��)��������(rbeginָ�����һ������rendָ���һ����ǰһ��)�������治�������ģ������������Χ�պöԳ�
	//���� Ҳ����rbeginָ�����һ������һ�� rendָ���һ�� �ǸպöԳƵ�

	//ͬʱ �������ǶԽ��ָ��Node*�ķ�װ ���������Ҳ������ ��ҲҪʵ��++ --�Ȳ��� ҲҪ���з�װ ����������
	//��=��Ҫ����ȫдһ���͵�����һ����struct�� ��Ϊ�󲿷ֹ��ܵ��߼���ʵ�ʺϵ����������෴�ģ��ܲ��ܸ���
	//һ���أ�    ������  ���԰ѷ������������һ�������� ͨ������Ѿ���װ�õĵ�����ȥʵ���Լ��Ĺ���
	// �������úõ������Ľӿھ���
	//����Ҳ˵�� �����++�������--�ҷ����rbegin��ָ�����һ������һ�������ڽ����õ�ʱ��Ӧ�����ƶ��ٽ�����
	//���������£�
    template<class Iterator,class Ref,class Ptr>
	struct ReverseIterator {
		typedef ReverseIterator<Iterator,Ref,Ptr> self;

		Iterator it;

		ReverseIterator(Iterator _it):it(_it) {

		}

		Ref operator*() {//��Ϊ��it�Ľ������ٵ���������Ƿ���Ref ���ﷵ�ص�������һ����
			             //�����->������ͬ��
			Iterator cur = it;
			return *--cur;
		}

		self& operator++() {//ǰ��
			//return --it;  self�Ƿ�������� it����������� ���ڸ�ʲô��
			--it;

			return *this;
		}

		self operator++(int) {//����
			self cur = *this;
			--it;
		
			return cur;
		}

		self& operator--() {//ǰ��
			//return ++it;
			++it;

			return *this;
		}

		self operator--(int) {//����
			self cur = *this;
			++it;

			return cur;
		}

		//��ķ���������Ľ����ú�->��Զ�Ǵ���itָ���ǰһ�������� ��Ϊ���ȡ�������ķ�ʽֻ��
		//rbegin() rend() �ͱ�������������rend�Ļ� ����Ҫ�ľ�����ָ�Ķ���������ǰһ��
		//����û����� �����õ�������ʱ�� �㲻��ֱ��ȥ������end() ��Ϊ��֪������ָ�����һ������һ��
		//������û�� ���������--��ȥ�����ã�����Ҳ��һ���� ������Ͽ������ķ����������rbegin()ָ�����һ��
		//rend()ָ���һ����ǰһ�� ������Ҳ����ֱ�ӽ����� rend ��Ҫ����--����ʵ��ʱ��rend()ָ���������Ҫ��
		//��һ������ ������õ�ʵ�־��Ǹպ��õ�����Ҫ���Ǹ� ������������ǵ�ʵ�� ��ҲҪ��� ���ǵĽӿ�(����
		// �ĳ���)����  
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


	//��ס�Ǵ�ͷ˫��ѭ������
	template<class T>
	class list {
		typedef ListNode<T> Node;//����ڵ�(ģ��)������ ��ģ���������
	public:
		typedef _list_iterator<T,T&,T*> iterator;//����public ���Ҫ�� ������Ҫ��private
		                                  //������Ҳ������ģ���������
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
		}//һ��СС�ĳ�ʼ�� Ĭ�Ϲ��캯���������Ͳ������� vs������ �������ǲ������
		//���캯������Ա���� ������������ͷ�ڵ�ĳ�ʼ��

		list() {
			empty_initialize();
		}

		iterator begin() {
			//return _head->next; ����д���ɶ��Բ�ǿ ��Ȼ���ָ������ʽת���ɵ���������
			return iterator(_head->next);
			//�����Ϳ����� �����Ƕ��ǲٿصĵ�����ָ���λ�� ���� �����������Ĭ�Ͽ���������ȫ����
		}

		iterator end() {
			return iterator(_head);
		}

	    //const iterator begin()const {
		//}

		//const iterator end()const {
		//}
		
		// ����const ����ȡ�õ�����ʱ ��vector��(ָ��ʵ��)����ֱ�Ӹ��const const����this
		// ָ���㲻�ܸı�vector���_start��ָ��ָ���ֵ ��ֻ�Ǻ�׺��const����thisָ��
		// �Ǳ�֤���ı�ָ��� �����ص�Ҳ�ǿ��� �ⶼ����ν ����Ҫ��ָ֤���ֵ���� vector
		// ���ص��� const_iterator(const T*)
		// ��������const��֤_head�����ı� ��const�����ܵ��� �����ܱ�֤ ������ָ��Ľ�㲻��
		// ���ı� ��Ҫ���vector�ķ��� ������д��const iterator��ȫû���� �������õ���������
		// �ı��� ���൱�� int *const p�� �ǻ���ô������������
		// ���Ի��� vector����Ҫ����һ��const_iterator ��Ҫ����ôʵ�����ֻ�������� �������������
		// ��һ������ ����������pnode��Ҫ���ľ��� const pnode ���ܸı�pnodeָ���ֵ �����Ըı�
		// pnode��ָ��(��֧�� ���� �����õ�) 

		const_iterator begin()const {
			return const_iterator(_head->prev);
		}

		const_iterator end()const {
			return const_iterator(_head);
		}


		//���������
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
	    
		//ģ�幹�캯��
		template<class Inputiterator>
		list(Inputiterator first,Inputiterator last) {//���յ����� ָ��
			empty_initialize();//û�������ʼ�� _head�������ֵ(������vs����Ĵ���)
            
			while (first != last) {
				push_back(*first);
				first++;
			}
		}

		void swap(list<T>& rhs) {
			std::swap(_head, rhs._head);
		}

		//����Ŀ�������͸�ֵ����������ִ�ʽд��ok �Ͳ��ֶ������
		list(const list<T>& rhs) {
			//empty_initialize();
			/*list ls(rhs.begin(),rhs.end());
			swap(ls);*/

			//�����һ��const������� �������� �������empty_�����������constҲ�ܵ���
			//���� const���������������ʱ����Ϊ��ֻ����Ҫ��Ȼ��ô��ֵ
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

		void insert(iterator pos,const T& val) {//�������������ʧЧ pos��ָ��˭����ָ��˭
			Node* cur = pos.pnode;
			Node* pre = cur->prev;

			Node* newnode = new Node(val);
			newnode->next = cur;
			newnode->prev = pre;

			pre->next = newnode;
			cur->prev = newnode;
		}

		iterator erase(iterator pos) {//�����������ʧЧ ���˶����Ұָ���� ��vector���Զ���
			assert(!empty());

			Node* cur = pos.pnode;
			Node* pre = cur->prev;
			Node* nex = cur->next;

			pre->next = nex;
			nex->prev = pre;
			delete cur;

			return iterator(nex);
		}

		//����insert �� erase����ʵ��ͷ��ͷɾ β��βɾֱ�����þ���
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
			erase(--end());//����Ҫ--end()
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

		void clear() {//������н��(����ͷ���) �������Ը��� 
			/*Node* cur = _head ->next;
			Node* tmp = cur;
			while (cur != _head) {
				cur = cur->next;
				delete tmp;
				tmp = cur;
			}*/

			iterator it = begin();
			while (it != end()) {
				it = erase(it);//����������ʧЧ �������erase�᷵��һ��ɾ�������һ����Ч������
			}
		}
	};
}
