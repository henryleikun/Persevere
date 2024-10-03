#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <stack>
#include <iomanip>
#include <queue>
#include <functional>
#include "UnionFindSet.h"
using namespace std;

//�ڽӱ�
namespace Link {
	template<class W>
	struct Edge {
		int _srci;
		int _dsti;
		W _w;
		struct Edge<W>* next;

		Edge(int srci = 0, int dsti = 0, W w = W())
			:_srci(srci), _dsti(dsti), _w(w), next(nullptr) {

		}
	};

	//WȨֵ����
	template<class V, class W, bool Def = false>//Ĭ������ͼ
	class Graph {
	private:
		vector<V> _vertex;//�±�ӳ�䶥��
		map<V, size_t> _indexMap;//����ӳ���±�
		vector<Edge<W>*> _link;//�ڽӱ�
	public:
		Graph() = default;

		//����ͼ�ķ�����������I/O�������Ƕ��ļ�������Ϊ�˷������
		//��ֱ�����ö��㼯���й��죬Ȼ���ֶ���ӱ�
		Graph(const vector<V>& vertex) {//���캯����һ�֣�vector�����й���
			size_t n = vertex.size();
			_vertex.reserve(n);

			for (size_t i = 0; i < n; ++i) {
				_vertex.push_back(vertex[i]);
				//_indexMap.insert(make_pair(vertex[i], i));
				_indexMap[vertex[i]] = i;
			}

			_link.resize(n);
		}

		size_t GetIndexofVertex(const V& vertex) {
			//if (_indexMap.count(vertex) == 0) {
			//	return -1;//û�ж�Ӧ�±�
			//}

			//return _indexMap[vertex];

			auto ret = _indexMap.find(vertex);
			if (ret != _indexMap.end())
				return ret->second;
			else {
				throw invalid_argument("�����ڵĶ���");
				return -1;
			}
		}

		//��� �յ� Ȩֵ
		void AddEdge(const V& src, const V& dst, const W& w) {
			size_t srci = GetIndexofVertex(src);
			size_t dsti = GetIndexofVertex(dst);

			Edge<W>* newnode = new Edge<W>(srci, dsti, w);
			newnode->next = _link[srci];
			_link[srci] = newnode;

			//���������ͼ �ԳƵ���
			if (Def == false) {
				Edge<W>* newnode = new Edge<W>(dsti, srci, w);
				newnode->next = _link[dsti];
				_link[dsti] = newnode;
			}
			//�����������ڽӱ���ʵ���е����⣬�����Ǽӵı����Ѿ��еıߵĻ�������Ӧ�ò�������
			//����Ͳ�д�ˣ���Ϊ�����������ڽӾ�����������
		}

		void Print() {//���ڽӱ����ʽ��ӡ
			for (int i = 0; i < _vertex.size(); i++) {
				Edge<W>* cur = _link[i];
				cout << "[" << i << "->" << _vertex[i] << "]" << "����>";
				while (cur != nullptr) {
					cout << "[" << cur->_dsti << "->" << _vertex[cur->_dsti] << "]" << "����>";
					cur = cur->next;
				}
				cout << endl;
			}
		}

		//������ȱ���
		void BFS(const V& v) {
			vector<bool> visited(_vertex.size(), false);
			size_t index = GetIndexofVertex(v);
			queue<size_t> q;
			q.push(index);
			visited[index] = true;

			while (!q.empty()) {
				size_t front = q.front();
				q.pop();

				cout << _vertex[front] << endl;
				Edge<W>* cur = _link[front];
				while (cur != nullptr) {
					if (visited[cur->_dsti] == false) {
						q.push(cur->_dsti);
						visited[cur->_dsti] = true;
					}

					cur = cur->next;
				}
			}
		}

		void _DFS(size_t index, vector<bool>& visited) {
			cout << _vertex[index] << endl;
			visited[index] = true;

			Edge<W>* cur = _link[index];
			while (cur != nullptr) {
				if (visited[cur->_dsti] == false) {
					_DFS(cur->_dsti, visited);
				}

				cur = cur->next;
			}
		}

		void DFS(const V& v) {
			vector<bool> visited(_vertex.size(), false);
			size_t index = GetIndexofVertex(v);
			
			_DFS(index, visited);
		}

	};


	void TestGraph1() {
		vector<string> v{ "����","����","����","����","����","���" };
		Graph<string, int> g(v);
		g.AddEdge("����", "����", 1);
		g.AddEdge("����", "����", 1);
		g.AddEdge("����", "����", 1);
		g.AddEdge("����", "����", 1);
		g.AddEdge("����", "���", 1);
		g.AddEdge("���", "����", 1);
		g.AddEdge("����", "���", 1);

		//g.Print();
		//g.BFS("����");
		g.DFS("����");
	}
}

namespace Amatrix{
	//WȨֵ����
	template<class V, class W, W MAX_W = INT_MAX, bool Def = false>//Ĭ������ͼ
	class Graph {
		typedef Graph<V, W, MAX_W, Def> self;
	private:
		vector<V> _vertex;//�±�ӳ�䶥��
		map<V, size_t> _indexMap;//����ӳ���±�
		vector<vector<W>> _matrix;//�ڽӾ���
	public:
		Graph() = default;

		//����ͼ�ķ�����������I/O�������Ƕ��ļ�������Ϊ�˷������
		//��ֱ�����ö��㼯���й��죬Ȼ���ֶ���ӱ�
		Graph(const vector<V>& vertex) {//���캯����һ�֣�vector�����й���
			size_t n = vertex.size();
			_vertex.reserve(n);

			for (size_t i = 0; i < n; ++i) {
				_vertex.push_back(vertex[i]);
				//_indexMap.insert(make_pair(vertex[i], i));
				_indexMap[vertex[i]] = i;
			}

			_matrix.resize(n);
			for (size_t i = 0; i < n; ++i) {
				_matrix[i].resize(n, MAX_W);//�ڽӾ���տ�ʼ������ȫ�������
				//�������Գɻ������Ҳ���������� ����0
			}
		}

		Graph(const initializer_list<V>& vertex) {//���캯����һ�֣���ʼ���б������й���
			size_t n = vertex.size();
			_vertex.reserve(n);

			int i = 0;
			for (auto it = vertex.begin(); it != vertex.end(); ++it) {
				_vertex.push_back(*it);
				//_indexMap.insert(make_pair(vertex[i], i));
				_indexMap[*it] = i;
				i++;
			}

			_matrix.resize(n);
			for (size_t i = 0; i < n; ++i) {
				_matrix[i].resize(n, MAX_W);//�ڽӾ���տ�ʼ������ȫ�������
				//�������Գɻ������Ҳ���������� ����0
			}
		}

		size_t GetIndexofVertex(const V& vertex) {
			//if (_indexMap.count(vertex) == 0) {
			//	return -1;//û�ж�Ӧ�±�
			//}

			//return _indexMap[vertex];

			auto ret = _indexMap.find(vertex);
			if (ret != _indexMap.end())
				return ret->second;
			else {
				throw invalid_argument("�����ڵĶ���");
				return -1;
			}
		}

		void _AddEdge(size_t srci, size_t dsti, const W& w) {
			_matrix[srci][dsti] = w;

			//���������ͼ �ԳƵ���
			if (Def == false) {
				_matrix[dsti][srci] = w;
			}
		}


		//��� �յ� Ȩֵ
		void AddEdge(const V& src, const V& dst, const W& w) {
			size_t srci = GetIndexofVertex(src);
			size_t dsti = GetIndexofVertex(dst);

			_AddEdge(srci, dsti, w);
		}

		//�������� ���ж�ͼ�Ƿ�ɻ� ����Ҫ˼��������Ϊ0�Ľ�����ȴ�ӡ ��ӡ���"ɾ��������Ӧ����"
		void Topsort() {//��ӡ��ͼ����������
			vector<int> indegree(_vertex.size(), 0);//�洢ÿ����������
			stack<size_t> st;//�洢���Ϊ0�Ķ����Ӧ���±�

			size_t n = _vertex.size();
			//��ͳ��ÿ���������ȣ������ڽӾ���
			for (size_t i = 0; i < n; ++i) {
				for (size_t j = 0; j < n; ++j) {
					if (_matrix[i][j] != MAX_W) {//��Ч�ڽӵ�
						indegree[j]++;
					}
				}
			}

			for (size_t i = 0; i < n; ++i) {
				if (indegree[i] == 0)
					st.push(i);//�洢���Ϊ0�Ķ����Ӧ���±�
			}

			while (!st.empty()) {
				size_t index = st.top();
				st.pop();
				cout << _vertex[index] << " ";//ȡ��ɾ���������Ӧ���Ϊ0�Ķ���

				for (size_t i = 0; i < n; ++i) {//����������Ϊ����ڽӵĶ����Ӧ���-1
					if (_matrix[index][i] != MAX_W) {
						--indegree[i];
						if (indegree[i] == 0)
							st.push(i);
					}
				}
			}
		}

		void Print() {//���ڽӾ������ʽ��ӡ
			//�ȴ�ӡ�������ŵĶ�Ӧ��ϵ
			size_t n = _vertex.size();
			for (int i = 0; i < n; i++) {
				cout << _vertex[i] << "����>" << "[" << i << "]" << endl;
			}

			//���Ŀǰ��Ϊ7
			cout << " ";
			for (int i = 0; i < n; i++) {
				cout << setw(7) << i;
			}
			cout << endl;

			for (int i = 0; i < n; i++) {
				cout << i;
				for (int j = 0; j < n; j++) {
					if (_matrix[i][j] == MAX_W) cout << setw(7) << "*";
					else cout << setw(7) << _matrix[i][j];
				}

				cout << endl;
			}
		}

		//������ȱ���
		void BFS(const V& v) {
			vector<bool> visited(_vertex.size(),false);

			size_t index = GetIndexofVertex(v);
			queue<size_t> q;
			q.push(index);
			visited[index] = true;

			while (!q.empty()) {
				int front = q.front();
				V ver = _vertex[front];
				cout << ver << endl;
				q.pop();

				for (int i = 0; i < _vertex.size(); i++) {
					if (_matrix[front][i] != MAX_W && visited[i] == false) {
						q.push(i);
						visited[i] = true;
					}
				}
			}
		}

		//BFSһ��һ���ӡ
		void _BFS(const V& v) {
			vector<bool> visited(_vertex.size(), false);

			size_t index = GetIndexofVertex(v);
			queue<size_t> q;
			q.push(index);
			visited[index] = true;
			size_t floor_num = 1;

			while (!q.empty()) {
				while (floor_num--) {
					int front = q.front();
					V ver = _vertex[front];
					cout << ver << " ";
					q.pop();

					for (int i = 0; i < _vertex.size(); i++) {
						if (_matrix[front][i] != MAX_W && visited[i] == false) {
							q.push(i);
							visited[i] = true;
						}
					}
				}

				cout << endl;
				floor_num = q.size();
			}
		}

		void _DFS(size_t index,vector<bool>& visited) {
			cout << _vertex[index] << endl;
			visited[index] = true;
            
			for (int i = 0; i < _vertex.size(); i++) {
				if (_matrix[index][i] != MAX_W && visited[i] == false) {
					_DFS(i, visited);
				}
			}
		}

		void DFS(const V& v) {
			vector<bool> visited(_vertex.size(), false);
			size_t index = GetIndexofVertex(v);

			_DFS(index,visited);
		}

		struct Edge {
			int _srci;
			int _dsti;
			W _w;

			Edge(int srci = 0, int dsti = 0, W w = W())
				:_srci(srci), _dsti(dsti), _w(w) {

			}

			//����º��� ��Edge�ܱȽ�  
			//Ҫ���ڿ⺯���ĺ���������Ϊ��Ա����ʱ Ҫconst��
			bool operator>(const Edge& rhs) const{
				return _w > rhs._w;
			}
		};

	    W Kruskal(self& Mintree) {//���Ǹ�����Ͳ���
			size_t n = _vertex.size();
			W total_w = 0;
			Mintree._vertex = _vertex;
			Mintree._indexMap = _indexMap;
			Mintree._matrix.resize(n);
			for (int i = 0; i < n; i++) {
				Mintree._matrix[i].resize(n,MAX_W);
			}

			priority_queue<Edge,vector<Edge>,greater<Edge>> edges;
			vector<int> v(n);//�����Ӧ�ı�ż� Ϊ�˸����鼯����(ģ��)
			for (int i = 0; i < n; i++) v[i] = i;
			UnionFindSet<int> ufs(v);

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (i < j && _matrix[i][j] != MAX_W) {//����ͼ�����Ǳ�ֻ�þ�����ϰ����
						edges.push(Edge(i, j, _matrix[i][j]));
					}
				}
			}
			//�������ȼ���������ԭͼ�����б߼���

			while (!edges.empty()) {
				Edge ed = edges.top();
				edges.pop();
				if (!ufs.IsInSet(ed._srci, ed._dsti)) {//���������ɻ�
					Mintree._matrix[ed._srci][ed._dsti] = ed._w;
					total_w += ed._w;
					ufs.Union(ed._srci, ed._dsti);
					n--;
				}
			}

			if (n == 1) return total_w;
			else return -1;//n!=1 ������С������ʧ��
		}

		//���Ҫ��һ�����
		W Prim(self& Mintree,const V& v) {
			size_t index = GetIndexofVertex(v);
			size_t n = _vertex.size();
			W total_w = 0;

			Mintree._vertex = _vertex;
			Mintree._indexMap = _indexMap;
			Mintree._matrix.resize(n);
			for (int i = 0; i < n; i++) {
				Mintree._matrix[i].resize(n, MAX_W);
			}

			vector<bool> minv(n, false);
			minv[index] = true;
			priority_queue<Edge,vector<Edge>,greater<Edge>> edges;
			for (int i = 0; i < n; i++) {
				if (_matrix[index][i] != MAX_W) edges.push(Edge(index, i, _matrix[index][i]));
			}

			size_t size = 0;//n-1����
			while (!edges.empty()) {
				Edge min_ed = edges.top();
				edges.pop();

				//����С�ߵ�������� Ӧ����δѡ����
				if (!minv[min_ed._dsti]) {
					minv[min_ed._dsti] = true;
					Mintree._AddEdge(min_ed._srci, min_ed._dsti, min_ed._w);
					size++;
					total_w += min_ed._w;

					//������¼ӽ����Ķ�����ڽӱ߸������(ֻ��δѡ��)
					for (int i = 0; i < n; i++) {
						if (_matrix[min_ed._dsti][i] != MAX_W && minv[i] == false)
							edges.push(Edge(min_ed._dsti, i, _matrix[min_ed._dsti][i]));
					}
				}

				if (size == n - 1) break;
			}

			if (size == n - 1) return total_w;
			else  return -1;//n!=1 ������С������ʧ��
		}

		void ShortestPath_Print(const V& begin,const vector<W>& dist, const vector<int>& pPath) {
			size_t srci = GetIndexofVertex(begin);
			size_t n = _vertex.size();

			for (int i = 0; i < n; i++) {
				int parent = i;
				vector<int> path;
				while (parent != srci) {
					path.push_back(parent);
					parent = pPath[parent];
				}
				path.push_back(parent);

				reverse(path.begin(), path.end());
				for (auto& e : path) {
					cout << _vertex[e] << "->";
				}

				cout << "���·����" << dist[i] << endl;
			}
		}
		

		//���·����Dijkstra�㷨  dist��pPath������Ͳ���
		void Dijkstra(const V& v,vector<W>& dist,vector<int>& pPath) {
			size_t srci = GetIndexofVertex(v);
			size_t n = _vertex.size();
			vector<bool> SQ(n, false);//ȷ�����·���ļ��� δȷ���Ķ��㼯��
			dist.resize(n, MAX_W);
			pPath.resize(n, -1);
			dist[srci] = W();//�Լ����Լ���0

			for (int k = 0; k < n; k++) {//ÿ��ѭ������ȷ��һ����������·��
				int u = -1;//����Q����������·����Ӧ�Ķ���
				W min = MAX_W;

				//���forѭ������ Q����������̵�·��(������)  һ���ҵõ�
				for (int i = 0; i < n; i++) {
					if (SQ[i] == false && dist[i] < min) {
						u = i;
						min = dist[i];
					}
				}

				SQ[u] = true;//ѡ��ȷ�����·���Ķ���

				//�����ɳ�
				for (int i = 0; i < n; i++) {
					//�����ڽӣ�����δȷ�����·�� �����и��̵�·��
					if (_matrix[u][i] != MAX_W && SQ[i] == false &&dist[u] + _matrix[u][i] < dist[i]) {
						dist[i] = dist[u] + _matrix[u][i];
						pPath[i] = u;//i������һ��������u����
					}
				}
			}

		}

		void BellmanFord(const V& v, vector<W>& dist, vector<int>& pPath) {
			size_t srci = GetIndexofVertex(v);
			size_t n = _vertex.size();
			dist.resize(n, MAX_W);
			pPath.resize(n, -1);
			dist[srci] = W();//�Լ����Լ���0

			for (int k = 0; k < n - 1; k++) {
				bool flag = false;

				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						//Ҫ�ڽ� ������Ч����(�ö����dist��Ӧ����MAX_WҪ��Ȼ�����Խ��) �����и���·��
						if (_matrix[i][j] != MAX_W && dist[i] != MAX_W
							&& dist[i] + _matrix[i][j] < dist[j]) {
							dist[j] = dist[i] + _matrix[i][j];
							pPath[j] = i;
							flag = true;
						}
					}
				}

				//û�и���
				if (flag == false) break;
			}

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (_matrix[i][j] != MAX_W && dist[i] != MAX_W
						&& dist[i] + _matrix[i][j] < dist[j]) {
						cout << "��Ȩ��·�����������·��" << endl;
						return;
					}
				}
			}
		}

		void FloydWarshall(vector<vector<W>>& vvDist,vector<vector<W>>& vvpPath) {
			size_t n = _vertex.size();
			vvDist.resize(n);
			vvpPath.resize(n);
			for (int i = 0; i < n; ++i) {
				vvDist[i].resize(n, MAX_W);
				vvpPath[i].resize(n, -1);
			}

			//�Ȱ�ֱ���Ķ�����е�һ�ֵĳ�ʼ��
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (_matrix[i][j] != MAX_W) {
						vvDist[i][j] = _matrix[i][j];
						vvpPath[i][j] = i;
					}

					if (i == j) vvDist[i][j] = 0;
				}
			}

			//��ÿ���������㶼���Ƿ񾭹����ж�����һ�¼���
			for (int k = 0; k < n; ++k) {
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						if (vvDist[i][k] != MAX_W && vvDist[k][j] != MAX_W
							&& vvDist[i][k] + vvDist[k][j] < vvDist[i][j]) {
							vvDist[i][j] = vvDist[i][k] + vvDist[k][j];
							vvpPath[i][j] = vvpPath[k][j];
						}
					}
				}
			}
		}

	};


	void TestGraph1() {
		vector<string> v{ "����","����","����","����","����","���" };
		//Graph<string, int,INT_MAX,true> g(v);
		Graph<string, int> g(v);
		g.AddEdge("����", "����", 1);
		g.AddEdge("����", "����", 1);
		g.AddEdge("����", "����", 1);
		g.AddEdge("����", "����", 1);
		g.AddEdge("����", "���", 1);
		g.AddEdge("���", "����", 1);
		g.AddEdge("����", "���", 1);

		g.Print();
	}

	void TestGraph2() {
		vector<string> v{ "����","����","����","����","����","���" };

		Graph<string, int> g(v);
		g.AddEdge("����", "����", 1);
		g.AddEdge("����", "����", 1);
		g.AddEdge("����", "����", 1);
		g.AddEdge("����", "����", 1);
		g.AddEdge("����", "���", 1);
		g.AddEdge("���", "����", 1);

		//g._BFS("����");
		g.DFS("����");
	}

	void TestGraph3() {
		vector<char> v = { 'a','b','c','d','e','f','g','h','i' };
		Graph<char, int> g(v);

		g.AddEdge('a', 'b', 4);
		g.AddEdge('a', 'h', 8);
		g.AddEdge('b', 'c', 8);
		g.AddEdge('b', 'h', 11); 
		g.AddEdge('c', 'i', 2);
		g.AddEdge('c', 'f', 4);
		g.AddEdge('c', 'd', 7);
		g.AddEdge('d', 'f', 14);
		g.AddEdge('d', 'e', 9);
		g.AddEdge('e', 'f', 10);
		g.AddEdge('f', 'g', 2);
		g.AddEdge('g', 'h', 1);
		g.AddEdge('g', 'i', 6);
		g.AddEdge('h', 'i', 7);

		Graph<char, int> mintree;
		g.Kruskal(mintree);

		/*cout << "Kruskal Mintree:" << endl;
		mintree.Print();*/

		g.Prim(mintree,'a');
		cout << "Prim Mintree:" << endl;
		mintree.Print();
	}

	void TestGraph4() {
		vector<char> v{ 's','y','z','t','x' };
		Graph<char, int, INT_MAX, true> g(v);//����ͼ
		g.AddEdge('s', 't', 10);
		g.AddEdge('s', 'y', 5);
		g.AddEdge('y', 't', 3);
		g.AddEdge('y', 'x', 9);
		g.AddEdge('y', 'z', 2);
		g.AddEdge('z', 's', 7);
		g.AddEdge('z', 'x', 6);
		g.AddEdge('t', 'y', 2);
		g.AddEdge('t', 'x', 1);

		vector<int> dist;
		vector<int> pPath;
		g.Dijkstra('s', dist, pPath);
		g.ShortestPath_Print('s', dist, pPath);
	}

	void TestGraph5() {
		vector<char> v{ 's','y','z','t','x' };
		Graph<char, int, INT_MAX, true> g(v);//����ͼ

		g.AddEdge('s', 't', 6);
		g.AddEdge('s', 'y', 7);
		g.AddEdge('y', 'z', 9);
		g.AddEdge('y', 'x', -3);
		g.AddEdge('z', 's', 2);
		g.AddEdge('z', 'x', 7);
		g.AddEdge('t', 'x', 5);
		g.AddEdge('t', 'y', 8);
		g.AddEdge('t', 'z', -4);
		g.AddEdge('x', 't', -2);

		vector<int> dist;
		vector<int> pPath;
		g.BellmanFord('x', dist, pPath);
		g.ShortestPath_Print('x', dist, pPath);
	}

	void TestGraph6() {
		vector<char> v{ '1','2','3','4','5' };
		Graph<char, int, INT_MAX, true> g(v);//����ͼ

		g.AddEdge('1', '2', 3);
		g.AddEdge('1', '3', 8);
		g.AddEdge('1', '5', -4);
		g.AddEdge('2', '4', 1);
		g.AddEdge('2', '5', 7);
		g.AddEdge('3', '2', 4);
		g.AddEdge('4', '1', 2);
		g.AddEdge('4', '3', -5);
		g.AddEdge('5', '4', 6);

		vector<vector<int>> vvDist;
		vector<vector<int>> vvpPath;
		g.FloydWarshall(vvDist, vvpPath);

		for (int i = 0; i < v.size(); i++) {
			g.ShortestPath_Print(v[i],vvDist[i], vvpPath[i]);
			cout << endl;
		}
	}


}



