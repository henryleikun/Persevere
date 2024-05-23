#define _CRT_SECURE_NO_WARNINGS 1
//��Ҫ�Ͷ������ķǵݹ�����͹���������ʵ��
//������ܻ��Ჹ��һЩ�������Ļ����ӿ�ʵ��
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <vector>
using namespace std;
typedef int BTdatatype;

typedef struct BTnode {
	BTdatatype _val;
	BTnode* _left;
	BTnode* _right;

	BTnode(BTdatatype val = BTdatatype()):_val(val),_right(nullptr),_left(nullptr) {

	}
};//���ڵ�

BTnode* BuyNode(BTdatatype val) {
	BTnode* newnode = new BTnode(val);
	
	return newnode;
}

BTnode* BT_creat_by_hand() {//Just for test
	BTnode* node1 = BuyNode(1);
	BTnode* node2 = BuyNode(2);
	BTnode* node3 = BuyNode(3);
	BTnode* node4 = BuyNode(4);
	BTnode* node5 = BuyNode(5);
	BTnode* node6 = BuyNode(6);
	BTnode* node7 = BuyNode(7);

	node1->_left = node2;
	node1->_right = node3;
	node2->_left = node4;
	node3->_left = node5;
	node3->_right = node6;
	node2->_right = node7;

	return node1;//���ظ��ڵ�
}

int BTreeSize(BTnode* root) {//��������Ľڵ����  ����������������������������������1
	if (root == NULL)
		return 0;

	return BTreeSize(root->_left) + BTreeSize(root->_right) + 1;
}


//�������ٶ�����
void BTreeDestroy(BTnode* root) {
	if (root == NULL)
		return;

	BTreeDestroy(root->_left);
	BTreeDestroy(root->_right);
	delete root;
}

//���µ��� �������� �������
//˼�룺�Ӹ���ʼ������ ����ʱ����������ѹ�룬������ѹ������ѹ�ң��ٽ��ղų��Ľ�ջ
void Level_order_reverse(BTnode* root) {
	if (root == nullptr)
		return;

	queue<BTnode*> q;
	stack<BTnode*> s;

	q.push(root);

	while (!q.empty()) {
		BTnode* temp_node = q.front();
		q.pop();

		if (temp_node->_left)
			q.push(temp_node->_left);

		if (temp_node->_right)
			q.push(temp_node->_right);

		s.push(temp_node);
	}

	while (!s.empty()) {
		cout << s.top()->_val << " ";
		s.pop();
	}

}

//�ǵݹ�ʵ��ǰ��������������
void Prevorder_noR(BTnode* root) {//ǰ��
	BTnode* cur = root;

	vector<BTdatatype> v;//���������浽v��
	stack<BTnode*> s;//���������

	while (cur || !s.empty()) {//curΪ����s��Ҳû��Ҫ����Ľ����
		
		while (cur) {//��ǰ������Ϊ�� ����������ջ
			v.push_back(cur->_val);//��ջ��ͬʱҲ���ڷ���

			s.push(cur);
			cur = cur->_left;
		}//�ڽ�ջ��ͬʱ��ʵҲ�Ѿ������˸� �����һ����������null ������һ�����Ƿ�����
		//�������������Ҳ��Ӧ���ϸ����ڵ���� ���Խ��ŷ����� Ҳ����stack���top
		

		BTnode* temp = s.top();
		s.pop();

		cur = temp->_right;
	}

	for (auto e : v) {
		cout << e << " ";
	}

	cout << endl;
}

void Inorder_noR(BTnode* root) {//����
	BTnode* cur = root;//��ʵ���ø��cur ���Ҳ�����root root�ڵݹ��￴�űȽ����
	
	stack<BTnode*> s;
	vector<BTdatatype> v;


	//������������ȫ��ջ ���Ȳ����� ��ջ��ȡ������ʱ���ٷ���
	while (cur || !s.empty()) {
		while (cur) {
			s.push(cur);
			cur = cur->_left;
		}//������ʱ���൱���Ѿ����ʹ��������� ������Ƿ���ջ����Ǹ�

		BTnode* temp = s.top();
		s.pop();
		v.push_back(temp->_val);//��ʱ�����

		cur = temp->_right;
	}

	for (auto e : v) {
		cout << e << " ";
	}

	cout << endl;
}
//ǰ����������� ˼·�����ȱ����������ף�Ȼ���ջ���任����˳��ȥ���б���
//ע������ѭ������������

/*
�ǵݹ�ʵ�ֺ������
������������ǰ����������ͬ �ҿ���������һ�����Ʒ���˳��
��������������ջ Ȼ����� ������� �������� Ȼ���Ҫ����ջ���һ���� �������������Ҫ��һ��ѭ��
ͬ�����߼� ��Ҫ����������ʵ�Ѿ��߹��ˡ�����һ��flag���ԣ� ���� ��ΪҪ��������� �����㲻����һ��
flag��ʾ ���Ե�һ���������Ǹ�ÿ����㶼����һ��flag 0��ʾû���ʹ���1��ʾ���ʹ���
��һ��ջ������ѭ���Ľ������洢��Щflagֵ  ���������������Ƚ��˷ѿռ�
�����еڶ���������������һ��prevָ����ָ����һ�η��ʵĽ�� ����˼·�ǣ�
������������ջ ���õ������ �ж� �����ұ��Ƿ�Ϊ�� �����Ƿ��ѷ��ʹ� Ϊ�ջ��ѷ��ʹ��ͶԸ����� Ȼ��pop��
���Ŷ�ջ����һ��������;��Ϊ�� �Ͷ��������������⴦�� ������һ��ѭ��*/
void Backorder_noR(BTnode* root) {
	BTnode* cur = root;
	BTnode* prev = nullptr;
	stack<BTnode*> s;
	vector<BTdatatype> v;

	while (cur || !s.empty()) {
		while (cur) {
			s.push(cur);
			cur = cur->_left;
		}//������ȫ��ջ

		BTnode* top = s.top();
		
        //top������Ϊ�ջ��������ѱ����ʹ�(prev == top->_right)
		if (top->_right == nullptr || prev == top->_right) {//���ʹ� ���߲��÷��� ֻ��Ҫ����top������
			v.push_back(top->_val);
			s.pop();
			prev = top;//��¼
		}
		else {//û���ʹ� ������������������������
			cur = top->_right;
		}
	}

	for (auto e : v) {
		cout << e << " ";
	}

	cout << endl;
}


//��֪ǰ������� ������Ӧ������
//�������ȥȷ���ݹ麯���Ĳ�����
//root���������� �϶������� ��Ӧ����������Ҳ�϶�Ҫ��
//i������preorder��ĸ����±� [begin,end]��������Ҫ�о�������
//��Ϊͨ��ǰ���i�����ҵ��� ��ͨ����������Խ����򻮷ֳ���������begin k-1 k+1 end
//��i����һ��λ�� i+1�ض�Ҳ��һ���� ����֪���������ĸ���(k-1 - begin + 1)
//i + �����ڵ���� + 1�������������±�Ȼ����ǽ���Ӧ��������������ݹ���ȥ �����±�Ҳ��
void _buildTree_by_pre_in(BTnode*& root, vector<int>& preorder, int i, vector<int>& inorder, int begin, int end) {
	if (begin == end) {
		root = new BTnode(inorder[begin]);
		return;
	}
	else if (begin > end)
		return;

	for (int k = begin; k <= end; k++) {
		if (preorder[i] == inorder[k]) {
			root = new BTnode(preorder[i]);
			//begin k-1 k+1 end
			_buildTree_by_pre_in(root->_left, preorder, i + 1, inorder, begin, k - 1);
			_buildTree_by_pre_in(root->_right, preorder, i + k - begin + 1, inorder, k + 1, end);
			return;
		}
	}
}

//�������������
BTnode* _buildTree_by_pre_in2(vector<int>& pre, int& prei, vector<int>& in,
	int begin, int end) {
	if (begin > end)
		return nullptr;

	int k = begin;
	while (k <= end) {
		if (pre[prei] == in[k]) {
			break;
		}

		k++;
	}

	//ǰ�����ȷ��ʸ� prei++�Ϳ��Գ�Ϊ��һ����
	BTnode* root = new BTnode(pre[prei++]);
	root->_left = _buildTree_by_pre_in2(pre, prei, in, begin, k - 1);
	root->_right = _buildTree_by_pre_in2(pre, prei, in, k + 1, end);

	return root;
}
//����������˼·������һ�µģ���Ҫ���㲻ͬ��һ�ǵݹ麯���ķ���ֵ �ҵ��ǿ�
//����Ҫ����root������ ֱ���ڵݹ��ͬʱ������������ ������Ҫ�� ͨ���ݹ�ķ���ֵ
//���н��д��� ���� �Ҷ�ǰ�����и�λ�õ�ȷ�� ����ͨ��prei������ ÿ�㶼++
//��++������һ������ʹ�� �ڻ��������ͬʱҲ������ǰ������У�������ͨ�� 
//ǰ��ĸ���ȷ������ �ٸ�������ĳ���(������ �������Ľڵ����)ֱ��������Ӧ��
//���ĸ��±�

BTnode* buildTree_by_pre_in(vector<int>& preorder, vector<int>& inorder) {
	BTnode* root;
	_buildTree_by_pre_in(root, preorder, 0, inorder, 0, inorder.size() - 1);
	return root;

	// int index = 0;
	// return _buildTree_by_pre_in2(preorder,index,inorder,0,inorder.size()-1);
}


//��֪����ͺ��򹹽���Ӧ������
//����ǰ�� ������ ����͵����� �ȸ� �������� �������� ����Ͱ������˼·д��
BTnode* _buildTree_by_in_post(vector<int>& inorder, int begin, int end
	, vector<int>& postorder, int& index) {
	if (begin > end)
		return nullptr;

	int k = begin;
	while (k <= end) {
		if (inorder[k] == postorder[index])
			break;

		++k;
	}//�ҵ�k ������������Ϊ begin k-1 k+1 end

	BTnode* root = new BTnode(postorder[index--]);
	root->_right = _buildTree_by_in_post(inorder, k + 1, end, postorder, index);
	root->_left = _buildTree_by_in_post(inorder, begin, k - 1, postorder, index);

	return root;
}


BTnode* buildTree_by_in_post(vector<int>& inorder, vector<int>& postorder) {
	int index = postorder.size() - 1;
	return _buildTree_by_in_post(inorder, 0, inorder.size() - 1, postorder, index);
}

int main() {
	//BTnode* root = BT_creat_by_hand();

	/*cout << "ǰ��";
	Prevorder_noR(root);
	cout << "����";
	Inorder_noR(root);
	cout << "����";
	Backorder_noR(root);*/

	//BTreeDestroy(root);

	//=======================================================
	vector<int> preorder{ 3,9,20,15,7 };
	vector<int> inorder{ 9,3,15,20,7 };

	BTnode* root = buildTree_by_pre_in(preorder,inorder);

	Backorder_noR(root);//�������һ��

	return 0;
}