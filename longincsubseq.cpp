/**
* Author:   Markus Niemel�
* Problem:  Longest Increasing Subsequence
* Started:  2014-02-23
*/

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> M, P, X;
int L;

int bsearch(int idx, int lo, int hi){
	if(lo >= hi)
		return X[M[lo]] < X[idx] ? lo : lo-1;
	return X[M[(lo+hi)/2]] < X[idx] ? bsearch(idx, (lo+hi)/2+1, hi) : bsearch(idx, lo, (lo+hi)/2-1);
}

vector<int> lis(vector<int> seq){
	vector<int> sol;
	int len = seq.size();
	if(len < 1)
		return sol;
	X = seq;
	M.resize(len+1);
	P.resize(len+1);
	L = 1;
	M[0] = P[0] = -1;
	M[1] = 0;
	for(int i = 1; i < len; i++){
		int j = bsearch(i, 1, L);
		P[i] = M[j];
		if(j == L || X[i] < X[M[j+1]]){
			M[j+1] = i;
			L = max(L, j+1);
		}
	}
	sol.resize(L);
	for(int i = M[L], j = L-1; i >= 0; i = P[i], j--)
		sol[j] = i;
	return sol;
}

int main(int argc, char* argv[]){
	vector<int> seq, sol;
	int n, tmp, len;
	while(scanf("%d", &n) > 0){
		seq.clear();
		while(n--){
			scanf("%d", &tmp);
			seq.push_back(tmp);
		}
		sol = lis(seq);
		len = sol.size();
		printf("%d\n", len);
		for(int i = 0; len > 0 && i < len; i++){
			printf("%d%c", sol[i], i+1 == len ? '\n' : ' ');
		}
	}
	return 0;
}