#define _CRT_SECURE_NO_WARNINGS 1

//¶þ²æÊ÷
#include <stdlib.h>
#include <stdio.h>
#include "Queue.h"
#include <assert.h>

typedef int BTdatatype;

typedef struct BTnode {
	BTdatatype val;
	struct BTnode* left;
	struct BTnode* right;
}BTnode;//Ê÷½Úµã


BTnode* BuyNode(BTdatatype val);

BTnode* BT_creat_by_hand();

void  PrevOrder(BTnode* root);

void  MidOrder(BTnode* root);

void  BackOrder(BTnode* root);

void LevelOrder(BTnode* root);

int BTreeSize(BTnode* root);

int Klevelsize(BTnode* root, int k);

int Leafsize(BTnode* root);

int BTreeHeight(BTnode* root);

BTnode* BTreeFind(BTnode* root, BTdatatype x);



