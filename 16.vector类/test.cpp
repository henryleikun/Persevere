#define _CRT_SECURE_NO_WARNINGS 1

#include "vector.h"
#include <algorithm>

using namespace Henry;

void Print(const vector<int>& v) {
	for (auto e : v) {
		cout << e << " ";
	}

	cout << endl;
}

int main() {
	vector<int> v1(4, 6);
	vector<int> v2(v1);
	Print(v1);

	v2.push_back(3);
	v2.push_back(4);
	v2.push_back(5);
	v2.push_back(7);
	Print(v2);

	vector<int>::iterator it = find(v2.begin(), v2.end(),3);
	it = v2.erase(it);
	Print(v2);

	it = v2.insert(it, 3);
	Print(v2);

	v2.pop_back();
	Print(v2);

	v2.resize(10);
	cout << v2.size() << endl;
	v2.reserve(1);
	cout << v2.capacity() << endl;

	vector<int> v3 = v2;
	Print(v3);
	return 0;
}