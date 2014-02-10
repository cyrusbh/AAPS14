/**
* Author:   Markus Niemelä
* Problem:  Spiderman's workout
* Started:  2014-02-10
* 
* Submission 2: Tracking max height instead of height of previous location.
*/

#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <climits>

using namespace std;

int dist[45];
int height[45][1010];
char route[45][1010];
char ans[45];
int M;

int main(int argc, char* argv[]){
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < 45; j++)
			for(int k = 0; k < 1010; k++)
				height[j][k] = INT_MAX;
		height[0][0] = 0;
		scanf("%d", &M);
		for(int j = 0; j < M; j++)
			scanf("%d", &dist[j]);
		for(int j = 0; j < M; j++){
			for(int pos = 0; pos < 505; pos++){
				if(height[j][pos] == INT_MAX)
					continue;
				int up = pos + dist[j], down = pos - dist[j];
				if(height[j+1][up] > max(height[j][pos], up)){
					height[j+1][up] = max(height[j][pos], up);
					route[j+1][up] = 'U';
				}
				if(down >= 0 && (height[j+1][down] > height[j][pos])){
					height[j+1][down] = height[j][pos];
					route[j+1][down] = 'D';
				}
			}
		}
		if(height[M][0] == INT_MAX)
			printf("IMPOSSIBLE\n");
		else{
			ans[M] = '\0';
			for(int j = M, pos = 0; j > 0; j--){
				ans[j-1] = route[j][pos];
				if(ans[j-1] == 'D')
					pos += dist[j-1];
				else
					pos -= dist[j-1];
			}
			printf("%s\n", ans);
		}
	}
	return 0;
}