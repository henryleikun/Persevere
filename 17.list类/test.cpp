#pragma once

#include <iostream>
//#include <list>
#include "list.h"

using namespace Henry;

int main() {
	list<int> ls;
	ls.push_back(1);
	ls.push_back(2);
	ls.push_back(3);
	ls.push_back(4);
	ls.push_back(5);

	list<int>::iterator it(ls.begin());

	/*for (; it != ls.end(); it++) {
		cout << *it << " ";
	}*/

	for (auto e : ls) {//�ײ��ǵ�����
		cout << e << " ";
	}
	cout << endl;

	const list<int> ll(ls.begin(),ls.end());
	list<int>::const_iterator constit = ll.begin();//���ö�Ӧconst�汾

	//*constit = 1; ������

	ls.pop_back();
	ls.pop_front();

	for (auto e : ls) {//�ײ��ǵ�����
		cout << e << " ";
	}
	cout << endl;

	ls.push_front(1);
	for (auto e : ls) {//�ײ��ǵ�����
		cout << e << " ";
	}
	cout << endl;

	struct S {
		int a;

		S(int _a = 0) :a(_a) {

		}
	};

	list<S> lls;
	lls.push_back(1);
	lls.push_back(2);
	lls.push_back(3);

	list<S>::iterator sit = lls.begin();

	cout << (*sit).a << endl;//�㲻��ֱ��*sit �Զ������� û������������
	//��Ȼ����������ָ�� ���� ���� sit->a
	//����ʵ�ֵ�-> sit->a ==>  sit.operator->()->a(sit->->a)��Ϊ�˴���Ŀɶ��� �Լ���ָ��
	//��£ ����ʡ�����м��->
	sit++;
	cout << sit->a << endl;
	const list<S> clls(lls.begin(),lls.end());
	list<S>::const_iterator csit = clls.begin();
	//csit->a = 1; ������

	return 0;
}