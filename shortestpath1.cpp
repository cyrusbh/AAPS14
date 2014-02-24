/**
* Author:   Markus Niemelä
* Problem:  Single source shortest path, non-negative weights
* Started:  2014-02-24
*/

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define INF 1000000000

vector<ii> dijk_sssp(vector<vii> AdjList, int start){
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
		vector<ii> data = dijk_sssp(AdjList, s);
		for(int i = 0; i < q; i++){
			scanf("%d", &a);
			if(a != s && data[a].second == -1)
				printf("Impossible\n");
			else
				printf("%d\n", data[a].first);
		}
		printf("\n");
		scanf("%d %d %d %d", &V, &E, &q, &s);
	}
	return 0;
}