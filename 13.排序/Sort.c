#define _CRT_SECURE_NO_WARNINGS 1
#include "Sort.h"
//下面的排序实现的都是升序 降序类似
void Swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

//最坏：O(N^2)---逆序每插一个都要遍历到最后
//最好：O(N) 顺序遍历1一边就结束
void InsertSort(int* arr, int n) {
	//插入排序的原理类似抽扑克牌 抽一张已有的进行比较 插到小的前面大的后面 
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

	while (gap > 1) {//gap等于1的时候 数组已接近有序，这里就是插入排序 排的很快
		gap = gap / 3 + 1;//gap最后会是1的
		//gap = gap / 2;这个gap最用也会是1 上面那个要+1处理

		//每一次gap 都是一次预排序 而gap为1的时候数组已接近有序，这时最后一次排序
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
	 
	for (int i = 0; i < n - 1; i++) {//需要跑n-1趟冒泡

		bool exchange = false;//优化 记录是否一趟一次没交换
		//一趟冒泡  两两比较 
		for (int j = 0; j < n-1-i; j++) {//每一趟 两两比较 第i趟冒泡的 n-i次
			if (arr[j] > arr[j + 1]) {
				Swap(&arr[j], &arr[j + 1]);
				exchange = true;
			}

		}

		if (exchange == false)
			break;
	}
}



//快排这里有三种实现方法 (两种优化思想) 主题思想都是一样的 当然这里都是递归的
//为了弄清这三种思想  这里将其封装成函数
//这里讨论区间问题都是左闭右闭

//优化1： 针对快排中的逆序问题 每一次的key值都是那个最大的值 每一次都要遍历完整个数组
//(右找小)，这里给出三数去中 来优化一下 找出最右边 最左边 中间值的第二大/小作为key值 (下标依旧left)
//以这个作为base来排序
int GetmidIndex(int* arr, int left, int right) {
	int mid = (left + right) / 2;

	if (arr[left] < arr[right]) {
		if (arr[mid] < arr[left]) {
			return left;//left是第二
		}
		else if (arr[mid] < arr[right])//left最小
			    return mid;
		     else
			    return right;
	}
	else {//arr[left]>arr[right]
		if (arr[mid] > arr[left])
			return left;
		else if (arr[mid] > arr[right])//left最大
			   return mid;
		     else
			   return right;
	}         
}

//1. 霍尔的原始思想 利用key值 左找大 右找小 返回key值的下标 将数据划分区间
int Quick_part1(int* arr,int left, int right) {//一趟快排
	int keyi = left;//保存key值的下标 因为有助于划分区间

	int Mid_keyi = GetmidIndex(arr, left, right);
	//获取三数中间值的下标
	Swap(&arr[keyi], &arr[Mid_keyi]);

	while (left < right) {//让右边先走 具体分析会在笔记中说明

		while (left < right && arr[right] >= arr[keyi]) {//在移动的过程中 
			//left和right可能不会满足left<right(即使是最外循环条件)
			right--;
		}//右找小

		while (left < right && arr[left] <= arr[keyi]) {
			left++;
		}//左找大

		Swap(&arr[left], &arr[right]);
	}
	//left == right时将key值放到这个位置
	Swap(&arr[left], &arr[keyi]);
	keyi = left;

	return keyi;
}

//2.挖坑法 上个方法是记住key的下标去划分区间 这里去保存key的值 让他做坑 
//同样右找小，左找大 找到的数换到 坑里 并成为新的坑 最后left和right总有一个是坑 二者相等时
//将key值放到坑里 并最为新的keyi值返回
int Quick_part2(int* arr, int left, int right) {
	int hole = left;
	int tmp = arr[left];

	int Mid_keyi = GetmidIndex(arr, left, right);
	//获取三数中间值的下标
	Swap(&arr[hole], &arr[Mid_keyi]);

	while (left < right) {

		while (left < right && arr[right] >= tmp) {//在移动的过程中 
			//left和right可能不会满足left<right(即使是最外循环条件)
			right--;
		}//右找小

		arr[hole] = arr[right];
		hole = right;

		while (left < right && arr[left] <= tmp) {
			left++;
		}//左找大

		arr[hole] = arr[left];
		hole = left;
	}

	//left == right
	arr[hole] = tmp;

	return hole;
}

//3. 前后指针法  同样是选left为keyi 定义两个“指针”prev cur，cur往前走 走到大于key值的
//cur++，小于key值 prev++，并交换cur和prev指向的值 cur++这样 cur和prev之间存的都是大于key的数
//当cur走出数组时，将prev的值与key值交换并将prev作为新的keyi返回
int Quick_part3(int* arr, int left, int right) {
	int keyi = left;
	int prev = left;
	int cur = left + 1;

	int Mid_keyi = GetmidIndex(arr, left, right);
	//获取三数中间值的下标
	Swap(&arr[keyi], &arr[Mid_keyi]);

	while (cur <= right) {

		if (arr[cur] < arr[keyi] && cur != ++prev) {//指向一样就不交换了
			Swap(&arr[prev], &arr[cur]);
		}

		cur++;
	}//cur出界

	Swap(&arr[prev], &arr[keyi]);

	return prev;
}

//优化2：当待排的数据中有大量 相同的数据时 因为我们设计的快排 是碰到相同的数继续走 
//极端想 如果全是一个数排序 那就一直走 就成O(N^2)了
//这里给出三路划分优化 结合霍尔和前后指针思想 将整个数据划分为 小于key值的区间，等于key值的区间
//大于key值的区间
//这里从新搞一个快排 因为 不止一个位置要返回
void QuickSort_Threedivide(int* arr,int  left,int right) {
	if (left >= right)
		return;

	int Midkey = GetmidIndex(arr, left, right);
	Swap(&arr[left], &arr[Midkey]);//三数取中

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
			Swap(&arr[cur++], &arr[l++]);//l永远指向那个key
		}

		if (arr[cur] == arr[l]) {
			cur++;
		}//cur和l之间全是和key值相同的值
	}//此时cur>r
	//[left,l-1][l,r][cur,right]

	QuickSort_Threedivide(arr, left, l - 1);
	QuickSort_Threedivide(arr, cur, right);
	//前序的思想
}

void QuickSort(int* arr,int left, int right) {
	if (left >= right) {
		return;
	}//left == right区间只有一个值 不需要排
	//left>right区间不存在 返回

	int keyi = Quick_part1(arr, left, right);
	//区间划分为[left,keyi-1] keyi [keyi+1 right];

	QuickSort(arr, left, keyi - 1);
	QuickSort(arr, keyi + 1, right);
}

//快排的非递归实现
//非递归实现其实是比递归难的 递归转非递归 有斐波那契那样的
//也有纯循环迭代的 当然也还有 利用栈实现的 因为栈很像递归 先进到深处 在倒退回来
//下面利用栈实现快排的非递归
void QuickSort_noR(int* arr, int left, int right) {
	//发现 递归下来的快排 画出递归展开图像是二叉树的结构  利用栈向里面压入区间值
	//区间是两个端点 一次push两个值 一次也pop两个值

	ST st;
	STiniti(&st);
	STPush(&st, right);
	STPush(&st, left);//先push 右端点 再左端点 取的时候先取左端点 再右端点

	while (!STisEmpty(&st)) {
		int begin = STtop(&st);
		STPop(&st);

		int end = STtop(&st);
		STPop(&st);

		int keyi = Quick_part1(arr, begin, end);
		//[begin,keyi-1] keyi [keyi+1,end]

		//和上面一样 压入顺序 先右后左 取出顺序 先左后右
		if (keyi + 1 < end) {//如果只有一个元素 或区间不存在 不许压栈 不需排序
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
//其实也可以用队列实现 就像层序那样 因为快排本身就像一个前序一样
//栈是深度优先 队列是广度优先

//向下调整
void AdjustDown(int* arr, int n, int parent) {//升序建大堆

	int child = parent * 2 + 1;//左孩子

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

	for (int i = (n - 1 - 1) / 2; i >= 0; i--) {//向下调整建堆
		AdjustDown(arr, n, i);
	}

	while (n) {
		Swap(&arr[0], &arr[n - 1]);
		n--;
		AdjustDown(arr, n, 0);
	}
}

void SelectSort(int* arr, int n) {//选择排序就是一个一个选
	/*for (int i = 0; i < n-1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (arr[i] > arr[j])
				Swap(&arr[i], &arr[j]);
		}
	} 普通的选择排序 这里给出优化后的 选择排序是
	一趟一趟选出最值，次值，次次值...  这里给出优化后 每一趟选出两个最值 一个这一趟
	的最大值，一个这一趟的最小值  一个这趟的最大值*/

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
	}  不是这样的的...*/

	int begin = 0, end = n - 1;
	while (begin < end) {
		int maxi = begin;
		int mini = begin;//保存最大最小下标

		for (int i = begin; i <= end; i++) {
			if (arr[i] > arr[maxi])
				maxi = i;
			if (arr[i] < arr[mini])
				mini = i;
		}

		Swap(&arr[begin], &arr[mini]);//小的前移
		if (begin == maxi)//如果begin和maxi重合 那么原有的max会到原来的mini地方
			Swap(&arr[mini], &arr[end]);
		else
		    Swap(&arr[maxi], &arr[end]);

		begin++;
		end--;
	}
}

//这里归并是二路归并 我说的归并组指的是 这两组数据要归并成一组 而这两组 合称归并组
//归并组第一组 归并组第二组 就是 二分后的归并组


//归并排序 唯一可以进行外排序的排序 其递归实现比较简单 主要也是二叉树的结构的递归 二分区间
//这里是数组的归并 而非链表 数组的归并是要借助第三方空间 取存储归并后有序序列再拷回原数组的
//链表可以将节点摘下来 不需要辅助空间 在链表oj里也有练过 这里为了方便也将一趟归并 封装成函数
void _MergeSort(int* arr,int left,int right,int* tmp) {
	if (left == right)//这个只会存在区间只有一个元素 而不存在区间不存在的情况
		return;       //因为区间是这样划分的[left,mid][mid+1,right]

	//这里给出小区间优化 原因是 当归并递归到最下层时 每组的数据量已经被分割的很小了
	//但还是要用递归去解决 未免有点大材小用 这里让 当该归并组的数据<10时去用更好的排序去排
	//这里选用插入
	if (left - right + 1 < 10) {
		InsertSort(arr+left, left - right + 1);
		return;
	}//这是一个二二叉树 越底层 组越多 节省的时间越多 但 这些时间是插入排序这些数据 相较于 递归的时间
	             
	int mid = (left + right) / 2;
	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;

	int j = left;//归并的区间存到tmp里下标要一致

	_MergeSort(arr, left, (left + right) / 2, tmp);
	_MergeSort(arr, (left + right) / 2 + 1, right, tmp);
	//先让左右区间有序 再归并有序 是一种后序的思想

	while (begin1 <= end1 && begin2 <= end2) {
		if (arr[begin1] <= arr[begin2]) {
			tmp[j++] = arr[begin1++];
		}
		else {
			tmp[j++] = arr[begin2++];
		}
	}//出来 肯定有一个走到end1后边了

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
	//不适合在这个函数递归 因为有动态开辟

	_MergeSort(arr, 0, n - 1, tmp);

	free(tmp);
}


//非递归实现归并排序
//归并的非递归不能利用栈 因为归并是一种后序的思想 左右子树有序 根有序
//栈是一种前序的思想 队列是层序的思想 这里利用纯循环迭代的思想来搞定 这个非递归
//稍稍有点麻烦 注意好区间的范围就行
void MergeSort_noR(int* arr, int n) {
	int* tmp = (int*)malloc(sizeof(int) * n);
	
	int gap = 1;
	//归并是二归一 gap确定这个二的每个组的个数

	while (gap < n) {

		int j = 0;//j在for循环里是跟着归并的数量走的 j来遍历tmp数组

		for (int i = 0; i < n;i += 2 * gap) {
			//通过i来划分每次归并的两组 
			int begin1 = i, end1 = begin1 + gap - 1;
			int begin2 = begin1 + gap, end2 = begin2 + gap - 1;

			//下面对gap下的两组进行归并 当然随着循环的进行，
			// 归并组的向后推进，有可能出现 区间越界的情况
			//这里给出所有的情况
			//begin1是不会越界的 循环条件就是begin1<n
			//情况1： end1越界 后面区间必越
			//情况2： 第一个区间存在 begin2越界 end2必越
			//情况3： begin2没越界 但end2越了 
			//当然最好的就是刚刚好 两个区间都存在 刚好搞定
			
			if (end1 >= n) {
				break;//不用归并了 不成两组
			}
			else if (begin2 >= n) {
				break;//同理
			}
			else if(end2 >= n){//begin2 < n
				//可以归并 但要调整第二个区间 让其不越界
				end2 = n - 1;
			}

			while (begin1 <= end1 && begin2 <= end2) {

				if (arr[begin1] <= arr[begin2]) {
					tmp[j++] = arr[begin1++];
				}
				else {
					tmp[j++] = arr[begin2++];
				}

			}//出来 肯定有一个走到end1后边了

			while (begin1 <= end1) {
				tmp[j++] = arr[begin1++];
			}

			while (begin2 <= end2) {
				tmp[j++] = arr[begin2++];
			}

			//归并一组 拷贝一组
			memcpy(arr + i, tmp + i, sizeof(int) * (end2 - i + 1));
		}

		gap *= 2;
	}

	free(tmp);
}
//这里还有一种方法 就是 上面是归并一组 拷贝一组 相对好理解一点 因为 循环到越界的归并组时
//是直接break的 这里给出 全copy回数组的思想 因为越界的时候就不能归并了 相较于break这里调整
//区间 对于end1越界的时候 将end1=n-1，后面的区间 调整为一个不存在的区间 让他没有去归并的机会
//因为归并的条件是两个区间都存在(左<=右)这里设置让左>右
/*
 if(end1 >= n){
   end1 = n-1;
   begin2 = n;
   end2 =n - 1; 这里就让begin2 > end2了
 }
 else if(begin2 >= n){
   begin2 = n;
   end2 =n - 1;
 }
 else if(end2 >= 2){
   end2 = n - 1; 
   
 }

 //归并。。。。

 memcpy(arr,tmp,sizeof(int)*n);

 主要就是让他不走循环 但又可以让这组归并的第一个组 写到tmp里 然后将tmp的所有数据
 全copy到arr里

 如果设置begin2 和 end2 让其都等于n-1 则这会进入归并
 而j是跟着归并组的数量走的 这里该组归并 有重叠的值 但j不知道 他只管++这就导致 tmp数组会越界
 总之 越界的时候 让归并组第二组设置不存在区间 不让他进入归并 让后让第一个有效组 去copy数据
*/


//计数排序 实际意义不大 有局限性 只能排整数  而且必须是数值浮动不大的数据
//这个排序不涉及比较 而是巧妙的利用了 数组的下标 来进行 排序 
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
	}//找出里面的数据最大最小值

	int* tmp = (int*)malloc(sizeof(int) * (max - min + 1));//我能存储这个范围的所有数字
	                                                    //下标意义上

	for (int i = 0; i < n; i++) {
		tmp[i] = 0;
	}

	//遍历数组 记录每个数出现的次数
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