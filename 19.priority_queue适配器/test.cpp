#define _CRT_SECURE_NO_WARNINGS 1
//#include <queue>//含priority_queue
//#include <iostream>
//#include <vector>
//#include <functional>//提供一些仿函数0
//using namespace std;

#include "priority_queue.h"
using namespace Henry;

int main() {
	//priority_queue<int, vector<int>, less<int>> pq;//大堆
	//pq.push(1);
	//pq.push(4);
	//pq.push(2);
	//pq.push(6);
	//pq.push(3);

	//while (!pq.empty()) {
	//	cout << pq.top() << endl;
	//	pq.pop();
	//}
	//less<int> ls;

	priority_queue<int> pq;//大堆
	pq.push(1);
	pq.push(4);
	pq.push(2);
	pq.push(6);
	pq.push(3);

	while (!pq.empty()) {
		cout << pq.top() << endl;
		pq.pop();
	}

	return 0;
}
