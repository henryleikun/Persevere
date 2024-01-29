#define _CRT_SECURE_NO_WARNINGS 1

#include "snake.h"

void test() {
  Snake snake = {0};
  GameStart(&snake);
  GameRun(&snake);
  GameEnd(&snake);

}


int main() {
	setlocale(LC_ALL, "");//字符集本地化 默认第二个参数是"C"

	//int choice = 0;
	//do {
		test();
		//SetPos(43, 32);
		//printf("再来一局吗？（Y/N）:");
		//choice = getchar();
		//getchar();
	//} while (choice == 'Y' || choice == 'y');

	return 0;
}