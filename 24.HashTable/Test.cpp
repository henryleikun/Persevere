#include "Myunordered_map.h"
#include "Myunordered_set.h"
//#include <unordered_map>
//using namespace std;
using namespace Henry;

void Test1() {//����̽��
	/*HashTable<string, string> hash;
	hash.Insert(make_pair("Insert", "����"));
	hash.Insert(make_pair("left", "��"));
	hash.Insert(make_pair("right", "��"));
	hash.Insert(make_pair("erase", "ɾ"));
	hash.Insert(make_pair("empty", "��"));*/


	Linear_explore::HashTable<int, int> hash;
	hash.Insert(make_pair(1, 1));
	hash.Insert(make_pair(4, 4));
	hash.Insert(make_pair(14, 14));
	hash.Insert(make_pair(24, 24));
	hash.Insert(make_pair(6, 6));
	hash.Insert(make_pair(9, 9));

	//�������ݵ�
	hash.Insert(make_pair(26, 26));
	hash.Insert(make_pair(7, 7));
}

void Test2() {//��ϣͰ
	Hash_Box::HashTable<int, int> hash;

	hash.Insert(make_pair(1, 1));
	hash.Insert(make_pair(4, 4));
	hash.Insert(make_pair(14, 14));
	hash.Insert(make_pair(24, 24));
	hash.Insert(make_pair(6, 6));
	hash.Insert(make_pair(9, 9));

	//hash.some();

	//�漰���� ע�⸺��������1
	hash.Insert(make_pair(26, 26));
	hash.Insert(make_pair(29, 29));
	hash.Insert(make_pair(34, 34));
	hash.Insert(make_pair(10, 10));
	hash.Insert(make_pair(11, 11));//��һ����
	hash.some();
}

//int main() {
//	//Test1();
//	//Test2();
//	//unordered_map<int, int> umap;
//	//umap.insert(make_pair(1, 1));
//	//umap.insert(make_pair(2, 2));
//	//umap.insert(make_pair(3, 3));
//
//	//unordered_map<int, int>::iterator it = umap.begin();
//	//it++;ָ��end ����++
//	//it--;Ϊ�վͲ���-- Ҳ���ǵ��������ס ֻ��������ҿ����������ƶ�
//
//	return 0;
//}

int main() {
	unordered_map<int, int> umap;
	umap.insert(make_pair(1, 1));
	umap.insert(make_pair(2, 2));
	umap.insert(make_pair(3, 3));

	//unordered_map<int, int>::iterator it = umap.end();
	/*it--;
	for (; it != umap.begin(); --it) {
		cout << (*it).first <<":" << (*it).second << endl;
	}*/

	unordered_map<int, int>::iterator it = umap.begin();

	//����ʵ������Ĺ�ϣ������ǰ��ղ���˳������� ����ʵ�����ٹ�ϣ����������һ��
	//��ָ��ȥά�������Ԫ��˳���γ�һ�� �����õ����� ������
	for (; it != umap.end(); ++it) {
		cout << (*it).first << ":" << (*it).second << endl;
	}
	cout << endl;

	umap[4] = 4;
    
	it = umap.begin();
	for (; it != umap.end(); ++it) {
		cout << (*it).first << ":" << (*it).second << endl;
	}

	cout << endl;

	cout << (umap.find(4))->first << endl;

	umap.erase(2);
	it = umap.begin();
	for (; it != umap.end(); ++it) {
		cout << (*it).first << ":" << (*it).second << endl;
	}

	return 0;
}