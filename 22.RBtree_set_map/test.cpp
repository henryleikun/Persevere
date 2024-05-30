//#include "RBtree.h"
#include <iostream>
#include <utility>
#include <map>
#include <set>

using std::make_pair;
using std::cout;
using std::endl;
using std::map;
using std::set;
using std::multimap;
using std::multiset;//multi�������ظ�keyֵ

//void Test_Rbtree() {
//	RBtree<string, string> rb;
//	rb.Insert(make_pair("insert", "����"));
//	rb.Insert(make_pair("erase", "ɾ��"));
//	rb.Insert(make_pair("left", "��"));
//	rb.Insert(make_pair("right", "��"));
//	rb.Insert(make_pair("sort", "����"));
//
//	rb.Inorder();
//
//	cout << rb.size() << endl;
//	
//	if (rb.Is_RBtree()) {
//		cout << "�Ǻ����" << endl;
//	}
//}

void Test_stan_set() {
	int a[] = { 8,9,5,0,10,20,50,11,33,90 };

	set<int> s;//key�ͺ���� ȥ�� ���� ����
	
	for (auto e : a) {
		s.insert(e);
	}

	set<int>::iterator it;
	for (it = s.begin(); it != s.end(); it++) {
		cout << *it << " ";
	}

	cout << endl;

	set<int>::iterator it1,it2;
	//cout << s.count(5) << endl;//��5�м��� ��Ҫ���multi����� ����ֻ��0 1
	it1 = s.lower_bound(5);//lower_bound ���ص�һ��>=5�ĵ�����
	it2 = s.upper_bound(20);//upper_bound���ص�һ��>20�ĵ����� it2ָ��33
	s.erase(it1,it2);//ע��erase�ĵ���������������ҿ�

	for (it = s.begin(); it != s.end(); it++) {
		cout << *it << " ";
	}//0 33 50 90 
	cout << endl;

	set<int>::iterator it3;
	auto itr = s.equal_range(33);//����һ��pair<iterator,iterator>����ҿ�һ�����Ԫ�صķ�Χ
	//Ҳ����Ҫ��Ϊmultiϵ����׼�� �ڶ���������ָ�����һ����ͬԪ�ص���һ��
	//Ԫ�ز����ھ� ��������ָ��ͬһ��Ԫ�صĵ����� ���Ԫ����>���Ԫ�صĵ�һ�� û�оͱ���

	for (it3 = itr.first; it3 != itr.second; it3++)
		cout << *it3 << " ";
	cout << endl;

	it3 = itr.first;
	cout << *it3 << endl;
	it3 = itr.second;
	cout << *it3 << endl;
}

void Test_stan_map() {
	int a[] = { 8,9,5,0,10,20,50,11,33,90 };

	map<int, int> m;//key-value�͵ĺ����ʵ�� ȥ�� ���� ����
	for (auto e : a) {
		m.insert(make_pair(e,e));
	}

	map<int, int>::iterator it;
	for (it = m.begin(); it != m.end(); it++) {
		cout << it->first << " ";
	}

	cout << endl;

	it = m.find(33);//�ҵ���key �ⲻ����map����set ���ҵĹؼ���Զ��keyֵ û�ҵ�����end()(nullptr)
	cout << it->first << endl;
	//�������� ����set������� map������֮�� ������������[]
	//����[]���� ����keyֵ ���ض�Ӧvalue������ Ҳ��������Խ�˻����޸�valueֵ
	//������Ҳ��һ������Ĺ��� ���keyֵ������ �ǾͲ����ӦkeyֵvalueĬ��
	m[20] = 21;
	m[22];//��������
	m[22] = 22;

	for (it = m.begin(); it != m.end(); it++) {
		cout << it->first << ":" << it->second << endl; 
	}
}
//multiϵ�� �Ͳ�˵���� ���嶨�ƽӿ���set����Ҳ˵�� ��Ҫ�� �ܴ��ظ�Ԫ�� �ײ㻹���ܴ���ͬԪ�صĺ����ʵ��

int main1() {
	//Test_Rbtree();
	//Test_stan_set();
	//Test_stan_map();

	return 0;
}