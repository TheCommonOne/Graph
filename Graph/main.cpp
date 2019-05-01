#include"AdjGraph.h"
#include"UFset.h"
#include"minHeap.h"

template<class t>
void Dijkstra(Graph<t>&G, int s, t D[], int Path[]);

template<class t>
Edge<t>* Kruskal(Graph<t>&G);

template<class t>
Edge< t>* Prim(Graph<t> &G, int start);

//v6 P
template<class t>
Edge<t>* Prim(Graph<t>&G, int start) {
	int node_sum = G.vertexNum;
	int c1, c2,edge_sum =0;
	int * neighbor = new int[node_sum];
	t * nearest = new t[node_sum];
	Edge<t> * MST = new Edge<t>[node_sum - 1];
	for (c1 = 0; c1 < node_sum; c1++)
	{
		nearest[c1] = 0x7fffffff;
		neighbor[c1] = start;
	}
	for (Edge<t> temp = G.FirstEdge(start); G.isEdge(temp); temp = G.NextEdge(temp))
	{
		if (temp.weight < nearest[temp.end])
		{
			nearest[temp.end] = temp.weight;
			neighbor[temp.end] = start;
		}
	}
	neighbor[start] = -1;

	for (c1 = 0; c1 < node_sum -1; c1++)
	{
		int min_weight = 0x7fffffff;
		int min_index = -1;
		for (c2 = 0; c2 < node_sum; c2++)
		{
			if (min_weight > nearest[c2] &&neighbor[c2] != -1)
			{
				min_weight = nearest[c2];
				min_index = c2;
			}
		}
		if (min_index > -1)
		{
			Edge<t> temp(neighbor[min_index], min_index, min_weight);
			neighbor[min_index] = -1;
			MST[edge_sum++] = temp;
			for (temp = G.FirstEdge(min_index); G.isEdge(temp); temp = G.NextEdge(temp))
			{
				if (nearest[temp.end] > temp.weight && neighbor[temp.end] >-1)
				{
					nearest[temp.end] = temp.weight;
					neighbor[temp.end] = min_index;
				}
			}
		}
	}
	return MST;
}

//v5 K
template<class t>
Edge<t> * Kruskal(Graph<t> &G) {
	int node_sum = G.vertexNum;
	int c1, c2, edge_sum = G.edgeNum;
	UFset set(node_sum);
	Edge<t> *MST = new Edge<t>[node_sum - 1];
	Edge<t> * all_edge = new Edge<t>[G.edgeNum];

	for (c1 = 0,c2 =0 ; c1 < node_sum; c1++)
	{
		for (Edge<t> temp = G.FirstEdge(c1); G.isEdge(temp); temp = G.NextEdge(temp))
		{
			if(temp.start<temp.end)
			all_edge[c2++] = temp;
		}
	}

	for (c1 = 0; c1 < edge_sum-1; c1++)
	{
		for (c2 =1; c2 < edge_sum-c1; c2++)
		{
			if (all_edge[c2 - 1] > all_edge[c2])
			{
				Edge<t> temp = all_edge[c2 - 1];
				all_edge[c2 - 1] = all_edge[c2];
				all_edge[c2] = temp;
			}
		}
	}

	for (c1 = 0,c2=0; c1 < edge_sum&&c2 < node_sum - 1;c1++)
	{
		if (set.Find(all_edge[c1].end) != set.Find(all_edge[c1].start))
		{
			set.Union(all_edge[c1].start, (all_edge[c1].end));
			MST[c2++] = all_edge[c1];
		}
	}
	delete[] all_edge;
	if (c2 == node_sum - 1)
		return MST;
	else
		return NULL;
}

//v6 D
template<class t>
void Dijkstra(Graph<t>&G, int s, t D[], int P[])
{
	int node_sum = G.vertexNum;
	int c1, c2;

	for (c1 = 0; c1 < node_sum; c1++)
	{
		G.Mark[c1] = UNVISITED;
		D[c1] = 0x7fffffff;
		P[c1] = -1;
	}
	for (Edge<t> temp = G.FirstEdge(s); G.isEdge(temp); temp = G.NextEdge(temp))
	{
		D[temp.end] = temp.weight;
		P[temp.end] = s;
	}

	D[s] = 0;
	P[s] = s;
	G.Mark[s] = VISITED;

	for (c1 = 0; c1 < node_sum; c1++)
	{
		int min_index = -1;
		t min_weight = 0x7fffffff;
		for (c2 = 0; c2 < node_sum; c2++)
		{
			if (min_weight > D[c2]&&G.Mark[c2] ==UNVISITED)
			{
				min_index = c2;
				min_weight = D[c2];
			}
		}
		if (min_index > -1)
		{
			G.Mark[min_index] = VISITED;
			P[min_index] = c1;
			for (Edge<t> temp = G.FirstEdge(min_index); G.isEdge(temp); temp = G.NextEdge(temp))
			{
				if (D[temp.end]> D[min_index]+ temp.weight && G.Mark[temp.end] == UNVISITED)
				{
					D[temp.end] = D[min_index] + temp.weight;
					P[temp.end] = min_index;
				}
			}
		}
	}
}

//v3 F
template<class t>
void Floyd(AdjGraph<t> &g, t **a, int**p) {
	int c1, c2, node_sum = g.vertexNum;
	Edge<t> temp;
	for (c1 = 0; c1 < node_sum; c1++)
		for (c2 = 0; c2 < node_sum; c2++)
		{
			if (g.matrix[c1][c2] >= 1)
			{
				a[c1][c2] = g.matrix[c1][c2];
				p[c1][c2] = c1;
			}
			else
			{
				a[c1][c2] = 0x7fffffff;
				p[c1][c2] = -1;
			}
			if (c1 == c2)
			{
				a[c1][c2] = 0;
				p[c1][c2] = c1;
			}
		}
	for (int adj_times = 0; adj_times < node_sum; adj_times++)
	{
		for (c1 = 0; c1 < node_sum; c1++)
			for (c2 = 0; c2 < node_sum; c2++)
			{
				if (c1!=c2&&a[c1][c2] > a[c1][adj_times] + a[adj_times][c2] && a[c1][adj_times] + a[adj_times][c2] > 0)
				{
					a[c1][c2] = a[c1][adj_times] + a[adj_times][c2];
					p[c1][c2] = adj_times;
				}
			}
	}
	
}

union test {
	int a;
	char c;
};
int main() {

	AdjGraph<int > graph(6,0);
	Edge<int> *MST;
	graph.setEdge(0, 1, 6);
	graph.setEdge(0, 2, 1);
	graph.setEdge(0, 3, 5);
	graph.setEdge(1, 0, 6);
	graph.setEdge(1, 2, 5);
	graph.setEdge(1, 4, 3);
	graph.setEdge(2, 0, 1);
	graph.setEdge(2, 1, 5);
	graph.setEdge(2, 3, 5);
	graph.setEdge(2, 4, 6);
	graph.setEdge(2, 5, 4);
	graph.setEdge(3, 0, 5);
	graph.setEdge(3, 2, 5);
	graph.setEdge(3, 5, 2);
	graph.setEdge(4, 1, 3);
	graph.setEdge(4, 2, 6);
	graph.setEdge(4, 5, 6);
	graph.setEdge(5, 2, 4);
	graph.setEdge(5, 3, 2);
	graph.setEdge(5, 4, 6);
	graph.DFSTraverse();
	graph.initiate();
	graph.BFSTraverse();
	cout << "Kruskal" << endl;
	MST = Kruskal(graph);
	for (int i = 0; i < 5; i++)
	{
		cout << MST[i];
	}
	delete[]MST;
	cout << "Prim" << endl;

	MST = Prim(graph,1);
	for (int i = 0; i < 5; i++)
	{
		cout << MST[i];
	}
	cout << "Dijkstra" << endl;

	int *D = new int[6];
	int *P = new int[6];
	Dijkstra(graph, 0, D, P);
	for (int i = 0; i < 6; i++)
	{
		cout << D[i]<<" ";
		cout << P[i];
		cout << endl;
	}

	//Delete
	delete [] D;
	delete [] P;

	/*cout << "Floyd" << endl;
	AdjGraph<int> gf(3, 1);
	int n = gf.vertexNum;
	gf.setEdge(0,1 , 10);
	gf.setEdge(1,0 , 9);
	gf.setEdge(1,2 , 6);
	gf.setEdge(2,1 , 13);
	gf.setEdge(0,2 , 5);
	gf.setEdge(2,0 , 2);

	int **Adj = new int *[n], **Path = new int *[n];
	for (int counter1 = 0; counter1 < n; counter1++)
	{
		Adj[counter1] = new int[n];
		Path[counter1] = new int[n];
	}

	Floyd(gf, (int**)Adj, (int**)Path);

	cout << "Adj" << endl;
	for (int counter1 = 0; counter1 <n; counter1++)
	{
		for (int counter2 = 0; counter2 < n; counter2++)
		{
			cout << Adj[counter1][counter2]<< " ";
		}
		cout << "\n";
	}

	cout << "Path" << endl;
	for (int counter1 = 0; counter1 < n; counter1++)
	{
		for (int counter2 = 0; counter2 < n; counter2++)
		{
			cout << Path[counter1][counter2] +1<< " ";
		}
		cout << "\n";
	}

	//Delete
	for (int counter1 = 0; counter1 < n; counter1++)
	{
		delete [] Adj[counter1];
		delete []Path[counter1];
	}
	delete[] Adj;
	delete[] Path;*/
	system("pause");
	return 0;
}

