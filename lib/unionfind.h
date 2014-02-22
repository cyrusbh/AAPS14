/**
* Filename: unionfind.h
* Author:   Markus Niemelä
*/
#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <cstdio>
#include <vector>


struct UFNode {
    UFNode* r;
	int rank;
    UFNode* root();
    void join(UFNode*);
};

class UnionFindSet{
	private:
		std::vector<UFNode*> sets;
	public:
		UnionFindSet(int);
		void join(int, int);
		UFNode* find(int);
};

#endif