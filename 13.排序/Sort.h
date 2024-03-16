#define _CRT_SECURE_NO_WARNINGS 1
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "stack.h"
#include <string.h>//memcpy等函数

void InsertSort(int* arr, int n);//插入

void ShellSort(int* arr, int n);//希尔

void BubbleSort(int* arr, int n);//冒泡

void QuickSort(int* arr, int left,int right);//快排 ---三种思想

void HeapSort(int* arr, int n);//堆排

void SelectSort(int* arr, int n);//选择排

void MergeSort(int* arr,int n);//归并排

void QuickSort_noR(int* arr, int left, int right);//快排非递归

void MergeSort_noR(int* arr, int n);//归并排非递归

void QuickSort_Threedivide(int* arr, int left, int right);//快排---三路划分

void CountSort(int* arr, int n);//计数排



