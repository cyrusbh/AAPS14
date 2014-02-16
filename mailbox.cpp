/**
* Author:   Markus Niemelä
* Problem:  The Mailbox Manufacturers Problem
* Started:  2014-02-15
*/

#include <cstdio>
#include <climits>
#include <algorithm>
#include <cstring>

using namespace std;

int memo[101][101][11];

int tries(int lo, int hi, int boxes){
	if(lo == hi)
		return 0;
	if(memo[lo][hi][boxes] == -1){
		int temp = INT_MAX;
		if(boxes == 1)
			memo[lo][hi][boxes] = (hi * (hi + 1)) / 2 - (lo * (lo + 1)) / 2;
		else{
			for(int i = lo+1; i <= hi; i++)
				temp = min(temp, i + max(tries(lo, i-1, boxes-1), tries(i, hi, boxes)));
			memo[lo][hi][boxes] = temp;
		}
	}
	return memo[lo][hi][boxes];
}

int main(int argc, char* argv[]){
	memset(memo, -1, sizeof(memo));
	int n, k, m;
	scanf("%d", &n);
	while(n--){
		scanf("%d %d", &k, &m);
		printf("%d\n", tries(0, m, k));
	}
	return 0;
}