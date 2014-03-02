/**
* Author:   Markus Niemelä
* Problem:  Minimum spanning tree
* Started:  2014-03-02
*/

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;

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


int main(int argc, char* argv[]){
	int V, E, u, v, w, cost;
	vector<vii> AdjList;
	scanf("%d %d", &V, &E);
	while(V || E){
		AdjList.assign(V, vii());
		for(int i = 0; i < E; i++){
			scanf("%d %d %d", &u, &v, &w);
			AdjList[u].push_back(ii(v, w));
			AdjList[v].push_back(ii(u, w));
		}
		vector<vii> mst = prim(AdjList, cost);
		if(mst.empty())
			printf("Impossible\n");
		else{
			printf("%d\n", cost);
			for(int i = 0; i < V; i++)
				for(int j = 0; j < (int)mst[i].size(); j++){
					sort(mst[i].begin(), mst[i].end());
					printf("%d %d\n", i, mst[i][j].first);
				}
		}
		scanf("%d %d", &V, &E);
	}
	return 0;
}