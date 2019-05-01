#include<iostream>
#include"graph.h"
#include<stack>
#include<queue>

using namespace std;

template<class t>
class AdjGraph : public Graph<t> 
{
public:

	int **matrix;
	AdjGraph(int vertexesNum, int direct);
	~AdjGraph();
	Edge<t> FirstEdge(int oneVertex);
	Edge<t> NextEdge(Edge<t> oneEdge);
	void setEdge(int start, int end, t weight);
	void delEdge(int start, int end);
	void initiate();

	Edge<t> * Prim(int start);
};

template<class t>
AdjGraph<t>::AdjGraph(int vertexesNum, int direct):Graph<t>(vertexesNum,direct) {
	int i, j;
	this->vertexNum = vertexesNum;
	this->directional = direct;
	this->matrix = (int**) new int*[vertexesNum];
	for (i = 0; i < vertexesNum; i++)
		this->matrix[i] = new int[this->vertexNum];
	for (i = 0; i < this->vertexNum; i++)
		for (j = 0; j < this->vertexNum; j++)
			this->matrix[i][j] = 0;
	this->Mark = new int[this->vertexNum];
	for (int i = 0; i < vertexesNum; i++)
	{
		this->Mark[i] = UNVISITED;
	}
	this->directional = direct;
}
template<class t>
AdjGraph<t>::~AdjGraph() {
	for (int i = 0; i < this->vertexNum; i++)
		delete[] this->matrix[i];
	delete[] this->matrix;
}
template<class t>
Edge<t> AdjGraph<t>::FirstEdge(int oneVertex) {
	Edge<t> tmpEdge;
	tmpEdge.start = oneVertex;
	for (int i = 0; i < this->vertexNum; i++)
	{
		if(matrix[oneVertex][i] != 0)
		{
			tmpEdge.end = i;
			tmpEdge.weight = matrix[oneVertex][i];
			break;
		}
	}
	return tmpEdge;
}
template<class t>
Edge<t> AdjGraph<t>::NextEdge(Edge<t> oneEdge) {
	Edge<t> tmpEdge;
	tmpEdge.start = oneEdge.start;
	for (int i = oneEdge.end + 1; i < this->vertexNum; i++)
	{
		if (matrix[oneEdge.start][i] != 0)
		{
			tmpEdge.end = i;
			tmpEdge.weight = matrix[oneEdge.start][i];
			break;
		}
	}
	return tmpEdge;
}
template<class t>
void AdjGraph<t>::setEdge(int start, int end, t weight) {
	if (this->matrix[start][end] == 0)
	{
		this->edgeNum++;
	}
	this->matrix[start][end] = weight;
	return;
}
template<class t>
void AdjGraph<t>::delEdge(int start, int end) {
	if (this->matrix[start][end] != 0)
	{
		this->edgeNum--;
	}
	this->matrix[start][end] = 0;
}

template<class t>
void AdjGraph<t>::initiate() {
	for (int i = 0; i < this->vertexNum; i++)
		this->Mark[i] = UNVISITED;
}

template<class t>
Edge<t> * AdjGraph<t>::Prim(int start) {
	int i, j;
	Edge<t> *MST;
	t *nearest;
	int *neighbor;
	int node_sum = this->vertexNum;
	nearest = new int[node_sum];
	delete[] nearest;
	nearest = new int[node_sum];
	neighbor = new int[node_sum];
	MST = new Edge<t>[node_sum - 1];
	for (i = 0; i < node_sum; i++)
	{
		neighbor[i] = start;
		nearest[i] = 0x7FFFFFFF;
	}
	for (Edge<t>e = this->FirstEdge(start); this->isEdge(e); e = this->NextEdge(e))
	{
		i = e.end;
		nearest[i] = e.weight;
	}
	neighbor[start] = -1;
	for (i = 0; i < node_sum; i++)
	{
		t min = 0x7FFFFFFF;
		int v = -1;
		for (j = 0; j < node_sum; j++)
		{
			if (nearest[j]<min&&neighbor[j]>-1)
			{
				min = nearest[j];
				v = j;
			}
		}
		if (v >= 0)
		{
			Edge<t> tempEdge(neighbor[v], v, nearest[v]);
			neighbor[v] = -1;
			MST[i] = tempEdge;
			for (Edge<t> e = this->FirstEdge(v); this->isEdge(e); e = this->NextEdge(e))
			{
				int u = e.end;
				if (neighbor[u] != -1 && nearest[u] > e.weight)
				{
					neighbor[u] = v;
					nearest[u] = e.weight;
				}
			}//for(e)
		}//if
	}//for(i)
	delete [] neighbor;
	delete[] nearest;
	return MST;
}

#pragma once
