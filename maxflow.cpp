/**
* Author:   Markus Niemelä
* Problem:  Maximum Flow
* Started:  2014-03-02
*/

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <bitset>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define INF 1000000000
#define MAX_V 500

vector<vi> ResMatrix;
vector<vi> AdjList;
vector<int> p;
int f, start;

void augment(int v, int minEdge){
	if(v == start){
		f = minEdge;
		return;
	}
	else if(p[v] != -1){
		augment(p[v], min(minEdge, ResMatrix[p[v]][v]));
		ResMatrix[p[v]][v] -= f;
		ResMatrix[v][p[v]] += f;
	}
}

vector<iii> edmond_karp(const vector<vi> AList, const vector<vi> AMatrix, int &maxflow, int s, int t){
	AdjList = vector<vi>(AList);
	ResMatrix = vector<vi>(AMatrix); //residual capacity
	maxflow = 0;
	int V = (int)AdjList.size();
	start = s;
	while(true){
		f = 0;
		bitset<MAX_V> vis;
		vis.set(s);
		queue<int> q;
		q.push(s);
		p.assign(V, -1);
		while(!q.empty()){
			int u = q.front();
			q.pop();
			if(u == t)
				break;
			for(int i = 0; i < (int)AdjList[u].size(); i++){
				int v = AdjList[u][i];
				if(ResMatrix[u][v] > 0 && !vis.test(v)){
					vis.set(v);
					p[v] = u;
					q.push(v);
				}
			}
		}
		augment(t, INF);
		if(f == 0)
			break;
		maxflow += f;
	}
	vector<iii> edges;
	for(int i = 0; i < V; i++)
		for(int j = 0; j < V; j++)
			if(AMatrix[i][j] > ResMatrix[i][j])
				edges.push_back(iii(AMatrix[i][j] - ResMatrix[i][j], ii(i,j)));
	return edges;
}

int main(int argc, char* argv[]){
	int V, E, s, t, u, v, c, maxflow;
	vector<vi> AdjList, AdjMatrix;
	while(scanf("%d %d %d %d", &V, &E, &s, &t) == 4){
		AdjList.assign(V, vi());
		AdjMatrix.assign(V, vi(V,0));
		for(int i = 0; i < E; i++){
			scanf("%d %d %d", &u, &v, &c);
			AdjMatrix[u][v] = c;
			AdjList[u].push_back(v);
			AdjList[v].push_back(u);
		}
		vector<iii> flow = edmond_karp(AdjList, AdjMatrix, maxflow, s, t);
		printf("%d %d %d\n", V, maxflow, (int)flow.size());
		for(int i = 0; i < (int)flow.size(); i++)
			printf("%d %d %d\n", flow[i].second.first, flow[i].second.second, flow[i].first);
	}
	return 0;
}

/*int main(int argc, char* argv[]){
	int V, E, s, t, u, v, c, maxflow;
	vector<vi> AdjList, AdjMatrix;
	int n = 1;
	while(scanf("%d %d %d %d", &V, &s, &t, &E) == 4){
		s--; t--;
		AdjList.assign(V, vi());
		AdjMatrix.assign(V, vi(V,0));
		for(int i = 0; i < E; i++){
			scanf("%d %d %d", &u, &v, &c);
			u--; v--;
			AdjMatrix[u][v] += c;
			AdjMatrix[v][u] += c;
			AdjList[u].push_back(v);
			AdjList[v].push_back(u);
		}
		vector<iii> flow = edmond_karp(AdjList, AdjMatrix, maxflow, s, t);
		printf("Network %d\nThe bandwidth is %d.\n\n", n, maxflow);
		n++;
	}
	return 0;
}*/