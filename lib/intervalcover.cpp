/**
* Filename: intervalcover.cpp
* Author:   Markus Niemelä
*/

#include "intervalcover.h"

using namespace std;

const double EPS = 1e-9;

/*
Function:		cover(double, double, vector<pair <double, double> >)

Description:	Given an interval [a,b] and a vector of intervals, find the optimal
				way to cover [a,b]. The function keeps greedily adding the largest
				interval that covers the lowest uncovered point until [a,b] is covered.

Input:			a: The lowest point of the interval to be covered.
				b: The highest point of the interval to be covered.
				intervals: The intervals with which to cover the interval [a,b].
				
Output:			A vector containing the indices of the intervals used to cover [a,b].
				If [a,b] cannot be covered, the vector is empty.
*/

vector<int> cover(double a, double b, vector<pair <double, double> > intervals){
	int n = intervals.size();
	vector<int> sol;
	map<pair <double, double>, int > index;
	double new_right, right = a;
	int cnt, i, j;
	bool flag = false, added;
	for(i = 0; i < n; ++i){
		index[intervals[i]] = i;
	}
	sort(intervals.begin(), intervals.end());
	new_right = a - EPS;
	for(cnt = i = j = 0; i < n; i = j){
		added = false;
		while(j < n && intervals[j].first <= right){
			if(intervals[j].second > new_right){
				new_right = intervals[j].second;
				if(added)
					sol[cnt] = index[intervals[j]];
				else
					sol.push_back(index[intervals[j]]);
				added = flag = true;
			}
			j++;
		}
		cnt++;
		right = new_right;
		if(right + EPS > b || j == i){
			break;
		}
	}
	if(!(right + EPS > b && flag))
		sol.clear();
	return sol;
}