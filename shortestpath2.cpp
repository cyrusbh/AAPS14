/**
* Author:   Markus Niemelä
* Problem:  Single source shortest path, time table
* Started:  2014-02-25
*/

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

struct edge{
	int v, d, t0, P;
};

typedef pair<int, int> ii;
typedef vector<edge> ve;
#define INF 1000000000

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

int main(int argc, char* argv[]){
	int V, E, q, s, u, v, t0, P, d, a;
	vector<ve> AdjList;
	scanf("%d %d %d %d", &V, &E, &q, &s);
	while(V || E || q || s){
		AdjList.assign(V, ve());
		for(int i = 0; i < E; i++){
			scanf("%d %d %d %d %d", &u, &v, &t0, &P, &d);
			edge tmp = {v, d, t0, P};
			AdjList[u].push_back(tmp);
		}
		vector<ii> data = timetable(AdjList, s);
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