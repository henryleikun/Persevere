#pragma once
#include <iostream>
#include <cassert>

using namespace std;

//����SGI(g++)ʹ�õ�STL�汾 ȥʵ�����vector
//�����ʵ�ֲ�����һ��string�Ǹ��������ģ���ʵ���� ����Ҫʹ��ģ�嶨��
//ģ���ʵ�ֺ�����Ҫ����һ���ļ���

//ע��� insert��eraseʵ�ֵ�ʱ�������ʧЧ������
//Ұָ�� ����ԭ��Ԫ��λ�ö�����Ԫ��λ�� ��������λ��

//�漰����� �Ͳ�Ҫȥʹ��memcpy�� memcpy���ʾ���һ��ǳ����

//���ں����β� ����ֵ�� ����vector<T> ����vector ���������������� �ĸ�����
//������ ���� ��vector<T>���һ�Ҫ�����ض��� ģ�������� 
//����������� ����vector<T>���� �ɶ���Ҳǿ
namespace Henry {

	template<typename T>
	class vector {
	private:
		//��׼vector��������ָ��������˳���
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


		//�������� ���ϵ�д�� ��������ִ�д�� ���赶ɱ�ˡ�
		//����

		void swap(vector<T>& rhs) {
			//��������������� ���б�׼��ĵ���
			std::swap(_start, rhs._start);
			std::swap(_finish, rhs._finish);
			std::swap(_end, rhs._end);
		}

		vector(const vector<T>& rhs) {
			vector<T> v(rhs._start, rhs._finish);//�������ȥ����rhs �ڽ���ɱ��
			swap(v);//ͨ����ʱ����v���ʵ���� ����
			//v�����Լ����������� ���ͷ� �ǿ���ʱ�ռ�
		}

		vector<T>& operator=(const vector<T>& rhs) {
			vector<T> v(rhs._start, rhs._finish);
			//����������Լ���ֵ�Լ�Ҳ�޷�
			swap(v);
			return *this;
		}

		//����һ�����������乹�캯��
	    // [first, last)  ��������캯����һ��ģ�庯�� ���ݴ�����β����ƶ϶�Ӧ����
		//��ָ�� ���ǵ����� �����±궼����
		//ע��������Ҳ�Ǹ����캯�� ��ζ�� ��Ҫ�Գ�Ա�������г�ʼ��
		//ע�������� ��������� �Զ����Ǽ�����Ա������ʼ���� ʵ����
		//��ǰ��Ҳ˵�� Ĭ�Ϲ��캯�� �����������ǲ�������� �����Ǳ��������㴦����
		//�Ͻ���� �����ȳ�ʼ���б����¡�
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


		//resize��reserve��string�Ĵ���һ��
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

		//Ϊ��ӭ��ģ�� �������� Ҳ������Ĭ�Ϲ���
		void resize(int n,const T& val = T()) {//val��ʼ����Ԫ��
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
			if (_finish == _end) {//����(����) 2����
				int newcapacity = capacity() == 0 ? 4 : 2 * capacity();
				reserve(newcapacity);
				//reserve���洦����ָ��Ĺ�ϵ
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

			if (_finish == _end) {//���� 2����
				int newcapacity = capacity() == 0 ? 4 : 2 * capacity();
				size_t sz = pos - _start;

				reserve(newcapacity);
				//reserve���洦����ָ��Ĺ�ϵ
				//����ע��������� pos����ָ��ԭ����λ�� ����Ҫ����pos ��posָ���¿ռ������
				//_start��λ�ô�  ����һ�ֵ�����ʧЧ��Ұָ�룩

				pos = _start + sz;
			}

			//����
			T* move = _finish - 1;

			while (move - pos >= 0) {
				*(move + 1) = *move;
				--move;
			}
			_finish++;

			*pos = val;
			return pos;//����ָ�������Ԫ��λ�õ�pos
		}

		iterator erase(iterator pos) { //vs(��ͬ��STLʵ��) erase��ǿ�Ƽ�� ʹ�����pos��ֹʹ��
			       //g++û��ǿ�Ƽ�� ��Ҳ�б������ ����ǿ�Ƽ����� 
				   //��vs��ǿ�Ƽ���ǽ����ڵ��������Զ������� ��������ԭ��ָ�� ֪������
				   //����ǿ�Ƽ�� Ϊʲôǿ�Ƽ����� ��erase�������һ��Ԫ�� �㻹�������
				   // �������ռ� ����ǷǷ������� ��������ͼ�סerase֮��ĵ�����������ʹ����
		    assert(!empty());
			assert(pos < _finish);

			T* move = pos;

			while (move + 1 != _finish) {
				*move = *(move + 1);
				move++;
 			}
			
			--_finish;

			return pos;
			//����ɾ��Ԫ�ص���һ��Ԫ�ص�λ�� ����vs�ı�׼��������� �ο�ɾ�����е�ż�� ��ż��
			//�������ֵ���� ɾ����Ҫ���µ�������ֵ ����һ�仰 erase��ĵ����� ����ʧЧ��
		}



	};
}