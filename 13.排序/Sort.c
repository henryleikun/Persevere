#define _CRT_SECURE_NO_WARNINGS 1
#include "Sort.h"
//���������ʵ�ֵĶ������� ��������
void Swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

//���O(N^2)---����ÿ��һ����Ҫ���������
//��ã�O(N) ˳�����1һ�߾ͽ���
void InsertSort(int* arr, int n) {
	//���������ԭ�����Ƴ��˿��� ��һ�����еĽ��бȽ� �嵽С��ǰ���ĺ��� 
	for (int i = 1; i < n; i++) {
		int end = i-1;
		int tmp = arr[i];

		while(end >= 0){
			if (arr[end] > tmp) {
				arr[end + 1] = arr[end];
				end--;
			}
			else
				break;
		}

		arr[end + 1] = tmp;
	}
}

//O(N^1.3)
void ShellSort(int* arr, int n) {
	int gap = n;

	while (gap > 1) {//gap����1��ʱ�� �����ѽӽ�����������ǲ������� �ŵĺܿ�
		gap = gap / 3 + 1;//gap������1��
		//gap = gap / 2;���gap����Ҳ����1 �����Ǹ�Ҫ+1����

		//ÿһ��gap ����һ��Ԥ���� ��gapΪ1��ʱ�������ѽӽ�������ʱ���һ������
	   for (int i = 0; i < n - gap; i += gap) {
		  int end = i;
		
		  int tmp = arr[end + gap];
		  while (end >= 0) {
		     if (arr[end] > tmp) {
			   arr[end + gap] = arr[end];
			   end -= gap;
			  }
			 else
				break;
		  }

		  arr[end + gap] = tmp;
	   }
    }
}

//O(N^2)
void BubbleSort(int* arr, int n) {
	 
	for (int i = 0; i < n - 1; i++) {//��Ҫ��n-1��ð��

		bool exchange = false;//�Ż� ��¼�Ƿ�һ��һ��û����
		//һ��ð��  �����Ƚ� 
		for (int j = 0; j < n-1-i; j++) {//ÿһ�� �����Ƚ� ��i��ð�ݵ� n-i��
			if (arr[j] > arr[j + 1]) {
				Swap(&arr[j], &arr[j + 1]);
				exchange = true;
			}

		}

		if (exchange == false)
			break;
	}
}



//��������������ʵ�ַ��� (�����Ż�˼��) ����˼�붼��һ���� ��Ȼ���ﶼ�ǵݹ��
//Ϊ��Ū��������˼��  ���ｫ���װ�ɺ���
//���������������ⶼ������ұ�

//�Ż�1�� ��Կ����е��������� ÿһ�ε�keyֵ�����Ǹ�����ֵ ÿһ�ζ�Ҫ��������������
//(����С)�������������ȥ�� ���Ż�һ�� �ҳ����ұ� ����� �м�ֵ�ĵڶ���/С��Ϊkeyֵ (�±�����left)
//�������Ϊbase������
int GetmidIndex(int* arr, int left, int right) {
	int mid = (left + right) / 2;

	if (arr[left] < arr[right]) {
		if (arr[mid] < arr[left]) {
			return left;//left�ǵڶ�
		}
		else if (arr[mid] < arr[right])//left��С
			    return mid;
		     else
			    return right;
	}
	else {//arr[left]>arr[right]
		if (arr[mid] > arr[left])
			return left;
		else if (arr[mid] > arr[right])//left���
			   return mid;
		     else
			   return right;
	}         
}

//1. ������ԭʼ˼�� ����keyֵ ���Ҵ� ����С ����keyֵ���±� �����ݻ�������
int Quick_part1(int* arr,int left, int right) {//һ�˿���
	int keyi = left;//����keyֵ���±� ��Ϊ�����ڻ�������

	int Mid_keyi = GetmidIndex(arr, left, right);
	//��ȡ�����м�ֵ���±�
	Swap(&arr[keyi], &arr[Mid_keyi]);

	while (left < right) {//���ұ����� ����������ڱʼ���˵��

		while (left < right && arr[right] >= arr[keyi]) {//���ƶ��Ĺ����� 
			//left��right���ܲ�������left<right(��ʹ������ѭ������)
			right--;
		}//����С

		while (left < right && arr[left] <= arr[keyi]) {
			left++;
		}//���Ҵ�

		Swap(&arr[left], &arr[right]);
	}
	//left == rightʱ��keyֵ�ŵ����λ��
	Swap(&arr[left], &arr[keyi]);
	keyi = left;

	return keyi;
}

//2.�ڿӷ� �ϸ������Ǽ�סkey���±�ȥ�������� ����ȥ����key��ֵ �������� 
//ͬ������С�����Ҵ� �ҵ��������� ���� ����Ϊ�µĿ� ���left��right����һ���ǿ� �������ʱ
//��keyֵ�ŵ����� ����Ϊ�µ�keyiֵ����
int Quick_part2(int* arr, int left, int right) {
	int hole = left;
	int tmp = arr[left];

	int Mid_keyi = GetmidIndex(arr, left, right);
	//��ȡ�����м�ֵ���±�
	Swap(&arr[hole], &arr[Mid_keyi]);

	while (left < right) {

		while (left < right && arr[right] >= tmp) {//���ƶ��Ĺ����� 
			//left��right���ܲ�������left<right(��ʹ������ѭ������)
			right--;
		}//����С

		arr[hole] = arr[right];
		hole = right;

		while (left < right && arr[left] <= tmp) {
			left++;
		}//���Ҵ�

		arr[hole] = arr[left];
		hole = left;
	}

	//left == right
	arr[hole] = tmp;

	return hole;
}

//3. ǰ��ָ�뷨  ͬ����ѡleftΪkeyi ����������ָ�롱prev cur��cur��ǰ�� �ߵ�����keyֵ��
//cur++��С��keyֵ prev++��������cur��prevָ���ֵ cur++���� cur��prev֮���Ķ��Ǵ���key����
//��cur�߳�����ʱ����prev��ֵ��keyֵ��������prev��Ϊ�µ�keyi����
int Quick_part3(int* arr, int left, int right) {
	int keyi = left;
	int prev = left;
	int cur = left + 1;

	int Mid_keyi = GetmidIndex(arr, left, right);
	//��ȡ�����м�ֵ���±�
	Swap(&arr[keyi], &arr[Mid_keyi]);

	while (cur <= right) {

		if (arr[cur] < arr[keyi] && cur != ++prev) {//ָ��һ���Ͳ�������
			Swap(&arr[prev], &arr[cur]);
		}

		cur++;
	}//cur����

	Swap(&arr[prev], &arr[keyi]);

	return prev;
}

//�Ż�2�������ŵ��������д��� ��ͬ������ʱ ��Ϊ������ƵĿ��� ��������ͬ���������� 
//������ ���ȫ��һ�������� �Ǿ�һֱ�� �ͳ�O(N^2)��
//���������·�����Ż� ��ϻ�����ǰ��ָ��˼�� ���������ݻ���Ϊ С��keyֵ�����䣬����keyֵ������
//����keyֵ������
//������¸�һ������ ��Ϊ ��ֹһ��λ��Ҫ����
void QuickSort_Threedivide(int* arr,int  left,int right) {
	if (left >= right)
		return;

	int Midkey = GetmidIndex(arr, left, right);
	Swap(&arr[left], &arr[Midkey]);//����ȡ��

	//int keyi = left;
	int r = left;
	int l = left;
	int cur = l + 1;

	while (cur <= r) {
		if (arr[cur] > arr[l]) {
			Swap(&arr[cur], &arr[r]);
			r--;
		}

		if (arr[cur] < arr[l]) {
			Swap(&arr[cur++], &arr[l++]);//l��Զָ���Ǹ�key
		}

		if (arr[cur] == arr[l]) {
			cur++;
		}//cur��l֮��ȫ�Ǻ�keyֵ��ͬ��ֵ
	}//��ʱcur>r
	//[left,l-1][l,r][cur,right]

	QuickSort_Threedivide(arr, left, l - 1);
	QuickSort_Threedivide(arr, cur, right);
	//ǰ���˼��
}

void QuickSort(int* arr,int left, int right) {
	if (left >= right) {
		return;
	}//left == right����ֻ��һ��ֵ ����Ҫ��
	//left>right���䲻���� ����

	int keyi = Quick_part1(arr, left, right);
	//���仮��Ϊ[left,keyi-1] keyi [keyi+1 right];

	QuickSort(arr, left, keyi - 1);
	QuickSort(arr, keyi + 1, right);
}

//���ŵķǵݹ�ʵ��
//�ǵݹ�ʵ����ʵ�Ǳȵݹ��ѵ� �ݹ�ת�ǵݹ� ��쳲�����������
//Ҳ�д�ѭ�������� ��ȻҲ���� ����ջʵ�ֵ� ��Ϊջ����ݹ� �Ƚ���� �ڵ��˻���
//��������ջʵ�ֿ��ŵķǵݹ�
void QuickSort_noR(int* arr, int left, int right) {
	//���� �ݹ������Ŀ��� �����ݹ�չ��ͼ���Ƕ������Ľṹ  ����ջ������ѹ������ֵ
	//�����������˵� һ��push����ֵ һ��Ҳpop����ֵ

	ST st;
	STiniti(&st);
	STPush(&st, right);
	STPush(&st, left);//��push �Ҷ˵� ����˵� ȡ��ʱ����ȡ��˵� ���Ҷ˵�

	while (!STisEmpty(&st)) {
		int begin = STtop(&st);
		STPop(&st);

		int end = STtop(&st);
		STPop(&st);

		int keyi = Quick_part1(arr, begin, end);
		//[begin,keyi-1] keyi [keyi+1,end]

		//������һ�� ѹ��˳�� ���Һ��� ȡ��˳�� �������
		if (keyi + 1 < end) {//���ֻ��һ��Ԫ�� �����䲻���� ����ѹջ ��������
			STPush(&st, end);
			STPush(&st, keyi + 1);
		}

		if (begin < keyi - 1) {
			STPush(&st, keyi - 1);
			STPush(&st, begin);
		}
	}

	STdestroy(&st);
}
//��ʵҲ�����ö���ʵ�� ����������� ��Ϊ���ű������һ��ǰ��һ��
//ջ��������� �����ǹ������

//���µ���
void AdjustDown(int* arr, int n, int parent) {//���򽨴��

	int child = parent * 2 + 1;//����

	while (child < n) {

		if (child + 1 < n && arr[child + 1] > arr[child]) {
			child++;
		}

		if (arr[child] > arr[parent]) {
			Swap(&arr[child], &arr[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			break;
	}
}

void HeapSort(int* arr, int n) {

	for (int i = (n - 1 - 1) / 2; i >= 0; i--) {//���µ�������
		AdjustDown(arr, n, i);
	}

	while (n) {
		Swap(&arr[0], &arr[n - 1]);
		n--;
		AdjustDown(arr, n, 0);
	}
}

void SelectSort(int* arr, int n) {//ѡ���������һ��һ��ѡ
	/*for (int i = 0; i < n-1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (arr[i] > arr[j])
				Swap(&arr[i], &arr[j]);
		}
	} ��ͨ��ѡ������ ��������Ż���� ѡ��������
	һ��һ��ѡ����ֵ����ֵ���δ�ֵ...  ��������Ż��� ÿһ��ѡ��������ֵ һ����һ��
	�����ֵ��һ����һ�˵���Сֵ  һ�����˵����ֵ*/

	/*int left = 0;
	int right = n;
	
	while (left < right) {
		for (int i = left+1; i < right; i++) {
			if (arr[i] < arr[left])
				Swap(&arr[i], &arr[left]);
		}

		for (int i = left + 1; i < right; i++) {
			if (arr[i] > arr[right-1])
				Swap(&arr[i], &arr[right-1]);
		}

		left++;
		right--;
	}  ���������ĵ�...*/

	int begin = 0, end = n - 1;
	while (begin < end) {
		int maxi = begin;
		int mini = begin;//���������С�±�

		for (int i = begin; i <= end; i++) {
			if (arr[i] > arr[maxi])
				maxi = i;
			if (arr[i] < arr[mini])
				mini = i;
		}

		Swap(&arr[begin], &arr[mini]);//С��ǰ��
		if (begin == maxi)//���begin��maxi�غ� ��ôԭ�е�max�ᵽԭ����mini�ط�
			Swap(&arr[mini], &arr[end]);
		else
		    Swap(&arr[maxi], &arr[end]);

		begin++;
		end--;
	}
}

//����鲢�Ƕ�·�鲢 ��˵�Ĺ鲢��ָ���� ����������Ҫ�鲢��һ�� �������� �ϳƹ鲢��
//�鲢���һ�� �鲢��ڶ��� ���� ���ֺ�Ĺ鲢��


//�鲢���� Ψһ���Խ�������������� ��ݹ�ʵ�ֱȽϼ� ��ҪҲ�Ƕ������Ľṹ�ĵݹ� ��������
//����������Ĺ鲢 �������� ����Ĺ鲢��Ҫ�����������ռ� ȡ�洢�鲢�����������ٿ���ԭ�����
//������Խ��ڵ�ժ���� ����Ҫ�����ռ� ������oj��Ҳ������ ����Ϊ�˷���Ҳ��һ�˹鲢 ��װ�ɺ���
void _MergeSort(int* arr,int left,int right,int* tmp) {
	if (left == right)//���ֻ���������ֻ��һ��Ԫ�� �����������䲻���ڵ����
		return;       //��Ϊ�������������ֵ�[left,mid][mid+1,right]

	//�������С�����Ż� ԭ���� ���鲢�ݹ鵽���²�ʱ ÿ����������Ѿ����ָ�ĺ�С��
	//������Ҫ�õݹ�ȥ��� δ���е���С�� ������ ���ù鲢�������<10ʱȥ�ø��õ�����ȥ��
	//����ѡ�ò���
	if (left - right + 1 < 10) {
		InsertSort(arr+left, left - right + 1);
		return;
	}//����һ���������� Խ�ײ� ��Խ�� ��ʡ��ʱ��Խ�� �� ��Щʱ���ǲ���������Щ���� ����� �ݹ��ʱ��
	             
	int mid = (left + right) / 2;
	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;

	int j = left;//�鲢������浽tmp���±�Ҫһ��

	_MergeSort(arr, left, (left + right) / 2, tmp);
	_MergeSort(arr, (left + right) / 2 + 1, right, tmp);
	//���������������� �ٹ鲢���� ��һ�ֺ����˼��

	while (begin1 <= end1 && begin2 <= end2) {
		if (arr[begin1] <= arr[begin2]) {
			tmp[j++] = arr[begin1++];
		}
		else {
			tmp[j++] = arr[begin2++];
		}
	}//���� �϶���һ���ߵ�end1�����

	while (begin1 <= end1) {
		tmp[j++] = arr[begin1++];
	}

	while (begin2 <= end2) {
		tmp[j++] = arr[begin2++];
	}

	memcpy(arr + left, tmp + left, sizeof(int) * (right - left + 1));
}

void MergeSort(int* arr,int n) {
	int* tmp = (int*)malloc(sizeof(int) * n);
	//���ʺ�����������ݹ� ��Ϊ�ж�̬����

	_MergeSort(arr, 0, n - 1, tmp);

	free(tmp);
}


//�ǵݹ�ʵ�ֹ鲢����
//�鲢�ķǵݹ鲻������ջ ��Ϊ�鲢��һ�ֺ����˼�� ������������ ������
//ջ��һ��ǰ���˼�� �����ǲ����˼�� �������ô�ѭ��������˼�����㶨 ����ǵݹ�
//�����е��鷳 ע�������ķ�Χ����
void MergeSort_noR(int* arr, int n) {
	int* tmp = (int*)malloc(sizeof(int) * n);
	
	int gap = 1;
	//�鲢�Ƕ���һ gapȷ���������ÿ����ĸ���

	while (gap < n) {

		int j = 0;//j��forѭ�����Ǹ��Ź鲢�������ߵ� j������tmp����

		for (int i = 0; i < n;i += 2 * gap) {
			//ͨ��i������ÿ�ι鲢������ 
			int begin1 = i, end1 = begin1 + gap - 1;
			int begin2 = begin1 + gap, end2 = begin2 + gap - 1;

			//�����gap�µ�������й鲢 ��Ȼ����ѭ���Ľ��У�
			// �鲢�������ƽ����п��ܳ��� ����Խ������
			//����������е����
			//begin1�ǲ���Խ��� ѭ����������begin1<n
			//���1�� end1Խ�� ���������Խ
			//���2�� ��һ��������� begin2Խ�� end2��Խ
			//���3�� begin2ûԽ�� ��end2Խ�� 
			//��Ȼ��õľ��Ǹոպ� �������䶼���� �պø㶨
			
			if (end1 >= n) {
				break;//���ù鲢�� ��������
			}
			else if (begin2 >= n) {
				break;//ͬ��
			}
			else if(end2 >= n){//begin2 < n
				//���Թ鲢 ��Ҫ�����ڶ������� ���䲻Խ��
				end2 = n - 1;
			}

			while (begin1 <= end1 && begin2 <= end2) {

				if (arr[begin1] <= arr[begin2]) {
					tmp[j++] = arr[begin1++];
				}
				else {
					tmp[j++] = arr[begin2++];
				}

			}//���� �϶���һ���ߵ�end1�����

			while (begin1 <= end1) {
				tmp[j++] = arr[begin1++];
			}

			while (begin2 <= end2) {
				tmp[j++] = arr[begin2++];
			}

			//�鲢һ�� ����һ��
			memcpy(arr + i, tmp + i, sizeof(int) * (end2 - i + 1));
		}

		gap *= 2;
	}

	free(tmp);
}
//���ﻹ��һ�ַ��� ���� �����ǹ鲢һ�� ����һ�� ��Ժ����һ�� ��Ϊ ѭ����Խ��Ĺ鲢��ʱ
//��ֱ��break�� ������� ȫcopy�������˼�� ��ΪԽ���ʱ��Ͳ��ܹ鲢�� �����break�������
//���� ����end1Խ���ʱ�� ��end1=n-1����������� ����Ϊһ�������ڵ����� ����û��ȥ�鲢�Ļ���
//��Ϊ�鲢���������������䶼����(��<=��)������������>��
/*
 if(end1 >= n){
   end1 = n-1;
   begin2 = n;
   end2 =n - 1; �������begin2 > end2��
 }
 else if(begin2 >= n){
   begin2 = n;
   end2 =n - 1;
 }
 else if(end2 >= 2){
   end2 = n - 1; 
   
 }

 //�鲢��������

 memcpy(arr,tmp,sizeof(int)*n);

 ��Ҫ������������ѭ�� ���ֿ���������鲢�ĵ�һ���� д��tmp�� Ȼ��tmp����������
 ȫcopy��arr��

 �������begin2 �� end2 ���䶼����n-1 ��������鲢
 ��j�Ǹ��Ź鲢��������ߵ� �������鲢 ���ص���ֵ ��j��֪�� ��ֻ��++��͵��� tmp�����Խ��
 ��֮ Խ���ʱ�� �ù鲢��ڶ������ò��������� ����������鲢 �ú��õ�һ����Ч�� ȥcopy����
*/


//�������� ʵ�����岻�� �о����� ֻ��������  ���ұ�������ֵ�������������
//��������漰�Ƚ� ��������������� ������±� ������ ���� 
void CountSort(int* arr, int n) {
	int max = arr[0];
	int min = arr[0];

	for (int i = 0; i < n; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}

		if (arr[i] < min) {
			min = arr[i];
		}
	}//�ҳ���������������Сֵ

	int* tmp = (int*)malloc(sizeof(int) * (max - min + 1));//���ܴ洢�����Χ����������
	                                                    //�±�������

	for (int i = 0; i < n; i++) {
		tmp[i] = 0;
	}

	//�������� ��¼ÿ�������ֵĴ���
	for (int i = 0; i < n; i++) {
		tmp[arr[i] - min]++;
	}

	int j = 0;
	for (int i = 0; i < (max - min + 1); i++) {

		while (tmp[i]) {
			arr[j] = i + min;
			j++;
			tmp[i]--;
		}
	}
	
	free(tmp);
}