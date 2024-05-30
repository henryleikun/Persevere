#pragma once
#include "RBtree.h"

namespace Henry {
	template<class K>
	class set {
		struct SetKeyofValue {
			const K& operator()(const K& key) {
				return key;
			}
		};
	private:
		RBtree<K, K, SetKeyofValue> rbtree;
	public:
		//keyֵ�ǲ������޸ĵ� ��setֻ��һ��keyֵ ������������ͳ������������ɺ�����ĳ������������
		//�����и�С֪ʶ�� ��������������޶���::�Ľ��Ҫô�����еľ�̬��Ա���Ա����Ҫô�Ƕ�Ӧ���������ͱ���
		//�ڲ��� ������û��ʵ����ʱȥ�����typedef ����������֪�������const_iterator�Ǿ�̬��Ա����
		//�������� ����ʱҪ����typename���߱����� ������������
		typedef typename RBtree<K, K, SetKeyofValue>::const_iterator iterator;
		typedef typename RBtree<K, K, SetKeyofValue>::const_iterator const_iterator;

		pair<iterator,bool> insert(const K& key) {
			return rbtree.Insert(key);//���ص�pair���iterator����ͨ������ �������iterator
			//ʵ������const_iterator ����ת�� 
			//���� template<class U, class V> pair (const pair<U,V>& pr);����pair�ĸ��ƹ��캯��
			//������캯����nb ��һ��ģ�庯�� ���U V�ͱ�pair��ģ�������ͬ������ͨ�ĸ��ƹ��� �������ͬ
			//����֧�� U V��Ӧ��Ա����ȥ��ʼ����pair�ĳ�Ա��first(pr.first)���� �Ǿ���һ�����캯�� 
			//����������������iterator�ܷ�ȥ��ʼ��const_iterator��Ȼ���� ������ʵ����const_iterator�Ĺ��캯��
			//�ܹ�����iterator��Ϊ�������� �����ʹ��һ�ָ������� ��Insert����pair<Node*,bool>Node* ����
			//����iteratorҲ�ܹ���const_iterator
		}

		void inorder() {
			rbtree.Inorder();
		}

		bool find(const K& key) {//set��find���ǿ���û��
			if (rbtree.Find(key)._pnode) {//Find���ص�����
				return true;
			}
			else {
				return false;
			}
		}
        
		//��������������ͨ����ͳ����󶼿��Ե��� û������ ��Ϊ�����iteratorʵ����const_iterator
		//���÷ֱ�ʵ�� ��ͨ�汾�ͳ��汾
		iterator begin() const {
			return rbtree.cbegin();
		}

		iterator end() const{
			return rbtree.cend();
		}

	};
}
