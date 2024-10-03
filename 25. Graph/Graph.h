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

//邻接表
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

	//W权值类型
	template<class V, class W, bool Def = false>//默认无向图
	class Graph {
	private:
		vector<V> _vertex;//下标映射顶点
		map<V, size_t> _indexMap;//顶点映射下标
		vector<Edge<W>*> _link;//邻接表
	public:
		Graph() = default;

		//构造图的方法，可以是I/O，可以是读文件，这里为了方便测试
		//就直接利用顶点集进行构造，然后手动添加边
		Graph(const vector<V>& vertex) {//构造函数的一种，vector来进行构造
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
			//	return -1;//没有对应下标
			//}

			//return _indexMap[vertex];

			auto ret = _indexMap.find(vertex);
			if (ret != _indexMap.end())
				return ret->second;
			else {
				throw invalid_argument("不存在的顶点");
				return -1;
			}
		}

		//起点 终点 权值
		void AddEdge(const V& src, const V& dst, const W& w) {
			size_t srci = GetIndexofVertex(src);
			size_t dsti = GetIndexofVertex(dst);

			Edge<W>* newnode = new Edge<W>(srci, dsti, w);
			newnode->next = _link[srci];
			_link[srci] = newnode;

			//如果是无向图 对称地来
			if (Def == false) {
				Edge<W>* newnode = new Edge<W>(dsti, srci, w);
				newnode->next = _link[dsti];
				_link[dsti] = newnode;
			}
			//这个函数针对邻接表其实还有点问题，当我们加的边是已经有的边的话，我们应该不做处理
			//这里就不写了，因为后续都是用邻接矩阵来操作的
		}

		void Print() {//以邻接表的形式打印
			for (int i = 0; i < _vertex.size(); i++) {
				Edge<W>* cur = _link[i];
				cout << "[" << i << "->" << _vertex[i] << "]" << "——>";
				while (cur != nullptr) {
					cout << "[" << cur->_dsti << "->" << _vertex[cur->_dsti] << "]" << "——>";
					cur = cur->next;
				}
				cout << endl;
			}
		}

		//广度优先遍历
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
		vector<string> v{ "张三","李四","王五","赵六","刘七","徐八" };
		Graph<string, int> g(v);
		g.AddEdge("张三", "李四", 1);
		g.AddEdge("张三", "王五", 1);
		g.AddEdge("李四", "赵六", 1);
		g.AddEdge("王五", "刘七", 1);
		g.AddEdge("王五", "徐八", 1);
		g.AddEdge("徐八", "赵六", 1);
		g.AddEdge("刘七", "徐八", 1);

		//g.Print();
		//g.BFS("张三");
		g.DFS("张三");
	}
}

namespace Amatrix{
	//W权值类型
	template<class V, class W, W MAX_W = INT_MAX, bool Def = false>//默认无向图
	class Graph {
		typedef Graph<V, W, MAX_W, Def> self;
	private:
		vector<V> _vertex;//下标映射顶点
		map<V, size_t> _indexMap;//顶点映射下标
		vector<vector<W>> _matrix;//邻接矩阵
	public:
		Graph() = default;

		//构造图的方法，可以是I/O，可以是读文件，这里为了方便测试
		//就直接利用顶点集进行构造，然后手动添加边
		Graph(const vector<V>& vertex) {//构造函数的一种，vector来进行构造
			size_t n = vertex.size();
			_vertex.reserve(n);

			for (size_t i = 0; i < n; ++i) {
				_vertex.push_back(vertex[i]);
				//_indexMap.insert(make_pair(vertex[i], i));
				_indexMap[vertex[i]] = i;
			}

			_matrix.resize(n);
			for (size_t i = 0; i < n; ++i) {
				_matrix[i].resize(n, MAX_W);//邻接矩阵刚开始里面存的全是无穷大
				//我们让自成环的情况也搞成无穷大了 而非0
			}
		}

		Graph(const initializer_list<V>& vertex) {//构造函数的一种，初始化列表来进行构造
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
				_matrix[i].resize(n, MAX_W);//邻接矩阵刚开始里面存的全是无穷大
				//我们让自成环的情况也搞成无穷大了 而非0
			}
		}

		size_t GetIndexofVertex(const V& vertex) {
			//if (_indexMap.count(vertex) == 0) {
			//	return -1;//没有对应下标
			//}

			//return _indexMap[vertex];

			auto ret = _indexMap.find(vertex);
			if (ret != _indexMap.end())
				return ret->second;
			else {
				throw invalid_argument("不存在的顶点");
				return -1;
			}
		}

		void _AddEdge(size_t srci, size_t dsti, const W& w) {
			_matrix[srci][dsti] = w;

			//如果是无向图 对称地来
			if (Def == false) {
				_matrix[dsti][srci] = w;
			}
		}


		//起点 终点 权值
		void AddEdge(const V& src, const V& dst, const W& w) {
			size_t srci = GetIndexofVertex(src);
			size_t dsti = GetIndexofVertex(dst);

			_AddEdge(srci, dsti, w);
		}

		//拓扑排序 能判断图是否成环 其主要思想就是入度为0的结点优先打印 打印完后"删除包括对应出边"
		void Topsort() {//打印该图的拓扑排序
			vector<int> indegree(_vertex.size(), 0);//存储每个顶点的入度
			stack<size_t> st;//存储入度为0的顶点对应的下标

			size_t n = _vertex.size();
			//先统计每个顶点的入度（遍历邻接矩阵）
			for (size_t i = 0; i < n; ++i) {
				for (size_t j = 0; j < n; ++j) {
					if (_matrix[i][j] != MAX_W) {//有效邻接点
						indegree[j]++;
					}
				}
			}

			for (size_t i = 0; i < n; ++i) {
				if (indegree[i] == 0)
					st.push(i);//存储入度为0的顶点对应的下标
			}

			while (!st.empty()) {
				size_t index = st.top();
				st.pop();
				cout << _vertex[index] << " ";//取出删除并输出对应入度为0的顶点

				for (size_t i = 0; i < n; ++i) {//将跟这个入度为零的邻接的顶点对应入度-1
					if (_matrix[index][i] != MAX_W) {
						--indegree[i];
						if (indegree[i] == 0)
							st.push(i);
					}
				}
			}
		}

		void Print() {//以邻接矩阵的形式打印
			//先打印顶点与编号的对应关系
			size_t n = _vertex.size();
			for (int i = 0; i < n; i++) {
				cout << _vertex[i] << "——>" << "[" << i << "]" << endl;
			}

			//宽度目前设为7
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

		//广度优先遍历
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

		//BFS一层一层打印
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

			//搞个仿函数 让Edge能比较  
			//要用在库函数的函数对象作为成员函数时 要const啊
			bool operator>(const Edge& rhs) const{
				return _w > rhs._w;
			}
		};

	    W Kruskal(self& Mintree) {//这是个输出型参数
			size_t n = _vertex.size();
			W total_w = 0;
			Mintree._vertex = _vertex;
			Mintree._indexMap = _indexMap;
			Mintree._matrix.resize(n);
			for (int i = 0; i < n; i++) {
				Mintree._matrix[i].resize(n,MAX_W);
			}

			priority_queue<Edge,vector<Edge>,greater<Edge>> edges;
			vector<int> v(n);//顶点对应的编号集 为了给并查集构造(模板)
			for (int i = 0; i < n; i++) v[i] = i;
			UnionFindSet<int> ufs(v);

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (i < j && _matrix[i][j] != MAX_W) {//无向图，我们边只拿矩阵的上半就行
						edges.push(Edge(i, j, _matrix[i][j]));
					}
				}
			}
			//现在优先级队列里是原图的所有边集合

			while (!edges.empty()) {
				Edge ed = edges.top();
				edges.pop();
				if (!ufs.IsInSet(ed._srci, ed._dsti)) {//这俩不构成环
					Mintree._matrix[ed._srci][ed._dsti] = ed._w;
					total_w += ed._w;
					ufs.Union(ed._srci, ed._dsti);
					n--;
				}
			}

			if (n == 1) return total_w;
			else return -1;//n!=1 构造最小生成树失败
		}

		//这个要有一个起点
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

			size_t size = 0;//n-1个退
			while (!edges.empty()) {
				Edge min_ed = edges.top();
				edges.pop();

				//该最小边的这个顶点 应该是未选过的
				if (!minv[min_ed._dsti]) {
					minv[min_ed._dsti] = true;
					Mintree._AddEdge(min_ed._srci, min_ed._dsti, min_ed._w);
					size++;
					total_w += min_ed._w;

					//把这个新加进来的顶点的邻接边给搞进来(只加未选的)
					for (int i = 0; i < n; i++) {
						if (_matrix[min_ed._dsti][i] != MAX_W && minv[i] == false)
							edges.push(Edge(min_ed._dsti, i, _matrix[min_ed._dsti][i]));
					}
				}

				if (size == n - 1) break;
			}

			if (size == n - 1) return total_w;
			else  return -1;//n!=1 构造最小生成树失败
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

				cout << "最短路径：" << dist[i] << endl;
			}
		}
		

		//最短路径的Dijkstra算法  dist和pPath是输出型参数
		void Dijkstra(const V& v,vector<W>& dist,vector<int>& pPath) {
			size_t srci = GetIndexofVertex(v);
			size_t n = _vertex.size();
			vector<bool> SQ(n, false);//确定最短路径的集合 未确定的顶点集合
			dist.resize(n, MAX_W);
			pPath.resize(n, -1);
			dist[srci] = W();//自己到自己是0

			for (int k = 0; k < n; k++) {//每次循环都能确定一个顶点的最短路径
				int u = -1;//保存Q集合里的最短路径对应的顶点
				W min = MAX_W;

				//这个for循环是找 Q集合里面最短的路径(纯遍历)  一定找得到
				for (int i = 0; i < n; i++) {
					if (SQ[i] == false && dist[i] < min) {
						u = i;
						min = dist[i];
					}
				}

				SQ[u] = true;//选出确定最短路径的顶点

				//进行松弛
				for (int i = 0; i < n; i++) {
					//与我邻接，并且未确定最短路径 并且有更短的路径
					if (_matrix[u][i] != MAX_W && SQ[i] == false &&dist[u] + _matrix[u][i] < dist[i]) {
						dist[i] = dist[u] + _matrix[u][i];
						pPath[i] = u;//i顶点上一个顶点是u顶点
					}
				}
			}

		}

		void BellmanFord(const V& v, vector<W>& dist, vector<int>& pPath) {
			size_t srci = GetIndexofVertex(v);
			size_t n = _vertex.size();
			dist.resize(n, MAX_W);
			pPath.resize(n, -1);
			dist[srci] = W();//自己到自己是0

			for (int k = 0; k < n - 1; k++) {
				bool flag = false;

				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						//要邻接 且是有效顶点(该顶点的dist不应该是MAX_W要不然计算会越界) 并且有更短路径
						if (_matrix[i][j] != MAX_W && dist[i] != MAX_W
							&& dist[i] + _matrix[i][j] < dist[j]) {
							dist[j] = dist[i] + _matrix[i][j];
							pPath[j] = i;
							flag = true;
						}
					}
				}

				//没有更新
				if (flag == false) break;
			}

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (_matrix[i][j] != MAX_W && dist[i] != MAX_W
						&& dist[i] + _matrix[i][j] < dist[j]) {
						cout << "负权回路，不存在最短路径" << endl;
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

			//先把直连的顶点进行第一轮的初始化
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (_matrix[i][j] != MAX_W) {
						vvDist[i][j] = _matrix[i][j];
						vvpPath[i][j] = i;
					}

					if (i == j) vvDist[i][j] = 0;
				}
			}

			//对每个两两顶点都对是否经过所有顶点做一下检验
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
		vector<string> v{ "张三","李四","王五","赵六","刘七","徐八" };
		//Graph<string, int,INT_MAX,true> g(v);
		Graph<string, int> g(v);
		g.AddEdge("张三", "李四", 1);
		g.AddEdge("张三", "王五", 1);
		g.AddEdge("李四", "赵六", 1);
		g.AddEdge("王五", "刘七", 1);
		g.AddEdge("王五", "徐八", 1);
		g.AddEdge("徐八", "赵六", 1);
		g.AddEdge("刘七", "徐八", 1);

		g.Print();
	}

	void TestGraph2() {
		vector<string> v{ "张三","李四","王五","赵六","刘七","徐八" };

		Graph<string, int> g(v);
		g.AddEdge("张三", "李四", 1);
		g.AddEdge("张三", "王五", 1);
		g.AddEdge("李四", "赵六", 1);
		g.AddEdge("王五", "刘七", 1);
		g.AddEdge("王五", "徐八", 1);
		g.AddEdge("徐八", "赵六", 1);

		//g._BFS("张三");
		g.DFS("张三");
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
		Graph<char, int, INT_MAX, true> g(v);//有向图
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
		Graph<char, int, INT_MAX, true> g(v);//有向图

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
		Graph<char, int, INT_MAX, true> g(v);//有向图

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



