/**
* Filename: graph.h
* Author:   Markus Niemelä
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

struct edge{
	int v, d, t0, P;
};

typedef std::pair<int, int> ii;
typedef std::pair<int, ii> iii;
typedef std::vector<int> vi;
typedef std::vector<ii> vii;
typedef std::vector<edge> ve;
#define INF 1000000000

std::vector<vi> floyd_warshall(const std::vector<vi>);
std::vector<ii> dijkstra(std::vector<vii>, int);
std::vector<ii> timetable(std::vector<ve>, int);
std::vector<ii> bellman_ford(std::vector<vii>, int);
std::vector<vii> prim(std::vector<vii>, int &);

#endif