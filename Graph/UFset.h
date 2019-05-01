#include<iostream>

using namespace std;

class UFset {
private:
	int element_sum;
	int*root;
	int*next;
	int*length;
public:
	UFset(int size) {
		element_sum = size;
		root = new int[size];
		next = new int[size];
		length = new int[size];
		for (int i = 0; i < size; i++)
		{
			root[i] = next[i] = i;
			length[i] = 1;
		}
	}
	~UFset() {
		delete root;
		delete next;
		delete length;
	}
	int Find(int v);
	void Union(int v, int u);
};

void UFset::Union(int v,int u) {
	if (root[v] == root[u])
		return;
	else if (length[root[v]] > length[root[u]])
	{
		int rt = root[u];
		length[root[v]] += length[root[u]];
		root[root[u]] = root[v];
		for (int j = next[rt]; j != rt; j = next[j])
		{
			root[j] = root[v];
		}
		swap(next[root[v]], next[rt]);
	}
	else
	{
		int rt = root[v];
		length[root[u]] += length[rt];
		root[root[v]] = root[u];
		for (int j = next[rt]; j != rt; j = next[j])
		{
			root[j] = root[u];
		}
		swap(next[rt], next[root[u]]);
	}
}

int UFset::Find(int v) {
	return root[v];
}

#pragma once
