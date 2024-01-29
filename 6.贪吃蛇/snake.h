#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

//使用C语言实现一个贪吃蛇项目
//技术：C语⾔函数、枚举、结构体、动态内存管理、预处理指令、链表、Win32API等
//实践性比较强 建议多多思考 知识多多归纳

#include <windows.h>//提供 windows操作系统提供的一些函数 win32API
//一些接收按键的函数 设置光标的函数等
#include <locale.h>//将字符集本地化 vs默认 字符集是C 不支持特定的一些宽字符

#include <stdlib.h>//system malloc等函数
#include <stdbool.h>
#include <stdio.h>

#define KEY_PRESS(VK) ( (GetAsyncKeyState(VK) & 0x1) ? 1 : 0 )

//定义一个宏
//将键盘上每个键的虚拟键值传递给函数，函数通过返回值来分辨按键的状态。
//GetAsyncKeyState 的返回值是short类型，在上⼀次调⽤ GetAsyncKeyState 函数后，如果
//返回的16位的short数据中，最⾼位是1，说明按键的状态是按下，如果最⾼是0，说明按键的状态是抬
//起；如果最低位被置为1则说明，该按键被按过，否则为0。
//如果我们要判断⼀个键是否被按过，可以检测GetAsyncKeyState返回值的最低值是否为1.

enum DIRECTION {//蛇运行方向的状态
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
};

enum STATE {
	OK=1,
	ESC,
	KILL_BY_WALL,
	KILL_BY_SELF
};



//链表实现蛇的身体结点
typedef struct SnakeNode {
	int x;
	int y;
	struct SnakeNode* next;
}SnakeNode;//每个节点 存储对应位置


typedef struct Snake {//用来维护 蛇自身
	SnakeNode* psnake;//指向蛇头 来控制整条蛇
	enum DIRECTION dir;//记录蛇的方向
	enum STATE state;//记录现在蛇的状态
	SnakeNode* pfood;//指向食物的指针
	int scores;//总得分
	int score_per_food;//每个食物的分
	int sleeptime;//蛇的速度 本程序是利用 一睡一走来实现蛇的移动
	//sleeptime越小 速度越快 越大 速度越慢
}Snake;

void SetPos(int x, int y);//定位光标位置

void GameStart(Snake* ps);//游戏运行前的准备工作

void Welcome();

void CreatMap();

void InitiSnake(Snake* ps);

void GameRun(Snake* ps);

void CreatFood(Snake* ps);

void PrintHelpInfo();

void Pause();

void SnakeMove(Snake* ps);

void KillbyWall(Snake* ps);

void KillbySelf(Snake* ps);

void GameEnd(Snake* ps);
