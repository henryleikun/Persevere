#define _CRT_SECURE_NO_WARNINGS 1

#include "snake.h"

void test() {
  Snake snake = {0};
  GameStart(&snake);
  GameRun(&snake);
  GameEnd(&snake);

}


int main() {
	setlocale(LC_ALL, "");//�ַ������ػ� Ĭ�ϵڶ���������"C"

	//int choice = 0;
	//do {
		test();
		//SetPos(43, 32);
		//printf("����һ���𣿣�Y/N��:");
		//choice = getchar();
		//getchar();
	//} while (choice == 'Y' || choice == 'y');

	return 0;
}