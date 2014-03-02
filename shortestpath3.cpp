/**
* Author:   Markus Niemelä
* Problem:  Single source shortest path, negative weights
* Started:  2014-02-26
*/

#include <cstdio>
#include <vector>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
#define INF 1000000000

vector<ii> bell_ford(vector<vii> AdjList, int start){
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


int main(int argc, char* argv[]){
	int V, E, q, s, u, v, w, a;
	vector<vii> AdjList;
	scanf("%d %d %d %d", &V, &E, &q, &s);
	while(V || E || q || s){
		AdjList.assign(V, vii());
		for(int i = 0; i < E; i++){
			scanf("%d %d %d", &u, &v, &w);
			AdjList[u].push_back(ii(v, w));
		}
		vector<ii> data = bell_ford(AdjList, s);
		for(int i = 0; i < q; i++){
			scanf("%d", &a);
			if(a != s && data[a].second == -1)
				printf("Impossible\n");
			else if(data[a].first == -INF)
				printf("-Infinity\n");
			else
				printf("%d\n", data[a].first);
		}
		printf("\n");
		scanf("%d %d %d %d", &V, &E, &q, &s);
	}
	return 0;
}