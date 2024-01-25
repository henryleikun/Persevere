#define _CRT_SECURE_NO_WARNINGS 1

//˫������ ����˫����ͷѭ������ �͵����������õ����
//����Ҫʵ��˫������Ļ������� 
//�������ﲻ�ܴӺ���ǰ���� ֻ��һ�������ߵ��� �������˫������ ����ѭ������˫�� ����������
//ʱ�临�Ӷȵ� ��Ȼ�����ÿռ�������

//������ͷ��  ���ڱ�λ ��ʼ������ʱ ͷָ���Ͷ���������� ��������һ�㲻�����ͷָ���ָ��  
// ���Զ�ͷָ������ һ��ָ��͹��� ��Ȼ���Ҫ�޸�ͷָ���ָ�� ҲҪ���Ƕ���
//ָ�� ���ʼ�� ������

typedef int Datatype;

typedef struct ListNode {
	Datatype data;
	struct ListNode* prev;
	struct ListNode* next;
}ListNode;


//��ʼ�� 
void Listinit(ListNode** pphead);

//���ٽڵ�
ListNode* BuyNode(Datatype elem);

//����
ListNode* Find(ListNode* phead, Datatype elem);


//�����ɾ�� ����������������д�� ����������ɾ ������ͷ��βɾ������������ʵ��
//������Ҳ���Զ��ֱ�ʵ�� ��Ȼ ��ʱ˫���� ʵ������ֻҪ�߼����� ����д�����ܼ�

//β��
void Push_back(ListNode* phead, Datatype elem);

//ͷ��
void Push_front(ListNode* phead, Datatype elem);

//����� ָ��λ��֮�����(�ϸ���������ָ��λ��֮ǰ���� �����)
void Listinsert(ListNode* pos, Datatype elem);

//ͷɾ
void Pop_front(ListNode* phead);

//βɾ
void Pop_back(ListNode* phead);

//����ɾ
void Listerase(ListNode* pos);

//��ӡ
void Print(ListNode* phead);

//����
void Destroy(ListNode* phead);//����ı���ͷָ���ָ�� �����ǽӿڵ�һ���� ������һ��ָ�봦��
//ͨ��phead�ͷŵ����п��ٹ��Ŀռ� ������ⲿ��pheadָ��NULL