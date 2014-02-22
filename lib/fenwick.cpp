/**
* Filename:	fenwick.cpp
* Author:   Markus Niemelä
*/

#include "fenwick.h"

using namespace std;

/*
The Fenwick tree, or binary indexed tree, is a data structure for computing
range sum queries with updates, both in O(log n).

Each element i stores the range sum query for the interval [i-LSOne(i), i],
where LSOne(i) is the least significant one in the binary representation of i.
*/

/*
Constructor for the FenwickTree class.

Input:		n: The size of the tree.
*/
FenwickTree::FenwickTree(int n) : ft(n+1, 0){};


/*
Function:		FenwickTree::sum(int)

Description:	The range sum query for the range [1,b].
				Iterates through elements by removing the least significant one
				and sums the range sums in O(log n).
*/
long long FenwickTree::sum(int b) {
	long long sum = 0; 
	for (; b; b -= (b & -b)) 
		sum += ft[b];
	return sum;
}

/*
Function:		FenwickTree::sum(int, int)

Description:	The range sum query for the range [a,b].
				Iterates through elements by removing the least significant one
				and sums the range sums in O(log n).
*/
long long FenwickTree::sum(int a, int b) { 
	return sum(b) - (a == 1 ? 0 : sum(a - 1));
}

/*
Function:		add(int, int)

Description:	Adds v to the index k.
				Iterates through elements by adding the least significant one
				and updates the range sums in O(log n).
*/
void FenwickTree::add(int k, int v) {
	for (; k < (int)ft.size(); k += (k & -k))
		ft[k] += v; 
}