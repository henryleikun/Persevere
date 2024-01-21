#define _CRT_SECURE_NO_WARNINGS 1

//�����ʵ��һ��������ͷ����  
//����ʹ�ñȽ϶�ľ��ǵ�����ͷ��ѭ������� ˫����ͷѭ������

#ifndef _SLIST_H
#define _SLIST_H

typedef int Datatype;

typedef struct ListNode {
	Datatype data;
	struct ListNode* next;
}ListNode;
//���

//������ͷ�������ڿ����½ڵ��Լ�ɾ�����ʱҪ���� ͷָ��Ĵ��� 
//�����ڲ���/ɾ�������Ĳ����� ��� �Ƕ�ͷָ����в����Ļ� Ӧ�ô�����ָ�� ��Ϊ������ı�ָ���ָ��
//����ͷָ��ָ���µĽ��  �����ǲ���Ҳ������ɾ�����µģ�
//��ʹ��һ��ָ�� ��ʵ��ָ���ֵ ����ָ����˵ ����ֵ���� ���� ���ܸı�ԭָ���ָ�� ����ָ��ָ���λ����
//��ַ���� ����������ҿ��ܻ������ָ�뱾�� ���� ����Ӧ��Ϊ����ָ��
//һ��ָ�� phead��ӳ���� ����ĵ�һ���ڵ��Ƿ񴴽�������(*phead ~ListNode)
// ����ָ�� pphead��ӳ���� ָ�������һ������ָ����û�е�����(*pphead~&ListNode)
 

//��c++linkedlist��������� ��ΪNode* head��һ��public��Ա���÷���ʱһֱ�Ƕ����ͷָ����в���
//����c++���� һ��ָ���ok  �� �Ǹ�ѧ����Ϣ����ϵͳ�� û���漰������ָ�� ����Ϊ ���Ǹ���ͷ����
//�ڿ����½ڵ��ʱ�� �Ƕ�head->next���в��� ��headָ���λ�ò��� ���Ƕ�ָ�뱾����в���
//����Ҳ��һ��ָ��  

//���� ��Ҫ����ͷ����ѭ��������в����Ļ�  ��Ҫ���ǵ�����ָ������� �Ժ������ε�ֵ���ݺ͵�ַ����
//�и���������˽�

//�����ڵ�
ListNode* BuyNode(Datatype elem);



//����Ĳ����ɾ�� ���԰�Ԫ���� ������find����ȥ�ҵ��洢��ӦԪ�ؽ��ĵ�ַ
//�ҵ��Ļ� ���ж�Ӧ����ɾ�� 
// Ҳ���԰�λ�������в����ɾ�� ��Ӧ�����Ĳ�����һ�����ĵ�ַ ���Ŷ������
// �������ַ��� Ϊ���Ƕ���Find������ʹ�÷�Χ��ͬ ��һ�����ں����ڲ�ʹ��Find �ڶ������ں����ⲿ
// ��ǰʹ��Find�õ�����ַ���뺯�� ����ʹ�ú���


//�����
void Listinsert(ListNode** pphead,ListNode* pos, Datatype elem);//��������posλ�õ�ǰ���
//ע��Ҫ���posָ�����ǰ��

//����ɾ
void Listerase(ListNode** pphead,ListNode* pos);

//β��
void Pushback(ListNode** pphead, Datatype elem);
//����insert���� ��ӦposΪNULL���������

//ͷ��
void Pushfront(ListNode** pphead, Datatype elem);


//βɾ
void Popback(ListNode** pphead);


//ͷɾ
void Popfront(ListNode** pphead);


//��ӡ
void Print(ListNode* phead);//���һ��ָ����� �Ƕ�������� �����ͷָ�����


//����
ListNode* Find(ListNode* phead, Datatype elem);


//�޸�
void  Modify(ListNode** pphead, ListNode* pos);

//����
void Destroy(ListNode** pphead);

#endif


