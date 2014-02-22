/**
* Filename: unionfind.cpp
* Author:   Markus Niemelä
*/

#include "unionfind.h"

using namespace std;

/*
Union-Find Disjoint Sets is a data structure for storing a set of
disjoint sets where it is very efficient (~O(1)) to find which set
an element belongs to and to merge two sets.

The disjoint sets are represented by a forest of trees, where the
root of a tree is the representative element for that set.
*/

/*
Function:		UFNode::root()

Description: 	Returns the root of the node by searching recursively, utilizing path
				compression on all visited nodes to speed up future lookups.
*/
UFNode* UFNode::root(){
	if(r != this)
		r = r->root();
	return r;
}

/*
Function:		UFNode::join()

Description: 	Joins the node to another node v. Rank is an upper bound for the tree's
				depth, and the tree with the lowest rank is inserted into the tree of the
				other node. Only if the rank is equal is the upper bound incremented, and
				the tree of node v is added to the tree of this node (although the opposite
				would be equally valid as an implementation).
*/
void UFNode::join(UFNode* v){
	if(root() != v->root()){
		if(r->rank < v->r->rank){
			r->r = v->r;
		}
		else if(r->rank > v->r->rank){
			v->r->r = r;
		}
		else{
			v->r->r = r;
			r->rank++;
		}
	}
}

/*
Constructor for the UnionFindSet class.

Input:		n: The number of initial sets.
*/
UnionFindSet::UnionFindSet(int n) : sets(n){
	for(int i = 0; i < n; i++){
		sets[i] = new UFNode();
		sets[i]->r = sets[i];
		sets[i]->rank = 0;
	}
}

/*
Function:		UnionFindSet::join(int, int)

Description:	Joins the set of a to the set of b.
*/
void UnionFindSet::join(int a, int b){
	sets[a]->join(sets[b]);
}

/*
Function:		UnionFindSet::find(int)

Description:	Returns a pointer to the root node of the set which a belongs to.
*/
UFNode* UnionFindSet::find(int a){
	return sets[a]->root();
}