/**
* Author:   Markus Niemelä
* Problem:  All Pairs Shortest Path
* Started:  2014-02-26
*/

#include <cstdio>
#include <vector>

using namespace std;

typedef vector<int> vi;
#define INF 1000000000

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


int main(int argc, char* argv[]){
	int V, E, q, u, v, w, a, b;
	vector<vi> AdjMatrix;
	scanf("%d %d %d", &V, &E, &q);
	while(V || E || q){
		AdjMatrix.assign(V, vector<int>(V,INF));
		for(int i = 0; i < E; i++){
			scanf("%d %d %d", &u, &v, &w);
			if(AdjMatrix[u][v] > w)
				AdjMatrix[u][v] = w;
		}
		for(int i = 0; i < V; i++)
			AdjMatrix[i][i] = 0;
		AdjMatrix = floyd_warshall(AdjMatrix);
		for(int i = 0; i < q; i++){
			scanf("%d %d", &a, &b);
			if(AdjMatrix[a][b] == INF)
				printf("Impossible\n");
			else if(AdjMatrix[a][b] == -INF)
				printf("-Infinity\n");
			else
				printf("%d\n", AdjMatrix[a][b]);
		}
		printf("\n");
		scanf("%d %d %d", &V, &E, &q);
	}
	return 0;
}