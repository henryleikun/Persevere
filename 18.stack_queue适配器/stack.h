#pragma once
//stack ��queue��ͬ��ǰ���vector��list�������������� ����
//STL�������(���� ������ �º��� �ռ������� ������ �㷨)���������
//�������������ȼ�����Ҳ��

//������ û�е�������ʵ�� ���������� �ֻ������ 220v�ĵ���б�ѹ �����ض��ĵ���
//��stackΪ�� stack��Ϊ������ ͨ�������ײ������Ľӿ���ʵ���Լ��Ľӿ�

//1.stack��һ��������������ר�����ھ��к���ȳ������������Ļ����У���ɾ��ֻ�ܴ�������һ�˽���
//Ԫ�صĲ�������ȡ������
//2. stack����Ϊ������������ʵ�ֵģ��������������Ƕ��ض����װ��Ϊ��ײ�����������ṩһ���ض�
//�ĳ�Ա������������Ԫ�أ����ض�����Ϊ��ײ�ģ�Ԫ���ض�������β��(��ջ��)��ѹ��͵�����
//3. stack�ĵײ������������κα�׼��������ģ�����һЩ�����ض��������࣬��Щ������Ӧ��֧������
//������
//empty���пղ���
//back����ȡβ��Ԫ�ز���
//push_back��β������Ԫ�ز���
//pop_back��β��ɾ��Ԫ�ز���
//4. ��׼����vector��deque��list��������Щ����Ĭ������£����û��Ϊstackָ���ض��ĵײ�������
//Ĭ�������ʹ��deque��

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include  <cassert>

using namespace std;

//Ĭ����deque��ʵ vector���ʺ�����ײ�����
//stackҪʵ�ֵĽӿ� pop push size top empty 
namespace Henry {
	template<class T,class Container = deque<T>>
	class stack {
	private:
		Container _con;
	public:
		stack() {//Ĭ�ϵ���_con�ĵ�Ĭ�Ϲ���
			     //����Ҳ���Զ�����
		}

		void push(const T& val) {
			_con.push_back(val);
		}

		void pop() {
			assert(!empty());
			_con.pop_back();
		}

		size_t size() {
			return _con.size();
		}

		bool empty() {
			return _con.size() == 0;
		}

		T& top() {
			assert(!empty());
			return _con.back();
		}
	};
}