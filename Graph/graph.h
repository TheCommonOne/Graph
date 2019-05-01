#include<iostream>
#include<stack>
#include<queue>
#include"edge.h"
#define UNVISITED 0
#define VISITED 1

using namespace std;

template<class t>
class Graph {
public:
	int vertexNum;
	int edgeNum;
	int *Mark;
	bool directional;
	Graph(int vertexesNum, int direct){
		vertexNum = vertexesNum;
		edgeNum = 0;
		Mark = new int[vertexNum];
		for (int i = 0; i < vertexesNum; i++)
		{
			Mark[i] = UNVISITED;
		}
		directional = direct;
	}
	~Graph(){
		delete [] Mark;
	}
	virtual Edge<t> FirstEdge(int oneVertex) = 0;
	virtual Edge<t> NextEdge(Edge<t> oneEdge) = 0;
	int VerticesNum() {
		return vertexNum;
	}
	int EdgesNum() {
		return edgeNum;
	}
	bool isEdge(Edge<t> oneEdge) {
		if (oneEdge.weight > 0 && oneEdge.weight<INFINITY && oneEdge.end >= 0)
			return true;
		else
			return false;
	}
	int StartVertex(Edge<t> oneEdge) {
		return oneEdge.start;
	}
	int EndVertex(Edge<t> oneEdge) {
		return oneEdge.end;
	}
	t Weight(Edge<t> oneEdge) {
		return oneEdge.weight;
	}
	virtual void setEdge(int start, int end, int weight) = 0;
	virtual void delEdge(int start, int end) = 0;
	void DFS(int v);
	void DFSTraverse();
	void DFSnoRecurs();
	void BFS(int v);
	void BFSTraverse();
};
template<class t>
void Graph<t>::DFS(int v) {
	this->Mark[v] = VISITED;
	cout << v;
	for (Edge<t> e = FirstEdge(v); this->isEdge(e); e = NextEdge(e))
	{
		if (Mark[this->EndVertex(e)] == UNVISITED)
			DFS(this->EndVertex(e));
	}
}
template<class t>
void Graph<t>::DFSTraverse() {
	for (int i = 0; i < vertexNum; i++)
	{
		if (Mark[i] == UNVISITED)
			DFS(i);
	}
	cout << endl;
}
template<class t>
void Graph<t>::DFSnoRecurs() {
	int i, v, u;
	stack<t> stk;
	for (int i = 0; i < vertexNum; i++)
	{
		if (Mark[i] == UNVISITED)
		{
			stk.push(i);
			cout << i;
			Mark[i] = VISITED;
			while (!stk.empty())
			{
				v = stk.pop();
				for (Edge<t> e = FirstEdge(v); isEdge(e); e = NextEdge(e))
				{
					u = EndVertex(e);
					if (Mark[u] == UNVISITED)
					{
						stk.push(u);
						cout << u;
						Mark[u] = VISITED;
					}
				}
			}
		}
	}
	cout << endl;
}
template<class t>
void Graph<t>::BFS(int v) {
	queue<t> que;
	Mark[v] = VISITED;
	cout << v;
	que.push(v);
	while (!que.empty())
	{
		v = que.front();
		que.pop();
		for (Edge<t> e = FirstEdge(v); this->isEdge(e); e = NextEdge(e))
		{
			int u = this->EndVertex(e);
			if (Mark[u] == UNVISITED)
			{
				Mark[u] = VISITED;
				cout << u;
				que.push(u);
			}
		}
	}
}
template<class t>
void Graph<t>::BFSTraverse() {
	int v;
	for (v = 0; v < vertexNum; v++)
	{
		if (Mark[v] == UNVISITED)
		{
			BFS(v);
		}
	}
	cout << endl;
}

#pragma once
