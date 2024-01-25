#define _CRT_SECURE_NO_WARNINGS 1

//双向链表 即是双向有头循环链表 和单链表两个用的最多
//这里要实现双向链表的基本功能 
//单链表里不能从后往前处理 只能一个方向走到死 而这里的双向链表 又是循环又是双向 处理起来简单
//时间复杂度低 当然这是用空间来换的

//这是有头的  有哨兵位 初始化链表时 头指针和投机点锁死了 后续操作一般不会更改头指针的指向  
// 所以对头指针来讲 一级指针就够了 当然如果要修改头指针的指向 也要考虑二级
//指针 像初始化 和销毁

typedef int Datatype;

typedef struct ListNode {
	Datatype data;
	struct ListNode* prev;
	struct ListNode* next;
}ListNode;


//初始化 
void Listinit(ListNode** pphead);

//开辟节点
ListNode* BuyNode(Datatype elem);

//查找
ListNode* Find(ListNode* phead, Datatype elem);


//插入和删除 可以像单链表那样先写出 任意插和任意删 后续的头插尾删等依靠这两个实现
//但这里也可以都分别实现 当然 这时双链表 实现起来只要逻辑清晰 代码写起来很简单

//尾插
void Push_back(ListNode* phead, Datatype elem);

//头插
void Push_front(ListNode* phead, Datatype elem);

//任意插 指定位置之后插入(上个单链表是指定位置之前插入 都差不多)
void Listinsert(ListNode* pos, Datatype elem);

//头删
void Pop_front(ListNode* phead);

//尾删
void Pop_back(ListNode* phead);

//任意删
void Listerase(ListNode* pos);

//打印
void Print(ListNode* phead);

//销毁
void Destroy(ListNode* phead);//这个改变了头指针的指向 但考虑接口的一致性 这里用一级指针处理
//通过phead释放掉所有开辟过的空间 最后在外部将phead指向NULL