/**
* Author:   Markus Niemelä
* Problem:  Nikola
* Started:  2014-03-03
*
* Submission 2: Using the memo table helps.
*/

#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

#define INF 1000000000

using namespace std;

int N;
int cost[1010];
int memo[1010][1010]; //pos, jump

//best cost to N, given that you arrived in pos with a length of jump.
int solve(int pos, int jump){
	if(pos == N)
		return cost[N];
	if(pos > N || pos <= 0)
		return INF;
	if(memo[pos][jump] != -1)
		return memo[pos][jump];
	memo[pos][jump] = min(solve(pos+jump+1, jump+1), solve(pos-jump, jump)) + cost[pos];
	return memo[pos][jump];
}

int main(int argc, char* argv[]){
	memset(memo, -1, sizeof(memo));
	scanf("%d", &N);
	for(int i = 1; i <= N; i++)
		scanf("%d", &cost[i]);
	printf("%d\n", solve(2, 1)); //must jump to 2 initially
}