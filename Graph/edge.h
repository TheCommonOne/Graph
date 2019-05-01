#include<iostream>

using namespace std;

template<class t>
class Edge {
public:
	int start, end;
	t weight;
	Edge(int st = INFINITY, int en = INFINITY, int w= INFINITY) {
		start = st;
		end = en;
		weight = w;
	}
	~Edge() {

	}
	bool operator > (Edge<t> oneEdge) {
		if (this->weight > oneEdge.weight)
			return true;
		return false;
	}
	bool operator <(Edge<t> oneEdge) {
		if (this->weight < oneEdge.weight)
			return true;
		return false;
	}
	template<class t>
	friend ostream& operator <<(ostream& out, Edge<t> e);
};

template<class t>
ostream& operator <<(ostream& out, Edge<t> e) {
	cout << "Start: " << e.start << " End: " << e.end <<" Weight: "<< e.weight<<endl;
	return out;
}

#pragma once
