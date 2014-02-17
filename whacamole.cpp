/**
* Author:   Markus Niemelä
* Problem:  Whac-a-Mole
* Started:  2014-02-16
*
* Comments: Originally tried an implementation using GCD, but ran into problems troubleshooting when
*			it didn't look at the right positions. Decided to do it in an uglier, but more easily
*			understandable way instead.
*/

#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

int W[11][36][36], M[11][36][36];

int main(int argc, char* argv[]){
	int n, d, m;
	int x, y, t;
	scanf("%d %d %d", &n, &d, &m);
	while(n || d || m){
		memset(W, 0, sizeof(W));
		memset(M, 0, sizeof(M));
		for(int i = 0; i < m; i++){
			scanf("%d %d %d", &x, &y, &t);
			M[t][x+5][y+5] = 1;
		}
		for(t = 1; t <= 10; t++){
			for(x = 0; x <= n+10; x++){
				for(y = 0; y <= n+10; y++){
					for(int i = -d; i <= d; i++){
						for(int j = -d; j <= d; j++){
							int dx = 0, dy = 0, moles = 0;
							while(x+dx >= 0 && x+dx <= n+10 && y+dy >= 0 && y+dy <= n+10 && dx*dx + dy*dy <= d*d){
								moles += M[t][x+dx][y+dy];
								if(moles + W[t-1][x][y] > W[t][x+dx][y+dy])
									W[t][x+dx][y+dy] = moles + W[t-1][x][y];
								dx += i;
								dy += j;
								if(!(i||j))
									break;
							}
							
						}
					}
				}
			}
		}
		int best = 0;
		for(x = 0; x <= n+10; x++)
			for(y = 0; y <= n+10; y++)
				if(W[10][x][y] > best)
					best = W[10][x][y];
		printf("%d\n", best);
		scanf("%d %d %d", &n, &d, &m);
	}
	return 0;
}