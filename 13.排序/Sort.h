#define _CRT_SECURE_NO_WARNINGS 1
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "stack.h"
#include <string.h>//memcpy�Ⱥ���

void InsertSort(int* arr, int n);//����

void ShellSort(int* arr, int n);//ϣ��

void BubbleSort(int* arr, int n);//ð��

void QuickSort(int* arr, int left,int right);//���� ---����˼��

void HeapSort(int* arr, int n);//����

void SelectSort(int* arr, int n);//ѡ����

void MergeSort(int* arr,int n);//�鲢��

void QuickSort_noR(int* arr, int left, int right);//���ŷǵݹ�

void MergeSort_noR(int* arr, int n);//�鲢�ŷǵݹ�

void QuickSort_Threedivide(int* arr, int left, int right);//����---��·����

void CountSort(int* arr, int n);//������



