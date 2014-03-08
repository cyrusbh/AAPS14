/**
* Filename: graph.cpp
* Author:   Markus Niemelä
*/

#include "graph.h"

using namespace std;


/*
Function:		floyd_warshall(const vector< vector<int> >)

Description:	Given an adjacency matrix representing a graph, calculates the shortest path
				between all nodes in the graph. If there is none, the length is set to INF.
				If there is an arbitrarily short path, the length is set to -INF.
				Returns a matrix with the distance between node i and j at position (i,j).
*/
vector<vi> floyd_warshall(const vector<vi> AdjMatrix){
	vector<vi> AdjM(AdjMatrix);
	int V = (int)AdjM.size();
	for(int k = 0; k < V; k++)
		for(int i = 0; i < V; i++)
			for(int j = 0; j < V; j++)
				if(AdjM[i][j] > AdjM[i][k] + AdjM[k][j] && AdjM[i][k] != INF && AdjM[k][j] != INF){
					AdjM[i][j] = AdjM[i][k] + AdjM[k][j];
				}
	for(int i = 0; i < V; i++)
		for(int j = 0; j < V; j++)
			for(int k = 0; k < V; k++)
				if(AdjM[i][k] != INF && AdjM[k][j] != INF && AdjM[k][k] < 0)
					AdjM[i][j] = -INF;
	return AdjM;
}

/*
Function:		dijkstra(vector< vector< pair<int, int> > >, int)

Description:	Given an adjacency list representing a graph with non-negative weighted edges, 
				and a starting node, calculates the shortest path to all nodes in the graph from 
				the starting node. If there is none, the length is set to INF and the parent to -1.
				Returns a vector of pairs of integers, where the pair at position i denotes (dist, parent)
				for node i in the shortest path from the starting node.
*/
vector<ii> dijkstra(vector<vii> AdjList, int start){
	vector<ii> data((int)AdjList.size(), ii(INF, -1)); //dist, parent
	data[start].first = 0;
	priority_queue <ii, vector<ii>, greater<ii> > pq;
	pq.push(ii(0, start));

	while(!pq.empty()){
		ii front = pq.top();
		pq.pop();
		int d = front.first, u = front.second;
		if(d > data[u].first)
			continue;
		for(int i = 0; i < (int)AdjList[u].size(); i++){
			ii v = AdjList[u][i];
			if(data[v.first].first > data[u].first + v.second){
				data[v.first].first = data[u].first + v.second;
				data[v.first].second = u;
				pq.push(ii(data[v.first].first, v.first));
			}
		}
	}
	return data;
}

/*
Function:		timetable(vector< vector< pair<int, int> > >, int)

Description:	Modified version of dijkstra's algorithm in which the graph edges can be traversed only
				at set points in time, t0 + i*P for all non-negative integers i.
				Given an adjacency list representing a graph with non-negative weighted edges, 
				and a starting node, calculates the shortest path to all nodes in the graph from 
				the starting node. If there is none, the length is set to INF and the parent to -1.
				Returns a vector of pairs of integers, where the pair at position i denotes (dist, parent)
				for node i in the shortest path from the starting node.
*/
vector<ii> timetable(vector<ve> AdjList, int start){
	vector<ii> data((int)AdjList.size(), ii(INF, -1)); //dist, parent
	data[start].first = 0;
	priority_queue <ii, vector<ii>, greater<ii> > pq;
	pq.push(ii(0, start));

	while(!pq.empty()){
		ii front = pq.top();
		pq.pop();
		int d = front.first, u = front.second;
		if(d > data[u].first)
			continue;
		for(int i = 0; i < (int)AdjList[u].size(); i++){
			edge e = AdjList[u][i];
			if(e.P == 0 && d > e.t0)
				continue;
			int dist = d;
			if(dist <= e.t0)
				dist = e.t0;
			else
				dist += (e.P - (dist - e.t0) % e.P) % e.P;
			if(data[e.v].first > dist + e.d){
				data[e.v].first = dist + e.d;
				data[e.v].second = u;
				pq.push(ii(data[e.v].first, e.v));
			}
		}
	}
	return data;
}

/*
Function:		bellman_ford(vector< vector< pair<int, int> > >, int)

Description:	Given an adjacency list representing a graph with negative weighted edges, 
				and a starting node, calculates the shortest path to all nodes in the graph from 
				the starting node. If there is none, the length is set to INF and the parent to -1.
				If there is an arbitrarily short path, the length is set to -INF.
				Returns a vector of pairs of integers, where the pair at position i denotes (dist, parent)
				for node i in the shortest path from the starting node.
*/
vector<ii> bellman_ford(vector<vii> AdjList, int start){
	int V = (int)AdjList.size();
	vector<ii> data(V, ii(INF, -1)); //dist, parent
	data[start].first = 0;
	for(int i = 0; i < V-1; i++){
		for(int u = 0; u < V; u++){
			for(int j = 0; j < (int)AdjList[u].size(); j++){
				ii v = AdjList[u][j];
				if(data[v.first].first > data[u].first + v.second && data[u].first != INF){
					data[v.first].first = data[u].first + v.second;
					data[v.first].second = u;
				}
			}
		}
	}
	for(int u = 0; u < V; u++){
		for(int j = 0; j < (int)AdjList[u].size(); j++){
			ii v = AdjList[u][j];
			if(data[v.first].first > data[u].first + v.second && data[u].first != INF){
				data[v.first].first = -INF;
				data[v.first].second = u;
			}
		}
	}
	return data;
}

/*
Function:		prim(vector< vector< pair<int, int> > >, int)

Description:	Given an adjacency list representing a graph, calculates a minimum spanning tree
				in the graph using Prim's algorithm. 
				Returns an adjacency list with the minimum spanning tree. If no such tree exists,
				returns an empty adjacency list.
*/
vector<vii> prim(vector<vii> AdjList, int &cost){
	int V = (int)AdjList.size();
	vector<vii> mst(V, vii());
	priority_queue<iii, vector<iii>, greater<iii> > pq;
	vector<bool> taken(V, false);
	cost = 0;
	taken[0] = true;
	int v_taken = 1;
	
	for(int i = 0; i < (int)AdjList[0].size(); i++){
		ii e = AdjList[0][i];
		if(!taken[e.first])
			pq.push(iii(e.second, ii(0, e.first)));
	}
	while(!pq.empty() && v_taken < V){
		iii front = pq.top();
		pq.pop();
		int u = front.second.first;
		int v = front.second.second;
		int w = front.first;
		if(!taken[v]){
			cost += w;
			v_taken++;
			taken[v] = true;
			if(u < v)
				mst[u].push_back(ii(v,w));
			else
				mst[v].push_back(ii(u,w));
			for(int i = 0; i < (int)AdjList[v].size(); i++){
				ii e = AdjList[v][i];
				if(!taken[e.first])
					pq.push(iii(e.second, ii(v, e.first)));
			}
		}
	}
	if(v_taken < V)
		mst.clear();
	return mst;
}