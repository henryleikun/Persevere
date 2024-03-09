#define _CRT_SECURE_NO_WARNINGS 1

#include "Heap.h"


// �ѵĹ���
void HeapCreate(Heap* hp, Hpdatatype* a, int n) {
	assert(hp);

	HeapInit(hp);

	for (int i = 0; i < n; i++) {
		HeapPush(hp, a[i]);
	}
}

void HeapInit(Heap* hp) {
	hp->arr = NULL;
	hp->capacity = 0;
	hp->size = 0;
}

// �ѵ�����
void HeapDestory(Heap* hp) {
	free(hp->arr);
	hp->arr = NULL;
	hp->capacity = 0;
	hp->size = 0;
}

void Swap(Hpdatatype* a, Hpdatatype* b) {
	Hpdatatype temp = *a;
	*a = *b;
	*b = temp;
}

//���ϵ��� push��
void AdjustUp(Hpdatatype* heap, int child) {
	assert(heap);//��������Ч��

	int parent = (child - 1) / 2;

	while (child>0) {//С��
		if (heap[parent] > heap[child]) {//С������
			Swap(&heap[parent], &heap[child]);

			child = parent;
			parent = (child - 1) / 2;
		}
		else {
			break;
		}
	}
}

//���µ��� pop��
void AdjustDown(Hpdatatype* heap, int size, int parent) {
	assert(heap);

	//С�� ��Ҫ���������ӵĽ�С�߱� �����������ӵĽ�С��
	int child = parent * 2 + 1;//Ĭ�������С
	while (child < size) {
		if ((child+1)<size && heap[child] > heap[child + 1]) {
			child++;
		}

		if (heap[child] < heap[parent]) {
			Swap(&heap[child], &heap[parent]);
			parent = child;
			child = parent * 2 + 1;//Ĭ������Ӵ�
		}
		else
			break;
	}
}

// �ѵĲ���
void HeapPush(Heap* hp, Hpdatatype x) {
	assert(hp);

	//�ջ�������������
	if (hp->size == hp->capacity) {
	  int newcapacity = hp->capacity == 0 ? 4 : hp->capacity * 2;
	  Hpdatatype* tmp = (Hpdatatype*)realloc(hp->arr,sizeof(Hpdatatype) * newcapacity);

	  if (tmp == NULL) {
		  perror("realloc failed");
	  }

	  hp->arr = tmp;
	  hp->capacity = newcapacity;
	}

	hp->arr[hp->size++] = x;

	AdjustUp(hp->arr, hp->size - 1);
}

// �ѵ�ɾ��
void HeapPop(Heap* hp) {
	//ɾ���Ѷ�Ԫ�� ������ú�˳���һ���ķ��� ������ ������Ԫ��ǰ��
	//�����ᵼ�º����ĸ��ӹ�ϵ���� �ƻ��ѵĽṹ �ܴ���ܲ��Ƕ���
	//������� ���µ��� ��ô�������� �öѶ�Ԫ�غͶ����һ��Ԫ�ؽ��� size-- ���ε����һ��Ԫ��
	//Ȼ���øղŵ��Ѷ���Ԫ�����µ��� ��Ϊһ���� ����/�µ�����ǰ����ǵ����Ķ����Ǹ���
	//���Ѷ�Ԫ������һ��������һ�����������Ƕ�(�������ε�Ԫ��)
	assert(hp);
	assert(!HeapEmpty(hp));

	Swap(&hp->arr[0], &hp->arr[hp->size - 1]);
	hp->size--;
	AdjustDown(hp->arr, hp->size, 0);
}

// ȡ�Ѷ�������
Hpdatatype HeapTop(Heap* hp) {
	assert(hp);
	assert(!HeapEmpty(hp));
	
	return hp->arr[0];
}

// �ѵ����ݸ���
int HeapSize(Heap* hp) {
	assert(hp);

	return hp->size;
}

// �ѵ��п�
bool HeapEmpty(Heap* hp) {
	assert(hp);

	return hp->size == 0;
}


//������  ����ʵ��һ��С��---��Ӧ����
//����Ĳ�������ָ��ѵĽṹ���������Ӧ �����ֳ����������ˡ�
//������ǰ���Ƕѣ��Ƕ����Ҫ���ѣ����㲻����ȥ����һ����(Heap�ṹ����
// �лῪ�ٶ�̬�ڴ�ȥ���ѵ�)�� Ȼ�󽨺ú� �ٸ�ص�����ɣ��������ܵͼ��ķ�����
//����Ĳ��������þ��ǿ���ֱ�Ӷ����������в��� ����������ɶ� ��Ϊ���Ѻ��ľ����������µ���
//����Ĳ������þ���ֱ�ӿ��Ե��õ��� �����Ķ�������Ƕ� �������־�������˵������
//���ϵ�������������Ԫ�ص�һ����ʼ�����ϵ��� ��Ϊһ��Ԫ�ؾͿ��Գɶ� �������±���
// ���µ���������Ϊ���������һ��Ԫ�ؿ�ʼ�����ǲ�����ģ���Ϊ���µ��� ����Ҷ�ڵ� �������Ƕ�
// ��ȫ���ù� Ӧ�ô����һ�����׿�ʼ�����µ���
// �����ַ������������ ��ʱ���� ����������ڱʼ���˵�� �������ʵ�� 
void Heapsort(Hpdatatype* heap, int size) {

	//���Ͻ���  //NlogN
	//for (int i = 1; i < size; i++) {//�±�Ϊ���Ԫ����ʱΪջ��Ԫ�� �����Ƕ�
	//	AdjustUp(heap, i);
	//}

	//���½���  //N
	for (int i = (size - 1 - 1) / 2; i >= 0; i--) {//i��Ϊ���һ������(����Ϊ����)
		AdjustDown(heap, size, i);
	}

	//����� ��ʼ����
	//˼·��pop���� ��Ϊ�Ѷ�Ԫ������Сֵ��Ҫȥ������ ���ƻ��� �����βԪ�ضԻ� �����µ����Ѷ�Ԫ��

	//NlogN
	while (size > 1) {
		Hpdatatype tmp = heap[size - 1];
		heap[size - 1] = heap[0];
		heap[0] = tmp;
		size--;

		AdjustDown(heap, size, 0);
	}
}; 

//TopK����  ������ձʼ�
//��С�� ������K����
void PrintTopk(Hpdatatype* Dataarr, int size, int k) {
   
	//�����Ͻ��� ǰk��Ԫ�� ����ֻ�����ϵ��� ���������½���
	for (int i = 1; i < k; i++) {
		AdjustUp(Dataarr,i);
	}

	for (int i = k; i < size; i++) {
		if (Dataarr[0] < Dataarr[i]) {
			Hpdatatype tmp = Dataarr[i];
			Dataarr[i] = Dataarr[0];
			Dataarr[0] = tmp;

			AdjustDown(Dataarr, k, 0);
		}
	}

	for (int i = 0; i < k; i++) {
		printf("%d ", Dataarr[i]);
	}
	
}

/*��������ļ��µ�TopK(���������)
  
void PrintTopk(int k){
  int a = 100000

  srand(time(0));

  FILE* fwrite = fopen("data.txt"."w");
  if(fwrite==NULL){
    perror("open failed!");
  }

  for(int i=0;i<a;i++){
    int val = rand%10000;//С��10000����
    fprintf(fwrite,"%d",val);
  }

  fclose(fwrite);

  Hpdatatype* kMinheap = (Hpdatatype*)malloc(sizeof(Hpdatatype)*k);
  FILE* fread = fopen("data.txt","r");
  if(fread==NULL){
	perror("open failed!");
  }

  for(int i = 0;i<k;i++){
    fscanf(fread,"%d",&kMinheap[i])
  }


  //���½�С��
  for(int i=(k-1-1)/2;i>=0;i--){
    AdjustDown(kMinheap,k,i);
  }


  int val=0;
  for(int i=k;i<100000;i++){
     fscanf(fread,"%d",&val);  //�ļ�ָ��ָ���k+1��Ԫ��
	 if(kMinheap[0]<val){
	   swap(val,kMinheap[0]);

	   AdjustDown(kMinheap,k,0);
	 }
  }

  fclose(fread);

  for(int i = 0;i < k;i++){
    printf("%d ",kMinheap[i]);
  }
}
 
*/

