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

bool Is_bigger_priority(char a, char top) {//�ж�a�Ƿ����b�����ȼ�
	if ((a == '*' || a == '/') && (top == '+' || top == '-'))
		return true;
    
	if (top == '(')
		return true;

	return false;
}


int main1() {
	//Test();
	//stack��ϰ �沨�����ʽ 
	//�����������׺���ʽ ��������� �����ո�(1 + 2 * (3 / 5))����
	//���ո���ڱ����ַ�����ʱ�� �����ַ����� �����һ�������ո���������ʽ
	//���ո����ȥ���� �����븺�� ����ʵ�ֵľ��Ƕ�������������

	//˼· �Ƚ���׺ת�ɺ�׺ �ٽ���׺����stack��ʵ������
	//��׺ת��׺ ���� �����ַ��� ���� ջΪ�� ��ջ��Ϊ�� ��ջ��Ԫ�رȽ����ȼ�
	//����ͻ���Ⱦͽ�ջ��Ԫ�س�ջ�ӵ��ַ����� ������ջ���Ƚ����ȼ� ֱ��ջΪ�ջ���������ȼ���ջ
	//���������� ֱ�ӽ�ջ ���俴��������ȼ�������� ����������(����ջ�� �ó�ջ�������
	//��ջ��Ԫ�رȽ����ȼ� ��ͽ��ַ��� С�ͳ�ջ ֱ������������
	//��׺���� ����׺���ֽ���ջ���� ����� ȷ�����ĸ� ȡջ������Ԫ�ؽ��м��� �ٽ������ջ
	//���ջ��ֻʣһ���� �Ǿ��ǽ��

	string str1;
	cout << "��׺���ʽ(�����ո�):";
	getline(cin, str1);

	stack<char> st1;//ת��׺�洢�����

	//str2�洢��׺���ʽ
	string str2;
	for (int i = 0; i < str1.size(); i++) {
		if (str1[i] >= '0' && str1[i] <= '9') {//���ֽ��ַ���
			str2 += str1[i];
		}
		else {//����  
			if (st1.empty()) {
			  st1.push(str1[i]);
			  continue;
			}

			if (str1[i] == '(') {
				st1.push(str1[i]);
				continue;
			}

			if (str1[i] == ')') {
				//��(��)֮�������� ����������ַ�����
				while (st1.top() != '(') {
					str2 += st1.top();
					st1.pop();
				}

				st1.pop();
				continue;
			}


			//str1[i]�ǼӼ��˳� ����( �� )
			char b = st1.top();
			if (Is_bigger_priority(str1[i], b)) {//��������ȼ�����ջ����
				st1.push(str1[i]);
			}
			else {
				while (!Is_bigger_priority(str1[i], b)) {//������ջ��Ԫ�ؾ����ַ���
					        //���ҽ����ж�ֱ�� ��������str1[i]�����ȼ��� ������ջ��
					//��b = '('ʱ bʱ���ȼ���С�� һ�������ѭ��
					st1.pop();
					str2 += b;
					if (st1.empty()) {//Ϊ�� push��ȥ Ȼ���ж���һ���ַ�
						break;
					}

					b = st1.top();
				}

				st1.push(str1[i]);
			}
		}
	}//��ʱ st1�ﻹ�����µķ���
	while (!st1.empty()) {
		str2 += st1.top();
		st1.pop();
	}

	//��ʱstr2�Ѿ��Ǻ�׺�ַ��� ���������� ��׺����
	stack<int> st2;//���к�׺�����ջ

	for (int i = 0; i < str2.size(); i++) {
		char temp = str2[i];

		if (temp == '+' || temp == '-'
			|| temp == '*' || temp == '/') {//����str[0] == ���ж� �����͸���
			int a = st2.top();
			st2.pop();
			int b = st2.top();
			st2.pop();
			//��ȡ���Ҳ����� ��ȡ�������

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


	cout << "�����:" << st2.top() << endl;
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


	while (st.size() != 1) {//ֻ��һ��Ԫ�ص�ʱ���ǽ��
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












