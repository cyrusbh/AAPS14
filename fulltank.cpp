/**
* Author:   Markus Niemelä
* Problem:  Full Tank?
* Started:  2014-03-08
*/

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
#define INF 1000000000

vector<vii> AdjList;
vector<int> price;

int dijkstra(int C, int s, int e){
	vector<vi> cost((int)AdjList.size(), vi(C+1, INF));
	cost[s][0] = 0;
	priority_queue <iii, vector<iii>, greater<iii> > pq; //cost, city, fuel
	pq.push(iii(cost[s][0], ii(s, 0)));

	while(!pq.empty()){
		iii front = pq.top();
		pq.pop();
		int c = front.first, u = front.second.first, f = front.second.second;
		if(c > cost[u][f])
			continue;
		if(u == e)
			break;
		for(int i = 0; i < (int)AdjList[u].size(); i++){
			int v = AdjList[u][i].first, d = AdjList[u][i].second;
			if(f >= d && cost[v][f-d] > cost[u][f]){
				cost[v][f-d] = cost[u][f];
				pq.push(iii(cost[v][f-d], ii(v, f-d)));
			}
			if(f < C && cost[u][f+1] > cost[u][f] + price[u]){
				cost[u][f+1] = cost[u][f] + price[u];
				pq.push(iii(cost[u][f+1], ii(u, f+1)));
			}
		}
	}
	return cost[e][0];
}

int main(int argc, char* argv[]){
	int n, m, p, u, v, d, q, c, s, e;
	scanf("%d %d", &n, &m);
	AdjList.assign(n, vii());
	price.assign(n, INF);
	for(int i = 0; i < n; i++)
		scanf("%d", &price[i]);
	for(int i = 0; i < m; i++){
		scanf("%d %d %d", &u, &v, &d);
		AdjList[u].push_back(ii(v, d));
		AdjList[v].push_back(ii(u, d));
	}
	scanf("%d", &q);
	for(int i = 0; i < q; i++){
		scanf("%d %d %d", &c, &s, &e);
		int res = dijkstra(c, s, e);
		if(res == INF)
			printf("impossible\n");
		else
			printf("%d\n", res);
	}
	return 0;
}