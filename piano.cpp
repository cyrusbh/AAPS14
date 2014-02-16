/**
* Author:   Markus Niemelä
* Problem:  Moving Pianos
* Started:  2014-02-16
*/

#include <cstdio>
#include <algorithm>

using namespace std;

int B[1001], E[1001], ind[1001];

bool cmp(int a, int b){
	return E[a] == E[b] ? B[a] < B[b] : E[a] < E[b];
}

int weekends(int m, int p){
	for(int i = 0, j = 1; j <= 100; j++){
		for(int k = p; k > 0 && i < m; k--, i++){
			if(E[ind[i]] < j)
				return 2;
			else if(B[ind[i]] > j)
				break;
		}
	}
	return 1;
}

int solve(){
	int m, p;
	scanf("%d %d", &m, &p);
	p = p/2;
	for(int i = 0; i < m; i++){
		scanf("%d %d", &B[i], &E[i]);
		ind[i] = i;
	}
	if(p < 1)
		return 2;
	
	sort(ind, ind + m, cmp);
	for(int i = 0, j = 1; j <= 100; j++){
		if((j-1)%7 > 4)
			continue;
		for(int k = p; k > 0 && i < m; k--, i++){
			if(E[ind[i]] < j)
				return weekends(m, p);
			else if(B[ind[i]] > j)
				break;
		}
	}
	return 0;
}

int main(int argc, char* argv[]){
	int n;
	scanf("%d", &n);
	while(n--){
		switch(solve()){
			case 0:
				printf("fine\n");
				break;
			case 1:
				printf("weekend work\n");
				break;
			case 2:
				printf("serious trouble\n");
				break;
		}
	}
	return 0;
}