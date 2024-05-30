#include "Mymap.h"
#include "Myset.h"
using namespace Henry;

void Test_Myset() {
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

	s.inorder();

	if (s.find(33)) {
		cout << "�ҵ���" << endl;
	 }
}

void Test_Mymap() {
	int a[] = { 8,9,5,0,10,20,50,11,33,90 };

	map<int, int> m;//key-value�͵ĺ����ʵ�� ȥ�� ���� ����
	for (auto e : a) {
		m.insert(make_pair(e, e));
	}

	map<int, int>::iterator it;
	for (it = m.begin(); it != m.end(); it++) {
		cout << it->first << " ";
	}

	cout << endl;

	it = m.find(33);//�ҵ���key �ⲻ����map����set ���ҵĹؼ���Զ��keyֵ û�ҵ�����end()(nullptr)
	cout << it->first << endl;

	m[20] = 21;
	m[22];//��������
	m[22] = 22;

	for (it = m.begin(); it != m.end(); it++) {
		cout << it->first << ":" << it->second << endl;
	}
}

void Test_Mymap2() {
	string strs[] = { "ƻ��", "����", "ƻ��", "ӣ��", "ƻ��", "ӣ��", "ƻ��", "ӣ��", "ƻ��" };

	map<string, int> countMap;
	map<string, int>::iterator it;

	for (auto e : strs) {
		it = countMap.find(e);
		if (it == countMap.end()) {//û�ҵ�
			countMap[e]++;//����+�޸�
		}
		else {//�ҵ�
			it->second++;
		}
	}

	for (it = countMap.begin(); it != countMap.end(); it++) {
		cout << it->first << ":" << it->second << endl;
	}
}

int main() {
	//Test_Myset();
	//Test_Mymap();
	Test_Mymap2();

	return 0;
}