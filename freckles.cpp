/**
* Author:   Markus Niemelä
* Problem:  Freckles
* Started:  2014-03-03
*
* Replaced iii with dii for the pq push. Thanks Obama.
*/

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, double> id;
typedef pair<double, double> dd;
typedef pair<double, ii> dii;
typedef pair<int, ii> iii;
typedef vector<ii> vii;
typedef vector<id> vid;

vector<vid> prim(vector<vid> AdjList, double &cost){
	int V = (int)AdjList.size();
	vector<vid> mst(V, vid());
	priority_queue<dii, vector<dii>, greater<dii> > pq;
	vector<bool> taken(V, false);
	cost = 0;
	taken[0] = true;
	int v_taken = 1;
	
	for(int i = 0; i < (int)AdjList[0].size(); i++){
		id e = AdjList[0][i];
		if(!taken[e.first])
			pq.push(dii(e.second, ii(0, e.first)));
	}
	while(!pq.empty() && v_taken < V){
		dii front = pq.top();
		pq.pop();
		int u = front.second.first;
		int v = front.second.second;
		double w = front.first;
		if(!taken[v]){
			cost += w;
			v_taken++;
			taken[v] = true;
			if(u < v)
				mst[u].push_back(id(v,w));
			else
				mst[v].push_back(id(u,w));
			for(int i = 0; i < (int)AdjList[v].size(); i++){
				id e = AdjList[v][i];
				if(!taken[e.first])
					pq.push(dii(e.second, ii(v, e.first)));
			}
		}
	}
	if(v_taken < V)
		mst.clear();
	return mst;
}


int main(int argc, char* argv[]){
	int n, V; 
	double cost, a, b;
	vector<vid> AdjList;
	vector<dd> coords;
	scanf("%d", &n);
	while(n--){
		scanf("%d", &V);
		coords.clear();
		AdjList.assign(V, vid());
		for(int i = 0; i < V; i++){
			scanf("%lf %lf", &a, &b);
			coords.push_back(dd(a,b));
		}
		for(int i = 0; i < V; i++)
			for(int j = 0; j < V; j++)
				if(i != j){
					double dx = coords[i].first - coords[j].first;
					double dy = coords[i].second - coords[j].second;
					AdjList[i].push_back(id(j, sqrt(dx*dx + dy*dy)));
				}
		vector<vid> mst = prim(AdjList, cost);
		printf("%.2lf\n", cost);
	}
	return 0;
}