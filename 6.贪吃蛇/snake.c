#define _CRT_SECURE_NO_WARNINGS 1
#include "snake.h"

void SetPos(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = {x,y};//COORD是一个结构体 存储控制台坐标信息  x列 y行
	SetConsoleCursorPosition(handle, pos);
}//控制台坐标从0开始

void Welcome() {
	//你的控制台是60行100列
	SetPos(40,10);
	printf("欢迎来到贪吃蛇游戏!\n");
	SetPos(45, 20);
	printf("开始游戏\n");
	//SetPos(90, 25);
	//printf("退出游戏\n");

	SetPos(43, 30);
	system("pause");
	system("cls");

	SetPos(35, 20);
	printf("按 W A S D控制蛇的移动 Q E控制蛇的速度");
	SetPos(35, 21);
	printf("Q加速 E减速");
	SetPos(40, 30);
	system("pause");
	system("cls");
}

void CreatMap() {
	//注意 本程序涉及到宽字符 占两个字节(蛇的身体，食物,墙) 
	//在创建地图时 行和列 搞成偶数 你有100列 60行  
	 
	//上墙 
	SetPos(0, 13);
	for(int i = 0; i < 50; i++) {
		wprintf(L"%lc",L'▲');
	}

	//下墙
	SetPos(0, 59);
	for (int i = 0; i < 50; i++) {
		wprintf(L"%lc", L'▼');
	}

	//左墙
	for (int i = 14; i < 59; i++) {
		SetPos(0, i);
		wprintf(L"%lc", L'■');
	}

	//右墙
	for (int i = 14; i < 59; i++) {
		SetPos(98, i);
		wprintf(L"%lc", L'■');
	}

}

void InitiSnake(Snake* ps) {//头插创建链表(蛇身)
	//墙 0~98列 14~58行  
	//默认蛇是在 40~50列  17行(蛇身体对于横着的位置一个是占两个字节 竖着也是两个字节)
	//但竖着的单位就是两个字节 默认长度5个SnakeNode

	ps->psnake = (SnakeNode*)malloc(sizeof(SnakeNode));
	if (ps->psnake == NULL) {
		perror("malloc failed!\n");
		return;
	}

	ps->psnake->x = 40;
	ps->psnake->y = 17;
	ps->psnake->next = NULL;
	SnakeNode* cur = NULL;
	for (int i = 1; i < 5; i++) {
		cur = (SnakeNode*)malloc(sizeof(SnakeNode));
		if (cur==NULL) {
			perror("malloc failed!\n");
			return;
		}

		cur->x = 40 + i * 2;
		cur->y = 17;
		cur->next = ps->psnake;
		ps->psnake = cur;
	}

	//打印蛇身
	SnakeNode* tmp = ps->psnake;
	while (tmp) {
		SetPos(tmp->x, tmp->y);
		wprintf(L"%lc", L'●');
		tmp = tmp->next;
	}

	//初始化其他信息
	ps->dir = RIGHT;//默认向右走
	ps->pfood = NULL;
	ps->scores = 0;
	ps->score_per_food = 10;//默认一个食物10分
	ps->sleeptime = 200;//200ms(0.2s)的睡眠时间
	ps->state = OK;
	 
}

void CreatFood(Snake* ps) {
	//创建的食物是随机的 注意食物不能在墙外 食物不能和蛇的身体重合 且列坐标是偶数
	//这样与蛇的身体才不会有间隙
	
	int x_temp = 0;
	int y_temp = 0;
	
   again:
	do {
		x_temp = rand() % 95 + 2;//x 在2~96范围内
		y_temp = rand() % 45 + 14;//y在14~58范围内
	} while (x_temp % 2 != 0);//出来的x，y在墙内且列是偶数 但还要确保不在蛇的身体内

	SnakeNode* cur = ps->psnake;
	while (cur) {
		if (cur->x == x_temp && cur->y == y_temp) {
			goto again;
		}//如果在蛇的身体里 那就回去在创建一个
		cur = cur->next;
	}

	//打印食物
	SnakeNode* food = (SnakeNode*)malloc(sizeof(SnakeNode));
	if (food==NULL) {
		perror("malloc failed!\n");
		return;
	}

	food->x = x_temp;
	food->y = y_temp;
	food->next = NULL;
	ps->pfood = food;

	SetPos(ps->pfood->x, ps->pfood->y);
	wprintf(L"%lc", L'★');
}

void GameStart(Snake* ps) {
	//设置控制台大小
	system("mode con cols=100 lines=60");//控制台看成坐标来自定义大小 列100 行60
	system("title 贪吃蛇");//控制台名称

	//隐藏控制台光标
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//获取当前控制台操作权限(句柄)
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(handle, &cursor);//获取控制台光标信息 放到cursor里
	//cursor是一个结构体 一个记录光标显示的比例 一个是是否隐藏(bool)	
	cursor.bVisible = false;//隐藏光标
	SetConsoleCursorInfo(handle, &cursor);//将刚才的设置 实现出来

	//打印欢迎界面
	Welcome();

	//打印地图
	CreatMap();

	//初始化蛇
	InitiSnake(ps);

	//创建食物
	CreatFood(ps);
}

void PrintHelpInfo() {
	SetPos(0, 0);
	printf("************************************\n");
	printf("* 不能撞到墙和自己                 *\n");
	printf("* Q加速 E减速 不同速度对应不同分值 *\n");
	printf("* 按ESC退出游戏 SPACE暂停游戏      *\n");
	printf("*                        by Henry  *\n");
	printf("************************************\n");
}

void Pause() {
	while (1) {
		Sleep(200);
		if (KEY_PRESS(VK_SPACE))
			break;
	}
}

void KillbyWall(Snake* ps) {//只看头
	//墙上下边范围 13  59 左右边范围0 98
	SnakeNode* cur = ps->psnake;
		if (cur->x == 0 || cur->x == 98 ||
			cur->y == 13 || cur->y == 59) {
			ps->state = KILL_BY_WALL;
			return;
		}

}

void KillbySelf(Snake* ps) {
	SnakeNode* cur = ps->psnake->next->next;//从第三个结点开始检查
	SnakeNode* head = ps->psnake;
	while (cur) {
		if (cur->x == head->x && cur->y == head->y) {
			ps->state = KILL_BY_SELF;
			return;
		}

		cur = cur->next;
	}
}


void SnakeMove(Snake* ps) {//走 需要知道方向 在对应方向开辟节点
	//与蛇连接 两种情况 对应方向上 刚好是食物 那就将新节点头插成为蛇头 
	// 释放旧食物结点 新建食物 打印蛇
	//不是也头插蛇头 将尾结点释放 并将原尾打印成空字符

	SnakeNode* newnode = (SnakeNode*)malloc(sizeof(SnakeNode));

	if (newnode == NULL) {
		perror("malloc failed!\n");
		return;
	}
	
	newnode->next = NULL;

	switch (ps->dir) {
	case UP:                       //注意列的单位是2
		newnode->x = ps->psnake->x;//向上 列不变 行减一
		newnode->y = ps->psnake->y - 1;
		break;
	case DOWN:
		newnode->x = ps->psnake->x;
		newnode->y = ps->psnake->y + 1;
		break;
	case LEFT:
		newnode->x = ps->psnake->x-2;
		newnode->y = ps->psnake->y;
		break;
	case RIGHT:
		newnode->x = ps->psnake->x+2;
		newnode->y = ps->psnake->y;
		break;
	}//新节点的坐标确定

	//判断新节点是否是食物
	if (newnode->x == ps->pfood->x && newnode->y == ps->pfood->y) {//如果是食物
		newnode->next = ps->psnake;
		ps->psnake = newnode;//头插成为蛇头

		//打印蛇
		while (newnode) {
			SetPos(newnode->x, newnode->y);
			wprintf(L"%lc", L'●');
			newnode = newnode->next;
		}
		//更新分值
		ps->scores += ps->score_per_food;

		free(ps->pfood);//释放原食物结点
		CreatFood(ps);//创建新食物
	}
	else {//不是食物
		newnode->next = ps->psnake;
		ps->psnake = newnode;//先头插再说

		while (newnode->next->next != NULL) {
			newnode = newnode->next;
		}//找倒数第二个结点

		SetPos(newnode->next->x, newnode->next->y);
		printf("  ");

		free(newnode->next);
		newnode->next = NULL;

		//打印蛇
		newnode = ps->psnake;
		while (newnode) {
			SetPos(newnode->x, newnode->y);
			wprintf(L"%lc", L'●');
			newnode = newnode->next;
		}

	}

	//判断是否撞墙或者撞到自己
	KillbyWall(ps);

	KillbySelf(ps);
}

void GameRun(Snake* ps) {//这是个循环 
	//整体思路是先获取按键信息 根据按键更新ps里的数据
	//接着进行走动和休眠来完成 移动
	PrintHelpInfo();

	do {
		//当前分数情况
		SetPos(43, 10);
		printf("当前得分：%d", ps->scores);
		SetPos(83, 12);
		printf("每个食物分数：%2d", ps->score_per_food);
		
		//检测按键
		if (KEY_PRESS(0x57) && ps->dir != DOWN) {//按W键 他不能往下走 其余类似
			ps->dir = UP;
		}
		else if (KEY_PRESS(0x53) && ps->dir != UP) {
			ps->dir = DOWN;
		}
		else if (KEY_PRESS(0X41) && ps->dir != RIGHT) {
			ps->dir = LEFT;
		}
		else if (KEY_PRESS(0X44) && ps->dir != LEFT) {
			ps->dir = RIGHT;
		}
		else if (KEY_PRESS(VK_SPACE)) {//空格 暂停
			Pause();
		}
		else if (KEY_PRESS(VK_ESCAPE)) {//ESC退出游戏
			ps->state = ESC;
			break;
		}
		else if(KEY_PRESS(0x51)){//Q加速 睡眠时间变小(>=40) 食物得分加2
			if (ps->sleeptime > 40) {
				ps->sleeptime -= 20;
				ps->score_per_food += 2;
			}
		}
		else if (KEY_PRESS(0x45)) {//E减速 睡眠时间变长 食物得分减2(>=20)
			if (ps->score_per_food > 2) {
				ps->sleeptime += 20;
				ps->score_per_food -= 2;
			}
		}

		//睡一下
		Sleep(ps->sleeptime);

		//走一下
		SnakeMove(ps);


	} while (ps->state == OK);


}

void GameEnd(Snake* ps) {//主要释放蛇的结点和食物
		SetPos(45, 30);
		printf("游戏结束！");
		SetPos(42, 31);
		printf("您的总分是：%d", ps->scores);

		SnakeNode* del = ps->psnake;
		SnakeNode* cur;
		while (del) {
			cur = del;
			del = del->next;
			free(cur);
		}

		ps->psnake = NULL;
		free(ps->pfood);

		SetPos(0, 58);

}