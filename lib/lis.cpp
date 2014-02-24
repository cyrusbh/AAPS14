/**
* Filename: lis.cpp
* Author:   Markus Niemelä
*/

#include "lis.h"

// Longest increasing subsequence. Implementation of algorithm found at 
// http://en.wikipedia.org/wiki/Longest_increasing_subsequence#Efficient_algorithms 

using namespace std;

vector<int> M, P, X;
int L;

/*
Function:		bsearch(int, int, int)

Description:	Returns the index j such that lo<=j<=hi, X[M[j]] < X[idx], or 0 if no such index exists. 
*/
int bsearch(int idx, int lo, int hi){
	if(lo >= hi)
		return X[M[lo]] < X[idx] ? lo : lo-1;
	return X[M[(lo+hi)/2]] < X[idx] ? bsearch(idx, (lo+hi)/2+1, hi) : bsearch(idx, lo, (lo+hi)/2-1);
}

/*
Function:		lis(vector<int>)

Description:	Given a sequence of integers, find a longest increasing subsequence.
				Returns a vector of indices identifying the first encountered longest increasing subsequence.
*/
vector<int> lis(vector<int> seq){
	vector<int> sol;
	int len = seq.size();
	if(len < 1)
		return sol;
	X = seq;
	M.resize(len+1);
	P.resize(len+1);
	//Initialize with first value (needed for bsearch)
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