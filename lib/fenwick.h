/**
* Filename:	fenwick.h
* Author:   Markus Niemelä
*/
#ifndef FENWICK_H
#define FENWICK_H

#include <cstdio>
#include <vector>

class FenwickTree{
	private:
        std::vector<long long> ft;
    public:
        FenwickTree(int);
        long long sum(int);
        long long sum(int, int);
        void add(int, int);
};

#endif