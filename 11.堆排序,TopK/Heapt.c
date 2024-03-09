#define _CRT_SECURE_NO_WARNINGS 1

#include "Heap.h"


// 堆的构建
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

// 堆的销毁
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

//向上调整 push后
void AdjustUp(Hpdatatype* heap, int child) {
	assert(heap);//数组是有效的

	int parent = (child - 1) / 2;

	while (child>0) {//小堆
		if (heap[parent] > heap[child]) {//小的上移
			Swap(&heap[parent], &heap[child]);

			child = parent;
			parent = (child - 1) / 2;
		}
		else {
			break;
		}
	}
}

//向下调整 pop后
void AdjustDown(Hpdatatype* heap, int size, int parent) {
	assert(heap);

	//小堆 我要和两个儿子的较小者比 先找两个儿子的较小者
	int child = parent * 2 + 1;//默认左儿子小
	while (child < size) {
		if ((child+1)<size && heap[child] > heap[child + 1]) {
			child++;
		}

		if (heap[child] < heap[parent]) {
			Swap(&heap[child], &heap[parent]);
			parent = child;
			child = parent * 2 + 1;//默认左儿子大
		}
		else
			break;
	}
}

// 堆的插入
void HeapPush(Heap* hp, Hpdatatype x) {
	assert(hp);

	//空或者满进行扩容
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

// 堆的删除
void HeapPop(Heap* hp) {
	//删除堆顶元素 如果采用和顺序表一样的方法 即覆盖 将后续元素前移
	//这样会导致后后面的父子关系混乱 破坏堆的结构 很大可能不是堆了
	//这里采用 向下调整 怎么个方法呢 让堆顶元素和堆最后一个元素交换 size-- 屏蔽掉最后一个元素
	//然后让刚才到堆顶的元素向下调整 成为一个堆 向上/下调整的前提就是调整的对象是个堆
	//而堆顶元素下面一个左子树一个右子树都是堆(除开屏蔽的元素)
	assert(hp);
	assert(!HeapEmpty(hp));

	Swap(&hp->arr[0], &hp->arr[hp->size - 1]);
	hp->size--;
	AdjustDown(hp->arr, hp->size, 0);
}

// 取堆顶的数据
Hpdatatype HeapTop(Heap* hp) {
	assert(hp);
	assert(!HeapEmpty(hp));
	
	return hp->arr[0];
}

// 堆的数据个数
int HeapSize(Heap* hp) {
	assert(hp);

	return hp->size;
}

// 堆的判空
bool HeapEmpty(Heap* hp) {
	assert(hp);

	return hp->size == 0;
}


//堆排序  这里实现一个小堆---对应降序
//这里的参数不是指向堆的结构体与调整对应 就体现出来其作用了。
//堆排序前提是堆，是堆你就要建堆，但你不能又去创建一个堆(Heap结构体是
// 有会开辟动态内存去建堆的)， 然后建好后 再搞回到数组吧，很垃圾很低级的方法啊
//这里的参数的设置就是可以直接对这个数组进行操作 让这个数组变成堆 因为建堆核心就是向上向下调整
//这里的参数设置就是直接可以调用调整 调整的对象必须是堆 这里两种具体做法说明如下
//向上调整法：从数组元素第一个开始做向上调整 因为一个元素就可以成堆 接着往下遍历
// 向下调整法：因为从数组最后一个元素开始，这是不划算的，因为向下调整 最后的叶节点 都可以是堆
// 完全不用管 应该从最后一个父亲开始做向下调整
// 这两种方法是有区别的 是时间上 具体分析会在笔记中说明 下面进行实现 
void Heapsort(Hpdatatype* heap, int size) {

	//向上建堆  //NlogN
	//for (int i = 1; i < size; i++) {//下标为零的元素暂时为栈顶元素 看作是堆
	//	AdjustUp(heap, i);
	//}

	//向下建堆  //N
	for (int i = (size - 1 - 1) / 2; i >= 0; i--) {//i先为最后一个父亲(不会为负数)
		AdjustDown(heap, size, i);
	}

	//建完堆 开始排序
	//思路和pop类似 因为堆顶元素是最小值想要去到并且 不破坏堆 就与堆尾元素对换 在向下调整堆顶元素

	//NlogN
	while (size > 1) {
		Hpdatatype tmp = heap[size - 1];
		heap[size - 1] = heap[0];
		heap[0] = tmp;
		size--;

		AdjustDown(heap, size, 0);
	}
}; 

//TopK问题  具体参照笔记
//建小堆 求最大的K个数
void PrintTopk(Hpdatatype* Dataarr, int size, int k) {
   
	//先向上建堆 前k个元素 这里只能向上调整 下面有向下建的
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

/*这里给出文件下的TopK(处理大数据)
  
void PrintTopk(int k){
  int a = 100000

  srand(time(0));

  FILE* fwrite = fopen("data.txt"."w");
  if(fwrite==NULL){
    perror("open failed!");
  }

  for(int i=0;i<a;i++){
    int val = rand%10000;//小于10000的数
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


  //向下建小堆
  for(int i=(k-1-1)/2;i>=0;i--){
    AdjustDown(kMinheap,k,i);
  }


  int val=0;
  for(int i=k;i<100000;i++){
     fscanf(fread,"%d",&val);  //文件指针指向第k+1个元素
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

