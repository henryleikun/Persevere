#pragma once
//���ȼ����� ��ʵ���Ƕѣ������ȼ������ȼ���Ӧ���С�ѣ������ȼ�����Ҳ��������
//����Ҫ�漰��STL�������������һ�����ԣ��º��� �º����������C�����и��ӵĺ���ָ��
//��C���Ե�qsort�����
//void qsort (void* base, size_t num, size_t size,int (*compar)(const void*, const void*));
//������������һ������ָ��ָ��һ���ܹ��ȴ�С��������qsort���ٻص������Ӷ�ʵ�֡��Զ��巺�͡������ĸ���
//������ָ��̫������ ��ʱ��Ҫ�������� C++�ĺ�������(�º���)������������˺ܺõĴ��� 
//����������()����� ʵ��һ�������ϵĺ��� ʵ�����ǵ��ó�Ա���� ������Ҫ��ֻ��һ��������������Ķ���
//�����ȼ����������Ҫһ���º�����ȷ���Ǹ߻��ǵ����ȼ�
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;


//�����Ƕ� �ѵĽӿ� pop push top empty size
//���ȼ�������Ϊ��������������������ӿ�Ҫ���� ��Ҫ֧���±����
//������һ��С��Ϊ��
namespace Henry {
	template<class T>//����º������� �ṹ����ʺ�
	struct less {
		bool operator()(const T& x, const T& y) {
			return x < y;//���T���Զ������� ȷ���������˶�Ӧ�ıȽ������
		}
	};

	template<class T>
	struct greater {
		bool operator()(const T& x, const T& y) {
			return x > y;
		}
	};

	//Ĭ�ϵײ�ʹ��vector �º�����С�� ����ʵ����� ����Ĭ����less����ʵʵ�ֵ��Ǵ��(������������)
	//�������� ���������less��ӦС�� ��ʵֻҪ�ı�Ƚϲ�������˳�����
	//�����ﰴ��������
	//��ʵ���ģ������ֲ������ Ӧ��compare���м� ��Ϊ Containerһ�㶼�����1����Compare�ᾭ����
	template<class T, class Container = vector<T>, class Compare = less<T>>
	class priority_queue {
	private:
		Container con;
	public:
		void adjust_up(int child) {//���ϵ���(pushʱ����)
			//assert(child >= 0 && child < con.size());

			int parent = (child - 1) / 2;

			while (child > 0) {

				//if (con[parent] > con[child]) {//����С��
				if (Compare()(con[parent], con[child])) {//�������� ��ΪĬ����less��Ӧ�Ǵ��
					swap(con[parent], con[child]);

					child = parent;
					parent = (child - 1) / 2;
				}
				else {
					break;
				}
			}
		}

		void adjust_down(int parent) {//���µ���(popʱ���ã����µ������ѿ���Ҳ��)
			//assert(parent >= 0 && parent < con.size());//����ֻ��Ϊ���Ͻ�
            //��Ԫ��ֻ��һ����ʱ����ִ��pop�������� �����ʵҲû��Ҫ������

			int child = parent * 2 + 1;//Ĭ��ʹ������ С�� ������������С�ıȸ���

			while (child < con.size()) {//����con.size()�ķ���ֵ��size_t

				                                  //con[child + 1] < con[child]С�� 
				if (child + 1 < con.size() - 1 && Compare()(con[child],con[child + 1])) {
					++child;
				}//�ҳ�����������Compare��

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