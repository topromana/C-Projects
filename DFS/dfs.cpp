#include "pch.h"
#include<iostream> 
#include<list> 
#include <list> 
#include <stack> 
#define NIL -1 
#include "Profiler.h"
using namespace std;
Profiler profiler("DFS");
int nrOp;
class graph
{
	int V,E;   
	list<int> *adjacency;
	void DFSAux(int v, bool visited[]);
	void DFSAuxDemo(int v, bool visited[]);
public:
	graph(int V,int E);    
	void DFS(int v);
	void DFSDemo(int v);
	void AuxFctTarjan(int u, int disc[], int low[],stack<int> *st, bool stackMember[]);
	void topologicalSortAux(int v, bool visited[], stack<int> &Stack);
	void addEdge(int v, int w);
	int found(int x, int y);
public:
	void Tarjan();
	void topologicalSort();
};

void graph::topologicalSortAux(int v, bool visited[], stack<int> &Stack)
{
	visited[v] = true;
	list<int>::iterator i;
	for (i = adjacency[v].begin(); i != adjacency[v].end(); ++i)
		if (!visited[*i])
			nrOp++,topologicalSortAux(*i, visited, Stack);
	Stack.push(v);
	nrOp++;
}

void graph::topologicalSort()
{
	stack<int> Stack; 
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		nrOp++,visited[i] = false;
	for (int i = 0; i < V; i++)
		if (visited[i] == false)
			nrOp++,topologicalSortAux(i, visited, Stack);
	while (Stack.empty() == false)
	{
		cout << Stack.top() << " ";
		Stack.pop();
	}
}

graph::graph(int V,int E)
{
	this->V = V;
	this->E = E;
	nrOp+=2;
	adjacency = new list<int>[V];
}

void graph::addEdge(int v, int w)
{
	adjacency[v].push_back(w); 
	nrOp++;
}
int demo;

void graph::DFSAuxDemo(int v, bool visited[])
{
	visited[v] = true;
	cout << v << " ";
	list<int>::iterator i;
	for (i = adjacency[v].begin(); i != adjacency[v].end(); ++i)
		if (!visited[*i])
			DFSAuxDemo(*i, visited);
}
void graph::DFSAux(int v, bool visited[])
{
	visited[v] = true;
	nrOp++;
	list<int>::iterator i;
	for (i = adjacency[v].begin(); i != adjacency[v].end(); ++i)
		if (!visited[*i])
			nrOp++,DFSAux(*i, visited);
}

int minOfTwo(int a, int b)
{
	nrOp++;
	if (a < b)
		return a;
	return b;
}
void graph::DFS(int v)
{
	
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;
	DFSAux(v, visited);
}
void graph::DFSDemo(int v)
{

	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;
	DFSAuxDemo(v, visited);
}
void graph::AuxFctTarjan(int u, int disc[], int low[], stack<int> *st,bool stackMember[])
{
	static int time = 0; 
	disc[u] = low[u] = ++time;
	st->push(u);
	stackMember[u] = true;
	list<int>::iterator i;
	for (i = adjacency[u].begin(); i != adjacency[u].end(); ++i)
	{
		int v = *i;  
		if (disc[v] == -1)
		{
			nrOp++;
			AuxFctTarjan(v, disc, low, st, stackMember);
			low[u] = minOfTwo(low[u], low[v]);
			nrOp++;
		} 
		else if (stackMember[v] == true)
			low[u] = minOfTwo(low[u], disc[v]);
	} 
	int w = 0;
	if (low[u] == disc[u])
	{
		nrOp++;
		while (st->top() != u)
		{
			w = (int)st->top();
			cout << w << " ";
			stackMember[w] = false;
			st->pop();
		}
		w = (int)st->top();
		cout << w << endl;
		stackMember[w] = false;
		st->pop();
	}
}

void graph::Tarjan()
{
	int *disc = new int[V];
	int *low = new int[V];
	bool *stackMember = new bool[V];
	stack<int> *st = new stack<int>();
	for (int i = 0; i < V; i++)
	{
		disc[i] = NIL;
		low[i] = NIL;
		stackMember[i] = false;
	}
	for (int i = 0; i < V; i++)
		if (disc[i] == NIL)
			nrOp++,AuxFctTarjan(i, disc, low, st, stackMember);
}
void demoDFS() {
	
	graph g(5,6);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(3, 4);

	cout <<"DFS"<<endl;
	g.DFSDemo(2);
	cout << endl<<"Tarjan"<<endl;
	g.Tarjan();
	cout << endl << "topological" << endl;
	g.topologicalSort();
	cout << endl << endl;
	//cout << endl << g.E;

}

int graph::found(int x, int y)
{
	list<int>::iterator i;
	for (i = adjacency[x].begin(); i != adjacency[x].end(); ++i)
		if (*i == y) return 1;
	return 0;

		
}
void graphs()
{
	int x, y;
	
	for (int E = 1000; E <= 4900; E += 100)
	{
		nrOp = 0;
		int V = 100;
		graph g(V, E);
		for (int i = 0; i < E; i++)
		{

			x = rand() % V;
			y = rand() % V;
			while (g.found(x, y)) {
				x = rand() % V;
				y = rand() % V;
			}
			g.addEdge(x, y);
		}
		g.DFS(2);
		
		profiler.countOperation("e varies", E, nrOp);
	}

	// v varies

	for (int V = 100; V <= 200; V += 10)
	{
		nrOp = 0;
		int E = 9000;
		graph g(V, E);
		for (int i = 0; i < E; i++)
		{

			x = rand() % V;
			y = rand() % V;
			while (g.found(x, y)) {
				x = rand() % V;
				y = rand() % V;
			}
			g.addEdge(x, y);
		}
		g.DFS(3);
		profiler.countOperation("v varies", V, nrOp);
	}
}

int main()
{
	cout << endl << "want demo?" << endl;
	cin >> demo;
	
	if(demo ==1)
	demoDFS();
	
	graphs();
	profiler.showReport();
	return 0;
}