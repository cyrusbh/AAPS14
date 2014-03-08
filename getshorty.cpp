/**
* Author:   Markus Niemelä
* Problem:  Get Shorty
* Started:  2014-03-08
*/

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, double> id;
typedef pair<double, int> di;
typedef vector<id> vid;
#define INF 1000000000

double dijkstra(vector<vid> AdjList, int start){
	vector<di> data((int)AdjList.size(), di(-INF, -1)); //dist, parent
	data[start].first = 1;
	priority_queue <di> pq;
	pq.push(di(1, start));

	while(!pq.empty()){
		di front = pq.top();
		pq.pop();
		double d = front.first;
		int u = front.second;
		if(d < data[u].first)
			continue;
		for(int i = 0; i < (int)AdjList[u].size(); i++){
			id v = AdjList[u][i];
			if(data[v.first].first < data[u].first * v.second){
				data[v.first].first = data[u].first * v.second;
				data[v.first].second = u;
				pq.push(di(data[v.first].first, v.first));
			}
		}
	}
	return data[data.size()-1].first;
}

int main(int argc, char* argv[]){
	vector<vid> AdjList;
	int n, m, x, y;
	double f;
	scanf("%d %d", &n, &m);
	while(n || m){
		AdjList.assign(n, vid());
		for(int i = 0; i < m; i++){
			scanf("%d %d %lf", &x, &y, &f);
			AdjList[x].push_back(id(y, f));
			AdjList[y].push_back(id(x, f));
		}
		printf("%.4lf\n", dijkstra(AdjList, 0));
		scanf("%d %d", &n, &m);
	}
	return 0;
}