#include<iostream>
#include"graph.h"
#include"edgeList.h"
using namespace std;

template<class t>
class ListGraph :public Graph<t> {
public:
	EdgeList<listData<t>> *graList;
	ListGraph(int vertexesNum) :Graph(verticesNum) {
		graList = new EdgeList<listData<t>>[vertexNum];
	}
	~ListGraph() {
		delete[] graList;
	}
	Edge FirstEdge(int oneVertex)
	{
		Edge<t> tmpEdge;
		tmpEdge.start = oneVertex;
		ListNode<listData<t>> *temp = graList[oneVertex].head;
	}
};

#pragma once
