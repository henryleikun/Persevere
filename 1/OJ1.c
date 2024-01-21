#define _CRT_SECURE_NO_WARNINGS 1


//给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。
//
//不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。
//
//元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素
//
//示例 1：
//
//输入：nums = [3, 2, 2, 3], val = 3
//输出：2, nums = [2, 2]
//解释：函数应该返回新的长度 2, 并且 nums 中的前两个元素均为 2。你不需要考虑数组中超出新长度后面的元素。
//例如，函数返回的新长度为 2 ，而 nums = [2, 2, 3, 3] 或 nums = [2, 2, 0, 0]，也会被视作正确答案。

//--------------------------------------------------------------------------------------


//同样可以暴力  遍历数组 当遍历到val的元素时 将后面元素覆盖掉 就好像 vector里的erase方法
//这里给出双指针法(快慢指针？) 定义两个index 充当指针
//定义src 和dst均指向数组第一个元素  这里src充当探路指针 他指向的值是否为val决定了 src 和dst的移动
//当src指向的值是val时src++ dst不动 只要 src指向的值不是val 就将src指向的值赋给dst指向的值 
//同时src 和dst++ 最终dst的值就是删除val后数组的长度 因为dst每++一次 意味着有一个非val值将到dst这个
//地方


#include <stdio.h>


int removeElement(int* nums, int numsSize, int val) {
	int src=0,dst = 0;

	while (src != numsSize) {
		if (nums[src] == val)
			src++;
		else {
			nums[dst++] = nums[src++];
		}
	}

	return dst;
}

int main() {
	int nums[4] = { 3, 2, 2,3 };

	int ret=removeElement(nums, 4, 3);
	for (int i = 0; i < ret; i++)
		printf("%d ", nums[i]);
	printf("\n");
	
	return 0;
}
