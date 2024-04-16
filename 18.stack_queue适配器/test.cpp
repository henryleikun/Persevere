#define _CRT_SECURE_NO_WARNINGS 1

#include <string>
#include "stack.h"
#include "queue.h"

using namespace Henry;


void Test() {
	stack<int, list<int>> st;

	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.push(5);

	while (!st.empty()) {
		cout << st.top() << " ";
		st.pop();
	}

	queue<int, list<int>> que;
	que.push(1);
	que.push(2);
	que.push(3);
	que.push(4);
	que.push(5);

	while (!que.empty()) {
		cout << que.front() << " ";
		que.pop();
	}

	que.push(100);
	cout << que.back();
}

bool Is_bigger_priority(char a, char top) {//判断a是否大于b的优先级
	if ((a == '*' || a == '/') && (top == '+' || top == '-'))
		return true;
    
	if (top == '(')
		return true;

	return false;
}


int main1() {
	//Test();
	//stack练习 逆波兰表达式 
	//这里输入的中缀表达式 简便下运算 不带空格(1 + 2 * (3 / 5))这种
	//带空格就在遍历字符串的时候 跳过字符就行 这里搞一个不带空格算数运算式
	//带空格可以去区分 负数与负号 这里实现的就是对正整数的运算

	//思路 先将中缀转成后缀 再将后缀带入stack中实现运算
	//中缀转后缀 数字 进入字符串 符号 栈为空 进栈不为空 与栈顶元素比较优先级
	//比其低或相等就将栈顶元素出栈加到字符串中 继续和栈顶比较优先级 直到栈为空或高于其优先级进栈
	//遇到左括号 直接进栈 将其看作最低优先级的运算符 遇到右括号(不进栈） 拿出栈顶运算符
	//和栈顶元素比较优先级 大就进字符串 小就出栈 直到遇到左括号
	//后缀计算 将后缀数字进入栈碰到 运算符 确定是哪个 取栈中两个元素进行计算 再将结果入栈
	//最后栈中只剩一个数 那就是结果

	string str1;
	cout << "中缀表达式(不带空格):";
	getline(cin, str1);

	stack<char> st1;//转后缀存储运算符

	//str2存储后缀表达式
	string str2;
	for (int i = 0; i < str1.size(); i++) {
		if (str1[i] >= '0' && str1[i] <= '9') {//数字进字符串
			str2 += str1[i];
		}
		else {//符号  
			if (st1.empty()) {
			  st1.push(str1[i]);
			  continue;
			}

			if (str1[i] == '(') {
				st1.push(str1[i]);
				continue;
			}

			if (str1[i] == ')') {
				//把(和)之间的运算符 依次输出到字符串里
				while (st1.top() != '(') {
					str2 += st1.top();
					st1.pop();
				}

				st1.pop();
				continue;
			}


			//str1[i]是加减乘除 不是( 或 )
			char b = st1.top();
			if (Is_bigger_priority(str1[i], b)) {//运算符优先级高于栈顶的
				st1.push(str1[i]);
			}
			else {
				while (!Is_bigger_priority(str1[i], b)) {//不高于栈顶元素就入字符串
					        //并且接着判断直到 碰到低于str1[i]的优先级的 或者是栈空
					//当b = '('时 b时优先级最小的 一定不会进循环
					st1.pop();
					str2 += b;
					if (st1.empty()) {//为空 push进去 然后判断下一个字符
						break;
					}

					b = st1.top();
				}

				st1.push(str1[i]);
			}
		}
	}//此时 st1里还有余下的符号
	while (!st1.empty()) {
		str2 += st1.top();
		st1.pop();
	}

	//此时str2已经是后缀字符串 接下来进行 后缀计算
	stack<int> st2;//进行后缀计算的栈

	for (int i = 0; i < str2.size(); i++) {
		char temp = str2[i];

		if (temp == '+' || temp == '-'
			|| temp == '*' || temp == '/') {//不能str[0] == 做判断 负数和负号
			int a = st2.top();
			st2.pop();
			int b = st2.top();
			st2.pop();
			//先取得右操作数 再取左操作数

			switch (temp) {
			case '+':
				st2.push(b + a);
				break;
			case '*':
				st2.push(b * a);
				break;
			case '-':
				st2.push(b - a);
				break;
			case '/':
				st2.push(b / a);
				break;
			}
		}
		else {
			st2.push(temp - '0');
		}
	}


	cout << "结果是:" << st2.top() << endl;
	return 0;
}

int Ack(int m, int n) {
	if (m == 0)
		return n + 1;
	else if (n == 0)
		return Ack(m - 1, 1);
	else
		return Ack(m - 1, Ack(m, n - 1));
}

int Ack_noR(int m, int n) {
	stack<int, vector<int>> st;
	st.push(m);
	st.push(n);


	while (st.size() != 1) {//只有一个元素的时候即是结果
		int right = st.top(); //n
		st.pop();
		int left = st.top();  //m
		st.pop();
		//Ack(left,right)

		if (left == 0) {
			st.push(right + 1);
		}
		else if (right == 0) {
			st.push(left - 1);
			st.push(1);
		}
		else {
			st.push(left - 1);
			st.push(left);
			st.push(right - 1);
		}
	}

	return st.top();
}


int main() {
	cout << Ack(2, 1) << endl;
	cout << Ack_noR(2, 1) << endl;

	return 0;
}












